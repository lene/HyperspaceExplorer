
#include "MatrixTest.h"

#include "Matrix.h"

#include <sstream>
#include <string>

using VecMath::Matrix;
using VecMath::Vector;
using std::ostringstream;
using std::string;

void MatrixTest::defaultConstructor() {
    Matrix<3> m;
    for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 3; ++j) {
            if (i != j) QVERIFY(m(i, j) == 0.);
            else QVERIFY(m(i, j) == 1.);
        }
    }
}

void MatrixTest::rotationAboutAxisConstructor() {
    Matrix<3> m(0, 1, 90.);

    QVERIFY(fabs(m(0,0)) < 1e-8);
    QVERIFY(fabs(m(0,1)+1) < 1e-8);
    QVERIFY(fabs(m(1,0)-1) < 1e-8);
    QVERIFY(fabs(m(1,1)) < 1e-8);
    QVERIFY(m(2,2) == 1);
}

void MatrixTest::matrixMultiplication() {
    Matrix<3> m1(0, 1, 90.), m2(0, 1, 180.), u;
    for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 3; ++j) {
            QVERIFY(fabs((m1*m1)(i,j)-m2(i,j)) < 1e-8);
            QVERIFY((m1*u)(i,j) == m1(i, j));
        }
    }
}

void MatrixTest::vectorMultiplication() {
    Matrix<3> m1(0,1,90.), u;
    Vector<3> v(1.,0.,0.);

    QVERIFY(u*v == v);
    QVERIFY((m1*v-Vector<3>(0., 1., 0.)).sqnorm() < 1e-8);
}

void MatrixTest::print() {
    Matrix<3> m;
    for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 3; ++j) {
            m(i,j) = 3.*i+j;
        }
    }

    string s = m.Print();

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