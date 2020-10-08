//
//  Func_DECStationaryFrequencies.h
//  revbayes-proj
//
//  Created by Michael Landis on 10/5/16.
//  Copyright © 2016 Michael Landis. All rights reserved.
//

#ifndef Func_DECStationaryFrequencies_h
#define Func_DECStationaryFrequencies_h


#include <string>
#include <iosfwd>
#include <vector>

#include "RlRateMatrix.h"
#include "RlTypedFunction.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "RateGenerator.h"
#include "RevPtr.h"
#include "RlDeterministicNode.h"
#include "TypedDagNode.h"
#include "TypedFunction.h"

namespace RevLanguage {
class ArgumentRules;
class TypeSpec;
    
    class Func_DECStationaryFrequencies : public TypedFunction<RateMatrix> {
        
    public:
        Func_DECStationaryFrequencies( void );
        
        // Basic utility functions
        Func_DECStationaryFrequencies*                                             clone(void) const;                                          //!< Clone the object
        static const std::string&                                       getClassType(void);                                         //!< Get Rev type
        static const TypeSpec&                                          getClassTypeSpec(void);                                     //!< Get class type spec
        std::string                                                     getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
        const TypeSpec&                                                 getTypeSpec(void) const;                                    //!< Get the type spec of the instance
        
        // Function functions you have to override
        RevBayesCore::TypedFunction< RevBayesCore::RateGenerator>*      createFunction(void) const;                                 //!< Create internal function object
        const ArgumentRules&                                            getArgumentRules(void) const;                               //!< Get argument rules
        
    };
    
}


#endif /* Func_DECStationaryFrequencies_h */
