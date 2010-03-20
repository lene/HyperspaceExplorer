/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#ifndef FUNCTIONPARAMETERVALUE_H
#define FUNCTIONPARAMETERVALUE_H

#include "FunctionParameterValueBase.h"

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
        virtual double toDouble() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "toDouble()", "");
            return 0.;
        }
	
        /** Default implementation for cast to unsigned. Concrete implementation
         *  will be defined in FunctionParameterValue<unsigned>.              */
        virtual unsigned toUnsigned() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator unsigned ",
                                              "did you explicitly cast the operand to unsigned? you should!");
            return 0;
        }

        /** Default implementation for cast to int. Concrete implementation
         *  will be defined in FunctionParameterValue<int>.                   */
        virtual int toInt() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator int", "");
            return 0;
        }

        /// Converts the parameter to string for printing
        virtual std::string toString() {
            std::ostringstream o;
            o << value;
            return o.str();
        }
        
        /** Default implementation for cast to RotationBase. Concrete
         *  implementation will be defined in FunctionParameterValue< Rotation<D> >.
         */
        virtual VecMath::RotationBase toRotationBase() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator VecMath::RotationBase", "");
            return VecMath::Rotation<5>();
        }

        /** Default implementation for cast to Rotation<5>. Concrete
         *  implementation will be defined in FunctionParameterValue< Rotation<5> >.
         */
        virtual VecMath::Rotation<5> toRotation5() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator VecMath::Rotation<5>", "");
            return VecMath::Rotation<5>();
        }

        /** Default implementation for cast to Rotation<6>. Concrete
         *  implementation will be defined in FunctionParameterValue< Rotation<6> >.
         */
        virtual VecMath::Rotation<6> toRotation6() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator VecMath::Rotation<6>", "");
            return VecMath::Rotation<6>();
        }

        /** Default implementation for cast to Rotation<7>. Concrete
         *  implementation will be defined in FunctionParameterValue< Rotation<7> >.
         */
        virtual VecMath::Rotation<7> toRotation7() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator VecMath::Rotation<7>", "");
            return VecMath::Rotation<7>();
        }
        /** Default implementation for cast to Rotation<8>. Concrete
         *  implementation will be defined in FunctionParameterValue< Rotation<8> >.
         */
        virtual VecMath::Rotation<8> toRotation8() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator VecMath::Rotation<8>", "");
            return VecMath::Rotation<8>();
        }
        /** Default implementation for cast to Rotation<9>. Concrete
         *  implementation will be defined in FunctionParameterValue< Rotation<9> >.
         */
        virtual VecMath::Rotation<9> toRotation9() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator VecMath::Rotation<9>", "");
            return VecMath::Rotation<9>();
        }
        /** Default implementation for cast to Rotation<10>. Concrete
         *  implementation will be defined in FunctionParameterValue< Rotation<10> >.
         */
        virtual VecMath::Rotation<10> toRotation10() {
            throw WrongParameterTypeException("FunctionParameterValue",
                                              "operator VecMath::Rotation<10>", "");
            return VecMath::Rotation<10>();
        }

    private:

      T value;                ///< The actual value of the parameter
};

#endif // FUNCTIONPARAMETERVALUE_H
