//
// C++ Implementation: RealFunction
//
// Description:
//
//
// Author: Helge Preuss <lene.preuss@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <vector>

#include "Globals.h"
#include "Log.h"
#include "ColorManager.h"

#include "Vector.h"
#include "Matrix.h"
#include "RealFunction.h"

#include "Transformation.h"
#include "Projection.h"

using std::cerr;
using std::endl;

using VecMath::NestedVector;
using VecMath::Vector;
using VecMath::Matrix;
using std::tr1::shared_ptr;

double RealBase::_min = -1.;
double RealBase::_max =  1.;
double RealBase::_d = 0.1;

/** RealFunction c'tor given only a name: All grid values are set to defaults
 */
RealFunction::RealFunction():
    RealBase(_min, _max, _d, _min, _max, _d, _min, _max, _d,
             ParameterMap()) { }

/** RealFunction c'tor given a definition set in \f$ R^3 \f$ (as parameter space)
 *  \param tmin minimal value in t
 *  \param tmax maximal value in t
 *  \param dt stepsize in t
 *  \param umin minimal value in u
 *  \param umax maximal value in u
 *  \param du stepsize in u
 *  \param vmin minimal value in v
 *  \param vmax maximal value in v
 *  \param dv stepsize in v
 *  \param parms function parameters                               */
RealFunction::RealFunction(double tmin, double tmax, double dt,
                           double umin, double umax, double du,
                           double vmin, double vmax, double dv,
                           ParameterMap parms):
        RealBase(tmin, tmax, dt, umin, umax, du, vmin, vmax, dv, parms) {

  if (MemRequired () > Globals::Instance().getMaxMemory()) {
    cerr << "Using a " << getTsteps() << "x" << getUsteps() << "x" << getVsteps()
         << " grid would require approx. " << MemRequired () << " MB of memory.\n";
    while (MemRequired () > Globals::Instance().getMaxMemory()) {
      getTsteps()--; getUsteps()--; getVsteps()--;
    }
    cerr << "Using a " << getTsteps() << "x" << getUsteps() << "x" << getVsteps()
         << " grid instead." << endl;
    getDt() = (getTmax()-getTmin())/getTsteps();
    getDu() = (getUmax()-getUmin())/getUsteps();
    getDv() = (getVmax()-getVmin())/getVsteps();
  }
}

/// Allocate and initialize X[][][] with values of f().
void RealFunction::Initialize () {
  _X = FunctionValueGrid<4, 3>(_function,
                               Vector<3, unsigned>(getTsteps()+2, getUsteps()+2, getVsteps()+2),
                               Vector<3>(getTmin(), getUmin(), getVmin()),
                               Vector<3>(getTmax(), getUmax(), getVmax()));

  calibrateColors();

}

void RealFunction::calibrateColors() const {

  std::pair< double, double > Wext = findExtremesInW();

  for (unsigned t = 0; t <= getTsteps(); t++) {
    for (unsigned u = 0; u <= getUsteps()+1; u++) {
      for (unsigned v = 0; v <= getVsteps()+1; v++) {
        ColMgrMgr::Instance().calibrateColor(
            X()[t][u][v],
            Color(float(t)/float(getTsteps()), float(u)/float(getUsteps()),
                  float(v)/float(getVsteps()),
                  (X()[t][u][v][3]-Wext.first)/(Wext.second-Wext.first)));
      }
    }
  }
}

std::pair< double, double > RealFunction::findExtremesInW() const {

  double Wmin = 0., Wmax = 0.;
  for (unsigned t = 0; t < getTsteps(); t++) {
    for (unsigned u = 0; u <= getUsteps()+1; u++) {
      for (unsigned v = 0; v <= getVsteps()+1; v++) {
        if (X()[t][u][v][3] < Wmin) Wmin = X()[t][u][v][3];
        if (X()[t][u][v][3] > Wmax) Wmax = X()[t][u][v][3];
      }
    }
  }

  return std::make_pair(Wmin, Wmax);
}

/// Re-initialize a RealFunction if the definition set has changed
/** \param tmin minimal value in t
 *  \param tmax maximal value in t
 *  \param dt stepsize in t
 *  \param umin minimal value in u
 *  \param umax maximal value in u
 *  \param du stepsize in u
 *  \param vmin minimal value in v
 *  \param vmax maximal value in v
 *  \param dv stepsize in v
 */
void RealFunction::ReInit(double tmin, double tmax, double dt,
                          double umin, double umax, double du,
                          double vmin, double vmax, double dv) {

  setBoundariesAndStepwidth(tmin, tmax, dt, umin, umax, du, vmin, vmax, dv);

  Initialize ();

}

/** \param tmin minimal value in t
 *  \param tmax maximal value in t
 *  \param dt stepsize in t
 *  \param umin minimal value in u
 *  \param umax maximal value in u
 *  \param du stepsize in u
 *  \param vmin minimal value in v
 *  \param vmax maximal value in v
 *  \param dv stepsize in v
 */
void RealFunction::setBoundariesAndStepwidth(double tmin, double tmax, double dt,
                                             double umin, double umax, double du,
                                             double vmin, double vmax, double dv) {
  getTmin() = tmin;   getTmax() = tmax;   getDt() = dt;
  getUmin() = umin;   getUmax() = umax;   getDu() = du;
  getVmin() = vmin;   getVmax() = vmax;   getDv() = dv;
  getTsteps() = unsigned ((getTmax()-getTmin())/getDt()+2);
  getUsteps() = unsigned ((getUmax()-getUmin())/getDu()+2);
  getVsteps() = unsigned ((getVmax()-getVmin())/getDv()+2);
}

/// Transforms a RealFunction
/** \param R rotation
 *  \param T translation                                                      */
void RealFunction::Transform (const VecMath::Rotation<4> &R,
                              const VecMath::Vector<4> &T) {
  Transformation<4, 3> xform(R, T);
  _Xtrans = xform.transform(_X.getValues());
}

void RealFunction::setDepthCueColors(double Wmax, double Wmin) {
  for(unsigned t = 0;t <= getTsteps() + 1;t++) {
    for(unsigned u = 0;u <= getUsteps() + 1;u++) {
      for(unsigned v = 0;v <= getVsteps() + 1;v++){
        ColMgrMgr::Instance().depthCueColor(Wmax, Wmin,
                                            Xtrans()[t][u][v][3],
                                            X()[t][u][v]);
      }
    }
  }
}

/// Projects a RealFunction into three-space
/** \param scr_w w coordinate of screen
 *  \param cam_w w coordinate of camera
 *  \param depthcue4d whether to use hyperfog/depth cue                       */
void RealFunction::Project (double scr_w, double cam_w, bool depthcue4d) {

  Projection<4, 3, 3> p(scr_w, cam_w, depthcue4d);
  _Xscr = p.project(Xtrans());

  if (depthcue4d) {
    std::pair< double, double > Wext = findExtremesInW();
    setDepthCueColors(Wext.first, Wext.second);
  }
}

#include "GridDrawer.h"

/// Draw the projected Function (onto screen or into GL list, as it is)
/** */
void RealFunction::Draw (void) {
# ifdef USE_GRID_DRAWER
    GridDrawer<3> draw(Xscr(), NULL);
    draw.execute();
# else
    for (unsigned t = 0; t < getTsteps(); t++)
      DrawPlane (t);
# endif
}


/// Draw the current plane of the projected Function
/** \param t current t value                                                  */
void RealFunction::DrawPlane (unsigned t){
  for (unsigned u = 0; u < getUsteps(); u++)
    DrawStrip (t, u);
}

/// Draw the current strip of the projected Function
/** \param t current t value
 *  \param u current u value                                                  */
void RealFunction::DrawStrip (unsigned t, unsigned u){
  for (unsigned v = 0; v < getVsteps(); v++)
    DrawCube (t, u, v);
}

/// Draw the current cube or cell of the projected Function
/** \param t current t value
 *  \param u current u value
 *  \param v current v value                                                  */
void RealFunction::DrawCube (unsigned t, unsigned u, unsigned v) {
    /// \todo don't use a malloc'ed pointer
    static Vector<3> *V = new Vector<3> [8];

    V[0] = Xscr()[t][u][v];     V[1] = Xscr()[t][u][v+1];
    V[2] = Xscr()[t][u+1][v];   V[3] = Xscr()[t][u+1][v+1];
    V[4] = Xscr()[t+1][u][v];   V[5] = Xscr()[t+1][u][v+1];
    V[6] = Xscr()[t+1][u+1][v]; V[7] = Xscr()[t+1][u+1][v+1];

    glBegin (GL_QUAD_STRIP);
    if (t == 0) {
        setVertex(X()[t][u][v], V[0]);
        setVertex(X()[t][u][v+1], V[1]);
        addVertices(2);
    }
    setVertex(X()[t][u+1][v], V[2]);
    setVertex(X()[t][u+1][v+1], V[3]);
    setVertex(X()[t+1][u+1][v], V[6]);
    setVertex(X()[t+1][u+1][v+1], V[7]);
    setVertex(X()[t+1][u][v], V[4]);
    setVertex(X()[t+1][u][v+1], V[5]);
    addVertices(6);
    if (u == 0) {
        setVertex(X()[t][u][v], V[0]);
        setVertex(X()[t][u][v+1], V[1]);
        addVertices(2);
    }
    glEnd ();

    glBegin (GL_QUADS);
    if (v == 0) {
        setVertex(X()[t][u][v], V[0]);
        setVertex(X()[t][u+1][v], V[2]);
        setVertex(X()[t+1][u+1][v], V[6]);
        setVertex(X()[t+1][u][v], V[4]);
        addVertices(4);
    }
    setVertex(X()[t][u][v+1], V[1]);
    setVertex(X()[t][u+1][v+1], V[3]);
    setVertex(X()[t+1][u+1][v+1], V[7]);
    setVertex(X()[t+1][u][v+1], V[5]);
    addVertices(4);
    glEnd ();
}

/// Calculate normal to function at a given point in definition set.
/** No further assumption is made than that f () is continuous.
 *
 *  This function is not yet used anywhere, but i like it.
 *  \param tt t value
 *  \param uu u value
 *  \param vv v value
 *  \return surface normal, normalized                                        */
Vector<4> &RealFunction::normal (double tt, double uu, double vv) {
  static Vector<4> n;

  Function::vec4vec1D D = df (tt, uu, vv);

  n = VecMath::vcross (D[0], D[1], D[2]);
  VecMath::vnormalize (n);

  return n;
}

const VecMath::NestedVector< Vector< 4 >, 3 > &RealFunction::X() const {
  return _X.getValues();
}

const VecMath::NestedVector< Vector< 4 >, 3 > &RealFunction::Xtrans() const {
  return _Xtrans;
}

const VecMath::NestedVector< Vector< 3 >, 3 >& RealFunction::Xscr() const {
    return _Xscr;
}


////////////////////////////////////////////////////////////////////////////////


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
 *  \param tmin	    minimal value in t
 *  \param tmax	    maximal value in t
 *  \param dt		stepsize in t
 *  \param umin	    minimal value in u
 *  \param umax	    maximal value in u
 *  \param du		stepsize in u
 *  \param vmin	    minimal value in v
 *  \param vmax	    maximal value in v
 *  \param dv		stepsize in v
 *  \param R		major radius
 *  \param r		minor radius
 *  \param rho		subminor radius */
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
 *  \param tmin	minimal value in t
 *  \param tmax	maximal value in t
 *  \param dt	stepsize in t
 *  \param umin	minimal value in u
 *  \param umax	maximal value in u
 *  \param du	stepsize in u
 *  \param vmin	minimal value in v
 *  \param vmax	maximal value in v
 *  \param dv	stepsize in v
 *  \param R	major radius
 *  \param r	minor radius
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
 *  \param tmin	minimal value in t
 *  \param tmax	maximal value in t
 *  \param dt	stepsize in t
 *  \param umin	minimal value in u
 *  \param umax	maximal value in u
 *  \param du	stepsize in u
 *  \param vmin	minimal value in v
 *  \param vmax	maximal value in v
 *  \param dv	stepsize in v
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
 *  \param tmin	minimal value in t
 *  \param tmax	maximal value in t
 *  \param dt	stepsize in t
 *  \param umin	minimal value in u
 *  \param umax	maximal value in u
 *  \param du	stepsize in u
 *  \param vmin	minimal value in v
 *  \param vmax	maximal value in v
 *  \param dv	stepsize in v
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
 *  \param tmin	minimal value in t
 *  \param tmax	maximal value in t
 *  \param dt	stepsize in t
 *  \param umin	minimal value in u
 *  \param umax	maximal value in u
 *  \param du	stepsize in u
 *  \param vmin	minimal value in v
 *  \param vmax	maximal value in v
 *  \param dv	stepsize in v
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
 *  \param tmin	minimal value in t
 *  \param tmax	maximal value in t
 *  \param dt	stepsize in t
 *  \param umin	minimal value in u
 *  \param umax	maximal value in u
 *  \param du	stepsize in u
 *  \param vmin	minimal value in v
 *  \param vmax	maximal value in v
 *  \param dv	stepsize in v
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
 *  \param tmin	minimal value in t
 *  \param tmax	maximal value in t
 *  \param dt	stepsize in t
 *  \param umin	minimal value in u
 *  \param umax	maximal value in u
 *  \param du	stepsize in u
 *  \param vmin	minimal value in v
 *  \param vmax	maximal value in v
 *  \param dv	stepsize in v
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
 *  \param tmin	minimal value in t
 *  \param tmax	maximal value in t
 *  \param dt	stepsize in t
 *  \param umin	minimal value in u
 *  \param umax	maximal value in u
 *  \param du	stepsize in u
 *  \param vmin	minimal value in v
 *  \param vmax	maximal value in v
 *  \param dv	stepsize in v
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
 *  \param tmin	minimal value in t
 *  \param tmax	maximal value in t
 *  \param dt	stepsize in t
 *  \param umin	minimal value in u
 *  \param umax	maximal value in u
 *  \param du	stepsize in u
 *  \param vmin	minimal value in v
 *  \param vmax	maximal value in v
 *  \param dv	stepsize in v
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
