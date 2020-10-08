//
//  LKJPartialDistribution.cpp
//  revbayes
//
//  Created by Michael R. May on 2017-08-29.
//  Copyright (c) 2014 revbayes team. All rights reserved.
//

#include "LKJPartialDistribution.h"

#include "RandomNumberFactory.h"
#include "DistributionLKJ.h"

#include "TypedDagNode.h"

namespace RevBayesCore { class DagNode; }
namespace RevBayesCore { class RandomNumberGenerator; }

using namespace RevBayesCore;

LKJPartialDistribution::LKJPartialDistribution(const TypedDagNode<double> *e, size_t d)  :
    TypedDistribution<RevBayesCore::MatrixReal>( new MatrixReal(d) ),
    eta( e ),
    dim( d )
{
    
    // add the parameters to our set (in the base class)
    // in that way other class can easily access the set of our parameters
    // this will also ensure that the parameters are not getting deleted before we do
    addParameter( e );
    
    redrawValue();
    
    value->setCholesky(true);
    
}


LKJPartialDistribution* LKJPartialDistribution::clone(void) const
{

    return new LKJPartialDistribution(*this);
}


/** Swap a parameter of the distribution */
void LKJPartialDistribution::swapParameterInternal(const DagNode *oldP, const DagNode *newP)
{
    
    if (oldP == eta)
    {
        eta = static_cast<const TypedDagNode<double>* >(newP);
    }

}


double LKJPartialDistribution::computeLnProbability(void)
{
    
    return RbStatistics::LKJ::lnPdfPartial(eta->getValue(), getValue());;
    
}

void LKJPartialDistribution::redrawValue(void)
{

    RandomNumberGenerator* rng = GLOBAL_RNG;
    *value = RbStatistics::LKJ::rvPartial(eta->getValue(), dim, *rng);

}
