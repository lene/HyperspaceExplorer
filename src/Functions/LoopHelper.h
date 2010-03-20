#ifndef LOOP_HELPER_H
#define LOOP_HELPER_H

#include "NestedVector.h"
#include "Vector.h"

#include <tr1/memory>

/// Class that applies a function on every value in a NestedVector
template <unsigned definition_space_dimension, unsigned parameter_space_dimension, unsigned dimension>
class LoopHelper {
  
  public:
    
    /// Set the function, boundaries and grid size we're working with
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

/// Specialization to end recursion
template <unsigned definition_space_dimension, unsigned parameter_space_dimension>
class LoopHelper< definition_space_dimension, parameter_space_dimension, 1 > {

  public:
    
    /// Set the function, boundaries and grid size we're working with
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


#endif