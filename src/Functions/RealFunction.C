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

#include "Transform.h"

using std::cerr;
using std::endl;

using VecMath::Vector;
using VecMath::Matrix;

double RealBase::_min = -1.;
double RealBase::_max =  1.;
double RealBase::_d = 0.1;

/** RealFunction c'tor given only a name: All grid values are set to defaults
 *  \param _name a name for the function
 */
RealFunction::RealFunction(const QString &_name):
        RealBase(_name, _min, _max, _d, _min, _max, _d, _min, _max, _d,
                 ParameterMap()) { }

/** RealFunction c'tor given a definition set in R� (as parameter space)
 *  \param _name a name for the function
 *  \param _tmin minimal value in t
 *  \param _tmax maximal value in t
 *  \param _dt stepsize in t
 *  \param _umin minimal value in u
 *  \param _umax maximal value in u
 *  \param _du stepsize in u
 *  \param _vmin minimal value in v
 *  \param _vmax maximal value in v
 *  \param _dv stepsize in v
 *  \param _parms function parameters                                         */
RealFunction::RealFunction(const QString &name,
                           double tmin, double tmax, double dt,
                           double umin, double umax, double du,
                           double vmin, double vmax, double dv,
                           ParameterMap _parms):
        RealBase(name, tmin, tmax, dt, umin, umax, du, vmin, vmax, dv,
                 _parms),
        _Xtrans(vec4vec3D()), _Xscr(vec3vec3D()) {
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

/// Initialize the temporary storage areas
/** Xscr[][][], Xtrans[][][]                */
void RealFunction::InitMem (void) {

    _Xscr.resize(getTsteps()+2);
    _Xtrans.resize(getTsteps()+2);

    for (unsigned t = 0; t <= getTsteps()+1; t++) {

        _Xscr[t].resize(getUsteps()+2);
        _Xtrans[t].resize(getUsteps()+2);

        for (unsigned u = 0; u <= getUsteps()+1; u++) {

            _Xscr[t][u].resize(getVsteps()+2);
            _Xtrans[t][u].resize(getVsteps()+2);
        }
    }
}

/// Allocate and initialize X[][][] with values of f()
/** Call InitMem() above */
void RealFunction::Initialize () {
    _X = vec4vec3D(getTsteps()+2);
//    ColMgrMgr::Instance().setFunction(this);

    for (unsigned t = 0; t <= getTsteps()+1; t++) {
        _X[t].resize(getUsteps()+2);

        for (unsigned u = 0; u <= getUsteps()+1; u++) {
            _X[t][u].resize(getVsteps()+2);

            for (unsigned v = 0; v <= getVsteps()+1; v++) {
                double T = getTmin()+t*getDt(), U =getUmin()+u*getDu(), V = getVmin()+v*getDv();
                _X[t][u][v] = f (T, U, V);
            }
        }
    }

    calibrateColors();

    InitMem ();
}

void RealFunction::calibrateColors() const {
    double Wmin = 0., Wmax = 0.;
    for (unsigned t = 0; t <= getTsteps()+1; t++) {
        for (unsigned u = 0; u <= getUsteps()+1; u++) {
            for (unsigned v = 0; v <= getVsteps()+1; v++) {
                if (_X[t][u][v][3] < Wmin) Wmin = _X[t][u][v][3];
                if (_X[t][u][v][3] > Wmax) Wmax = _X[t][u][v][3];
            }
        }
    }

    for (unsigned t = 0; t <= getTsteps()+1; t++) {
        for (unsigned u = 0; u <= getUsteps()+1; u++) {
            for (unsigned v = 0; v <= getVsteps()+1; v++) {
                ColMgrMgr::Instance().calibrateColor(
                    _X[t][u][v],
                    Color(float(t)/float(getTsteps()), float(u)/float(getUsteps()),
                          float(v)/float(getVsteps()),
                          (_X[t][u][v][3]-Wmin)/(Wmax-Wmin)));
            }
        }
    }
}

/// Re-initialize a RealFunction if the definition set has changed
/** \param _tmin minimal value in t
 *  \param _tmax maximal value in t
 *  \param _dt stepsize in t
 *  \param _umin minimal value in u
 *  \param _umax maximal value in u
 *  \param _du stepsize in u
 *  \param _vmin minimal value in v
 *  \param _vmax maximal value in v
 *  \param _dv stepsize in v                                              */
void RealFunction::ReInit(double tmin, double tmax, double dt,
                          double umin, double umax, double du,
                          double vmin, double vmax, double dv) {

    SingletonLog::Instance()  << "Function::ReInit(" << tmin << ", " << tmax << ", " << dt << ", "
	<< umin << ", " << umax<< ", " << du << ", " << vmin << ", " << vmax << ", " << dv << ")\n";

  getTmin() = tmin;   getTmax() = tmax;   getDt() = dt;
  getUmin() = umin;   getUmax() = umax;   getDu() = du;
  getVmin() = vmin;   getVmax() = vmax;   getDv() = dv;
  getTsteps() = unsigned ((getTmax()-getTmin())/getDt()+2);
  getUsteps() = unsigned ((getUmax()-getUmin())/getDu()+2);
  getVsteps() = unsigned ((getVmax()-getVmin())/getDv()+2);

  Initialize ();
}

/// Transforms a RealFunction
/** \todo As I look at it, i think this could be optimized by making the
 *        transformation matrices static and only canging the corresponding
 *        entries... but how to do this beautifully, i don't know
 *  \param R rotation
 *  \param T translation                                                      */
void RealFunction::Transform (const VecMath::Rotation<4> &R,
                              const VecMath::Vector<4> &T) {
    Matrix<4> Rot(R);
    transform< vec4vec3D, 4 >::xform(Rot, T, _X, _Xtrans);
}

void RealFunction::setDepthCueColors(double Wmax, double Wmin) {
    for(unsigned t = 0;t <= getTsteps() + 1;t++) {
        for(unsigned u = 0;u <= getUsteps() + 1;u++) {
            for(unsigned v = 0;v <= getVsteps() + 1;v++){
                ColMgrMgr::Instance().depthCueColor(Wmax, Wmin,
                                                    _Xtrans[t][u][v][3],
                                                    _X[t][u][v]);
            }
        }
    }
}

/// Projects a RealFunction into three-space
/** \param scr_w w coordinate of screen
 *  \param cam_w w coordinate of camera
 *  \param depthcue4d whether to use hyperfog/depth cue                       */
void RealFunction::Project (double scr_w, double cam_w, bool depthcue4d) {
    double ProjectionFactor;
    double Wmax = 0, Wmin = 0;

    for (unsigned t = 0; t <= getTsteps()+1; t++) {
        for (unsigned u = 0; u <= getUsteps()+1; u++) {
            for (unsigned v = 0; v <= getVsteps()+1; v++) {

                if (_Xtrans[t][u][v][3] < Wmin) Wmin = _Xtrans[t][u][v][3];
                if (_Xtrans[t][u][v][3] > Wmax) Wmax = _Xtrans[t][u][v][3];

                ProjectionFactor = (scr_w-cam_w)/(_Xtrans[t][u][v][3]-cam_w);

                for (unsigned i = 0; i <= 2; i++) {
                    _Xscr[t][u][v][i] = ProjectionFactor*_Xtrans[t][u][v][i];
                }
            }
        }
    }

    if (depthcue4d) setDepthCueColors(Wmax, Wmin);
}

/// Draw the projected Function (onto screen or into GL list, as it is)
/** */
void RealFunction::Draw (void) {
    for (unsigned t = 0; t < getTsteps(); t++)
        DrawPlane (t);
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

using std::string;
using std::setw;
using std::setprecision;
/// Draw the current cube or cell of the projected Function
/** \param t current t value
 *  \param u current u value
 *  \param v current v value                                                  */
void RealFunction::DrawCube (unsigned t, unsigned u, unsigned v) {
    static Vector<3> *V = new Vector<3> [8];

    V[0] = _Xscr[t][u][v];     V[1] = _Xscr[t][u][v+1];
    V[2] = _Xscr[t][u+1][v];   V[3] = _Xscr[t][u+1][v+1];
    V[4] = _Xscr[t+1][u][v];   V[5] = _Xscr[t+1][u][v+1];
    V[6] = _Xscr[t+1][u+1][v]; V[7] = _Xscr[t+1][u+1][v+1];

    glBegin (GL_QUAD_STRIP);
    if (t == 0) {
        setVertex(_X[t][u][v], V[0]);
        setVertex(_X[t][u][v+1], V[1]);
        addVertices(2);
    }
    setVertex(_X[t][u+1][v], V[2]);
    setVertex(_X[t][u+1][v+1], V[3]);
    setVertex(_X[t+1][u+1][v], V[6]);
    setVertex(_X[t+1][u+1][v+1], V[7]);
    setVertex(_X[t+1][u][v], V[4]);
    setVertex(_X[t+1][u][v+1], V[5]);
    addVertices(6);
    if (u == 0) {
        setVertex(_X[t][u][v], V[0]);
        setVertex(_X[t][u][v+1], V[1]);
        addVertices(2);
    }
    glEnd ();

    glBegin (GL_QUADS);
    if (v == 0) {
        setVertex(_X[t][u][v], V[0]);
        setVertex(_X[t][u+1][v], V[2]);
        setVertex(_X[t+1][u+1][v], V[6]);
        setVertex(_X[t+1][u][v], V[4]);
        addVertices(4);
    }
    setVertex(_X[t][u][v+1], V[1]);
    setVertex(_X[t][u+1][v+1], V[3]);
    setVertex(_X[t+1][u+1][v+1], V[7]);
    setVertex(_X[t+1][u][v+1], V[5]);
    addVertices(4);
    glEnd ();
}


////////////////////////////////////////////////////////////////////////////////


/// Hypersphere c'tor given a definition set in R� (as parameter space) and a
/// radius
/** \param _tmin minimal value in t
 *  \param _tmax maximal value in t
 *  \param _dt stepsize in t
 *  \param _umin minimal value in u
 *  \param _umax maximal value in u
 *  \param _du stepsize in u
 *  \param _vmin minimal value in v
 *  \param _vmax maximal value in v
 *  \param _dv stepsize in v
 *  \param _rad radius                                                        */
Hypersphere::Hypersphere(double tmin, double tmax, double dt,
                         double umin, double umax, double du,
                         double vmin, double vmax, double dv,
                         double rad):
        RealFunction ("Hypersphere",
                      tmin, tmax, dt, umin, umax, du, vmin, vmax, dv),
        _radius (rad) {
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

/// Hypersphere defining function
/** \param tt		t value
 *  \param uu		u value
 *  \param vv		v value
 *  \return		value of defining function at point in question
 */
Vector<4> &Hypersphere::f (double tt, double uu, double vv) {
  double sinphi = sin (pi/2*tt), cosphi = cos (pi/2*tt),	//  hypersphere
    sintht = sin (pi*uu), costht = cos (pi*uu),
    sinpsi = sin (pi*vv), cospsi = cos (pi*vv);
  _F[0] = _radius*sinpsi*sintht*cosphi;
  _F[1] = _radius*sinpsi*sintht*sinphi;
  _F[2] = _radius*sinpsi*costht;
  _F[3] = _radius*cospsi;

  return _F;
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

  n = f (tt, uu, vv);
  VecMath::vnormalize (n);

  return n;
}


///////////////////////////////////////////////////////////////////////////////


/** Torus1 c'tor given a definition set in R� (as parameter space) and three
 *  radii: major, minor and... what'sitcalled... subminor
 *  \param _tmin	minimal value in t
 *  \param _tmax	maximal value in t
 *  \param _dt		stepsize in t
 *  \param _umin	minimal value in u
 *  \param _umax	maximal value in u
 *  \param _du		stepsize in u
 *  \param _vmin	minimal value in v
 *  \param _vmax	maximal value in v
 *  \param _dv		stepsize in v
 *  \param _R		major radius
 *  \param _r		minor radius
 *  \param _rho		subminor radius */
Torus1::Torus1 (double tmin, double tmax, double dt,
		double umin, double umax, double du,
		double vmin, double vmax, double dv,
		double R, double r, double rho):
    RealFunction ("Torus 1",
                tmin, tmax, dt, umin, umax, du, vmin, vmax, dv),
    _R (R), _r (r), _rho (rho) {
      declareParameter("Major Radius", 2.0);
      declareParameter("Minor Radius", 1.0);
      declareParameter("Micro Radius", 0.5);
      Initialize ();
}

/** Torus1 defining function
 *  \param tt t value
 *  \param uu u value
 *  \param vv v value
 *  \return value of defining function at point in question                   */
Vector<4> &Torus1::f (double tt, double uu, double vv) {
    _F[0] =  cos (pi*tt)*(_R+cos (pi*uu)*(_r+_rho*cos (pi*vv)));
    _F[1] =  sin (pi*tt)*(_R+cos (pi*uu)*(_r+_rho*cos (pi*vv)));
    _F[2] =  sin (pi*uu)*(_r+_rho*cos (pi*vv));
    _F[3] =  _rho*sin (pi*vv);

    return _F;
}


///////////////////////////////////////////////////////////////////////////////


/** Torus2 c'tor given a definition set in R³ (as parameter space) and two
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
  RealFunction ("Torus 2",
                tmin, tmax, dt, umin, umax, du, vmin, vmax, dv),
  _R (R), _r (r) {
    declareParameter("Major Radius", 1.0);
    declareParameter("Minor Radius", 0.5);

      Initialize ();
}

/** Torus2 defining function
 *  \param tt		t value
 *  \param uu		u value
 *  \param vv		v value
 *  \return		value of defining function at point in question
 */
Vector<4> &Torus2::f (double tt, double uu, double vv) {
  _F[0] =  cos (pi*tt)*(_R+_r*cos (pi*uu)*cos (pi*vv));
  _F[1] =  cos (pi*tt)*(_R+_r*cos (pi*uu)*sin (pi*vv));
  _F[2] =  cos (pi*tt)*(_R+_r*sin (pi*uu));
  _F[3] =  sin (pi*tt)*_R;

  return _F;
}


////////////////////////////////////////////////////////////////////////////////


/** Fr3r (example R³->R function) c'tor given a definition set in R³
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
    RealFunction ("1/(r²+1)",
                  tmin, tmax, dt, umin, umax, du, vmin, vmax, dv) {
  Initialize ();
}

/** Fr3r defining function
 *  \param tt		t value
 *  \param uu		u value
 *  \param vv		v value
 *  \return		value of defining function at point in question
 */
Vector<4> &Fr3r::f (double tt, double uu, double vv) {
  _F[0] = tt;
  _F[1] = uu;
  _F[2] = vv;
  double rsq = tt*tt+uu*uu+vv*vv;
  _F[3] = 1./(rsq+.25);
  // sin (pi*(tt*tt+uu*uu+vv*vv));
  // exp (tt*tt+uu*uu+vv*vv);

  return _F;
}


////////////////////////////////////////////////////////////////////////////////


/** GravitationPotential c'tor given a definition set in R³ (as parameter space),
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
 *  \param _M   Mass of the generating sphere
 *  \param _R   Radius of the generating sphere
 */
GravitationPotential::GravitationPotential (double xmin, double xmax, double dx,
                                            double ymin, double ymax, double dy,
                                            double zmin, double zmax, double dz,
                                            double M, double R):
        RealFunction ("Gravitation Potential",
                      xmin, xmax, dx, ymin, ymax, dy, zmin, zmax, dz),
  _M (M), _R (R) {
      declareParameter("M", 1.0);
      declareParameter("R", 0.25);
      Initialize ();
}

/** GravitationPotential defining function
 *  \param tt   t value
 *  \param uu   u value
 *  \param vv   v value
 *  \return     value of defining function at point in question
 */
Vector<4> &GravitationPotential::f (double tt, double uu, double vv) {
  const double G = 1;		//  arbitrary value for gravitation constant
  _F[0] = tt;
  _F[1] = uu;
  _F[2] = vv;
  double rsq = tt*tt+uu*uu+vv*vv;
  if (rsq > _R*_R)
    _F[3] = G*_M/rsq;
  else
    _F[3] = G*_M/(_R*_R*_R)*sqrt (rsq);

  return _F;
}


///////////////////////////////////////////////////////////////////////////////


/** Fr3rSin c'tor given a definition set in R� (as parameter space)
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
        RealFunction ("sin (r²)",
                      tmin, tmax, dt, umin, umax, du, vmin, vmax, dv) {
  Initialize ();
}

/** Fr3rSin defining function
 *  \param tt		t value
 *  \param uu		u value
 *  \param vv		v value
 *  \return		sin (pi*(x�+y�+z�))
 */
Vector<4> &Fr3rSin::f (double tt, double uu, double vv) {
  _F[0] = tt;
  _F[1] = uu;
  _F[2] = vv;
  _F[3] = sin (pi*(tt*tt+uu*uu+vv*vv));

  return _F;
}


///////////////////////////////////////////////////////////////////////////////


/** Fr3rExp c'tor given a definition set in R� (as parameter space)
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
        RealFunction ("exp (r²)",
                      tmin, tmax, dt, umin, umax, du, vmin, vmax, dv) {
  Initialize ();
}

/** Fr3rExp defining function
 *  \param tt		t value
 *  \param uu		u value
 *  \param vv		v value
 *  \return		exp (x�+y�+z�)
 */
Vector<4> &Fr3rExp::f (double tt, double uu, double vv) {
  _F[0] = tt;
  _F[1] = uu;
  _F[2] = vv;
  _F[3] = exp (tt*tt+uu*uu+vv*vv);

  return _F; }


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
  RealFunction ("Polar: Hypersphere",
                tmin, tmax, dt, umin, umax, du, vmin, vmax, dv) {
  Initialize ();
}

/** Polar defining function
 *  \param tt		t value
 *  \param uu		u value
 *  \param vv		v value
 *  \return		value of defining function at point in question
 */
Vector<4> &Polar::f (double tt, double uu, double vv) {
  double sinphi = sin (pi*tt), cosphi = cos (pi*tt),
    sintht = sin (pi*uu), costht = cos (pi*uu),
    sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
    Radius = sin (pi/3.*(tt+uu+vv));

  _F[0] = Radius*sinpsi*sintht*cosphi;
  _F[1] = Radius*sinpsi*sintht*sinphi;
  _F[2] = Radius*sinpsi*costht;
  _F[3] = Radius*cospsi;

  return _F;
}


///////////////////////////////////////////////////////////////////////////////


/** PolarSin c'tor given a definition set in R³ (as parameter space) and a
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
        RealFunction ("Polar: r = 1/2+sin (Phase*pi*t*u*v)",
                      tmin, tmax, dt, umin, umax, du, vmin, vmax, dv),
    _phase (phase) {
    declareParameter("Phase", 2.0);
    Initialize ();
}

/** PolarSin defining function
 *  \param tt		t value
 *  \param uu		u value
 *  \param vv		v value
 *  \return		r = 1/2 + |sin (pi*phase*theta*phi*psi)|
 */
Vector<4> &PolarSin::f (double tt, double uu, double vv) {
  double sinphi = sin (pi*tt), cosphi = cos (pi*tt),
    sintht = sin (pi*uu), costht = cos (pi*uu),
    sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
    Radius = .5+fabs (sin (_phase*tt*uu*vv*pi));

  _F[0] = Radius*sinpsi*sintht*cosphi;
  _F[1] = Radius*sinpsi*sintht*sinphi;
  _F[2] = Radius*sinpsi*costht;
  _F[3] = Radius*cospsi;

  return _F;
}


///////////////////////////////////////////////////////////////////////////////


/** PolarSin2 c'tor given a definition set in R³ (as parameter space)
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
        RealFunction ("Polar: r = sin (pi/3.*(t+u+v))",
                      tmin, tmax, dt, umin, umax, du, vmin, vmax, dv) {
    Initialize ();
}

/** PolarSin2 defining function
 *  \param tt		t value
 *  \param uu		u value
 *  \param vv		v value
 *  \return		r = sin (pi/3*(phi+theta+psi))
 */
Vector<4> &PolarSin2::f (double tt, double uu, double vv) {
  double sinphi = sin (pi*tt), cosphi = cos (pi*tt),
    sintht = sin (pi*uu), costht = cos (pi*uu),
    sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
    Radius = sin (pi/3.*(tt+uu+vv));

  _F[0] = Radius*sinpsi*sintht*cosphi;
  _F[1] = Radius*sinpsi*sintht*sinphi;
  _F[2] = Radius*sinpsi*costht;
  _F[3] = Radius*cospsi;

  return _F;
}


///////////////////////////////////////////////////////////////////////////////


/** PolarR c'tor given a definition set in R³ (as parameter space) and a
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
        RealFunction ("Polar: r = sqrt (t²+u²+v²)",
                      tmin, tmax, dt, umin, umax, du, vmin, vmax, dv),
        _phase (phase) {
      declareParameter("Phase", 2.0);
  Initialize ();
}

/** PolarR defining function
 *  \param tt		t value
 *  \param uu		u value
 *  \param vv		v value
 *  \return		r = sqrt (phi�+theta�+psi�)
 */
Vector<4> &PolarR::f (double tt, double uu, double vv) {
  double sinphi = sin (pi*tt), cosphi = cos (pi*tt),
    sintht = sin (pi*uu), costht = cos (pi*uu),
    sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
    Radius = sqrt (tt*tt+uu*uu+vv*vv);

  _F[0] = Radius*sinpsi*sintht*cosphi;
  _F[1] = Radius*sinpsi*sintht*sinphi;
  _F[2] = Radius*sinpsi*costht;
  _F[3] = Radius*cospsi;

  return _F;
}
