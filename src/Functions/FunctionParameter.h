///
/// C++ Interface: FunctionParameter
///
/// Description:
///
///
/// \author: Lene Preuss <lene.preuss@gmail.com>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///

#ifndef FUNCTION_PARAMETER_H
#define FUNCTION_PARAMETER_H

#include "FunctionParameterValue.h"

#include <string>
#include <tr1/memory>

/// A parameter to a Function with a name, an optional description and a default
/** This class stores a FunctionParameterValue for the value of the parameter,
 *  and one for its default value. It also stores strings to provide the name of
 *  the parameter and one for the optional description.
 *
 *  It provides access to the parameter values through the type cast operators.
 *  These are delegated to the cast operators of the value member.
 *
 *  Write access is not so convenient, because it requires an object of type
 *  FunctionParameterValue<T>, which must be created with a call to
 *  ParameterFac::createParameterWithValue(). Pass that pointer to setValue().
 *
 *  There are also getters and setters for name and description, of course.
 *
 *  This class uses the Pimpl idiom to ensure encapsulation. It may do a bad
 *  job at it, this is my first go at a pimpl class. The data members are
 *  hidden in a private struct FunctionParameter::Impl.
 *
 *  \see FunctionParameterValueBase
 *  \ingroup FunctionParameterGroup                                           */
class FunctionParameter {

    public:
      
        typedef std::tr1::shared_ptr< FunctionParameterValueBase > value_ptr_type;
        typedef std::tr1::shared_ptr< FunctionParameter > parameter_ptr_type;
  
        /// Construct a FunctionParameter from a name
        FunctionParameter(const std::string &name, const std::string &description = "");
        
        ~FunctionParameter();

        double toDouble() const;
        unsigned toUnsigned() const;
        int toInt() const;
        std::string toString() const;

        VecMath::Rotation<5> toRotation5() const;
        VecMath::Rotation<6> toRotation6() const;
        VecMath::Rotation<7> toRotation7() const;
        VecMath::Rotation<8> toRotation8() const;
        VecMath::Rotation<9> toRotation9() const;
        VecMath::Rotation<10> toRotation10() const;

        /// get the name of the function parameter
        const std::string &getName() const;
        
        /// set the name of the function parameter
        void setName(const std::string &name);
        
        /// get the long description of the function parameter
        const std::string &getDescription() const;
        
        /// set the long description of the function parameter
        void setDescription(const std::string &description);

        /// set the value of the parameter.
        void setValue(FunctionParameter::value_ptr_type value);
        
        /// Set a value from a string, as contained in a QLineEdit
        void setValue(const std::string &newValue);

        /// set the default value of the parameter.
        void setDefaultValue(FunctionParameter::value_ptr_type defaultValue);

        /// \return Pointer to FunctionParameterValue containing the parameter's value
        FunctionParameter::value_ptr_type value() const;
        
        /// \return Default parameter value is no value was given
        FunctionParameter::value_ptr_type defaultValue() const;

    private:

        /// Name of the function parameter
        std::string _name;
        
        /// Description which is shown in the parameter input dialog
        std::string _description;
        
        /// Pointer to FunctionParameterValue containing the parameter's value
        FunctionParameter::value_ptr_type _value;
        
        /// Default parameter value is no value was given
        FunctionParameter::value_ptr_type _defaultValue;
};

#endif
