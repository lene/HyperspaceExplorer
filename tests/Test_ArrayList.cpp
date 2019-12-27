/*
 * Hyperspace Explorer - visualizing higher-dimensional geometry
 * Copyright (C) 2011  Lene Preuss <lene.preuss@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "Test_ArrayList.h"

#include "GlobalFunctions.h"

#include "ArrayList.impl.h"

using namespace UnitTests;
using std::string;

void Test_ArrayList::makeListRuns() {
  makeArrayList(1, 2);
  makeArrayList(1., 2., 3.);
  ArrayList<4, string> string4 = makeArrayList(string("one"), string("two"), string("three"), string("four"));
}

# ifdef TEST_ACCESS_OPERATOR
  void Test_ArrayList::accessOperator2() {
    ArrayList<2, int> int2 = makeArrayList(1, 2);
    for (unsigned i = 0; i < 2; ++i) {
      testEqual(int2[i], i+1);
    }
  }
  void Test_ArrayList::accessOperator3(){
    ArrayList<3, double> double3 = makeArrayList(1., 2., 3.);
    qDebug() << double3.toString();
    for (unsigned i = 0; i < 3; ++i) {
      testEqual(double3[i], i+1);
    }
  }
  void Test_ArrayList::accessOperator4() {
    ArrayList<4, double> int4 = makeArrayList(0., 1., 2., 3.); 
    qDebug() << int4.toString();
    for (unsigned i = 0; i < 4; ++i) {
      testEqual(int4[i], i);
    }

  }

  void Test_ArrayList::accessOperator5() {
    ArrayList<5, int> int5 = makeArrayList(0, 1, 2, 3, 4);
    qDebug() << int5.toString();
    for (unsigned i = 0; i < 5; ++i) {
      testEqual(int5[i], i);
    }
  }

  void Test_ArrayList::accessOperator10() {
    ArrayList<10, int> int10 = makeArrayList(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    qDebug() << int10.toString();
    for (unsigned i = 0; i < 10; ++i) {
      testEqual(int10[i], i);
    }
  }
#endif

void Test_ArrayList::minusElement2() {
  ArrayList<2, int> int2 = makeArrayList(1, 2);

  ArrayList<1, int> head = int2.minusElement(1);
  ArrayList<1, int> tail = int2.minusElement(0);
  
  testEqual(head[0], 1);
  testEqual(tail[0], 2);
}

void Test_ArrayList::minusElement3() {
  ArrayList<3, double> double3 = makeArrayList(1., 2., 3.);
  
  ArrayList<2, double> first = double3.minusElement(2);
  ArrayList<2, double> gap = double3.minusElement(1);
  ArrayList<2, double> last = double3.minusElement(0);
  
  QVERIFY(first.contains(1.));
  QVERIFY(first.contains(2.));
  QVERIFY(!first.contains(3.));
  QVERIFY(gap.contains(1.));
  QVERIFY(!gap.contains(2.));
  QVERIFY(gap.contains(3.));
  QVERIFY(!last.contains(1.));
  QVERIFY(last.contains(2.));
  QVERIFY(last.contains(3.));

}

void Test_ArrayList::isPermutation2() {

  ArrayList<2, int> original = makeArrayList(0, 1);
  
  QVERIFY(isPermutation(original, original));
  QVERIFY(isPermutation(original, makeArrayList(1, 0)));  
  QVERIFY(!isPermutation(original, makeArrayList(1, 1)));  
}

void Test_ArrayList::isPermutation3() {
  
  ArrayList<3, int> original2 = makeArrayList(0, 1, 2);
  
  QVERIFY(isPermutation(original2, original2));
  QVERIFY(isPermutation(original2, makeArrayList(0, 2, 1)));
  QVERIFY(isPermutation(original2, makeArrayList(1, 0, 2)));
  QVERIFY(isPermutation(original2, makeArrayList(1, 2, 0)));  
  QVERIFY(isPermutation(original2, makeArrayList(2, 0, 1)));  
  QVERIFY(isPermutation(original2, makeArrayList(2, 1, 0)));  

  QVERIFY(!isPermutation(original2, makeArrayList(0, 0, 1)));
  QVERIFY(!isPermutation(original2, makeArrayList(0, 0, 2)));
  QVERIFY(!isPermutation(original2, makeArrayList(0, 1, 3)));
}

void Test_ArrayList::isPermutation5() {
  
  ArrayList<5, int> original3 = makeArrayList(0, 1, 2, 3, 4);
  
  QVERIFY(isPermutation(original3, original3));
  QVERIFY(isPermutation(original3, makeArrayList(4, 3, 2, 1, 0)));
  QVERIFY(!isPermutation(original3, makeArrayList(4, 4, 2, 1, 0)));
  QVERIFY(!isPermutation(original3, makeArrayList(5, 3, 2, 1, 0)));
}

void Test_ArrayList::isPermutation10() {
  
  ArrayList<10, int> original4 = makeArrayList(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
  
  QVERIFY(isPermutation(original4, original4));
  QVERIFY(isPermutation(original4, makeArrayList(0, 1, 2, 3, 4, 5, 6, 7, 9, 8)));
  QVERIFY(isPermutation(original4, makeArrayList(9, 8, 7, 6, 5, 4, 3, 2, 1, 0)));
  QVERIFY(!isPermutation(original4, makeArrayList(0, 1, 2, 3, 4, 5, 6, 7, 9, 9)));
  QVERIFY(!isPermutation(original4, makeArrayList(0, 1, 2, 3, 4, 5, 6, 7, 9, 10)));
  
}

#ifdef COMPARE_TIMES  

# include "Util.h"

  void Test_ArrayList::timing() {
    const unsigned run_count = 100000;
    {
      ScopedTimer t1("integer arguments");
      bool is;
      for (unsigned i = 0; i < run_count; ++i) {
        is = Util::isPermutation(0, 1, 2, 3, 4, 4, 3, 2, 1, 0);
      }
    }
    {
      ScopedTimer t2("arrayList");
      bool is;
      for (unsigned i = 0; i < run_count; ++i) {
        is = isPermutation(makeArrayList(0, 1, 2, 3, 4), makeArrayList(4, 3, 2, 1, 0));
      }
    } 
    {
      ScopedTimer t3("predefined arrayList");
      bool is;
      const ArrayList<5, int> l1 = makeArrayList(0, 1, 2, 3, 4), l2 = makeArrayList(4, 3, 2, 1, 0);
      for (unsigned i = 0; i < run_count; ++i) {
        is = isPermutation(l1, l2);
      }
    } 
  }
#endif    

void Test_ArrayList::shift() {
    test(makeArrayList(1,2,3).shift() == makeArrayList(2, 3, 1), "shift?");
}

void Test_ArrayList::reverse() {
    test(makeArrayList(1,2,3).reverse() == makeArrayList(3, 2, 1), "reverse (odd number of elements)");
    test(makeArrayList(1,2,3,4).reverse() == makeArrayList(4, 3, 2, 1), "reverse (even number of elements)");
}


void Test_ArrayList::circularPermutation() {
    test(isCircularPermutation(makeArrayList(1), makeArrayList(1)), "one element, equal");
    test(!isCircularPermutation(makeArrayList(1), makeArrayList(2)), "one element, not equal");
    test(isCircularPermutation(makeArrayList(1,2), makeArrayList(1,2)), "two elements, equal");
    test(isCircularPermutation(makeArrayList(1,2), makeArrayList(2,1)), "two elements, swapped");
    test(!isCircularPermutation(makeArrayList(1,2), makeArrayList(1,3)), "two elements, not equal");
    test(isCircularPermutation(makeArrayList(1,2,3), makeArrayList(1,2,3)), "three elements, equal");
    test(isCircularPermutation(makeArrayList(1,2,3), makeArrayList(3,1,2)), "three elements, shifted");
    test(isCircularPermutation(makeArrayList(1,2,3), makeArrayList(3,2,1)), "three elements, reversed");
    test(!isCircularPermutation(makeArrayList(1,2,3), makeArrayList(4,2,1)), "three elements, not equal");
    test(isCircularPermutation(makeArrayList(1,2,3,4), makeArrayList(1,2,3,4)), "four elements, equal");
    test(isCircularPermutation(makeArrayList(1,2,3,4), makeArrayList(4,1,2,3)), "four elements, shifted");
    test(isCircularPermutation(makeArrayList(1,2,3,4), makeArrayList(4,3,2,1)), "four elements, reversed");
    test(!isCircularPermutation(makeArrayList(1,2,3,4), makeArrayList(1,2,4,3)), "four elements, garbled");

}