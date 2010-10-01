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

#ifndef MATRIXTEST_H_
#define MATRIXTEST_H_

#include <QtTest/QtTest>

/// Unit tests for class VecMath::Matrix
class Test_Matrix: public QObject {

  Q_OBJECT

  static const double EPSILON = 1e-8;

private slots:
  void defaultConstructor();
  void rotationAboutAxisConstructor();
  void matrixMultiplication();
  void vectorMultiplication();
  void toString();

};


#endif /* MATRIXTEST_H_ */
