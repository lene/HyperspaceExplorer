///
/// C++ Interface: FunctionParameter
///
/// Description:
///
///
/// \author: Helge Preuss <lene.preuss@gmail.com>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///

#ifndef FUNCTION_PARAMETER_H
#define FUNCTION_PARAMETER_H

#include "FunctionParameterValue.h"

#include <string>
#include <iostream>
#include <sstream>
#include <tr1/memory>

#include "SingletonHolder.h"



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
        /// Construct a FunctionParameter from a name
        FunctionParameter(const std::string &_name,
                          const std::string &_description = "");
        ~FunctionParameter();

        double toDouble() { return operator double(); }
        unsigned toUnsigned() { return operator unsigned(); }
        int toInt() { return operator int(); }
        std::string toString() { return operator std::string(); }

        operator VecMath::Rotation<5>() { return m_value->operator VecMath::Rotation<5>(); } 
        operator VecMath::Rotation<6>() { return m_value->operator VecMath::Rotation<6>(); } 
        operator VecMath::Rotation<7>() { return m_value->operator VecMath::Rotation<7>(); } 
        operator VecMath::Rotation<8>() { return m_value->operator VecMath::Rotation<8>(); } 
        operator VecMath::Rotation<9>() { return m_value->operator VecMath::Rotation<9>(); } 
        operator VecMath::Rotation<10>() { return m_value->operator VecMath::Rotation<10>(); } 

        /// get the name of the function parameter
        const std::string &getName() const;
        /// set the name of the function parameter
        void setName(const std::string &_name);
        /// get the long description of the function parameter
        const std::string &getDescription() const;
        /// set the long description of the function parameter
        void setDescription(const std::string &_description);

        /// set the value of the parameter.
        /** Requires a pointer created by
         *  ParameterFac::createParameterWithValue().
         *  \todo Can't I call createParameterWithValue() from inside
         *        setValue()?                                                 */
        template<typename T> void setValue(FunctionParameterValue<T> *_value) {
            m_value.reset( _value );
        }

        /// Set a value from a string, as contained in a QLineEdit
        void setValue(std::string _value);

        /// set the default value of the parameter.
        /** Requires a pointer created by
         *  ParameterFac::createParameterWithDefault().
         *  \todo Can't I call createParameterWithDefault() from inside
         *        setDefaultValue()?                                          */
        template<typename T> void setDefaultValue(FunctionParameterValue<T> *_defaultValue ) {
            m_defaultValue.reset(_defaultValue);
        }

        /// \return Pointer to FunctionParameterValue containing the parameter's value
        FunctionParameterValueBase *value() const;
        /// \return Default parameter value is no value was given
        FunctionParameterValueBase *defaultValue() const;

    private:
        /// get the value if it is of type double
        operator double();
        /// get the value if it is of type unsigned
        operator unsigned();
        /// get the value if it is of type int
        operator int();
        /// get the value if it is of type std::string
        operator std::string();

	/// Name of the function parameter
        std::string name;
        /// Description which is shown in the parameter input dialog
        std::string description;
        /// Pointer to FunctionParameterValue containing the parameter's value
        std::tr1::shared_ptr<FunctionParameterValueBase> m_value;
        /// Default parameter value is no value was given
        std::tr1::shared_ptr<FunctionParameterValueBase> m_defaultValue;
};

/// Class with factory methods to create a FunctionParameter
/** \see FunctionParameterValueBase
 *  \ingroup FunctionParameterGroup                                           */
class FunctionParameterFactory {
    public:
        /// Create a FunctionParameter from a value of type T
        template <typename T>
                FunctionParameter *createParameterWithValue(
                    const std::string &_name, const T &_value) {
            FunctionParameter *tmp = new FunctionParameter(_name);
            tmp->setValue(new FunctionParameterValue<T>(_value));

            return tmp;
        }

        /// Create a FunctionParameter from a default value of type T
        template <typename T>
                FunctionParameter *createParameterWithDefault(
                    const std::string &_name, const T &_default,
                    const std::string &_description = "") {
            FunctionParameter *tmp = new FunctionParameter(_name, _description);
            tmp->setDefaultValue(new FunctionParameterValue<T>(_default));
            tmp->setValue(new FunctionParameterValue<T>(_default));

            return tmp;
        }
};

/// Declare ParameterFac as a singleton and generate access to it
/** \see FunctionParameterValueBase
 *  \ingroup FunctionParameterGroup                                           */

typedef Loki::SingletonHolder<FunctionParameterFactory> TheFunctionParameterFactory;

#endif
