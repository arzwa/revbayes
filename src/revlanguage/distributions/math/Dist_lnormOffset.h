#ifndef Dist_offsetLognormal_H
#define Dist_offsetLognormal_H

#include <iosfwd>
#include <vector>

#include "LognormalWithOffsetDistribution.h"
#include "RlContinuousDistribution.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RevVariable.h"

namespace RevLanguage {
class TypeSpec;
    
    
    /**
     * The RevLanguage wrapper of the lognormal with offset distribution.
     *
     * The RevLanguage wrapper of the lognormal with offset distribution simply
     * manages the interactions through the Rev with our core.
     * That is, the internal distribution object can be constructed and hooked up
     * in a model graph.
     * See the LognormalWithOffsetDistribution for more details.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     * @since 2012-08-08, version 1.0
     *
     */
    class Dist_lnormOffset : public ContinuousDistribution {
        
    public:
        Dist_lnormOffset( void );
        
        // Basic utility functions
        Dist_lnormOffset*                                   clone(void) const;                                                                      //!< Clone the object
        static const std::string&                           getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&                              getClassTypeSpec(void);                                                                 //!< Get class type spec
        std::vector<std::string>                            getDistributionFunctionAliases(void) const;                                             //!< Get the alternative names used for the constructor function in Rev.
        std::string                                         getDistributionFunctionName(void) const;                                                //!< Get the Rev-name for this distribution.
        const TypeSpec&                                     getTypeSpec(void) const;                                                                //!< Get the type spec of the instance
        const MemberRules&                                  getParameterRules(void) const;                                                          //!< Get member rules (const)
        void                                                printValue(std::ostream& o) const;                                                      //!< Print the general information on the function ('usage')
        
        
        // Distribution functions you have to override
        RevBayesCore::LognormalWithOffsetDistribution*      createDistribution(void) const;
        
    protected:
        
        void                                                setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);       //!< Set member variable
        
        
    private:
        
        RevPtr<const RevVariable>                           mean;
        RevPtr<const RevVariable>                           sd;
        RevPtr<const RevVariable>                           offset;
        
    };
    
}

#endif
