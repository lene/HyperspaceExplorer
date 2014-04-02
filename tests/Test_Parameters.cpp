/*
 * Hyperspace Explorer - visualizing higher-dimensional geometry
 * Copyright (C) 2011  Lene Preuss <lene.preuss@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "Test_Parameters.h"

#include "GlobalFunctions.h"
#include "ExpectException.h"

using namespace UnitTests;

void Test_Parameters::test_insertAndRetrieve() {
    ParameterMap map;
    const int INT_VALUE = 1;
    const std::string INT_KEY = "one";
    map.insertByValue(INT_KEY, INT_VALUE);
    int i = map.getValue(INT_KEY)->toInt();
    test(i == INT_VALUE, "retrieved stored value");

    const double DOUBLE_VALUE = 2.0;
    const std::string DOUBLE_KEY = "two";
    map.insertByValue(DOUBLE_KEY, DOUBLE_VALUE);
    double d = map.getValue(DOUBLE_KEY)->toDouble();
    test(d == DOUBLE_VALUE, "retrieved stored value");

    const std::string STRING_VALUE = "three";
    const std::string STRING_KEY = "three";
    map.insertByValue(STRING_KEY, STRING_VALUE);
    std::string s = map.getValue(STRING_KEY)->toString();
    test(s == STRING_VALUE, "retrieved stored value");
}

void Test_Parameters::test_insertByDefault() {
    ParameterMap map;
    const int INT_VALUE = 1;
    const std::string INT_KEY = "one";
    map.insertByDefault(INT_KEY, INT_VALUE);
    int i = map.getValue(INT_KEY)->toInt();
    test(i == INT_VALUE, "retrieved stored value");

}

void Test_Parameters::test_changeValue() {
    ParameterMap map;
    const int OLD_INT_VALUE = 1;
    const int NEW_INT_VALUE = 2;
    const std::string INT_KEY = "one";
    map.insertByValue(INT_KEY, OLD_INT_VALUE);
    test(map.getValue(INT_KEY)->toInt() == OLD_INT_VALUE, "retrieved value stored first");

    map.set(INT_KEY, NEW_INT_VALUE);

    test(map.getValue(INT_KEY)->toInt() == NEW_INT_VALUE, "retrieved new stored value");
}

void Test_Parameters::test_nonexistentEntry() {
    ParameterMap map;
    expectException<ParameterMap::NonexistentParameterAccessed>(
        [&]() { auto parameter = map.getParameter("Help, I don't exist!"); }
    );
}

