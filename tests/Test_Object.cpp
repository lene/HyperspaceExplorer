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

#include "Test_Object.h"

#include "GlobalFunctions.h"
#include "MockView.h"

#include "FunctionFactory.h"
#include "ColorManager.h"

#include "ObjectImplementations.h"

#include "Vector.impl.h"
#include "Rotation.impl.h"

using namespace UnitTests;

using VecMath::Vector;
using VecMath::Rotation;

using std::cerr;
using std::endl;
using std::string;

class Test_Object::ObjectTestImplementation: public Object {

  public:
    ObjectTestImplementation();

    virtual std::string getFunctionName() const { return TEST_FUNCTION_NAME.toStdString(); }

    VecMath::Vector<4> function_value(double tt, double uu, double vv) { return operator()(tt,uu,vv); }
//    VecMath::MultiDimensionalVector<VecMath::Vector<4>, 3> vertices() { return X(); }
//    VecMath::MultiDimensionalVector<VecMath::Vector<4>, 3> transformed_vertices() { return Xtrans(); }
//    VecMath::MultiDimensionalVector<VecMath::Vector<3>, 3> projected_vertices() { return Xscr(); }

};

const QString Test_Object::TEST_FUNCTION_NAME = "FunctionTestImplementation";


Test_Object::ObjectTestImplementation::ObjectTestImplementation():
    Object(0,0) {
  for (unsigned i = 0; i < NUM_PARAMETERS; ++i) {
    std::ostringstream o;
    o << "parameter " << i;
    declareParameter(o.str(), (double)i);
  }
  Initialize();
}

void Test_Object::initTestCase() {
    ColMgrMgr::Instance().setColorManager("XYZ to RGB");
}

void Test_Object::init() {
  view_ = new MockView;
  object_ = new ObjectTestImplementation;
}

void Test_Object::getDefinitionSpaceDimensions() {
  testEqual(object_->getDefinitionSpaceDimensions(), 0);
}

void Test_Object::getNumParameters() {
  testEqual(object_->getNumParameters(), NUM_PARAMETERS);
}

void Test_Object::meetsFormalRequirements() {
    testEqual(object_->getFunctionName(), Test_Object::TEST_FUNCTION_NAME.toStdString());
}


void Test_Object::ReInit() { }


void Test_Object::rotateAboutAllAxes() {

  object_->Transform(Rotation<4>(90., 0., 0., 0., 0., 90.), Vector<4>());

//    testGreaterEqual(function_->transformed_vertices().size(), GRID_SIZE);
  try {
    object_->for_each_vertex_transformed(testVerticesNotEqual);
  } catch (const NotYetImplementedException &e) {
    QSKIP(e.what(), SkipSingle);
  }
}

void Test_Object::rotated360DegreesIsIdentical() {
  object_->Transform(Rotation<4>(360., 360., 360., 360., 360., 360.), Vector<4>());

  try {
    object_->for_each_vertex_transformed(testVerticesEqual);
  } catch (const NotYetImplementedException &e) {
    QSKIP(e.what(), SkipSingle);
  }
}

void Test_Object::project() {

  object_->Transform(Rotation<4>(), Vector<4>());
  object_->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, false);

  setProjectionParameters(PROJECTION_CAMERA_W, PROJECTION_SCREEN_W);
  try {
    object_->for_each_vertex_transformed_projected(checkProjectedVertex);
  } catch (const NotYetImplementedException &e) {
    QSKIP(e.what(), SkipSingle);
  }

}

void checkGetColorRuns_2(const VecMath::Vector<4> &x,
                       const VecMath::Vector<4> &,
                       const VecMath::Vector<3> &) {
  Color rgba = ColMgrMgr::Instance().getColor(x);
}

void Test_Object::projectWithDepthCue() {

  object_->Transform(Rotation<4>(), Vector<4>());
  object_->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, true);

  try {
    object_->for_each_vertex_transformed_projected(checkGetColorRuns_2);
  } catch (const NotYetImplementedException &e) {
    QSKIP(e.what(), SkipSingle);
  }

    QSKIP("All W values are equal. \nThus the color for all vertices is equal. \n"
          "Nothing meaningful to test. \nTo do: write a class with varying function values.",
          SkipSingle);
}


void Test_Object::draw() {

    object_->Transform(Rotation<4>(), Vector<4>());
    object_->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, false);

    object_->Draw(view_);

//    testGreaterEqual(view_->numVerticesDrawn(), (GRID_SIZE+1)*(GRID_SIZE+1)*(GRID_SIZE+1));

    setGlobalView(view_);

    object_->for_each_vertex(checkVertexPresent);
    object_->for_each_projected(checkVertexDrawn);
}

void Test_Object::tesseract() {
  Hypercube f(1.);
  testFunction(&f);
  testDynamicallyCreatedFunction("Tesseract");
}

void Test_Object::pentachoron()
{

}

void Test_Object::mengersponge()
{

}

void Test_Object::altmengersponge()
{

}

void Test_Object::sierpinskigasket()
{

}


void Test_Object::testFunction(Object *f) {

  testGetParametersRuns(f);

  testDrawDrawsAllVertices(f);

  testNonzeroRotationRuns(f);

  testReinitRuns(f);
}

void testGetParametersRuns(Object * f) {
  ParameterMap parameters = f->getParameters();
}

void Test_Object::testDrawDrawsAllVertices(Object * f) {
  f->Transform(VecMath::Rotation<4>(), VecMath::Vector<4>());
  f->Project(2., 4., false);
  f->Draw(view_);

  testAllVerticesDrawn(f);
}

void Test_Object::testNonzeroRotationRuns(Object * f) {
  qsrand(1);

  VecMath::Rotation<4> r(random_number<double>(), random_number<double>(), random_number<double>(),
                         random_number<double>(), random_number<double>(), random_number<double>());
  VecMath::Vector<4> t(random_number<double>(), random_number<double>(),
                       random_number<double>(), random_number<double>());

  f->Transform(r, t, Vector<4>(1.));
  f->Project(2., 4., false);
  f->Draw(view_);
}

void testReinitRuns(Object * f) {
  f->ReInit(-2., 2., 0.8, -2., 2., 0.8, -2., 2., 1.0);
}

void Test_Object::testAllVerticesDrawn(Object *f) {
  setGlobalView(view_);
  f->for_each_vertex(checkVertexPresent);
}

void Test_Object::testDynamicallyCreatedFunction(const std::string& fname) {
  Object *f;
  try {
     f = dynamic_cast<Object *>(TheFunctionFactory::Instance().createFunction(fname));
  } catch (const FunctionFactory::BadFunctionException &e) {
    QFAIL(e.what());
  }
  QVERIFY2(f != NULL, "creating failed!");
  f->ReInit(-1., 1., 1., -1., 1., 1., -1., 1., 1.);

  testGetParametersRuns(f);

  testDrawDrawsAllVertices(f);

  testNonzeroRotationRuns(f);

}
