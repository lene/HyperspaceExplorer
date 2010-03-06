#ifndef TEST_SURFACE_H_
#define TEST_SURFACE_H_

#include <QtTest/QtTest>

#include "Surface.h"

class Test_Surface: public QObject {

    Q_OBJECT

    static const double X_MIN = -1.;
    static const double X_MAX =  1.;
    static const unsigned GRID_SIZE = 20;

    const static QString TEST_FUNCTION_NAME;
    static const double CONSTANT_FUNCTION_VALUE = 1.;

    static const double EPSILON = 1e-8;

    static const double PROJECTION_SCREEN_W = 2.;
    static const double PROJECTION_CAMERA_W = 4.;

    class SurfaceTestImplementation: public Surface {

    public:
      SurfaceTestImplementation();

      VecMath::Vector<4> function_value(double tt, double uu, double) { return f(tt,uu); }
      vec4vec2D vertices() { return _X; }
      vec4vec2D transformed_vertices() { return _Xtrans; }
      vec3vec2D projected_vertices() { return _Xscr; }

      unsigned xsteps() const { return getTsteps(); }
      unsigned ysteps() const { return getUsteps(); }

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

    private:
        SurfaceTestImplementation *_function;
};


#endif
