
#include "Test_RealFunction.h"

#include "RealFunction.h"
#include "ColorManager.h"

using VecMath::Vector;
using VecMath::Rotation;
using std::cerr;
using std::endl;
using std::string;

const QString Test_RealFunction::TEST_FUNCTION_NAME = "FunctionTestImplementation";

Test_RealFunction::RealFunctionTestImplementation::RealFunctionTestImplementation():
    RealFunction(
                 Test_RealFunction::TEST_FUNCTION_NAME,
                 X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1),
                 X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1),
                 X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1)) {
  Initialize();
}

Vector<4> &Test_RealFunction::RealFunctionTestImplementation::f (double tt, double uu, double vv) {
    _F[0] = tt;
    _F[1] = uu;
    _F[2] = vv;
    _F[3] = CONSTANT_FUNCTION_VALUE;

    return _F;
}

void Test_RealFunction::initTestCase() {
    ColMgrMgr::Instance().setColorManager("XYZ to RGB");
}

void Test_RealFunction::cleanupTestCase() { }

void Test_RealFunction::functionValue() {
    _function = new RealFunctionTestImplementation();

    for (double x = X_MIN; x <= X_MAX; x += 1.) {
        for (double y = X_MIN; y <= X_MAX; y += 1.) {
            for (double z = X_MIN; z <= X_MAX; z += 1.) {
                QVERIFY( (_function->function_value(x, y, z) - Vector<4>(x, y, z,CONSTANT_FUNCTION_VALUE)).sqnorm() <= EPSILON );
            }
        }
    }
}

void Test_RealFunction::meetsFormalRequirements() {
    _function = new RealFunctionTestImplementation();

    QVERIFY(_function->getDefinitionSpaceDimensions() == 3);
    QVERIFY(_function->vertices().size() >= GRID_SIZE);
    QVERIFY(_function->vertices()[0].size() >= GRID_SIZE);
    QVERIFY(_function->vertices()[0][0].size() >= GRID_SIZE);

    QVERIFY(_function->getFunctionName() == Test_RealFunction::TEST_FUNCTION_NAME);
}

void Test_RealFunction::boundsAndSteps() {
    _function = new RealFunctionTestImplementation();
    QVERIFY(_function->xsteps() == GRID_SIZE);
    QVERIFY(_function->ysteps() == GRID_SIZE);
    QVERIFY(_function->zsteps() == GRID_SIZE);
}

void Test_RealFunction::rotateAboutAllAxes() {
    _function = new RealFunctionTestImplementation();

    _function->Transform(Rotation<4>(90., 0., 0., 0., 0., 90.), Vector<4>());

    QVERIFY(_function->transformed_vertices().size() >= GRID_SIZE);
    QVERIFY(_function->transformed_vertices()[0].size() >= GRID_SIZE);
    QVERIFY(_function->transformed_vertices()[0][0].size() >= GRID_SIZE);

    for (unsigned i = 0; i < GRID_SIZE; ++i) {
        for (unsigned j = 0; j < GRID_SIZE; ++j) {
            for (unsigned k = 0; k < GRID_SIZE; ++k) {
                Vector<4> vertex = _function->vertices()[i][j][k],
                          transformed_vertex = _function->transformed_vertices()[i][j][k];
                QVERIFY((vertex - transformed_vertex).sqnorm() > EPSILON);
            }
        }
    }
}

void Test_RealFunction::rotated360DegreesIsIdentical() {
    _function = new RealFunctionTestImplementation();

    _function->Transform(Rotation<4>(360., 360., 360., 360., 360., 360.), Vector<4>());

    for (unsigned i = 0; i < GRID_SIZE; ++i) {
        for (unsigned j = 0; j < GRID_SIZE; ++j) {
            for (unsigned k = 0; k < GRID_SIZE; ++k) {
                Vector<4> vertex = _function->vertices()[i][j][k],
                          transformed_vertex = _function->transformed_vertices()[i][j][k];
                QVERIFY((vertex - transformed_vertex).sqnorm() < EPSILON);
            }
        }
    }
}

void Test_RealFunction::project() {
    _function = new RealFunctionTestImplementation();

    _function->Transform(Rotation<4>(), Vector<4>());
    _function->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, false);

    QVERIFY(_function->projected_vertices().size() >= GRID_SIZE);
    QVERIFY(_function->projected_vertices()[0].size() >= GRID_SIZE);
    QVERIFY(_function->projected_vertices()[0][0].size() >= GRID_SIZE);

    // intercept theorem gives this factor (constant because f is constant)
    const double PROJECTION_FACTOR =
            (PROJECTION_CAMERA_W-PROJECTION_SCREEN_W) /
            (PROJECTION_CAMERA_W-CONSTANT_FUNCTION_VALUE);

    for (unsigned i = 0; i < GRID_SIZE; ++i) {
        for (unsigned j = 0; j < GRID_SIZE; ++j) {
            for (unsigned k = 0; k < GRID_SIZE; ++k) {
                Vector<4> vertex = _function->vertices()[i][j][k];
                Vector<3> projected_vertex = _function->projected_vertices()[i][j][k];
                for(unsigned m = 0; m < 3; ++m) {
                    QVERIFY(fabs(projected_vertex[m] - vertex[m]*PROJECTION_FACTOR) < EPSILON);
                }
            }
        }
    }
}

void Test_RealFunction::projectWithDepthCue() {
    _function = new RealFunctionTestImplementation();

    _function->Transform(Rotation<4>(), Vector<4>());
    _function->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, true);

    for (unsigned i = 0; i < GRID_SIZE; ++i) {
        for (unsigned j = 0; j < GRID_SIZE; ++j) {
            for (unsigned k = 0; k < GRID_SIZE; ++k) {
                Vector<4> vertex = _function->vertices()[i][j][k];
                Vector<3> projected_vertex = _function->projected_vertices()[i][j][k];
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
    _function = new RealFunctionTestImplementation();

    _function->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, false);

    _function->Draw();

    QSKIP("No idea how to correctly test drawing yet", SkipSingle);
}

void Test_RealFunction::torus1() {
  Torus1 f;
  f(0.,0.,0.);
}

void Test_RealFunction::torus2() {
  Torus2 f;
  f(0.,0.,0.);
}

void Test_RealFunction::fr3r() {
  Fr3r f;
  f(0.,0.,0.);
}

void Test_RealFunction::gravitationPotential() {
  GravitationPotential f;
  f(0.,0.,0.);
}

void Test_RealFunction::fr3rSin() {
  Fr3rSin f;
  f(0.,0.,0.);
}

void Test_RealFunction::fr3rExp() {
  Fr3rExp f;
  f(0.,0.,0.);
}

void Test_RealFunction::polar() {
  Polar f(-1, 1, .1, -1, 1, .1, -1, 1, .1);
  f(0.,0.,0.);
}

void Test_RealFunction::polarSin() {
  PolarSin f;
  f(0.,0.,0.);
}

void Test_RealFunction::polarSin2() {
  PolarSin2 f;
  f(0.,0.,0.);
}

void Test_RealFunction::polarR() {
  PolarR f;
  f(0.,0.,0.);
}
