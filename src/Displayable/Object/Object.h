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

#if(!defined OBJECT_H)
#define OBJECT_H

#include "FunctionHolder.h"

#include "ParametricFunction.h"
#include "MultiDimensionalVector.h"

/// Generalized four-dimensional Object, described by vertexes and surfaces
/** An Object is a four-dimensional geometrical object which can not be
 *  described as a mathematical function from \f$ R^3 \f$ to \f$ R \f$ or from
 *  \f$ R^2 \f$ to \f$ R^4 \f$.
 *
 *  Instead it is described as a set of surfaces.
 *  \ingroup FunctionGroup
 *  @author Lene Preuss <lene.preuss@gmail.com>                         */
class Object: public VertexHolder<4, 1, double> {
    
public:

    Object (unsigned, unsigned);
    virtual ~Object () { }
    virtual void ReInit (double, double, double,
                         double, double, double,
                         double, double, double);
    virtual void calibrateColors();

    virtual void Draw (UI::View *);

    /// \see Function::getDefinitionSpaceDimensions()
    virtual unsigned getDefinitionSpaceDimensions() { return 0; }

protected:
    virtual void Initialize();

    /// the surfaces, stored as vectors of indeces to the points in X
    VecMath::MultiDimensionalVector<unsigned, 2> Surface;

    /// Set a vertex at a specified index
    void setX(unsigned i, const VecMath::Vector<4, double> &x);

    using VertexHolder<4, 1, double>::setX;

    void clearAndResizeX(unsigned size);
    
};

namespace {
  static DisplayableClass displayable_class_object(
    "Object", "Geometrical object", "Displayable"
  );
}

#endif
