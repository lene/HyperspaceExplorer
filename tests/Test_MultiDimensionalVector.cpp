
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

void testForEach(unsigned &i) { i = 2; }

void Test_MultiDimensionalVector::for_each() {
  Vector2D v = generate2DVector();
  
  v.for_each(testForEach);
  
  for (unsigned i = 0; i < v.size(); ++i) {
    for (unsigned j = 0; j < v[i].size(); ++j) {
      QVERIFY(v[i][j] == 2);
    }
  }
}

unsigned sum_of_all_elements = 0;
void testForEachConst(const unsigned &i) { sum_of_all_elements += i; }

unsigned calculateSumForSize(unsigned size) {
  unsigned n = size*size;
  unsigned sum = 0;
  for (unsigned i = 0; i < n; ++i) sum += i;
  return sum;
}

void Test_MultiDimensionalVector::for_each_const() {
  Vector2D v = generate2DVector(0, 4);

  v.for_each(testForEachConst);
  
  QVERIFY(sum_of_all_elements == calculateSumForSize(4));
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
