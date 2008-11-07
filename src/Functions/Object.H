
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

#include "Function.H"
#include "Vector.H"

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
        /// one-dimensional array of unsigned, implemented as a std::vector
        typedef std::vector<unsigned> uintvec1D;
        /// two-dimensional array of unsigned, implemented as a nested vector
        typedef std::vector<uintvec1D> uintvec2D;

        Object (const QString &, unsigned, unsigned);
        virtual ~Object () { }
        virtual void ReInit (double, double, double,
                             double, double, double,
                             double, double, double);

        virtual void Transform (const VecMath::Rotation<4> &R,
                                const VecMath::Vector<4> &T);
        virtual void Project (double ScrW, double CamW, bool DepthCue4D);
        virtual void Draw (void);
        virtual VecMath::Vector<4> &operator () (double, double, double) {
            throw std::logic_error("Object::operator() should never be called");
        }

        /// \see Function::getDefinitionSpaceDimensions()
        virtual const unsigned getDefinitionSpaceDimensions() { return 0; }

    protected:
        virtual void Initialize();

        /// Set temporary storage for the function values
        void setX(const vec4vec1D &);

        vec4vec1D X;        ///< temporary storage for the function values
        vec4vec1D Xtrans;   ///< temp. storage for transformed function values
        vec3vec1D Xscr;     ///< temporary storage for projected function values

        /// the surfaces, stored as vectors of indeces to the points in X
        uintvec2D Surface;

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

/// A four-dimensional cube
/** \ingroup ObjectGroup                                                    */
class Hypercube: public Object {
public:
    Hypercube (): Object ("Hypercube", 16, 24) {
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
        out << "Hypercube (a = " << _a << ")" << std::ends;
        return out.str ();
    }
protected:
    virtual void Initialize();
    void DeclareSquare (unsigned, unsigned, unsigned, unsigned, unsigned);

    double _a;                  ///< Side length of the hypercube
    VecMath::Vector<4> _center; ///< Center of the hypercube
};

namespace {
    Function *createHypercube() { return new Hypercube(); }
    const bool registeredH = TheFunctionFactory::Instance().registerFunction("Hypercube", createHypercube);
}

///////////////////////////////////////////////////////////////////////////////

/// A four-dimensional Menger Sponge.
/** A Menger Sponge in three dimensions is a fractal produced by subdividing
 *  a cube and taking away parts of the cube which get subsequentally
 *  smaller. The \em level parameter controls how often this process is repeated,
 *  i.e. how many holes there are in the final object.
 *
 *  A four-dimensional Menger Sponge is created analogously from a hypercube.
 *
 *  The fractal can be further controlled by the \em distance parameter:
 *  \li \em distance = 0: Only the innermost cube is removed, resulting in a
 *      four-dimensional foam with connected body and disjoint holes.
 *  \li \em distance = 1: the innermost and the next to innermost cubes are
 *      removed, which results in a foam in three dimensions, but has holes in
 *      the four-dimensional structure.
 *  \li \em distance = 2: the holes reach the surface of the cube, resulting in
 *      a sponge structure - both the holes and the cubes ("curd") are
 *      connected.
 *  \li \em distance = 3: only the corners of the hypercube remain, resulting in
 *      dust - the "curd" is disjoint, the holes are connected.
 *  \ingroup ObjectGroup                                                    */
class Sponge: public Hypercube {
public:
    /// Sponge constructor
    /** @param _level hypersponge level
     *  @param _distance distance of subcubes to center to be counted as part of
     *                   the fractal
     *                   \li = 0: solid hypercube
     *                   \li = 1: foam
     *                   \li = 2: sponge
     *                   \li = 3: dust
     *                   \li >= 4: nothing
     *  @param _rad side_length/2
     *  @param _center center                                                 */
    Sponge (unsigned _level = 1, unsigned _distance = 2, double _rad = 0.8,
            VecMath::Vector<4> _center = VecMath::Vector<4>(0., 0.,0., 0.));
    virtual ~Sponge ();

    virtual void Transform (const VecMath::Rotation<4> &R,
                            const VecMath::Vector<4> &T);
    virtual void Project (double ScrW, double CamW, bool DepthCue4D);
    virtual void Draw (void);

    virtual void SetParameters(const ParameterMap &parms) {
        std::cerr << "Sponge::SetParameters(" << parms.print() << ")\n";
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "Level")
                    Level = unsigned(*i->second);
                if (i->second->getName() == "Distance")
                    distance = unsigned(*i->second);
                if (i->second->getName() == "Size")
                    rad = double(*i->second);
            }
#       else
            setParameter(parms, this->Phase, "Phase");
#       endif
        }

    /// Rebuild the Sponge if the parameters have changed
    virtual void ReInit (double, double, double,
                         double, double, double,
                         double, double, double) {
        List.clear();
        Object::ReInit(0,0,0,0,0,0,0,0,0);
    }

    /** @return A string with a description of the Hypersponge object         */
    virtual std::string description () {
        std::ostringstream out;
        out << "Sponge (level = " << Level << ")" << std::ends;
        return out.str ();
    }

protected:
    virtual void Initialize();
    virtual unsigned long MemRequired (unsigned);
    unsigned Level;                 ///< Level of the hypersponge

    /// List of sub-sponges (see Initialize())
    /** @todo Use smart pointers instead of a simple pointer-to-object        */
    std::vector<Hypercube *> List;

    int distance;                   ///< max. distance (see Initialize())
    double rad;                     ///< radius, more correctly size, of the sponge
    VecMath::Vector<4> center;      ///< center of the sponge
};

namespace {
    Function *createSponge() { return new Sponge(); }
    const bool registeredS = TheFunctionFactory::Instance().registerFunction("Sponge", createSponge);
}

///////////////////////////////////////////////////////////////////////////////

/// A four-dimensional pyramid, also known as hypersimplex
/** \ingroup ObjectGroup                                                    */
class Pyramid: public Object {
public:
    Pyramid (): Object ("Hyperpyramid", 5, 10) {
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
    const bool registeredP = TheFunctionFactory::Instance().registerFunction("Pyramid", createPyramid);
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
    const bool registeredG = TheFunctionFactory::Instance().registerFunction("Gasket", createGasket);
}

#endif
