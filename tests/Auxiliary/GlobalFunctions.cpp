/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#include "GlobalFunctions.h"

#include "Vector.impl.h"

#include <QtTest/QtTest>
#include <QString>

using std::string;

QString comparisonString(double checked, double precondition, const QString &operation) {
  return QString::number(checked) + " " + operation + " " + QString::number(precondition);
}

QString comparisonString(const string &checked, const string &precondition, const string &operation) {
  return (checked + " " + operation + " " + precondition).c_str();
}

namespace UnitTests {

void test(bool condition, const QString &message) {
  QVERIFY2(
    condition,
    message.toAscii());
}

void test(bool condition, const std::string& message) {
  QVERIFY2(
    condition,
    message.c_str());
}

void testEqual(double checked, double precondition) {
  test(
    checked == precondition,
    comparisonString(checked, precondition, "==")
  );
}

void testEqual(const std::string& checked, const std::string& precondition) {
  test(
    checked == precondition,
    comparisonString(checked, precondition, "==")
  );
}

template <unsigned D, typename NUM>
void testEqual(const VecMath::Vector<D, NUM> &checked,
               const VecMath::Vector<D, NUM> &precondition) {
  test(
    VecMath::sqnorm(checked-precondition) < EPSILON,
    checked.toString() + " == " + precondition.toString()
  );
}

void testGreaterEqual(double checked, double precondition) {
  test(
    checked >= precondition,
    comparisonString(checked, precondition, ">=")
  );
}

template <unsigned D, typename NUM>
void testNotEqual(const VecMath::Vector<D, NUM> &checked,
                  const VecMath::Vector<D, NUM> &precondition) {
  test(
    VecMath::sqnorm(checked-precondition) > EPSILON,
    checked.toString() + " != " + precondition.toString()
  );
}

template <typename Value, class Container> bool contains(const Container &container, 
                                                         const Value &value) {
  return std::find(container.begin(), container.end(), value) != container.end();
}

template <typename Value, class Container>
void testContains(const Container &container, const Value &value) {
  test(contains(container, value), 
       string("Container contains value"));
}

template <class Container>
void testContains(const Container &container, const std::string &value) {
  test(contains(container, value), 
       "Container contains \""+value+"\"");
}


/// Explicit instantiation
template void testEqual(const VecMath::Vector<4, double> &checked,
                        const VecMath::Vector<4, double> &precondition);
/// Explicit instantiation
template void testNotEqual(const VecMath::Vector<4, double> &checked,
                           const VecMath::Vector<4, double> &precondition);
/// Explicit instantiation
template void testContains(const std::vector<std::string> &container, 
                           const std::string &value);

}
