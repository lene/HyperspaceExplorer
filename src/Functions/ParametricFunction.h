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

#ifndef VECTORFUNCTION_H
#define VECTORFUNCTION_H

#include "ParameterMap.h"
#include "Vector.h"

template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
  class ParametricFunction {

    public:
      
      typedef VecMath::Vector<parameter_space_dimension> argument_type;
      typedef VecMath::Vector<definition_space_dimension> return_type;
      
      virtual return_type f(const argument_type &x) = 0;

        /** \return number of parameters for the function                     */
        unsigned getNumParameters() { return _parameters.size(); }

        /// \return The collection of all parameters (and their values)
        ParameterMap getParameters() { return _parameters; }
        /// \return The value of the parameter which is named \p name
        FunctionParameter *getParameter(const std::string &name) {
          return _parameters.getParameter(name);
        }
        FunctionParameterValueBase *getParameterValue(const std::string &name) {
          return _parameters.getValue(name);
        }
    
    protected:
      /// Add a parameter to the list of parameters
      template <typename T> void declareParameter(const std::string &parameter_name,
                                                  const T &);
      /// Add a parameter to the list of parameters
      template <typename T> void declareParameter(const std::string &,
                                                  const T &, const T &);

    private:
      ParameterMap _parameters;
};

#endif // VECTORFUNCTION_H
