//
// C++ Interface: RealFunction
//
// Description:
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef REAL_FUNCTION_H
#define REAL_FUNCTION_H

#include "Function.H"

/// \em RealBase provides a base class for functions which take three parameters
/** The \em RealBase interface provides abstract members for the evaluation of
 *  the function values on a three-dimensional grid.
 *
 *  abstract member:
 *      \li Vector &f (double, double);
 *
 *  member:
 *      \li operator () (double t, double u, double);
 *
 *  \todo Vector &normal (double, double, double); - or in base class?
 *
 *  \ingroup RealGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>                         */
class RealBase: public Function {
    public:
        /** type of the function used to generate values, optimized with a
         *  reference as return value                                         */
        typedef VecMath::Vector<4> &function_type(double, double, double);
        /// the real, raw type of the function used to generate values
        typedef VecMath::Vector<4> raw_function_type (double, double, double);

        RealBase() { }
        /// constructor
        RealBase(const QString &name,
                 double _tmin, double _tmax, double _dt,
                 double _umin, double _umax, double _du,
                 double _vmin, double _vmax, double _dv,
                 ParameterMap _parms = ParameterMap()):
                Function(name, _parms),
                tmin (_tmin), tmax (_tmax), dt (_dt),
                umin (_umin), umax (_umax), du (_du),
                vmin (_vmin), vmax (_vmax), dv (_dv),
                tsteps (unsigned ((tmax-tmin)/dt+1)),
                usteps (unsigned ((umax-umin)/du+1)),
                vsteps (unsigned ((vmax-vmin)/dv+1)) { }

    protected:
        /// number of steps in t
        unsigned &getTsteps() { return tsteps; }
        /// number of steps in t
        unsigned getTsteps() const { return tsteps > 0? tsteps: 1; }
        /// number of steps in u
        unsigned &getUsteps() { return usteps; }
        /// number of steps in u
        unsigned getUsteps() const { return usteps > 0? usteps: 1; }
        /// number of steps in v
        unsigned &getVsteps()  { return vsteps; }
        /// number of steps in v
        unsigned getVsteps() const { return vsteps > 0? vsteps: 1; }

        double &getTmin() { return tmin; }          ///< min. value of the first parameter, t
        double getTmin() const { return tmin; }     ///< min. value of the first parameter, t
        double &getTmax() { return tmax; }          ///< max. value of the first parameter, t
        double getTmax() const { return tmax; }     ///< max. value of the first parameter, t
        double &getDt() { return dt; }              ///< delta in t
        const double &getDt() const { return dt; }  ///< delta in t
        double &getUmin() { return umin; }          ///< min. value of the second parameter, u
        double getUmin() const { return umin; }     ///< min. value of the second parameter, u
        double &getUmax() { return umax; }          ///< max. value of the second parameter, u
        double getUmax() const { return umax; }     ///< max. value of the second parameter, u
        double &getDu() { return du; }              ///< delta in u
        const double &getDu() const { return du; }  ///< delta in u
        double &getVmin() { return vmin; }          ///< min. value of the third parameter, v
        double getVmin() const { return vmin; }     ///< min. value of the third parameter, v
        double &getVmax() { return vmax; }          ///< max. value of the third parameter, v
        double getVmax() const { return vmax; }     ///< max. value of the third parameter, v
        double &getDv() { return dv; }              ///< delta in v
        const double &getDv() const { return dv; }  ///< delta in v

        /// The mathematical function defining the Function object
        virtual VecMath::Vector<4> &f(double, double, double) = 0;
        /// Function evaluation operator for three parameters
        /** @param t first argument, e.g. x or t
         *  @param u second argument, e.g. y or u
         *  @param v third argument, e.g. z or v
         *  @return f(t, u, v)                                                */
        VecMath::Vector<4> &operator () (double t, double u, double v) {
            return f(t,u,v);
        }

        static double _min, ///< default value for all lower bounds
                      _max, ///< default value for all upper bounds
                      _d;   ///< default value for all stepsizes

    private:
        double tmin, ///< min. value of the first parameter, here called t
               tmax, ///< min. value of the first parameter, here called t
               dt,   ///< stepsize in first parameter
               umin, ///< min. value of the second parameter, here called u
               umax, ///< min. value of the second parameter, here called u
               du,   ///< stepsize in second parameter
               vmin, ///< min. value of the third parameter, here called v
               vmax, ///< min. value of the third parameter, here called v
               dv;   ///< stepsize in third parameter
        unsigned tsteps, ///< number of steps in t
                 usteps, ///< number of steps in u
                 vsteps; ///< number of steps in v
};

/// A RealFunction is a mathematical function  \f$ f: R^3 \rightarrow R \f$ .
/** The function \em f is evaluated on a 3-dimensional cartesian grid. The
 *  function value constitutes the fourth dimension of the Function object:
 *  \f$ \vec{x} = ( x, y, z, f(x, y, z) ) \f$.
 *
 *  The parent class Function provides the evaluation on the grid, together
 *  with methods to rotate and translate the grid in 4-space,  to project the
 *  transformed grid onto 3-space, and to draw the projected grid into an OpenGL
 *  display list.
 *
 *  \ingroup RealGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class RealFunction: public RealBase {
    public:
        RealFunction(const QString &name);
        RealFunction (const QString &name,
                      double _tmin, double _tmax, double _dt,
                      double _umin, double _umax, double _du,
                      double _vmin, double _vmax, double _dv,
                      ParameterMap _parms = ParameterMap());
        virtual ~RealFunction() { }

        virtual void Transform (const VecMath::Rotation<4> &R,
                                const VecMath::Vector<4> &T);
        virtual void Project (double ScrW, double CamW, bool DepthCue4D);
        virtual void Draw (void);

        virtual void ReInit(double _tmin, double _tmax, double _dt,
                            double _umin, double _umax, double _du,
                            double _vmin, double _vmax, double _dv);

        /// \see Function::getDefinitionSpaceDimensions()
        virtual const unsigned getDefinitionSpaceDimensions() { return 3; }

    protected:
        VecMath::Vector<4> &normal(double t, double u, double v);

        void DrawPlane (unsigned);
        void DrawStrip (unsigned, unsigned);
        void DrawCube (unsigned, unsigned, unsigned);

        virtual void Initialize (void);
        virtual void InitMem (void);

        vec4vec3D X,      ///< temporary storage for function values on grid
                  Xtrans; ///< temporary storage for transformed function values
        vec3vec3D Xscr;   ///< temporary storage for projected function values
        /// temporary storage for the value of the function at a given point
        VecMath::Vector<4> F;


};


/*******************************************************************************
 *
 *  classes which implement RealFunction::f (double, double, double) follow
 *  the descendants may also implement Function::df () and Function::normal (),
 *  but need not
 */

////////////////////////////////////////////////////////////////////////////////

/// A hypersphere.
/** Defining function is
    \f{eqnarray*} {
        F_0 & = & Radius*\sin(\psi)*\sin(\theta)*\cos(\phi)    \\
        F_1 & = & Radius*\sin(\psi)*\sin(\theta)*\sin(\phi)    \\
        F_2 & = & Radius*\sin(\psi)*\cos(\theta)               \\
        F_3 & = & Radius*\cos(\psi)
    \f}
 *  \ingroup RealGroup                                                    */
class Hypersphere: public RealFunction {
    public:
        Hypersphere(): RealFunction("Hypersphere"), _radius(1.) { }
        Hypersphere (double _tmin, double _tmax, double _dt,
                     double _umin, double _umax, double _du,
                     double _vmin, double _vmax, double _dv,
                     double _rad = 1);
        virtual ~Hypersphere() { }
        virtual void SetParameters(const ParameterMap &);

    protected:
        virtual function_type f;
        virtual function_type normal;

        double _radius;         ///< Radius of the hypersphere
};

namespace {
    Function *createHypersphere() { return new Hypersphere(); }
    const bool registeredR1 = TheFunctionFactory::Instance().registerFunction("Hypersphere", createHypersphere);
}

///////////////////////////////////////////////////////////////////////////////

/// A <a href="http://teamikaria.com/wiki/Rotope_42">ditorus</a>
/** A four-dimensional torus where there are three radii - one circling about
 *  the main axis, the second circling perpendicular to the first circle, and
 *  the third circling about the second circle, perpendicular to all other
 *  directions
 *  \ingroup PolarGroup                                                    */
class Torus1: public RealFunction {
    public:
        Torus1(): RealFunction("Torus1"), R(2.), r(1.), rho(0.5) { }
        Torus1 (double _tmin, double _tmax, double _dt,
                double _umin, double _umax, double _du,
                double _vmin, double _vmax, double _dv,
                double _R = 2, double _r = 1, double _rho = 0.5);
        virtual ~Torus1() { }
        virtual void SetParameters(const ParameterMap &parms) {
    //  parms["Radius"].value must be set!
#if 1
    for (ParameterMap::const_iterator i = parms.begin(); i != parms.end(); ++i) {
        if (i->second->getName() == "Major Radius") R = double(*i->second);
        if (i->second->getName() == "Minor Radius") r = double(*i->second);
        if (i->second->getName() == "Micro Radius") rho = double(*i->second);
    }
#else
    setParameter(parms, this->R, "Major Radius");
    setParameter(parms, this->r, "Minor Radius");
    setParameter(parms, this->rho, "Micro Radius");
#endif
}

    protected:
        virtual function_type f;

        double R;       ///< major radius of the torus
        double r;       ///< minor radius of the torus
        double rho;     ///< smallest radius of the torus
};

namespace {
    Function *createTorus1() { return new Torus1(); }
    const bool registeredR2 = TheFunctionFactory::Instance().registerFunction("Torus1", createTorus1);
}

///////////////////////////////////////////////////////////////////////////////

/// A <a href="http://teamikaria.com/wiki/Rotope_22">toraspherinder</a>
/** A four-dimensional torus where a sphere circles about a center point in a
 *  direction perpendicular to all directions making up the sphere
 *  \ingroup RealGroup                                                    */
class Torus2: public RealFunction {
    public:
        Torus2(): RealFunction("Torus2"), R(1.), r(0.5) { }
        Torus2 (double _tmin, double _tmax, double _dt,
                double _umin, double _umax, double _du,
                double _vmin, double _vmax, double _dv,
                double _R = 1, double _r = 0.5);
        virtual ~Torus2 () { }
        virtual void SetParameters(const ParameterMap &parms) {
            //  parms["Radius"].value must be set!
#if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "Major Radius")
                    R = double(*i->second);
                if (i->second->getName() == "Minor Radius")
                    r = double(*i->second);
            }
#else
            setParameter(parms, this->R, "Major Radius");
            setParameter(parms, this->r, "Minor Radius");
#endif
        }

    protected:
        virtual function_type f;

        double R;   ///< major radius of the torus
        double r;   ///< minor radius of the torus
};

namespace {
    Function *createTorus2() { return new Torus2(); }
    const bool registeredR3 = TheFunctionFactory::Instance().registerFunction("Torus2", createTorus2);
}

///////////////////////////////////////////////////////////////////////////////

/// an example function from \f$R^3 \rightarrow R\f$
/** \f{eqnarray*}{
        r^2      & = & x^2+y^2+z^2  \\
        f(x,y,z) & = & 1./(r^2+.25)
    \f}
 *  \ingroup RealGroup                                                    */
class Fr3r: public RealFunction {
    public:
        Fr3r(): RealFunction("Fr3r") { }
        Fr3r (double _tmin, double _tmax, double _dt,
              double _umin, double _umax, double _du,
              double _vmin, double _vmax, double _dv);
        virtual ~Fr3r() { }

    protected:
        virtual function_type f;
};

namespace {
    Function *createFr3r() { return new Fr3r(); }
    const bool registeredR4 = TheFunctionFactory::Instance().registerFunction("Fr3r", createFr3r);
}

///////////////////////////////////////////////////////////////////////////////

/// a function describing the gravitational potential of a spherical mass
/** \ingroup RealGroup                                                    */
class GravitationPotential: public RealFunction {
    public:
        GravitationPotential(): RealFunction("GravitationPotential"), M(1.), R(0.25) { }
        GravitationPotential (double _tmin, double _tmax, double _dt,
                              double _umin, double _umax, double _du,
                              double _vmin, double _vmax, double _dv,
                              double _M = 1, double _R = 0.25);
        virtual ~GravitationPotential () { }
        virtual void SetParameters(const ParameterMap &parms) {
#if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "M") M = double(*i->second);
                if (i->second->getName() == "R") R = double(*i->second);
            }
#else
            setParameter(parms, this->M, "M");
            setParameter(parms, this->R, "R");
#endif
        }

    protected:
        virtual function_type f;

        double M;   ///< Mass of the generating sphere(not really M, but M/R^3)
        double R;   ///< Radius of the generating sphere
};

namespace {
    Function *createGravitationPotential() { return new GravitationPotential(); }
    const bool registeredR5 = TheFunctionFactory::Instance().registerFunction("GravitationPotential", createGravitationPotential);
}

///////////////////////////////////////////////////////////////////////////////

/// \f$ f(x,y,z) = \sin (\pi*(x^2+y^2+z^2)) \f$
/** \ingroup RealGroup                                                    */
class Fr3rSin: public RealFunction {
    public:
        Fr3rSin(): RealFunction("Fr3rSin") { }
        Fr3rSin (double _tmin, double _tmax, double _dt,
                 double _umin, double _umax, double _du,
                 double _vmin, double _vmax, double _dv);
        virtual ~Fr3rSin () { }

    protected:
        virtual function_type f;
};

namespace {
    Function *createFr3rSin() { return new Fr3rSin(); }
    const bool registeredR6 = TheFunctionFactory::Instance().registerFunction("Fr3rSin", createFr3rSin);
}

///////////////////////////////////////////////////////////////////////////////

/// \f$ f(x,y,z) = \exp (x^2+y^2+z^2) \f$
/** \ingroup RealGroup                                                    */
class Fr3rExp: public RealFunction {
    public:
        Fr3rExp(): RealFunction("Fr3rExp") { }
        Fr3rExp (double _tmin, double _tmax, double _dt,
                 double _umin, double _umax, double _du,
                 double _vmin, double _vmax, double _dv);
        virtual ~Fr3rExp () { }

    protected:
        virtual function_type f;
};

namespace {
    Function *createFr3rExp() { return new Fr3rExp(); }
    const bool registeredR7 = TheFunctionFactory::Instance().registerFunction("Fr3rExp", createFr3rExp);
}

///////////////////////////////////////////////////////////////////////////////

/// A hypersphere as an example polar function
/** \ingroup PolarGroup                                                    */
class Polar: public RealFunction {
    public:
        Polar (double _tmin, double _tmax, double _dt,
               double _umin, double _umax, double _du,
               double _vmin, double _vmax, double _dv);
        virtual ~Polar() { }

    protected:
        virtual function_type f;
};

///////////////////////////////////////////////////////////////////////////////

/// \f$ r(\psi, \theta, \phi) = |\sin (Phase*\pi*\psi*\theta*\phi)| \f$
/** \ingroup PolarGroup                                                    */
class PolarSin: public RealFunction {
    public:
        PolarSin(): RealFunction("PolarSin"), Phase(2.) { }
        PolarSin (double _tmin, double _tmax, double _dt,
                  double _umin, double _umax, double _du,
                  double _vmin, double _vmax, double _dv,
                  double _phase = 2);
        virtual ~PolarSin () { }

        virtual void SetParameters(const ParameterMap &parms) {
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "Phase") Phase = double(*i->second);
            }
#       else
            setParameter(parms, this->Phase, "Phase");
#       endif
        }

    protected:
        virtual function_type f;
        double Phase;               ///< phase
};

namespace {
    Function *createPolarSin() { return new PolarSin(); }
    const bool registeredR8 = TheFunctionFactory::Instance().registerFunction("PolarSin", createPolarSin);
}

///////////////////////////////////////////////////////////////////////////////

/// \f$ r = \sin(\pi/3.*(\psi+\theta+\phi)) \f$
/** \ingroup PolarGroup                                                    */
class PolarSin2: public RealFunction {
    public:
        PolarSin2(): RealFunction("PolarSin2") { }
        PolarSin2 (double _tmin, double _tmax, double _dt,
                   double _umin, double _umax, double _du,
                   double _vmin, double _vmax, double _dv);
        virtual ~PolarSin2 () { }

    protected:
        virtual function_type f;
};

namespace {
    Function *createPolarSin2() { return new PolarSin2(); }
    const bool registeredR9 = TheFunctionFactory::Instance().registerFunction("PolarSin2", createPolarSin2);
}

///////////////////////////////////////////////////////////////////////////////

/// \f$ r = \sqrt{\psi^2+\theta^2+\phi^2} \f$
/** \ingroup PolarGroup                                                    */
class PolarR: public RealFunction {
    public:
        PolarR(): RealFunction("PolarR"), Phase(2.) { }
        PolarR (double _tmin, double _tmax, double _dt,
                double _umin, double _umax, double _du,
                double _vmin, double _vmax, double _dv,
                double _phase = 2);
        virtual ~PolarR () { }

        virtual void SetParameters(const ParameterMap &parms) {
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "Phase") Phase = double(*i->second);
            }
#       else
            setParameter(parms, this->Phase, "Phase");
#       endif
        }

    protected:
        virtual function_type f;
        double Phase;               ///< phase
};

namespace {
    Function *createPolarR() { return new PolarR(); }
    const bool registeredR10 = TheFunctionFactory::Instance().registerFunction("PolarR", createPolarR);
}

#endif
