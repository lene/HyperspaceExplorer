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

#include "RealFunctionImplementations.h"

#include "Vector.impl.h"

using std::shared_ptr;
using VecMath::Vector;

/// Hypersphere c'tor given a definition set in \f$ R^3 \f$ (as parameter space) and a radius
/** \param tmin minimal value in t
 *  \param tmax maximal value in t
 *  \param dt stepsize in t
 *  \param umin minimal value in u
 *  \param umax maximal value in u
 *  \param du stepsize in u
 *  \param vmin minimal value in v
 *  \param vmax maximal value in v
 *  \param dv stepsize in v
 *  \param rad radius                                                        */
Hypersphere::Hypersphere(double tmin, double tmax, double dt,
                         double umin, double umax, double du,
                         double vmin, double vmax, double dv,
                         double rad):
        RealFunction (tmin, tmax, dt, umin, umax, du, vmin, vmax, dv),
        _radius (rad) {

    _function = shared_ptr< ParametricFunction<4, 3> >(new DefiningFunction(this));

    declareParameter("Radius", 1.0);
    Initialize ();
}

void Hypersphere::SetParameters(const ParameterMap &parms) {
    //  parms["Radius"].value must be set!
#if 1
    for (ParameterMap::const_iterator i = parms.begin(); i != parms.end(); ++i) {
        if (i->second->getName() == "Radius") _radius = i->second->toDouble();
    }
#else
    setParameter(parms, this->_radius, "Radius");
#endif
}

ParametricFunction< 4, 3 >::return_type Hypersphere::DefiningFunction::f(
  const ParametricFunction< 4, 3 >::argument_type& x) {

  double sinphi = sin(pi/2*x[0]),
         cosphi = cos(pi/2*x[0]),
         sintht = sin(pi*x[1]),
         costht = cos(pi*x[1]),
         sinpsi = sin(pi*x[2]),
         cospsi = cos(pi*x[2]);

  Vector<4> F;
  F[0] = _parent->_radius*sinpsi*sintht*cosphi;
  F[1] = _parent->_radius*sinpsi*sintht*sinphi;
  F[2] = _parent->_radius*sinpsi*costht;
  F[3] = _parent->_radius*cospsi;

  return F;

}


/// Calculate normal to function at a given point in definition set
/** Overridden because it's much easier to calculate in a Hypersphere than in
 *  a generic function
 *  \param tt t value
 *  \param uu u value
 *  \param vv v value
 *  \return surface normal, normalized                                        */
Vector<4> &Hypersphere::normal (double tt, double uu, double vv) {
    static Vector<4> n;

  n = operator() (tt, uu, vv);
  VecMath::vnormalize (n);

  return n;
}


///////////////////////////////////////////////////////////////////////////////


/** Torus1 c'tor given a definition set in \f$ R^3 \f$ (as parameter space) and three
 *  radii: major, minor and... what'sitcalled... subminor
 *  \param tmin     minimal value in t
 *  \param tmax     maximal value in t
 *  \param dt   stepsize in t
 *  \param umin     minimal value in u
 *  \param umax     maximal value in u
 *  \param du   stepsize in u
 *  \param vmin     minimal value in v
 *  \param vmax     maximal value in v
 *  \param dv   stepsize in v
 *  \param R    major radius
 *  \param r    minor radius
 *  \param rho    subminor radius */
Torus1::Torus1 (double tmin, double tmax, double dt,
                double umin, double umax, double du,
                double vmin, double vmax, double dv,
                double R, double r, double rho):
    RealFunction (tmin, tmax, dt, umin, umax, du, vmin, vmax, dv),
    _R (R), _r (r), _rho (rho) {

  _function = shared_ptr< ParametricFunction<4, 3> >(new DefiningFunction(this));

  declareParameter("Major Radius", 2.0);
  declareParameter("Minor Radius", 1.0);
  declareParameter("Micro Radius", 0.5);
  Initialize ();
}

ParametricFunction< 4, 3 >::return_type Torus1::DefiningFunction::f(
  const ParametricFunction< 4, 3 >::argument_type& x) {

  VecMath::Vector<4> F;
  F[0] =  cos(pi*x[0])*(_parent->_R+cos(pi*x[1])*(_parent->_r+_parent->_rho*cos(pi*x[2])));
  F[1] =  sin(pi*x[0])*(_parent->_R+cos(pi*x[1])*(_parent->_r+_parent->_rho*cos(pi*x[2])));
  F[2] =  sin(pi*x[1])*(_parent->_r+_parent->_rho*cos(pi*x[2]));
  F[3] =  _parent->_rho*sin(pi*x[2]);

  return F;
}


///////////////////////////////////////////////////////////////////////////////


/** Torus2 c'tor given a definition set in \f$ R^3 \f$ (as parameter space) and two
 *  radii - a major and a minor (defining a sphere)
 *  \param tmin minimal value in t
 *  \param tmax maximal value in t
 *  \param dt stepsize in t
 *  \param umin minimal value in u
 *  \param umax maximal value in u
 *  \param du stepsize in u
 *  \param vmin minimal value in v
 *  \param vmax maximal value in v
 *  \param dv stepsize in v
 *  \param R  major radius
 *  \param r  minor radius
 */
Torus2::Torus2 (double tmin, double tmax, double dt,
                double umin, double umax, double du,
                double vmin, double vmax, double dv,
                double R, double r):
  RealFunction (tmin, tmax, dt, umin, umax, du, vmin, vmax, dv),
  _R (R), _r (r) {

  _function = shared_ptr< ParametricFunction<4, 3> >(new DefiningFunction(this));

  declareParameter("Major Radius", 1.0);
  declareParameter("Minor Radius", 0.5);

  Initialize ();
}

ParametricFunction< 4, 3 >::return_type
Torus2::DefiningFunction::f(const ParametricFunction< 4, 3 >::argument_type& x) {
  Vector<4> F;
  F[0] =  cos(pi*x[0])*(_parent->_R+_parent->_r*cos(pi*x[1])*cos(pi*x[2]));
  F[1] =  cos(pi*x[0])*(_parent->_R+_parent->_r*cos(pi*x[1])*sin(pi*x[2]));
  F[2] =  cos(pi*x[0])*(_parent->_R+_parent->_r*sin(pi*x[1]));
  F[3] =  sin(pi*x[0])*_parent->_R;

  return F;

}

////////////////////////////////////////////////////////////////////////////////


/** Fr3r (example \f$ R^3 \rightarrow R \f$ function) c'tor given a definition set in \f$ R^3 \f$
 *  \param tmin minimal value in t
 *  \param tmax maximal value in t
 *  \param dt stepsize in t
 *  \param umin minimal value in u
 *  \param umax maximal value in u
 *  \param du stepsize in u
 *  \param vmin minimal value in v
 *  \param vmax maximal value in v
 *  \param dv stepsize in v
 */
Fr3r::Fr3r (double tmin, double tmax, double dt,
            double umin, double umax, double du,
            double vmin, double vmax, double dv):
    RealFunction (tmin, tmax, dt, umin, umax, du, vmin, vmax, dv) {

  _function = shared_ptr< ParametricFunction<4, 3> >(new DefiningFunction(this));

  Initialize ();
}

ParametricFunction< 4, 3 >::return_type
Fr3r::DefiningFunction::f(const ParametricFunction< 4, 3 >::argument_type& x) {
  Vector<4> F;
  F[0] = x[0];
  F[1] = x[1];
  F[2] = x[2];
  double rsq = x[0]*x[0]+x[1]*x[1]+x[2]*x[2];
  F[3] = 1./(rsq+.25);
  // sin (pi*(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]));
  // exp (x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);

  return F;

}

////////////////////////////////////////////////////////////////////////////////


/** GravitationPotential c'tor given a definition set in \f$ R^3 \f$ (as parameter space),
 *  a mass and a radius of a spherical mass
 *  \param xmin minimal value in t
 *  \param xmax maximal value in t
 *  \param dx   stepsize in t
 *  \param ymin minimal value in u
 *  \param ymax maximal value in u
 *  \param dy   stepsize in u
 *  \param zmin minimal value in v
 *  \param zmax maximal value in v
 *  \param dz   stepsize in v
 *  \param M   Mass of the generating sphere
 *  \param R   Radius of the generating sphere
 */
GravitationPotential::GravitationPotential (double xmin, double xmax, double dx,
                                            double ymin, double ymax, double dy,
                                            double zmin, double zmax, double dz,
                                            double M, double R):
        RealFunction (xmin, xmax, dx, ymin, ymax, dy, zmin, zmax, dz),
  _M (M), _R (R) {

  _function = shared_ptr< ParametricFunction<4, 3> >(new DefiningFunction(this));

  declareParameter("M", 1.0);
  declareParameter("R", 0.25);

  Initialize ();
}

ParametricFunction< 4, 3 >::return_type
GravitationPotential::DefiningFunction::f(const ParametricFunction< 4, 3 >::argument_type& x) {
  const double G = 1;     //  arbitrary value for gravitation constant
  Vector<4> F;
  F[0] = x[0];
  F[1] = x[1];
  F[2] = x[2];
  double rsq = x[0]*x[0]+x[1]*x[1]+x[2]*x[2];
  if (rsq > _parent->_R*_parent->_R)
    F[3] = G*_parent->_M/rsq;
  else
    F[3] = G*_parent->_M/(_parent->_R*_parent->_R*_parent->_R)*sqrt (rsq);

  return F;

}

///////////////////////////////////////////////////////////////////////////////


/** Fr3rSin c'tor given a definition set in \f$ R^3 \f$ (as parameter space)
 *  \param tmin minimal value in t
 *  \param tmax maximal value in t
 *  \param dt stepsize in t
 *  \param umin minimal value in u
 *  \param umax maximal value in u
 *  \param du stepsize in u
 *  \param vmin minimal value in v
 *  \param vmax maximal value in v
 *  \param dv stepsize in v
 */
Fr3rSin::Fr3rSin (double tmin, double tmax, double dt,
                  double umin, double umax, double du,
                  double vmin, double vmax, double dv):
        RealFunction (tmin, tmax, dt, umin, umax, du, vmin, vmax, dv) {

  _function = shared_ptr< ParametricFunction<4, 3> >(new DefiningFunction(this));

  Initialize ();
}

ParametricFunction< 4, 3 >::return_type
Fr3rSin::DefiningFunction::f(const ParametricFunction< 4, 3 >::argument_type& x) {
  Vector<4> F;
  F[0] = x[0];
  F[1] = x[1];
  F[2] = x[2];
  F[3] = sin (pi*(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]));

  return F;

}

///////////////////////////////////////////////////////////////////////////////


/** Fr3rExp c'tor given a definition set in \f$ R^3 \f$ (as parameter space)
 *  \param tmin minimal value in t
 *  \param tmax maximal value in t
 *  \param dt stepsize in t
 *  \param umin minimal value in u
 *  \param umax maximal value in u
 *  \param du stepsize in u
 *  \param vmin minimal value in v
 *  \param vmax maximal value in v
 *  \param dv stepsize in v
 */
Fr3rExp::Fr3rExp (double tmin, double tmax, double dt,
                  double umin, double umax, double du,
                  double vmin, double vmax, double dv):
        RealFunction (tmin, tmax, dt, umin, umax, du, vmin, vmax, dv) {

  _function = shared_ptr< ParametricFunction<4, 3> >(new DefiningFunction(this));

  Initialize ();
}

ParametricFunction< 4, 3 >::return_type
Fr3rExp::DefiningFunction::f(const ParametricFunction< 4, 3 >::argument_type& x) {
  Vector<4> F;
  F[0] = x[0];
  F[1] = x[1];
  F[2] = x[2];
  F[3] = exp (x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);

  return F;

}

///////////////////////////////////////////////////////////////////////////////


/** Polar (example polar function) c'tor given a definition set in [t, u, v]
 *  as parameter space
 *  \param tmin minimal value in t
 *  \param tmax maximal value in t
 *  \param dt stepsize in t
 *  \param umin minimal value in u
 *  \param umax maximal value in u
 *  \param du stepsize in u
 *  \param vmin minimal value in v
 *  \param vmax maximal value in v
 *  \param dv stepsize in v
 */
Polar::Polar(double tmin, double tmax, double dt,
             double umin, double umax, double du,
             double vmin, double vmax, double dv):
  RealFunction (tmin, tmax, dt, umin, umax, du, vmin, vmax, dv) {

  _function = shared_ptr< ParametricFunction<4, 3> >(new DefiningFunction(this));

  Initialize ();
}

ParametricFunction< 4, 3 >::return_type
Polar::DefiningFunction::f(const ParametricFunction< 4, 3 >::argument_type& x) {
  double sinphi = sin (pi*x[0]), cosphi = cos (pi*x[0]),
    sintht = sin (pi*x[1]), costht = cos (pi*x[1]),
    sinpsi = sin (pi*x[2]), cospsi = cos (pi*x[2]),
    Radius = sin (pi/3.*(x[0]+x[1]+x[2]));

  Vector<4> F;
  F[0] = Radius*sinpsi*sintht*cosphi;
  F[1] = Radius*sinpsi*sintht*sinphi;
  F[2] = Radius*sinpsi*costht;
  F[3] = Radius*cospsi;

  return F;

}

///////////////////////////////////////////////////////////////////////////////


/** PolarSin c'tor given a definition set in \f$ R^3 \f$ (as parameter space) and a
 *  phase
 *  \param tmin minimal value in t
 *  \param tmax maximal value in t
 *  \param dt stepsize in t
 *  \param umin minimal value in u
 *  \param umax maximal value in u
 *  \param du stepsize in u
 *  \param vmin minimal value in v
 *  \param vmax maximal value in v
 *  \param dv stepsize in v
 *  \param phase phase
 */
PolarSin::PolarSin (double tmin, double tmax, double dt,
                    double umin, double umax, double du,
                    double vmin, double vmax, double dv,
                    double phase):
        RealFunction (tmin, tmax, dt, umin, umax, du, vmin, vmax, dv),
    _phase (phase) {

    _function = shared_ptr< ParametricFunction<4, 3> >(new DefiningFunction(this));

    declareParameter("Phase", 2.0);
    Initialize ();
}

ParametricFunction< 4, 3 >::return_type
PolarSin::DefiningFunction::f(const ParametricFunction< 4, 3 >::argument_type& x) {

  double sinphi = sin (pi*x[0]),
    cosphi = cos (pi*x[0]),
    sintht = sin (pi*x[1]),
    costht = cos (pi*x[1]),
    sinpsi = sin (pi*x[2]),
    cospsi = cos (pi*x[2]),
    Radius = .5+fabs (sin (_parent->_phase*x[0]*x[1]*x[2]*pi));

  Vector<4> F;
  F[0] = Radius*sinpsi*sintht*cosphi;
  F[1] = Radius*sinpsi*sintht*sinphi;
  F[2] = Radius*sinpsi*costht;
  F[3] = Radius*cospsi;

  return F;

}

///////////////////////////////////////////////////////////////////////////////


/** PolarSin2 c'tor given a definition set in \f$ R^3 \f$ (as parameter space)
 *  \param tmin minimal value in t
 *  \param tmax maximal value in t
 *  \param dt stepsize in t
 *  \param umin minimal value in u
 *  \param umax maximal value in u
 *  \param du stepsize in u
 *  \param vmin minimal value in v
 *  \param vmax maximal value in v
 *  \param dv stepsize in v
 */
PolarSin2::PolarSin2 (double tmin, double tmax, double dt,
                      double umin, double umax, double du,
                      double vmin, double vmax, double dv):
        RealFunction (tmin, tmax, dt, umin, umax, du, vmin, vmax, dv) {

  _function = shared_ptr< ParametricFunction<4, 3> >(new DefiningFunction(this));

  Initialize ();
}

ParametricFunction< 4, 3 >::return_type
PolarSin2::DefiningFunction::f(const ParametricFunction< 4, 3 >::argument_type& x) {

  double sinphi = sin (pi*x[0]),
         cosphi = cos (pi*x[0]),
         sintht = sin (pi*x[1]),
         costht = cos (pi*x[1]),
         sinpsi = sin (pi*x[2]),
         cospsi = cos (pi*x[2]),
         Radius = sin (pi/3.*(x[0]+x[1]+x[2]));

  Vector<4> F;
  F[0] = Radius*sinpsi*sintht*cosphi;
  F[1] = Radius*sinpsi*sintht*sinphi;
  F[2] = Radius*sinpsi*costht;
  F[3] = Radius*cospsi;

  return F;

}

///////////////////////////////////////////////////////////////////////////////


/** PolarR c'tor given a definition set in \f$ R^3 \f$ (as parameter space) and a
 *  phase
 *  \param tmin minimal value in t
 *  \param tmax maximal value in t
 *  \param dt stepsize in t
 *  \param umin minimal value in u
 *  \param umax maximal value in u
 *  \param du stepsize in u
 *  \param vmin minimal value in v
 *  \param vmax maximal value in v
 *  \param dv stepsize in v
 *  \param phase phase
 */
PolarR::PolarR (double tmin, double tmax, double dt,
                double umin, double umax, double du,
                double vmin, double vmax, double dv,
                double phase):
        RealFunction (tmin, tmax, dt, umin, umax, du, vmin, vmax, dv),
        _phase (phase) {

  _function = shared_ptr< ParametricFunction<4, 3> >(new DefiningFunction(this));

  declareParameter("Phase", 2.0);
  Initialize ();
}

ParametricFunction< 4, 3 >::return_type
PolarR::DefiningFunction::f(const ParametricFunction< 4, 3 >::argument_type& x) {

  double sinphi = sin (pi*x[0]),
         cosphi = cos (pi*x[0]),
         sintht = sin (pi*x[1]),
         costht = cos (pi*x[1]),
         sinpsi = sin (pi*x[2]),
         cospsi = cos (pi*x[2]),
         Radius = sqrt (x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);

  Vector<4> F;
  F[0] = Radius*sinpsi*sintht*cosphi;
  F[1] = Radius*sinpsi*sintht*sinphi;
  F[2] = Radius*sinpsi*costht;
  F[3] = Radius*cospsi;

  return F;

}
