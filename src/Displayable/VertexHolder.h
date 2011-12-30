/*
Hyperspace Explorer - visualizing higher-dimensional geometry
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

#ifndef VertexHolder_H
#define VertexHolder_H

#include "Displayable.h"

namespace VecMath {
  template <typename T, unsigned D> class MultiDimensionalVector;
}

template <unsigned N, unsigned P, typename NUM> class ParametricFunction;
template <unsigned N, unsigned P, typename NUM> class VertexGrid;

/// This class stores vertices in a \p P - dimensional (hyper-) grid in an \p N
/// dimensional vector space.
/**
 *  It provides functions to apply an arbitray Transform on the \p N dimensional
 *  vertices and Project them into three-dimensional space. The Draw() method
 *  must be implemented in inheriting classes.
 *
 *  \tparam N The dimension of the definition vector space.
 *  \tparam P The dimension of the parameter vector space.
 *  \tparam NUM The numeric type managed by the grid.
 *
 *  \ingroup FunctionGroup
 *  @author Lene Preuss <lene.preuss@gmail.com>
 */
template <unsigned N, unsigned P, typename NUM = double>
class VertexHolder : public Displayable {

  public:

    /// The type of the function that is evaluated on every vertex of the grid.
   // typedef ParametricFunction<N, P, NUM> function_type;
    /// A vertex in \p N - space.
    typedef VecMath::Vector<N, NUM> vertex_type;
    /// A vertex projected into three dimensions.
    typedef VecMath::Vector<3, NUM> projected_vertex_type;

    VertexHolder(ParameterMap parameters);

    virtual void Transform (const VecMath::Rotation<N, NUM> &R,
                            const vertex_type &T,
                            const vertex_type &scale = vertex_type(1.));
    virtual void Project (double ScrW, double CamW, bool DepthCue4D);

    virtual void calibrateColors();

    virtual unsigned int getDefinitionSpaceDimensions();

    virtual void for_each_vertex(function_on_fourspace_vertex apply);
    virtual void for_each_vertex_transformed(function_on_fourspace_and_transformed_vertex apply);
    virtual void for_each_vertex_transformed_projected(function_on_fourspace_transformed_and_projected_vertex apply);
    virtual void for_each_projected(function_on_projected_vertex apply);

  protected:

    /// Array of vertices.
    const VecMath::MultiDimensionalVector< vertex_type, P > &X() const;
    /// Replaces the array of vertices with \p x.
    void setX(const VertexGrid<N, P, NUM>& x);
    /// Array of vertices after transform.
    const VecMath::MultiDimensionalVector< vertex_type, P > &Xtrans() const;
    /// Replaces the array of transformed vertices with \p x.
    void setXtrans(const VecMath::MultiDimensionalVector< vertex_type, P >& x);
    /// Array of projected vertices.
    const VecMath::MultiDimensionalVector< projected_vertex_type, P > &Xscr() const;
    /// Replaces the array of projected vertices with \p x.
    void setXscr(const VecMath::MultiDimensionalVector< projected_vertex_type, P >& x);

    /// Access to the vertices as VertexGrid<N, P, NUM>.
    const VertexGrid<N, P, NUM> &getGrid() const;
    /// Write access to the vertices as VertexGrid<N, P, NUM>.
    VertexGrid<N, P, NUM> &getGridNonConst();
    
    /// Sets the function that is called for every vertex by calibrateColors().
    void setColorCalibrationFunction(function_on_fourspace_vertex calibrate);

  private:

    class Impl;
    std::unique_ptr<Impl> pImpl_;

};

#endif // VertexHolder_H
