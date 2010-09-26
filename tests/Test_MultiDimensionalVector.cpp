
#include "Test_MultiDimensionalVector.h"

#include "MultiDimensionalVector.impl.h"

#include <algorithm>

using VecMath::MultiDimensionalVector;

void Test_MultiDimensionalVector::push_back_1D() {
    Test_MultiDimensionalVector::Vector1D v;

    v.push_back(1);

    if (std::find(v.begin(), v.end(), 1) == v.end())
        QFAIL("1 not found.");
}

void Test_MultiDimensionalVector::push_back_2D() {
    Vector2D v;
    Vector1D v1 = generate1DVector();

    v.push_back(v1);

    if (std::find(v.begin(), v.end(), v1) == v.end())
        QFAIL("1D vector not found.");
}

Test_MultiDimensionalVector::Vector1D Test_MultiDimensionalVector::generate1DVector(
        Test_MultiDimensionalVector::stored_type start_value, unsigned size) {
    Vector1D v;
    for (unsigned i = start_value; i < start_value+size; i++)
        v.push_back(i);
    return v;
}

void Test_MultiDimensionalVector::testGenerate2DVector() {
    stored_type start_value = 0;
    unsigned size = 3;

    Vector2D v = generate2DVector(start_value, size);

    QVERIFY(v.size() == size);
    for (unsigned i = start_value; i < start_value+size*size; i += size) {
        QVERIFY(std::find(v.begin(), v.end(), generate1DVector(i, size)) != v.end());
    }

}

void Test_MultiDimensionalVector::erase() {
    Vector2D v = generate2DVector();

    v.erase(v.begin());

    QVERIFY(std::find(v.begin(), v.end(), generate1DVector(0, 3)) == v.end());
    QVERIFY(v.size() == 2);
}

Test_MultiDimensionalVector::Vector2D Test_MultiDimensionalVector::generate2DVector(
        Test_MultiDimensionalVector::stored_type start_value, unsigned size) {
    Vector2D v;
    for (unsigned i = start_value; i < start_value+size*size; i += size) {
        v.push_back(generate1DVector(i, size));
    }

    return v;
}

void Test_MultiDimensionalVector::resize() {
    Vector2D v;
    QVERIFY(v.size() == 0);

    v.resize(3, generate1DVector());

    QVERIFY(v.size() == 3);
    for (unsigned i = 0; i < 3; ++i)
        QVERIFY(v[i] == generate1DVector());
}
