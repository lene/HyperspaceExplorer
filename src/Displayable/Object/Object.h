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


#include <vector>
#include <sstream>
#include <string>

#include "ParameterMap.h"
#include "Displayable.h"
#include "Vector.h"
#include "MultiDimensionalVector.h"

#include "Vector.impl.h"

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
class Object: public Displayable {
    
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
        vec4vec1D X_as_old_format() const;
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

    vec4vec1D X_;        ///< temporary storage for the function values
    vec4vec1D Xtrans_;   ///< temp. storage for transformed function values
    vec3vec1D Xscr_;     ///< temporary storage for projected function values
    
    mutable VecMath::MultiDimensionalVector< vertex_type, 1 > X_in_new_format_;
    mutable VecMath::MultiDimensionalVector< vertex_type, 1 > Xtrans_in_new_format_;
    mutable VecMath::MultiDimensionalVector< projected_vertex_type, 1 > Xscr_in_new_format_;
    
};

namespace {
  static DisplayableClass displayable_class_object(
    "Object", "Geometrical object", "Displayable"
  );
}


///////////////////////////////////////////////////////////////////////////////

#include "SurfaceType.h"

/// A four-dimensional cube
/** \ingroup ObjectGroup                                                    */
class Hypercube: public Object {
public:
    /// Construct a hypercube with a side length and a center
    Hypercube (double a = 1.,
               const VecMath::Vector<4> &_center = VecMath::Vector<4>(0., 0., 0., 0.));
    virtual ~Hypercube() { }

    virtual std::string getFunctionName() const { return "Tesseract"; }

    virtual void SetParameters(const ParameterMap &parms) {
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "Size") _a = i->second->toDouble();
            }
#       else
            setParameter(parms, this->a, "Size");
#       endif
    }

    /// \return A string carrying a description of the Function
    virtual std::string description () {
        std::ostringstream out;
        out << "Tesseract of edge length " << _a << std::ends;
        return out.str ();
    }
#   if !USE_INT_INDICES
      /// reimplement Draw() to make use of the stored vertices (instead of indices)
      virtual void Draw (UI::View *view);

#   endif
  protected:
    virtual void Initialize();
    void DeclareSquare (unsigned, unsigned, unsigned, unsigned, unsigned, unsigned = 0);

    double _a;                  ///< Side length of the hypercube
    VecMath::Vector<4> _center; ///< Center of the hypercube

    static constexpr unsigned num_vertices = 16;
    static constexpr unsigned num_faces = 24;

#   if !USE_INT_INDICES
      surface_vec_type Surface;
#   endif
};

namespace {
    Displayable *createHypercube() { return new Hypercube; }
    const bool registeredH = TheFunctionFactory::Instance().registerFunction(createHypercube, "Object");
}

///////////////////////////////////////////////////////////////////////////////

/// A four-dimensional pyramid, also known as hypersimplex
/** \ingroup ObjectGroup                                                    */
class Pyramid: public Object {
public:
    Pyramid (): Object (5, 10) {
        declareParameter("Size", 1.0);
    }
    Pyramid (double _a,
             const VecMath::Vector<4> &_Center = VecMath::Vector<4> (0., 0., 0., 0.));
    virtual ~Pyramid() { }

    virtual std::string getFunctionName() const { return "Pentachoron"; }

    virtual void SetParameters(const ParameterMap &parms) {
#       if 1
        for (ParameterMap::const_iterator i = parms.begin();
             i != parms.end(); ++i) {
                 if (i->second->getName() == "Size") a = i->second->toDouble();
             }
#       else
             setParameter(parms, this->a, "Size");
#       endif
    }

protected:
    virtual void Initialize();
    void DeclareTriangle (unsigned, unsigned, unsigned, unsigned);

    VecMath::Vector<4> center;  ///< location
    double a;                   ///< size
};

namespace {
    Displayable *createPyramid() { return new Pyramid(); }
    const bool registeredP =
            TheFunctionFactory::Instance().registerFunction(createPyramid, "Object");
}

///////////////////////////////////////////////////////////////////////////////

/// A four-dimensional version of the Sierpinski Gasket.
/** This object is similar to the Menger Sponge, but it uses a Hypersimplex as
 *  generator.
 *
 *  It lacks the \p distance parameter, because there is only one way
 *  to generate a Sierpinski Gasket of level \p n. Otherwise it is analogous to
 *  the Menger Sponge fractal.
 *  \ingroup ObjectGroup                                                      */
class Gasket: public Pyramid {
    public:
        /// Create a gasket with a level, size and center
        Gasket (unsigned level = 1, double rad = 1,
                VecMath::Vector<4> Center = VecMath::Vector<4> (0., 0.,0., 0.));
        virtual ~Gasket() { }

        virtual std::string getFunctionName() const { return "4D Sierpinski Gasket"; }

        virtual void Transform (const VecMath::Rotation<4> &R,
                                const VecMath::Vector<4> &T,
                                const VecMath::Vector<4> &scale);
        virtual void Project (double ScrW, double CamW, bool DepthCue4D);
        virtual void Draw (UI::View *view);

        virtual void SetParameters(const ParameterMap &parms) {
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "Level")
                    Level = i->second->toUnsigned();
                if (i->second->getName() == "Size")
                    rad = i->second->toDouble();
            }
#       else
            setParameter(parms, this->Phase, "Phase");
#       endif
        }

        virtual void ReInit (double, double, double,
                             double, double, double,
                             double, double, double) {
            List.clear();
            Object::ReInit(0,0,0,0,0,0,0,0,0);
        }

    protected:
        virtual void Initialize();
        virtual unsigned long MemRequired (void);
        unsigned Level;                 ///< Recursion depth creating the gasket
        std::vector<Pyramid *> List;    ///< List of sub-gaskets
        double rad;                     ///< Scale of the gasket
        VecMath::Vector<4> center;
};

namespace {
    Displayable *createGasket() { return new Gasket(); }
    const bool registeredG =
            TheFunctionFactory::Instance().registerFunction(createGasket, "Object");
}

#endif
