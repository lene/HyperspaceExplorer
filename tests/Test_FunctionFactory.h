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

#ifndef TEST_FUNCTIONFACTORY_H
#define TEST_FUNCTIONFACTORY_H

#include "FunctionFactory.h"
#include "RealFunction.h"

#include <QtTest/QtTest>


class Test_FunctionFactory : public QObject {

  Q_OBJECT

public:

    class FunctionTestImplementation: public RealFunction {
  public:
    FunctionTestImplementation() { }

    virtual std::string getFunctionName() const { return TEST_FUNCTION_NAME; }

    VecMath::Vector<4> f() { return VecMath::Vector<4>(0.,0.,0.,1.); }

  };

private slots:

  void registerFunction();

  void unregisterFunction();
  void createFunction();
  void listFunctions();

private:

  void printRegisteredFunctions();

  Displayable *_function;

  const static std::string TEST_FUNCTION_NAME;

};

#endif // TEST_FUNCTIONFACTORY_H
