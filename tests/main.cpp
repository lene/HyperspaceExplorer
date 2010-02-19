
#include "RotopeTest.h"

#include <QtTest/QtTest>

using QTest::qExec;


void printSummary(int failedTestSuites) {
    qDebug() << failedTestSuites << " Test suites failed.";
}

int main(int argc, char **argv) {
    unsigned failedTestSuites = 0;

    if (qExec(new RotopeTest)) failedTestSuites++;

    printSummary(failedTestSuites);

    return failedTestSuites;
}
