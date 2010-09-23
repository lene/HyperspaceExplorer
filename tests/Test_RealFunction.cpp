
#include "Test_RealFunction.h"

#include "MockView.h"

#include "RealFunction.h"
#include "ColorManager.h"

using VecMath::Vector;
using VecMath::Rotation;
using std::cerr;
using std::endl;
using std::string;

const QString Test_RealFunction::TEST_FUNCTION_NAME = "FunctionTestImplementation";


Test_RealFunction::RealFunctionTestImplementation::RealFunctionTestImplementation():
    RealFunction(X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1),
                 X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1),
                 X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1)) {
    _function = std::tr1::shared_ptr< ParametricFunction<4, 3> >(new DefiningFunction());
  Initialize();
}

Vector<4> &Test_RealFunction::RealFunctionTestImplementation::f (double tt, double uu, double vv) {
  _F = _function->f(Vector<3>(tt, uu, vv));
  return _F;
}

ParametricFunction< 4, 3 >::return_type
Test_RealFunction::RealFunctionTestImplementation::DefiningFunction::f(
  const ParametricFunction< 4, 3 >::argument_type& x) {
  return VecMath::Vector<4>(x[0], x[1], x[2], CONSTANT_FUNCTION_VALUE);
}

void Test_RealFunction::initTestCase() {
    ColMgrMgr::Instance().setColorManager("XYZ to RGB");
    view_ = new MockView;
}

void Test_RealFunction::cleanupTestCase() { }

void Test_RealFunction::functionValue() {
    function_ = new RealFunctionTestImplementation();

    for (double x = X_MIN; x <= X_MAX; x += 1.) {
        for (double y = X_MIN; y <= X_MAX; y += 1.) {
            for (double z = X_MIN; z <= X_MAX; z += 1.) {
                QVERIFY( (function_->function_value(x, y, z) - Vector<4>(x, y, z,CONSTANT_FUNCTION_VALUE)).sqnorm() <= EPSILON );
            }
        }
    }
}

void Test_RealFunction::meetsFormalRequirements() {
    function_ = new RealFunctionTestImplementation();

    QVERIFY(function_->getDefinitionSpaceDimensions() == 3);
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

    for (unsigned i = 0; i < GRID_SIZE; ++i) {
        for (unsigned j = 0; j < GRID_SIZE; ++j) {
            for (unsigned k = 0; k < GRID_SIZE; ++k) {
                Vector<4> vertex = function_->vertices()[i][j][k],
                          transformed_vertex = function_->transformed_vertices()[i][j][k];
                QVERIFY((vertex - transformed_vertex).sqnorm() > EPSILON);
            }
        }
    }
}

void Test_RealFunction::rotated360DegreesIsIdentical() {
    function_ = new RealFunctionTestImplementation();

    function_->Transform(Rotation<4>(360., 360., 360., 360., 360., 360.), Vector<4>());

    for (unsigned i = 0; i < GRID_SIZE; ++i) {
        for (unsigned j = 0; j < GRID_SIZE; ++j) {
            for (unsigned k = 0; k < GRID_SIZE; ++k) {
                Vector<4> vertex = function_->vertices()[i][j][k],
                          transformed_vertex = function_->transformed_vertices()[i][j][k];
                QVERIFY((vertex - transformed_vertex).sqnorm() < EPSILON);
            }
        }
    }
}

void Test_RealFunction::project() {
    function_ = new RealFunctionTestImplementation();

    function_->Transform(Rotation<4>(), Vector<4>());
    function_->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, false);

    QVERIFY(function_->projected_vertices().size() >= GRID_SIZE);
    QVERIFY(function_->projected_vertices()[0].size() >= GRID_SIZE);
    QVERIFY(function_->projected_vertices()[0][0].size() >= GRID_SIZE);

    // intercept theorem gives this factor (constant because f is constant)
    const double PROJECTION_FACTOR =
            (PROJECTION_CAMERA_W-PROJECTION_SCREEN_W) /
            (PROJECTION_CAMERA_W-CONSTANT_FUNCTION_VALUE);

    for (unsigned i = 0; i < GRID_SIZE; ++i) {
        for (unsigned j = 0; j < GRID_SIZE; ++j) {
            for (unsigned k = 0; k < GRID_SIZE; ++k) {
                Vector<4> vertex = function_->vertices()[i][j][k];
                Vector<3> projected_vertex = function_->projected_vertices()[i][j][k];
                cerr << projected_vertex << " == " << vertex*PROJECTION_FACTOR << "?" << endl;
                QSKIP("not solved yet why this fails.", SkipSingle);
                for(unsigned m = 0; m < 3; ++m) {
                    QVERIFY2(fabs(projected_vertex[m] - vertex[m]*PROJECTION_FACTOR) < EPSILON,
                             (projected_vertex.toString()+std::string(" != ")+(vertex*PROJECTION_FACTOR).toString()).c_str()
                             );
                }
            }
        }
    }
}

void Test_RealFunction::projectWithDepthCue() {
    function_ = new RealFunctionTestImplementation();

    function_->Transform(Rotation<4>(), Vector<4>());
    function_->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, true);

    for (unsigned i = 0; i < GRID_SIZE; ++i) {
        for (unsigned j = 0; j < GRID_SIZE; ++j) {
            for (unsigned k = 0; k < GRID_SIZE; ++k) {
                Vector<4> vertex = function_->vertices()[i][j][k];
                Vector<3> projected_vertex = function_->projected_vertices()[i][j][k];
                Color rgba = ColMgrMgr::Instance().getColor(vertex);

//                cerr << vertex << " : " << projected_vertex << " " <<string(rgba).c_str()
//                     << endl;
            }
        }
    }

    QSKIP("All W values are equal. \nThus the color for all vertices is equal. \n"
          "Nothing meaningful to test. \nTo do: write a class with varying function values.",
          SkipSingle);
}

void Test_RealFunction::draw() {
    function_ = new RealFunctionTestImplementation();

    function_->Transform(Rotation<4>(), Vector<4>());
    function_->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, false);

    function_->Draw(view_);

    QSKIP("No idea how to correctly test drawing yet", SkipSingle);
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

template<typename T> T random_number() {
  return (T)qrand()/(T)RAND_MAX;
}

void Test_RealFunction::testFunction(RealFunction &f) {
  qsrand(1);
  ParameterMap parameters = f.getParameters();
//  cerr << f.getFunctionName().toStdString() << " parameters ("<< parameters.size() << "): " << parameters.toString() << endl;
  f(0.,0.,0.);
  VecMath::Rotation<4> r(random_number<double>(), random_number<double>(), random_number<double>(), random_number<double>(), random_number<double>(), random_number<double>());
  VecMath::Vector<4> t(random_number<double>(), random_number<double>(), random_number<double>(), random_number<double>());
  f.Transform(r, t);
  f.Project(2., 4., false);
  f.Draw(view_);
  f.ReInit(-2., 2., 0.8, -2., 2., 0.8, -2., 2., 1.0);
}
