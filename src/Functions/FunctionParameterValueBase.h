/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef FUNCTIONPARAMETERVALUEBASE_H
#define FUNCTIONPARAMETERVALUEBASE_H

#include "Rotation.h"

#include <stdexcept>

/// \defgroup FunctionParameterGroup A generalized interface for function parameters of arbitrary type
/// \ingroup FunctionGroup

/// Interface for a value of a function parameter. Inherited by a template class.
/** A lot of fumbling has taken place to make this hierarchy work despite the limitations of the
 *  C++ language, and I'm still not sure everything is clean and works as it should.
 *
 *  The objections of the classes based on FunctionParameterValueBase and declared in this file
 *  are as follows:
 *   - present a unified interface to get and set function parameters of any type
 *   - these parameters must know their own type
 *   - the parameters know their name, default value and optionally a longer description string
 *
 *  A parameter value is read by casting the parameter to the appropriate type or calling the
 *  \c "toType()" method (i.e., toDouble(), toUnsigned(), toInt(), toString() and the toRotationN()
 *  family).
 *
 *  A parameter value is set by calling setValue().
 *
 *  Because C++ does not allow declaring STL containers of abstract types, FunctionParameter must be
 *  a concrete type, and may not be a template.
 *  Therefore, I made FunctionParameter contain a FunctionParameterValue, which is a template and
 *  implements the abstract FunctionParameterValueBase.
 *
 *  FunctionParameterValueBase defines the (virtual, of course) interface a FunctionParameterValue
 *  implements. Because virtual functions can not be defined as templates, I have to define
 *  setValue() for every type that can be used as a function parameter, and I also have to declare
 *  all casting operators which will serve as accessor to the value.
 *
 *  setValue() can be defined with an empty function body. It is defined in the derived class as a
 *  function template. The cast operators are declared abstract in the base class, with a no-operation
 *  implementation in the derived class template and a specialization for every type that the template
 *  will be instantiated for. The cast operators must also be declared in the FunctionParameter class,
 *  which delegates them to the FunctionParameterValue object it holds. In that way, you can cast a
 *  FunctionParameter object to a desired type, and thus get access to its value.
 *
 *  Should I ever want to add another type of possible function parameter, I must declare a setValue()
 *  function for it in FunctionParameterValueBase, and a cast operator in FunctionParameterValueBase,
 *  FunctionParameterValue and FunctionParameter. Then I must define a specialization for it in
 *  FunctionParameter.C. Man, what a pain in the ass!
 *
 *  Finally, I had to declare a Factory to create FunctionParameter objects depending on the type of
 *  its value in the class ParameterFac. There are two ways to create a parameter:
 *   - either when you want to declare it for a Function (in the constructor of the concrete Function
 *      object). Then you want to give it a default value. createParameterWithDefault() is the function
 *      for that.
 *   - or you want to pass a FunctionParameter to a function to actually set the parameter.
 *      createParameterWithValue() does this.
 *
 *  If this elaborate construction of a type system for function parameters strikes you as needlessly
 *  complicated, thank the architects of the C++ language for it. (Just kidding. It makes perfect
 *  sense to forbid templated functions as virtual members, and I'm sure there is a good reason to
 *  forbid abstract classes as container contents. (I just don't see it now, but I did not think hard
 *  on it.) C++ is a very clever language.)
 *
 *  \ingroup FunctionParameterGroup                                           */
class FunctionParameterValueBase {
  public:
    /// Exception thrown when a FunctionParameterValue member not matching its template argument is called
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

    /** I have to declare the getters and setters for every type of derived classes that will be
     *  instantiated. PITA.
     *
     *  what's worse, i have to define no-ops as default implementation, because otherwise the
     *  templated derived class would remain abstract. that totally breaks type-safety during
     *  compilation.
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

    /// set a parameter using a C-style string, distinguishing from a std::string
    virtual void setValue(const char *) = 0;

    virtual double toDouble() const = 0;			///< get a double parameter
    virtual unsigned toUnsigned() const = 0;			///< get an unsigned parameter
    virtual int toInt() const = 0;				///< get an integer parameter
    virtual std::string toString() const = 0;                 ///< string representation

    virtual VecMath::RotationBase toRotationBase() const = 0; ///< get a RotationBase parameter
    virtual VecMath::Rotation<5> toRotation5() const = 0;     ///< get a Rotation<5> parm
    virtual VecMath::Rotation<6> toRotation6() const = 0;     ///< get a Rotation<6> parm
    virtual VecMath::Rotation<7> toRotation7() const = 0;     ///< get a Rotation<7> parm
    virtual VecMath::Rotation<8> toRotation8() const = 0;     ///< get a Rotation<8> parm
    virtual VecMath::Rotation<9> toRotation9() const = 0;     ///< get a Rotation<9> parm
    virtual VecMath::Rotation<10> toRotation10() const = 0;   ///< get a Rotation<10> parm

};

#endif // FUNCTIONPARAMETERVALUEBASE_H
