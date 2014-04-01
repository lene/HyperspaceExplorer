/* 
 * File:   Test_Multithreading.cpp
 * Author: lene
 * 
 * Created on April 1, 2014, 12:59 PM
 */

#include "Test_Multithreading.h"

#include "Multithreading.h"

#include "GlobalFunctions.h"

#include <iostream>

using namespace UnitTests;

int increase(int i) { return i+1; }

void Test_Multithreading::test_mappedVector() {
    std::vector<int> ints(CONTAINER_SIZE, 0);
    auto result = Multithreading::mapped(ints, increase);
    for (auto i: result) test(i == 1, std::string("element of result set is not 1"));
}

