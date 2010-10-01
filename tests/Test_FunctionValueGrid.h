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

#ifndef TEST_FUNCTIONVALUEGRID_H_
#define TEST_FUNCTIONVALUEGRID_H_

#include "FunctionValueGrid.h"

#include <QtTest/QtTest>

#include <tr1/memory>

/// Unit tests for class FunctionValueGrid
class Test_FunctionValueGrid: public QObject {

  Q_OBJECT

private slots:

  void initTestCase();

  void initializeGrid();
  void functionValues();
  void changeGridSize();
  void inhomogenousGridSize();
  void nonconstantFunctionAndBoundaries();

  void floatValues();
  void complexValues();

private:

  void resetGridSize();

  std::tr1::shared_ptr< FunctionValueGrid<4, 3> > _grid;

  const static double DEFAULT_X_MIN = -1.;
  const static double DEFAULT_X_MAX =  1.;
  const static unsigned DEFAULT_GRID_SIZE = 10;

  const static VecMath::Vector<3> DEFAULT_XMIN;
  const static VecMath::Vector<3> DEFAULT_XMAX;
  const static VecMath::Vector<3, unsigned> DEFAULT_GRID;
};


#endif /* MATRIXTEST_H_ */
