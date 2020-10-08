#ifndef Dist_uniformTimeTree_H
#define Dist_uniformTimeTree_H

#include <math.h>
#include <iosfwd>
#include <string>
#include <vector>

#include "UniformTimeTreeDistribution.h"
#include "RlTimeTree.h"
#include "RlTypedDistribution.h"
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
     * @file
     * This file contains the declaration of the Rev uniform time tree distribution
     *
     * @brief Declaration of the Rev uniform time tree distribution
     *
     * @author Fredrik Ronquist
     */
 class Dist_uniformTimeTree :  public TypedDistribution<TimeTree> {
        
    public:
                Dist_uniformTimeTree( void );        //!< Constructor
        virtual ~Dist_uniformTimeTree();             //!< Virtual destructor
        
        // Basic utility functions
        Dist_uniformTimeTree*                           clone(void) const;                                                                      //!< Clone the object
        static const std::string&                       getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&                          getClassTypeSpec(void);                                                                 //!< Get class type spec
        std::string                                     getDistributionFunctionName(void) const;                                                //!< Get the Rev-name for this distribution.
        const TypeSpec&                                 getTypeSpec(void) const;                                                                //!< Get the type spec of the instance
        const MemberRules&                              getParameterRules(void) const;                                                          //!< Get member rules (const)
        
        
        // Distribution functions you have to override
        RevBayesCore::UniformTimeTreeDistribution*      createDistribution(void) const;                                                         //!< Create the core object corresponding to this wrapper
        
    protected:
        
        void                                            setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);       //!< Set member variable
        
        
    private:
        
        RevPtr<const RevVariable>                       root_age;
        RevPtr<const RevVariable>                       taxa;
    };

}

#endif
