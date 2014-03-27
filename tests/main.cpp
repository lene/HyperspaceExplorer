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

/// Otherwise, only run the latest test suites
#define RUN_ALL_TESTS 1

#include "Test_Rotope.h"
#include "Test_Displayable.h"
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
#include "Test_DisplayableClass.h"
#include "Test_Observer.h"
#include "Test_Object.h"
#include "Test_ArrayList.h"
#include "Test_Composite.h"
#include "Test_Util.h"
#include "Test_PartitionedMultithreadedMap.h"
#include "Test_FacePolygon.h"

#include "Auxiliary/TestRunner.h"

#include <QtTest/QtTest>


int main(int argc, char **argv) {
    // A QApplication must be instantiated for GUI tests to work. This causes a compiler warning.
    QApplication *app = new QApplication(argc, argv);

    TestRunner runner;
#if RUN_ALL_TESTS
    runner.run(new Test_Vector);
    runner.run(new Test_Matrix);
    runner.run(new Test_Rotation);
    runner.run(new Test_Realm);
    runner.run(new Test_Displayable);
    runner.run(new Test_FunctionFactory);
    runner.run(new Test_FunctionValueGrid);
    runner.run(new Test_ParametricFunction);
    runner.run(new Test_Projection);
    runner.run(new Test_GridDrawer);
    runner.run(new Test_MultiDimensionalVector);
    runner.run(new Test_DisplayableClass);
    runner.run(new Test_Observer);
    runner.run(new Test_ArrayList);
    runner.run(new Test_RealFunction);
    runner.run(new Test_Surface);
#endif
    runner.run(new Test_Rotope);
    runner.run(new Test_Composite);
    runner.run(new Test_FunctionHolder);
    runner.run(new Test_Transformation);
    runner.run(new Test_PartitionedMultithreadedMap);
    runner.run(new Test_Object);
    runner.run(new Test_Util);
    runner.run(new Test_FacePolygon);

    runner.printSummary();

    return runner.exitValue();
}
