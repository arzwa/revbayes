#ifndef Move_HomeologPairPhase_H
#define Move_HomeologPairPhase_H

#include "RlMove.h"
#include "TypedDagNode.h"

#include <ostream>
#include <string>

namespace RevLanguage {
    
    
    /**
     * The RevLanguage wrapper of the scaling move.
     *
     * The RevLanguage wrapper of the scaling move simply
     * manages the interactions through the Rev with our core.
     * That is, the internal move object can be constructed and hooked up
     * in a DAG-nove (variable) that it works on.
     * See the ScaleMove.h for more details.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     * @since 2014-01-28, version 1.0
     *
     */
    class Move_HomeologPairPhase : public Move {
        
    public:
        
        Move_HomeologPairPhase(void);                                                                                                            //!< Default constructor
        
        // Basic utility functions
        virtual Move_HomeologPairPhase*             clone(void) const;                                                                          //!< Clone object
        void                                        constructInternalObject(void);                                                              //!< We construct the a new internal move.
        static const std::string&                   getClassType(void);                                                                         //!< Get Rev type
        static const TypeSpec&                      getClassTypeSpec(void);                                                                     //!< Get class type spec
        std::string                                 getMoveName(void) const;                                                                    //!< Get the name used for the constructor function in Rev.
        const MemberRules&                          getParameterRules(void) const;                                                              //!< Get member rules (const)
        virtual const TypeSpec&                     getTypeSpec(void) const;                                                                    //!< Get language type of the object
        virtual void                                printValue(std::ostream& o) const;                                                          //!< Print value (for user)
        
    protected:
        
        void                                        setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);           //!< Set member variable
        
        RevPtr<const RevVariable>                   ctmc;                                                                                       //!< The variable on which the move works
        RevPtr<const RevVariable>                   tip1;                                                                                  //!< The variable on which the move works
        RevPtr<const RevVariable>                   tip2;                                                                                  //!< The variable on which the move works
        RevPtr<const RevVariable>                   tip3;                                                                                  //!< The variable on which the move works
        RevPtr<const RevVariable>                   tip4;                                                                                  //!< The variable on which the move works
        
    };
    
}


#endif
