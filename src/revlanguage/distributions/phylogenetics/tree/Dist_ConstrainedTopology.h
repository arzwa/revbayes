#ifndef Dist_ConstrainedTopology_H
#define Dist_ConstrainedTopology_H

#include <math.h>
#include <iosfwd>
#include <string>
#include <vector>

#include "TopologyConstrainedTreeDistribution.h"
#include "RlTypedDistribution.h"
#include "RlTimeTree.h"
#include "DagMemberFunction.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RevVariable.h"
#include "RlDagMemberFunction.h"
#include "RlDeterministicNode.h"
#include "RlStochasticNode.h"
#include "RlTypedFunction.h"
#include "StochasticNode.h"
#include "Tree.h"
#include "TypedDagNode.h"
#include "TypedDistribution.h"
#include "TypedFunction.h"

namespace RevLanguage {
class TypeSpec;
    
    /**
     * The RevLanguage wrapper of the Dist_ConstrainedTopology
     *
     * The RevLanguage wrapper of the constrained-topology distribution connects
     * the variables/parameters of the process and creates the internal Dist_ConstrainedTopology object.
     * Please read the Dist_ConstrainedTopology.h for more info.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     * @since 2014-01-26, version 1.0
     *
     */
    class Dist_ConstrainedTopology : public TypedDistribution<TimeTree> {
        
    public:
                                                            Dist_ConstrainedTopology(void);
        
        // Basic utility functions
        Dist_ConstrainedTopology*                           clone(void) const;                                                                      //!< Clone the object
        static const std::string&                           getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&                              getClassTypeSpec(void);                                                                 //!< Get class type spec
        std::vector<std::string>                            getDistributionFunctionAliases(void) const;                                             //!< Get the alternative names used for the constructor function in Rev.
        std::string                                         getDistributionFunctionName(void) const;                                                //!< Get the Rev-name for this distribution.
        const TypeSpec&                                     getTypeSpec(void) const;                                                                //!< Get the type spec of the instance
        const MemberRules&                                  getParameterRules(void) const;                                                          //!< Get member rules (const)
        
        // Distribution functions you have to override
        RevBayesCore::TopologyConstrainedTreeDistribution*  createDistribution(void) const;
        
    protected:
        void                                                setConstParameter(const std::string& name, const RevPtr<const RevVariable>& var);       //!< Set member variable
        
    private:
        RevPtr<const RevVariable>                           base_distribution;
        RevPtr<const RevVariable>                           constraints;
        RevPtr<const RevVariable>                           backbone;
        RevPtr<const RevVariable>                           invert_constraint;                                                                      //!< Boolean indicating whether topologies are rooted
    };
}

#endif
