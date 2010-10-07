/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2008-2010  Lene Preuss <lene.preuss@gmail.com>

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

#include "RealFunction.h"

#include "FunctionHolder.impl.h"
#include "DefinitionRangeOfDimension.impl.h"

#include "Transformation.impl.h"
#include "Projection.impl.h"
#include "GridDrawer.impl.h"
#include "MultiDimensionalVector.impl.h"

#include "ColorManager.h"

//#include "Log.h"
//#include "ScopedTimer.h"

using std::cerr;
using std::endl;

using VecMath::MultiDimensionalVector;
using VecMath::Vector;
using VecMath::Rotation;

class RealFunction::Impl {

  public:

    Impl(RealFunction *f);

    void Project (double ScrW, double CamW, bool DepthCue4D);
    void Draw (UI::View *view);

    void calibrateColors() const;

    const MultiDimensionalVector< Vector< 4 >, 3 > &X() const {
      return parent_->X();
    }
    const MultiDimensionalVector< Vector<4>, 3 > &Xtrans() const {
      return parent_->Xtrans();
    }
    const MultiDimensionalVector< Vector<3>, 3 > &Xscr() const {
      return parent_->Xscr();
    }

    DefinitionRangeOfDimension<3> getDefinitionRange() const { return parent_->getDefinitionRange(); }

  private:
    /// Initialize depth cue.
    void setDepthCueColors(double Wmax, double Wmin);

    /// Finds maximum and minimum function value in w.
    std::pair<double, double> findExtremesInW() const;

    void DrawPlane (unsigned, UI::View *view);
    void DrawStrip (unsigned, unsigned, UI::View *view);
    void DrawCube (unsigned, unsigned, unsigned, UI::View *view);

    RealFunction *parent_;

};

RealFunction::Impl::Impl(RealFunction *f): parent_(f) { }

void RealFunction::Impl::Project(double scr_w, double cam_w, bool depthcue4d) {
  Projection<4, 3, 3> p(scr_w, cam_w, depthcue4d);
  parent_->setXscr(p.project(Xtrans()));

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
    for (unsigned t = 0; t <= getDefinitionRange().getNumSteps(0); t++)
      DrawPlane (t, view);
# endif

}

void RealFunction::Impl::calibrateColors() const {

  std::pair< double, double > Wext = findExtremesInW();

  for (unsigned t = 0; t <= getDefinitionRange().getNumSteps(0); t++) {
    for (unsigned u = 0; u <= getDefinitionRange().getNumSteps(1)+1; u++) {
      for (unsigned v = 0; v <= getDefinitionRange().getNumSteps(2)+1; v++) {
        ColMgrMgr::Instance().calibrateColor(
            X()[t][u][v],
            Color(float(t)/float(getDefinitionRange().getNumSteps(0)),
                  float(u)/float(getDefinitionRange().getNumSteps(1)),
                  float(v)/float(getDefinitionRange().getNumSteps(2)),
                  (X()[t][u][v][3]-Wext.first)/(Wext.second-Wext.first)));
      }
    }
  }
}

void RealFunction::Impl::setDepthCueColors(double Wmax, double Wmin) {
  for(unsigned t = 0;t <= getDefinitionRange().getNumSteps(0) + 1;t++) {
    for(unsigned u = 0;u <= getDefinitionRange().getNumSteps(1) + 1;u++) {
      for(unsigned v = 0;v <= getDefinitionRange().getNumSteps(2) + 1;v++){
        ColMgrMgr::Instance().depthCueColor(Wmax, Wmin,
                                            Xtrans()[t][u][v][3],
                                            X()[t][u][v]);
      }
    }
  }
}

std::pair< double, double > RealFunction::Impl::findExtremesInW() const {

  double Wmin = 0., Wmax = 0.;
  for (unsigned t = 0; t < getDefinitionRange().getNumSteps(0); t++) {
    for (unsigned u = 0; u <= getDefinitionRange().getNumSteps(1)+1; u++) {
      for (unsigned v = 0; v <= getDefinitionRange().getNumSteps(2)+1; v++) {
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
  for (unsigned u = 0; u <= getDefinitionRange().getNumSteps(1); u++)
    DrawStrip (t, u, view);
}

/// Draw the current strip of the projected Function
/** \param t current t value
 *  \param u current u value                                                  */
void RealFunction::Impl::DrawStrip (unsigned t, unsigned u, UI::View *view){
  for (unsigned v = 0; v <= getDefinitionRange().getNumSteps(2); v++)
    DrawCube (t, u, v, view);
}

/// Draw the current cube or cell of the projected Function
/** \param t current t value
 *  \param u current u value
 *  \param v current v value                                                  */
void RealFunction::Impl::DrawCube (unsigned t, unsigned u, unsigned v, UI::View* view) {
    /// \todo don't use a malloc'ed pointer
    static Vector<3> *V = new Vector<3> [8];

    V[0] = Xscr()[t][u][v];     V[1] = Xscr()[t][u][v+1];
    V[2] = Xscr()[t][u+1][v];   V[3] = Xscr()[t][u+1][v+1];
    V[4] = Xscr()[t+1][u][v];   V[5] = Xscr()[t+1][u][v+1];
    V[6] = Xscr()[t+1][u+1][v]; V[7] = Xscr()[t+1][u+1][v+1];

    view->drawCube(X(), t, u, v,
                   V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);
}

/** RealFunction c'tor given only a name: All grid values are set to defaults
 *  \todo don't initialize the grid!
 */
RealFunction::RealFunction():
  FunctionHolder<4, 3, double>(ParameterMap()),
  pImpl_(new Impl(this)) { }

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
  FunctionHolder<4, 3, double>(parms),
  pImpl_(new Impl(this)) {
  setDefinitionRange(tmin, tmax, dt, umin, umax, du, vmin, vmax, dv);
}

RealFunction::~RealFunction() { }

void RealFunction::Initialize () {

  Vector<3, unsigned> numSteps = getDefinitionRange().getNumSteps();
  Vector<3, double> min = getDefinitionRange().getMinValue();
  Vector<3, double> max = getDefinitionRange().getMaxValue();

#ifdef DEBUG_NUM_STEPS
  std::cerr << "RealFunction::Initialize (): num steps = " << numSteps << std::endl;
#endif
  setX(
    FunctionValueGrid<4, 3>(
      _function, numSteps+Vector<3, unsigned>(2), min, max
    )
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

/** \todo get rid of this function. */
unsigned int RealFunction::getNumParameters() {
    return Function::getNumParameters();
}

/// Re-initialize a RealFunction if the definition set has changed
void RealFunction::ReInit(double tmin, double tmax, double dt,
                          double umin, double umax, double du,
                          double vmin, double vmax, double dv) {
  setDefinitionRange(tmin, tmax, dt, umin, umax, du, vmin, vmax, dv);
  Initialize ();
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
