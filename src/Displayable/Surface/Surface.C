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

#include "Surface.h"

#include "FunctionHolder.impl.h"

#include "ColorManager.h"

#include "View.h"

#include "Transformation.impl.h"
#include "Projection.impl.h"
#include "MultiDimensionalVector.impl.h"

#include "DefinitionRangeOfDimension.impl.h"

using VecMath::MultiDimensionalVector;
using VecMath::Vector;

struct Surface::Impl {

  Impl(Surface *f): parent_(f) { }

  void Transform (const VecMath::Rotation<4> &R, const VecMath::Vector<4> &T);
  void Project (double ScrW, double CamW, bool DepthCue4D);
  void Draw (UI::View *view);

  void calibrateColors() const;

  const VecMath::MultiDimensionalVector< Vector< 4 >, 2 > &X() const {
    return parent_->X();
  }
  const VecMath::MultiDimensionalVector< VecMath::Vector<4>, 2 > &Xtrans() const {
    return parent_->Xtrans();
  }
  const VecMath::MultiDimensionalVector< VecMath::Vector<3>, 2 > &Xscr() const {
    return parent_->Xscr();
  }

  void DrawStrip (unsigned t, UI::View *view);

  /// Set up the grid using boundaries and stepwidth.
  void setBoundariesAndStepwidth(double tmin, double tmax, double dt,
                                 double umin, double umax, double du);

  std::pair<double, double> findExtremesInW() const;

  DefinitionRangeOfDimension<2> getDefinitionRange() const { return parent_->getDefinitionRange(); }

  /// Initialize depth cue.
  void setDepthCueColors(double Wmax, double Wmin);

  Surface *parent_;

};

void Surface::Impl::Project(double scr_w, double cam_w, bool depthcue4d) {
  parent_->FunctionHolder<4, 2>::Project(scr_w, cam_w, depthcue4d);
  if (depthcue4d) {
    std::pair< double, double > Wext = findExtremesInW();
    setDepthCueColors(Wext.first, Wext.second);
  }
}

void Surface::Impl::setDepthCueColors(double Wmax, double Wmin) {
  for (unsigned t = 0; t <= getDefinitionRange().getNumSteps(0)+1; t++) {
    for (unsigned u = 0; u <= getDefinitionRange().getNumSteps(1)+1; u++) {
      ColMgrMgr::Instance().depthCueColor(Wmax, Wmin,
                                          Xtrans()[t][u][3],
                                          X()[t][u]);
    }
  }
}

void Surface::Impl::calibrateColors() const {
  std::pair< double, double > Wext = findExtremesInW();

  for (unsigned t = 0; t <= getDefinitionRange().getNumSteps(0)+1; t++) {
    for (unsigned u = 0; u <= getDefinitionRange().getNumSteps(1)+1; u++) {
      float r = float(t)/float(getDefinitionRange().getNumSteps(0));
      float g = float(u)/float(getDefinitionRange().getNumSteps(1));
      float b = (Wext.second-X()[t][u][3])/(Wext.second-Wext.first);
      ColMgrMgr::Instance().calibrateColor(X()[t][u], Color(r, g, b));
    }
  }

}

/** draw the current strip of the projected Surface
 *  @param t current t value                                                  */
void Surface::Impl::DrawStrip (unsigned t, UI::View *view) {

  for (unsigned u = 0; u <= getDefinitionRange().getNumSteps(1); u++) {
    view->drawQuadrangle(X()[t][u], X()[t+1][u], X()[t+1][u+1], X()[t][u+1],
                         Xscr()[t][u], Xscr()[t+1][u], Xscr()[t+1][u+1], Xscr()[t][u+1]);
  }
}

/** \return Maxima and minima in the W dimension
 */
std::pair< double, double > Surface::Impl::findExtremesInW() const {
  double Wmax = 0, Wmin = 0;

  for (unsigned t = 0; t <= getDefinitionRange().getNumSteps(0); t++) {
    for (unsigned u = 0; u <= getDefinitionRange().getNumSteps(1)+1; u++) {
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
  getDefinitionRange().setMinValue(0, tmin);   getDefinitionRange().setMaxValue(0, tmax);
  getDefinitionRange().setStepsize(0, dt);
  getDefinitionRange().setMinValue(1, umin);   getDefinitionRange().setMaxValue(1, umax);
  getDefinitionRange().setStepsize(1, du);
  getDefinitionRange().setNumSteps(0, unsigned((getDefinitionRange().getMaxValue(0)-getDefinitionRange().getMinValue(0))/getDefinitionRange().getStepsize(0)+2));
  getDefinitionRange().setNumSteps(1, unsigned((getDefinitionRange().getMaxValue(1)-getDefinitionRange().getMinValue(1))/getDefinitionRange().getStepsize(1)+2));
}

/// Surface default c'tor, zeroes everything
Surface::Surface():
  FunctionHolder<4, 2, double>(ParameterMap()),
  pImpl_(new Impl(this)) { }


/** Surface c'tor given a definition set in \f$ R^2 \f$ (as parameter space)
 *  \param umin minimal value in u
 *  \param umax maximal value in u
 *  \param du stepsize in u
 *  \param vmin minimal value in v
 *  \param vmax maximal value in v
 *  \param dv stepsize in v
 *  \param parms Parameter for the function
 */
Surface::Surface (double umin, double umax, double du,
                  double vmin, double vmax, double dv,
                  ParameterMap parms):
    FunctionHolder<4, 2, double>(parms),
    pImpl_(new Impl(this)) {
  setDefinitionRange(umin, umax, du, vmin, vmax, dv, 0, 0, 0);
}

Surface::~Surface() { }

/// allocate and initialize X[][] with values of f()
/** call InitMem () above                                                     */
void Surface::Initialize () {

  Vector<2, unsigned> numSteps = getDefinitionRange().getNumSteps();
  Vector<2, double> min = getDefinitionRange().getMinValue();
  Vector<2, double> max = getDefinitionRange().getMaxValue();

  setX(
    FunctionValueGrid<4, 2>(
      _function, numSteps+Vector<2, unsigned>(2), min, max
    )
  );

  calibrateColors();
}

void Surface::calibrateColors() const {
  pImpl_->calibrateColors();
}

/// re-initialize a Surface if the definition set has changed
void Surface::ReInit(double, double, double,
                     double _tmin, double _tmax, double _dt,
                     double _umin, double _umax, double _du) {
  setDefinitionRange(_tmin, _tmax, _dt, _umin, _umax, _du, 0, 0, 0);
  Initialize();
}

unsigned int Surface::getNumParameters() {
  return Displayable::getNumParameters();
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

    Displayable::vec4vec1D D = df(uu, vv);

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
Displayable::vec4vec1D Surface::df (double uu, double vv) {

    static Vector<4> F0, F;        //  f (u, v)
    static double h = 1e-5;     //  maybe tweak to get best results

    static Displayable::vec4vec1D DF(3);

    F0 = operator() (uu, vv);

    F = operator() (uu+h, vv); //  derive after u
    DF[0] = (F-F0)/h;
    F = operator() (uu, vv+h); //  derive after v
    DF[1] = (F-F0)/h;
    DF[2] = (F-F0)/h;           //  are you sure this is correct?

    return DF;
}

/** projects a Surface into three-space
 *  \param scr_w w coordinate of screen
 *  \param cam_w w coordinate of camera
 *  \param depthcue4d whether to use hyperfog/depth cue                        */
void Surface::Project (double scr_w, double cam_w, bool depthcue4d) {
  pImpl_->Project(scr_w, cam_w, depthcue4d);
}
