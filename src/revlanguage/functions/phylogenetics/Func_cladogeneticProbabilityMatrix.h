//
//  Func_cladogeneticProbabilityMatrix.h
//
//  Created by Will Freyman on 8/1/17.
//

#ifndef Func_cladogeneticProbabilityMatrix_H
#define Func_cladogeneticProbabilityMatrix_H


#include <string>
#include <iosfwd>
#include <vector>

#include "RlCladogeneticProbabilityMatrix.h"
#include "RlTypedFunction.h"
#include "CladogeneticProbabilityMatrix.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "RevPtr.h"
#include "RlDeterministicNode.h"
#include "TypedDagNode.h"
#include "TypedFunction.h"

namespace RevLanguage {
class ArgumentRules;
class TypeSpec;
    
    class Func_cladogeneticProbabilityMatrix : public TypedFunction<CladogeneticProbabilityMatrix> {
        
    public:
        
        Func_cladogeneticProbabilityMatrix( void );
        
        Func_cladogeneticProbabilityMatrix*                                             clone(void) const;               //!< Clone the object
        static const std::string&                                                       getClassType(void);              //!< Get Rev type
        static const TypeSpec&                                                          getClassTypeSpec(void);          //!< Get class type spec
        std::string                                                                     getFunctionName(void) const;     //!< Get the primary name of the function in Rev
        const TypeSpec&                                                                 getTypeSpec(void) const;         //!< Get the type spec of the instance
        
        RevBayesCore::TypedFunction< RevBayesCore::CladogeneticProbabilityMatrix>*      createFunction(void) const;      //!< Create internal function object
        const ArgumentRules&                                                            getArgumentRules(void) const;    //!< Get argument rules
        
    };
    
}


#endif
