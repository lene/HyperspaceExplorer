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

#include "MultiDimensionalVector.h"
#include "Vector.h"

#include <tr1/memory>

/// Class that applies a function on every value in a MultiDimensionalVector
/** \tparam N The dimension of the definition vector space.
 *  \tparam P The dimension of the parameter vector space.
 *  \tparam dimension The dimension (in parameter vector space) we currently
 *      loop over.
 *  \tparam NUM The numeric type managed by the grid.
 */
template <unsigned N, unsigned P, unsigned dimension, typename NUM>
class LoopHelper {

  public:

    /// Set the function, boundaries and grid size we're working with
    LoopHelper(
        const VecMath::Vector<P, NUM> &x_min,
        const VecMath::Vector<P, NUM> &x_max,
        const VecMath::Vector<P, unsigned> &grid_size,
        std::tr1::shared_ptr< ParametricFunction< N, P, NUM > > f
    );

    /// Loop over one dimension, if necessary loop over lower dimensions too.
    void recalculateOneDimensionOfGrid(
        VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, dimension > &values,
        VecMath::Vector<P, NUM> &current_x
    );

  private:

    /// Lower boundary of grid on which the ParametricFunction is applied.
    VecMath::Vector<P, NUM> _x_min;
    /// Upper boundary of grid on which the ParametricFunction is applied.
    VecMath::Vector<P, NUM> _x_max;
    /// Vector of grid sizes.
    VecMath::Vector<P, unsigned> _grid_size;
    /// The function to be evaluated on every grid point.
    std::tr1::shared_ptr< ParametricFunction< N, P, NUM > > _f;

};

/// Specialization to end recursion
template <unsigned N, unsigned P, typename NUM>
class LoopHelper< N, P, 1, NUM > {

  public:

    /// Set the function, boundaries and grid size we're working with.
    LoopHelper(
        const VecMath::Vector<P, NUM> &x_min,
        const VecMath::Vector<P, NUM> &x_max,
        const VecMath::Vector<P, unsigned> &grid_size,
        std::tr1::shared_ptr< ParametricFunction< N, P, NUM > > f
    );

    /// Loop over one dimension, evaluating _f and filling \p values.
    void recalculateOneDimensionOfGrid(
        VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, 1 > &values,
        VecMath::Vector<P, NUM> &current_x
    );

  private:

    /// Lower boundary of grid on which the ParametricFunction is applied.
    VecMath::Vector<P, NUM> _x_min;
    /// Upper boundary of grid on which the ParametricFunction is applied.
    VecMath::Vector<P, NUM> _x_max;
    /// Vector of grid sizes.
    VecMath::Vector<P, unsigned> _grid_size;
    /// The function to be evaluated on every grid point.
    std::tr1::shared_ptr< ParametricFunction< N, P, NUM > > _f;
};

template <unsigned N, unsigned P, unsigned dimension, typename NUM>
  LoopHelper<N, P, dimension, NUM>::LoopHelper(
    const VecMath::Vector<P, NUM> &x_min,
    const VecMath::Vector<P, NUM> &x_max,
    const VecMath::Vector<P, unsigned> &grid_size,
    std::tr1::shared_ptr< ParametricFunction< N, P, NUM > > f):
    _x_min(x_min), _x_max(x_max), _grid_size(grid_size), _f(f) { }

template <unsigned N, unsigned P, typename NUM>
  LoopHelper<N, P, 1, NUM>::LoopHelper(
    const VecMath::Vector<P, NUM> &x_min,
    const VecMath::Vector<P, NUM> &x_max,
    const VecMath::Vector<P, unsigned> &grid_size,
    std::tr1::shared_ptr< ParametricFunction< N, P, NUM > > f):
    _x_min(x_min), _x_max(x_max), _grid_size(grid_size), _f(f) { }

template <unsigned N, unsigned P, unsigned dimension, typename NUM>
void
LoopHelper<N, P, dimension, NUM>::
recalculateOneDimensionOfGrid(
      VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, dimension > &values,
      VecMath::Vector<P, NUM> &current_x) {
  unsigned grid_size_in_current_dim = _grid_size[dimension-1];
  NUM x_min_in_current_dim = _x_min[dimension-1];
  NUM x_max_in_current_dim = _x_max[dimension-1];

  values.resize(grid_size_in_current_dim);

  for (unsigned i = 0; i < grid_size_in_current_dim; ++i) {
    NUM x = (x_max_in_current_dim-x_min_in_current_dim)*(NUM)i/(NUM)(grid_size_in_current_dim-1)+x_min_in_current_dim;
    LoopHelper< N, P, dimension-1, NUM > sub_looper(
      _x_min, _x_max, _grid_size, _f);
    current_x[dimension-1] = x;
    sub_looper.recalculateOneDimensionOfGrid(values[i], current_x);
  }
}

template <unsigned N, unsigned P, typename NUM>
void
LoopHelper<N, P, 1, NUM>::
recalculateOneDimensionOfGrid(
      VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, 1> &values,
      VecMath::Vector<P, NUM> &current_x) {
  unsigned grid_size_in_current_dim = _grid_size[0];
  NUM x_min_in_current_dim = _x_min[0];
  NUM x_max_in_current_dim = _x_max[0];

  values.resize(grid_size_in_current_dim);

  for (unsigned i = 0; i < grid_size_in_current_dim; ++i) {
    NUM x = (x_max_in_current_dim-x_min_in_current_dim)*(NUM)i/(NUM)(grid_size_in_current_dim-1)+x_min_in_current_dim;
    current_x[0] = x;
    VecMath::Vector<N, NUM> fx = _f->f(current_x);
    values[i] = fx;
  }
}


#endif