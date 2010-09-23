
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
#include "Test_GridDrawer.h"
#include "Test_FunctionFactory.h"

#include <QtTest/QtTest>

using QTest::qExec;

class TestRunner {

  public:

    TestRunner(): executedTestSuites_(0), failedTestSuites_(0), startTime_(clock()) { }

    void run(QObject *test) {
      if (qExec(test)) failedTestSuites_++;
      executedTestSuites_++;
    }

    void printSummary() const {
      double timeElapsed = double(clock()-startTime_)/CLOCKS_PER_SEC;
      if (failedTestSuites_) qDebug() << QString(80, '*');
      qDebug() << "Tests finished in " << timeElapsed << " seconds.";
      qDebug() << failedTestSuites_ << " Test suites out of " << executedTestSuites_ << " failed.";
      if (failedTestSuites_) qDebug() << QString(80, '*');
    }

    unsigned exitValue() const { return failedTestSuites_; }

  private:
    unsigned executedTestSuites_;
    unsigned failedTestSuites_;

    clock_t startTime_;
};


int main(int argc, char **argv) {
    // A QApplication must be instantiated for GUI tests to work. This causes a compiler warning.
    QApplication *app = new QApplication(argc, argv);

    TestRunner runner;

    runner.run(new Test_Vector);
    runner.run(new Test_Matrix);
    runner.run(new Test_NestedVector);
    runner.run(new Test_Rotation);
    runner.run(new Test_Realm);
    runner.run(new Test_Rotope);
    runner.run(new Test_Function);
    runner.run(new Test_RealFunction);
    runner.run(new Test_Surface);
    runner.run(new Test_FunctionValueGrid);
    runner.run(new Test_ParametricFunction);
    runner.run(new Test_Transformation);
    runner.run(new Test_Projection);
    runner.run(new Test_GridDrawer);
    runner.run(new Test_FunctionFactory);

    runner.printSummary();

    return runner.exitValue();
}
