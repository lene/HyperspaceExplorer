/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include "Test_Rotope.h"
#include "Test_Function.h"
#include "Test_RealFunction.h"
#include "Test_Surface.h"
#include "Test_Vector.h"
#include "Test_Matrix.h"
#include "Test_MultiDimensionalVector.h"
#include "Test_Rotation.h"
#include "Test_Realm.h"
#include "Test_ParametricFunction.h"
#include "Test_FunctionValueGrid.h"
#include "Test_Transformation.h"
#include "Test_Projection.h"
#include "Test_GridDrawer.h"
#include "Test_FunctionFactory.h"
#include "Test_FunctionHolder.h"

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
    runner.run(new Test_Rotation);
    runner.run(new Test_Realm);
    runner.run(new Test_Rotope);
    runner.run(new Test_Function);
    runner.run(new Test_FunctionFactory);
    runner.run(new Test_FunctionValueGrid);
    runner.run(new Test_ParametricFunction);
    runner.run(new Test_Transformation);
    runner.run(new Test_Projection);
    runner.run(new Test_GridDrawer);
    runner.run(new Test_MultiDimensionalVector);
    runner.run(new Test_RealFunction);
    runner.run(new Test_Surface);
    runner.run(new Test_FunctionHolder);

    runner.printSummary();

    return runner.exitValue();
}
