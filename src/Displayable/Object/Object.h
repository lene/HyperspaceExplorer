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

#define USE_INT_INDICES 0

/// Artificial type to use in Typelists
struct EmptyType {};

/// Generalized four-dimensional Object, described by vertexes and surfaces
/** An Object is a four-dimensional geometrical object which can not be
 *  described as a mathematical function from \f$ R^3 \f$ to \f$ R \f$ or from
 *  \f$ R^2 \f$ to \f$ R^4 \f$.
 *
 *  Instead it is described as a set of surfaces.
 *  \ingroup FunctionGroup
 *  @author Helge Preuss <lene.preuss@gmail.com>                         */
class Object: public VertexHolder<4, 1, double> {
    
public:

    /// The numeric type that is used in all calculations.
    typedef double numeric_type;
    /// A vertex in \p N - space.
    typedef VecMath::Vector<4, double> vertex_type;
    /// A vertex projected into three dimensions.
    typedef VecMath::Vector<3, double> projected_vertex_type;

    Object (unsigned, unsigned);
    virtual ~Object () { }
    virtual void ReInit (double, double, double,
                         double, double, double,
                         double, double, double);
    virtual void calibrateColors() const;

    virtual void Transform (const VecMath::Rotation<4> &R,
                            const VecMath::Vector<4> &T,
                            const VecMath::Vector<4> &scale = 1.);
    virtual void Project (double ScrW, double CamW, bool DepthCue4D);
    virtual void Draw (UI::View *);
    virtual VecMath::Vector<4> &operator () (double, double, double) {
        throw std::logic_error("Object::operator() should never be called");
    }

    /// \see Function::getDefinitionSpaceDimensions()
    virtual unsigned getDefinitionSpaceDimensions() { return 0; }

    virtual void for_each_vertex(function_on_fourspace_vertex apply);
    virtual void for_each_vertex_transformed(function_on_fourspace_and_transformed_vertex apply);
    virtual void for_each_projected(function_on_projected_vertex apply);
    virtual void for_each_vertex_transformed_projected(function_on_fourspace_transformed_and_projected_vertex apply);

protected:
    virtual void Initialize();

    const VecMath::MultiDimensionalVector< vertex_type, 1 > &X() const;
    void setX(const vec4vec1D &);           ///< Set temporary storage for the function values
    void setX(const VecMath::MultiDimensionalVector< vertex_type, 1 > &);           ///< Set temporary storage for the function values
    void setX(int i, const vertex_type &x);
    void resizeX(unsigned size);
    void X_push_back(const vertex_type &x);
    const VecMath::MultiDimensionalVector< vertex_type, 1 > &Xtrans() const;
    void resizeXtrans(unsigned size);
    void setXtrans(const VecMath::MultiDimensionalVector< vertex_type, 1 > &);           ///< Set temporary storage for the function values
    const VecMath::MultiDimensionalVector< projected_vertex_type, 1 > &Xscr() const;
    void setXscr(const VecMath::MultiDimensionalVector< projected_vertex_type, 1 > &);           ///< Set temporary storage for the function values
    void resizeXscr(unsigned size);
    void setXscr(int i, const projected_vertex_type &x);

    /// the surfaces, stored as vectors of indeces to the points in X
    VecMath::MultiDimensionalVector<unsigned, 2> Surface;

    /** A pointless function, but it must be overridden to satisfy the
     *  Function interface. In an Object it is never called because the
     *  four-dimensional object is represented by a list of surfaces instead
     *  of a mathematical function.
     */
    virtual VecMath::Vector<4> &f (double, double, double) {
        throw std::logic_error("Object::f() should never be called");
    }

private:

    VecMath::MultiDimensionalVector< vertex_type, 1 > X_;        ///< temporary storage for the function values
    VecMath::MultiDimensionalVector< vertex_type, 1 > Xtrans_;   ///< temp. storage for transformed function values
    VecMath::MultiDimensionalVector< projected_vertex_type, 1 > Xscr_;     ///< temporary storage for projected function values
    
};

namespace {
  static DisplayableClass displayable_class_object(
    "Object", "Geometrical object", "Displayable"
  );
}

#endif
