/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
    Copyright (C) 2008  Lene Preuss <lene.preuss@gmail.com>

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
    (Seriously, has anyone ever done this?)

*/
#ifndef REAL_FUNCTION_H
#define REAL_FUNCTION_H

#include "Function.h"

#include "ParametricFunction.h"
#include "FunctionValueGrid.h"
#include "NestedVector.h"

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
 *  \author Lene Preuss <lene.preuss@gmail.com>                         */
class RealBase: public Function {
    public:
        /** type of the function used to generate values, optimized with a
         *  reference as return value                                         */
        typedef VecMath::Vector<4> &function_type(double, double, double);
        /// the real, raw type of the function used to generate values
        typedef VecMath::Vector<4> raw_function_type (double, double, double);

        RealBase(): Function() { }
        /// constructor
        RealBase(double tmin, double tmax, double dt,
                 double umin, double umax, double du,
                 double vmin, double vmax, double dv,
                 ParameterMap _parms = ParameterMap()):
                Function(_parms),
                _tmin (tmin), _tmax (tmax), _dt (dt),
                _umin (umin), _umax (umax), _du (du),
                _vmin (vmin), _vmax (vmax), _dv (dv),
                _tsteps (unsigned ((tmax-tmin)/dt+1)),
                _usteps (unsigned ((umax-umin)/du+1)),
                _vsteps (unsigned ((vmax-vmin)/dv+1)) { }

    protected:
        /// number of steps in t
        unsigned &getTsteps() { return _tsteps; }
        /// number of steps in t
        unsigned getTsteps() const { return _tsteps > 0? _tsteps: 1; }
        /// number of steps in u
        unsigned &getUsteps() { return _usteps; }
        /// number of steps in u
        unsigned getUsteps() const { return _usteps > 0? _usteps: 1; }
        /// number of steps in v
        unsigned &getVsteps()  { return _vsteps; }
        /// number of steps in v
        unsigned getVsteps() const { return _vsteps > 0? _vsteps: 1; }

        double &getTmin() { return _tmin; }          ///< min. value of the first parameter, t
        double getTmin() const { return _tmin; }     ///< min. value of the first parameter, t
        double &getTmax() { return _tmax; }          ///< max. value of the first parameter, t
        double getTmax() const { return _tmax; }     ///< max. value of the first parameter, t
        double &getDt() { return _dt; }              ///< delta in t
        const double &getDt() const { return _dt; }  ///< delta in t
        double &getUmin() { return _umin; }          ///< min. value of the second parameter, u
        double getUmin() const { return _umin; }     ///< min. value of the second parameter, u
        double &getUmax() { return _umax; }          ///< max. value of the second parameter, u
        double getUmax() const { return _umax; }     ///< max. value of the second parameter, u
        double &getDu() { return _du; }              ///< delta in u
        const double &getDu() const { return _du; }  ///< delta in u
        double &getVmin() { return _vmin; }          ///< min. value of the third parameter, v
        double getVmin() const { return _vmin; }     ///< min. value of the third parameter, v
        double &getVmax() { return _vmax; }          ///< max. value of the third parameter, v
        double getVmax() const { return _vmax; }     ///< max. value of the third parameter, v
        double &getDv() { return _dv; }              ///< delta in v
        const double &getDv() const { return _dv; }  ///< delta in v

        static double _min, ///< default value for all lower bounds
                      _max, ///< default value for all upper bounds
                      _d;   ///< default value for all stepsizes

    private:
        double _tmin, ///< min. value of the first parameter, here called t
               _tmax, ///< min. value of the first parameter, here called t
               _dt,   ///< stepsize in first parameter
               _umin, ///< min. value of the second parameter, here called u
               _umax, ///< min. value of the second parameter, here called u
               _du,   ///< stepsize in second parameter
               _vmin, ///< min. value of the third parameter, here called v
               _vmax, ///< min. value of the third parameter, here called v
               _dv;   ///< stepsize in third parameter
        unsigned _tsteps, ///< number of steps in t
                 _usteps, ///< number of steps in u
                 _vsteps; ///< number of steps in v
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
 *  @author Lene Preuss <lene.preuss@gmail.com>                         */
class RealFunction: public RealBase {
  public:
    RealFunction();
    RealFunction(double tmin, double tmax, double dt,
                 double umin, double umax, double du,
                 double vmin, double vmax, double dv,
                 ParameterMap _parms = ParameterMap());
    virtual ~RealFunction() { }

    virtual void Transform (const VecMath::Rotation<4> &R,
                            const VecMath::Vector<4> &T);
    virtual void Project (double ScrW, double CamW, bool DepthCue4D);
    virtual void Draw (void);

    virtual void ReInit(double tmin, double tmax, double dt,
                        double umin, double umax, double du,
                        double vmin, double vmax, double dv);

    /// Called by the ColorManager after setting the Function on the CM
    virtual void calibrateColors() const;

    /// \see Function::getDefinitionSpaceDimensions()
    virtual unsigned getDefinitionSpaceDimensions() { return 3; }

    /// Function evaluation operator for three parameters
    /** @param t first argument, e.g. x or t
     *  @param u second argument, e.g. y or u
     *  @param v third argument, e.g. z or v
     *  @return f(t, u, v)                                                */
    VecMath::Vector<4> &operator () (double t, double u, double v) {
        static VecMath::Vector<4> F;
        F = _function->f(VecMath::Vector<3>(t, u, v));
        return F;
    }

  protected:

    VecMath::Vector<4> &normal(double t, double u, double v);

    void DrawPlane (unsigned);
    void DrawStrip (unsigned, unsigned);
    void DrawCube (unsigned, unsigned, unsigned);

    virtual void Initialize (void);

    const VecMath::NestedVector< VecMath::Vector<4>, 3 > &X() const;
    const VecMath::NestedVector< VecMath::Vector<4>, 3 > &Xtrans() const;
    const VecMath::NestedVector< VecMath::Vector<3>, 3 > &Xscr() const;

    std::tr1::shared_ptr< ParametricFunction<4, 3> > _function;

  private:

    void setDepthCueColors(double Wmax, double Wmin);

    void setBoundariesAndStepwidth(double tmin, double tmax, double dt,
                                   double umin, double umax, double du,
                                   double vmin, double vmax, double dv);

    std::pair<double, double> findExtremesInW() const;

    FunctionValueGrid<4, 3> _X;
    FunctionValueGrid<4, 3>::value_storage_type _Xtrans;
    VecMath::NestedVector< VecMath::Vector<3>, 3 > _Xscr;

};


////////////////////////////////////////////////////////////////////////////////

/// A hypersphere.
/** Defining function is
    \f{eqnarray*} {
        F_0 & = & Radius*\sin \psi*\sin \theta*\cos \phi   \\
        F_1 & = & Radius*\sin \psi*\sin \theta*\sin \phi   \\
        F_2 & = & Radius*\sin \psi*\cos \theta             \\
        F_3 & = & Radius*\cos \psi
    \f}
 *  \ingroup RealGroup                                                    */
class Hypersphere: public RealFunction {

  public:

    Hypersphere(): RealFunction(), _radius(1.) { }
    Hypersphere (double _tmin, double _tmax, double _dt,
                 double _umin, double _umax, double _du,
                 double _vmin, double _vmax, double _dv,
                 double _rad = 1);
    virtual ~Hypersphere() { }
    virtual void SetParameters(const ParameterMap &);
    virtual std::string getFunctionName() const { return "Hypersphere"; }

  protected:

    class DefiningFunction: public ParametricFunction<4, 3> {

      public:

        DefiningFunction(Hypersphere *parent): _parent(parent) { }
        virtual return_type f(const argument_type &x);

      private:

        /// Not a smart pointer because it's initialized to \c this and mustn't be deleted
        Hypersphere* _parent;

    };

    virtual function_type normal;

    double _radius;         ///< Radius of the hypersphere

};

namespace {
    Function *createHypersphere() { return new Hypersphere(); }
    const bool registeredR1 = TheFunctionFactory::Instance().registerFunction(createHypersphere);
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
    Torus1(): RealFunction(), _R(2.), _r(1.), _rho(0.5) { }
    Torus1 (double tmin, double tmax, double dt,
            double umin, double umax, double du,
            double vmin, double vmax, double dv,
            double R = 2, double r = 1, double rho = 0.5);
    virtual ~Torus1() { }

    virtual std::string getFunctionName() const { return "Ditorus"; }

    virtual void SetParameters(const ParameterMap &parms) {
      //  parms["Radius"].value must be set!
#     if 1
      for (ParameterMap::const_iterator i = parms.begin(); i != parms.end(); ++i) {
        if (i->second->getName() == "Major Radius") _R = i->second->toDouble();
        if (i->second->getName() == "Minor Radius") _r = i->second->toDouble();
        if (i->second->getName() == "Micro Radius") _rho = i->second->toDouble();
      }
#     else
        setParameter(parms, this->_R, "Major Radius");
        setParameter(parms, this->_r, "Minor Radius");
        setParameter(parms, this->_rho, "Micro Radius");
#     endif
    }

  protected:

    class DefiningFunction: public ParametricFunction<4, 3> {

      public:

        DefiningFunction(Torus1 *parent): _parent(parent) { }
        virtual return_type f(const argument_type &x);

      private:

        /// Not a smart pointer because it's initialized to \c this and mustn't be deleted
        Torus1* _parent;

    };

    double _R;       ///< major radius of the torus
    double _r;       ///< minor radius of the torus
    double _rho;     ///< smallest radius of the torus
};

namespace {
    Function *createTorus1() { return new Torus1(); }
    const bool registeredR2 = TheFunctionFactory::Instance().registerFunction(createTorus1);
}

///////////////////////////////////////////////////////////////////////////////

/// A <a href="http://teamikaria.com/wiki/Rotope_22">toraspherinder</a>
/** A four-dimensional torus where a sphere circles about a center point in a
 *  direction perpendicular to all directions making up the sphere
 *  \ingroup RealGroup                                                    */
class Torus2: public RealFunction {
    public:
        Torus2(): RealFunction(), _R(1.), _r(0.5) { }
        Torus2 (double tmin, double tmax, double dt,
                double umin, double umax, double du,
                double vmin, double vmax, double dv,
                double R = 1, double r = 0.5);
        virtual ~Torus2 () { }

        virtual std::string getFunctionName() const { return "Toraspherinder"; }

        virtual void SetParameters(const ParameterMap &parms) {
            //  parms["Radius"].value must be set!
#if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "Major Radius")
                    _R = i->second->toDouble();
                if (i->second->getName() == "Minor Radius")
                    _r = i->second->toDouble();
            }
#else
            setParameter(parms, this->_R, "Major Radius");
            setParameter(parms, this->_r, "Minor Radius");
#endif
        }

  protected:

    class DefiningFunction: public ParametricFunction<4, 3> {

      public:

        DefiningFunction(Torus2 *parent): _parent(parent) { }
        virtual return_type f(const argument_type &x);

      private:

        /// Not a smart pointer because it's initialized to \c this and mustn't be deleted
        Torus2* _parent;

    };

    double _R;   ///< major radius of the torus
    double _r;   ///< minor radius of the torus
};

namespace {
    Function *createTorus2() { return new Torus2(); }
    const bool registeredR3 = TheFunctionFactory::Instance().registerFunction(createTorus2);
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
        Fr3r(): RealFunction() { }
        Fr3r (double tmin, double tmax, double dt,
              double umin, double umax, double du,
              double vmin, double vmax, double dv);
        virtual ~Fr3r() { }

        virtual std::string getFunctionName() const { return "1/(r�+1)"; }

    protected:
    class DefiningFunction: public ParametricFunction<4, 3> {

      public:

        DefiningFunction(Fr3r *parent): _parent(parent) { }
        virtual return_type f(const argument_type &x);

      private:

        /// Not a smart pointer because it's initialized to \c this and mustn't be deleted
        Fr3r* _parent;

    };
};

namespace {
    Function *createFr3r() { return new Fr3r(); }
    const bool registeredR4 = TheFunctionFactory::Instance().registerFunction(createFr3r);
}

///////////////////////////////////////////////////////////////////////////////

/// a function describing the gravitational potential of a spherical mass
/** \ingroup RealGroup                                                    */
class GravitationPotential: public RealFunction {

  public:

    GravitationPotential(): RealFunction(), _M(1.), _R(0.25) { }

    GravitationPotential (double tmin, double tmax, double dt,
                          double umin, double umax, double du,
                          double vmin, double vmax, double dv,
                          double M = 1, double R = 0.25);
    virtual ~GravitationPotential () { }

    virtual std::string getFunctionName() const { return "Gravitation Potential"; }

    virtual void SetParameters(const ParameterMap &parms) {
#if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "M") _M = i->second->toDouble();
                if (i->second->getName() == "R") _R = i->second->toDouble();
            }
#else
            setParameter(parms, this->_M, "M");
            setParameter(parms, this->_R, "R");
#endif
        }

    protected:

    class DefiningFunction: public ParametricFunction<4, 3> {

      public:

        DefiningFunction(GravitationPotential *parent): _parent(parent) { }
        virtual return_type f(const argument_type &x);

      private:

        /// Not a smart pointer because it's initialized to \c this and mustn't be deleted
        GravitationPotential* _parent;

    };

    double _M;   ///< Mass of the generating sphere(not really M, but M/R^3)
    double _R;   ///< Radius of the generating sphere
};

namespace {
    Function *createGravitationPotential() { return new GravitationPotential(); }
    const bool registeredR5 = TheFunctionFactory::Instance().registerFunction(createGravitationPotential);
}

///////////////////////////////////////////////////////////////////////////////

/// \f$ f(x,y,z) = \sin (\pi*(x^2+y^2+z^2)) \f$
/** \ingroup RealGroup                                                    */
class Fr3rSin: public RealFunction {
    public:
        Fr3rSin(): RealFunction() { }
        Fr3rSin (double tmin, double tmax, double dt,
                 double umin, double umax, double du,
                 double vmin, double vmax, double dv);
        virtual ~Fr3rSin () { }

        virtual std::string getFunctionName() const { return "sin (r�)"; }

    protected:
    class DefiningFunction: public ParametricFunction<4, 3> {

      public:

        DefiningFunction(Fr3rSin *parent): _parent(parent) { }
        virtual return_type f(const argument_type &x);

      private:

        /// Not a smart pointer because it's initialized to \c this and mustn't be deleted
        Fr3rSin* _parent;

    };
};

namespace {
    Function *createFr3rSin() { return new Fr3rSin(); }
    const bool registeredR6 = TheFunctionFactory::Instance().registerFunction(createFr3rSin);
}

///////////////////////////////////////////////////////////////////////////////

/// \f$ f(x,y,z) = \exp (x^2+y^2+z^2) \f$
/** \ingroup RealGroup                                                    */
class Fr3rExp: public RealFunction {
    public:
        Fr3rExp(): RealFunction() { }
        Fr3rExp (double tmin, double tmax, double dt,
                 double umin, double umax, double du,
                 double vmin, double vmax, double dv);
        virtual ~Fr3rExp () { }

        virtual std::string getFunctionName() const { return "exp (r�)"; }

    protected:
    class DefiningFunction: public ParametricFunction<4, 3> {

      public:

        DefiningFunction(Fr3rExp *parent): _parent(parent) { }
        virtual return_type f(const argument_type &x);

      private:

        /// Not a smart pointer because it's initialized to \c this and mustn't be deleted
        Fr3rExp* _parent;

    };
};

namespace {
    Function *createFr3rExp() { return new Fr3rExp(); }
    const bool registeredR7 = TheFunctionFactory::Instance().registerFunction(createFr3rExp);
}

///////////////////////////////////////////////////////////////////////////////

/// A hypersphere as an example polar function
/** \ingroup PolarGroup                                                    */
class Polar: public RealFunction {
    public:
        Polar (double tmin, double tmax, double dt,
               double umin, double umax, double du,
               double vmin, double vmax, double dv);
        virtual ~Polar() { }

    protected:
    class DefiningFunction: public ParametricFunction<4, 3> {

      public:

        DefiningFunction(Polar *parent): _parent(parent) { }
        virtual return_type f(const argument_type &x);

      private:

        /// Not a smart pointer because it's initialized to \c this and mustn't be deleted
        Polar* _parent;

    };
};

///////////////////////////////////////////////////////////////////////////////

/// \f$ r(\psi, \theta, \phi) = |\sin (_phase*\pi*\psi*\theta*\phi)| \f$
/** \ingroup PolarGroup                                                    */
class PolarSin: public RealFunction {
    public:
        PolarSin(): RealFunction(), _phase(2.) { }
        PolarSin (double tmin, double tmax, double dt,
                  double umin, double umax, double du,
                  double vmin, double vmax, double dv,
                  double phase = 2);
        virtual ~PolarSin () { }

        virtual std::string getFunctionName() const { return "Polar: r = 1/2+sin (Phase*pi*t*u*v)"; }

        virtual void SetParameters(const ParameterMap &parms) {
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "Phase") _phase = i->second->toDouble();
            }
#       else
            setParameter(parms, this->_phase, "Phase");
#       endif
        }

    protected:
    class DefiningFunction: public ParametricFunction<4, 3> {

      public:

        DefiningFunction(PolarSin *parent): _parent(parent) { }
        virtual return_type f(const argument_type &x);

      private:

        /// Not a smart pointer because it's initialized to \c this and mustn't be deleted
        PolarSin* _parent;

    };

    double _phase;               ///< phase
};

namespace {
    Function *createPolarSin() { return new PolarSin(); }
    const bool registeredR8 = TheFunctionFactory::Instance().registerFunction(createPolarSin);
}

///////////////////////////////////////////////////////////////////////////////

/// \f$ r = \sin(\pi/3.*(\psi+\theta+\phi)) \f$
/** \ingroup PolarGroup                                                    */
class PolarSin2: public RealFunction {
    public:
        PolarSin2(): RealFunction() { }
        PolarSin2 (double tmin, double tmax, double dt,
                   double umin, double umax, double du,
                   double vmin, double vmax, double dv);
        virtual ~PolarSin2 () { }

        virtual std::string getFunctionName() const { return "Polar: r = sin (pi/3.*(t+u+v))"; }

    protected:
    class DefiningFunction: public ParametricFunction<4, 3> {

      public:

        DefiningFunction(PolarSin2 *parent): _parent(parent) { }
        virtual return_type f(const argument_type &x);

      private:

        /// Not a smart pointer because it's initialized to \c this and mustn't be deleted
        PolarSin2* _parent;

    };
};

namespace {
    Function *createPolarSin2() { return new PolarSin2(); }
    const bool registeredR9 = TheFunctionFactory::Instance().registerFunction(createPolarSin2);
}

///////////////////////////////////////////////////////////////////////////////

/// \f$ r = \sqrt{\psi^2+\theta^2+\phi^2} \f$
/** \ingroup PolarGroup                                                    */
class PolarR: public RealFunction {
    public:
        PolarR(): RealFunction(), _phase(2.) { }
        PolarR (double _tmin, double _tmax, double _dt,
                double _umin, double _umax, double _du,
                double _vmin, double _vmax, double _dv,
                double _phase = 2);
        virtual ~PolarR () { }

        virtual std::string getFunctionName() const { return "Polar: r = sqrt (t�+u�+v�)"; }

        virtual void SetParameters(const ParameterMap &parms) {
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "Phase") _phase = i->second->toDouble();
            }
#       else
            setParameter(parms, this->_phase, "Phase");
#       endif
        }

    protected:
    class DefiningFunction: public ParametricFunction<4, 3> {

      public:

        DefiningFunction(PolarR *parent): _parent(parent) { }
        virtual return_type f(const argument_type &x);

      private:

        /// Not a smart pointer because it's initialized to \c this and mustn't be deleted
        PolarR* _parent;

    };

    double _phase;               ///< phase
};

namespace {
    Function *createPolarR() { return new PolarR(); }
    const bool registeredR10 = TheFunctionFactory::Instance().registerFunction(createPolarR);
}

#endif
