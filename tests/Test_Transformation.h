/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
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

#ifndef TEST_TRANSFORMATION_H
#define TEST_TRANSFORMATION_H

#include "TransformationFactory.h"

#include <QtTest/QtTest>

#include <memory>

class Test_Transformation: public QObject {

  Q_OBJECT

  private slots:

    void initTestCase();
    void cleanupTestCase();

    void transformPerformed();
    void multithreadedTransformPerformed();
    void multithreadedTransformFaster();
    void factorySetsSingleAndMultithreaded();
    void rotationPreservesNorm_data();
    void rotationPreservesNorm();
    void rotate90DegreesIsOrthogonal_data();
    void rotate90DegreesIsOrthogonal();
    void rotate180DegreesIsNegative_data();
    void rotate180DegreesIsNegative();
    void rotate360DegreesIsEqual_data();
    void rotate360DegreesIsEqual();
    void translationAddsVector_data();
    void translationAddsVector();
    void scaleScales_data();
    void scaleScales();

    void rotateFloatVector();

    void rotateFloats_data();
    void rotateFloats();

  private:

    static constexpr unsigned min_size_for_multithreaded_advantage = 1024;
    
    int timeTransform(const Transformation< 4, 3, double > *transform);
    int timeTransformationMethod(TransformationFactory::Method method);
    
    std::shared_ptr< FunctionValueGrid<4, 3> > _grid;

};

#endif // TEST_TRANSFORMATION_H
