
#include "RotationTest.h"

#include "Rotation.h"

#include <sstream>
#include <string>


using VecMath::Rotation;
using VecMath::NumAxes;
using VecMath::Matrix;
using VecMath::Vector;
using std::ostringstream;
using std::string;

void RotationTest::defaultCtor() {
    Rotation<3> rot;
    for (unsigned i = 0; i < NumAxes<3>::num; ++i)
        QVERIFY(rot[i] == 0);
}
void RotationTest::varargsCtor() {
    Rotation<4> rot(1., 2., 3., 4., 5., 6.);
    for (unsigned i = 0; i < NumAxes<4>::num; ++i) {
        QVERIFY(rot[i] == i+1);
    }
}
void RotationTest::toMatrix() {
    Rotation<3> rot(0., 90., 0.);
    Matrix<3> m(rot);
    Vector<3> v(1., 0., 0.),
            vprime = m*v;
    QVERIFY((Vector<3>(0.,0.,1.)-vprime).sqnorm() < EPSILON);

    QSKIP("Not understood yet how Rotation maps to a Matrix. "
          "Understand that and test other Rotations as well.",
          SkipSingle);
}

void RotationTest::plus() {
    Rotation<3> rot1(1., 2., 3.), rot2(-1., -1., -1.),
            rot = rot1+rot2;
    for (unsigned i = 0; i < NumAxes<3>::num; ++i) {
        QVERIFY(rot[i] == i);
    }
}
