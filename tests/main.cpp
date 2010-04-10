
#include "Test_Rotope.h"
#include "Test_Function.h"
#include "Test_RealFunction.h"
#include "Test_Surface.h"
#include "Test_Vector.h"
#include "Test_Matrix.h"
#include "Test_NestedVector.h"
#include "Test_Rotation.h"
#include "Test_Realm.h"
#include "Test_ParametricFunction.h"
#include "Test_FunctionValueGrid.h"
#include "Test_Transformation.h"
#include "Test_Projection.h"

#include <QtTest/QtTest>

using QTest::qExec;


void printSummary(int failedTestSuites) {
    if (failedTestSuites) qDebug() << QString(80, '*');
    qDebug() << failedTestSuites << " Test suites failed.";
    if (failedTestSuites) qDebug() << QString(80, '*');
}

int main(int argc, char **argv) {
    // A QApplication must be instantiated for GUI tests to work. This causes a compiler warning.
    QApplication *app = new QApplication(argc, argv);

    unsigned failedTestSuites = 0;

    if (qExec(new Test_Vector)) failedTestSuites++;
    if (qExec(new Test_Matrix)) failedTestSuites++;
    if (qExec(new Test_NestedVector)) failedTestSuites++;
    if (qExec(new Test_Rotation)) failedTestSuites++;
    if (qExec(new Test_Realm)) failedTestSuites++;
    if (qExec(new Test_Rotope)) failedTestSuites++;
    if (qExec(new Test_Function)) failedTestSuites++;
    if (qExec(new Test_RealFunction)) failedTestSuites++;
    if (qExec(new Test_Surface)) failedTestSuites++;
    if (qExec(new Test_FunctionValueGrid)) failedTestSuites++;
    if (qExec(new Test_ParametricFunction)) failedTestSuites++;
    if (qExec(new Test_Transformation)) failedTestSuites++;
    if (qExec(new Test_Projection)) failedTestSuites++;
                
    printSummary(failedTestSuites);

    return failedTestSuites;
}
