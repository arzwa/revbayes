#ifndef Func_simStartingTree_H
#define Func_simStartingTree_H

#include <iosfwd>

#include "Procedure.h"
#include "RevPtr.h"

namespace RevLanguage {
class ArgumentRules;
class RevVariable;
class TypeSpec;
    
    /**
     * @brief Rev function to simumlate a birth-death tree.
     *
     * This procedure simulates a simple tree.
     * The tree is either totally balanced, or a caterpillar tree.
     * The internode distance is fix to 1.0.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     * @since Version 1.0, 2019-05-09
     *
     */
    class Func_simStartingTree : public Procedure {
        
    public:
        Func_simStartingTree( void );
        
        // Basic utility functions
        Func_simStartingTree*                   clone(void) const;                                          //!< Clone object
        static const std::string&                   getClassType(void);                                         //!< Get Rev simTree
        static const TypeSpec&                      getClassTypeSpec(void);                                     //!< Get class simTree spec
        std::string                                 getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
        const TypeSpec&                             getTypeSpec(void) const;                                    //!< Get language simTree of the object
        
        // Func_source functions
        const ArgumentRules&                        getArgumentRules(void) const;                               //!< Get argument rules
        const TypeSpec&                             getReturnType(void) const;                                  //!< Get simTree of return val
        
        RevPtr<RevVariable>                         execute(void);                                              //!< Execute function
        
    private:
        
        
    };
    
}

#endif

