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

#ifndef LOOP_HELPER_H
#define LOOP_HELPER_H

#include "NestedVector.h"
#include "Vector.h"

#include <tr1/memory>

/// Class that applies a function on every value in a NestedVector
template <unsigned N, unsigned P, unsigned dimension>
class LoopHelper {
  
  public:
    
    /// Set the function, boundaries and grid size we're working with
    LoopHelper(
        const VecMath::Vector<P> &x_min,
        const VecMath::Vector<P> &x_max,
        const VecMath::Vector<P, unsigned> &grid_size,
        std::tr1::shared_ptr< ParametricFunction< N, P > > f
    );
    
    /// Loop over one dimension, if necessary loop over lower dimensions too.
    void recalculateOneDimensionOfGrid(
        VecMath::NestedVector< VecMath::Vector<N>, dimension > &values,
        VecMath::Vector<P> &current_x
    );
    
  private:
    
    VecMath::Vector<P> _x_min;
    VecMath::Vector<P> _x_max;
    VecMath::Vector<P, unsigned> _grid_size;
    std::tr1::shared_ptr< ParametricFunction< N, P > > _f;
    
};

/// Specialization to end recursion
template <unsigned N, unsigned P>
class LoopHelper< N, P, 1 > {

  public:
    
    /// Set the function, boundaries and grid size we're working with.
    LoopHelper(
        const VecMath::Vector<P> &x_min,
        const VecMath::Vector<P> &x_max,
        const VecMath::Vector<P, unsigned> &grid_size,
        std::tr1::shared_ptr< ParametricFunction< N, P > > f
    );

    /// Loop over one dimension, evaluating _f and filling \p values.
    void recalculateOneDimensionOfGrid(
        VecMath::NestedVector< VecMath::Vector<N>, 1 > &values,
        VecMath::Vector<P> &current_x
    );

  private:
    
    VecMath::Vector<P> _x_min;
    VecMath::Vector<P> _x_max;
    VecMath::Vector<P, unsigned> _grid_size;
    std::tr1::shared_ptr< ParametricFunction< N, P > > _f;
};

template <unsigned N, unsigned P, unsigned dimension>
  LoopHelper<N, P, dimension>::LoopHelper(
    const VecMath::Vector<P> &x_min,
    const VecMath::Vector<P> &x_max,
    const VecMath::Vector<P, unsigned> &grid_size,
    std::tr1::shared_ptr< ParametricFunction< N, P > > f):
    _x_min(x_min), _x_max(x_max), _grid_size(grid_size), _f(f) { }

template <unsigned N, unsigned P>
  LoopHelper<N, P, 1>::LoopHelper(
    const VecMath::Vector<P> &x_min,
    const VecMath::Vector<P> &x_max,
    const VecMath::Vector<P, unsigned> &grid_size,
    std::tr1::shared_ptr< ParametricFunction< N, P > > f):
    _x_min(x_min), _x_max(x_max), _grid_size(grid_size), _f(f) { }

template <unsigned N, unsigned P, unsigned dimension>
void 
LoopHelper<N, P, dimension>::
recalculateOneDimensionOfGrid(
      VecMath::NestedVector< VecMath::Vector<N>, dimension > &values,
      VecMath::Vector<P> &current_x) {
  unsigned grid_size_in_current_dim = _grid_size[dimension-1];
  double x_min_in_current_dim = _x_min[dimension-1];
  double x_max_in_current_dim = _x_max[dimension-1];
  
  values.resize(grid_size_in_current_dim);

  for (unsigned i = 0; i < grid_size_in_current_dim; ++i) {
    double x = (x_max_in_current_dim-x_min_in_current_dim)*(double)i/(double)(grid_size_in_current_dim-1)+x_min_in_current_dim;
    LoopHelper< N, P, dimension-1 > sub_looper(
      _x_min, _x_max, _grid_size, _f);
    current_x[dimension-1] = x;
    sub_looper.recalculateOneDimensionOfGrid(values[i], current_x);
  }
}

template <unsigned N, unsigned P>
void 
LoopHelper<N, P, 1>::
recalculateOneDimensionOfGrid(
      VecMath::NestedVector< VecMath::Vector<N>, 1> &values,
      VecMath::Vector<P> &current_x) {
  unsigned grid_size_in_current_dim = _grid_size[0];
  double x_min_in_current_dim = _x_min[0];
  double x_max_in_current_dim = _x_max[0];

  values.resize(grid_size_in_current_dim);

  for (unsigned i = 0; i < grid_size_in_current_dim; ++i) {
    double x = (x_max_in_current_dim-x_min_in_current_dim)*(double)i/(double)(grid_size_in_current_dim-1)+x_min_in_current_dim;
    current_x[0] = x;
    VecMath::Vector<N> fx = _f->f(current_x);
#   if 0
    std::cerr << current_x << " -> " << fx << std::endl;
#   endif    
    values[i] = fx;
  }
}


#endif