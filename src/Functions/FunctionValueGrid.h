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
      FunctionValueGrid(const function_ptr_type &f);
      FunctionValueGrid(const function_ptr_type &f,
                        const FunctionValueGrid::boundary_type &x_min, const FunctionValueGrid::boundary_type &x_max,
                        const FunctionValueGrid::grid_size_type &grid_size);
      virtual ~FunctionValueGrid() { }

      void setGridSize(const FunctionValueGrid::grid_size_type &grid_size);
      void setBoundaries(const FunctionValueGrid::boundary_type &x_min, const FunctionValueGrid::boundary_type &x_max);
      
      const value_storage_type &getValues() const { return _function_values; }
      
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
        const FunctionValueGrid::function_ptr_type &f):
    _f(f), _x_min(), _x_max(), _grid_size(), _function_values() { }

template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
  FunctionValueGrid<definition_space_dimension, parameter_space_dimension>::FunctionValueGrid(
        const FunctionValueGrid::function_ptr_type &f,
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

template <unsigned definition_space_dimension, unsigned parameter_space_dimension, unsigned dimension>
struct LoopHelper {
  
    LoopHelper(
        const VecMath::Vector<parameter_space_dimension> &x_min,
        const VecMath::Vector<parameter_space_dimension> &x_max,
        const VecMath::Vector<parameter_space_dimension, unsigned> &grid_size,
        std::tr1::shared_ptr< ParametricFunction< definition_space_dimension, parameter_space_dimension > > f
    );
    
    void recalculateOneDimensionOfGrid(
        VecMath::NestedVector< VecMath::Vector<definition_space_dimension>, dimension > &values,
        VecMath::Vector<parameter_space_dimension> &current_x
    );
    
  private:
    
    VecMath::Vector<parameter_space_dimension> _x_min;
    VecMath::Vector<parameter_space_dimension> _x_max;
    VecMath::Vector<parameter_space_dimension, unsigned> _grid_size;
    std::tr1::shared_ptr< ParametricFunction< definition_space_dimension, parameter_space_dimension > > _f;
    
};

template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
struct LoopHelper< definition_space_dimension, parameter_space_dimension, 1 > {

      LoopHelper(
        const VecMath::Vector<parameter_space_dimension> &x_min,
        const VecMath::Vector<parameter_space_dimension> &x_max,
        const VecMath::Vector<parameter_space_dimension, unsigned> &grid_size,
        std::tr1::shared_ptr< ParametricFunction< definition_space_dimension, parameter_space_dimension > > f
    );

    void recalculateOneDimensionOfGrid(
        VecMath::NestedVector< VecMath::Vector<definition_space_dimension>, 1 > &values,
        VecMath::Vector<parameter_space_dimension> &current_x
    );

  private:
    
    VecMath::Vector<parameter_space_dimension> _x_min;
    VecMath::Vector<parameter_space_dimension> _x_max;
    VecMath::Vector<parameter_space_dimension, unsigned> _grid_size;
    std::tr1::shared_ptr< ParametricFunction< definition_space_dimension, parameter_space_dimension > > _f;
};

template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
  void FunctionValueGrid<definition_space_dimension, parameter_space_dimension>::recalculate_grid() {
    LoopHelper< definition_space_dimension, parameter_space_dimension, parameter_space_dimension > looper(
      _x_min, _x_max, _grid_size, _f);
    VecMath::Vector<parameter_space_dimension> x = _x_min;
    looper.recalculateOneDimensionOfGrid(_function_values, x);
}


template <unsigned definition_space_dimension, unsigned parameter_space_dimension, unsigned dimension>
  LoopHelper<definition_space_dimension, parameter_space_dimension, dimension>::LoopHelper(
    const VecMath::Vector<parameter_space_dimension> &x_min,
    const VecMath::Vector<parameter_space_dimension> &x_max,
    const VecMath::Vector<parameter_space_dimension, unsigned> &grid_size,
    std::tr1::shared_ptr< ParametricFunction< definition_space_dimension, parameter_space_dimension > > f):
    _x_min(x_min), _x_max(x_max), _grid_size(grid_size), _f(f) { }

template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
  LoopHelper<definition_space_dimension, parameter_space_dimension, 1>::LoopHelper(
    const VecMath::Vector<parameter_space_dimension> &x_min,
    const VecMath::Vector<parameter_space_dimension> &x_max,
    const VecMath::Vector<parameter_space_dimension, unsigned> &grid_size,
    std::tr1::shared_ptr< ParametricFunction< definition_space_dimension, parameter_space_dimension > > f):
    _x_min(x_min), _x_max(x_max), _grid_size(grid_size), _f(f) { }

template <unsigned definition_space_dimension, unsigned parameter_space_dimension, unsigned dimension>
void 
LoopHelper<definition_space_dimension, parameter_space_dimension, dimension>::
recalculateOneDimensionOfGrid(
      VecMath::NestedVector< VecMath::Vector<definition_space_dimension>, dimension > &values,
      VecMath::Vector<parameter_space_dimension> &current_x) {
  unsigned grid_size_in_current_dim = _grid_size[dimension-1];
  double x_min_in_current_dim = _x_min[dimension-1];
  double x_max_in_current_dim = _x_max[dimension-1];
  
  values.resize(grid_size_in_current_dim);

  for (unsigned i = 0; i < grid_size_in_current_dim; ++i) {
    double x = (x_max_in_current_dim-x_min_in_current_dim)*(double)i/(double)(grid_size_in_current_dim-1)+x_min_in_current_dim;
    LoopHelper< definition_space_dimension, parameter_space_dimension, dimension-1 > sub_looper(
      _x_min, _x_max, _grid_size, _f);
    current_x[dimension-1] = x;
    sub_looper.recalculateOneDimensionOfGrid(values[i], current_x);
  }
}

template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
void 
LoopHelper<definition_space_dimension, parameter_space_dimension, 1>::
recalculateOneDimensionOfGrid(
      VecMath::NestedVector< VecMath::Vector<definition_space_dimension>, 1> &values,
      VecMath::Vector<parameter_space_dimension> &current_x) {
  unsigned grid_size_in_current_dim = _grid_size[0];
  double x_min_in_current_dim = _x_min[0];
  double x_max_in_current_dim = _x_max[0];

  values.resize(grid_size_in_current_dim);

  for (unsigned i = 0; i < grid_size_in_current_dim; ++i) {
    double x = (x_max_in_current_dim-x_min_in_current_dim)*(double)i/(double)(grid_size_in_current_dim-1)+x_min_in_current_dim;
    current_x[0] = x;
    VecMath::Vector<definition_space_dimension> fx = _f->f(current_x);
#   if 0
    std::cerr << current_x << " -> " << fx << std::endl;
#   endif    
    values[i] = fx;
  }
}


#endif // FUNCTIONVALUEGRID_H
