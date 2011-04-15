/*
 * Hyperspace Explorer - visualizing higher-dimensional geometry
 * Copyright (C) 2011  Lene Preuss <lene.preuss@gmail.com>
 *
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

#include "Test_Composite.h"
#include "GlobalFunctions.h"

#include <SimpleComposite.h>
#include "ColorManager.h"

using namespace UnitTests;

using VecMath::Rotation;
using VecMath::Vector;

void Test_Composite::initTestCase() {
  ColMgrMgr::Instance().setColorManager("XYZ to RGB");
}

void Test_Composite::init() {
  simple_composite_ = new SimpleComposite;
}

void Test_Composite::createSimpleComposite() {
  SimpleComposite composite;
}

void Test_Composite::testSimpleCompositeComponents() {
  UnitTests::testEqual(simple_composite_->getNumComponents(), 2);
}

void Test_Composite::meetsFormalRequirements() {
  testEqual(simple_composite_->getDefinitionSpaceDimensions(), 0);
  testEqual(simple_composite_->getFunctionName(), "SimpleComposite");
}

void Test_Composite::getNumParameters() {
  testEqual(simple_composite_->getNumParameters(), 0);
}

void Test_Composite::rotateAboutAllAxes() {
  simple_composite_->Transform(Rotation<4>(90., 0., 0., 0., 0., 90.), Vector<4>());
  fail("method to compare vertices to rotated vertices (must differ from each other) not yet implemented.");
}

void Test_Composite::rotated360DegreesIsIdentical() {
  simple_composite_->Transform(Rotation<4>(360., 360., 360., 360., 360., 360.), Vector<4>());
  fail("method to compare vertices to rotated vertices (must be equal) not yet implemented.");
}


