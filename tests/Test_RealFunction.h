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

      void testFunction(RealFunction &f);
      void testDrawDrawsAllVertices(RealFunction &f);
      void testNonzeroRotationRuns(RealFunction &f);
      void testAllVerticesDrawn(RealFunction* f);

      RealFunctionTestImplementation *function_;
      MockView *view_;
};

static const double CONSTANT_FUNCTION_VALUE = 1.;

static const double PROJECTION_SCREEN_W = 2.;
static const double PROJECTION_CAMERA_W = 4.;

static const double EPSILON = 1e-8;

void testGetParametersRuns(RealFunction &f);
void testFunctionEvaluationRuns(RealFunction &f);
void testReinitRuns(RealFunction &f);

#endif /* REALFUNCTIONTEST_H_ */
