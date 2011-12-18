/* 
 * File:   ObjectImplementations.h
 * Author: lene
 *
 * Created on December 18, 2011, 5:43 PM
 */

#ifndef OBJECTIMPLEMENTATIONS_H
#define	OBJECTIMPLEMENTATIONS_H

#include "Object.h"
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


#endif	/* OBJECTIMPLEMENTATIONS_H */

