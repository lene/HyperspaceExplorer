/*
 * BasicTest.h
 *
 *  Created on: Jan 29, 2010
 *      Author: lene
 */

#ifndef BASICTEST_H_
#define BASICTEST_H_

#include <QtTest/QtTest>

class BasicTest: public QObject
{
public:
  BasicTest();
  virtual ~BasicTest();

private slots:
  void initTestCase() { qDebug("called before everything else"); }
  void myFirstTest()
  { QVERIFY(1 == 1); }
  void mySecondTest()
  { QVERIFY(1 != 2); }
  void cleanupTestCase()
  { qDebug("called after myFirstTest and mySecondTest"); }
};

#endif /* BASICTEST_H_ */
