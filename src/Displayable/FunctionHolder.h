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

#ifndef FUNCTIONHOLDER_H
#define FUNCTIONHOLDER_H

#include "VertexHolder.h"

template <unsigned P> class DefinitionRangeOfDimension;

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
class FunctionHolder : public VertexHolder<N, P, NUM> {

public:

    /// The type of the function that is evaluated on every vertex of the grid.
    typedef ParametricFunction<N, P, NUM> function_type;
    /// A vertex in \p N - space.
    typedef VecMath::Vector<N, NUM> vertex_type;
    /// A vertex projected into three dimensions.
    typedef VecMath::Vector<3, NUM> projected_vertex_type;

    FunctionHolder(ParameterMap parameters);
    FunctionHolder(std::shared_ptr< function_type > f);
    FunctionHolder(std::shared_ptr< function_type > f,
                   DefinitionRangeOfDimension<P> boundaries);

    virtual void Draw (UI::View *);

    void setDefinitionRange(double tmin, double tmax, double dt,
                            double umin, double umax, double du,
                            double vmin, double vmax, double dv);
    
    virtual unsigned getNumParameters();

protected:

    virtual void Initialize (void);

    const DefinitionRangeOfDimension<P> &getDefinitionRange() const;

  private:

    class Impl;
    std::unique_ptr<Impl> pImpl_;

};

namespace {
  static DisplayableClass displayable_class_function_holder(
    "FunctionHolder", "Functions evaluated on a grid", "Displayable"
  );
}

#endif // FUNCTIONHOLDER_H
