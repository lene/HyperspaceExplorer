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

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "SingletonHolder.h"
#include "Rotation.h"

/// \defgroup FunctionParameterGroup A generalized interface for function parameters of arbitrary type
/// \ingroup FunctionGroup

/// Interface for a value of a function parameter. Inherited by a template class.
/** A lot of fumbling has taken place to make this hierarchy work despite the
 *  limitations of the C++ language, and I'm still not sure everything is clean
 *  and works as it should.
 *
 *  The objections of the classes based on FunctionParameterValueBase and
 *  declared in this file are as follows:
 *   - present a unified interface to get and set function parameters of any
 *      type
 *   - these parameters must know their own type
 *   - the parameters know their name, default value and optionally a longer
 *      description string
 *
 *  A parameter value is read by casting the parameter to the appropriate type.
 *  A parameter value is set by calling setValue().
 *
 *  Because C++ does not allow declaring STL containers of abstract types,
 *  FunctionParameter must be a concrete type, and may not be a template.
 *  Therefore, I made FunctionParameter contain a FunctionParameterValue, which
 *  is a template and implements the abstract FunctionParameterValueBase.
 *
 *  FunctionParameterValueBase defines the (virtual, of course) interface a
 *  FunctionParameterValue implements. Because virtual functions can not be
 *  defined as templates, I have to define setValue() for every type that can
 *  be used as a function parameter, and I also have to declare all casting
 *  operators which will serve as accessor to the value.
 *
 *  setValue() can be defined with an empty function body. It is defined in the
 *  derived class as a function template. The cast operators are declared
 *  abstract in the base class, with a no-operation implementation in the
 *  derived class template and a specialization for every type that the template
 *  will be instantiated for. The cast operators must also be declared in the
 *  FunctionParameter class, which delegates them to the FunctionParameterValue
 *  object it holds. In that way, you can cast a FunctionParameter object to a
 *  desired type, and thus get access to its value.
 *
 *  Should I ever want to add another type of possible function parameter, I
 *  must declare a setValue() function for it in FunctionParameterValueBase, and
 *  a cast operator in FunctionParameterValueBase, FunctionParameterValue and
 *  FunctionParameter. Then I must define a specialization for it in
 *  FunctionParameter.C. Man, what a pain in the ass!
 *
 *  Finally, I had to declare a Factory to create FunctionParameter objects
 *  depending on the type of its value in the class ParameterFac. There are two
 *  ways to create a parameter:
 *   - either when you want to declare it for a Function (in the constructor of
 *      the concrete Function object). Then you want to give it a default value.
 *      createParameterWithDefault() is the function for that.
 *   - or you want to pass a FunctionParameter to a function to actually set the
 *      parameter. createParameterWithValue() does this.
 *
 *  If this elaborate construction of a type system for function parameters
 *  strikes you as needlessly complicated, thank the architects of the C++
 *  language for it. (Just kidding. It makes perfect sense to forbid templated
 *  functions as virtual members, and I'm sure there is a good reason to forbid
 *  abstract classes as container contents. (I just don't see it now, but I did
 *  not think hard on it.) C++ is a very clever language.)
 *
 *  \ingroup FunctionParameterGroup                                           */
class FunctionParameterValueBase {
    public:
        /// Exception thrown when a FunctionParameterValue member not matching
        /// its template argument is called
        struct WrongParameterTypeException: public std::logic_error {
            /// Create a WrongParameterTypeException
            /** \param _class Class name
             *  \param _function Erroneously called function
             *  \param _type Argument type for \p _function
             */
            WrongParameterTypeException(const std::string &_class,
                                        const std::string &_function,
                                        const std::string &_type):
                std::logic_error("Tried to call default implementation for "+
                                 _class+"::"+_function+"("+_type+")!") { }
        };

        /** I have to declare the getters and setters for every type of
            derived classes that will be instantiated. PITA.
            what's worse, i have to define no-ops as default implementation,
            because otherwise the templated derived class would remain
            abstract. that totally breaks type-safety during compilation.
         */
        /// set a double parm
        virtual void setValue(const double &) {
            throw WrongParameterTypeException("FunctionParameterValueBase",
                                              "setValue", "double");
        }
        /// set an unsigned parm
        virtual void setValue(const unsigned &) {
            throw WrongParameterTypeException("FunctionParameterValueBase",
                                              "setValue", "unsigned");
        }
        /// set an int parm
        virtual void setValue(const int &) {
            throw WrongParameterTypeException("FunctionParameterValueBase",
                                              "setValue", "int");
        }
        /// set a string parm
        virtual void setValue(const std::string &) {
            throw WrongParameterTypeException("FunctionParameterValueBase",
                                              "setValue", "std::string");
        }
        /// set a Rotation<5> parameter
        /** setValue() functions for VecMath::Rotation's must be specified
         *  manually, because you can't have virtual function templates
         */
        virtual void setValue(const VecMath::Rotation<5> &) {
            throw WrongParameterTypeException("FunctionParameterValueBase",
                                              "setValue", "VecMath::Rotation<5>");
        }
        /// set a Rotation<6> parameter
        /** setValue() functions for VecMath::Rotation's must be specified
         *  manually, because you can't have virtual function templates
         */
        virtual void setValue(const VecMath::Rotation<6> &) {
            throw WrongParameterTypeException("FunctionParameterValueBase",
                                              "setValue", "VecMath::Rotation<6>");
        }
        /// set a Rotation<7> parameter
        /** setValue() functions for VecMath::Rotation's must be specified
         *  manually, because you can't have virtual function templates
         */
        virtual void setValue(const VecMath::Rotation<7> &) {
            throw WrongParameterTypeException("FunctionParameterValueBase",
                                              "setValue", "VecMath::Rotation<7>");
        }
        /// set a Rotation<8> parameter
        /** setValue() functions for VecMath::Rotation's must be specified
         *  manually, because you can't have virtual function templates
         */
        virtual void setValue(const VecMath::Rotation<8> &) {
            throw WrongParameterTypeException("FunctionParameterValueBase",
                                              "setValue", "VecMath::Rotation<8>");
        }
        /// set a Rotation<9> parameter
        /** setValue() functions for VecMath::Rotation's must be specified
         *  manually, because you can't have virtual function templates
         */
        virtual void setValue(const VecMath::Rotation<9> &) {
            throw WrongParameterTypeException("FunctionParameterValueBase",
                                              "setValue", "VecMath::Rotation<9>");
        }
        /// set a Rotation<10> parameter
        /** setValue() functions for VecMath::Rotation's must be specified
         *  manually, because you can't have virtual function templates
         */
        virtual void setValue(const VecMath::Rotation<10> &) {
            throw WrongParameterTypeException("FunctionParameterValueBase",
                                              "setValue", "VecMath::Rotation<10>");
        }

        /// set a C-string parameter - abstract method
        virtual void setValue(const char *) = 0;

        virtual operator double() = 0;                  ///< get a double parm
        virtual operator unsigned() = 0;                ///< get an unsigned parm
        virtual operator int() = 0;                     ///< get an int parm
        virtual operator std::string() = 0;             ///< get a string parm
        virtual operator VecMath::RotationBase() = 0;   ///< get a RotationBase parm
        virtual operator VecMath::Rotation<5>() = 0;    ///< get a Rotation<5> parm
        virtual operator VecMath::Rotation<6>() = 0;    ///< get a Rotation<6> parm
        virtual operator VecMath::Rotation<7>() = 0;    ///< get a Rotation<7> parm
        virtual operator VecMath::Rotation<8>() = 0;    ///< get a Rotation<8> parm
        virtual operator VecMath::Rotation<9>() = 0;    ///< get a Rotation<9> parm
        virtual operator VecMath::Rotation<10>() = 0;   ///< get a Rotation<10> parm

        virtual std::string toString() = 0;             ///< string representation
    };

/// A value for a function parameter. Template depending on its type.
/** Defines the interface declared by FunctionParameterValueBase:
 *   - implements setValue(const T &), leaving the other overloaded setValue()
 *      members untouched as no-ops
 *   - implements the type cast operators declared abstract in the base class
 *      as no-ops (the base class cant't define the default implementations of
 *      the cast operators, because this class needs to define a specialization
 *      of the operator T() - so it needs to declare all of them)
 *   - stores a T and gives access to it via the cast operator
 *
 *  \see FunctionParameterValueBase
 *  \ingroup FunctionParameterGroup                                           */
template <typename T> class FunctionParameterValue:
        public FunctionParameterValueBase {
    public:
        /// Construct the FunctionParameterValue object with its actual value
        FunctionParameterValue<T>(const T &_value): value(_value) { }

        /// Set a value from a string, as contained in a QLineEdit
        virtual void setValue(const char *);

        /** Default implementation for cast to double. Concrete implementation
         *  will be defined in FunctionParameterValue<double>.                */
        virtual operator double() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator double", "");
            return 0.;
        }

        /** Default implementation for cast to unsigned. Concrete implementation
         *  will be defined in FunctionParameterValue<unsigned>.              */
        virtual operator unsigned() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator unsigned ",
                                              "did you explicitly cast the operand to unsigned? you should");
            return 0;
        }

        /** Default implementation for cast to int. Concrete implementation
         *  will be defined in FunctionParameterValue<int>.                   */
        virtual operator int() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator int", "");
            return 0;
        }

        /** Default implementation for cast to string. Concrete implementation
         *  will be defined in FunctionParameterValue<string>.                */
        virtual operator std::string() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator std::string", "");
            return toString();
        }

        /** Default implementation for cast to RotationBase. Concrete
         *  implementation will be defined in FunctionParameterValue<Rotation<D> >.
         */
        virtual operator VecMath::RotationBase() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator VecMath::RotationBase", "");
            return VecMath::Rotation<5>();
        }

        /** Default implementation for cast to Rotation<5>. Concrete
         *  implementation will be defined in FunctionParameterValue<Rotation<5>>.
         */
        virtual operator VecMath::Rotation<5>() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator VecMath::Rotation<5>", "");
            return VecMath::Rotation<5>();
        }

        /** Default implementation for cast to Rotation<6>. Concrete
         *  implementation will be defined in FunctionParameterValue<Rotation<6>>.
         */
        virtual operator VecMath::Rotation<6>() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator VecMath::Rotation<6>", "");
            return VecMath::Rotation<6>();
        }

        /** Default implementation for cast to Rotation<7>. Concrete
         *  implementation will be defined in FunctionParameterValue<Rotation<7>>.
         */
        virtual operator VecMath::Rotation<7>() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator VecMath::Rotation<7>", "");
            return VecMath::Rotation<7>();
        }
        /** Default implementation for cast to Rotation<8>. Concrete
         *  implementation will be defined in FunctionParameterValue<Rotation<8>>.
         */
        virtual operator VecMath::Rotation<8>() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator VecMath::Rotation<8>", "");
            return VecMath::Rotation<8>();
        }
        /** Default implementation for cast to Rotation<9>. Concrete
         *  implementation will be defined in FunctionParameterValue<Rotation<9>>.
         */
        virtual operator VecMath::Rotation<9>() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator VecMath::Rotation<9>", "");
            return VecMath::Rotation<9>();
        }
        /** Default implementation for cast to Rotation<10>. Concrete
         *  implementation will be defined in FunctionParameterValue<Rotation<10>>.
         */
        virtual operator VecMath::Rotation<10>() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator VecMath::Rotation<10>", "");
            return VecMath::Rotation<10>();
        }

        /// Converts the parameter to string for printing
        virtual std::string toString() {
            std::ostringstream o;
            o << value << std::ends;
            return o.str();
        }
    private:
        T value;                ///< The actual value of the parameter
};

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

        /// get the value if it is of type double
        operator double();
        /// get the value if it is of type unsigned
        operator unsigned();
        /// get the value if it is of type int
        operator int();
        /// get the value if it is of type std::string
        operator std::string();

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
            pImpl->value.reset ( _value );
        }

        /// Set a value from a string, as contained in a QLineEdit
        void setValue(std::string _value);

        /// set the default value of the parameter.
        /** Requires a pointer created by
         *  ParameterFac::createParameterWithDefault().
         *  \todo Can't I call createParameterWithDefault() from inside
         *        setDefaultValue()?                                          */
        template<typename T> void setDefaultValue(FunctionParameterValue<T> *_defaultValue ) {
            pImpl->defaultValue.reset(_defaultValue);
        }

        /// \return Pointer to FunctionParameterValue containing the parameter's value
        FunctionParameterValueBase *value() const;
        /// \return Default parameter value is no value was given
        FunctionParameterValueBase *defaultValue() const;

    private:
    /*  these accessors are never used, but i like to keep them around
        std::auto_ptr<FunctionParameterValueBase> value() {
            return pImpl->value;
        }
        const std::auto_ptr<FunctionParameterValueBase> value() const {
            return pImpl->value;
        }
        std::auto_ptr<FunctionParameterValueBase> defaultValue() {
            return pImpl->defaultValue;
        }
    */
        /// Data members for class FunctionParameter
        struct Impl {
            /// Initialize the data members with empty values
            Impl(const std::string &_name,
                 const std::string &_description = ""):
                 name(_name), description(_description), value(0),
                 defaultValue(0) {}
            ~Impl() { }
            /// Name of the function parameter
            std::string name;
            /// Description which is shown in the parameter input dialog
            std::string description;
            /// Pointer to FunctionParameterValue containing the parameter's value
            std::auto_ptr<FunctionParameterValueBase> value;
            /// Default parameter value is no value was given
            std::auto_ptr<FunctionParameterValueBase> defaultValue;
        };
        Impl *pImpl;            ///< Pointer to the data member
};

/// Class with factory methods to create a FunctionParameter
/** \see FunctionParameterValueBase
 *  \ingroup FunctionParameterGroup                                           */
class ParameterFac {
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

typedef Loki::SingletonHolder<ParameterFac> ParameterFactory;

#endif
