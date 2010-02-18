
#include "BasicTest.h"
#include "RotopeTest.h"

#include <QtTest/QtTest>

using QTest::qExec;

int main(int argc, char **argv) {
    unsigned failedTestSuites = 0;

    if (qExec(new BasicTest)) failedTestSuites++;
    if (qExec(new RotopeTest)) failedTestSuites++;

    return failedTestSuites;
}
