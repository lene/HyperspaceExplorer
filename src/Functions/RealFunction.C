//
// C++ Implementation: RealFunction
//
// Description: 
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <vector>

#include "Vector.H"
#include "RealFunction.H"

using VecMath::Vector;

/// Hypersphere c'tor given a definition set in R³ (as parameter space) and a
/// radius
/** @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _rad		radius
 */
Hypersphere::Hypersphere (double _tmin, double _tmax, double _dt,
                          double _umin, double _umax, double _du,
                          double _vmin, double _vmax, double _dv,
                          double _rad):
        RealFunction ("Hypersphere", _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
  Radius (_rad) {
      parameterNames.push_back("Radius");
      Initialize ();
}

/// Hypersphere defining function
/** @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		value of defining function at point in question
 */
Vector<4> &Hypersphere::f (double tt, double uu, double vv) {
  double sinphi = sin (pi/2*tt), cosphi = cos (pi/2*tt),	//  hypersphere
    sintht = sin (pi*uu), costht = cos (pi*uu),
    sinpsi = sin (pi*vv), cospsi = cos (pi*vv);
  F[0] = Radius*sinpsi*sintht*cosphi;
  F[1] = Radius*sinpsi*sintht*sinphi;
  F[2] = Radius*sinpsi*costht;
  F[3] = Radius*cospsi;

  return F;
}


/// Calculate normal to function at a given point in definition set
/** Overridden because it's much easier to calculate in a Hypersphere than in
 *  a generic function
 *  @param tt t value
 *  @param uu u value
 *  @param vv v value
 *  @return surface normal, normalized                                        */
Vector<4> &Hypersphere::normal (double tt, double uu, double vv) {
    static Vector<4> n;

  n = f (tt, uu, vv);
  VecMath::vnormalize (n);

  return n;
}


///////////////////////////////////////////////////////////////////////////////


/** Torus1 c'tor given a definition set in R³ (as parameter space) and three
 *  radii: major, minor and... what'sitcalled... subminor
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _R		major radius
 *  @param _r		minor radius
 *  @param _rho		subminor radius */
Torus1::Torus1 (double _tmin, double _tmax, double _dt,
		double _umin, double _umax, double _du,
		double _vmin, double _vmax, double _dv,
		double _R, double _r, double _rho):
  RealFunction ("Torus 1", _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
  R (_R), r (_r), rho (_rho) {
      parameterNames.push_back("Major Radius");
      parameterNames.push_back("Minor Radius");
      parameterNames.push_back("Micro Radius");
      Initialize ();
}

/** Torus1 defining function
 *  @param tt t value
 *  @param uu u value
 *  @param vv v value
 *  @return value of defining function at point in question                   */
Vector<4> &Torus1::f (double tt, double uu, double vv) {
  F[0] =  cos (pi*tt)*(R+cos (pi*uu)*(r+rho*cos (pi*vv)));
  F[1] =  sin (pi*tt)*(R+cos (pi*uu)*(r+rho*cos (pi*vv)));
  F[2] =  sin (pi*uu)*(r+rho*cos (pi*vv));
  F[3] =  rho*sin (pi*vv);

  return F;
}


///////////////////////////////////////////////////////////////////////////////


/** Torus2 c'tor given a definition set in R³ (as parameter space) and two
 *  radii - a major and a minor (defining a sphere)
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _R		major radius
 *  @param _r		minor radius
 */
Torus2::Torus2 (double _tmin, double _tmax, double _dt,
		double _umin, double _umax, double _du,
		double _vmin, double _vmax, double _dv,
		double _R, double _r):
  RealFunction ("Torus 2", _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
  R (_R), r (_r) {
      parameterNames.push_back("Major Radius");
      parameterNames.push_back("Minor Radius");

      Initialize ();
}

/** Torus2 defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		value of defining function at point in question
 */
Vector<4> &Torus2::f (double tt, double uu, double vv) {
  F[0] =  cos (pi*tt)*(R+r*cos (pi*uu)*cos (pi*vv));
  F[1] =  cos (pi*tt)*(R+r*cos (pi*uu)*sin (pi*vv));
  F[2] =  cos (pi*tt)*(R+r*sin (pi*uu));
  F[3] =  sin (pi*tt)*R;

  return F;
}


////////////////////////////////////////////////////////////////////////////////


/** Fr3r (example R³->R function) c'tor given a definition set in R³
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 */
Fr3r::Fr3r (double _tmin, double _tmax, double _dt,
            double _umin, double _umax, double _du,
            double _vmin, double _vmax, double _dv):
    RealFunction ("1/(r²+1)", _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** Fr3r defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		value of defining function at point in question
 */
Vector<4> &Fr3r::f (double tt, double uu, double vv) {
  F[0] = tt;
  F[1] = uu;
  F[2] = vv;
  double rsq = tt*tt+uu*uu+vv*vv;
  F[3] = 1./(rsq+.25);
  // sin (pi*(tt*tt+uu*uu+vv*vv));
  // exp (tt*tt+uu*uu+vv*vv);

  return F;
}


////////////////////////////////////////////////////////////////////////////////


/** GravitationPotential c'tor given a definition set in R³ (as parameter space),
 *  a mass and a radius of a spherical mass
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _M		Mass
 *  @param _R		radius
 */
GravitationPotential::GravitationPotential (double xmin, double xmax, double dx,
                                            double ymin, double ymax, double dy,
                                            double zmin, double zmax, double dz,
                                            double _M, double _R):
        RealFunction ("Gravitation Potential", xmin, xmax, dx, ymin, ymax, dy, zmin, zmax, dz),
  M (_M), R (_R) {
      parameterNames.push_back("M");
      parameterNames.push_back("R");
      Initialize ();
}

/** GravitationPotential defining function
 *  @param tt   t value
 *  @param uu   u value
 *  @param vv   v value
 *  @return     value of defining function at point in question
 */
Vector<4> &GravitationPotential::f (double tt, double uu, double vv) {
  const double G = 1;		//  arbitrary value for gravitation constant
  F[0] = tt;
  F[1] = uu;
  F[2] = vv;
  double rsq = tt*tt+uu*uu+vv*vv;
  if (rsq > R*R)
    F[3] = G*M/rsq;
  else
    F[3] = G*M/(R*R*R)*sqrt (rsq);

  return F;
}


///////////////////////////////////////////////////////////////////////////////


/** Fr3rSin c'tor given a definition set in R³ (as parameter space)
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 */
Fr3rSin::Fr3rSin (double _tmin, double _tmax, double _dt,
		  double _umin, double _umax, double _du,
		  double _vmin, double _vmax, double _dv):
        RealFunction ("sin (r²)", _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** Fr3rSin defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		sin (pi*(x²+y²+z²))
 */
Vector<4> &Fr3rSin::f (double tt, double uu, double vv) {
  F[0] = tt;
  F[1] = uu;
  F[2] = vv;
  F[3] = sin (pi*(tt*tt+uu*uu+vv*vv));

  return F;
}


///////////////////////////////////////////////////////////////////////////////


/** Fr3rExp c'tor given a definition set in R³ (as parameter space)
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 */
Fr3rExp::Fr3rExp (double _tmin, double _tmax, double _dt,
		  double _umin, double _umax, double _du,
		  double _vmin, double _vmax, double _dv):
        RealFunction ("exp (r²)", _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** Fr3rExp defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		exp (x²+y²+z²)
 */
Vector<4> &Fr3rExp::f (double tt, double uu, double vv) {
  F[0] = tt;
  F[1] = uu;
  F[2] = vv;
  F[3] = exp (tt*tt+uu*uu+vv*vv);

  return F; }


///////////////////////////////////////////////////////////////////////////////


/** Polar (example polar function) c'tor given a definition set in [t, u, v]
 *  as parameter space
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 */
Polar::Polar (double _tmin, double _tmax, double _dt,
	      double _umin, double _umax, double _du,
	      double _vmin, double _vmax, double _dv):
  RealFunction ("Polar: Hypersphere", _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** Polar defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		value of defining function at point in question
 */
Vector<4> &Polar::f (double tt, double uu, double vv) {
  double sinphi = sin (pi*tt), cosphi = cos (pi*tt),
    sintht = sin (pi*uu), costht = cos (pi*uu),
    sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
    Radius = sin (pi/3.*(tt+uu+vv));

  F[0] = Radius*sinpsi*sintht*cosphi;
  F[1] = Radius*sinpsi*sintht*sinphi;
  F[2] = Radius*sinpsi*costht;
  F[3] = Radius*cospsi;

  return F;
}


///////////////////////////////////////////////////////////////////////////////


/** PolarSin c'tor given a definition set in R³ (as parameter space) and a
 *  phase
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _phase	phase
 */
PolarSin::PolarSin (double _tmin, double _tmax, double _dt,
		    double _umin, double _umax, double _du,
		    double _vmin, double _vmax, double _dv,
		    double _phase):
        RealFunction ("Polar: r = 1/2+sin (Phase*pi*t*u*v)", _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
  Phase (_phase) {
  Initialize ();
}

/** PolarSin defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		r = 1/2 + |sin (pi*phase*theta*phi*psi)|
 */
Vector<4> &PolarSin::f (double tt, double uu, double vv) {
  double sinphi = sin (pi*tt), cosphi = cos (pi*tt),
    sintht = sin (pi*uu), costht = cos (pi*uu),
    sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
    Radius = .5+fabs (sin (Phase*tt*uu*vv*pi));

  F[0] = Radius*sinpsi*sintht*cosphi;
  F[1] = Radius*sinpsi*sintht*sinphi;
  F[2] = Radius*sinpsi*costht;
  F[3] = Radius*cospsi;

  return F;
}


///////////////////////////////////////////////////////////////////////////////


/** PolarSin2 c'tor given a definition set in R³ (as parameter space)
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 */
PolarSin2::PolarSin2 (double _tmin, double _tmax, double _dt,
		      double _umin, double _umax, double _du,
		      double _vmin, double _vmax, double _dv):
        RealFunction ("Polar: r = sin (pi/3.*(t+u+v))", _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
    parameterNames.push_back("Phase");
    Initialize ();
}

/** PolarSin2 defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		r = sin (pi/3*(phi+theta+psi))
 */
Vector<4> &PolarSin2::f (double tt, double uu, double vv) {
  double sinphi = sin (pi*tt), cosphi = cos (pi*tt),
    sintht = sin (pi*uu), costht = cos (pi*uu),
    sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
    Radius = sin (pi/3.*(tt+uu+vv));

  F[0] = Radius*sinpsi*sintht*cosphi;
  F[1] = Radius*sinpsi*sintht*sinphi;
  F[2] = Radius*sinpsi*costht;
  F[3] = Radius*cospsi;

  return F;
}


///////////////////////////////////////////////////////////////////////////////


/** PolarR c'tor given a definition set in R³ (as parameter space) and a
 *  phase
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _phase	phase
 */
PolarR::PolarR (double _tmin, double _tmax, double _dt,
		double _umin, double _umax, double _du,
		double _vmin, double _vmax, double _dv,
		double _phase):
        RealFunction ("Polar: r = sqrt (t²+u²+v²)", _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
  Phase (_phase) {
      parameterNames.push_back("Phase");
  Initialize ();
}

/** PolarR defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		r = sqrt (phi²+theta²+psi²)
 */
Vector<4> &PolarR::f (double tt, double uu, double vv) {
  double sinphi = sin (pi*tt), cosphi = cos (pi*tt),
    sintht = sin (pi*uu), costht = cos (pi*uu),
    sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
    Radius = sqrt (tt*tt+uu*uu+vv*vv);

  F[0] = Radius*sinpsi*sintht*cosphi;
  F[1] = Radius*sinpsi*sintht*sinphi;
  F[2] = Radius*sinpsi*costht;
  F[3] = Radius*cospsi;

  return F;
}
