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
        FunctionParameter(const std::string &name,
                          const std::string &description = "");
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
        /** Requires a pointer created by ParameterFac::createParameterWithValue().
         *  \todo Can't I call createParameterWithValue() from inside
         *        setValue()?                                                 */
        template<typename T> void setValue(
          std::tr1::shared_ptr< FunctionParameterValue<T> > value) {
            _value.reset( value );
        }
        void setValue(
          std::tr1::shared_ptr< FunctionParameterValueBase > value) {
          _value = value;
        }
        /// Set a value from a string, as contained in a QLineEdit
        void setValue(const std::string &newValue);

        /// set the default value of the parameter.
        /** Requires a pointer created by ParameterFac::createParameterWithDefault().
         *  \todo Can't I call createParameterWithDefault() from inside
         *        setDefaultValue()?                                          */
        template<typename T> void setDefaultValue(
          std::tr1::shared_ptr< FunctionParameterValue<T> > defaultValue ) {
            _defaultValue.reset(defaultValue);
        }
        void setDefaultValue(
          std::tr1::shared_ptr< FunctionParameterValueBase > defaultValue) {
          _defaultValue = defaultValue;
        }

        /// \return Pointer to FunctionParameterValue containing the parameter's value
        std::tr1::shared_ptr<FunctionParameterValueBase> value() const;
        /// \return Default parameter value is no value was given
        std::tr1::shared_ptr<FunctionParameterValueBase> defaultValue() const;

    private:

        /// Name of the function parameter
        std::string _name;
        /// Description which is shown in the parameter input dialog
        std::string _description;
        /// Pointer to FunctionParameterValue containing the parameter's value
        std::tr1::shared_ptr<FunctionParameterValueBase> _value;
        /// Default parameter value is no value was given
        std::tr1::shared_ptr<FunctionParameterValueBase> _defaultValue;
};

/// Class with factory methods to create a FunctionParameter
/** \see FunctionParameterValueBase
 *  \ingroup FunctionParameterGroup                                           */
class FunctionParameterFactory {
    public:
        /// Create a FunctionParameter from a value of type T
        template <typename T>
            std::tr1::shared_ptr<FunctionParameter> createParameterWithValue(
                    const std::string &_name, const T &_value) {
            std::tr1::shared_ptr< FunctionParameter > tmp(new FunctionParameter(_name));
            tmp->setValue(
                std::tr1::shared_ptr< FunctionParameterValueBase >(
                    new FunctionParameterValue<T>(_value)));

            return tmp;
        }

        /// Create a FunctionParameter from a default value of type T
        template <typename T>
            std::tr1::shared_ptr<FunctionParameter> createParameterWithDefault(
                    const std::string &_name, const T &_default,
                    const std::string &_description = "") {
            std::tr1::shared_ptr<FunctionParameter> tmp(new FunctionParameter(_name, _description));
            tmp->setDefaultValue(
                std::tr1::shared_ptr<FunctionParameterValueBase>(
                    new FunctionParameterValue<T>(_default)));
            tmp->setValue(
                std::tr1::shared_ptr<FunctionParameterValueBase>(
                    new FunctionParameterValue<T>(_default)));

            return tmp;
        }
};

/// Declare ParameterFac as a singleton and generate access to it
/** \see FunctionParameterValueBase
 *  \ingroup FunctionParameterGroup                                           */
typedef Loki::SingletonHolder<FunctionParameterFactory> TheFunctionParameterFactory;

#endif
