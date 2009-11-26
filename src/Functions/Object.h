
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//      author:       helge preuss (scout@hyperspace-travel.de)
//      license:      GPL (see License.txt)


#if(!defined OBJECT_H)
#define OBJECT_H


#include <vector>
#include <sstream>
#include <string>

#include "Function.h"
#include "Vector.h"
#include "uintvec.h"

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
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class Object: public Function {
    public:

        Object (const QString &, unsigned, unsigned);
        virtual ~Object () { }
        virtual void ReInit (double, double, double,
                             double, double, double,
                             double, double, double);
        virtual void calibrateColors() const;

        virtual void Transform (const VecMath::Rotation<4> &R,
                                const VecMath::Vector<4> &T);
        virtual void Project (double ScrW, double CamW, bool DepthCue4D);
        virtual void Draw (void);
        virtual VecMath::Vector<4> &operator () (double, double, double) {
            throw std::logic_error("Object::operator() should never be called");
        }

        /// \see Function::getDefinitionSpaceDimensions()
        virtual unsigned getDefinitionSpaceDimensions() { return 0; }

    protected:
        virtual void Initialize();

        /// Set temporary storage for the function values
        void setX(const vec4vec1D &);

        vec4vec1D X;        ///< temporary storage for the function values
        vec4vec1D Xtrans;   ///< temp. storage for transformed function values
        vec3vec1D Xscr;     ///< temporary storage for projected function values

        /// the surfaces, stored as vectors of indeces to the points in X
        VecMath::uintvec<2> Surface;

        /** A pointless function, but it must be overridden to satisfy the
         *  Function interface. In an Object it is never called because the
         *  four-dimensional object is represented by a list of surfaces instead
         *  of a mathematical function.
         */
        virtual VecMath::Vector<4> &f (double, double, double) {
            throw std::logic_error("Object::f() should never be called");
        }
};


///////////////////////////////////////////////////////////////////////////////

#if USE_INT_INDICES
typedef VecMath::uintvec<2> surface_vec_type;
#else
template <unsigned D, unsigned N_vertex> class SurfaceType {

  public:
    typedef VecMath::Vector<D> vertex_type;
    typedef const vertex_type * vertex_ptr_type;

    SurfaceType() { for (unsigned i = 0; i < N_vertex; _vertices[i++] = 0) ; }
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
    
    const vertex_ptr_type &operator[](unsigned i) const { return _vertices[i]; }
    unsigned index(unsigned i) const { return _indices[i]; }

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
      
      vertex_ptr_type _vertices[N_vertex];
      unsigned _indices[N_vertex];
};

typedef std::vector< SurfaceType<4, 4> > surface_vec_type;
#endif
/// A four-dimensional cube
/** \ingroup ObjectGroup                                                    */
class Hypercube: public Object {
public:
    Hypercube (): Object ("Tesseract", 16, 24) {
        _a = 1;
        declareParameter("Size", 1.0);
        Initialize();
    }
    /// Construct a hypercube with a side length and a center
    Hypercube (double a,
               const VecMath::Vector<4> &_center = VecMath::Vector<4>(0., 0., 0., 0.));
    virtual ~Hypercube() { }

    virtual void SetParameters(const ParameterMap &parms) {
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "Size") _a = double(*i->second);
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
      virtual void Draw (void);
      
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
    Function *createHypercube() { return new Hypercube(); }
    const bool registeredH = TheFunctionFactory::Instance().registerFunction("Tesseract", createHypercube);
}

///////////////////////////////////////////////////////////////////////////////

/// A four-dimensional pyramid, also known as hypersimplex
/** \ingroup ObjectGroup                                                    */
class Pyramid: public Object {
public:
    Pyramid (): Object ("Pentachoron", 5, 10) {
        declareParameter("Size", 1.0);
    }
    Pyramid (double _a,
             const VecMath::Vector<4> &_Center = VecMath::Vector<4> (0., 0., 0., 0.));
    virtual ~Pyramid() { }

    virtual void SetParameters(const ParameterMap &parms) {
#       if 1
        for (ParameterMap::const_iterator i = parms.begin();
             i != parms.end(); ++i) {
                 if (i->second->getName() == "Size") a = double(*i->second);
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
    Function *createPyramid() { return new Pyramid(); }
    const bool registeredP =
            TheFunctionFactory::Instance().registerFunction("Pentachoron",
                                                            createPyramid);
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

        virtual void Transform (const VecMath::Rotation<4> &R,
                                const VecMath::Vector<4> &T);
        virtual void Project (double ScrW, double CamW, bool DepthCue4D);
        virtual void Draw (void);

        virtual void SetParameters(const ParameterMap &parms) {
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "Level")
                    Level = unsigned(*i->second);
                if (i->second->getName() == "Size")
                    rad = double(*i->second);
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
    Function *createGasket() { return new Gasket(); }
    const bool registeredG =
            TheFunctionFactory::Instance().registerFunction("Gasket", createGasket);
}

#endif
