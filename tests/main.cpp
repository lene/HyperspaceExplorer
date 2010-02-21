
#include "RotopeTest.h"
#include "FunctionTest.h"
#include "RealFunctionTest.h"
#include "VectorTest.h"
#include "MatrixTest.h"
#include "NestedVectorTest.h"
#include "RotationTest.h"
#include "RealmTest.h"

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

    if (qExec(new VectorTest)) failedTestSuites++;
    if (qExec(new MatrixTest)) failedTestSuites++;
    if (qExec(new NestedVectorTest)) failedTestSuites++;
    if (qExec(new RotationTest)) failedTestSuites++;
    if (qExec(new RotopeTest)) failedTestSuites++;
    if (qExec(new RealmTest)) failedTestSuites++;
//    if (qExec(new FunctionTest)) failedTestSuites++;
    if (qExec(new RealFunctionTest)) failedTestSuites++;
        
    printSummary(failedTestSuites);

    return failedTestSuites;
}
