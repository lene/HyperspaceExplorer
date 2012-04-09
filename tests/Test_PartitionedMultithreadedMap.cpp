/*
    Hyperspace Explorer - visualizing higher-dimensional geometry
    Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

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

#include "Test_PartitionedMultithreadedMap.h"
#include "Multithreading.h"
#include "GlobalFunctions.h"

void verifyMultithreadedIsFaster(int elapsed_multi, int elapsed_single) {
    qDebug() << "Multithreaded: " << elapsed_multi << "ms, single threaded: " << elapsed_single << "ms";
    if (Util::isMultithreadedSensible()) {
        QVERIFY2(elapsed_multi < elapsed_single, "Multithreaded transform should be faster");    
    } else {
        if (elapsed_multi >= elapsed_single) {
            QSKIP(
                "Multithreaded slower than singlethreaded; that may be because you don't have enough processors",
                SkipSingle
            );
        }
    }
}

template <typename T> T duplicate(const T &operand) {
    return 2*operand;
}

template <typename T> void checkElementsAreDuplicated(const std::vector<T> &result, const std::vector<T> & initial) {

    UnitTests::testEqual(result.size(), initial.size());
    
    for(unsigned i = 0; i < initial.size(); ++i) {
        UnitTests::testEqual(result[i], 2*initial[i]);
    }
    
}

template <typename T> std::vector<T> Test_PartitionedMultithreadedMap::prepareTestData() {
    std::vector<T> test_data(min_size_for_multithreaded_advantage);
    for (unsigned i = 0; i < min_size_for_multithreaded_advantage; ++i) test_data[i] = i;
    return test_data;
}

template <typename T, typename Method> 
std::vector<T> Test_PartitionedMultithreadedMap::executeMap(const std::vector<T> & data, const Method &method) {
    return Multithreading::partitionedMapped(data, method);
}

template <typename T, typename Method> 
void Test_PartitionedMultithreadedMap::executeTestForMethod(const Method &method) {
    std::vector<T> test_data = prepareTestData<T>();

    checkElementsAreDuplicated(executeMap(test_data, method), test_data);
}

void Test_PartitionedMultithreadedMap::initTestCase() {
    
}

void Test_PartitionedMultithreadedMap::worksForFunctor() {
    executeTestForMethod< int, Duplicate<int> >(Duplicate<int>());
}

typedef int (*duplication_function)(const int &);

void Test_PartitionedMultithreadedMap::worksForFunction() {
    executeTestForMethod< int, duplication_function >(&(duplicate<int>));    
}

void Test_PartitionedMultithreadedMap::isFaster() {
    std::vector<int> test_data = prepareTestData<int>();
    TakeYourTime d;
    QTime t;
    t.start();
    executeMap(test_data, d);
    int elapsed_multi = t.elapsed();

    t.start();
    std::vector<int> results(test_data.size());
    for (unsigned i = 0; i < test_data.size(); ++i) {
        results[i] = d(test_data[i]);
    }
    int elapsed_single = t.elapsed();

    verifyMultithreadedIsFaster(elapsed_multi, elapsed_single);
}

void Test_PartitionedMultithreadedMap::mappingInPlace() {
    auto test_data = prepareTestData<int>();
    Multithreading::partitionedMap(test_data, Duplicate<int>());
    for (unsigned i = 0; i < test_data.size(); ++i) {
        UnitTests::testEqual(test_data[i], 2*i);
    }
}

void Test_PartitionedMultithreadedMap::mappingToArgument() {
    auto test_data = prepareTestData<int>();
    std::vector<int> output;
    Multithreading::partitionedMap(test_data, output, Duplicate<int>());
    UnitTests::testEqual(output.size(), test_data.size());
    for (unsigned i = 0; i < output.size(); ++i) {
        UnitTests::testEqual(output[i], 2*i);
    }
}
