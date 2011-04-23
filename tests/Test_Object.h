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

#ifndef TEST_OBJECT_H_
#define TEST_OBJECT_H_

#include <QtTest/QtTest>

#include "Object.h"

class MockView;

/// Unit tests for class Object and its implementations
class Test_Object: public QObject {

  Q_OBJECT

  class ObjectTestImplementation;

  static const unsigned NUM_PARAMETERS = 3;

  const static QString TEST_FUNCTION_NAME;

public:
  static const double CONSTANT_FUNCTION_VALUE = 1.;

private slots:

  void initTestCase();
  void init();

  void getDefinitionSpaceDimensions();
  void getNumParameters();
  void meetsFormalRequirements();
  void ReInit();

  void rotateAboutAllAxes();
  void rotated360DegreesIsIdentical();

  void project();
  void projectWithDepthCue();

  void draw();

  void tesseract();
  void pentachoron();
  void mengersponge();
  void sierpinskigasket();
  void altmengersponge();

private:

  void testFunction(Object *f);
  void testDynamicallyCreatedFunction(const std::string& fname);
  void testDrawDrawsAllVertices(Object * f);
  void testAllVerticesDrawn(Object *f);
  void testNonzeroRotationRuns(Object * f);

  ObjectTestImplementation *object_;
  MockView *view_;
};

void testGetParametersRuns(Object * f);
void testReinitRuns(Object * f);


#if 0
#endif
#endif /* REALFUNCTIONTEST_H_ */
