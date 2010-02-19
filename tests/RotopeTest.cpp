
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

    QVERIFY(std::find(_vertices.begin(), _vertices.end(), VecMath::Vector<4>(-1., -1., 0., 0.)) != _vertices.end());
    QVERIFY(std::find(_vertices.begin(), _vertices.end(), VecMath::Vector<4>(-1.,  1., 0., 0.)) != _vertices.end());
    QVERIFY(std::find(_vertices.begin(), _vertices.end(), VecMath::Vector<4>( 1., -1., 0., 0.)) != _vertices.end());
    QVERIFY(std::find(_vertices.begin(), _vertices.end(), VecMath::Vector<4>( 1.,  1., 0., 0.)) != _vertices.end());
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

    QVERIFY(std::find(_vertices.begin(), _vertices.end(), VecMath::Vector<4>(-1., -sqrt(0.75), 0., 0.)) != _vertices.end());
    QVERIFY(std::find(_vertices.begin(), _vertices.end(), VecMath::Vector<4>( 1., -sqrt(0.75), 0., 0.)) != _vertices.end());
    QVERIFY(std::find(_vertices.begin(), _vertices.end(), VecMath::Vector<4>( 0.,  sqrt(0.75), 0., 0.)) != _vertices.end());
    QVERIFY(_vertices.size() == 3);
}

void RotopeTest::circleRealm() {
    setRotope("ER");
    Realm definedCircle = generateCircleRealm();
    QVERIFY(_realm == definedCircle);
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
    setRotope("ER");

    QVERIFY(std::find(_vertices.begin(), _vertices.end(), VecMath::Vector<4>(-1., 0., 0., 0.)) != _vertices.end());
    QVERIFY(std::find(_vertices.begin(), _vertices.end(), VecMath::Vector<4>( 1., 0., 0., 0.)) != _vertices.end());

    // the line's end points are wrapped to the original points
    // this is implementation dependent, damn
    QVERIFY(_vertices.size() == 2*_numSegments+2);
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

}

void RotopeTest::cylinder1Realm() {
    setRotope("ERE");

}

void RotopeTest::cylinder1Vertices() {
    setRotope("ERE");

}

void RotopeTest::cylinder2Realm() {
    setRotope("EER");

}

void RotopeTest::cylinder2Vertices() {
    setRotope("EER");

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
