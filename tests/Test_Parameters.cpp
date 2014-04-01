/* 
 * File:   Test_Parameters.cpp
 * Author: lene
 * 
 * Created on April 1, 2014, 5:01 PM
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
    test(i == INT_VALUE, std::string("retrieved stored value"));

    const double DOUBLE_VALUE = 2.0;
    const std::string DOUBLE_KEY = "two";
    map.insertByValue(DOUBLE_KEY, DOUBLE_VALUE);
    double d = map.getValue(DOUBLE_KEY)->toDouble();
    test(d == DOUBLE_VALUE, std::string("retrieved stored value"));

    const std::string STRING_VALUE = "three";
    const std::string STRING_KEY = "three";
    map.insertByValue(STRING_KEY, STRING_VALUE);
    std::string s = map.getValue(STRING_KEY)->toString();
    test(s == STRING_VALUE, std::string("retrieved stored value"));
}

void Test_Parameters::test_insertByDefault() {
    ParameterMap map;
    const int INT_VALUE = 1;
    const std::string INT_KEY = "one";
    map.insertByDefault(INT_KEY, INT_VALUE);
    int i = map.getValue(INT_KEY)->toInt();
    test(i == INT_VALUE, std::string("retrieved stored value"));

}

void Test_Parameters::test_changeValue() {
    ParameterMap map;
    const int OLD_INT_VALUE = 1;
    const int NEW_INT_VALUE = 2;
    const std::string INT_KEY = "one";
    map.insertByValue(INT_KEY, OLD_INT_VALUE);
    test(map.getValue(INT_KEY)->toInt() == OLD_INT_VALUE, std::string("retrieved value stored first"));

    map.set(INT_KEY, NEW_INT_VALUE);

    test(map.getValue(INT_KEY)->toInt() == NEW_INT_VALUE, std::string("retrieved new stored value"));
}

void Test_Parameters::test_nonexistentEntry() {
    ParameterMap map;
    expectException<ParameterMap::NonexistentParameterAccessed>(
        [&]() { auto parameter = map.getParameter("Help, I don't exist!"); }
    );
}

