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

#include "Test_Surface.h"

#include "MockView.h"

#include "Surface/SurfaceImplementations.h"
#include "ColorManager.h"
#include "FunctionFactory.h"

#include "Vector.impl.h"
#include "MultiDimensionalVector.impl.h"
#include "Rotation.impl.h"
#include "GridDrawer.impl.h"

#include <memory>
#include <FunctionFactory.h>
#include <Util.h>

using VecMath::Vector;
using VecMath::Rotation;
using std::cerr;
using std::endl;
using std::string;
using std::shared_ptr;

using namespace UnitTests;

class Test_Surface::SurfaceTestImplementation: public Surface {

public:
  SurfaceTestImplementation();
  virtual std::string getFunctionName() const { return TEST_FUNCTION_NAME; }

  VecMath::Vector<4> function_value(double tt, double uu) { return _function->f(VecMath::Vector<2>(tt,uu)); }
  VecMath::MultiDimensionalVector< VecMath::Vector<4>, 2 > vertices() {
    return X();
  }
  VecMath::MultiDimensionalVector< VecMath::Vector<4>, 2 > transformed_vertices() { return Xtrans(); }
  VecMath::MultiDimensionalVector< VecMath::Vector<3>, 2 > projected_vertices() { return Xscr(); }

  unsigned xsteps() const { return getDefinitionRange().getNumSteps(0); }
  unsigned ysteps() const { return getDefinitionRange().getNumSteps(1); }

private:

  class DefiningFunction: public ParametricFunction<4, 2> {
  public:
    DefiningFunction(SurfaceTestImplementation *parent): parent_(parent) { }
    virtual return_type f(const argument_type &x);
  private:
    /// Not a smart pointer because it's initialized to \c this and mustn't be deleted
    SurfaceTestImplementation *parent_;
  };

};


const std::string Test_Surface::TEST_FUNCTION_NAME = "FunctionTestImplementation";

Test_Surface::SurfaceTestImplementation::SurfaceTestImplementation():
    Surface(X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1),
            X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1),
            ParameterMap()
           ) {
  _function = shared_ptr< ParametricFunction<4, 2> >(new DefiningFunction(this));
  Initialize();
}

Vector<4> Test_Surface::SurfaceTestImplementation::DefiningFunction::f (const Vector<2> &x) {

  Vector<4>F(x[0], x[1], CONSTANT_FUNCTION_VALUE, CONSTANT_FUNCTION_VALUE);
  return F;
}

void Test_Surface::initTestCase() {
    ColMgrMgr::Instance().setColorManager("XYZ to RGB");
}

void Test_Surface::init() {
  view_ = new MockView;
}

void Test_Surface::functionValue() {
  function_ = new SurfaceTestImplementation();

  for (double x = X_MIN; x <= X_MAX; x += 1.) {
    for (double y = X_MIN; y <= X_MAX; y += 1.) {
      QVERIFY2(
        VecMath::sqnorm(function_->function_value(x, y) - Vector<4>(x, y, CONSTANT_FUNCTION_VALUE,CONSTANT_FUNCTION_VALUE)) <= EPSILON,
        (QString::number(x).toStdString()+", "+QString::number(y).toStdString()+" -> "+function_->function_value(x, y).toString()+
         " != "+Vector<4>(x, y, CONSTANT_FUNCTION_VALUE,CONSTANT_FUNCTION_VALUE).toString()).c_str()
        );
    }
  }
}

void Test_Surface::meetsFormalRequirements() {
  function_ = new SurfaceTestImplementation();

  testEqual(function_->getDefinitionSpaceDimensions(), 2);
  testGreaterEqual(function_->vertices().size(), GRID_SIZE);
  testGreaterEqual(function_->vertices()[0].size(), GRID_SIZE);
  testEqual(function_->getFunctionName(), Test_Surface::TEST_FUNCTION_NAME);
}

void Test_Surface::boundsAndSteps() {
  function_ = new SurfaceTestImplementation();
  testEqual(function_->xsteps(), GRID_SIZE);
  testEqual(function_->ysteps(), GRID_SIZE);
}

void Test_Surface::getNumParameters() {
  function_ = new SurfaceTestImplementation();
  testEqual(function_->getNumParameters(), 0);
}

void Test_Surface::rotateAboutAllAxes() {
  function_ = new SurfaceTestImplementation();

  function_->Transform(Rotation<4>(90., 0., 0., 0., 0., 90.), Vector<4>());

  testGreaterEqual(function_->transformed_vertices().size(), GRID_SIZE);
  testGreaterEqual(function_->transformed_vertices()[0].size(), GRID_SIZE);

  for (unsigned i = 0; i < GRID_SIZE; ++i) {
    for (unsigned j = 0; j < GRID_SIZE; ++j) {
      Vector<4> vertex = function_->vertices()[i][j],
                transformed_vertex = function_->transformed_vertices()[i][j];
      QVERIFY(VecMath::sqnorm(vertex - transformed_vertex) > EPSILON);
    }
  }
}

void Test_Surface::rotated360DegreesIsIdentical() {
  function_ = new SurfaceTestImplementation();

  function_->Transform(Rotation<4>(360., 360., 360., 360., 360., 360.), Vector<4>());

  for (unsigned i = 0; i < GRID_SIZE; ++i) {
    for (unsigned j = 0; j < GRID_SIZE; ++j) {
      Vector<4> vertex = function_->vertices()[i][j],
                transformed_vertex = function_->transformed_vertices()[i][j];
      QVERIFY(VecMath::sqnorm(vertex - transformed_vertex) < EPSILON);
    }
  }
}

void Test_Surface::project() {
  function_ = new SurfaceTestImplementation();

  function_->Transform(Rotation<4>(), Vector<4>());
  function_->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, false);

  testGreaterEqual(function_->projected_vertices().size(), GRID_SIZE);
  testGreaterEqual(function_->projected_vertices()[0].size(), GRID_SIZE);

  // intercept theorem gives this factor (constant because f is constant)
  const double PROJECTION_FACTOR =
            (PROJECTION_CAMERA_W-PROJECTION_SCREEN_W) /
            (PROJECTION_CAMERA_W-CONSTANT_FUNCTION_VALUE);

  for (unsigned i = 0; i < GRID_SIZE; ++i) {
    for (unsigned j = 0; j < GRID_SIZE; ++j) {
      Vector<4> vertex = function_->vertices()[i][j];
      Vector<3> projected_vertex = function_->projected_vertices()[i][j];
      for(unsigned m = 0; m < 3; ++m) {
        QVERIFY(fabs(projected_vertex[m] - vertex[m]*PROJECTION_FACTOR) < EPSILON);
      }
    }
  }
}

void Test_Surface::projectWithDepthCue() {
  function_ = new SurfaceTestImplementation();

  function_->Transform(Rotation<4>(), Vector<4>());
  function_->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, true);

  for (unsigned i = 0; i < GRID_SIZE; ++i) {
    for (unsigned j = 0; j < GRID_SIZE; ++j) {
      Vector<4> vertex = function_->vertices()[i][j];
      Vector<3> projected_vertex = function_->projected_vertices()[i][j];
      Color rgba = ColMgrMgr::Instance().getColor(vertex);

//                cerr << vertex << " : " << projected_vertex << " " <<string(rgba).c_str()
//                     << endl;
    }
  }

  QSKIP("All W values are equal. \nThus the color for all vertices is equal. \n"
        "Nothing meaningful to test. \nTo do: write a class with varying function values.",
        SkipSingle);
}

void Test_Surface::draw() {
  function_ = new SurfaceTestImplementation();

  function_->Transform(Rotation<4>(), Vector<4>());
  function_->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, false);

  function_->Draw(view_);

  testGreaterEqual(view_->numVerticesDrawn(), (GRID_SIZE+1)*(GRID_SIZE+1));

  UnitTests::setGlobalView(view_);
  function_->for_each_vertex(UnitTests::checkVertexPresent);
  function_->for_each_projected(UnitTests::checkVertexDrawn);
}

void Test_Surface::surface1() {
  performSurfaceTest<Surface1, 0>("Surface1");
}
void Test_Surface::horizon() {
  performSurfaceTest<Horizon, 0>("Horizon");
}
void Test_Surface::torus3() {
  performSurfaceTest<Torus3, 0>("Torus3");
}

void Test_Surface::testFunction(Surface &f) {
  qsrand(1);
  ParameterMap parameters = f.getParameters();
//  cerr << f.getFunctionName().toStdString() << " parameters ("<< parameters.size() << "): " << parameters.toString() << endl;
  f(0.,0.);
  VecMath::Rotation<4> r(random_number<double>(), random_number<double>(), random_number<double>(), random_number<double>(), random_number<double>(), random_number<double>());
  VecMath::Vector<4> t(random_number<double>(), random_number<double>(), random_number<double>(), random_number<double>());
  f.Transform(r, t);
  f.Project(2., 4., false);
  f.Draw(view_);
  f.ReInit(1., 1., 1., -2., 2., 0.2, -2., 2., 0.2);
}

void Test_Surface::testDynamicallyCreatedFunction(const std::string& fname) {
  Surface *f;
  try {
     f = dynamic_cast<Surface *>(TheFunctionFactory::Instance().createFunction(fname));
  } catch (const FunctionFactory::BadFunctionException &e) {
    QFAIL(e.what());
  }
  QVERIFY2(f != NULL, "creating failed!");
  f->ReInit(1., 1., 1., -1., 1., 1., -1., 1., 1.);
  testFunction(*f);

}


