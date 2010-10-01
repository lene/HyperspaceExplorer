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

#include "Test_Rotope.h"

/// \todo fix in RotopeBase that this must be included firat
#include "Rotation.h"
#include "Rotopes/RotopeInterface.h"
#include "Rotopes/RotopeFactory.h"

#include <string>

Realm generateSquareRealm();
Realm generateTriangleRealm();
Realm generateCircleRealm();
std::vector<Realm> generatePartialSphereSurfaceSquares();

void Test_Rotope::initTestCase() { }

void Test_Rotope::cleanupTestCase() { }

void Test_Rotope::oneDimensionalRotope() {
    try {
        _rotope = RotopeFactory::generate(std::string("E"));
    } catch (std::logic_error e) {
        return;
    }
    QFAIL("Bad Rotope exception expected, but not thrown");
}

void Test_Rotope::squareRealm() {
    setRotope("EE");
    Realm definedSquare = generateSquareRealm();

    QVERIFY(_realm == definedSquare);
}

Realm generateSquareRealm() {
    Realm squareRealm;
    squareRealm.push_back(0);
    squareRealm.push_back(1);
    squareRealm.push_back(3);
    squareRealm.push_back(2);
    squareRealm.setDimension(2);
    return squareRealm;
}

void Test_Rotope::squareVertices() {
    setRotope("EE");

    QVERIFY(isInVertices(VecMath::Vector<4>(-1., -1., 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>(-1.,  1., 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1., -1., 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1.,  1., 0., 0.)));
    QVERIFY(_vertices.size() == 4);
}

void Test_Rotope::triangleRealm() {
    setRotope("ET");
    Realm definedTriangle = generateTriangleRealm();

    QVERIFY(_realm == definedTriangle);
}

Realm generateTriangleRealm() {
    Realm triangleRealm;
    triangleRealm.push_back(0);
    triangleRealm.push_back(1);
    triangleRealm.push_back(2);
    triangleRealm.setDimension(2);
    return triangleRealm;
}

void Test_Rotope::triangleVertices() {
    setRotope("ET");

    QVERIFY(isInVertices(VecMath::Vector<4>(-1., -sqrt(0.75), 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1., -sqrt(0.75), 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0.,  sqrt(0.75), 0., 0.)));
    QVERIFY(_vertices.size() == 3);
}

void Test_Rotope::circleRealm() {
    setRotope("ER");
    Realm definedCircle = generateCircleRealm();
    QVERIFY2(_realm == definedCircle, (_realm.toString()+" != "+definedCircle.toString()).c_str());
}

Realm generateCircleRealm() {
    Realm circleRealm;
    for (unsigned i = 0; i < Test_Rotope::numberOfVerticesForCircle(); i += 2)
        circleRealm.push_back(i);
    for (unsigned i = 1; i < Test_Rotope::numberOfVerticesForCircle(); i += 2)
        circleRealm.push_back(i);
    circleRealm.setDimension(2);
    return circleRealm;
}

unsigned Test_Rotope::numberOfVerticesForCircle() {
    // the line's end points are wrapped to the original points
    // this is implementation dependent, damn it
    return 2*RotopeInterface::DEFAULT_NUM_SEGMENTS+2;
}
void Test_Rotope::circleVertices() {
    setRotope("ER");

    QVERIFY(isInVertices(VecMath::Vector<4>(-1., 0., 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1., 0., 0., 0.)));

    QVERIFY(_vertices.size() == numberOfVerticesForCircle());
}

void Test_Rotope::cubeRealm() {
    setRotope("EEE");

    QVERIFY(_realm.dimension() == 3);

    Realm square = generateSquareRealm();
    QVERIFY(_realm.contains(square));
    square.addOffset(4);
    QVERIFY(_realm.contains(square));

    QVERIFY(_realm.size() == 6);
}

void Test_Rotope::cubeVertices() {
    setRotope("EEE");
    // from now on, i'll only test for a few selected vertices
    QVERIFY(isInVertices(VecMath::Vector<4>(-1., -1., -1., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1.,  1.,  1., 0.)));
    QVERIFY(_vertices.size() == 8);
}

void Test_Rotope::prismRealm() {
    setRotope("ETE");

    QVERIFY(_realm.dimension() == 3);

    Realm triangle = generateTriangleRealm();
    QVERIFY(_realm.contains(triangle));
    triangle.addOffset(3);
    QVERIFY(_realm.contains(triangle));

    QVERIFY(_realm.size() == 5);
}

void Test_Rotope::prismVertices() {
    setRotope("ETE");
    QVERIFY(isInVertices(VecMath::Vector<4>(-1., -sqrt(0.75), -1., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>(-1., -sqrt(0.75),  1., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0.,  sqrt(0.75),  1., 0.)));
    QVERIFY(_vertices.size() == 6);
}

void Test_Rotope::cylinder1Realm() {
    setRotope("ERE");

    QVERIFY(_realm.dimension() == 3);

    Realm circle = generateCircleRealm();
    QVERIFY(_realm.contains(circle));
    circle.addOffset(numberOfVerticesForCircle());
    QVERIFY(_realm.contains(circle));
    QVERIFY(_realm.size() == numberOfVerticesForCircle() + 2);
}

void Test_Rotope::cylinder1Vertices() {
    setRotope("ERE");

    QVERIFY(isInVertices(VecMath::Vector<4>(-1., 0., -1., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1., 0., -1., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1., 0.,  1., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1., 0.,  1., 0.)));

    QVERIFY(_vertices.size() == 2*numberOfVerticesForCircle());

}

void Test_Rotope::cylinder2Realm() {
    setRotope("EER");

    QVERIFY(_realm.dimension() == 3);

    QSKIP("Not sure how to correctly test Realm, and the caps are not yet implemented anyway.", SkipSingle);
    _rotope->print();

}

void Test_Rotope::cylinder2Vertices() {
    setRotope("EER");

    QVERIFY(isInVertices(VecMath::Vector<4>(-1., -1., 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>(-1.,  1., 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1., -1., 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1.,  1., 0., 0.)));

}

void Test_Rotope::coneRealm() {
    setRotope("ERT");

    QVERIFY(_realm.dimension() == 3);

    QVERIFY(_realm.contains(generateCircleRealm()));

    QVERIFY(_realm.size() == numberOfVerticesForCircle() + 1);
}

void Test_Rotope::coneVertices() {
    setRotope("ERT");
    QVERIFY(isInVertices(VecMath::Vector<4>(-1.,  0., -sqrt(0.75), 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1.,  0., -sqrt(0.75), 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0., -1., -sqrt(0.75), 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0.,  1., -sqrt(0.75), 0.)));

}

void Test_Rotope::sphereRealm() {
    setRotope("ERR");

    QVERIFY2(_realm.dimension() == 3,
             (QString("Actual dimension: ")+QString::number(_realm.dimension())).toAscii());

    std::vector<Realm> surfaces = generatePartialSphereSurfaceSquares();

    for (std::vector<Realm>::iterator i = surfaces.begin(); i != surfaces.end(); ++i) {
        QVERIFY(_realm.contains(*i));
    }
}

std::vector<Realm> generatePartialSphereSurfaceSquares() {
    std::vector<Realm> partialSphere;

    Realm squareSurface;    //  what is this rectangular part of a surface actually called? damn, can't remember...
    unsigned VERTICES = Test_Rotope::numberOfVerticesForCircle();

    squareSurface.push_back(0);
    squareSurface.push_back(VERTICES);
    squareSurface.push_back(VERTICES+2);
    squareSurface.push_back(2);
    squareSurface.setDimension(2);
    partialSphere.push_back(squareSurface);

    squareSurface.addOffset(2);
    partialSphere.push_back(squareSurface);

    squareSurface.addOffset(VERTICES-2);
    partialSphere.push_back(squareSurface);

    squareSurface.addOffset(2);
    partialSphere.push_back(squareSurface);

    squareSurface.addOffset(VERTICES-2);
    partialSphere.push_back(squareSurface);

    squareSurface.addOffset(2);
    partialSphere.push_back(squareSurface);

    squareSurface.addOffset(VERTICES-2);
    partialSphere.push_back(squareSurface);

    squareSurface.addOffset(2);
    partialSphere.push_back(squareSurface);

    return partialSphere;
}

void Test_Rotope::sphereRealmFull() {
    setRotope("ERR");
    for (unsigned i =0; i < _vertices.size(); ++i) {
        QVERIFY(_realm.contains(i));
    }
    QVERIFY(!(_realm.contains(_vertices.size())));
}

void Test_Rotope::sphereVertices() {
    setRotope("ERR");
    QVERIFY(isInVertices(VecMath::Vector<4>(-1.,  0.,  0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1.,  0.,  0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0., -1.,  0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0.,  1.,  0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0.,  0.,  1., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0.,  0., -1., 0.)));

    for (std::vector< VecMath::Vector<4> >::const_iterator i = _vertices.begin();
            i != _vertices.end(); ++i) {
        QVERIFY(VecMath::sqnorm(*i) -1 < EPSILON);
    }
}

void Test_Rotope::rotateTaper() {
    try {
        setRotope("ETR");
    } catch (BadRotopeOperation e) {
        return;
    }
    QFAIL("Generating a Rotation of a Taper should throw a BadRotopeOperation.");
}

void Test_Rotope::rotateExtrudedTaper() {
    try {
        setRotope("ETER");
    } catch (BadRotopeOperation e) {
        return;
    }
    QFAIL("Generating a Rotation of an extruded Taper should throw a BadRotopeOperation.");
}

void Test_Rotope::tesseractRealm() {
    setRotope("EEEE");
    QVERIFY(_realm.dimension() == 4);
    // test subrealms?
    QVERIFY(_realm.size() == 8);
}

void Test_Rotope::tesseractVertices() {
    setRotope("EEEE");
    for (double x = -1; x <= 1; x += 2) {
        for (double y = -1; y <= 1; y += 2) {
            for (double z = -1; z <= 1; z += 2) {
                for (double w = -1; w <= 1; w += 2) {
                    QVERIFY(isInVertices(VecMath::Vector<4>(x, y, z, w)));
                }
            }
        }
    }
    QVERIFY(_vertices.size() == 16);
}

void Test_Rotope::penteract() {
    setRotope("EEEEE");
    // i need to think of ways to test objects with D > 4. later.
    if (false) printVertices();
}

void Test_Rotope::setRotope(const string &generator) {
    _rotope = RotopeFactory::generate(generator);
    setRealm();
    setVertices();
}

void Test_Rotope::setRealm() {
    _realm = _rotope->realm();
}

void Test_Rotope::setVertices() {
    _vertices = _rotope->projected_vertices();
}

bool Test_Rotope::isInVertices(const VecMath::Vector<4> &vertex) const {
    if (std::find(_vertices.begin(), _vertices.end(), vertex) != _vertices.end()) return true;
    for (std::vector< VecMath::Vector<4> >::const_iterator i = _vertices.begin();
            i != _vertices.end(); ++i) {
        if (VecMath::sqnorm(vertex-*i) < EPSILON) return true;
    }
    return false;
}

void Test_Rotope::printVertices() {
    for (std::vector< VecMath::Vector<4> >::const_iterator i = _vertices.begin();
            i != _vertices.end(); ++i) {
        std::cout << *i << std::endl;
    }
}
