
#include "VectorTest.h"

#include "Vector.h"

#include <sstream>
#include <string>

using VecMath::Vector;
using std::ostringstream;
using std::string;

void VectorTest::defaultConstructor() {
    Vector<3> v;
    for (unsigned i = 0; i < 3; ++i)
        QVERIFY(v[i] == 0.);
}

void VectorTest::varargsConstructor() {
    Vector<3> v(0., 1., 2.);
    for (unsigned i = 0; i < 3; ++i)
        QVERIFY(v[i] == (double)i);
}

void VectorTest::plus() {
    Vector<3> v1(0., 1., 2.), v2(1., 1., 1.);
    for (unsigned i = 0; i < 3; ++i)
        QVERIFY((v1+v2)[i] == (double)i+1.);
}

void VectorTest::minus() {
    Vector<3> v1(0., 1., 2.), v2(1., 1., 1.);
    for (unsigned i = 0; i < 3; ++i)
        QVERIFY((v1-v2)[i] == (double)i-1.);
}

void VectorTest::scale() {
    Vector<3> v1(0., 1., 2.);
    for (unsigned i = 0; i < 3; ++i)
        QVERIFY((v1*2.)[i] == (double)i*2.);
}

void VectorTest::dotProduct() {
    Vector<3> v1(2., 0., 0.), v2(0., 2., 0.);
    QVERIFY(v1*v1 == 4.);
    QVERIFY(v1*v2 == 0.);
}

void VectorTest::sqnorm() {
    Vector<3> v1(2., 0., 0.);
    QVERIFY(v1.sqnorm() == 4.);
}

void VectorTest::equals() {
    Vector<3> v1(2., 0., 0.), v2(1., 0., 0.);
    QVERIFY(v1 == v2*2.);
}

void VectorTest::smaller() {
    Vector<3> v1(2., 0., 0.), v2(1., 0., 0.);
    QVERIFY(v2 < v1);
    QVERIFY(!(v1 < v1));
    QVERIFY(!(v1 < v2));
}

void VectorTest::toString() {
    Vector<3> v(0., 1., 2.);
    string s = v.toString();

    QVERIFY(s.find("0") != s.npos);
    QVERIFY(s.find("1", s.find("0")) != s.npos);
    QVERIFY(s.find("2", s.find("1")) != s.npos);
}
