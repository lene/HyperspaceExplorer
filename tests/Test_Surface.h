#ifndef TEST_SURFACE_H_
#define TEST_SURFACE_H_

#include <QtTest/QtTest>

#include "Surface.h"

/// Unit tests for class Surface and its implementations
class Test_Surface: public QObject {

    Q_OBJECT

    static const double X_MIN = -1.;
    static const double X_MAX =  1.;
    static const unsigned GRID_SIZE = 5;

    const static QString TEST_FUNCTION_NAME;
    static const double CONSTANT_FUNCTION_VALUE = 1.;

    static const double EPSILON = 1e-8;

    static const double PROJECTION_SCREEN_W = 2.;
    static const double PROJECTION_CAMERA_W = 4.;

    class SurfaceTestImplementation: public Surface {

    public:
      SurfaceTestImplementation();

      VecMath::Vector<4> function_value(double tt, double uu) { return _function->f(VecMath::Vector<2>(tt,uu)); }
      VecMath::NestedVector< VecMath::Vector<4>, 2 > vertices() { return X(); }
      VecMath::NestedVector< VecMath::Vector<4>, 2 > transformed_vertices() { return Xtrans(); }
      vec3vec2D projected_vertices() { return _Xscr; }

      unsigned xsteps() const { return getTsteps(); }
      unsigned ysteps() const { return getUsteps(); }

    private:
        
      struct DefiningFunction: public ParametricFunction<4, 2> {
        virtual return_type f(const argument_type &x);
      };
      
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

        void surface1();
        void horizon();
        void torus3();
        void t_z2();
        void t_z3();
        void t_zA();
        void t_ez();
        void t_emz2();
        void t_zm1();
        void t_zm2();
        void t_sqrtz();
        void t_lnz();
        void t_sinz();
        void t_cosz();
        void t_sinhz();
        void t_coshz();
        void t_tanz();
        
    private:
        SurfaceTestImplementation *_function;
};


#endif
