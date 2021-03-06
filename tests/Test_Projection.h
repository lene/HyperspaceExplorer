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

#ifndef TEST_PROJECTION_H
#define TEST_PROJECTION_H

#include <QtTest/QtTest>

#include "Projection.h"

class Test_Projection: public QObject {

  Q_OBJECT

  static constexpr double EPSILON = 1.e-8;

  private slots:

    void initTestCase();
    void cleanupTestCase();

    void project1D();
    void project1D_data();

    void project5to3();
    void project5to3_data();

    void project2D();
    void project2D_data();

    void projectWithViewpoints();

    /// Test whether projection works with data type float instead of double.
    void projectFloats();
    void projectFloats_data();

    /// Test whether projection works with data type complex<double> too.
    void projectComplex();
    void projectComplex_data();

};

#endif // TEST_PROJECTION_H
