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

///
/** This class evaluates a ParametricFunction on all vertices of a \p P - dimensional
 *  (hyper-) grid in \p N dimensional vector space.
 *
 *  \todo It provides functions to apply an arbitray Transform on the \p N -
 *  dimensional vertices, Project them into three-dimensional space and Draw
 *  the resulting three-dimensional image onto a View.
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
    typedef ParametricFunction<N, P, NUM> function_type;
    /// A vertex in \p N - space.
    typedef VecMath::Vector<N, NUM> vertex_type;
    /// A vertex projected into three dimensions.
    typedef VecMath::Vector<3, NUM> projected_vertex_type;

    VertexHolder(ParameterMap parameters);
    VertexHolder(std::shared_ptr< function_type > f);

    virtual void Transform (const VecMath::Rotation<N, NUM> &R,
                            const vertex_type &T,
                            const vertex_type &scale = vertex_type(1.));
    virtual void Project (double ScrW, double CamW, bool DepthCue4D);

    virtual unsigned int getDefinitionSpaceDimensions();

    virtual void for_each_vertex(function_on_fourspace_vertex apply);
    virtual void for_each_vertex_transformed(function_on_fourspace_and_transformed_vertex apply);
    virtual void for_each_vertex_transformed_projected(function_on_fourspace_transformed_and_projected_vertex apply);
    virtual void for_each_projected(function_on_projected_vertex apply);

    /** \return number of parameters for the function */
    virtual unsigned getNumParameters();

  protected:

    /// Array of function values.
    const VecMath::MultiDimensionalVector< vertex_type, P > &X() const;
    void setX(const VertexGrid<N, P, NUM>& x);
    /// Array of function values after transform.
    const VecMath::MultiDimensionalVector< vertex_type, P > &Xtrans() const;
    void setXtrans(const VecMath::MultiDimensionalVector< vertex_type, P >& x);
    /// Array of projected function values.
    const VecMath::MultiDimensionalVector< projected_vertex_type, P > &Xscr() const;
    void setXscr(const VecMath::MultiDimensionalVector< projected_vertex_type, P >& x);

  private:

    class Impl;
    std::unique_ptr<Impl> pImpl_;

};

#endif // VertexHolder_H
