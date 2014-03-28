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

#ifndef TEST_SURFACE_H_
#define TEST_SURFACE_H_

#include <QtTest/QtTest>

#include "Surface/Surface.h"

#include "DefinitionRangeOfDimension.h"

#include "FunctionHolder.impl.h"

class MockView;

/// Unit tests for class Surface and its implementations
class Test_Surface: public QObject {

    Q_OBJECT

    static constexpr double X_MIN = -1.;
    static constexpr double X_MAX =  1.;
    static constexpr unsigned GRID_SIZE = 5;

    const static std::string TEST_FUNCTION_NAME;
    static constexpr double CONSTANT_FUNCTION_VALUE = 1.;

    static constexpr double EPSILON = 1e-8;

    static constexpr double PROJECTION_SCREEN_W = 2.;
    static constexpr double PROJECTION_CAMERA_W = 4.;

    class SurfaceTestImplementation;

    private slots:

        void initTestCase();
        void init();

        void functionValue();
        void meetsFormalRequirements();
        void boundsAndSteps();

        void getNumParameters();

        void rotateAboutAllAxes();
        void rotated360DegreesIsIdentical();

        void project();
        void projectWithDepthCue();

        void draw();

        void surface1();
        void horizon();
        void torus3();

protected:
      template <class SurfaceType, unsigned num_parameters>
      void performSurfaceTest(const std::string &fname);

private:

      void testFunction(Surface &f);
      void testDynamicallyCreatedFunction(const std::string &fname);

      SurfaceTestImplementation *function_;
      MockView *view_;
};

#include "GlobalFunctions.h"

template <class SurfaceType, unsigned num_parameters>
void Test_Surface::performSurfaceTest(const std::string &fname) {
  SurfaceType f(-1., 1., 0.5, -1., 1., 0.5);
  UnitTests::testEqual(f.getNumParameters(), num_parameters);
  testFunction(f);
  testDynamicallyCreatedFunction(fname);
}

#endif
