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

void Test_Multithreading::test_mapped() {
    std::vector<int> ints(CONTAINER_SIZE, 0);
    auto result = Multithreading::mapped(ints, increase);
    for (auto i: result) test(i == 1, std::string("element of result set is not 1"));
}

void Test_Multithreading::test_partitionedMap() {
    std::vector<int> ints(CONTAINER_SIZE, 0), result;
    Multithreading::partitionedMap(ints, result, increase);
    for (auto i: result) test(i == 1, std::string("element of result set is not 1"));
}

void Test_Multithreading::test_partitionedMapInPlace() {
    std::vector<int> ints(CONTAINER_SIZE, 0);
    Multithreading::partitionedMap(ints, increase);
    for (auto i: ints) test(i == 1, std::string("element of result set is not 1"));
}

void Test_Multithreading::test_partitionedMapped() {
    std::vector<int> ints(CONTAINER_SIZE, 0);
    auto result = Multithreading::partitionedMapped(ints, increase);
    for (auto i: result) test(i == 1, std::string("element of result set is not 1"));
}
