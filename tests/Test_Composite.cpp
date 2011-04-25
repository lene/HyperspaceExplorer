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
  simple_composite_ = std::shared_ptr<Composite>(new SimpleComposite);
  view_ = std::shared_ptr<MockView>(new MockView);
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

    testEqual(view_->numVerticesDrawn(), 24);

    setGlobalView(view_);

    simple_composite_->for_each_vertex(checkVertexPresent);
    simple_composite_->for_each_projected(checkVertexDrawn);
}

void Test_Composite::ReInit() {
  try {
    simple_composite_->ReInit(-1., 1., 0.5,  -1., 1., 0.5,  -1., 1., 0.5);
  } catch (NotYetImplementedException e) {
      fail(e.what());
  }
  QSKIP("Implement me: Test_Composite::ReInit()", SkipSingle);
}

void Test_Composite::calibrateColors() {
  try {
    simple_composite_->calibrateColors();
  } catch (NotYetImplementedException e) {
      fail(e.what());
  }
  QSKIP("Implement me: Test_Composite::calibrateColors()", SkipSingle);
}

#include "Object.h"

class CompositeWithScaling: public Composite {
public:
  CompositeWithScaling(): Composite() {
    addComponent(
        std::shared_ptr<Displayable> (new Hypercube),
        VecMath::Vector<4>(-1., 0., 0., 0.),
        VecMath::Rotation<4>()
      );
      addComponent(
        std::shared_ptr<Displayable> (new Hypercube),
        VecMath::Vector<4>(0.5, 0., 0., 0.),
        VecMath::Rotation<4>(),
        VecMath::makeVector(0.5, 0.5, 0.5, 0.5)
      );
  }
  virtual std::string getFunctionName() const { return "CompositeWithScaling"; }
};

void Test_Composite::compositeWithScaling() {
  std::shared_ptr<Displayable> composite(new CompositeWithScaling);
  composite->Transform(Rotation<4>(), Vector<4>());
  composite->Project(PROJECTION_SCREEN_W, PROJECTION_CAMERA_W, false);
  composite->Draw(view_);
  std::vector< VecMath::Vector<4> > vertices_to_test;
  vertices_to_test.push_back(Vector<4>(-2., -1., -1., -1.));
  view_->printVertices();
  for (std::vector< VecMath::Vector<4> >::iterator it = vertices_to_test.begin();
          it != vertices_to_test.end(); ++it) {
//      if (!view_->isTransformedVertexPresent(*it)) view_->printVertices();
//    test(view_->isTransformedVertexPresent(*it), it->toString().append(" present"));
  }
  QSKIP("Implement me: Test_Composite::compositeWithScaling()", SkipSingle);

}

void Test_Composite::compositeWithRotation() {
   QSKIP("Implement me: Test_Composite::compositeWithRotation()", SkipSingle);
}

void Test_Composite::commitDrawIsDeferred() {
  QSKIP("To do: ensure that commitDraw() is executed only from the toplevel Composite Draw() routine", SkipSingle);
}