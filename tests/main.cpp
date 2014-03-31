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

/// Otherwise, only run the latest test suites, as manually defined below
#define RUN_ALL_TESTS 0

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
#include "Test_ChangeDir.h"
#include "Test_ComplexFunction.h"
#include "Test_ColorManager.h"
#include "Test_Projector.h"

#include "Auxiliary/TestRunner.h"

#include <QtTest/QtTest>

std::map<std::string, QObject *> tests_by_name;

void fillTestsMap() {
    tests_by_name.insert(std::pair<std::string, QObject *>("Vector", new Test_Vector));
    tests_by_name.insert(std::pair<std::string, QObject *>("Matrix", new Test_Matrix));
    tests_by_name.insert(std::pair<std::string, QObject *>("Rotation", new Test_Rotation));
    tests_by_name.insert(std::pair<std::string, QObject *>("Realm", new Test_Realm));
    tests_by_name.insert(std::pair<std::string, QObject *>("Displayable", new Test_Displayable));
    tests_by_name.insert(std::pair<std::string, QObject *>("FunctionFactory", new Test_FunctionFactory));
    tests_by_name.insert(std::pair<std::string, QObject *>("FunctionValueGrid", new Test_FunctionValueGrid));
    tests_by_name.insert(std::pair<std::string, QObject *>("ParametricFunction", new Test_ParametricFunction));
    tests_by_name.insert(std::pair<std::string, QObject *>("Projection", new Test_Projection));
    tests_by_name.insert(std::pair<std::string, QObject *>("GridDrawer", new Test_GridDrawer));
    tests_by_name.insert(std::pair<std::string, QObject *>("MultiDimensionalVector", new Test_MultiDimensionalVector));
    tests_by_name.insert(std::pair<std::string, QObject *>("DisplayableClass", new Test_DisplayableClass));
    tests_by_name.insert(std::pair<std::string, QObject *>("Observer", new Test_Observer));
    tests_by_name.insert(std::pair<std::string, QObject *>("ArrayList", new Test_ArrayList));
    tests_by_name.insert(std::pair<std::string, QObject *>("RealFunction", new Test_RealFunction));
    tests_by_name.insert(std::pair<std::string, QObject *>("Surface", new Test_Surface));
    tests_by_name.insert(std::pair<std::string, QObject *>("Rotope", new Test_Rotope));
    tests_by_name.insert(std::pair<std::string, QObject *>("Composite", new Test_Composite));
    tests_by_name.insert(std::pair<std::string, QObject *>("FunctionHolder", new Test_FunctionHolder));
    tests_by_name.insert(std::pair<std::string, QObject *>("Transformation", new Test_Transformation));
    tests_by_name.insert(std::pair<std::string, QObject *>("PartitionedMultithreadedMap", new Test_PartitionedMultithreadedMap));
    tests_by_name.insert(std::pair<std::string, QObject *>("Object", new Test_Object));
    tests_by_name.insert(std::pair<std::string, QObject *>("Util", new Test_Util));
    tests_by_name.insert(std::pair<std::string, QObject *>("FacePolygon", new Test_FacePolygon));
    tests_by_name.insert(std::pair<std::string, QObject *>("ChangeDir", new Test_ChangeDir));
    tests_by_name.insert(std::pair<std::string, QObject *>("ComplexFunction", new Test_ComplexFunction));
    tests_by_name.insert(std::pair<std::string, QObject *>("ColorManager", new Test_ColorManager));
    tests_by_name.insert(std::pair<std::string, QObject *>("Projector", new Test_Projector));
}

int main(int argc, char **argv) {
    // A QApplication must be instantiated for GUI tests to work. This causes a compiler warning.
    QApplication *app = new QApplication(argc, argv);
    
    std::vector<std::string> tests_to_run;
    for (int i = 1; i < argc; i++) {
        tests_to_run.push_back(std::string(argv[i]));
    }

    fillTestsMap();
    
    TestRunner runner;
    
    if (tests_to_run.empty()) {
#     if RUN_ALL_TESTS
        for (auto test: tests_by_name) {
            runner.run(test.second);
        }
#     else
        runner.run(new Test_Projector);
#     endif
    } else {
        for (auto test: tests_to_run) {
            if (tests_by_name.find(test) != tests_by_name.end()) {
                runner.run(tests_by_name[test]);
            }
        }
    }
    runner.printSummary();

    return runner.exitValue();
}
