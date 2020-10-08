#ifndef RlModel_H
#define RlModel_H

#include <ostream>
#include <string>
#include <set>
#include <vector>

#include "Model.h"
#include "WorkspaceToCoreWrapperObject.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RevVariable.h"

namespace RevLanguage {
class Argument;
class TypeSpec;
    
    /**
     * RevLanguage wrapper class for the Model object.
     *
     *
     * The wraper class provides the Rev interface to the core class Model.
     * See Model.h for more details.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     *
     */
    class Model : public WorkspaceToCoreWrapperObject<RevBayesCore::Model> {
        
    public:
        
        Model(void);                                                                                                                        //!< Default constructor
        
        // Basic utility functions
        virtual Model*                              clone(void) const;                                                                      //!< Clone object
        void                                        constructInternalObject(void);                                                          //!< We construct the a new internal model object.
        static const std::string&                   getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&                      getClassTypeSpec(void);                                                                 //!< Get class type spec
        std::string                                 getConstructorFunctionName(void) const;                                                 //!< Get the name used for the constructor function in Rev.
        const MemberRules&                          getParameterRules(void) const;                                                          //!< Get member rules (const)
        virtual const TypeSpec&                     getTypeSpec(void) const;                                                                //!< Get language type of the object

        // Member method inits
        virtual RevPtr<RevVariable>                 executeMethod(const std::string& name, const std::vector<Argument>& args, bool &f);     //!< Override to map member methods to internal functions
        
        
    protected:
        
        virtual void                                printValue(std::ostream& o, bool user) const;                                                      //!< Print value (for user)
        void                                        setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);     //!< Set member variable
        void                                        printModelDotGraph(const std::string &fn, bool vb, const std::string &bgc);
        
        std::set<RevPtr<const RevVariable> >        sources;
        
    };
    
}

#endif
