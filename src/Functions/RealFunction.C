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

#include "Globals.H"
#include "Log.H"
#include "ColorManager.H"

#include "Vector.H"
#include "Matrix.H"
#include "RealFunction.H"

using std::cerr;
using std::endl;

using VecMath::Vector;
using VecMath::Matrix;

/** RealFunction c'tor given a definition set in R³ (as parameter space)
 *  @param name a name for the function
 *  @param _tmin minimal value in t
 *  @param _tmax maximal value in t
 *  @param _dt stepsize in t
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                                  */
RealFunction::RealFunction(const QString &name,
                           double _tmin, double _tmax, double _dt,
                           double _umin, double _umax, double _du,
                           double _vmin, double _vmax, double _dv,
                           parameterMap _parms):
        RealBase(name, _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv,
                 _parms),
        Xtrans(vec4vec3D()), Xscr(vec3vec3D()) {
    if (MemRequired () > Globals::Instance().getMaxMemory()) {
        cerr << "Using a " << tsteps << "x" << usteps << "x" << vsteps
             << " grid would require approx. " << MemRequired () << " MB of memory.\n";
        while (MemRequired () > Globals::Instance().getMaxMemory()) {
            tsteps--; usteps--; vsteps--;
        }
        cerr << "Using a " << tsteps << "x" << usteps << "x" << vsteps
             << " grid instead." << endl;
        dt = (tmax-tmin)/tsteps;
        du = (umax-umin)/usteps;
        dv = (vmax-vmin)/vsteps;
    }
}

/// Initialize the temporary storage areas
/** Xscr[][][], Xtrans[][][]                */
void RealFunction::InitMem (void) {

    Xscr.resize(tsteps+2);
    Xtrans.resize(tsteps+2);

    for (unsigned t = 0; t <= tsteps+1; t++) {

        Xscr[t].resize(usteps+2);
        Xtrans[t].resize(usteps+2);

        for (unsigned u = 0; u <= usteps+1; u++) {

            Xscr[t][u].resize(vsteps+2);
            Xtrans[t][u].resize(vsteps+2);
        }                           //  for (unsigned u = 0; u <= usteps+1; u++)

    }                               //  for (unsigned t = 0; t <= tsteps+1; t++)
}                                   //  InitMem ()

/// Allocate and initialize X[][][] with values of f()
/** Call InitMem() above */
void RealFunction::Initialize () {
    double Wmin = 0., Wmax = 0.;
    X = vec4vec3D(tsteps+2);
    ColMgrMgr::Instance().setFunction(this);

    for (unsigned t = 0; t <= tsteps+1; t++) {
        X[t].resize(usteps+2);

        for (unsigned u = 0; u <= usteps+1; u++) {
            X[t][u].resize(vsteps+2);

            for (unsigned v = 0; v <= vsteps+1; v++) {
                double T = tmin+t*dt, U =umin+u*du, V = vmin+v*dv;
                X[t][u][v] = f (T, U, V);
                if (X[t][u][v][3] < Wmin) Wmin = X[t][u][v][3];
                if (X[t][u][v][3] > Wmax) Wmax = X[t][u][v][3];
            }
        }
    }

    for (unsigned t = 0; t <= tsteps+1; t++) {
        for (unsigned u = 0; u <= usteps+1; u++) {
            for (unsigned v = 0; v <= vsteps+1; v++) {
                ColMgrMgr::Instance().calibrateColor(
                    X[t][u][v],
                    Color(float(t)/float(tsteps), float(u)/float(usteps),
                          float(v)/float(vsteps),
                          (X[t][u][v][3]-Wmin)/(Wmax-Wmin)));
            }
        }
    }
    InitMem ();
}

/// Re-initialize a RealFunction if the definition set has changed
/** @param tmin minimal value in t
 *  @param tmax maximal value in t
 *  @param dt stepsize in t
 *  @param umin minimal value in u
 *  @param umax maximal value in u
 *  @param du stepsize in u
 *  @param vmin minimal value in v
 *  @param vmax maximal value in v
 *  @param dv stepsize in v                                                   */
void RealFunction::ReInit(double _tmin, double _tmax, double _dt,
                      double _umin, double _umax, double _du,
                      double _vmin, double _vmax, double _dv) {

    SingletonLog::Instance()  << "Function::ReInit(" << _tmin << ", " << _tmax << ", " << _dt << ", "
	<< _umin << ", " << _umax<< ", " << _du << ", " << _vmin << ", " << _vmax << ", " << _dv << ")\n";

  tmin = _tmin;   tmax = _tmax;   dt = _dt;
  umin = _umin;   umax = _umax;   du = _du;
  vmin = _vmin;   vmax = _vmax;   dv = _dv;
  tsteps = unsigned ((tmax-tmin)/dt+2); usteps = unsigned ((umax-umin)/du+2); vsteps = unsigned ((vmax-vmin)/dv+2);

  Initialize ();
}

/// Transforms a RealFunction
/** \todo As I look at it, i think this could be optimized by making the
 *        transformation matrices static and only canging the corresponding
 *        entries... but how to do this beautifully, i don't know
 *  @param thetaxy rotation around xy plane (z axis); should be ignored because
 *                 3D rotation takes care of it, but isn't
 *  @param thetaxz rotation around xz plane (y axis); should be ignored because
 *                 3D rotation takes care of it, but isn't
 *  @param thetaxw rotation around xw plane
 *  @param thetayz rotation around xy plane (x axis); should be ignored because
 *                 3D rotation takes care of it, but isn't
 *  @param thetayw rotation around yw plane
 *  @param thetazw rotation around zw plane
 *  @param tx translation in x direction
 *  @param ty translation in y direction
 *  @param tz translation in z direction
 *  @param tw translation in w direction                                      */
void RealFunction::Transform (double thetaxy, double thetaxz, double thetaxw,
                          double thetayz, double thetayw, double thetazw,
                          double tx, double ty, double tz, double tw) {
    Matrix<4> Rxy = Matrix<4> (0, 1, thetaxy), Rxz = Matrix<4> (0, 2, thetaxz),
              Rxw = Matrix<4> (0, 3, thetaxw), Ryz = Matrix<4> (1, 2, thetayz),
              Ryw = Matrix<4> (1, 3, thetayw), Rzw = Matrix<4> (2, 3, thetazw),
              Rxyz = Rxy*Rxz, Rxwyz = Rxw*Ryz, Ryzw = Ryw*Rzw,
              Rot = Rxyz*Rxwyz*Ryzw;
    Vector<4> trans = Vector<4>(tx, ty, tz, tw);

    for (unsigned t = 0; t <= tsteps+1; t++)
        for (unsigned u = 0; u <= usteps+1; u++)
            for (unsigned v = 0; v <= vsteps+1; v++)
                Xtrans[t][u][v] = (Rot*X[t][u][v])+trans;
}

/// Projects a Function into three-space
/** @param scr_w w coordinate of screen
 *  @param cam_w w coordinate of camera
 *  @param depthcue4d whether to use hyperfog/depth cue                       */
void RealFunction::Project (double scr_w, double cam_w, bool depthcue4d) {
    double ProjectionFactor;
    double Wmax = 0, Wmin = 0;

    for (unsigned t = 0; t <= tsteps+1; t++) {
        for (unsigned u = 0; u <= usteps+1; u++) {
            for (unsigned v = 0; v <= vsteps+1; v++) {

                if (Xtrans[t][u][v][3] < Wmin) Wmin = Xtrans[t][u][v][3];
                if (Xtrans[t][u][v][3] > Wmax) Wmax = Xtrans[t][u][v][3];

                ProjectionFactor = (scr_w-cam_w)/(Xtrans[t][u][v][3]-cam_w);

                for (unsigned i = 0; i <= 2; i++) {
                    Xscr[t][u][v][i] = ProjectionFactor*Xtrans[t][u][v][i];
                }
            }
        }
    }

    if (!depthcue4d) return;

    for (unsigned t = 0; t <= tsteps+1; t++)
        for (unsigned u = 0; u <= usteps+1; u++)
            for (unsigned v = 0; v <= vsteps+1; v++) {
                ColMgrMgr::Instance().depthCueColor(Wmax, Wmin,
                    Xtrans[t][u][v][3], X[t][u][v]);
            }
}

/// Draw the projected Function (onto screen or into GL list, as it is)
/** */
void RealFunction::Draw (void) {
    for (unsigned t = 0; t < tsteps; t++)
        DrawPlane (t);
}

/// Calculate normal to function at a given point in definition set.
/** No further assumption is made than that f () is continuous. \n
 *  This function is not yet used anywhere, but i like it.
 *  @param tt t value
 *  @param uu u value
 *  @param vv v value
 *  @return surface normal, normalized                                        */
Vector<4> &RealFunction::normal (double tt, double uu, double vv) {
    static Vector<4> n;

    Function::vec4vec1D D = df (tt, uu, vv);

    n = VecMath::vcross (D[0], D[1], D[2]);
    VecMath::vnormalize (n);

    return n;
}

/// Draw the current plane of the projected Function
/** @param t current t value                                                  */
void RealFunction::DrawPlane (unsigned t){
    for (unsigned u = 0; u < usteps; u++)
        DrawStrip (t, u);
}

/// Draw the current strip of the projected Function
/** @param t current t value
 *  @param u current u value                                                  */
void RealFunction::DrawStrip (unsigned t, unsigned u){
    for (unsigned v = 0; v < vsteps; v++)
        DrawCube (t, u, v);
}

using std::string;
using std::setw;
using std::setprecision;
/// Draw the current cube or cell of the projected Function
/** @param t current t value
 *  @param u current u value
 *  @param v current v value                                                  */
void RealFunction::DrawCube (unsigned t, unsigned u, unsigned v) {
    static Vector<3> *V = new Vector<3> [8];

    V[0] = Xscr[t][u][v];     V[1] = Xscr[t][u][v+1];
    V[2] = Xscr[t][u+1][v];   V[3] = Xscr[t][u+1][v+1];
    V[4] = Xscr[t+1][u][v];   V[5] = Xscr[t+1][u][v+1];
    V[6] = Xscr[t+1][u+1][v]; V[7] = Xscr[t+1][u+1][v+1];

    glBegin (GL_QUAD_STRIP);
    if (t == 0) {
        setVertex(X[t][u][v], V[0]);
        setVertex(X[t][u][v+1], V[1]);
        addVertices(2);
    }
    setVertex(X[t][u+1][v], V[2]);
    setVertex(X[t][u+1][v+1], V[3]);
    setVertex(X[t+1][u+1][v], V[6]);
    setVertex(X[t+1][u+1][v+1], V[7]);
    setVertex(X[t+1][u][v], V[4]);
    setVertex(X[t+1][u][v+1], V[5]);
    addVertices(6);
    if (u == 0) {
        setVertex(X[t][u][v], V[0]);
        setVertex(X[t][u][v+1], V[1]);
        addVertices(2);
    }
    glEnd ();

    glBegin (GL_QUADS);
    if (v == 0) {
        setVertex(X[t][u][v], V[0]);
        setVertex(X[t][u+1][v], V[2]);
        setVertex(X[t+1][u+1][v], V[6]);
        setVertex(X[t+1][u][v], V[4]);
        addVertices(4);
    }
    setVertex(X[t][u][v+1], V[1]);
    setVertex(X[t][u+1][v+1], V[3]);
    setVertex(X[t+1][u+1][v+1], V[7]);
    setVertex(X[t+1][u][v+1], V[5]);
    addVertices(4);
    glEnd ();
}


////////////////////////////////////////////////////////////////////////////////


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
Hypersphere::Hypersphere(double _tmin, double _tmax, double _dt,
                         double _umin, double _umax, double _du,
                         double _vmin, double _vmax, double _dv,
                         double _rad):
        RealFunction ("Hypersphere",
                      _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
        Radius (_rad) {
    newParameterName("Radius");
    insertParameter(
        std::make_pair("Radius", new FunctionParameter<double>(1.0)));
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
    RealFunction ("Torus 1",
                _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
    R (_R), r (_r), rho (_rho) {
      newParameterName("Major Radius");
      newParameterName("Minor Radius");
      newParameterName("Micro Radius");
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
  RealFunction ("Torus 2",
                _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
  R (_R), r (_r) {
      newParameterName("Major Radius");
      newParameterName("Minor Radius");

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
    RealFunction ("1/(r²+1)",
                  _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
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
        RealFunction ("Gravitation Potential",
                      xmin, xmax, dx, ymin, ymax, dy, zmin, zmax, dz),
  M (_M), R (_R) {
      newParameterName("M");
      newParameterName("R");
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
        RealFunction ("sin (r²)",
                      _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
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
        RealFunction ("exp (r²)",
                      _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
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
  RealFunction ("Polar: Hypersphere",
                _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
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
        RealFunction ("Polar: r = sin (pi/3.*(t+u+v))",
                      _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
    newParameterName("Phase");
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
      newParameterName("Phase");
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
