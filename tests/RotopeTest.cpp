
#include "RotopeTest.h"

/// \todo fix in RotopeBase that this must be included firat
#include "Rotation.h"
#include "Rotopes/RotopeBase.h"
#include "Rotopes/RotopeFactory.h"

Realm generateSquareRealm();
Realm generateTriangleRealm();
Realm generateCircleRealm();
std::vector<Realm> generateSphereSurfaceSquares();

void RotopeTest::initTestCase() { }

void RotopeTest::cleanupTestCase() { }

void RotopeTest::oneDimensionalRotope() {
    try {
        _rotope = RotopeFactory::generate(std::string("E"));
    } catch (std::logic_error e) {
        return;
    }
    QFAIL("Bad Rotope exception expected, but not thrown");
}

void RotopeTest::squareRealm() {
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

void RotopeTest::squareVertices() {
    setRotope("EE");

    QVERIFY(isInVertices(VecMath::Vector<4>(-1., -1., 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>(-1.,  1., 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1., -1., 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1.,  1., 0., 0.)));
    QVERIFY(_vertices.size() == 4);
}

void RotopeTest::triangleRealm() {
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

void RotopeTest::triangleVertices() {
    setRotope("ET");

    QVERIFY(isInVertices(VecMath::Vector<4>(-1., -sqrt(0.75), 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1., -sqrt(0.75), 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0.,  sqrt(0.75), 0., 0.)));
    QVERIFY(_vertices.size() == 3);
}

void RotopeTest::circleRealm() {
    setRotope("ER");
    Realm definedCircle = generateCircleRealm();
    QVERIFY(_realm == definedCircle);
}

Realm generateCircleRealm() {
    qWarning() << "Assuming that rotate_base::_numSegments equals 4";
    Realm circleRealm;
    for (unsigned i = 0; i < RotopeTest::numberOfVerticesForCircle(); i += 2)
        circleRealm.push_back(i);
    for (unsigned i = 1; i < RotopeTest::numberOfVerticesForCircle(); i += 2)
        circleRealm.push_back(i);
    circleRealm.setDimension(2);
    return circleRealm;
}

unsigned RotopeTest::numberOfVerticesForCircle() {
    // the line's end points are wrapped to the original points
    // this is implementation dependent, damn it
    return 2*_numSegments+2;
}
void RotopeTest::circleVertices() {
    setRotope("ER");

    QVERIFY(isInVertices(VecMath::Vector<4>(-1., 0., 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1., 0., 0., 0.)));

    QVERIFY(_vertices.size() == numberOfVerticesForCircle());
}

void RotopeTest::cubeRealm() {
    setRotope("EEE");

    QVERIFY(_realm.dimension() == 3);

    Realm square = generateSquareRealm();
    QVERIFY(_realm.contains(square));
    square.add(4);
    QVERIFY(_realm.contains(square));

    QVERIFY(_realm.size() == 6);
}

void RotopeTest::cubeVertices() {
    setRotope("EEE");
    // from now on, i'll only test for a few selected vertices
    QVERIFY(isInVertices(VecMath::Vector<4>(-1., -1., -1., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1.,  1.,  1., 0.)));
    QVERIFY(_vertices.size() == 8);
}

void RotopeTest::prismRealm() {
    setRotope("ETE");

    QVERIFY(_realm.dimension() == 3);

    Realm triangle = generateTriangleRealm();
    QVERIFY(_realm.contains(triangle));
    triangle.add(4);
    QVERIFY(_realm.contains(triangle));

    QVERIFY(_realm.size() == 5);
}

void RotopeTest::prismVertices() {
    setRotope("ETE");
    QVERIFY(isInVertices(VecMath::Vector<4>(-1., -sqrt(0.75), -1., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>(-1., -sqrt(0.75),  1., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0.,  sqrt(0.75),  1., 0.)));
    QVERIFY(_vertices.size() == 6);
}

void RotopeTest::cylinder1Realm() {
    setRotope("ERE");

    QVERIFY(_realm.dimension() == 3);

    Realm circle = generateCircleRealm();
    QVERIFY(_realm.contains(circle));
    circle.add(numberOfVerticesForCircle());
    QVERIFY(_realm.contains(circle));
    QVERIFY(_realm.size() == numberOfVerticesForCircle() + 2);
}

void RotopeTest::cylinder1Vertices() {
    setRotope("ERE");

    QVERIFY(isInVertices(VecMath::Vector<4>(-1., 0., -1., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1., 0., -1., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1., 0.,  1., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1., 0.,  1., 0.)));

    QVERIFY(_vertices.size() == 2*numberOfVerticesForCircle());

}

void RotopeTest::cylinder2Realm() {
    setRotope("EER");

    QVERIFY(_realm.dimension() == 3);

    QSKIP("Not sure how to correctly test Realm, and the caps are not yet implemented anyway.", SkipSingle);
    _rotope->print();

}

void RotopeTest::cylinder2Vertices() {
    setRotope("EER");

    QVERIFY(isInVertices(VecMath::Vector<4>(-1., -1., 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>(-1.,  1., 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1., -1., 0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1.,  1., 0., 0.)));

}

void RotopeTest::coneRealm() {
    setRotope("ERT");

    QVERIFY(_realm.dimension() == 3);

    QVERIFY(_realm.contains(generateCircleRealm()));

    QVERIFY(_realm.size() == numberOfVerticesForCircle() + 1);
}

void RotopeTest::coneVertices() {
    setRotope("ERT");
    QVERIFY(isInVertices(VecMath::Vector<4>(-1.,  0., -sqrt(0.75), 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1.,  0., -sqrt(0.75), 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0., -1., -sqrt(0.75), 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0.,  1., -sqrt(0.75), 0.)));

}

void RotopeTest::sphereRealm() {
    setRotope("ERR");

    QVERIFY(_realm.dimension() == 3);

    std::vector<Realm> surfaces = generateSphereSurfaceSquares();

    for (std::vector<Realm>::iterator i = surfaces.begin(); i != surfaces.end(); ++i)
        QVERIFY(_realm.contains(*i));

    std::cerr << _realm.toString();

    QSKIP("Sphere realm test not done yet.", SkipSingle);
}

std::vector<Realm> generateSphereSurfaceSquares() {
    std::vector<Realm> partialSphere;

    Realm squareSurface;    //  what is this actually called? damn, can't remember...

    squareSurface.push_back(0);
    squareSurface.push_back(10);
    squareSurface.push_back(12);
    squareSurface.push_back(2);
    squareSurface.setDimension(2);
    partialSphere.push_back(squareSurface);

    squareSurface.add(2);
    partialSphere.push_back(squareSurface);

    squareSurface.add(8);
    partialSphere.push_back(squareSurface);

    squareSurface.add(2);
    partialSphere.push_back(squareSurface);

    squareSurface.add(8);
    partialSphere.push_back(squareSurface);

    squareSurface.add(2);
    partialSphere.push_back(squareSurface);

    squareSurface.add(8);
    partialSphere.push_back(squareSurface);

    squareSurface.add(2);
    partialSphere.push_back(squareSurface);

    return partialSphere;
}

void RotopeTest::sphereVertices() {
    setRotope("ERR");
    QVERIFY(isInVertices(VecMath::Vector<4>(-1.,  0.,  0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 1.,  0.,  0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0., -1.,  0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0.,  1.,  0., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0.,  0.,  1., 0.)));
    QVERIFY(isInVertices(VecMath::Vector<4>( 0.,  0., -1., 0.)));

    for (std::vector< VecMath::Vector<4> >::const_iterator i = _vertices.begin();
            i != _vertices.end(); ++i) {
        QVERIFY(i->sqnorm() -1 < EPSILON);
    }
}

void RotopeTest::tesseractRealm() {
    setRotope("EEEE");
    QVERIFY(_realm.dimension() == 4);
    // test subrealms?
    QVERIFY(_realm.size() == 8);
}

void RotopeTest::tesseractVertices() {
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

void RotopeTest::penteract() {
    setRotope("EEEEE");
    // i need to think of ways to test objects with D > 4. later.
    if (false) printVertices();
}

void RotopeTest::setRotope(const string &generator) {
    _rotope = RotopeFactory::generate(generator);
    setRealm();
    setVertices();
}

void RotopeTest::setRealm() {
    _realm = _rotope->realm();
}

void RotopeTest::setVertices() {
    _vertices = _rotope->vertices();
}

bool RotopeTest::isInVertices(const VecMath::Vector<4> &vertex) const {
    if (std::find(_vertices.begin(), _vertices.end(), vertex) != _vertices.end()) return true;
    for (std::vector< VecMath::Vector<4> >::const_iterator i = _vertices.begin();
            i != _vertices.end(); ++i) {
        if ((vertex-*i).sqnorm() < EPSILON) return true;
    }
    return false;
}

void RotopeTest::printVertices() {
    for (std::vector< VecMath::Vector<4> >::const_iterator i = _vertices.begin();
            i != _vertices.end(); ++i) {
        std::cout << *i << std::endl;
    }
}
