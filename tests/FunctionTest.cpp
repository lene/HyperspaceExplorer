/*
 * FunctionTest.cpp
 *
 *  Created on: Feb 19, 2010
 *      Author: helge
 */

#include "FunctionTest.h"

#include "RealFunction.h"
#include "Surface.h"
#include "ComplexFunction.h"
#include "Sponge.h"
#include "ColorManager.h"

#include <cstdlib>

using VecMath::Vector;
using VecMath::Rotation;
using std::cerr;
using std::endl;

FunctionTest::~FunctionTest() { }

void FunctionTest::initTestCase() {
    ColMgrMgr::Instance().setColorManager("XYZ to RGB");
}

void FunctionTest::cleanupTestCase() {

}

class RealFunctionTestImplementation: public RealFunction {

    friend class FunctionTest;

public:
    RealFunctionTestImplementation():
        RealFunction("RealFunctionTestImplementation", -1, 1, 0.5, -1, 1, 0.5, -1, 1, 0.5) {
        Initialize();
    }

    Vector<4> function_value(double tt, double uu, double vv) { return f(tt,uu,vv); }
    vec4vec3D vertices() { return X; }
    vec4vec3D transformed_vertices() { return Xtrans; }
    vec3vec3D projected_vertices() { return Xscr; }

protected:
    virtual function_type f;
};

Vector<4> &RealFunctionTestImplementation::f (double tt, double uu, double vv) {
    F[0] = tt;
    F[1] = uu;
    F[2] = vv;
    F[3] = 1;

    return F;
}

void FunctionTest::realFunction() {
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

void FunctionTest::surfaceFunction() {
    _function = new Horizon();
    QVERIFY(_function->getDefinitionSpaceDimensions() == 2);
    qDebug() << _function->getNumParameters()
            << _function->getFunctionName();
}

void FunctionTest::complexFunction() {
    _function = new z3();
    QVERIFY(_function->getDefinitionSpaceDimensions() == 2);
    qDebug() << _function->getNumParameters()
            << _function->getFunctionName();
}

void FunctionTest::objectFunction() {
//    _function = new Hypercube();
}

