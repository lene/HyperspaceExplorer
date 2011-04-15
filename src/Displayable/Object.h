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

        Object (unsigned, unsigned);
        virtual ~Object () { }
        virtual void ReInit (double, double, double,
                             double, double, double,
                             double, double, double);
        virtual void calibrateColors() const;

        virtual void Transform (const VecMath::Rotation<4> &R,
                                const VecMath::Vector<4> &T);
        virtual void Project (double ScrW, double CamW, bool DepthCue4D);
        virtual void Draw (UI::View *view);
        virtual VecMath::Vector<4> &operator () (double, double, double) {
            throw std::logic_error("Object::operator() should never be called");
        }

        /// \see Function::getDefinitionSpaceDimensions()
        virtual unsigned getDefinitionSpaceDimensions() { return 0; }

        virtual void for_each_vertex(function_on_fourspace_vertex apply);
        virtual void for_each_projected(function_on_projected_vertex apply);

    protected:
        virtual void Initialize();

        /// Set temporary storage for the function values
        void setX(const vec4vec1D &);

        vec4vec1D X;        ///< temporary storage for the function values
        vec4vec1D Xtrans;   ///< temp. storage for transformed function values
        vec3vec1D Xscr;     ///< temporary storage for projected function values

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
};

namespace {
  static DisplayableClass displayable_class_object(
    "Object", "Geometrical object", "Displayable"
  );
}


///////////////////////////////////////////////////////////////////////////////

#include "Util.h"

#if USE_INT_INDICES
typedef VecMath::uintvec<2> surface_vec_type;
#else
/// Defines a surface element in \p D -space.
/**
 *  \tparam D Dimension of vector space the surface is defined in.
 *  \tparam N_vertex Number of vertices per surface element / polygon.
 */
template <unsigned D, unsigned N_vertex> class SurfaceType {

  public:

    /// The type of the \p D -dimensional vertices.
    typedef VecMath::Vector<D> vertex_type;
    /// Pointer to vertex_type.
    typedef const vertex_type * vertex_ptr_type;

    /// Construct an empty SurfaceType.
    SurfaceType() { for (unsigned i = 0; i < N_vertex; _vertices[i++] = 0) ; }

    /// Construct a SurfaceType with a vertex array and three vertices.
    SurfaceType(const std::vector<vertex_type> &original_container,
                const vertex_type &v0, const vertex_type &v1,
                const vertex_type &v2) {
      _vertices[0] = &v0; _indices[0] = index_of(v0, original_container);
      _vertices[1] = &v1; _indices[1] = index_of(v1, original_container);
      _vertices[2] = &v2; _indices[2] = index_of(v2, original_container);
      for (unsigned i = 3; i < N_vertex; ++i) {
        _vertices[i] = 0;
        _indices[i] = 0;
      }
    }

    /// Construct a SurfaceType with a vertex array and four vertices.
    SurfaceType(const std::vector<vertex_type> &original_container,
                const vertex_type &v0, const vertex_type &v1,
                const vertex_type &v2, const vertex_type &v3) {
      _vertices[0] = &v0; _indices[0] = index_of(v0, original_container);
      _vertices[1] = &v1; _indices[1] = index_of(v1, original_container);
      _vertices[2] = &v2; _indices[2] = index_of(v2, original_container);
      _vertices[3] = &v3; _indices[3] = index_of(v3, original_container);
      for (unsigned i = 4; i < N_vertex; ++i) {
        _vertices[i] = 0;
        _indices[i] = 0;
      }
    }

    /// Returns the \p i -th vertex.
    const vertex_ptr_type &operator[](unsigned i) const { return _vertices[i]; }

    /// Returns the \p i -th index into the vertices array.
    unsigned index(unsigned i) const { return _indices[i]; }

    /// Preliminary version, only for N_vertex = 4
    bool operator==(const SurfaceType<D, 4> &other) const {
      if (N_vertex != 4) return false;
      if (!Util::isPermutation(
          _indices[0], _indices[1], _indices[2], _indices[3],
          other._indices[0], other._indices[1], other._indices[2], other._indices[3])) {
        return false;
      }
      return (_vertices[0] == other._vertices[0] &&
              _vertices[1] == other._vertices[1] &&
              _vertices[2] == other._vertices[2] &&
              _vertices[3] == other._vertices[3]);
    }

    /// Debugging output
    void print() {
      for (unsigned i = 0; i < N_vertex; ++i)
        std::cerr << _indices[i] << ": " << *(_vertices[i]) << " ";
      std::cerr << std::endl;
    }

    private:
      /// a version of std::find() that returns an index instead of an iterator
      static unsigned index_of(const vertex_type &x,
                               const std::vector<vertex_type> &original_container) {
        // assuming that more surfaces have vertices that have just been added
        // to the end of original_container
        for (int i = original_container.size()-1; i >= 0; --i) {
          if (original_container[i] == x) return i;
        }
        throw std::logic_error("SurfaceType::index_of(): Tried to find the index of a vertex that was not in the container");
      }

      /// Array of vertices the Surface consists of
      /** \todo why not a vector or something?
       */
      vertex_ptr_type _vertices[N_vertex];

      /// Array of indices pointing into _vertices.
      /** \todo why not a vector or something?
       */
      unsigned _indices[N_vertex];
};

typedef std::vector< SurfaceType<4, 4> > surface_vec_type;
#endif
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
                                const VecMath::Vector<4> &T);
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