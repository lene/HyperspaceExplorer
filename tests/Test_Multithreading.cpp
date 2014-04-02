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

#include "Test_Multithreading.h"

#include "Multithreading.h"

#include "GlobalFunctions.h"

#include <iostream>

using namespace UnitTests;

int increase(int i) { return i+1; }

void Test_Multithreading::test_mapped() {
    std::vector<int> ints(CONTAINER_SIZE, 0);
    auto result = Multithreading::mapped(ints, increase);
    for (auto i: result) test(i == 1, "element of result set is not 1");
}

void Test_Multithreading::test_partitionedMap() {
    std::vector<int> ints(CONTAINER_SIZE, 0), result;
    Multithreading::partitionedMap(ints, result, increase);
    for (auto i: result) test(i == 1, "element of result set is not 1");
}

void Test_Multithreading::test_partitionedMapInPlace() {
    std::vector<int> ints(CONTAINER_SIZE, 0);
    Multithreading::partitionedMap(ints, increase);
    for (auto i: ints) test(i == 1, "element of result set is not 1");
}

void Test_Multithreading::test_partitionedMapped() {
    std::vector<int> ints(CONTAINER_SIZE, 0);
    auto result = Multithreading::partitionedMapped(ints, increase);
    for (auto i: result) test(i == 1, "element of result set is not 1");
}
