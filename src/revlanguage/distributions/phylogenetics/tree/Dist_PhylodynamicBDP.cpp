#include <stddef.h>
#include <iosfwd>
#include <string>
#include <vector>

#include "ArgumentRule.h"
#include "ArgumentRules.h"
// #include "ConstantRateSerialSampledBirthDeathProcess.h"
#include "Dist_PhylodynamicBDP.h"
#include "ModelVector.h"
#include "OptionRule.h"
#include "EpisodicBirthDeathSamplingTreatmentProcess.h"
#include "Probability.h"
#include "RealPos.h"
#include "RlString.h"
#include "RlTaxon.h"
#include "RlTimeTree.h"
#include "AbstractBirthDeathProcess.h"
#include "ConstantNode.h"
#include "DagNode.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "IndirectReferenceFunction.h"
#include "ModelObject.h"
#include "RbVector.h"
#include "RevNullObject.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RevVariable.h"
#include "RlBirthDeathProcess.h"
#include "RlConstantNode.h"
#include "Taxon.h"
#include "TypeSpec.h"
#include "TypedDagNode.h"
#include "TypedFunction.h"
#include "UserFunctionNode.h"

namespace RevBayesCore { class Tree; }

using namespace RevLanguage;

/**
 * Default constructor.
 *
 * The default constructor does nothing except allocating the object.
 */
Dist_PhylodynamicBDP::Dist_PhylodynamicBDP() : BirthDeathProcess()
{

}


/**
 * The clone function is a convenience function to create proper copies of inherited objected.
 * E.g. a.clone() will create a clone of the correct type even if 'a' is of derived type 'b'.
 *
 * \return A new copy of the process.
 */
Dist_PhylodynamicBDP* Dist_PhylodynamicBDP::clone( void ) const
{
    return new Dist_PhylodynamicBDP(*this);
}


/**
 * Create a new internal distribution object.
 *
 * This function simply dynamically allocates a new internal distribution object that can be
 * associated with the variable. The internal distribution object is created by calling its
 * constructor and passing the distribution-parameters (other DAG nodes) as arguments of the
 * constructor. The distribution constructor takes care of the proper hook-ups.
 *
 * \return A new internal distribution object.
 */
RevBayesCore::AbstractBirthDeathProcess* Dist_PhylodynamicBDP::createDistribution( void ) const
{
    // get the parameters

    // the start age
    RevBayesCore::TypedDagNode<double>* sa       = static_cast<const RealPos &>( start_age->getRevObject() ).getDagNode();

    // the start condition
    bool uo = ( start_condition == "originAge" ? true : false );

    // sampling condition
    const std::string& cond                     = static_cast<const RlString &>( condition->getRevObject() ).getValue();

    // get the taxa to simulate either from a vector of rev taxon objects or a vector of names
    std::vector<RevBayesCore::Taxon> tn = static_cast<const ModelVector<Taxon> &>( taxa->getRevObject() ).getValue();

    RevBayesCore::AbstractBirthDeathProcess* d;

    // To avoid fracturing implementations, constant-rate processes call the piecewise-constant version, which can accomodate this

    // birth rate
    RevBayesCore::DagNode* b_s = lambda->getRevObject().getDagNode();
    // death rate
    RevBayesCore::DagNode* d_s = mu->getRevObject().getDagNode();
    // serial sampling rate
    RevBayesCore::DagNode* s_s = phi->getRevObject().getDagNode();
    // treatment probability
    RevBayesCore::DagNode* t_s = r->getRevObject().getDagNode();

    // There are no bursts or mass extinctions in the standard phylodynamic application
    // birth burst
    RevBayesCore::DagNode* b_e = NULL;
    // death burst (mass extinction)
    RevBayesCore::DagNode* d_e = NULL;
    // event sampling
    RevBayesCore::DagNode* s_e = NULL;
    if ( Phi->getRevObject() != RevNullObject::getInstance() )
    {
        s_e = Phi->getRevObject().getDagNode();
    }
    // event treatment
    RevBayesCore::DagNode* t_e = NULL;
    if ( r_event->getRevObject() != RevNullObject::getInstance() )
    {
        t_e = r_event->getRevObject().getDagNode();
    }

    // global rate change times
    RevBayesCore::TypedDagNode<RevBayesCore::RbVector<double> >* gt = NULL;
    if ( timeline->getRevObject() != RevNullObject::getInstance() )
    {
        gt = static_cast<const ModelVector<RealPos> &>( timeline->getRevObject() ).getDagNode();
    }

    // parameter-specific timelines
    RevBayesCore::TypedDagNode<RevBayesCore::RbVector<double> >* lt = NULL;
    if ( lambda_timeline->getRevObject() != RevNullObject::getInstance() )
    {
        lt = static_cast<const ModelVector<RealPos> &>( lambda_timeline->getRevObject() ).getDagNode();
    }

    RevBayesCore::TypedDagNode<RevBayesCore::RbVector<double> >* mt = NULL;
    if ( mu_timeline->getRevObject() != RevNullObject::getInstance() )
    {
        mt = static_cast<const ModelVector<RealPos> &>( mu_timeline->getRevObject() ).getDagNode();
    }

    RevBayesCore::TypedDagNode<RevBayesCore::RbVector<double> >* pt = NULL;
    if ( phi_timeline->getRevObject() != RevNullObject::getInstance() )
    {
        pt = static_cast<const ModelVector<RealPos> &>( phi_timeline->getRevObject() ).getDagNode();
    }

    RevBayesCore::TypedDagNode<RevBayesCore::RbVector<double> >* rt = NULL;
    if ( r_timeline->getRevObject() != RevNullObject::getInstance() )
    {
        rt = static_cast<const ModelVector<RealPos> &>( r_timeline->getRevObject() ).getDagNode();
    }

    // There are no bursts or mass extinctions in the standard phylodynamic application
    RevBayesCore::TypedDagNode<RevBayesCore::RbVector<double> >* Lt = NULL;
    RevBayesCore::TypedDagNode<RevBayesCore::RbVector<double> >* Mt = NULL;

    RevBayesCore::TypedDagNode<RevBayesCore::RbVector<double> >* Pt = NULL;
    if ( Phi_timeline->getRevObject() != RevNullObject::getInstance() )
    {
        Pt = static_cast<const ModelVector<RealPos> &>( Phi_timeline->getRevObject() ).getDagNode();
    }

    d = new RevBayesCore::EpisodicBirthDeathSamplingTreatmentProcess(sa,
                                                                     b_s,
                                                                     d_s,
                                                                     s_s,
                                                                     t_s,
                                                                     b_e,
                                                                     d_e,
                                                                     s_e,
                                                                     t_e,
                                                                     gt,
                                                                     lt,
                                                                     mt,
                                                                     pt,
                                                                     rt,
                                                                     Lt,
                                                                     Mt,
                                                                     Pt,
                                                                     cond,
                                                                     tn,
                                                                     uo,
                                                                     NULL);

    return d;
}


/**
 * Get Rev type of object
 *
 * \return The class' name.
 */
const std::string& Dist_PhylodynamicBDP::getClassType( void )
{

    static std::string rev_type = "Dist_PhylodynamicBDP";

    return rev_type;
}


/**
 * Get class type spec describing type of an object from this class (static).
 *
 * \return TypeSpec of this class.
 */
const TypeSpec& Dist_PhylodynamicBDP::getClassTypeSpec( void )
{

    static TypeSpec rev_type_spec = TypeSpec( getClassType(), new TypeSpec( BirthDeathProcess::getClassTypeSpec() ) );

    return rev_type_spec;
}


/**
 * Get the alternative Rev names (aliases) for the constructor function.
 *
 * \return Rev aliases of constructor function.
 */
std::vector<std::string> Dist_PhylodynamicBDP::getDistributionFunctionAliases( void ) const
{
    // create alternative constructor function names variable that is the same for all instance of this class
    std::vector<std::string> a_names;
    a_names.push_back( "PhylodynamicBDP" );

    return a_names;
}


/**
 * Get the Rev name for the distribution.
 * This name is used for the constructor and the distribution functions,
 * such as the density and random value function
 *
 * \return Rev name of constructor function.
 */
std::string Dist_PhylodynamicBDP::getDistributionFunctionName( void ) const
{
    // create a distribution name variable that is the same for all instance of this class
    std::string d_name = "PhylodynamicBirthDeathProcess";

    return d_name;
}


/**
 * Get the member rules used to create the constructor of this object.
 *
 * The member rules of the constant-rate birth-death process are:
 * (1) the speciation rate lambda which must be a positive real.
 * (2) the extinction rate mu that must be a positive real.
 * (3) all member rules specified by BirthDeathProcess.
 *
 * \return The member rules.
 */
const MemberRules& Dist_PhylodynamicBDP::getParameterRules(void) const
{

    static MemberRules dist_member_rules;
    static bool rules_set = false;

    if ( rules_set == false )
    {
        std::vector<std::string> aliases;
        aliases.push_back("rootAge");
        aliases.push_back("originAge");
        dist_member_rules.push_back( new ArgumentRule( aliases, RealPos::getClassTypeSpec()    , "The start time of the process.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY ) );

        std::vector<TypeSpec> paramTypes;
        paramTypes.push_back( RealPos::getClassTypeSpec() );
        paramTypes.push_back( ModelVector<RealPos>::getClassTypeSpec() );
        dist_member_rules.push_back( new ArgumentRule( "lambda",  paramTypes, "The birth rate(s).", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY ) );
        dist_member_rules.push_back( new ArgumentRule( "mu",      paramTypes, "The death rate(s).", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY ) );
        dist_member_rules.push_back( new ArgumentRule( "phi",     paramTypes, "The serial sampling rate(s).", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY ) );
        dist_member_rules.push_back( new ArgumentRule( "r",       paramTypes, "The probabilit(y|ies) of death upon sampling (treatment).", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY, new Probability(1.0) ) );

        std::vector<TypeSpec> event_sampling_paramTypes;
        event_sampling_paramTypes.push_back( Probability::getClassTypeSpec() );
        event_sampling_paramTypes.push_back( ModelVector<Probability>::getClassTypeSpec() );
        dist_member_rules.push_back( new ArgumentRule( "Phi",     event_sampling_paramTypes, "The probability of sampling taxa at sampling events (at present only if input is scalar).", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY, new Probability(0.0) ) );

        std::vector<TypeSpec> other_event_paramTypes;
        other_event_paramTypes.push_back( ModelVector<Probability>::getClassTypeSpec() );
        dist_member_rules.push_back( new ArgumentRule( "R",       other_event_paramTypes, "The treatment probabilities for the sampling events (excluding sampling at present).", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY, NULL ) );

        dist_member_rules.push_back( new ArgumentRule( "timeline",    ModelVector<RealPos>::getClassTypeSpec(), "The rate interval change times of the piecewise constant process.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY, NULL ) );
        dist_member_rules.push_back( new ArgumentRule( "lambdaTimeline",    ModelVector<RealPos>::getClassTypeSpec(), "The rate interval change times of the speciation rate.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY, NULL ) );
        dist_member_rules.push_back( new ArgumentRule( "muTimeline",        ModelVector<RealPos>::getClassTypeSpec(), "The rate interval change times of the extinction rate.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY, NULL ) );
        dist_member_rules.push_back( new ArgumentRule( "phiTimeline",       ModelVector<RealPos>::getClassTypeSpec(), "The rate interval change times of the sampling rate.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY, NULL ) );
        dist_member_rules.push_back( new ArgumentRule( "rTimeline",         ModelVector<RealPos>::getClassTypeSpec(), "The rate interval change times of the (serial) treatment probability.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY, NULL ) );
        dist_member_rules.push_back( new ArgumentRule( "PhiTimeline",       ModelVector<RealPos>::getClassTypeSpec(), "The rate interval change times of the sampling rate.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY, NULL ) );

        std::vector<std::string> optionsCondition;
        optionsCondition.push_back( "time" );
        optionsCondition.push_back( "survival" );
        optionsCondition.push_back( "sampling" );
        dist_member_rules.push_back( new OptionRule( "condition", new RlString("time"), optionsCondition, "The condition of the process." ) );
        dist_member_rules.push_back( new ArgumentRule( "taxa"  , ModelVector<Taxon>::getClassTypeSpec(), "The taxa used for initialization.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY ) );

        rules_set = true;
    }

    return dist_member_rules;
}


/**
 * Get type-specification on this object (non-static).
 *
 * \return The type spec of this object.
 */
const TypeSpec& Dist_PhylodynamicBDP::getTypeSpec( void ) const
{

    static TypeSpec ts = getClassTypeSpec();

    return ts;
}


/**
 * Set a member variable.
 *
 * Sets a member variable with the given name and store the pointer to the variable.
 * The value of the variable might still change but this function needs to be called again if the pointer to
 * the variable changes. The current values will be used to create the distribution object.
 *
 * \param[in]    name     Name of the member variable.
 * \param[in]    var      Pointer to the variable.
 */
void Dist_PhylodynamicBDP::setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var)
{
    if ( name == "lambda" )
    {
        lambda = var;
    }
    else if ( name == "mu" )
    {
        mu = var;
    }
    else if ( name == "phi" )
    {
        phi = var;
    }
    else if ( name == "r" )
    {
        r = var;
    }
    else if ( name == "Phi" )
    {
        Phi = var;
    }
    else if ( name == "R" )
    {
        r_event = var;
    }
    else if ( name == "rootAge" || name == "originAge" )
    {
        start_age = var;
        start_condition = name;
    }
    else if ( name == "timeline" )
    {
        timeline = var;
    }
    else if ( name == "lambdaTimeline" )
    {
        lambda_timeline = var;
    }
    else if ( name == "muTimeline" )
    {
        mu_timeline = var;
    }
    else if ( name == "phiTimeline" )
    {
        phi_timeline = var;
    }
    else if ( name == "rTimeline" )
    {
        r_timeline = var;
    }
    else if ( name == "PhiTimeline" )
    {
        Phi_timeline = var;
    }
    else
    {
        BirthDeathProcess::setConstParameter(name, var);
    }

}
