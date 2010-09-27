
#include "Test_Matrix.h"

#include "Matrix.impl.h"
#include "Vector.impl.h"

#include <sstream>
#include <string>

using VecMath::Matrix;
using VecMath::Vector;
using std::ostringstream;
using std::string;

void Test_Matrix::defaultConstructor() {
    Matrix<3> m;
    for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 3; ++j) {
            if (i != j) QVERIFY(m(i, j) == 0.);
            else QVERIFY(m(i, j) == 1.);
        }
    }
}

void Test_Matrix::rotationAboutAxisConstructor() {
    Matrix<3> m(0, 1, 90.);

    QVERIFY(fabs(m(0,0)) < EPSILON);
    QVERIFY(fabs(m(0,1)+1) < EPSILON);
    QVERIFY(fabs(m(1,0)-1) < EPSILON);
    QVERIFY(fabs(m(1,1)) < EPSILON);
    QVERIFY(m(2,2) == 1);
}

void Test_Matrix::matrixMultiplication() {
    Matrix<3> m1(0, 1, 90.), m2(0, 1, 180.), u;
    for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 3; ++j) {
            QVERIFY(fabs((m1*m1)(i,j)-m2(i,j)) < EPSILON);
            QVERIFY((m1*u)(i,j) == m1(i, j));
        }
    }
}

void Test_Matrix::vectorMultiplication() {
    Matrix<3> m1(0,1,90.), u;
    Vector<3> v(1.,0.,0.);

    QVERIFY(u*v == v);
    QVERIFY(VecMath::sqnorm(m1*v-Vector<3>(0., 1., 0.)) < EPSILON);
}

void Test_Matrix::toString() {
    Matrix<3> m;
    for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 3; ++j) {
            m(i,j) = 3.*i+j;
        }
    }

    string s = m.toString();

    qWarning() << "This test relies on the string representation being sorted row-wise.";
    QVERIFY(s.find("0") != s.npos);
    QVERIFY(s.find("1", s.find("0")) != s.npos);
    QVERIFY(s.find("2", s.find("1")) != s.npos);
    QVERIFY(s.find("3", s.find("2")) != s.npos);
    QVERIFY(s.find("4", s.find("3")) != s.npos);
    QVERIFY(s.find("5", s.find("4")) != s.npos);
    QVERIFY(s.find("6", s.find("5")) != s.npos);
    QVERIFY(s.find("7", s.find("6")) != s.npos);
    QVERIFY(s.find("8", s.find("7")) != s.npos);
}
