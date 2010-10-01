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

#ifndef TEST_PARAMETRICFUNCTION_H_
#define TEST_PARAMETRICFUNCTION_H_

#include "ParametricFunction.h"

#include "Rotation.h"

#include <QtTest/QtTest>

#include <tr1/memory>

/// Unit tests for class ParametricFunction
class Test_ParametricFunction: public QObject {

  Q_OBJECT

public:

  class ParametricFunctionTestImplementation: public ParametricFunction<4,3> {
    public:
      ParametricFunctionTestImplementation();

      virtual return_type f(const argument_type &) { return VecMath::Vector<4>(0.,0.,0.,CONST_FUNCTION_W); }

      const static double CONST_FUNCTION_W = 1.;
  };

  ~Test_ParametricFunction();

private slots:

  void initTestCase();
  void cleanupTestCase();

  void getNumParameters();
  void definedParametersArePresent();
  void definedParametersHaveCorrectValues();
  void getParameterValueWorks();
  void settingParameters();
  void accessedNonexistentParameter();
  void setParameters();
  void functionValue();

private:

  void initializeFunction();

  std::tr1::shared_ptr< ParametricFunction<4, 3> > _function;

  const static unsigned TEST_FUNCTION_NUM_PARAMETERS = 5;
  const static double DOUBLE_PARAMETER_VALUE;
  const static unsigned UNSIGNED_PARAMETER_VALUE;
  const static int INT_PARAMETER_VALUE;
  const static std::string STRING_PARAMETER_VALUE;
  const static VecMath::Rotation<5> ROTATION_PARAMETER_VALUE;

};


#endif /* FUNCTIONTEST_H_ */
