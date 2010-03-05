#ifndef REALFUNCTIONTEST_H_
#define REALFUNCTIONTEST_H_

#include <QtTest/QtTest>

#include "RealFunction.h"

class Test_RealFunction: public QObject {

    Q_OBJECT

    static const double X_MIN = -1.;
    static const double X_MAX =  1.;
    static const unsigned GRID_SIZE = 5;

    static const double CONSTANT_FUNCTION_VALUE = 1.;

    static const double EPSILON = 1e-8;

    static const double PROJECTION_SCREEN_W = 2.;
    static const double PROJECTION_CAMERA_W = 4.;

    class RealFunctionTestImplementation: public RealFunction {

    public:
        RealFunctionTestImplementation():
            RealFunction(
                    "RealFunctionTestImplementation",
                    X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1),
                    X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1),
                    X_MIN, X_MAX, (X_MAX-X_MIN)/(GRID_SIZE-1)) {
            Initialize();
        }

        VecMath::Vector<4> function_value(double tt, double uu, double vv) { return f(tt,uu,vv); }
        vec4vec3D vertices() { return _X; }
        vec4vec3D transformed_vertices() { return _Xtrans; }
        vec3vec3D projected_vertices() { return _Xscr; }

        unsigned xsteps() const { return getTsteps(); }
        unsigned ysteps() const { return getUsteps(); }
        unsigned zsteps() const { return getVsteps(); }

    protected:
        virtual function_type f;
    };

    private slots:
        void initTestCase();
        void cleanupTestCase();

        void functionValue();
        void meetsFormalRequirements();
        void boundsAndSteps();

        void rotateAboutAllAxes();
        void rotated360DegreesIsIdentical();

        void project();
        void projectWithDepthCue();

        void draw();

        void functionWithParameters();

    private:
        RealFunctionTestImplementation *_function;
};


#endif /* REALFUNCTIONTEST_H_ */
