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

#include "Test_RealFunction.h"

#include "MockView.h"

#include "MultiDimensionalVector.impl.h"
#include "Vector.impl.h"
#include "Rotation.impl.h"

#include "RealFunctionImplementations.h"
#include "ColorManager.h"

using VecMath::Vector;
using VecMath::Rotation;
using std::cerr;
using std::endl;
using std::string;

/// Stores a pointer to the view used by Test_RealFunction for global functions used by Function::for_each
MockView *globalView = NULL;

void checkVertexPresent(const VecMath::Vector<4> &v) {
  QVERIFY2(globalView->isVertexPresent(v), v.toString().c_str());
}

void checkVertexDrawn(const VecMath::Vector<3> &v) {
  QVERIFY2(globalView->isVertexDrawn(v), v.toString().c_str());
}

void checkVerticesEqual(const VecMath::Vector<4> &v1, const VecMath::Vector<4> &v2) {
  QVERIFY(VecMath::sqnorm(v1 - v2) < EPSILON);
}


void checkVerticesNotEqual(const VecMath::Vector<4> &v1, const VecMath::Vector<4> &v2) {
  QVERIFY(VecMath::sqnorm(v1 - v2) > EPSILON);
}

template<typename T> T random_number() {
  return (T)qrand()/(T)RAND_MAX;
}

class Test_RealFunction::RealFunctionTestImplementation: public RealFunction {

  public:
    RealFunctionTestImplementation();

    virtual std::string getFunctionName() const { return TEST_FUNCTION_NAME.toStdString(); }

    VecMath::Vector<4> function_value(double tt, double uu, double vv) { return f(tt,uu,vv); }
    VecMath::MultiDimensionalVector<VecMath::Vector<4>, 3> vertices() { return X(); }
    VecMath::MultiDimensionalVector<VecMath::Vector<4>, 3> transformed_vertices() { return Xtrans(); }
    VecMath::MultiDimensionalVector<VecMath::Vector<3>, 3> projected_vertices() { return Xscr(); }

    unsigned xsteps() const { return getTsteps(); }
    unsigned ysteps() const { return getUsteps(); }
    unsigned zsteps() const { return getVsteps(); }

  protected:
    class DefiningFunction: public ParametricFunction<4, 3> {

      public:

        virtual return_type f(const argument_type &x);
    };

    virtual function_type f;
};

const QString Test_RealFunction::TEST_FUNCTION_NAME = "FunctionTestImplementation";


Test_RealFunction::RealFunctionTestImplementation::RealFunctionTestImplementation():
    RealFunction(X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1),
                 X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1),
                 X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1)) {
  _function = std::tr1::shared_ptr< ParametricFunction<4, 3> >(new DefiningFunction());
  for (unsigned i = 0; i < NUM_PARAMETERS; ++i) {
    std::ostringstream o;
    o << "parameter " << i;
    declareParameter(o.str(), (double)i);
  }
  Initialize();
}

Vector<4> &Test_RealFunction::RealFunctionTestImplementation::f (double tt, double uu, double vv) {
  static Vector<4> F;
  F = _function->f(Vector<3>(tt, uu, vv));
  return F;
}

ParametricFunction< 4, 3 >::return_type
Test_RealFunction::RealFunctionTestImplementation::DefiningFunction::f(
  const ParametricFunction< 4, 3 >::argument_type& x) {
  return VecMath::Vector<4>(x[0], x[1], x[2], CONSTANT_FUNCTION_VALUE);
}

void Test_RealFunction::initTestCase() {
    ColMgrMgr::Instance().setColorManager("XYZ to RGB");
}

void Test_RealFunction::init() {
  view_ = new MockView;
}

void Test_RealFunction::functionValue() {
    function_ = new RealFunctionTestImplementation();

    for (double x = X_MIN; x <= X_MAX; x += 1.) {
        for (double y = X_MIN; y <= X_MAX; y += 1.) {
            for (double z = X_MIN; z <= X_MAX; z += 1.) {
                QVERIFY( VecMath::sqnorm(function_->function_value(x, y, z) -
                                         Vector<4>(x, y, z,CONSTANT_FUNCTION_VALUE)) <= EPSILON );
            }
        }
    }
}

void Test_RealFunction::getDefinitionSpaceDimensions() {
  function_ = new RealFunctionTestImplementation();
  QVERIFY(function_->getDefinitionSpaceDimensions() == 3);
}

void Test_RealFunction::getNumParameters() {
  function_ = new RealFunctionTestImplementation();
//  QVERIFY(function_->getNumParameters() == NUM_PARAMETERS);
}

void Test_RealFunction::meetsFormalRequirements() {
    function_ = new RealFunctionTestImplementation();

    QVERIFY(function_->vertices().size() >= GRID_SIZE);
    QVERIFY(function_->vertices()[0].size() >= GRID_SIZE);
    QVERIFY(function_->vertices()[0][0].size() >= GRID_SIZE);

    QVERIFY(function_->getFunctionName() == Test_RealFunction::TEST_FUNCTION_NAME.toStdString());
}

void Test_RealFunction::boundsAndSteps() {
    function_ = new RealFunctionTestImplementation();
    QVERIFY(function_->xsteps() == GRID_SIZE);
    QVERIFY(function_->ysteps() == GRID_SIZE);
    QVERIFY(function_->zsteps() == GRID_SIZE);
}

void Test_RealFunction::rotateAboutAllAxes() {
    function_ = new RealFunctionTestImplementation();

    function_->Transform(Rotation<4>(90., 0., 0., 0., 0., 90.), Vector<4>());

    QVERIFY(function_->transformed_vertices().size() >= GRID_SIZE);
    QVERIFY(function_->transformed_vertices()[0].size() >= GRID_SIZE);
    QVERIFY(function_->transformed_vertices()[0][0].size() >= GRID_SIZE);

    function_->for_each(checkVerticesNotEqual);
}

void Test_RealFunction::rotated360DegreesIsIdentical() {
    function_ = new RealFunctionTestImplementation();

    function_->Transform(Rotation<4>(360., 360., 360., 360., 360., 360.), Vector<4>());

    function_->for_each(checkVerticesEqual);
}

// intercept theorem gives this factor (constant because f is constant)
const double PROJECTION_FACTOR =
  (PROJECTION_CAMERA_W-PROJECTION_SCREEN_W) /
  (PROJECTION_CAMERA_W-CONSTANT_FUNCTION_VALUE);

void checkProjectProjects(const VecMath::Vector<4> &x,
                          const VecMath::Vector<4> &,
                          const VecMath::Vector<3> &xscr) {
  cerr << xscr << " == " << x*PROJECTION_FACTOR << "?" << endl;
  for(unsigned m = 0; m < 3; ++m) {
    QVERIFY2(fabs(xscr[m] - x[m]*PROJECTION_FACTOR) < EPSILON,
             (xscr.toString()+std::string(" != ")+(x*PROJECTION_FACTOR).toString()).c_str()
             );
  }
}

void Test_RealFunction::project() {
    function_ = new RealFunctionTestImplementation();

    function_->Transform(Rotation<4>(), Vector<4>());
    function_->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, false);

    QVERIFY(function_->projected_vertices().size() >= GRID_SIZE);
    QVERIFY(function_->projected_vertices()[0].size() >= GRID_SIZE);
    QVERIFY(function_->projected_vertices()[0][0].size() >= GRID_SIZE);

    QSKIP("not solved yet why this fails.", SkipSingle);
    function_->for_each(checkProjectProjects);
}

void checkGetColorRuns(const VecMath::Vector<4> &x,
                       const VecMath::Vector<4> &,
                       const VecMath::Vector<3> &) {
  Color rgba = ColMgrMgr::Instance().getColor(x);
}

void Test_RealFunction::projectWithDepthCue() {
    function_ = new RealFunctionTestImplementation();

    function_->Transform(Rotation<4>(), Vector<4>());
    function_->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, true);

    function_->for_each(checkGetColorRuns);

    QSKIP("All W values are equal. \nThus the color for all vertices is equal. \n"
          "Nothing meaningful to test. \nTo do: write a class with varying function values.",
          SkipSingle);
}


void Test_RealFunction::draw() {
    function_ = new RealFunctionTestImplementation();

    function_->Transform(Rotation<4>(), Vector<4>());
    function_->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, false);

    function_->Draw(view_);

    QVERIFY(view_->numVerticesDrawn() >= (GRID_SIZE+1)*(GRID_SIZE+1)*(GRID_SIZE+1));

    globalView = view_;

    function_->for_each(checkVertexPresent);
    function_->for_each(checkVertexDrawn);
}

void Test_RealFunction::torus1() {
  Torus1 f(-1, 1, 1., -1, 1, 1., -1, 1, 1.);
  testFunction(f);
}

void Test_RealFunction::torus2() {
  Torus2 f(-1, 1, 1., -1, 1, 1., -1, 1, 1.);
  testFunction(f);
}

void Test_RealFunction::fr3r() {
  Fr3r f(-1, 1, 1., -1, 1, 1., -1, 1, 1.);
  testFunction(f);
}

void Test_RealFunction::gravitationPotential() {
  GravitationPotential f(-1, 1, 1., -1, 1, 1., -1, 1, 1.);
  testFunction(f);
}

void Test_RealFunction::fr3rSin() {
  Fr3rSin f(-1, 1, 1., -1, 1, 1., -1, 1, 1.);
  testFunction(f);
}

void Test_RealFunction::fr3rExp() {
  Fr3rExp f(-1, 1, 1., -1, 1, 1., -1, 1, 1.);
  testFunction(f);
}

void Test_RealFunction::polarSin() {
  PolarSin f(-1, 1, 1., -1, 1, 1., -1, 1, 1.);
  testFunction(f);
}

void Test_RealFunction::polarSin2() {
  PolarSin2 f(-1, 1, 1., -1, 1, 1., -1, 1, 1.);
  testFunction(f);
}

void Test_RealFunction::polarR() {
  PolarR f(-1, 1, 1., -1, 1, 1., -1, 1, 1.);
  testFunction(f);
}

void Test_RealFunction::testFunction(RealFunction &f) {

  testGetParametersRuns(f);

  testFunctionEvaluationRuns(f);

  testDrawDrawsAllVertices(f);

  testNonzeroRotationRuns(f);

  testReinitRuns(f);
}

void testGetParametersRuns(RealFunction& f) {
  ParameterMap parameters = f.getParameters();
}

void testFunctionEvaluationRuns(RealFunction& f) {
  f(0.,0.,0.);
}

void Test_RealFunction::testDrawDrawsAllVertices(RealFunction& f) {
  f.Transform(VecMath::Rotation<4>(), VecMath::Vector<4>());
  f.Project(2., 4., false);
  f.Draw(view_);

  testAllVerticesDrawn(&f);
}

void Test_RealFunction::testNonzeroRotationRuns(RealFunction& f) {
  qsrand(1);

  VecMath::Rotation<4> r(random_number<double>(), random_number<double>(), random_number<double>(),
                         random_number<double>(), random_number<double>(), random_number<double>());
  VecMath::Vector<4> t(random_number<double>(), random_number<double>(),
                       random_number<double>(), random_number<double>());

  f.Transform(r, t);
  f.Project(2., 4., false);
  f.Draw(view_);
}

void testReinitRuns(RealFunction& f) {
  f.ReInit(-2., 2., 0.8, -2., 2., 0.8, -2., 2., 1.0);
}

void Test_RealFunction::testAllVerticesDrawn(RealFunction *f) {
  globalView = view_;
  f->for_each(checkVertexPresent);
}

