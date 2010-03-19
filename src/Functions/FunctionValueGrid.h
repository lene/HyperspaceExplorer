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

#include <tr1/memory>

template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
  class FunctionValueGrid {
    public:

      typedef ParametricFunction<definition_space_dimension, parameter_space_dimension> function_type;
      typedef std::tr1::shared_ptr<function_type> function_ptr_type;
      typedef VecMath::Vector<parameter_space_dimension> boundary_type;
      typedef VecMath::Vector<parameter_space_dimension, unsigned> grid_size_type;
      typedef VecMath::NestedVector< VecMath::Vector<definition_space_dimension>, parameter_space_dimension > value_storage_type;
      
      FunctionValueGrid();
      FunctionValueGrid(function_ptr_type f);
      FunctionValueGrid(function_ptr_type f,
                        const FunctionValueGrid::boundary_type &x_min, const FunctionValueGrid::boundary_type &x_max,
                        const FunctionValueGrid::grid_size_type &grid_size);
      virtual ~FunctionValueGrid() { }

      void setGridSize(const FunctionValueGrid::grid_size_type &grid_size);
      void setBoundaries(const FunctionValueGrid::boundary_type &x_min, const FunctionValueGrid::boundary_type &x_max);
      
    private:

      void recalculate_grid();
      
      function_ptr_type _f;
      boundary_type _x_min;
      boundary_type _x_max;
      grid_size_type _grid_size;
      value_storage_type _function_values;
      
      const static double EPSILON = 1e-8;
};

template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
  FunctionValueGrid<definition_space_dimension, parameter_space_dimension>::FunctionValueGrid():
    _f(), _x_min(), _x_max(), _grid_size(), _function_values() { }

template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
  FunctionValueGrid<definition_space_dimension, parameter_space_dimension>::FunctionValueGrid(
        FunctionValueGrid::function_ptr_type f):
    _f(f), _x_min(), _x_max(), _grid_size(), _function_values() { }

template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
  FunctionValueGrid<definition_space_dimension, parameter_space_dimension>::FunctionValueGrid(
          FunctionValueGrid::function_ptr_type f,
        const FunctionValueGrid::boundary_type &x_min,
        const FunctionValueGrid::boundary_type &x_max,
        const FunctionValueGrid::grid_size_type &grid_size):
      _f(f), _x_min(), _x_max(), _grid_size(), _function_values() {
    setGridSize(grid_size);
    setBoundaries(x_min, x_max);  
  }

template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
  void FunctionValueGrid<definition_space_dimension, parameter_space_dimension>::setGridSize(
    const FunctionValueGrid::grid_size_type &grid_size) {
  if (grid_size == _grid_size) return;
  _grid_size = grid_size;
  if ((_x_max-_x_min).sqnorm() > EPSILON) recalculate_grid();
}

template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
  void FunctionValueGrid<definition_space_dimension, parameter_space_dimension>::setBoundaries(
    const FunctionValueGrid::boundary_type &x_min, const FunctionValueGrid::boundary_type &x_max) {
  if ((_x_max-x_max).sqnorm() < EPSILON && (_x_min-x_min).sqnorm() < EPSILON) return;
  _x_min = x_min;
  _x_max = x_max;
  if (_grid_size.sqnorm()) recalculate_grid();
}

template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
  void FunctionValueGrid<definition_space_dimension, parameter_space_dimension>::recalculate_grid() {
    
}
    
#endif // FUNCTIONVALUEGRID_H
