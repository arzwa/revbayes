#include "LognormalWithOffsetDistribution.h"

#include "DistributionLognormal.h"
#include "RandomNumberFactory.h"
#include "RbConstants.h"

#include "TypedDagNode.h"

namespace RevBayesCore { class DagNode; }

using namespace RevBayesCore;

/** LogNormalWithOffsetDistribution constructor
 * @param m The mean of the natural logarithm of the variable
 * @param s The standard deviation of the natural logarithm of the variable
 * @param o Offset
*/

LognormalWithOffsetDistribution::LognormalWithOffsetDistribution(const TypedDagNode<double> *m, const TypedDagNode<double> *s, const TypedDagNode<double> *o) : ContinuousDistribution( new double( 1.0 ) ),
    mean( m ),
    sd( s ),
    offset( o )
{
    // add the parameters to our set (in the base class)
    // in that way other class can easily access the set of our parameters
    // this will also ensure that the parameters are not getting deleted before we do
    addParameter( mean );
    addParameter( sd );
    addParameter( offset );
    
    *value = offset->getValue() + RbStatistics::Lognormal::rv(mean->getValue(), sd->getValue(), *GLOBAL_RNG);
}


LognormalWithOffsetDistribution::~LognormalWithOffsetDistribution( void )
{
    // We don't delete the parameters, because they might be used somewhere else too. The model needs to do that!
}


double LognormalWithOffsetDistribution::cdf( void ) const
{
    return RbStatistics::Lognormal::cdf(mean->getValue(), sd->getValue(), *value - offset->getValue());
}


LognormalWithOffsetDistribution* LognormalWithOffsetDistribution::clone( void ) const
{
    return new LognormalWithOffsetDistribution( *this );
}


double LognormalWithOffsetDistribution::computeLnProbability( void )
{
    
    double v = *value - offset->getValue();
    if ( v < 0.0 )
    {
        return RbConstants::Double::neginf;
    }
    
    return RbStatistics::Lognormal::lnPdf(mean->getValue(), sd->getValue(), v);
}


double LognormalWithOffsetDistribution::getMax( void ) const
{
    return RbConstants::Double::inf;
}


double LognormalWithOffsetDistribution::getMin( void ) const
{
    return offset->getValue();
}


double LognormalWithOffsetDistribution::quantile(double p) const
{
    return RbStatistics::Lognormal::quantile(mean->getValue(), sd->getValue(), p) + offset->getValue();
}


void LognormalWithOffsetDistribution::redrawValue( void )
{
    *value = RbStatistics::Lognormal::rv(mean->getValue(), sd->getValue(), *GLOBAL_RNG) + offset->getValue();
}


/** Swap a parameter of the distribution */
void LognormalWithOffsetDistribution::swapParameterInternal(const DagNode *oldP, const DagNode *newP)
{
    
    if (oldP == mean)
    {
        mean = static_cast<const TypedDagNode<double>* >( newP );
    }
    if (oldP == sd)
    {
        sd = static_cast<const TypedDagNode<double>* >( newP );
    }
    if (oldP == offset)
    {
        offset = static_cast<const TypedDagNode<double>* >( newP );
    }
    
}
