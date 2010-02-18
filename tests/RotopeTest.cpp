
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

void RotopeTest::square() {
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

void RotopeTest::triangle() {
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

void RotopeTest::circle() {
    _rotope = RotopeFactory::generate(std::string("ER"));
    Realm circleEdges = _rotope->realm();
    Realm definedCircle = generateCircleRealm();

    QVERIFY(circleEdges == definedCircle);
}

/// this is valid if rotate_base::_numSegments equals 4
Realm generateCircleRealm() {
    Realm circleRealm;
    circleRealm.push_back(0);
    circleRealm.push_back(2);
    circleRealm.push_back(4);
    circleRealm.push_back(6);
    circleRealm.push_back(8);
    circleRealm.push_back(1);
    circleRealm.push_back(3);
    circleRealm.push_back(5);
    circleRealm.push_back(7);
    circleRealm.push_back(9);
    circleRealm.setDimension(2);
    return circleRealm;
}
