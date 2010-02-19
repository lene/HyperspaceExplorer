
#include "RotopeTest.h"

/// \todo fix in RotopeBase that this must be included firat
#include "Rotation.h"
#include "Rotopes/RotopeBase.h"
#include "Rotopes/RotopeFactory.h"

Realm generateSquareRealm();
Realm generateTriangleRealm();
Realm generateCircleRealm();

void RotopeTest::initTestCase() {

}

void RotopeTest::cleanupTestCase() {
}

void RotopeTest::oneDimensionalRotope() {
    try {
        _rotope = RotopeFactory::generate(std::string("E"));
    } catch (std::logic_error e) {
        return;
    }
    QFAIL("Bad Rotope exception expected, but not thrown");
}

void RotopeTest::squareRealm() {
    _rotope = RotopeFactory::generate(std::string("EE"));
    Realm squareEdges = _rotope->realm();
    Realm definedSquare = generateSquareRealm();

    QVERIFY(squareEdges == definedSquare);
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
    _rotope = RotopeFactory::generate(std::string("EE"));
    std::vector<VecMath::Vector<4> > vertices = _rotope->vertices();

    QVERIFY(std::find(vertices.begin(), vertices.end(), VecMath::Vector<4>(-1., -1., 0., 0.)) != vertices.end());
    QVERIFY(std::find(vertices.begin(), vertices.end(), VecMath::Vector<4>(-1.,  1., 0., 0.)) != vertices.end());
    QVERIFY(std::find(vertices.begin(), vertices.end(), VecMath::Vector<4>( 1., -1., 0., 0.)) != vertices.end());
    QVERIFY(std::find(vertices.begin(), vertices.end(), VecMath::Vector<4>( 1.,  1., 0., 0.)) != vertices.end());
    QVERIFY(vertices.size() == 4);
}

void RotopeTest::triangleRealm() {
    _rotope = RotopeFactory::generate(std::string("ET"));
    Realm triangleEdges = _rotope->realm();
    Realm definedTriangle = generateTriangleRealm();

    QVERIFY(triangleEdges == definedTriangle);
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
    _rotope = RotopeFactory::generate(std::string("ET"));
    std::vector<VecMath::Vector<4> > vertices = _rotope->vertices();

    QVERIFY(std::find(vertices.begin(), vertices.end(), VecMath::Vector<4>(-1., -sqrt(0.75), 0., 0.)) != vertices.end());
    QVERIFY(std::find(vertices.begin(), vertices.end(), VecMath::Vector<4>( 1., -sqrt(0.75), 0., 0.)) != vertices.end());
    QVERIFY(std::find(vertices.begin(), vertices.end(), VecMath::Vector<4>( 0.,  sqrt(0.75), 0., 0.)) != vertices.end());
    QVERIFY(vertices.size() == 3);
}

void RotopeTest::circleRealm() {
    _rotope = RotopeFactory::generate(std::string("ER"));
    Realm circleEdges = _rotope->realm();
    Realm definedCircle = generateCircleRealm();

    QVERIFY(circleEdges == definedCircle);
}

/// this is valid if rotate_base::_numSegments equals 4
Realm generateCircleRealm() {

    Realm circleRealm;
    for (unsigned i = 0; i < 2*RotopeTest::_numSegments+2; i += 2)
        circleRealm.push_back(i);
    for (unsigned i = 1; i < 2*RotopeTest::_numSegments+2; i += 2)
        circleRealm.push_back(i);
    circleRealm.setDimension(2);
    return circleRealm;
}

void RotopeTest::circleVertices() {
    _rotope = RotopeFactory::generate(std::string("ER"));
    std::vector<VecMath::Vector<4> > vertices = _rotope->vertices();

    QVERIFY(std::find(vertices.begin(), vertices.end(), VecMath::Vector<4>(-1., 0., 0., 0.)) != vertices.end());
    QVERIFY(std::find(vertices.begin(), vertices.end(), VecMath::Vector<4>( 1., 0., 0., 0.)) != vertices.end());

    // the line's end points are wrapped to the original points
    // this is implementation dependent, damn
    QVERIFY(vertices.size() == 2*_numSegments+2);
}

void RotopeTest::cubeRealm() {
    _rotope = RotopeFactory::generate(std::string("EEE"));
    Realm cubeSurfaces = _rotope->realm();
    QVERIFY(cubeSurfaces.dimension() == 3);

    Realm square = generateSquareRealm();
    QVERIFY(cubeSurfaces.contains(square));
    square.add(4);
    QVERIFY(cubeSurfaces.contains(square));

    QVERIFY(cubeSurfaces.size() == 6);
}

void RotopeTest::prismRealm() {
    _rotope = RotopeFactory::generate(std::string("ETE"));
    Realm prismSurfaces = _rotope->realm();
    QVERIFY(prismSurfaces.dimension() == 3);

    Realm triangle = generateTriangleRealm();
    QVERIFY(prismSurfaces.contains(triangle));
    triangle.add(4);
    QVERIFY(prismSurfaces.contains(triangle));

    QVERIFY(prismSurfaces.size() == 5);
}

