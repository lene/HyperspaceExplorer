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

#ifndef FUNCTIONVALUEGRID_H
#define FUNCTIONVALUEGRID_H

#include "ParametricFunction.h"

#include "NestedVector.h"
#include "Vector.h"

template <unsigned definition_space_dimension, unsigned value_space_dimension>
  class FunctionValueGrid {
    public:

      typedef ParametricFunction<definition_space_dimension, value_space_dimension> function_type;
      typedef VecMath::Vector<value_space_dimension> boundary_type;
      typedef VecMath::Vector<value_space_dimension, unsigned> grid_size_type;
      
      FunctionValueGrid();
      FunctionValueGrid(const FunctionValueGrid::function_type &f);
      FunctionValueGrid(const FunctionValueGrid::function_type &f,
                        const FunctionValueGrid::boundary_type &x_min, const FunctionValueGrid::boundary_type &x_max,
                        const FunctionValueGrid::grid_size_type &grid_size);

      void setGridSize(const FunctionValueGrid::grid_size_type &grid_size);
      void setBoundaries(const FunctionValueGrid::boundary_type &x_min, const FunctionValueGrid::boundary_type &x_max);
      
    private:

      function_type *_f;
      boundary_type _x_min;
      boundary_type _x_max;
      grid_size_type _grid_size;
      VecMath::NestedVector< VecMath::Vector<definition_space_dimension>, value_space_dimension > _function_values;
};

template <unsigned definition_space_dimension, unsigned value_space_dimension>
  FunctionValueGrid<definition_space_dimension, value_space_dimension>::FunctionValueGrid():
    _f(), _x_min(), _x_max(), _grid_size(), _function_values() { }

template <unsigned definition_space_dimension, unsigned value_space_dimension>
  FunctionValueGrid<definition_space_dimension, value_space_dimension>::FunctionValueGrid(
        const FunctionValueGrid::function_type &f):
    _f(&f), _x_min(), _x_max(), _grid_size(), _function_values() { }

template <unsigned definition_space_dimension, unsigned value_space_dimension>
  FunctionValueGrid<definition_space_dimension, value_space_dimension>::FunctionValueGrid(
        const FunctionValueGrid::function_type &f,
        const FunctionValueGrid::boundary_type &x_min,
        const FunctionValueGrid::boundary_type &x_max,
        const FunctionValueGrid::grid_size_type &grid_size):
      _f(&f), _x_min(), _x_max(), _grid_size(), _function_values() {
    setGridSize(grid_size);
    setBoundaries(x_min, x_max);  
  }


#endif // FUNCTIONVALUEGRID_H
