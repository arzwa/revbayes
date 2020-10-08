#ifndef Move_ShrinkExpandScale_H
#define Move_ShrinkExpandScale_H

#include <ostream>
#include <string>

#include "RlMove.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RevVariable.h"

namespace RevLanguage {
class TypeSpec;
    
    /**
     * @brief Rev Wrapper of a scaling move on all elements of a real valued vector.
     *
     * This class is the RevLanguage wrapper of ShrinkExpandScale.
     *
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     * @copyright GPL version 3
     * @since 2016-08-31, version 1.0
     */
    class Move_ShrinkExpandScale : public Move {
        
    public:
        
        Move_ShrinkExpandScale(void);                                                                                                                    //!< Default constructor
        
        // Basic utility functions
        virtual Move_ShrinkExpandScale*             clone(void) const;                                                                              //!< Clone the object
        void                                        constructInternalObject(void);                                                                  //!< We construct the a new internal move.
        static const std::string&                   getClassType(void);                                                                             //!< Get Rev type
        static const TypeSpec&                      getClassTypeSpec(void);                                                                         //!< Get class type spec
        std::string                                 getMoveName(void) const;                                                                        //!< Get the name used for the constructor function in Rev.
        const MemberRules&                          getParameterRules(void) const;                                                                  //!< Get member rules (const)
        virtual const TypeSpec&                     getTypeSpec(void) const;                                                                        //!< Get language type of the object
        virtual void                                printValue(std::ostream& o) const;                                                              //!< Print value (for user)
        
    protected:
        
        void                                        setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);               //!< Set member variable
        
        RevPtr<const RevVariable>                   x;                                                                                              //!< The variable holding the real valued vector.
        RevPtr<const RevVariable>                   sd;                                                                                              //!< The variable holding the real valued vector.
        RevPtr<const RevVariable>                   lambda;                                                                                         //!< The variable for the tuning parameter.
        RevPtr<const RevVariable>                   tune;                                                                                           //!< The variable telling if to tune or not.
        
    };
    
}

#endif
