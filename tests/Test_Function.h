#ifndef FUNCTIONTEST_H_
#define FUNCTIONTEST_H_

#include <QtTest/QtTest>

#include "Function.h"

class Function;

class Test_Function: public QObject {

  Q_OBJECT

  class FunctionTestImplementation: public Function {
  public:
    FunctionTestImplementation();
    virtual void Transform (const VecMath::Rotation<4> &R,
                            const VecMath::Vector<4> &T);
    virtual void Project (double, double, bool);
    virtual void Draw (void);
    virtual void ReInit(double _tmin, double _tmax, double _dt,
                        double _umin, double _umax, double _du,
                        double _vmin, double _vmax, double _dv);
    virtual void calibrateColors() const;
    virtual unsigned getDefinitionSpaceDimensions();
    void SetParameters(const ParameterMap &parms);

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
  
public:
  ~Test_Function();
    
private slots:

  void initTestCase();
  void cleanupTestCase();

  void instantiate();

  void parameters();
  void parameterWithoutCast();
  void setParameters();
  void accessedNonexistentParameter();

private:
  Function *_function;
  
  const static QString TEST_FUNCTION_NAME;
  const static unsigned TEST_FUNCTION_DIMENSIONS = 3;
  const static unsigned TEST_FUNCTION_NUM_PARAMETERS = 4;

};


#endif /* FUNCTIONTEST_H_ */
