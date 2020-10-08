#include <stddef.h>
#include <fstream>
#include <vector>

#include "Argument.h"
#include "Ellipsis.h"
#include "Func_clear.h"
#include "RlUtils.h"
#include "TypeSpec.h"
#include "Workspace.h"
#include "ArgumentRules.h"
#include "Procedure.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RevVariable.h"
#include "RlFunction.h"

using namespace RevLanguage;

/** Default constructor */
Func_clear::Func_clear( void ) : Procedure()
{
    
}


/**
 * The clone function is a convenience function to create proper copies of inherited objected.
 * E.g. a.clone() will create a clone of the correct type even if 'a' is of derived type 'b'.
 *
 * \return A new copy of the process.
 */
Func_clear* Func_clear::clone( void ) const
{
    
    return new Func_clear( *this );
}


/** Execute function */
RevPtr<RevVariable> Func_clear::execute( void )
{
    
    // we clear the entire workspace if there were no arguments
    if ( args.size() == 0 )
    {
        Workspace::userWorkspace().clear();
    }
    else
    {
        for (size_t i = 0; i < args.size(); ++i) 
        {
            Workspace::userWorkspace().eraseVariable( args[i].getVariable() );
        }
    }
    
    return NULL;
}


/** Get argument rules */
const ArgumentRules& Func_clear::getArgumentRules( void ) const
{
    
    static ArgumentRules argumentRules = ArgumentRules();
    static bool rules_set = false;
    
    if ( !rules_set ) {
        
        argumentRules.push_back( new Ellipsis( "Variables to remove.", RevObject::getClassTypeSpec() ) );
        rules_set = true;
    }
    
    return argumentRules;
}


/** Get Rev type of object */
const std::string& Func_clear::getClassType(void)
{
    
    static std::string rev_type = "Func_clear";
    
	return rev_type; 
}


/** Get class type spec describing type of object */
const TypeSpec& Func_clear::getClassTypeSpec(void)
{
    
    static TypeSpec rev_type_spec = TypeSpec( getClassType(), new TypeSpec( Function::getClassTypeSpec() ) );
    
	return rev_type_spec; 
}


/**
 * Get the primary Rev name for this function.
 */
std::string Func_clear::getFunctionName( void ) const
{
    // create a name variable that is the same for all instance of this class
    std::string f_name = "clear";
    
    return f_name;
}



/** Get type spec */
const TypeSpec& Func_clear::getTypeSpec( void ) const
{
    
    static TypeSpec type_spec = getClassTypeSpec();
    
    return type_spec;
}


/** Get return type */
const TypeSpec& Func_clear::getReturnType( void ) const
{
    
    static TypeSpec return_typeSpec = RlUtils::Void;
    
    return return_typeSpec;
}

