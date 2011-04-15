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

#ifndef REALFUNCTIONTEST_H_
#define REALFUNCTIONTEST_H_

#include <QtTest/QtTest>

#include "RealFunction.h"

class MockView;

/// Unit tests for class RealFunction and its implementations
class Test_RealFunction: public QObject {

    Q_OBJECT

    static const double X_MIN = -1.;
    static const double X_MAX =  1.;
    static const unsigned GRID_SIZE = 5;
    static const unsigned NUM_PARAMETERS = 3;

    const static QString TEST_FUNCTION_NAME;

    class RealFunctionTestImplementation;

    private slots:

      void initTestCase();
      void init();

        void functionValue();
        void getDefinitionSpaceDimensions();
        void getNumParameters();
        void meetsFormalRequirements();
        void boundsAndSteps();
        void ReInit();

        void rotateAboutAllAxes();
        void rotated360DegreesIsIdentical();

        void project();
        void projectWithDepthCue();

        void draw();

        void torus1();
        void torus2();
        void fr3r();
        void gravitationPotential();
        void fr3rSin();
        void fr3rExp();
        void polarSin();
        void polarSin2();
        void polarR();

    private:

      template <class FunctionType, unsigned num_parameters>
      void performFunctionTest(const std::string &fname);

      void testFunction(RealFunction &f);
      void testDynamicallyCreatedFunction(const std::string &fname);

      void testDrawDrawsAllVertices(RealFunction &f);
      void testNonzeroRotationRuns(RealFunction &f);
      void testAllVerticesDrawn(RealFunction* f);

      RealFunctionTestImplementation *function_;
      MockView *view_;
};

static const double CONSTANT_FUNCTION_VALUE = 1.;

static const double PROJECTION_SCREEN_W = 2.;
static const double PROJECTION_CAMERA_W = 4.;

void testGetParametersRuns(RealFunction &f);
void testFunctionEvaluationRuns(RealFunction &f);
void testReinitRuns(RealFunction &f);

#endif /* REALFUNCTIONTEST_H_ */
