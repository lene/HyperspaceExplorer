/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
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
    (Seriously, has anyone ever done this?)

*/

#ifndef VECTORFUNCTION_H
#define VECTORFUNCTION_H

#include "ParameterMap.h"
#include "Vector.h"

#include <memory>

/// A function describing a \p P dimensional surface in \p N dimensional space
/** See also http://en.wikipedia.org/wiki/Parametric_surface for an explanation
 *  of two-dimensional surfaces in three-dimensional space, ie. a
 *  ParametricFunction < 3, 2 >.
 *
 *  A ParametricFunction has the following attributes:
 *  - A name.
 *  - An optional longer description.
 *  - An optional set of parameters, such as the radius of a sphere.
 *  - A definition space in \f$ R^P \f$. It defaults to extending from -1 to 1
 *    in every coordinate of the parameter vector space.
 *
 *  It also has a mathematical function \f$ f: R^P \rightarrow R^N \f$ which
 *  defines the parametric \p P -surface in \p N -space. This function must be
 *  implemented in a daughter class of ParametricFunction < N, P > as the pure
 *  virtual function \see f().
 *
 *  \tparam N The dimension of the definition vector space.
 *  \tparam P The dimension of the parameter vector space.
 *  \tparam NUM The numeric type managed by the grid.
 *
 *  \ingroup FunctionGroup
 *  @author Lene Preuss <lene.preuss@gmail.com>
 */
template <unsigned N, unsigned P, typename NUM = double>
  class ParametricFunction {

    public:

      /// The argument type for the function - a \p P dimensional Vector.
      typedef VecMath::Vector<P, NUM> argument_type;
      /// The return type of the function - a \p N dimensional Vector.
      typedef VecMath::Vector<N, NUM> return_type;

      ParametricFunction():
        _function_name(), _function_description(),
        _parameters(),
        _default_x_min(-1.), _default_x_max(1.) { }

      virtual ~ParametricFunction() { }

      /// The function defining the parametric equation for the \p P -surface.
      /** Implement this in every derived class.
       *  \param x Value of the parameter to be evaluated.
       *  \return The evaluation of the parametric equation at point \p x.
       */
      virtual return_type f(const argument_type &x) = 0;

      /// \return The name of the function as string.
      std::string getName() const { return _function_name; }

      /// \return An optional description of the function.
      std::string getDescription() const { return _function_description; }

      /// \return Number of additional parameters for the function.
      unsigned getNumParameters() const { return _parameters.size(); }

      /// \return The collection of all additional parameters (and their values).
      ParameterMap getParameterMap() const { return _parameters; }

      /// \return Pointer to the FunctionParameter which is named \p name.
      FunctionParameter::parameter_ptr_type getParameter(const std::string &name) {
        return FunctionParameter::parameter_ptr_type(_parameters.getParameter(name));
      }

      /// \return Pointer to the FunctionParameterValue which is named \p name.
      FunctionParameter::value_ptr_type getParameterValue(const std::string &name) {
        return FunctionParameter::value_ptr_type(_parameters.getValue(name));
      }

      /// \return The lower boundary in parameter space which is set initially.
      argument_type getDefaultXMin() const { return _default_x_min; }
      /// \return The upper boundary in parameter space which is set initially.
      argument_type getDefaultXMax() const { return _default_x_max; }

    protected:

      /// Give the function a name - only allowed for classes implementing ParametricFunction.
      void setName(const std::string &newName) { _function_name = newName; }

      /// Give the function a description - only allowed for classes implementing ParametricFunction.
      void setDescription(const std::string &newDescription) { _function_description = newDescription; }

      /// Add a parameter with a name and a default value to the parameter list
      /** \tparam T Type of the parameter to be declared.
       */
      template <typename T> void declareParameter(const std::string &parameter_name,
                                                  const T &parameter_default_value);

      /// Add a parameter with a name, a value and a default value to the parameter list
      /** \tparam T Type of the parameter to be declared.
       */
      template <typename T> void declareParameter(const std::string &parameter_name,
                                                  const T &parameter_default_value,
                                                  const T &parameter_value);

      /// Change the definition space on which this function is evaluated by default.
      void setDefaultBoundaries(const ParametricFunction::argument_type &x_min,
                                const ParametricFunction::argument_type &x_max);

    private:

      /// Name for the function.
      std::string _function_name;
      /// Slightly more exhaustive description of the function.
      std::string _function_description;
      /// List of FunctionParameter s the function might have.
      ParameterMap _parameters;
      /// Default lower boundary of definition space.
      argument_type _default_x_min;
      /// Default upper boundary of definition space.
      argument_type _default_x_max;
};

/** \param x_min Lower boundary of the default definition space.
 *  \param x_max Upper boundary of the default definition space.
 */
template <unsigned N, unsigned P, typename NUM>
inline
void ParametricFunction<N, P, NUM>::setDefaultBoundaries(
  const ParametricFunction<N, P, NUM>::argument_type& x_min,
  const ParametricFunction<N, P, NUM>::argument_type& x_max) {
  _default_x_min = x_min;
  _default_x_max = x_max;
}

/** \param parameter_name Name of the parameter.
 *  \param parameter_default_value Default value for the parameter.
 */
template <unsigned N, unsigned P, typename NUM>
template<typename T>
inline
void ParametricFunction<N, P, NUM>::declareParameter(
    const std::string &parameter_name,
    const T &parameter_default_value) {
  if (_parameters.find(parameter_name) != _parameters.end()) return;

  _parameters.insertByDefault(parameter_name, parameter_default_value);
}

/** \param parameter_name Name of the parameter.
 *  \param parameter_default_value Default value for the parameter.
 *  \param parameter_value Actual value of the parameter.
 */
template <unsigned N, unsigned P, typename NUM>
  template<typename T>
inline
void ParametricFunction<N, P, NUM>::declareParameter(
    const std::string& parameter_name,
    const T& parameter_default_value,
    const T& parameter_value) {
  declareParameter(parameter_name, parameter_default_value);
  _parameters[parameter_name]->setValue(new FunctionParameterValue<T>(parameter_value));
}

#endif // VECTORFUNCTION_H
