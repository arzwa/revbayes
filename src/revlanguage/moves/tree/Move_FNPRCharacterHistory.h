#ifndef Move_FNPRCharacterHistory_H
#define Move_FNPRCharacterHistory_H

#include <ostream>
#include <string>

#include "RlMove.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RevVariable.h"

namespace RevLanguage {
class TypeSpec;
    
    
    /**
     * @brief Rev wrapper class for the FNPR move.
     *
     * This class is the Rev wrapper class for the FNPR move,
     * a move that proposes a new topology based on a subtree-prune
     * and regraft move with fixed node ages.
     *
     *
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     * @copyright GPL version 3
     */
    class Move_FNPRCharacterHistory : public Move {
        
    public:
        
        Move_FNPRCharacterHistory(void);                                                                                                                    //!< Default constructor
        
        // Basic utility functions
        virtual Move_FNPRCharacterHistory*          clone(void) const;                                                                      //!< Clone object
        void                                        constructInternalObject(void);                                                          //!< We construct the a new internal Move.
        static const std::string&                   getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&                      getClassTypeSpec(void);                                                                 //!< Get class type spec
        std::string                                 getMoveName(void) const;                                                                //!< Get the name used for the constructor function in Rev.
        const MemberRules&                          getParameterRules(void) const;                                                          //!< Get member rules (const)
        virtual const TypeSpec&                     getTypeSpec(void) const;                                                                //!< Get language type of the object
        virtual void                                printValue(std::ostream& o) const;                                                      //!< Print value (for user)
        
    protected:
        
        void                                        setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);       //!< Set member variable
        
        RevPtr<const RevVariable>                   tree;
        RevPtr<const RevVariable>                   ctmc;
        RevPtr<const RevVariable>                   rate_generator;
        
    };
    
}

#endif
