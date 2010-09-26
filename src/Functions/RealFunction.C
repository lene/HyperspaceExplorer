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

#include "DefinitionRangeOfDimension.impl.h"

#include "Transformation.impl.h"
#include "Projection.impl.h"
#include "GridDrawer.impl.h"

#include "ColorManager.h"

//#include "Log.h"
//#include "ScopedTimer.h"

using std::cerr;
using std::endl;

using VecMath::NestedVector;
using VecMath::Vector;

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
 *  \author Lene Preuss <lene.preuss@gmail.com>                         
 */
class RealFunctionDefinitionRange: public DefinitionRangeOfDimension<3> {

  public:

    RealFunctionDefinitionRange(double tmin, double tmax, double dt,
                                double umin, double umax, double du,
                                double vmin, double vmax, double dv) {
      setRange(0, DefinitionSpaceRange(tmin, tmax, dt));
      setRange(1, DefinitionSpaceRange(umin, umax, du));
      setRange(2, DefinitionSpaceRange(vmin, vmax, dv));       
    }

    unsigned getTsteps() const { return getNumSteps(0); }
    void setTsteps(unsigned numSteps) { setNumSteps(0, numSteps); }
    void decrementTsteps() { setTsteps(getTsteps()-1); }

    unsigned getUsteps() const { return getNumSteps(1); }
    void setUsteps(unsigned numSteps) { setNumSteps(1, numSteps); }
    void decrementUsteps() { setUsteps(getUsteps()-1); }

    unsigned getVsteps() const { return getNumSteps(2); }
    void setVsteps(unsigned numSteps) { setNumSteps(2, numSteps); }
    void decrementVsteps() { setVsteps(getVsteps()-1); }

    void setTmin(double tmin) { setMinValue(0, tmin); }
    double getTmin() const { return getMinValue(0); }
    void setTmax(double tmax) { setMaxValue(0, tmax); }
    double getTmax() const { return getMaxValue(0); }
    void setDt(double dt) { setStepsize(0, dt); }
    double getDt() const { return getStepsize(0); }

    void setUmin(double umin) { setMinValue(1, umin); }
    double getUmin() const { return getMinValue(1); } 
    void setUmax(double umax) { setMaxValue(1, umax); }
    double getUmax() const { return getMaxValue(1); }
    void setDu(double du) { setStepsize(1, du); }
    double getDu() const { return getStepsize(1); }  
    
    void setVmin(double vmin) { setMinValue(2, vmin); }
    double getVmin() const { return getMinValue(2); }
    void setVmax(double vmax) { setMaxValue(2, vmax); }
    double getVmax() const { return getMaxValue(2); }
    void setDv(double dv) { setStepsize(2, dv); }
    double getDv() const { return getStepsize(2); }  

};

class RealFunction::Impl {
  
  public:
    
    Impl(double tmin, double tmax, double dt,
         double umin, double umax, double du,
         double vmin, double vmax, double dv);

    void Transform (const VecMath::Rotation<4> &R, const VecMath::Vector<4> &T);
    void Project (double ScrW, double CamW, bool DepthCue4D);
    void Draw (UI::View *view);
    
    void calibrateColors() const;
         
    void for_each(function_on_fourspace_vertex apply);
    void for_each(function_on_fourspace_and_transformed_vertex apply);
    void for_each(function_on_fourspace_transformed_and_projected_vertex apply);
    void for_each(function_on_projected_vertex apply);

    const VecMath::NestedVector< Vector< 4 >, 3 > &X() const { return _X.getValues(); }
    const VecMath::NestedVector< VecMath::Vector<4>, 3 > &Xtrans() const { return _Xtrans; }
    const VecMath::NestedVector< VecMath::Vector<3>, 3 > &Xscr() const { return _Xscr; }

    /// Set up the grid using boundaries and stepwidth.
    void setBoundariesAndStepwidth(double tmin, double tmax, double dt,
                                   double umin, double umax, double du,
                                   double vmin, double vmax, double dv);
    RealFunctionDefinitionRange definitionRange_;
    /// Array of function values.
    FunctionValueGrid<4, 3> _X;

  private:
    /// Initialize depth cue.
    void setDepthCueColors(double Wmax, double Wmin);

    /// Finds maximum and minimum function value in w.
    std::pair<double, double> findExtremesInW() const;

    void DrawPlane (unsigned, UI::View *view);
    void DrawStrip (unsigned, unsigned, UI::View *view);
    void DrawCube (unsigned, unsigned, unsigned, UI::View *view);
    
    /// Array of function values after transform.
    FunctionValueGrid<4, 3>::value_storage_type _Xtrans;
    /// Array of projected function values.
    VecMath::NestedVector< VecMath::Vector<3>, 3 > _Xscr;

};

RealFunction::Impl::Impl(double tmin, double tmax, double dt, 
                         double umin, double umax, double du, 
                         double vmin, double vmax, double dv):
  definitionRange_(tmin, tmax, dt, umin, umax, du, vmin, vmax, dv) { }

void RealFunction::Impl::Transform(const VecMath::Rotation< 4 >& R, const VecMath::Vector< 4 >& T) {
  Transformation<4, 3> xform(R, T);
  _Xtrans = xform.transform(X());
}

void RealFunction::Impl::Project(double scr_w, double cam_w, bool depthcue4d) {
  Projection<4, 3, 3> p(scr_w, cam_w, depthcue4d);
  _Xscr = p.project(Xtrans());

  if (depthcue4d) {
    std::pair< double, double > Wext = findExtremesInW();
    setDepthCueColors(Wext.first, Wext.second);
  }
}

void RealFunction::Impl::Draw(UI::View* view) {
//  ScopedTimer timer("Draw()");
# ifdef USE_GRID_DRAWER
std::cerr << "USE_GRID_DRAWER" << std::endl;
    GridDrawer<3> draw(X(), Xscr(), view);
    draw.execute();
# else
    for (unsigned t = 0; t < definitionRange_.getTsteps(); t++)
      DrawPlane (t, view);
# endif

}

void RealFunction::Impl::calibrateColors() const {

  std::pair< double, double > Wext = findExtremesInW();

  for (unsigned t = 0; t <= definitionRange_.getTsteps(); t++) {
    for (unsigned u = 0; u <= definitionRange_.getUsteps()+1; u++) {
      for (unsigned v = 0; v <= definitionRange_.getVsteps()+1; v++) {
        ColMgrMgr::Instance().calibrateColor(
            X()[t][u][v],
            Color(float(t)/float(definitionRange_.getTsteps()), 
                  float(u)/float(definitionRange_.getUsteps()),
                  float(v)/float(definitionRange_.getVsteps()),
                  (X()[t][u][v][3]-Wext.first)/(Wext.second-Wext.first)));
      }
    }
  }
}

void RealFunction::Impl::for_each(Function::function_on_fourspace_vertex apply) {
  for (unsigned t = 0; t < definitionRange_.getTsteps(); t++)
    for (unsigned u = 0; u < definitionRange_.getUsteps(); u++)
      for (unsigned v = 0; v < definitionRange_.getVsteps(); v++)
        apply(X()[t][u][v]);
}

void RealFunction::Impl::for_each(Function::function_on_fourspace_and_transformed_vertex apply) {
  for (unsigned t = 0; t < definitionRange_.getTsteps(); t++)
    for (unsigned u = 0; u < definitionRange_.getUsteps(); u++)
      for (unsigned v = 0; v < definitionRange_.getVsteps(); v++)
        apply(X()[t][u][v], Xtrans()[t][u][v]);
}

void RealFunction::Impl::for_each(Function::function_on_fourspace_transformed_and_projected_vertex apply) {
  for (unsigned t = 0; t < definitionRange_.getTsteps(); t++)
    for (unsigned u = 0; u < definitionRange_.getUsteps(); u++)
      for (unsigned v = 0; v < definitionRange_.getVsteps(); v++)
        apply(X()[t][u][v], Xtrans()[t][u][v], Xscr()[t][u][v]);
}

void RealFunction::Impl::for_each(Function::function_on_projected_vertex apply) {
  for (unsigned t = 0; t < definitionRange_.getTsteps(); t++)
    for (unsigned u = 0; u < definitionRange_.getUsteps(); u++)
      for (unsigned v = 0; v < definitionRange_.getVsteps(); v++)
        apply(Xscr()[t][u][v]);
}

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
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep, 
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep, 
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep)) { }
 
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
  Function(parms), pImpl_(new Impl(tmin, tmax, dt, umin, umax, du, vmin, vmax, dv)) { }

RealFunction::~RealFunction() { }

/// Allocate and initialize X[][][] with values of f().
void RealFunction::Initialize () {
  
  Vector<3, unsigned> numSteps = pImpl_->definitionRange_.getNumSteps();
  Vector<3, double> min = pImpl_->definitionRange_.getMinValue();
  Vector<3, double> max = pImpl_->definitionRange_.getMaxValue();
  
  pImpl_->_X = FunctionValueGrid<4, 3>(
    _function, numSteps.operator+(2), min, max
  );

  calibrateColors();

}

void RealFunction::calibrateColors() const {
  pImpl_->calibrateColors();
}

unsigned int RealFunction::getDefinitionSpaceDimensions() { return 3; }

/** @param t first argument, e.g. x or t
 *  @param u second argument, e.g. y or u
 *  @param v third argument, e.g. z or v
 *  @return f(t, u, v)                                                
 */
Vector<4>& RealFunction::operator()(double t, double u, double v) {
  static VecMath::Vector<4> F;
  F = _function->f(VecMath::Vector<3>(t, u, v));
  return F;
}

void RealFunction::for_each(Function::function_on_fourspace_vertex apply) {
  pImpl_->for_each(apply);
}

void RealFunction::for_each(Function::function_on_fourspace_and_transformed_vertex apply) {
  pImpl_->for_each(apply);
}

void RealFunction::for_each(Function::function_on_fourspace_transformed_and_projected_vertex apply) {
  pImpl_->for_each(apply);
}

void RealFunction::for_each(Function::function_on_projected_vertex apply) {
  pImpl_->for_each(apply);
}

unsigned int RealFunction::getTsteps() const { return pImpl_->definitionRange_.getTsteps(); }
unsigned int RealFunction::getUsteps() const { return pImpl_->definitionRange_.getUsteps(); }
unsigned int RealFunction::getVsteps() const { return pImpl_->definitionRange_.getVsteps(); }


/// Re-initialize a RealFunction if the definition set has changed
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
  pImpl_->Transform(R, T);
}

/// Projects a RealFunction into three-space
/** \param scr_w w coordinate of screen
 *  \param cam_w w coordinate of camera
 *  \param depthcue4d whether to use hyperfog/depth cue                       */
void RealFunction::Project (double scr_w, double cam_w, bool depthcue4d) {
  pImpl_->Project(scr_w, cam_w, depthcue4d);
}

/// Draw the projected Function (onto screen or into GL list, as it is)
/** */
void RealFunction::Draw (UI::View *view) {
  pImpl_->Draw(view);
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
  return pImpl_->Xtrans();
}

const VecMath::NestedVector< Vector< 3 >, 3 >& RealFunction::Xscr() const {
    return pImpl_->Xscr();
}
