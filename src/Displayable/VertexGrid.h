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

#ifndef VertexGrid_H
#define VertexGrid_H

#include "ParametricFunction.h"

#include "LoopHelper.h"
#include "MultiDimensionalVector.h"
#include "Vector.h"

#include <memory>

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
  class VertexGrid {

    public:

      /// Type for storing the size of the grid in all required dimensions.
      typedef VecMath::Vector<P, unsigned> grid_size_type;
      /// Type for the storage of the function values on all grid points.
      typedef VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P > value_storage_type;

      /// Create an empty grid.
      VertexGrid();
      /// Fill a grid with a defined grid size. The supplied ParametricFunction knows its definition space.
      VertexGrid(const VertexGrid::grid_size_type &grid_size);
      
      VertexGrid(const value_storage_type &vertices);
      /// Copy constructor is needed because otherwise it is implicitly deleted
      VertexGrid(const VertexGrid<N, P, NUM> &other) {
          _vertices = other._vertices;
          _grid_size = other._grid_size;
      }
      
      VertexGrid<N, P, NUM> & operator=(const VertexGrid<N, P, NUM> & other) {
          if (this == &other) return *this;
          _vertices = other._vertices;
          _grid_size = other._grid_size;
          return *this;
      }

      virtual ~VertexGrid() { }

      /// Change the size of the grid. If possible, function values are recalculated.
      void setGridSize(const VertexGrid::grid_size_type &grid_size);

      /// Access the stored function values.
      const value_storage_type &getValues() const { return _vertices; }

      /// Access the stored function values.
      value_storage_type &getValuesNonConst() { return _vertices; }

    protected:

      /// Number of points on the grid in all dimensions.
      grid_size_type _grid_size;
      /// The actual function values on the grid.
      value_storage_type _vertices;

};

namespace VertexGridUtility {
    template <typename T, unsigned D>
    void resizeRecursively(
        VecMath::MultiDimensionalVector<T, D> &vec,
        const VecMath::Vector<D, unsigned> &size
    );

    template <typename T>
    void resizeRecursively(
        VecMath::MultiDimensionalVector<T, 1> &vec,
        const VecMath::Vector<1, unsigned> &size
    );
}
template <unsigned N, unsigned P, typename NUM>
  VertexGrid<N, P, NUM>::VertexGrid():
    _grid_size(), _vertices() { }

/** \param f The function whose values are stored on its definition space.
 *  \param grid_size The size of the grid in each of its dimensions.
 */
template <unsigned N, unsigned P, typename NUM>
  VertexGrid<N, P, NUM>::VertexGrid(
        const VertexGrid::grid_size_type &grid_size):
      _grid_size(), _vertices() {
    setGridSize(grid_size);
  }

template <unsigned N, unsigned P, typename NUM>
  VertexGrid<N, P, NUM>::VertexGrid(
        const VertexGrid::value_storage_type &values):
      _grid_size(), _vertices(values) {
    _grid_size = values.size();
  }

/** \param grid_size The new grid size.
 */
template <unsigned N, unsigned P, typename NUM>
  void VertexGrid<N, P, NUM>::setGridSize(
    const VertexGrid::grid_size_type &grid_size) {
  if (grid_size == _grid_size) return;
  _grid_size = grid_size;
  VertexGridUtility::resizeRecursively(_vertices, _grid_size);
}

namespace VertexGridUtility {
    template <unsigned D> 
    VecMath::Vector<D-1, unsigned>
    clipSizeVector(const VecMath::Vector<D, unsigned> &size) {
        VecMath::Vector<D-1, unsigned> size_rest;
        for (unsigned i = 1; i < D; ++i) size_rest[i] = size[i];
        return size_rest;
    }

    template <typename T, unsigned D>
    void resizeRecursively(
        VecMath::MultiDimensionalVector<T, D> &vec,
        const VecMath::Vector<D, unsigned> &size
    ) {
        vec.resize(size[0]);
        auto size_rest = clipSizeVector(size);

        for (auto it = vec.begin(); it != vec.end(); ++it) {
            resizeRecursively(*it, size_rest);
        }
    }

    template <typename T>
    void resizeRecursively(
        VecMath::MultiDimensionalVector<T, 1> &vec,
        const VecMath::Vector<1, unsigned> &size
    ) {
        vec.resize(size[0]);
    }
}
#endif // VertexGrid_H
