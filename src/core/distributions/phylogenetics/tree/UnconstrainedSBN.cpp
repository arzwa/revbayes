#include <boost/foreach.hpp>
#include "Clade.h"
#include "DistributionGamma.h"
#include "DistributionGeneralizedGamma.h"
#include "DistributionLognormal.h"
#include "DistributionScaledDirichlet.h"
#include "RandomNumberFactory.h"
#include "RandomNumberGenerator.h"
#include "RbConstants.h"
#include "RbException.h"
#include "TopologyNode.h"
#include "UnconstrainedSBN.h"

#include <algorithm>
#include <cmath>

using namespace RevBayesCore;

// Empty constructor (needed by smart moves)
UnconstrainedSBN::UnconstrainedSBN(void) : TypedDistribution<Tree>( new Tree() ),
    parameters( ),
    taxa( )
{

}

UnconstrainedSBN::UnconstrainedSBN(const SBNParameters parameters) : TypedDistribution<Tree>( new Tree() ),
    parameters( parameters ),
    taxa( parameters.getTaxa() )
{
    // Class SBNParameters handles parameterization of these edge_length_distributions
    // Here we simply use those parameters
    // Parameters are set either by calling a learn___() function or reading in an SBN
    simulateTree();

}


UnconstrainedSBN::~UnconstrainedSBN()
{
    // the tree will be deleted automatically by the base class

}


UnconstrainedSBN* UnconstrainedSBN::clone( void ) const
{

    return new UnconstrainedSBN( *this );
}

double UnconstrainedSBN::computeLnProbability( void )
{
    double lnProbability = 0.0;

    // Here we compute the probability of the tree topology according to the SBN

    lnProbability += computeLnProbabilityUnrootedTopologyMarginalize();

    // Add branch lengths
    lnProbability += computeLnProbabilityBranchLengths();

    return lnProbability;
}

double UnconstrainedSBN::computeLnProbabilityBranchLengths( void )
{
    double lnProbability = 0.0;

    std::map<RbBitSet,std::vector<double> > edge_length_params = parameters.getEdgeLengthDistributionParameters();

    // Only needed if we're using a compound parameterization on branch lengths and tree length
    std::vector<double> branch_length_alpha;
    std::vector<double> branch_length_beta;
    std::vector<double> branch_length_simplex_coords;
    double tree_length = value->getTreeLength();

    // Get branch lengths
    const std::vector<TopologyNode*> tree_nodes = value->getNodes();
    for (size_t i=0; i<tree_nodes.size(); ++i)
    {
      if (!tree_nodes[i]->isRoot())
      {
        // Subsplit this_subsplit = tree_nodes[i]->getSubsplit(taxa);
        // RbBitSet this_split = this_subsplit.asSplitBitset();
        RbBitSet this_split = tree_nodes[i]->getSubsplit(taxa).asSplitBitset();
        // std::cout << "About to get branch length parameters for split " << this_split << std::endl;

        std::vector<double> these_params = edge_length_params[this_split];
        if ( parameters.getBranchLengthApproximationMethod() == "compound" )
        {
          branch_length_alpha.push_back(these_params[0]);
          branch_length_beta.push_back(these_params[1]);
          branch_length_simplex_coords.push_back((tree_nodes[i]->getBranchLength())/tree_length);
        }
        else if ( parameters.getBranchLengthApproximationMethod() == "gammaMOM" )
        {
          // std::cout << "Computing branch length probability for branch " << i << ", lnProb = " << RbStatistics::Gamma::pdf(these_params[0], these_params[1], tree_nodes[i]->getBranchLength()) << std::endl;
          // std::cout << "gamma shape: " << these_params[0] << "; gamma rate: " << these_params[1] << "; evaluating density at x=" << tree_nodes[i]->getBranchLength() << std::endl;
          lnProbability += RbStatistics::Gamma::lnPdf(these_params[0], these_params[1], tree_nodes[i]->getBranchLength());
        }
        else if ( parameters.getBranchLengthApproximationMethod() == "generalizedGamma" )
        {
          // std::cout << "generalized gamma a: " << these_params[0] << "; generalized gamma c: " << these_params[1] << "; generalized gamma l: " << these_params[2] << "; evaluating density at x=" << tree_nodes[i]->getBranchLength() << std::endl;
          // std::cout << "Computing branch length probability for branch " << i << ", lnProb = " << RbStatistics::GeneralizedGamma::lnPdf(these_params[0], these_params[1], these_params[2], tree_nodes[i]->getBranchLength()) << std::endl;
          lnProbability += RbStatistics::GeneralizedGamma::lnPdf(these_params[0], these_params[1], these_params[2], tree_nodes[i]->getBranchLength());
        }
        else
        {
          // // std::cout << "Computing branch length probability for branch " << i << ", lnProb = " << RbStatistics::Lognormal::pdf(these_params[0], these_params[1], tree_nodes[i]->getBranchLength()) << std::endl;
          // // std::cout << "lognormal mu: " << these_params[0] << "; lognormal sigma: " << these_params[1] << "; evaluating density at x=" << tree_nodes[i]->getBranchLength() << std::endl;
          lnProbability += RbStatistics::Lognormal::lnPdf(these_params[0], these_params[1], tree_nodes[i]->getBranchLength());
        }

      }
    }

    if ( parameters.getBranchLengthApproximationMethod() == "compound" )
    {
      // Tree length probability
      RbBitSet whole_tree = RbBitSet(taxa.size(),true);
      std::vector<double> these_params = edge_length_params[whole_tree];
      lnProbability += RbStatistics::Gamma::lnPdf(these_params[0], these_params[1], tree_length);

      // Branch length proportion probability
      lnProbability += RbStatistics::ScaledDirichlet::lnPdf(branch_length_alpha,branch_length_beta,branch_length_simplex_coords);

    }

    return lnProbability;
}

double UnconstrainedSBN::computeLnProbabilityUnrootedTopologyMarginalize( void )
{
    // Make the tree properly rooted so that rooting to branches has the desired effect

    double lnProbability = 0.0;

    std::vector<double> lnl_given_root;
    double offset = RbConstants::Double::neginf;
    // sum over rooting locations
    // std::cout << "marginalizing over " << value->getNumberOfNodes() << " possible rooting locations" << std::endl;
    for (size_t ri=0; ri < value->getNumberOfNodes(); ++ri)
    {
      if (!(value->getNode(ri).isRoot()))
      {
        Tree *tree_rooted = value->clone();
        tree_rooted->makeRooted(tree_rooted->getNode(ri),true);
        double lnl = parameters.computeLnProbabilityRootedTopology( *(tree_rooted) );
        // std::cout << "at" << ri << ", lnL_tot = " << lnl << std::endl;
        lnl_given_root.push_back(lnl);
        delete tree_rooted;
      }
    }
    // std::cout << "marginalization complete" << std::endl;
    lnProbability = logSumExp(lnl_given_root);

    // std::cout << "computed lnProb" << std::endl;

    return lnProbability;
}

double UnconstrainedSBN::logSumExp( std::vector<double> &x )
{
    double offset = RbConstants::Double::neginf;
    double sum = 0.0;
    for (size_t i=0; i < x.size(); ++i)
    {
      if (x[i] > offset)
      {
        offset = x[i];
      }
    }

    for (size_t i=0; i < x.size(); ++i)
    {
      sum += exp(x[i] - offset);
    }

    return log(sum) + offset;
}

double UnconstrainedSBN::logSumExp( double &x1, double &x2 )
{
    double offset = std::max(x1,x2);

    x1 -= offset;
    x2 -= offset;

    double exp_x1 = exp(x1);
    double exp_x2 = exp(x2);

    return log(exp_x1 + exp_x2) + offset;
}

double UnconstrainedSBN::logSumExpWeights( std::vector<double> &x, std::vector<double> &p )
{
    double offset = RbConstants::Double::neginf;
    double sum = 0.0;
    for (size_t i=0; i < x.size(); ++i)
    {
      if (x[i] > offset)
      {
        offset = x[i];
      }
    }

    for (size_t i=0; i < x.size(); ++i)
    {
      sum += p[i] * exp(x[i] - offset);
    }

    return log(sum) + offset;
}

double UnconstrainedSBN::logSumExpWeights( double &x1, double &x2, double &p1, double &p2 )
{
    double offset = std::max(x1,x2);

    double exp_x1 = p1 * exp(x1 - offset);
    double exp_x2 = p2 * exp(x2 - offset);

    return log(exp_x1 + exp_x2) + offset;
}


void UnconstrainedSBN::redrawValue( void )
{
    simulateTree();
}

void UnconstrainedSBN::setValue(RevBayesCore::Tree *v, bool force)
{

    // delegate to super class
    TypedDistribution<Tree>::setValue( v, force );

}


void UnconstrainedSBN::simulateTree( void )
{

    // Get the rng
    RandomNumberGenerator* rng = GLOBAL_RNG;

    // the tree object
    // Tree *psi = value;
    Tree *psi = new Tree();

    // We always draw a rooted tree, if we want to unroot we need it to first be rooted
    psi->setRooted(true);

    // For drawing branch lengths
    std::map<RbBitSet,std::vector<double> > edge_length_params = parameters.getEdgeLengthDistributionParameters();

    // create the tip nodes
    std::vector<TopologyNode*> tip_nodes;
    for (size_t i=0; i<taxa.size(); ++i)
    {
        // create the i-th taxon
        TopologyNode* node = new TopologyNode( taxa[i], i );
        tip_nodes.push_back(node);
    }

    // List of active tree nodes/subsplits
    // We pair them such that each tree node corresponds to the subsplit it defines
    std::vector<std::pair<Subsplit,TopologyNode*> > active;

    // Root split
    double u = rng->uniform01();
    TopologyNode* root = new TopologyNode();
    root->setNodeType(false, true, false);
    Subsplit root_split = parameters.drawRootSplit();
    active.push_back(std::make_pair(root_split,root));

    // All other subplits
    while (active.size() > 0)
    {
      // Get a node/subsplit to work on, remove that from list
      std::pair<Subsplit,TopologyNode*> this_parent = active.back();
      active.pop_back();

      Subsplit this_parent_subsplit = this_parent.first;
      TopologyNode* this_parent_node = this_parent.second;

      TopologyNode* Y_child_node;
      TopologyNode* Z_child_node;

      // Choose subsplit of Y
      Subsplit Y_child = parameters.drawSubsplitForY(this_parent_subsplit);
      if ( Y_child.isFake() )
      {
        // This is a tip, we don't add it to the active pile
        Y_child_node = tip_nodes[Y_child.getYBitset().getFirstSetBit()];
      }
      else
      {
        // This is an internal node
        Y_child_node = new TopologyNode();
        active.push_back(std::make_pair(Y_child,Y_child_node));
      }

      // Choose subsplit of Z
      Subsplit Z_child = parameters.drawSubsplitForZ(this_parent_subsplit);
      if ( Z_child.isFake() )
      {
        // This is a tip, we don't add it to the active pile
        Z_child_node = tip_nodes[Z_child.getYBitset().getFirstSetBit()];
      }
      else
      {
        // This is an internal node
        Z_child_node = new TopologyNode();
        active.push_back(std::make_pair(Z_child,Z_child_node));
      }

      // Attach nodes to eachother
      this_parent_node->addChild(Y_child_node);
      this_parent_node->addChild(Z_child_node);
      Y_child_node->setParent(this_parent_node);
      Z_child_node->setParent(this_parent_node);

    }

    // initialize the topology by setting the root
    psi->setRoot(root, true);

    // TODO: with the selection of taxa for tips using bitsets, taxon names are paired to indices, the following may be extraneous
    // re-couple tip node names with tip indices
    // this is necessary because otherwise tip names get scrambled across replicates
    for (size_t i=0; i<taxa.size(); i++)
    {
    	psi->getTipNodeWithName(taxa[i].getName()).setIndex(i);
    }

    psi->unroot();
    psi->setRooted( false );
    psi->orderNodesByIndex();

    // Add branch lengths
    double brlen_sum = 0.0;
    const std::vector<TopologyNode*> tree_nodes = psi->getNodes();
    for (size_t i=0; i<tree_nodes.size(); ++i)
    {
      if (!tree_nodes[i]->isRoot())
      {
        double brlen;
        // Subsplit this_subsplit = tree_nodes[i]->getSubsplit(taxa);
        // RbBitSet this_split = this_subsplit.asSplitBitset();
        RbBitSet this_split = tree_nodes[i]->getSubsplit(taxa).asSplitBitset();

        std::vector<double> these_params = edge_length_params[this_split];
        if ( parameters.getBranchLengthApproximationMethod() == "gammaMOM" || parameters.getBranchLengthApproximationMethod() == "compound" )
        {
          brlen = RbStatistics::Gamma::rv(these_params[0], these_params[1], *rng);
        }
        else if ( parameters.getBranchLengthApproximationMethod() == "generalizedGamma" )
        {
          brlen = RbStatistics::GeneralizedGamma::rv(these_params[0], these_params[1], these_params[2], *rng);
        }
        else
        {
          brlen  = RbStatistics::Lognormal::rv(these_params[0], these_params[1], *rng);
        }
        tree_nodes[i]->setBranchLength(brlen,false);
        brlen_sum += brlen;
      }
    }

    // If doing compound parameterization, readjust tree length
    if ( parameters.getBranchLengthApproximationMethod() == "compound" )
    {
      RbBitSet whole_tree = RbBitSet(taxa.size(),true);
      std::vector<double> these_params = edge_length_params[whole_tree];
      double tree_length = RbStatistics::Gamma::rv(these_params[0], these_params[1], *rng);
      double scaling_factor = tree_length/brlen_sum;
      for (size_t i=0; i<tree_nodes.size(); ++i)
      {
        if (!tree_nodes[i]->isRoot())
        {
          tree_nodes[i]->setBranchLength(tree_nodes[i]->getBranchLength()*scaling_factor,false);
        }
      }
    }

  // finally store the new value
    delete value;
    value = psi;

}


/** Swap a parameter of the distribution */
void UnconstrainedSBN::swapParameterInternal( const DagNode *oldP, const DagNode *newP )
{
  // SBNs have their parameters set once and they do not change afterwards
}

// /**
//  * We check here if all the constraints are satisfied.
//  * These are hard constraints, that is, the clades must be monophyletic.
//  *
//  * \return     True if the constraints are matched, false otherwise.
//  */
// bool UnconstrainedSBN::matchesConstraints( void )
// {
//
//     if ( constraints.empty() == true )
//     {
// 		return true;
// 	}
//     else
//     {
//
// 		const TopologyNode &root = value->getRoot();
// 		for (std::vector<Clade>::iterator it = constraints.begin(); it != constraints.end(); ++it)
// 		{
// 			if ( root.containsClade( *it, true ) == false )
// 			{
// 				return false;
// 			}
// 		}
//
// 		return true;
// 	}
//
// }