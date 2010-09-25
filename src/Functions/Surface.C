
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

#include "View.h"

#include "FunctionValueGrid.h"
#include "Transformation.h"
#include "Projection.h"

#include "DefinitionRangeOfDimension.h"

#include <utility>

using VecMath::NestedVector;
using VecMath::Vector;
using VecMath::Matrix;

/// SurfaceBase provides a base class for functions which take two parameters
/** The SurfaceBase interface provides abstract members for the evaluation
 * of the function values on a two-dimensional grid.
 *
 *  abstract member:
 *      \li Vector &f (double, double);
 *
 *  member:
 *      \li operator () (double t, double u, double);
 *
 *  @todo Vector &normal (double, double); - or in base class?
 *
 *  \ingroup SurfaceGroup
 *  @author Lene Preuss <lene.preuss@gmail.com>                         */
class SurfaceDefinitionRange: public DefinitionRangeOfDimension<2> {
  public:

    /** \param _tmin lower bound in first parameter
     *  \param _tmax upper bound in first parameter
     *  \param _dt stepsize in first parameter
     *  \param _umin lower bound in second parameter
     *  \param _umax upper bound in second parameter
     *  \param _du stepsize in second parameter
     */
    SurfaceDefinitionRange(double tmin, double tmax, double dt,
                           double umin, double umax, double du) {
      setRange(0, DefinitionSpaceRange(tmin, tmax, dt));
      setRange(1, DefinitionSpaceRange(umin, umax, du));
    }

    unsigned getTsteps() const { return getNumSteps(0); }
    void setTsteps(unsigned numSteps) { setNumSteps(0, numSteps); }
    void decrementTsteps() { setTsteps(getTsteps()-1); }

    unsigned getUsteps() const { return getNumSteps(1); }
    void setUsteps(unsigned numSteps) { setNumSteps(1, numSteps); }
    void decrementUsteps() { setUsteps(getUsteps()-1); }

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

    static double _min, ///< Default value for lower grid boundary
                  _max, ///< Default value for upper grid boundary
                  _d;   ///< Default value for step size

};

double SurfaceDefinitionRange::_min = -1.;
double SurfaceDefinitionRange::_max =  1.;
double SurfaceDefinitionRange::_d = 0.1;

struct Surface::Impl {
  
  Impl(double _umin, double _umax, double _du,
       double _vmin, double _vmax, double _dv):
    definitionRange_(_umin, _umax, _du, _vmin, _vmax, _dv) { }
  
  void DrawStrip (unsigned t, UI::View *view);

    /// Set up the grid using boundaries and stepwidth.
    void setBoundariesAndStepwidth(double tmin, double tmax, double dt,
                                   double umin, double umax, double du);

    std::pair<double, double> findExtremesInW() const;

    const NestedVector< Vector<4>, 2 > &X() const { return _X.getValues(); }
    
    SurfaceDefinitionRange definitionRange_;

    /// Array of function values.
    FunctionValueGrid<4, 2> _X;
    /// Array of function values after transform.
    FunctionValueGrid<4, 2>::value_storage_type _Xtrans;
    /// Array of projected function values.
    VecMath::NestedVector< VecMath::Vector<3>, 2 > _Xscr;
};  

/** draw the current strip of the projected Surface
 *  @param t current t value                                                  */
void Surface::Impl::DrawStrip (unsigned t, UI::View *view) {

  for (unsigned u = 0; u <= definitionRange_.getUsteps(); u++) {
    view->drawQuadrangle(X()[t][u], X()[t+1][u], X()[t+1][u+1], X()[t][u+1],
                         _Xscr[t][u], _Xscr[t+1][u], _Xscr[t+1][u+1], _Xscr[t][u+1]);
  }
}

/** \return Maxima and minima in the W dimension
 */
std::pair< double, double > Surface::Impl::findExtremesInW() const {
  double Wmax = 0, Wmin = 0;

  for (unsigned t = 0; t <= definitionRange_.getTsteps()+1; t++) {
    for (unsigned u = 0; u <= definitionRange_.getUsteps()+1; u++) {
      if (X()[t][u][3] < Wmin) Wmin = X()[t][u][3];
      if (X()[t][u][3] > Wmax) Wmax = X()[t][u][3];
    }
  }

  return std::make_pair(Wmin, Wmax);
}

/** \param tmin minimal value in t
 *  \param tmax maximal value in t
 *  \param dt stepsize in t
 *  \param umin minimal value in u
 *  \param umax maximal value in u
 *  \param du stepsize in u
 */
void Surface::Impl::setBoundariesAndStepwidth(double tmin, double tmax, double dt,
                                        double umin, double umax, double du) {
  definitionRange_.setTmin(tmin);   definitionRange_.setTmax(tmax);   definitionRange_.setDt(dt);
  definitionRange_.setUmin(umin);   definitionRange_.setUmax(umax);   definitionRange_.setDu(du);
  definitionRange_.setTsteps(unsigned((definitionRange_.getTmax()-definitionRange_.getTmin())/definitionRange_.getDt()+2));
  definitionRange_.setUsteps(unsigned((definitionRange_.getUmax()-definitionRange_.getUmin())/definitionRange_.getDu()+2));
}

/// Surface default c'tor, zeroes everything
Surface::Surface (): 
  Function(ParameterMap()),
  pImpl_(new Impl(SurfaceDefinitionRange::_min, SurfaceDefinitionRange::_max, SurfaceDefinitionRange::_d, 
                  SurfaceDefinitionRange::_min, SurfaceDefinitionRange::_max, SurfaceDefinitionRange::_d)) { }


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
    Function(_parms), pImpl_(new Impl(_umin, _umax, _du, _vmin, _vmax, _dv)) { }

Surface::~Surface() { }

/// allocate and initialize X[][] with values of f()
/** call InitMem () above                                                     */
void Surface::Initialize () {

    pImpl_->_X = FunctionValueGrid<4, 2>(_function,
                                         Vector<2, unsigned>(getTsteps()+2, getUsteps()+2),
                                         Vector<2>(pImpl_->definitionRange_.getTmin(), 
                                                   pImpl_->definitionRange_.getUmin()),
                                         Vector<2>(pImpl_->definitionRange_.getTmax(), 
                                                   pImpl_->definitionRange_.getUmax()));

    calibrateColors();
}

void Surface::calibrateColors() const {

  std::pair< double, double > Wext = pImpl_->findExtremesInW();

  for (unsigned t = 0; t <= getTsteps()+1; t++) {
        for (unsigned u = 0; u <= getUsteps()+1; u++) {
            ColMgrMgr::Instance().calibrateColor(
                X()[t][u],
                Color(float(t)/float(getTsteps()), float(u)/float(getUsteps()),
                      (Wext.second-X()[t][u][3])/(Wext.second-Wext.first)));
        }
    }
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
  pImpl_->setBoundariesAndStepwidth(_tmin, _tmax, _dt, _umin, _umax, _du);

  Initialize ();

}

unsigned int Surface::getDefinitionSpaceDimensions() { return 2; }

void Surface::for_each(Function::function_on_fourspace_vertex apply) {
  for (unsigned t = 0; t < getTsteps(); t++)
    for (unsigned u = 0; u < getUsteps(); u++)
      apply(X()[t][u]);
}

void Surface::for_each(function_on_fourspace_and_transformed_vertex apply) {
  for (unsigned t = 0; t < getTsteps(); t++)
    for (unsigned u = 0; u < getUsteps(); u++)
      apply(X()[t][u], Xtrans()[t][u]);
}

void Surface::for_each(function_on_fourspace_transformed_and_projected_vertex apply) {
  for (unsigned t = 0; t < getTsteps(); t++)
    for (unsigned u = 0; u < getUsteps(); u++)
      apply(X()[t][u], Xtrans()[t][u], Xscr()[t][u]);
}

void Surface::for_each(Function::function_on_projected_vertex apply) {
  for (unsigned t = 0; t < getTsteps(); t++)
    for (unsigned u = 0; u < getUsteps(); u++)
      apply(Xscr()[t][u]);
}

/** @param u first argument, e.g. y or u
 *  @param v second argument, e.g. z or v
 *  @return f(t, u, v)                                                
 */
Vector< 4 >& Surface::operator()(double u, double v, double ) {
  static VecMath::Vector<4> F;
  F = _function->f(VecMath::Vector<2>(u, v));
  return F;
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
  pImpl_->_Xtrans = xform.transform(X());
}

/** projects a Surface into three-space
 *  \param scr_w w coordinate of screen
 *  \param cam_w w coordinate of camera
 *  \param depthcue4d whether to use hyperfog/depth cue                        */
void Surface::Project (double scr_w, double cam_w, bool depthcue4d) {

    Projection<4, 3, 2> p(scr_w, cam_w, depthcue4d);
    pImpl_->_Xscr = p.project(Xtrans());

    if (depthcue4d) {
        std::pair< double, double > Wext = pImpl_->findExtremesInW();
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
        pImpl_->DrawStrip (t, view);
}

unsigned int Surface::getTsteps() const { return pImpl_->definitionRange_.getTsteps(); }

unsigned int Surface::getUsteps() const { return pImpl_->definitionRange_.getUsteps(); }

const NestedVector< Vector<4>, 2 > &Surface::X() const {
  return pImpl_->X();
}

const NestedVector< Vector<4>, 2 > &Surface::Xtrans() const {
  return pImpl_->_Xtrans;
}

const VecMath::NestedVector< Vector< 3 >, 2 >& Surface::Xscr() const {
  return pImpl_->_Xscr;
}
