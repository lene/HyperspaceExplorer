
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

void RealFunctionTest::functionValue() {
    _function = new RealFunctionTestImplementation();
    QVERIFY( (_function->function_value(0,0,0) - Vector<4>(0.,0.,0.,1.)).sqnorm() <= 1e-8 );
}

void RealFunctionTest::meetsFormalRequirements() {
    _function = new RealFunctionTestImplementation();

    QVERIFY(_function->getDefinitionSpaceDimensions() == 3);
    QVERIFY(_function->vertices().size() >= 5);
    QVERIFY(_function->vertices()[0].size() >= 5);
    QVERIFY(_function->vertices()[0][0].size() >= 5);

    qDebug() << _function->getNumParameters()
            << _function->getFunctionName();
}

void RealFunctionTest::rotateAboutAllAxes() {
    _function = new RealFunctionTestImplementation();

    _function->Transform(Rotation<4>(90., 0., 0., 0., 0., 90.), Vector<4>());

    QVERIFY(_function->transformed_vertices().size() >= 5);
    QVERIFY(_function->transformed_vertices()[0].size() >= 5);
    QVERIFY(_function->transformed_vertices()[0][0].size() >= 5);

    for (unsigned i = 0; i < _function->vertices().size()-2; ++i) {
        for (unsigned j = 0; j < _function->vertices()[i].size()-2; ++j) {
            for (unsigned k = 0; k < _function->vertices()[i][j].size()-2; ++k) {
                Vector<4> vertex = _function->vertices()[i][j][k],
                          transformed_vertex = _function->transformed_vertices()[i][j][k];
                QVERIFY((vertex - transformed_vertex).sqnorm() > 1e-8);
            }
        }
    }
}

void RealFunctionTest::rotated360DegreesIsIdentical() {
    _function = new RealFunctionTestImplementation();

    _function->Transform(Rotation<4>(360., 360., 360., 360., 360., 360.), Vector<4>());

    for (unsigned i = 0; i < _function->vertices().size()-2; ++i) {
        for (unsigned j = 0; j < _function->vertices()[i].size()-2; ++j) {
            for (unsigned k = 0; k < _function->vertices()[i][j].size()-2; ++k) {
                Vector<4> vertex = _function->vertices()[i][j][k],
                          transformed_vertex = _function->transformed_vertices()[i][j][k];
                QVERIFY((vertex - transformed_vertex).sqnorm() < 1e-8);
            }
        }
    }
}

void RealFunctionTest::project() {
    _function = new RealFunctionTestImplementation();

    _function->Project(2, 4, false);

    QVERIFY(_function->projected_vertices().size() >= 5);
    QVERIFY(_function->projected_vertices()[0].size() >= 5);
    QVERIFY(_function->projected_vertices()[0][0].size() >= 5);

    for (unsigned i = 0; i < _function->projected_vertices().size()-2; ++i) {
        for (unsigned j = 0; j < _function->projected_vertices()[i].size()-2; ++j) {
            for (unsigned k = 0; k < _function->projected_vertices()[i][j].size()-2; ++k) {
                Vector<3> projected_vertex = _function->projected_vertices()[i][j][k];
//                cerr << projected_vertex << " ";
            }
//            cerr << endl;
        }
    }
    QSKIP("No idea how to correctly test projection yet", SkipSingle);
}

void RealFunctionTest::draw() {
    _function = new RealFunctionTestImplementation();

    _function->Project(4, 8, false);

    _function->Draw();

    QSKIP("No idea how to correctly test drawing yet", SkipSingle);

}
