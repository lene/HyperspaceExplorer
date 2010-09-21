
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//      author:       helge preuss (lene.preuss@gmail.com)
//      license:      GPL (see License.txt)


#include "Globals.h"
#include "ColorManager.h"

#include "Matrix.h"

#include "Surface.h"

#include "Transformation.h"
#include "Projection.h"


using VecMath::NestedVector;
using VecMath::Vector;
using VecMath::Matrix;
using std::tr1::shared_ptr;

////////////////////////////////////////////////////////////////////////////////

double SurfaceBase::_min = -1.;
double SurfaceBase::_max =  1.;
double SurfaceBase::_d = 0.1;


/// Surface default c'tor, zeroes everything
Surface::Surface (): SurfaceBase(_min, _max, _d, _min, _max, _d) { }


/** Surface c'tor given a definition set in \f$ R^2 \f$ (as parameter space)
 *  \param _umin minimal value in u
 *  \param _umax maximal value in u
 *  \param _du stepsize in u
 *  \param _vmin minimal value in v
 *  \param _vmax maximal value in v
 *  \param _dv stepsize in v
 *  \param _parms Parameter for the function                                  */
Surface::Surface (double _umin, double _umax, double _du,
                  double _vmin, double _vmax, double _dv,
                  ParameterMap _parms):
    SurfaceBase(_umin, _umax, _du, _vmin, _vmax, _dv, _parms) { }

/// allocate and initialize X[][] with values of f()
/** call InitMem () above                                                     */
void Surface::Initialize () {

    _X = FunctionValueGrid<4, 2>(_function,
                                         Vector<2, unsigned>(getTsteps()+2, getUsteps()+2),
                                         Vector<2>(getTmin(), getUmin()),
                                         Vector<2>(getTmax(), getUmax()));

    calibrateColors();
}

void Surface::calibrateColors() const {

  std::pair< double, double > Wext = findExtremesInW();

  for (unsigned t = 0; t <= getTsteps()+1; t++) {
        for (unsigned u = 0; u <= getUsteps()+1; u++) {
            ColMgrMgr::Instance().calibrateColor(
                X()[t][u],
                Color(float(t)/float(getTsteps()), float(u)/float(getUsteps()),
                      (Wext.second-X()[t][u][3])/(Wext.second-Wext.first)));
        }
    }
}

/** \return Maxima and minima in the W dimension
 */
std::pair< double, double > Surface::findExtremesInW() const {
  double Wmax = 0, Wmin = 0;

  for (unsigned t = 0; t <= getTsteps()+1; t++) {
    for (unsigned u = 0; u <= getUsteps()+1; u++) {
      if (X()[t][u][3] < Wmin) Wmin = X()[t][u][3];
      if (X()[t][u][3] > Wmax) Wmax = X()[t][u][3];
    }
  }

  return std::make_pair(Wmin, Wmax);
}

/** re-initialize a Surface if the definition set has changed
 *  @param _tmin minimal value in t (ignored)
 *  @param _tmax maximal value in t (ignored)
 *  @param _dt stepsize in t (ignored)
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u                                                  */
void Surface::ReInit(double, double, double,
                     double _tmin, double _tmax, double _dt,
                     double _umin, double _umax, double _du) {
  setBoundariesAndStepwidth(_tmin, _tmax, _dt, _umin, _umax, _du);

  Initialize ();

}

/** \param tmin minimal value in t
 *  \param tmax maximal value in t
 *  \param dt stepsize in t
 *  \param umin minimal value in u
 *  \param umax maximal value in u
 *  \param du stepsize in u
 */
void Surface::setBoundariesAndStepwidth(double tmin, double tmax, double dt,
                                        double umin, double umax, double du) {
    getTmin() = tmin; getTmax() = tmax; getDt() = dt;
    getUmin() = umin; getUmax() = umax; getDu() = du;
    getTsteps() = unsigned ((getTmax()-getTmin())/getDt()+1);
    getUsteps() = unsigned ((getUmax()-getUmin())/getDu()+1);
}

/// return the approximate amount of memory needed to display a Function of current definition set
/** \todo uses hardcoded and experimentally found value for memory per cell
 *  @return approx. mem required                                              */
unsigned long Surface::MemRequired (void) {
    return (getTsteps()+2)*(getUsteps()+2);
}

/// calculate normal to function at a given point in definition set
/** no further assumption is made than that f () is continuous
 *
 *  this function is not yet used anywhere, but i like it
 *  @param uu u value
 *  @param vv v value
 *  @return surface normal, normalized                                        */
Vector<4> &Surface::normal (double uu, double vv) {
    static Vector<4> n;

    Function::vec4vec1D D = df(uu, vv);

    n = VecMath::vcross(D[0], D[1], D[2]);
    VecMath::vnormalize(n);

    return n;
}

/** numerical calculation of the derivatives in u and v:
    \f[
        \frac{df}{du} = \lim_{h \rightarrow 0}
            \frac{f(u+h, v) - f(u, v)}{h},
        \frac{df}{dv}\mbox{analogously}
    \f]
 *
 *  @param uu u value
 *  @param vv v value
 *  @return gradient in t, u and v as array                                   */
Function::vec4vec1D Surface::df (double uu, double vv) {

    static Vector<4> F0, F;        //  f (u, v)
    static double h = 1e-5;     //  maybe tweak to get best results

    static Function::vec4vec1D DF(3);

    F0 = operator() (uu, vv);

    F = operator() (uu+h, vv); //  derive after u
    DF[0] = (F-F0)/h;
    F = operator() (uu, vv+h); //  derive after v
    DF[1] = (F-F0)/h;
    DF[2] = (F-F0)/h;           //  are you sure this is correct?

    return DF;
}

/// Transforms a Surface
/** \param R rotation
 *  \param T translation                                                      */
void Surface::Transform (const VecMath::Rotation<4> &R, const VecMath::Vector<4> &T) {
  Transformation<4, 2> xform(R, T);
  _Xtrans = xform.transform(_X.getValues());
}

/** projects a Surface into three-space
 *  \param scr_w w coordinate of screen
 *  \param cam_w w coordinate of camera
 *  \param depthcue4d whether to use hyperfog/depth cue                        */
void Surface::Project (double scr_w, double cam_w, bool depthcue4d) {

    Projection<4, 3, 2> p(scr_w, cam_w, depthcue4d);
    _Xscr = p.project(Xtrans());

    if (depthcue4d) {
        std::pair< double, double > Wext = findExtremesInW();
        for (unsigned t = 0; t <= getTsteps()+1; t++) {
            for (unsigned u = 0; u <= getUsteps()+1; u++) {
                ColMgrMgr::Instance().depthCueColor(Wext.first, Wext.second,
                                                    Xtrans()[t][u][3],
                                                    X()[t][u]);
            }
        }
    }

}


/** draw the projected Surface (onto screen or into GL list, as it is)        */
void Surface::Draw (UI::View *view) {
    for (unsigned t = 0; t <= getTsteps(); t++)
        DrawStrip (t);
}


/** draw the current strip of the projected Surface
 *  @param t current t value                                                  */
void Surface::DrawStrip (unsigned t){
    glBegin (GL_QUAD_STRIP);

    for (unsigned u = 0; u <= getUsteps(); u++) {
        setVertex(X()[t][u], Xscr()[t][u]);
        setVertex(X()[t+1][u], Xscr()[t+1][u]);
    }

    setVertex(X()[t][0], Xscr()[t][0]);
    setVertex(X()[t+1][0], Xscr()[t+1][0]);

    glEnd ();
}

const NestedVector< Vector<4>, 2 > &Surface::X() const {
  return _X.getValues();
}

const NestedVector< Vector<4>, 2 > &Surface::Xtrans() const {
  return _Xtrans;
}

const VecMath::NestedVector< Vector< 3 >, 2 >& Surface::Xscr() const {
  return _Xscr;
}

///////////////////////////////////////////////////////////////////////////////


/** Surface1 c'tor given a definition set in \f$ R^2 \f$ (as parameter space)
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                                  */
Surface1::Surface1 (double _umin, double _umax, double _du,
                    double _vmin, double _vmax, double _dv):
        Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {

    _function = shared_ptr< ParametricFunction<4, 2> >(new DefiningFunction);
    Initialize();
}

Vector<4> Surface1::DefiningFunction::f (const Vector<2> &x) {
  double uu = x[0], vv = x[1];
  double sintht = sin (pi*uu), costht = cos (pi*uu),
         sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
         Radius = 1;
  Vector<4> F;
  F[0] = Radius*sintht*sinpsi;
  F[1] = Radius*costht*sinpsi;
  F[2] = Radius*costht;
  F[3] = Radius*cospsi;

  return F;
}



///////////////////////////////////////////////////////////////////////////////


/** Horizon c'tor given a definition set in \f$ R^2 \f$ (as parameter space)
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                                  */
Horizon::Horizon (double _umin, double _umax, double _du,
                  double _vmin, double _vmax, double _dv):
    Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {
    _function = shared_ptr< ParametricFunction<4, 2> >(new DefiningFunction);
    Initialize ();
}

Vector<4> Horizon::DefiningFunction::f (const Vector<2> &x) {
  double t = x[0]*pi, phi = x[1]*pi/2.;

  Vector<4> F;
  F[0] = (1-sin (t))*cos (phi);
  F[1] = (1-sin (t))*sin (phi);
  F[2] = (1+sin (t))*cos (phi);
  F[3] = (1+sin (t))*sin (phi);
  F *= 1./sqrt (2.)*cos (t);

  return F;
}

////////////////////////////////////////////////////////////////////////////////


/** Torus3 c'tor given a definition set in \f$ R^2 \f$ (as parameter space)
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                                  */
Torus3::Torus3 (double _umin, double _umax, double _du,
                double _vmin, double _vmax, double _dv):
        Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {
    _function = shared_ptr< ParametricFunction<4, 2> >(new DefiningFunction);
    Initialize ();
}

/** Torus3 defining function
 *  @param theta u value
 *  @param phi v value
 *  @return (costht, sintht, cosphi, sinphi)                                  */
Vector<4> Torus3::DefiningFunction::f (const Vector<2> &x) {
  double theta = x[0]*pi, phi = x[1]*pi;

  Vector<4> F;
  F[0] = cos (theta);
  F[1] = sin (theta);
  F[2] = cos (phi);
  F[3] = sin (phi);

  return F;
}
