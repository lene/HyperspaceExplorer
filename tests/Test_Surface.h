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

#include "Surface.h"

class MockView;

/// Unit tests for class Surface and its implementations
class Test_Surface: public QObject {

    Q_OBJECT

    static const double X_MIN = -1.;
    static const double X_MAX =  1.;
    static const unsigned GRID_SIZE = 5;

    const static std::string TEST_FUNCTION_NAME;
    static const double CONSTANT_FUNCTION_VALUE = 1.;

    static const double EPSILON = 1e-8;

    static const double PROJECTION_SCREEN_W = 2.;
    static const double PROJECTION_CAMERA_W = 4.;

    class SurfaceTestImplementation: public Surface {

    public:
      SurfaceTestImplementation();
      virtual std::string getFunctionName() const { return TEST_FUNCTION_NAME; }

      VecMath::Vector<4> function_value(double tt, double uu) { return _function->f(VecMath::Vector<2>(tt,uu)); }
      VecMath::MultiDimensionalVector< VecMath::Vector<4>, 2 > vertices() { return X(); }
      VecMath::MultiDimensionalVector< VecMath::Vector<4>, 2 > transformed_vertices() { return Xtrans(); }
      VecMath::MultiDimensionalVector< VecMath::Vector<3>, 2 > projected_vertices() { return Xscr(); }

      unsigned xsteps() const { return getTsteps(); }
      unsigned ysteps() const { return getUsteps(); }

    private:

      struct DefiningFunction: public ParametricFunction<4, 2> {
        virtual return_type f(const argument_type &x);
      };

    };

    private slots:

        void initTestCase();
        void init();

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

      void testFunction(Surface &f);
      void testDynamicallyCreatedFunction(const std::string &fname);

      SurfaceTestImplementation *_function;
      MockView *view_;
};


#endif
