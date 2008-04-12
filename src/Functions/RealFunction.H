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

/// A \em RealFunction is a mathematical function  \f$ f: R^3 \rightarrow R \f$ .
/** The function \em f is evaluated on a 3-dimensional cartesian grid. The
 *  function value constitutes the fourth dimension of the Function object:
 *  \f$ \vec{x} = ( x, y, z, f(x, y, z) ) \f$.
 *
 *  The parent class \em Function provides the evaluation on the grid, together
 *  with methods to rotate and translate the grid in 4-space,  to project the
 *  transformed grid onto 3-space, and to draw the projected grid into an OpenGL
 *  display list.
 *
 *  \ingroup RealGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class RealFunction: public RealBase {
    public:
        RealFunction (const QString &name,
                      double _tmin, double _tmax, double _dt,
                      double _umin, double _umax, double _du,
                      double _vmin, double _vmax, double _dv,
                      parameterMap _parms = parameterMap());
        virtual ~RealFunction() { }

        virtual void Transform (double Rxy, double Rxz, double Rxw,
                                double Ryz, double Ryw, double Rzw,
                                double Tx, double Ty, double Tz, double Tw);
        virtual void Project (double ScrW, double CamW, bool DepthCue4D);
        virtual void Draw (void);

        virtual void ReInit(double _tmin, double _tmax, double _dt,
                            double _umin, double _umax, double _du,
                            double _vmin, double _vmax, double _dv);

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
        Hypersphere (double _tmin, double _tmax, double _dt,
                     double _umin, double _umax, double _du,
                     double _vmin, double _vmax, double _dv,
                     double _rad = 1);
        virtual ~Hypersphere() { }
        virtual void SetParameters (double _a = 0, double = 0, double = 0,
                                    double = 0) { Radius = _a; }

    protected:
        virtual function_type f;
        virtual function_type normal;

        double Radius;
};


///////////////////////////////////////////////////////////////////////////////

/** a four-dimensional torus where there are three radii - one circling about
 *  the main axis, the second circling perpendicular to the first circle, and
 *  the third circling about the second circle, perpendicular to all other
 *  directions
 *  \ingroup PolarGroup                                                    */
class Torus1: public RealFunction {
    public:
        Torus1 (double _tmin, double _tmax, double _dt,
                double _umin, double _umax, double _du,
                double _vmin, double _vmax, double _dv,
                double _R = 2, double _r = 1, double _rho = 0.5);
        virtual ~Torus1() { }
        virtual void SetParameters (double _a = 0, double _b = 0,
                                    double _c = 0, double = 0) {
                                        R = _a; r = _b; rho = _c; }

    protected:
        virtual function_type f;

        double R, r, rho;
};


///////////////////////////////////////////////////////////////////////////////

/** a four-dimensional torus where a sphere circles about a center point in a
 *  direction perpendicular to all directions making up the sphere
 *  \ingroup RealGroup                                                    */
class Torus2: public RealFunction {
    public:
        Torus2 (double _tmin, double _tmax, double _dt,
                double _umin, double _umax, double _du,
                double _vmin, double _vmax, double _dv,
                double _R = 1, double _r = 0.5);
        virtual ~Torus2 () { }
        virtual void SetParameters (double _a = 0, double _b = 0,
                                    double = 0, double = 0) {
                                        R = _a; r = _b; }

    protected:
        virtual function_type f;

        double R, r;
};


///////////////////////////////////////////////////////////////////////////////

/** an example function from \f$R^3 \rightarrow R\f$
    \f{eqnarray*}{
        r^2      & = & x^2+y^2+z^2  \\
        f(x,y,z) & = & 1./(r^2+.25)
    \f}
 *  \ingroup RealGroup                                                    */
class Fr3r: public RealFunction {
    public:
        Fr3r (double _tmin, double _tmax, double _dt,
              double _umin, double _umax, double _du,
              double _vmin, double _vmax, double _dv);
        virtual ~Fr3r() { }

    protected:
        virtual function_type f;

        double Radius;
};


///////////////////////////////////////////////////////////////////////////////

/** a function describing the gravitational potential of a spherical mass
 *  \ingroup RealGroup                                                    */
class GravitationPotential: public RealFunction {
    public:
        GravitationPotential (double _tmin, double _tmax, double _dt,
                              double _umin, double _umax, double _du,
                              double _vmin, double _vmax, double _dv,
                              double _M = 1, double _R = 0.25);
        virtual ~GravitationPotential () { }
        virtual void SetParameters (double _a = 0, double _b = 0, double = 0, double = 0) {
            M = _a; R = _b;
        }

    protected:
        virtual function_type f;

        double M,               //  not really M, but M/R^3
        R;
};

///////////////////////////////////////////////////////////////////////////////

/** \f$ f(x,y,z) = \sin (\pi*(x^2+y^2+z^2)) \f$
 *  \ingroup RealGroup                                                    */
class Fr3rSin: public RealFunction {
    public:
        Fr3rSin (double _tmin, double _tmax, double _dt,
                 double _umin, double _umax, double _du,
                 double _vmin, double _vmax, double _dv);
        virtual ~Fr3rSin () { }

    protected:
        virtual function_type f;
};

///////////////////////////////////////////////////////////////////////////////

/** \f$ f(x,y,z) = \exp (x^2+y^2+z^2) \f$
 *  \ingroup RealGroup                                                    */
class Fr3rExp: public RealFunction {
    public:
        Fr3rExp (double _tmin, double _tmax, double _dt,
                 double _umin, double _umax, double _du,
                 double _vmin, double _vmax, double _dv);
        virtual ~Fr3rExp () { }

    protected:
        virtual function_type f;
};

///////////////////////////////////////////////////////////////////////////////

/** a hypersphere as an example polar function
 *  \ingroup PolarGroup                                                    */
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

/** \f$ r(\psi, \theta, \phi) = |\sin (Phase*\pi*\psi*\theta*\phi)| \f$
 *  \ingroup PolarGroup                                                    */
class PolarSin: public RealFunction {
    public:
        PolarSin (double _tmin, double _tmax, double _dt,
                  double _umin, double _umax, double _du,
                  double _vmin, double _vmax, double _dv,
                  double _phase = 2);
        virtual ~PolarSin () { }
        virtual void SetParameters (double _a = 0, double = 0, double = 0, double = 0) {
            Phase = _a; }

    protected:
        virtual function_type f;
        double Phase;
};


///////////////////////////////////////////////////////////////////////////////

/** \f$ r = \sin(\pi/3.*(\psi+\theta+\phi)) \f$
 *  \ingroup PolarGroup                                                    */
class PolarSin2: public RealFunction {
    public:
        PolarSin2 (double _tmin, double _tmax, double _dt,
                   double _umin, double _umax, double _du,
                   double _vmin, double _vmax, double _dv);
        virtual ~PolarSin2 () { }

    protected:
        virtual function_type f;
};


///////////////////////////////////////////////////////////////////////////////

/** \f$ r = \sqrt{\psi^2+\theta^2+\phi^2} \f$
 *  \ingroup PolarGroup                                                    */
class PolarR: public RealFunction {
    public:
        PolarR (double _tmin, double _tmax, double _dt,
                double _umin, double _umax, double _du,
                double _vmin, double _vmax, double _dv,
                double _phase = 2);
        virtual ~PolarR () { }
        virtual void SetParameters (double _a = 0, double = 0, double = 0, double = 0) {
            Phase = _a; }

    protected:
        virtual function_type f;
        double Phase;
};

#endif
