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

*/

#ifndef FUNCTIONVALUEGRID_H
#define FUNCTIONVALUEGRID_H

#include "ParametricFunction.h"

#include "LoopHelper.h"
#include "MultiDimensionalVector.h"
#include "Vector.h"

#include <tr1/memory>

/// Values of a ParametricFunction stored on a grid representation of its parameter space.
/** This class evaluates the parametric equation represented by a ParametricFunction
 *  on points throughout its definition space and stores the values of the function
 *  at those points in a \p P dimensional grid.
 *
 *  \tparam N The dimension of the definition vector space.
 *  \tparam P The dimension of the parameter vector space.
 *  \tparam NUM The numeric type managed by the grid.
 *
 *  \ingroup FunctionGroup
 *  @author Lene Preuss <lene.preuss@gmail.com>
 */
template <unsigned N, unsigned P, typename NUM = double>
  class FunctionValueGrid {

    public:

      /// The type of the function whose values are stored in this class.
      typedef ParametricFunction<N, P, NUM> function_type;
      /// The type of pointers to function_type, used for late binding.
      typedef std::tr1::shared_ptr<function_type> function_ptr_type;
      /// The type of the lower and upper bounds of the definition space.
      typedef VecMath::Vector<P, NUM> boundary_type;
      /// Type for storing the size of the grid in all required dimensions.
      typedef VecMath::Vector<P, unsigned> grid_size_type;
      /// Type for the storage of the function values on all grid points.
      typedef VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P > value_storage_type;

      /// Create an empty grid.
      FunctionValueGrid();
      /// Prepare a grid with a defined ParametricFunction.
      FunctionValueGrid(const function_ptr_type &f);
      /// Fill a grid with a defined grid size. The supplied ParametricFunction knows its definition space.
      FunctionValueGrid(const function_ptr_type &f,
                        const FunctionValueGrid::grid_size_type &grid_size);
      /// Fill a grid with a defined grid size and boundaries.
      FunctionValueGrid(const function_ptr_type &f,
                        const FunctionValueGrid::grid_size_type &grid_size,
                        const FunctionValueGrid::boundary_type &x_min, const FunctionValueGrid::boundary_type &x_max);

      virtual ~FunctionValueGrid() { }

      /// Change the size of the grid. If possible, function values are recalculated.
      void setGridSize(const FunctionValueGrid::grid_size_type &grid_size);
      /// Change the size of the definition space. If possible, function values are recalculated.
      void setBoundaries(const FunctionValueGrid::boundary_type &x_min, const FunctionValueGrid::boundary_type &x_max);

      /// Access the stored function values.
      const value_storage_type &getValues() const { return _function_values; }

      /// Access the stored function values.
      value_storage_type &getValuesNonConst() { return _function_values; }

    private:

      /// Loop over the entire definition space and fill the grid with the function values at those points.
      void recalculate_grid();

      /// The ParametricFunction that evaluates the points on the grid.
      function_ptr_type _f;
      /// Lower boundary of the grid in all dimensions.
      boundary_type _x_min;
      /// Upper boundary of the grid in all dimensions.
      boundary_type _x_max;
      /// Number of points on the grid in all dimensions.
      grid_size_type _grid_size;
      /// The actual function values on the grid.
      value_storage_type _function_values;

      /// \todo this should be somewhere global.
      static constexpr double EPSILON = 1e-8;
};

template <unsigned N, unsigned P, typename NUM>
  FunctionValueGrid<N, P, NUM>::FunctionValueGrid():
    _f(), _x_min(), _x_max(), _grid_size(), _function_values() { }

/** \param f The function whose values are stored on its definition space.
 */
template <unsigned N, unsigned P, typename NUM>
  FunctionValueGrid<N, P, NUM>::FunctionValueGrid(
        const FunctionValueGrid::function_ptr_type &f):
    _f(f), _x_min(), _x_max(), _grid_size(), _function_values() {
  setBoundaries(f->getDefaultXMin(), f->getDefaultXMax());
}

/** \param f The function whose values are stored on its definition space.
 *  \param grid_size The size of the grid in each of its dimensions.
 */
template <unsigned N, unsigned P, typename NUM>
  FunctionValueGrid<N, P, NUM>::FunctionValueGrid(
        const FunctionValueGrid::function_ptr_type &f,
        const FunctionValueGrid::grid_size_type &grid_size):
      _f(f), _x_min(), _x_max(), _grid_size(), _function_values() {
    setGridSize(grid_size);
    setBoundaries(f->getDefaultXMin(), f->getDefaultXMax());
  }

/** \param f The function whose values are stored on its definition space.
 *  \param grid_size The size of the grid in each of its dimensions.
 *  \param x_min Lower boundary of the definition space.
 *  \param x_max Upper boundary of the definition space.
 */
template <unsigned N, unsigned P, typename NUM>
  FunctionValueGrid<N, P, NUM>::FunctionValueGrid(
        const FunctionValueGrid::function_ptr_type &f,
        const FunctionValueGrid::grid_size_type &grid_size,
        const FunctionValueGrid::boundary_type &x_min,
        const FunctionValueGrid::boundary_type &x_max):
      _f(f), _x_min(), _x_max(), _grid_size(), _function_values() {
    setGridSize(grid_size);
    setBoundaries(x_min, x_max);
  }

/** \param grid_size The new grid size.
 */
template <unsigned N, unsigned P, typename NUM>
  void FunctionValueGrid<N, P, NUM>::setGridSize(
    const FunctionValueGrid::grid_size_type &grid_size) {
  if (grid_size == _grid_size) return;
  _grid_size = grid_size;
  if (abs(VecMath::sqnorm(_x_max-_x_min)) > EPSILON) recalculate_grid();
}

/** \param x_min Lower boundary of the definition space.
 *  \param x_max Upper boundary of the definition space.
 */
template <unsigned N, unsigned P, typename NUM>
  void FunctionValueGrid<N, P, NUM>::setBoundaries(
    const FunctionValueGrid::boundary_type &x_min, const FunctionValueGrid::boundary_type &x_max) {
  if (abs(VecMath::sqnorm(_x_max-x_max)) < EPSILON && abs(VecMath::sqnorm(_x_min-x_min)) < EPSILON) return;
  _x_min = x_min;
  _x_max = x_max;
  if (VecMath::sqnorm(_grid_size)) recalculate_grid();
}

/** Initialize a LoopHelper and set it off.
 */
template <unsigned N, unsigned P, typename NUM>
  void FunctionValueGrid<N, P, NUM>::recalculate_grid() {
    LoopHelper< N, P, P, NUM > looper(
      _x_min, _x_max, _grid_size, _f);
    VecMath::Vector<P, NUM> x = _x_min;
    looper.recalculateOneDimensionOfGrid(_function_values, x);
}

#endif // FUNCTIONVALUEGRID_H
