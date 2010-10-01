/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

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

#include "Test_Rotation.h"

#include "Vector.impl.h"
#include "Rotation.impl.h"
#include "Matrix.impl.h"

#include <sstream>
#include <string>


using VecMath::Rotation;
using VecMath::NumAxes;
using VecMath::Matrix;
using VecMath::Vector;
using std::ostringstream;
using std::string;

void Test_Rotation::defaultCtor() {
    Rotation<3> rot;
    for (unsigned i = 0; i < NumAxes<3>::num; ++i)
        QVERIFY(rot[i] == 0);
}
void Test_Rotation::varargsCtor() {
    Rotation<4> rot(1., 2., 3., 4., 5., 6.);
    for (unsigned i = 0; i < NumAxes<4>::num; ++i) {
        QVERIFY(rot[i] == i+1);
    }
}
void Test_Rotation::toMatrix() {
    Rotation<3> rot(0., 90., 0.);
    Matrix<3> m(rot);
    Vector<3> v(1., 0., 0.),
            vprime = m*v;
    QVERIFY(VecMath::sqnorm(Vector<3>(0.,0.,1.)-vprime) < EPSILON);

    QSKIP("Not understood yet how Rotation maps to a Matrix. "
          "Understand that and test other Rotations as well.",
          SkipSingle);
}

void Test_Rotation::plus() {
    Rotation<3> rot1(1., 2., 3.), rot2(-1., -1., -1.),
            rot = rot1+rot2;
    for (unsigned i = 0; i < NumAxes<3>::num; ++i) {
        QVERIFY(rot[i] == i);
    }
}
