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

#include "RealFunction.h"

#include "Transformation.h"
#include "Projection.h"
#include "GridDrawer.h"

#include "Vector.h"
#include "Matrix.h"

#include "Globals.h"
#include "Log.h"
#include "ColorManager.h"
#include "ScopedTimer.h"

#include <vector>

using std::cerr;
using std::endl;

using VecMath::NestedVector;
using VecMath::Vector;
using VecMath::Matrix;
using std::tr1::shared_ptr;

double RealFunctionDefinitionRange::min_ = -1.;
double RealFunctionDefinitionRange::max_ =  1.;
double RealFunctionDefinitionRange::d_ = 0.1;

struct RealFunction::Impl {
  
    Impl(double tmin, double tmax, double dt,
         double umin, double umax, double du,
         double vmin, double vmax, double dv): 
      definitionRange_(tmin, tmax, dt, umin, umax, du, vmin, vmax, dv) { }

      const VecMath::NestedVector< Vector< 4 >, 3 > &X() const { return _X.getValues(); }

      /// Initialize depth cue.
    void setDepthCueColors(double Wmax, double Wmin);

    /// Set up the grid using boundaries and stepwidth.
    void setBoundariesAndStepwidth(double tmin, double tmax, double dt,
                                   double umin, double umax, double du,
                                   double vmin, double vmax, double dv);

    /// Finds maximum and minimum function value in w.
    std::pair<double, double> findExtremesInW() const;

    void DrawPlane (unsigned, UI::View *view);
    void DrawStrip (unsigned, unsigned, UI::View *view);
    void DrawCube (unsigned, unsigned, unsigned, UI::View *view);
    
    RealFunctionDefinitionRange definitionRange_;
    /// Array of function values.
    FunctionValueGrid<4, 3> _X;
    /// Array of function values after transform.
    FunctionValueGrid<4, 3>::value_storage_type _Xtrans;
    /// Array of projected function values.
    VecMath::NestedVector< VecMath::Vector<3>, 3 > _Xscr;

};

void RealFunction::Impl::setDepthCueColors(double Wmax, double Wmin) {
  for(unsigned t = 0;t <= definitionRange_.getTsteps() + 1;t++) {
    for(unsigned u = 0;u <= definitionRange_.getUsteps() + 1;u++) {
      for(unsigned v = 0;v <= definitionRange_.getVsteps() + 1;v++){
        ColMgrMgr::Instance().depthCueColor(Wmax, Wmin,
                                            _Xtrans[t][u][v][3],
                                            X()[t][u][v]);
      }
    }
  }
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
void RealFunction::Impl::setBoundariesAndStepwidth(double tmin, double tmax, double dt,
                                             double umin, double umax, double du,
                                             double vmin, double vmax, double dv) {
  definitionRange_.setTmin(tmin);   definitionRange_.setTmax(tmax);   definitionRange_.setDt(dt);
  definitionRange_.setUmin(umin);   definitionRange_.setUmax(umax);   definitionRange_.setDu(du);
  definitionRange_.setVmin(vmin);   definitionRange_.setVmax(vmax);   definitionRange_.setDv(dv);
  definitionRange_.setTsteps(unsigned((definitionRange_.getTmax()-definitionRange_.getTmin())/definitionRange_.getDt()+2));
  definitionRange_.setUsteps(unsigned((definitionRange_.getUmax()-definitionRange_.getUmin())/definitionRange_.getDu()+2));
  definitionRange_.setVsteps(unsigned((definitionRange_.getVmax()-definitionRange_.getVmin())/definitionRange_.getDv()+2));
}

std::pair< double, double > RealFunction::Impl::findExtremesInW() const {

  double Wmin = 0., Wmax = 0.;
  for (unsigned t = 0; t < definitionRange_.getTsteps(); t++) {
    for (unsigned u = 0; u <= definitionRange_.getUsteps()+1; u++) {
      for (unsigned v = 0; v <= definitionRange_.getVsteps()+1; v++) {
        if (X()[t][u][v][3] < Wmin) Wmin = X()[t][u][v][3];
        if (X()[t][u][v][3] > Wmax) Wmax = X()[t][u][v][3];
      }
    }
  }

  return std::make_pair(Wmin, Wmax);
}


/// Draw the current plane of the projected Function
/** \param t current t value                                                  */
void RealFunction::Impl::DrawPlane (unsigned t, UI::View *view){
//  ScopedTimer timer("RealFunction::DrawPlane()");
  for (unsigned u = 0; u < definitionRange_.getUsteps(); u++)
    DrawStrip (t, u, view);
}

/// Draw the current strip of the projected Function
/** \param t current t value
 *  \param u current u value                                                  */
void RealFunction::Impl::DrawStrip (unsigned t, unsigned u, UI::View *view){
  for (unsigned v = 0; v < definitionRange_.getVsteps(); v++)
    DrawCube (t, u, v, view);
}

/// Draw the current cube or cell of the projected Function
/** \param t current t value
 *  \param u current u value
 *  \param v current v value                                                  */
void RealFunction::Impl::DrawCube (unsigned t, unsigned u, unsigned v, UI::View* view) {
    /// \todo don't use a malloc'ed pointer
    static Vector<3> *V = new Vector<3> [8];

    V[0] = _Xscr[t][u][v];     V[1] = _Xscr[t][u][v+1];
    V[2] = _Xscr[t][u+1][v];   V[3] = _Xscr[t][u+1][v+1];
    V[4] = _Xscr[t+1][u][v];   V[5] = _Xscr[t+1][u][v+1];
    V[6] = _Xscr[t+1][u+1][v]; V[7] = _Xscr[t+1][u+1][v+1];

    view->drawCube(X(), t, u, v,
                   V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);
}

/** RealFunction c'tor given only a name: All grid values are set to defaults
 */
RealFunction::RealFunction():
  Function(ParameterMap()),
    pImpl_(new Impl(
      RealFunctionDefinitionRange::min_, RealFunctionDefinitionRange::max_, RealFunctionDefinitionRange::d_, 
      RealFunctionDefinitionRange::min_, RealFunctionDefinitionRange::max_, RealFunctionDefinitionRange::d_, 
      RealFunctionDefinitionRange::min_, RealFunctionDefinitionRange::max_, RealFunctionDefinitionRange::d_)) { }
 
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
  Function(parms), pImpl_(new Impl(tmin, tmax, dt, umin, umax, du, vmin, vmax, dv)) {

  if (MemRequired () > Globals::Instance().getMaxMemory()) {
    cerr << "Using a " << pImpl_->definitionRange_.getTsteps() << "x" 
                       << pImpl_->definitionRange_.getUsteps() << "x" 
                       << pImpl_->definitionRange_.getVsteps()
         << " grid would require approx. " << MemRequired () << " MB of memory.\n";
    while (MemRequired () > Globals::Instance().getMaxMemory()) {
      pImpl_->definitionRange_.decrementTsteps(); 
      pImpl_->definitionRange_.decrementUsteps(); 
      pImpl_->definitionRange_.decrementVsteps();
    }
    cerr << "Using a " << pImpl_->definitionRange_.getTsteps() << "x" 
                       << pImpl_->definitionRange_.getUsteps() << "x" 
                       << pImpl_->definitionRange_.getVsteps()
         << " grid instead." << endl;
    pImpl_->definitionRange_.setDt((pImpl_->definitionRange_.getTmax()-pImpl_->definitionRange_.getTmin()) /
                                    pImpl_->definitionRange_.getTsteps());
    pImpl_->definitionRange_.setDu((pImpl_->definitionRange_.getUmax()-pImpl_->definitionRange_.getUmin()) /
                                    pImpl_->definitionRange_.getUsteps());
    pImpl_->definitionRange_.setDv((pImpl_->definitionRange_.getVmax()-pImpl_->definitionRange_.getVmin()) /
                                    pImpl_->definitionRange_.getVsteps());
  }
}

RealFunction::~RealFunction() { }

/// Allocate and initialize X[][][] with values of f().
void RealFunction::Initialize () {
  pImpl_->_X = FunctionValueGrid<4, 3>(_function,
                               Vector<3, unsigned>(pImpl_->definitionRange_.getTsteps()+2, 
                                                   pImpl_->definitionRange_.getUsteps()+2, 
                                                   pImpl_->definitionRange_.getVsteps()+2),
                               Vector<3>(pImpl_->definitionRange_.getTmin(), 
                                         pImpl_->definitionRange_.getUmin(), 
                                         pImpl_->definitionRange_.getVmin()),
                               Vector<3>(pImpl_->definitionRange_.getTmax(), 
                                         pImpl_->definitionRange_.getUmax(), 
                                         pImpl_->definitionRange_.getVmax()));

  calibrateColors();

}

void RealFunction::calibrateColors() const {

  std::pair< double, double > Wext = pImpl_->findExtremesInW();

  for (unsigned t = 0; t <= pImpl_->definitionRange_.getTsteps(); t++) {
    for (unsigned u = 0; u <= pImpl_->definitionRange_.getUsteps()+1; u++) {
      for (unsigned v = 0; v <= pImpl_->definitionRange_.getVsteps()+1; v++) {
        ColMgrMgr::Instance().calibrateColor(
            X()[t][u][v],
            Color(float(t)/float(pImpl_->definitionRange_.getTsteps()), 
                  float(u)/float(pImpl_->definitionRange_.getUsteps()),
                  float(v)/float(pImpl_->definitionRange_.getVsteps()),
                  (X()[t][u][v][3]-Wext.first)/(Wext.second-Wext.first)));
      }
    }
  }
}

unsigned int RealFunction::getDefinitionSpaceDimensions() { return 3; }

Vector<4>& RealFunction::operator()(double t, double u, double v) {
  static VecMath::Vector<4> F;
  F = _function->f(VecMath::Vector<3>(t, u, v));
  return F;
}

void RealFunction::for_each(Function::function_on_fourspace_vertex apply) {
  for (unsigned t = 0; t < pImpl_->definitionRange_.getTsteps(); t++)
    for (unsigned u = 0; u < pImpl_->definitionRange_.getUsteps(); u++)
      for (unsigned v = 0; v < pImpl_->definitionRange_.getVsteps(); v++)
        apply(X()[t][u][v]);
}

void RealFunction::for_each(Function::function_on_fourspace_and_transformed_vertex apply) {
  for (unsigned t = 0; t < pImpl_->definitionRange_.getTsteps(); t++)
    for (unsigned u = 0; u < pImpl_->definitionRange_.getUsteps(); u++)
      for (unsigned v = 0; v < pImpl_->definitionRange_.getVsteps(); v++)
        apply(X()[t][u][v], Xtrans()[t][u][v]);
}

void RealFunction::for_each(Function::function_on_fourspace_transformed_and_projected_vertex apply) {
  for (unsigned t = 0; t < pImpl_->definitionRange_.getTsteps(); t++)
    for (unsigned u = 0; u < pImpl_->definitionRange_.getUsteps(); u++)
      for (unsigned v = 0; v < pImpl_->definitionRange_.getVsteps(); v++)
        apply(X()[t][u][v], Xtrans()[t][u][v], Xscr()[t][u][v]);
}

void RealFunction::for_each(Function::function_on_projected_vertex apply) {
  for (unsigned t = 0; t < pImpl_->definitionRange_.getTsteps(); t++)
    for (unsigned u = 0; u < pImpl_->definitionRange_.getUsteps(); u++)
      for (unsigned v = 0; v < pImpl_->definitionRange_.getVsteps(); v++)
        apply(Xscr()[t][u][v]);
}

unsigned int RealFunction::getTsteps() const { return pImpl_->definitionRange_.getTsteps(); }
unsigned int RealFunction::getUsteps() const { return pImpl_->definitionRange_.getUsteps(); }
unsigned int RealFunction::getVsteps() const { return pImpl_->definitionRange_.getVsteps(); }


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

  pImpl_->setBoundariesAndStepwidth(tmin, tmax, dt, umin, umax, du, vmin, vmax, dv);

  Initialize ();

}


/// Transforms a RealFunction
/** \param R rotation
 *  \param T translation                                                      */
void RealFunction::Transform (const VecMath::Rotation<4> &R,
                              const VecMath::Vector<4> &T) {
  Transformation<4, 3> xform(R, T);
  pImpl_->_Xtrans = xform.transform(X());
}

/// Projects a RealFunction into three-space
/** \param scr_w w coordinate of screen
 *  \param cam_w w coordinate of camera
 *  \param depthcue4d whether to use hyperfog/depth cue                       */
void RealFunction::Project (double scr_w, double cam_w, bool depthcue4d) {

  Projection<4, 3, 3> p(scr_w, cam_w, depthcue4d);
  pImpl_->_Xscr = p.project(Xtrans());

  if (depthcue4d) {
    std::pair< double, double > Wext = pImpl_->findExtremesInW();
    pImpl_->setDepthCueColors(Wext.first, Wext.second);
  }
}

/// Draw the projected Function (onto screen or into GL list, as it is)
/** */
void RealFunction::Draw (UI::View *view) {
//  ScopedTimer timer("Draw()");
# ifdef USE_GRID_DRAWER
std::cerr << "USE_GRID_DRAWER" << std::endl;
    GridDrawer<3> draw(X(), Xscr(), view);
    draw.execute();
# else
    for (unsigned t = 0; t < pImpl_->definitionRange_.getTsteps(); t++)
      pImpl_->DrawPlane (t, view);
# endif
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
  return pImpl_->X();
}

const VecMath::NestedVector< Vector< 4 >, 3 > &RealFunction::Xtrans() const {
  return pImpl_->_Xtrans;
}

const VecMath::NestedVector< Vector< 3 >, 3 >& RealFunction::Xscr() const {
    return pImpl_->_Xscr;
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
