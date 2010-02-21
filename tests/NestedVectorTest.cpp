
#include "NestedVectorTest.h"

#include "NestedVector.h"

#include <algorithm>

using VecMath::NestedVector;

void NestedVectorTest::push_back_1D() {
    NestedVectorTest::Vector1D v;

    v.push_back(1);

    if (std::find(v.begin(), v.end(), 1) == v.end())
        QFAIL("1 not found.");
}

void NestedVectorTest::push_back_2D() {
    Vector2D v;
    Vector1D v1 = generate1DVector();

    v.push_back(v1);

    if (std::find(v.begin(), v.end(), v1) == v.end())
        QFAIL("1D vector not found.");
}

NestedVectorTest::Vector1D NestedVectorTest::generate1DVector(
        NestedVectorTest::stored_type start_value, unsigned size) {
    Vector1D v;
    for (unsigned i = start_value; i < start_value+size; i++)
        v.push_back(i);
    return v;
}

void NestedVectorTest::testGenerate2DVector() {
    stored_type start_value = 0;
    unsigned size = 3;

    Vector2D v = generate2DVector(start_value, size);

    QVERIFY(v.size() == size);
    for (unsigned i = start_value; i < start_value+size*size; i += size) {
        QVERIFY(std::find(v.begin(), v.end(), generate1DVector(i, size)) != v.end());
    }

}

void NestedVectorTest::erase() {
    Vector2D v = generate2DVector();

    v.erase(v.begin());

    QVERIFY(std::find(v.begin(), v.end(), generate1DVector(0, 3)) == v.end());
    QVERIFY(v.size() == 2);
}

NestedVectorTest::Vector2D NestedVectorTest::generate2DVector(
        NestedVectorTest::stored_type start_value, unsigned size) {
    Vector2D v;
    for (unsigned i = start_value; i < start_value+size*size; i += size) {
        v.push_back(generate1DVector(i, size));
    }

    return v;
}

void NestedVectorTest::resize() {
    Vector2D v;
    QVERIFY(v.size() == 0);

    v.resize(3, generate1DVector());

    QVERIFY(v.size() == 3);
    for (unsigned i = 0; i < 3; ++i)
        QVERIFY(v[i] == generate1DVector());
}
