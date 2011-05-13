/* 
 * File:   Test_Util.h
 * Author: lene
 *
 * Created on May 13, 2011, 8:09 PM
 */

#ifndef TEST_UTIL_H
#define	TEST_UTIL_H

#include <QtTest/QtTest>

class Test_Util: public QObject {

  Q_OBJECT

private slots:

  void find_in_vector();
  void itoa();
  void atoi();
  void ftoa();
  void atod();
  void isPermutation();
  void trim();
  void explode();

};

#endif	/* TEST_UTIL_H */

