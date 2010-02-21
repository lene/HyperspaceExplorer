#ifndef REALFUNCTIONTEST_H_
#define REALFUNCTIONTEST_H_

#include <QtTest/QtTest>


#include "RealFunction.h"

class RealFunctionTest: public QObject {

    Q_OBJECT

    class RealFunctionTestImplementation: public RealFunction {

    public:
        RealFunctionTestImplementation():
            RealFunction("RealFunctionTestImplementation", -1, 1, 0.5, -1, 1, 0.5, -1, 1, 0.5) {
            Initialize();
        }

        VecMath::Vector<4> function_value(double tt, double uu, double vv) { return f(tt,uu,vv); }
        vec4vec3D vertices() { return X; }
        vec4vec3D transformed_vertices() { return Xtrans; }
        vec3vec3D projected_vertices() { return Xscr; }

    protected:
        virtual function_type f;
    };

    private slots:
        void initTestCase();
        void cleanupTestCase();

        void functionValue();
        void meetsFormalRequirements();
        void rotateAboutAllAxes();
        void rotated360DegreesIsIdentical();
        void project();

        void draw();

    private:
        RealFunctionTestImplementation *_function;
};


#endif /* REALFUNCTIONTEST_H_ */
