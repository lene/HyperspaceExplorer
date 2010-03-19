/*
    <one line to give the program's name and a brief idea of what it does.>
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

#ifndef VECTORFUNCTION_H
#define VECTORFUNCTION_H

#include "ParameterMap.h"
#include "Vector.h"

#undef USE_SHARED_PTR

#ifdef USE_SHARED_PTR
#include <tr1/memory>
#endif

template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
  class ParametricFunction {

    public:

      typedef VecMath::Vector<parameter_space_dimension> argument_type;
      typedef VecMath::Vector<definition_space_dimension> return_type;

      virtual ~ParametricFunction() { }

      virtual return_type f(const argument_type &x) = 0;

      /** \return number of parameters for the function                     */
      unsigned getNumParameters() { return _parameters.size(); }

      /// \return The collection of all parameters (and their values)
      ParameterMap getParameters() { return _parameters; }

      /// \return Pointer to the FunctionParameter which is named \p name
#ifdef USE_SHARED_PTR
      std::tr1::shared_ptr<FunctionParameter> getParameter(const std::string &name) {
        return std::tr1::shared_ptr<FunctionParameter>(_parameters.getParameter(name));
      }
#     else
      FunctionParameter* getParameter(const std::string &name) {
        return _parameters.getParameter(name);
      }
#     endif

      /// \return Pointer to the FunctionParameterValue which is named \p name
#ifdef USE_SHARED_PTR
      std::tr1::shared_ptr<FunctionParameterValueBase> getParameterValue(const std::string &name) {
        return std::tr1::shared_ptr<FunctionParameterValueBase>(_parameters.getValue(name));
      }
#     else
      FunctionParameterValueBase* getParameterValue(const std::string &name) {
        return _parameters.getValue(name);
      }
#     endif

    protected:
      /// Add a parameter to the list of parameters
      template <typename T> void declareParameter(const std::string &parameter_name,
                                                  const T &parameter_default_value);
      /// Add a parameter to the list of parameters
      template <typename T> void declareParameter(const std::string &parameter_name,
                                                  const T &parameter_default_value,
                                                  const T &parameter_value);

    private:

      ParameterMap _parameters;
};

/// Add a parameter with a name and a default value to the parameter list
template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
template<typename T>
inline
void ParametricFunction<definition_space_dimension, parameter_space_dimension>::declareParameter(
    const std::string &parameter_name,
    const T &parameter_default_value) {
  if (_parameters.find(parameter_name) != _parameters.end()) return;

  _parameters.insertByDefault(parameter_name, parameter_default_value);
  std::cerr << _parameters.toString() << std::endl;
}

/// Add a parameter with a name and a default value to the parameter list
template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
  template<typename T>
inline
void ParametricFunction<definition_space_dimension, parameter_space_dimension>::declareParameter(
    const std::string& parameter_name,
    const T& parameter_default_value,
    const T& parameter_value) {
  declareParameter(parameter_name, parameter_default_value);
  _parameters[parameter_name]->setValue(new FunctionParameterValue<T>(parameter_value));
}

#endif // VECTORFUNCTION_H
