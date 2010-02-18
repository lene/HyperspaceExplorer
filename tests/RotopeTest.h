#ifndef ROTOPETEST_H_
#define ROTOPETEST_H_

#include <QtTest/QtTest>

class RotopeBase;

class RotopeTest: public QObject {

  Q_OBJECT

private slots:
  void initTestCase();
  void cleanupTestCase();

  void oneDimensionalRotope();
  void square();
  void triangle();
  void circle();

private:
  RotopeBase *_rotope;

};


#endif /* ROTOPETEST_H_ */
