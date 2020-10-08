#ifndef Dist_GilbertGraph_H
#define Dist_GilbertGraph_H

#include <math.h>
#include <iostream>
#include <string>
#include <vector>

#include "RlMatrixRealSymmetric.h"
#include "RlTypedDistribution.h"
#include "GilbertGraphDistribution.h"
#include "DagMemberFunction.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "MatrixReal.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RevVariable.h"
#include "RlDagMemberFunction.h"
#include "RlDeterministicNode.h"
#include "RlStochasticNode.h"
#include "RlTypedFunction.h"
#include "StochasticNode.h"
#include "TypedDagNode.h"
#include "TypedDistribution.h"
#include "TypedFunction.h"

namespace RevLanguage {
class TypeSpec;
    
    /**
     * The RevLanguage wrapper of the LKJ distribution.
     *
     * The RevLanguage wrapper of the LKJ distribution simply
     * manages the interactions through the Rev with our core.
     * That is, the internal distribution object can be constructed and hooked up
     * in a model graph.
     * See the LKJDistribution for more details.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Nicolas Lartillot)
     * @since 2014-03-27, version 1.0
     *
     */
    class Dist_GilbertGraph : public TypedDistribution<MatrixRealSymmetric> {
        
    public:
        Dist_GilbertGraph( void );
        virtual ~Dist_GilbertGraph();
        
        // Basic utility functions
        Dist_GilbertGraph*                              clone(void) const;                                                                      //!< Clone the object
        static const std::string&                       getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&                          getClassTypeSpec(void);                                                                 //!< Get class type spec
        std::string                                     getDistributionFunctionName(void) const;                                                //!< Get the Rev-name for this distribution.
        const TypeSpec&                                 getTypeSpec(void) const;                                                                //!< Get the type spec of the instance
        const MemberRules&                              getParameterRules(void) const;                                                          //!< Get member rules (const)
        void                                            printValue(std::ostream& o) const;                                                      //!< Print the general information on the function ('usage')
        
        
        // Distribution functions you have to override
        RevBayesCore::GilbertGraphDistribution*         createDistribution(void) const;
        
    protected:
        
        void                                            setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);       //!< Set member variable
        
        
    private:
        RevPtr<const RevVariable>                       edge_probability;
        RevPtr<const RevVariable>                       dim;
        
    };
    
}
#endif /* defined(__revbayes__Dist_GilbertGraph__) */
