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

#ifndef FUNCTIONTEST_H_
#define FUNCTIONTEST_H_

#include <QtTest/QtTest>

#include "Displayable.h"

/// Unit tests for class Function
class Test_Function: public QObject {

  Q_OBJECT

  class FunctionTestImplementation: public Displayable {
  public:
    FunctionTestImplementation();

    virtual std::string getFunctionName() const { return TEST_FUNCTION_NAME; }

    VecMath::Vector<4> f() { return VecMath::Vector<4>(0.,0.,0.,_doubleParm); }
    void SetParameters(const ParameterMap &parms);

    virtual void scale(const VecMath::Vector< 4, double >&scaling_factor);
    virtual void Transform (const VecMath::Rotation<4> &R,
                            const VecMath::Vector<4> &T);
    virtual void Project (double, double, bool);
    virtual void Draw (std::shared_ptr< UI::View >);
    virtual void ReInit(double _tmin, double _tmax, double _dt,
                        double _umin, double _umax, double _du,
                        double _vmin, double _vmax, double _dv);
    virtual void calibrateColors() const;
    virtual unsigned getDefinitionSpaceDimensions();

    virtual void for_each_vertex(function_on_fourspace_vertex apply);
    virtual void for_each_projected(function_on_projected_vertex apply);

    double _doubleParm;
    unsigned _unsignedParm;
    int _intParm;
    std::string _stringParm;


  protected:
    virtual VecMath::Vector<4> &operator () (double x, double y, double z);
    virtual void Initialize (void);

  };

  class ParameterTestImplementation: public FunctionTestImplementation {
  public:
    ParameterTestImplementation();
  };

  class RotationParameterTestImplementation: public FunctionTestImplementation {
    public:
      RotationParameterTestImplementation();
  };

public:
  ~Test_Function();

private slots:

  void initTestCase();
  void cleanupTestCase();

  void instantiate();

  void parameters();
  void parameter_get();
  void parameter_set();
  void parameterWithoutCast();
  void setParameters();
  void accessedNonexistentParameter();
  void functionValue();
  void rotationAsParameter();

private:
  Displayable *_function;

  const static std::string TEST_FUNCTION_NAME;
  const static unsigned TEST_FUNCTION_DIMENSIONS = 3;
  const static unsigned TEST_FUNCTION_NUM_PARAMETERS = 4;

};


#endif /* FUNCTIONTEST_H_ */
