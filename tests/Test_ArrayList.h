/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#ifndef TEST_ARRAYLIST_H
#define TEST_ARRAYLIST_H

#include <QtTest/QtTest>

#include "ArrayList.h"

/// operator[] is defective when compiled with -O2. Should that ever change, define this.
#undef TEST_ACCESS_OPERATOR
/// Define this to compare run times for isPermutation() with Util::isPermutation().
#undef COMPARE_TIMES  

class Test_ArrayList: public QObject {

  Q_OBJECT

private slots:

  void makeListRuns();
  void minusElement2();
  void minusElement3();
  void test_isPermutation2();
  void test_isPermutation3();
  void test_isPermutation5();
  void test_isPermutation10();

# ifdef TEST_ACCESS_OPERATOR
    void accessOperator2();
    void accessOperator3();
    void accessOperator4();
    void accessOperator5();
    void accessOperator10();
# endif

# ifdef COMPARE_TIMES  
    void timing();
# endif    

};

#endif // TEST_ARRAYLIST_H
