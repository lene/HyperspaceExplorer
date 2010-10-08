/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#include "Test_DisplayableClass.h"

#include "GlobalFunctions.h"

#include "FunctionHolder.h"

#include <iostream>

using namespace UnitTests;
using std::vector;
using std::string;

void Test_DisplayableClass::initTestcase() {
//  root_ = DisplayableClass::getRootNode();
}

void Test_DisplayableClass::rootNode() {
  DisplayableClass root_ = DisplayableClass::getRootNode();
  testEqual(root_.getName(), "Displayable");
  testEqual(root_.getDescription(), "Objects");
}

void printDisplayableClass(const DisplayableClass &d) {
  std::cerr << d.getName() << ": " << d.getDescription() << std::endl;
}

bool containsClassWithName(const vector<DisplayableClass> &classes, const string &name) {
  for (vector<DisplayableClass>::const_iterator i = classes.begin(); i != classes.end(); ++i) {
    if (i->getName() == name) return true;
  }
  return false;
}

void Test_DisplayableClass::getSubClasses() {
  DisplayableClass root_ = DisplayableClass::getRootNode();
  string root_name = root_.getName();
  std::vector<DisplayableClass> subclasses = root_.getSubClasses();
  testEqual(subclasses.size(), 3);  // FunctionHolder, Surface, Object
  test(containsClassWithName(subclasses, "FunctionHolder"),
       "FunctionHolder is subclass of "+root_name);
  test(containsClassWithName(subclasses, "Surface"),
       "Surface is subclass of "+root_name);
  test(containsClassWithName(subclasses, "Object"),
       "Object is subclass of "+root_name);
}

void Test_DisplayableClass::findClass() {
  testEqual(DisplayableClass::findClass("FunctionHolder").getName(), "FunctionHolder");
  testEqual(DisplayableClass::findClass("RealFunction").getName(), "RealFunction");
  try {
    DisplayableClass::findClass("nonexistent class name");
    QFAIL("findClass() with a nonexistent class name should throw an exception!");
  } catch (const DisplayableClass::DisplayableClassException &e) { 
    return; 
  } catch (...) {
    QFAIL("findClass() with a nonexistent class name threw an exception, but of wrong type!");
  }
}

void Test_DisplayableClass::getDisplayables() {
  QSKIP("Not yet implemented", SkipSingle);
}

