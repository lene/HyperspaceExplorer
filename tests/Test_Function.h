#ifndef FUNCTIONTEST_H_
#define FUNCTIONTEST_H_

#include <QtTest/QtTest>

class Function;

class Test_Function: public QObject {

  Q_OBJECT

public:
  ~Test_Function();
    
private slots:

  void initTestCase();
  void cleanupTestCase();

  void surfaceFunction();
  void complexFunction();
  void objectFunction();

private:
  Function *_function;

};


#endif /* FUNCTIONTEST_H_ */
