
#include "Test_Surface.h"

#include "MockView.h"

#include "SurfaceImplementations.h"
#include "ComplexFunction.h"
#include "ColorManager.h"

#include "Vector.impl.h"
#include "MultiDimensionalVector.impl.h"
#include "Rotation.impl.h"

#include <tr1/memory>

using VecMath::Vector;
using VecMath::Rotation;
using std::cerr;
using std::endl;
using std::string;
using std::tr1::shared_ptr;

void testFunction(Surface &f);

const std::string Test_Surface::TEST_FUNCTION_NAME = "FunctionTestImplementation";

Test_Surface::SurfaceTestImplementation::SurfaceTestImplementation():
    Surface(X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1),
            X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1)) {
  _function = shared_ptr< ParametricFunction<4, 2> >(new DefiningFunction);
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
  _function = new SurfaceTestImplementation();

  for (double x = X_MIN; x <= X_MAX; x += 1.) {
    for (double y = X_MIN; y <= X_MAX; y += 1.) {
      cerr << Vector<4>(x, y, CONSTANT_FUNCTION_VALUE,CONSTANT_FUNCTION_VALUE) << endl;
      QVERIFY2(
        VecMath::sqnorm(_function->function_value(x, y) - Vector<4>(x, y, CONSTANT_FUNCTION_VALUE,CONSTANT_FUNCTION_VALUE)) <= EPSILON,
        (QString::number(x).toStdString()+", "+QString::number(y).toStdString()+" -> "+_function->function_value(x, y).toString()+
         " != "+Vector<4>(x, y, CONSTANT_FUNCTION_VALUE,CONSTANT_FUNCTION_VALUE).toString()).c_str()
        );
    }
  }
}

void Test_Surface::meetsFormalRequirements() {
  _function = new SurfaceTestImplementation();

  QVERIFY(_function->getDefinitionSpaceDimensions() == 2);
  QVERIFY(_function->vertices().size() >= GRID_SIZE);
  QVERIFY(_function->vertices()[0].size() >= GRID_SIZE);

  QVERIFY(_function->getFunctionName() == Test_Surface::TEST_FUNCTION_NAME);
}

void Test_Surface::boundsAndSteps() {
  _function = new SurfaceTestImplementation();
  QVERIFY(_function->xsteps() == GRID_SIZE);
  QVERIFY(_function->ysteps() == GRID_SIZE);
}

void Test_Surface::rotateAboutAllAxes() {
  _function = new SurfaceTestImplementation();

  _function->Transform(Rotation<4>(90., 0., 0., 0., 0., 90.), Vector<4>());

  QVERIFY(_function->transformed_vertices().size() >= GRID_SIZE);
  QVERIFY(_function->transformed_vertices()[0].size() >= GRID_SIZE);

  for (unsigned i = 0; i < GRID_SIZE; ++i) {
    for (unsigned j = 0; j < GRID_SIZE; ++j) {
      Vector<4> vertex = _function->vertices()[i][j],
                transformed_vertex = _function->transformed_vertices()[i][j];
      QVERIFY(VecMath::sqnorm(vertex - transformed_vertex) > EPSILON);
    }
  }
}

void Test_Surface::rotated360DegreesIsIdentical() {
  _function = new SurfaceTestImplementation();

  _function->Transform(Rotation<4>(360., 360., 360., 360., 360., 360.), Vector<4>());

  for (unsigned i = 0; i < GRID_SIZE; ++i) {
    for (unsigned j = 0; j < GRID_SIZE; ++j) {
      Vector<4> vertex = _function->vertices()[i][j],
                transformed_vertex = _function->transformed_vertices()[i][j];
      QVERIFY(VecMath::sqnorm(vertex - transformed_vertex) < EPSILON);
    }
  }
}

void Test_Surface::project() {
  _function = new SurfaceTestImplementation();

  _function->Transform(Rotation<4>(), Vector<4>());
  _function->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, false);

  QVERIFY(_function->projected_vertices().size() >= GRID_SIZE);
  QVERIFY(_function->projected_vertices()[0].size() >= GRID_SIZE);

  // intercept theorem gives this factor (constant because f is constant)
  const double PROJECTION_FACTOR =
            (PROJECTION_CAMERA_W-PROJECTION_SCREEN_W) /
            (PROJECTION_CAMERA_W-CONSTANT_FUNCTION_VALUE);

  for (unsigned i = 0; i < GRID_SIZE; ++i) {
    for (unsigned j = 0; j < GRID_SIZE; ++j) {
      Vector<4> vertex = _function->vertices()[i][j];
      Vector<3> projected_vertex = _function->projected_vertices()[i][j];
      for(unsigned m = 0; m < 3; ++m) {
        QVERIFY(fabs(projected_vertex[m] - vertex[m]*PROJECTION_FACTOR) < EPSILON);
      }
    }
  }
}

void Test_Surface::projectWithDepthCue() {
  _function = new SurfaceTestImplementation();

  _function->Transform(Rotation<4>(), Vector<4>());
  _function->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, true);

  for (unsigned i = 0; i < GRID_SIZE; ++i) {
    for (unsigned j = 0; j < GRID_SIZE; ++j) {
      Vector<4> vertex = _function->vertices()[i][j];
      Vector<3> projected_vertex = _function->projected_vertices()[i][j];
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
  _function = new SurfaceTestImplementation();

  _function->Transform(Rotation<4>(), Vector<4>());
  _function->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, false);

  _function->Draw(view_);

  QSKIP("No idea how to correctly test drawing yet", SkipSingle);
}

void Test_Surface::surface1() {
  Surface1 f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::horizon() {
  Horizon f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::torus3() {
  Torus3 f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::t_z2() {
  z2 f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::t_z3() {
  z3 f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::t_zA() {
  zA f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::t_ez() {
  ez f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::t_emz2() {
  emz2 f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::t_zm1() {
  zm1 f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::t_zm2() {
  zm2 f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::t_sqrtz() {
  sqrtz f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::t_lnz() {
  lnz f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::t_sinz() {
  sinz  f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::t_cosz() {
  cosz f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::t_sinhz() {
  sinhz f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::t_coshz() {
  coshz f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}
void Test_Surface::t_tanz() {
  tanz f(-1., 1., 0.5, -1., 1., 0.5);
  testFunction(f);
}

template<typename T> T random_number() {
  return (T)qrand()/(T)RAND_MAX;
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