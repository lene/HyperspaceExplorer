#ifndef FUNCTIONTEST_H_
#define FUNCTIONTEST_H_

#include <QtTest/QtTest>

class Function;

class FunctionTest: public QObject 
{

  Q_OBJECT

private slots:

  void initTestCase();
  void cleanupTestCase();

  void realFunction();
  void surfaceFunction();
  void complexFunction();
  void objectFunction();

private:

  Function *_function;

};


#endif /* FUNCTIONTEST_H_ */
