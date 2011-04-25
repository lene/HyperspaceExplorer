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

#include "Test_GridDrawer.h"

#include "GridDrawer.impl.h"
#include "Vector.impl.h"
#include "MultiDimensionalVector.impl.h"

#include <complex>

using VecMath::Vector;
using VecMath::MultiDimensionalVector;

typedef MultiDimensionalVector< Vector<4>, 2 > original2D;
typedef MultiDimensionalVector< Vector<3>, 2 > projected2D;

void Test_GridDrawer::initTestCase() { }

void Test_GridDrawer::init() {
    view_ = new MockView;
}

void Test_GridDrawer::cleanupTestCase() { }

void Test_GridDrawer::createGridDrawer() {
  original2D dummy_vertices;
  projected2D dummy_projections;
  GridDrawer<2> drawer(dummy_vertices, dummy_projections, view_);
}
