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

#include "Rotation.impl.h"

using namespace UnitTests;

using VecMath::Rotation;
using VecMath::Vector;

void Test_Composite::initTestCase() {
  ColMgrMgr::Instance().setColorManager("XYZ to RGB");
}

void Test_Composite::init() {
  simple_composite_ = new SimpleComposite;
  view_ = new MockView;
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
  try {
    simple_composite_->for_each_vertex_transformed(testVerticesNotEqual);
  } catch (const NotYetImplementedException &e) {
    fail(e.what());
  }
}

Vector<4> offset;
void testVerticesEqualPlusOffset(const Vector<4> &v1, const Vector<4> &v2) {
    testVerticesEqual(v1+offset, v2);
}

void Test_Composite::rotated360DegreesIsIdentical() {
  simple_composite_->Transform(Rotation<4>(360., 360., 360., 360., 360., 360.), Vector<4>());
  try {
    for (unsigned i = 0; i < simple_composite_->getNumComponents(); ++i) {
      CompositeComponent sub_component = simple_composite_->getComponent(i);
      std::shared_ptr<Displayable> component_object = sub_component.component_;
      offset = sub_component.translation_;
      component_object->for_each_vertex_transformed(testVerticesEqualPlusOffset);
    }
  } catch (const NotYetImplementedException &e) {
    QSKIP(e.what(), SkipSingle);
  }
}

void testProjectedPlusOffset(const Vector<4> &original, const Vector<4> &, const Vector<3> &projected) {
    static Vector<4> dummy;
    checkProjectedVertex(original+offset, dummy, projected);
}

void Test_Composite::project() {

  simple_composite_->Transform(Rotation<4>(), Vector<4>());
  simple_composite_->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, false);

  setProjectionParameters(PROJECTION_CAMERA_W, PROJECTION_SCREEN_W);
  try {
    for (unsigned i = 0; i < simple_composite_->getNumComponents(); ++i) {
      CompositeComponent sub_component = simple_composite_->getComponent(i);
      std::shared_ptr<Displayable> component_object = sub_component.component_;
      offset = sub_component.translation_;
      component_object->for_each_vertex_transformed_projected(testProjectedPlusOffset);
    }
  } catch (const NotYetImplementedException &e) {
    QSKIP(e.what(), SkipSingle);
  }

}

void Test_Composite::draw() {

    simple_composite_->Transform(Rotation<4>(), Vector<4>());
    simple_composite_->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, false);

    simple_composite_->Draw(view_);
    view_->printVertices();
    testGreaterEqual(view_->numVerticesDrawn(), 32);

    setGlobalView(view_);

    simple_composite_->for_each_vertex(checkVertexPresent);
    simple_composite_->for_each_projected(checkVertexDrawn);
}

