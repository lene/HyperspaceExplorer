
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

#include "Transformation.h"
#include "Projection.h"


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
class SurfaceDefinitionRange {
    public:

        /** \param _tmin lower bound in first parameter
         *  \param _tmax upper bound in first parameter
         *  \param _dt stepsize in first parameter
         *  \param _umin lower bound in second parameter
         *  \param _umax upper bound in second parameter
         *  \param _du stepsize in second parameter
         *  \param _parms parameters to the Surface                           */
        SurfaceDefinitionRange(double _tmin, double _tmax, double _dt,
                               double _umin, double _umax, double _du):
                tmin (_tmin), tmax (_tmax), dt (_dt),
                umin (_umin), umax (_umax), du (_du),
                tsteps (unsigned ((tmax-tmin)/dt+1)),
                usteps (unsigned ((umax-umin)/du+1)) { }

        /// number of steps in t
        unsigned &getTsteps() { return tsteps; }
        /// number of steps in t
        unsigned getTsteps() const { return tsteps > 0? tsteps: 1; }
        /// number of steps in u
        unsigned &getUsteps() { return usteps; }
        /// number of steps in u
        unsigned getUsteps() const { return usteps > 0? usteps: 1; }

        double &getTmin() { return tmin; }          ///< min. value of the first parameter, t
        double getTmin() const { return tmin; }     ///< min. value of the first parameter, t
        double &getTmax() { return tmax; }          ///< max. value of the first parameter, t
        double getTmax() const { return tmax; }     ///< max. value of the first parameter, t
        double &getDt() { return dt; }              ///< delta in t
        const double &getDt() const { return dt; }  ///< delta in t
        double &getUmin() { return umin; }          ///< min. value of the second parameter, u
        double getUmin() const { return umin; }     ///< min. value of the second parameter, u
        double &getUmax() { return umax; }          ///< max. value of the second parameter, u
        double getUmax() const { return umax; }     ///< max. value of the second parameter, u
        double &getDu() { return du; }              ///< delta in u
        const double &getDu() const { return du; }  ///< delta in u

    static double _min, ///< Default value for lower grid boundary
                  _max, ///< Default value for upper grid boundary
                  _d;   ///< Default value for step size

    private:
        double tmin, ///< min. value of the first parameter, here called t
               tmax, ///< min. value of the first parameter, here called t
               dt,   ///< stepsize in first parameter
               umin, ///< min. value of the second parameter, here called u
               umax, ///< min. value of the second parameter, here called u
               du;   ///< stepsize in second parameter
        unsigned tsteps, ///< number of steps in t
                 usteps; ///< number of steps in u
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
    definitionRange_.getTmin() = tmin; definitionRange_.getTmax() = tmax; definitionRange_.getDt() = dt;
    definitionRange_.getUmin() = umin; definitionRange_.getUmax() = umax; definitionRange_.getDu() = du;
    definitionRange_.getTsteps() = unsigned ((definitionRange_.getTmax()-definitionRange_.getTmin())/definitionRange_.getDt()+1);
    definitionRange_.getUsteps() = unsigned ((definitionRange_.getUmax()-definitionRange_.getUmin())/definitionRange_.getDu()+1);
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

void Surface::for_each(Function::function_on_projected_vertex apply) {
  for (unsigned t = 0; t < getTsteps(); t++)
    for (unsigned u = 0; u < getUsteps(); u++)
      apply(Xscr()[t][u]);
}

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
