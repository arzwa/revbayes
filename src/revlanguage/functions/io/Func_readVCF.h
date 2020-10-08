#ifndef Func_readVCF_H
#define Func_readVCF_H

#include <string>
#include <iosfwd>

#include "Procedure.h"
#include "RevPtr.h"


namespace RevLanguage {
class ArgumentRules;
class RevVariable;
class TypeSpec;
    
    /**
     * This is the interface for a class that reads in a distance matrix, in Phylip format.
     */
    
    class Func_readVCF : public Procedure {
        
    public:
        // Basic utility functions
        Func_readVCF*                       clone(void) const;                                                      //!< Clone the object
        static const std::string&           getClassType(void);                                                     //!< Get Rev type
        static const TypeSpec&              getClassTypeSpec(void);                                                 //!< Get class type spec
        std::string                         getFunctionName(void) const;                                            //!< Get the primary name of the function in Rev
        const TypeSpec&                     getTypeSpec(void) const;                                                //!< Get language type of the object
        
        // Regular functions
        RevPtr<RevVariable>                 execute(void);                                                          //!< Execute function
        const ArgumentRules&                getArgumentRules(void) const;                                           //!< Get argument rules
        const TypeSpec&                     getReturnType(void) const;                                              //!< Get type of return value
        
    };
    
}

#endif
