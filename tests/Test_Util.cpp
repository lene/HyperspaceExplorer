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

#include "Test_Util.h"

#include "GlobalFunctions.h"

#include <sstream>

using namespace UnitTests;
using std::string;
using std::vector;


void Test_Util::find_in_vector() {
  vector<int> vec_int;
  vec_int.push_back(1);
  vec_int.push_back(2);
  vec_int.push_back(3);

  test(Util::find(1, vec_int) != vec_int.end(), "1 not found");
  test(Util::find(2, vec_int) != vec_int.end(), "2 not found");
  test(Util::find(3, vec_int) != vec_int.end(), "3 not found");

  test(Util::find(4, vec_int) == vec_int.end(), "4 found");

  vector<string> vec_str;
  vec_str.push_back("buh!");
 
  test(Util::find(string("buh!"), vec_str) != vec_str.end(), "buh! not found");

  test(Util::find(string("bah!"), vec_str) == vec_str.end(), "bah! found");

}

void Test_Util::itoa() {
  testEqual(Util::itoa(1), "1");
  testEqual(Util::itoa(-1), "-1");
}

void Test_Util::atoi() {
  testEqual(Util::atoi("1"), 1);
  testEqual(Util::atoi("-1"), -1);
  testEqual(Util::atoi("zero"), 0);
}

void Test_Util::ftoa() {
  testEqual(Util::ftoa(1.5), "1.5");
}

void Test_Util::atod() {
  testEqual(Util::atod(string("1.5")), 1.5);
}

void Test_Util::isPermutation() {
  test(Util::isPermutation(1, 0, 1, 0), "(1, 0) permutation of (1, 0)");
  test(Util::isPermutation(1, 0, 0, 1), "(0, 1) permutation of (1, 0)");
  test(!Util::isPermutation(1, 0, 1, 1), "(1, 1) not permutation of (1, 0)");
  test(!Util::isPermutation(1, 0, 1, 2), "(1, 1) not permutation of (1, 0)");
  test(Util::isPermutation(1, 2, 3, 1, 2, 3), "(1, 2, 3) permutation of (1, 2, 3)");
  test(Util::isPermutation(1, 2, 3, 1, 3, 2), "(1, 3, 2) permutation of (1, 2, 3)");
  test(!Util::isPermutation(1, 2, 3, 1, 1, 3), "(1, 1) not permutation of (1, 2, 3)");
  test(!Util::isPermutation(1, 2, 3, 1, 2, 4), "(1, 1) not permutation of (1, 2, 3)");
}

void Test_Util::trim() {
  testEqual(Util::trim(" text"), "text");
  testEqual(Util::trim("text "), "text");
  testEqual(Util::trim(" text "), "text");
  testEqual(Util::trim("text"), "text");
}

void Test_Util::explode() {
  string total = "one, two, three";
  vector<string> parts = Util::explode(",", total);

  testContains(parts, string("one"));
  testContains(parts, string(" two"));
  testContains(parts, string(" three"));

  parts = Util::explode(", ", total);
  testContains(parts, string("one"));
  testContains(parts, string("two"));
  testContains(parts, string("three"));
}
