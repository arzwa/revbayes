/**
 * @file
 * This file contains the declaration of RevLanguage wrapper of SlidingMove.
 *
 * @brief Declaration of Move_Slide
 *
 * (c) Copyright 2009-
 * @date Last modified: $Date: 2012-08-06 20:14:22 +0200 (Mon, 06 Aug 2012) $
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 * @since 2009-11-20, version 1.0
 * @extends RbObject
 *
 * $Id: Real.h 1746 2012-08-06 18:14:22Z hoehna $
 */

#ifndef Move_Slide_H
#define Move_Slide_H

#include <ostream>
#include <string>

#include "RlMove.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RevVariable.h"

namespace RevLanguage {
class TypeSpec;
    
    class Move_Slide : public Move {
        
    public:
        
        Move_Slide(void);                                                                                                                   //!< Default constructor (0.0)
        
        // Basic utility functions
        virtual Move_Slide*                         clone(void) const;                                                                      //!< Clone object
        void                                        constructInternalObject(void);                                                          //!< We construct the a new internal SlidingMove.
        static const std::string&                   getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&                      getClassTypeSpec(void);                                                                 //!< Get class type spec
        std::string                                 getMoveName(void) const;                                                                //!< Get the name used for the constructor function in Rev.
        const MemberRules&                          getParameterRules(void) const;                                                          //!< Get member rules (const)
        virtual const TypeSpec&                     getTypeSpec(void) const;                                                                //!< Get language type of the object
        virtual void                                printValue(std::ostream& o) const;                                                      //!< Print value (for user)
        
    protected:
        
        void                                        setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);       //!< Set member variable
        
        RevPtr<const RevVariable>                   x;
        RevPtr<const RevVariable>                   delta;
        RevPtr<const RevVariable>                   tune;   
        
    };
    
}

#endif
