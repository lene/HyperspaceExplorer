
#include "RealFunctionTest.h"

#include "RealFunction.h"
#include "ColorManager.h"

using VecMath::Vector;
using VecMath::Rotation;
using std::cerr;
using std::endl;

Vector<4> &RealFunctionTest::RealFunctionTestImplementation::f (double tt, double uu, double vv) {
    F[0] = tt;
    F[1] = uu;
    F[2] = vv;
    F[3] = 1;

    return F;
}

void RealFunctionTest::initTestCase() {
    ColMgrMgr::Instance().setColorManager("XYZ to RGB");
}

void RealFunctionTest::cleanupTestCase() { }

void RealFunctionTest::realFunction() {
    RealFunctionTestImplementation function;
    QVERIFY(function.getDefinitionSpaceDimensions() == 3);
    QVERIFY( (function.function_value(0,0,0) - Vector<4>(0.,0.,0.,1.)).sqnorm() <= 1e-8 );

    QVERIFY(function.vertices().size() >= 5);
    QVERIFY(function.vertices()[0].size() >= 5);
    QVERIFY(function.vertices()[0][0].size() >= 5);

    function.Transform(Rotation<4>(1., 1., 1., 1., 1., 1.), Vector<4>());

    QVERIFY(function.transformed_vertices().size() >= 5);
    QVERIFY(function.transformed_vertices()[0].size() >= 5);
    QVERIFY(function.transformed_vertices()[0][0].size() >= 5);

    for (unsigned i = 0; i < function.vertices().size()-2; ++i) {
        for (unsigned j = 0; j < function.vertices()[i].size()-2; ++j) {
            for (unsigned k = 0; k < function.vertices()[i][j].size()-2; ++k) {
                Vector<4> vertex = function.vertices()[i][j][k],
                          transformed_vertex = function.transformed_vertices()[i][j][k];
                QVERIFY((vertex - transformed_vertex).sqnorm() > 1e-8);
            }
        }
    }

    function.Project(4, 8, false);

    QVERIFY(function.projected_vertices().size() >= 5);
    QVERIFY(function.projected_vertices()[0].size() >= 5);
    QVERIFY(function.projected_vertices()[0][0].size() >= 5);

    for (unsigned i = 0; i < function.projected_vertices().size()-2; ++i) {
        for (unsigned j = 0; j < function.projected_vertices()[i].size()-2; ++j) {
            for (unsigned k = 0; k < function.projected_vertices()[i][j].size()-2; ++k) {
                Vector<3> projected_vertex = function.projected_vertices()[i][j][k];
                cerr << projected_vertex << " ";
            }
            cerr << endl;
        }
    }

    function.Draw();

    qDebug() << function.getNumParameters()
            << function.getFunctionName();
}
