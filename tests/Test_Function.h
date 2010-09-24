#ifndef FUNCTIONTEST_H_
#define FUNCTIONTEST_H_

#include <QtTest/QtTest>

#include "Function.h"

/// Unit tests for class Function
class Test_Function: public QObject {

  Q_OBJECT

  class FunctionTestImplementation: public Function {
  public:
    FunctionTestImplementation();

    virtual std::string getFunctionName() const { return TEST_FUNCTION_NAME; }

    VecMath::Vector<4> f() { return VecMath::Vector<4>(0.,0.,0.,_doubleParm); }
    void SetParameters(const ParameterMap &parms);

    virtual void Transform (const VecMath::Rotation<4> &R,
                            const VecMath::Vector<4> &T);
    virtual void Project (double, double, bool);
    virtual void Draw (UI::View*);
    virtual void ReInit(double _tmin, double _tmax, double _dt,
                        double _umin, double _umax, double _du,
                        double _vmin, double _vmax, double _dv);
    virtual void calibrateColors() const;
    virtual unsigned getDefinitionSpaceDimensions();

    virtual void for_each(function_on_fourspace_vertex apply);
    virtual void for_each(function_on_projected_vertex apply);

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
  Function *_function;

  const static std::string TEST_FUNCTION_NAME;
  const static unsigned TEST_FUNCTION_DIMENSIONS = 3;
  const static unsigned TEST_FUNCTION_NUM_PARAMETERS = 4;

};


#endif /* FUNCTIONTEST_H_ */
