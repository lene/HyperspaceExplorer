#ifndef REALFUNCTIONTEST_H_
#define REALFUNCTIONTEST_H_

#include <QtTest/QtTest>

#include "RealFunction.h"

/// Unit tests for class RealFunction and its implementations
class Test_RealFunction: public QObject {

    Q_OBJECT

    static const double X_MIN = -1.;
    static const double X_MAX =  1.;
    static const unsigned GRID_SIZE = 5;

    const static QString TEST_FUNCTION_NAME;
    static const double CONSTANT_FUNCTION_VALUE = 1.;

    static const double EPSILON = 1e-8;

    static const double PROJECTION_SCREEN_W = 2.;
    static const double PROJECTION_CAMERA_W = 4.;

    class RealFunctionTestImplementation: public RealFunction {

    public:
        RealFunctionTestImplementation();

        VecMath::Vector<4> function_value(double tt, double uu, double vv) { return f(tt,uu,vv); }
        VecMath::NestedVector<VecMath::Vector<4>, 3> vertices() { return X(); }
        VecMath::NestedVector<VecMath::Vector<4>, 3> transformed_vertices() { return Xtrans(); }
        vec3vec3D projected_vertices() { return _Xscr; }

        unsigned xsteps() const { return getTsteps(); }
        unsigned ysteps() const { return getUsteps(); }
        unsigned zsteps() const { return getVsteps(); }

    protected:
        class DefiningFunction: public ParametricFunction<4, 3> {
          
          public:
            
            virtual return_type f(const argument_type &x);
        };    

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
        
        void torus1();
        void torus2();
        void fr3r();
        void gravitationPotential();
        void fr3rSin();
        void fr3rExp();
        void polar();
        void polarSin();
        void polarSin2();
        void polarR();
        
    private:
        RealFunctionTestImplementation *_function;
};


#endif /* REALFUNCTIONTEST_H_ */
