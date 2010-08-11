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

#ifndef FUNCTIONPARAMETERFACTORY_H
#define FUNCTIONPARAMETERFACTORY_H

#include "FunctionParameter.h"

#include "SingletonHolder.h"

/// Class with factory methods to create a FunctionParameter
/** \see FunctionParameterValueBase
 *  \ingroup FunctionParameterGroup                                           */
class FunctionParameterFactory {

public:

    /// Create a FunctionParameter from a value of type \p T
    /** \tparam T Type of the parameter to be declared.
     */
    template <typename T>
        FunctionParameter::parameter_ptr_type createParameterWithValue(
            const std::string &name, const T &value,
            const std::string &description = "") {
        FunctionParameter::parameter_ptr_type tmp(new FunctionParameter(name, description));
        tmp->setValue(
            FunctionParameter::value_ptr_type(new FunctionParameterValue<T>(value)));

        return tmp;
    }

    /// Create a FunctionParameter from a default value of type  \p T
    /** \tparam T Type of the parameter to be declared.
     */
    template <typename T>
        FunctionParameter::parameter_ptr_type createParameterWithDefault(
                const std::string &name, const T &defaultValue,
                const std::string &description = "") {
        FunctionParameter::parameter_ptr_type tmp = createParameterWithValue(name, defaultValue, description);
        tmp->setDefaultValue(
            FunctionParameter::value_ptr_type(new FunctionParameterValue<T>(defaultValue)));

        return tmp;
    }
};

/// Declare ParameterFac as a singleton and generate access to it
/** \see FunctionParameterValueBase
 *  \ingroup FunctionParameterGroup                                           */
typedef Loki::SingletonHolder<FunctionParameterFactory> TheFunctionParameterFactory;

#endif // FUNCTIONPARAMETERFACTORY_H
