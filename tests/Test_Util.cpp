/* 
 * File:   Test_Util.cpp
 * Author: lene
 * 
 * Created on May 13, 2011, 8:09 PM
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

  test(Util::find(1, vec_int) != vec_int.end(), string("1 not found"));
  test(Util::find(2, vec_int) != vec_int.end(), string("2 not found"));
  test(Util::find(3, vec_int) != vec_int.end(), string("3 not found"));

  test(Util::find(4, vec_int) == vec_int.end(), string("4 found"));

  vector<string> vec_str;
  vec_str.push_back("buh!");
 
  test(Util::find(string("buh!"), vec_str) != vec_str.end(), string("buh! not found"));

  test(Util::find(string("bah!"), vec_str) == vec_str.end(), string("bah! found"));

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
  test(Util::isPermutation(1, 0, 1, 0), string("(1, 0) permutation of (1, 0)"));
  test(Util::isPermutation(1, 0, 0, 1), string("(0, 1) permutation of (1, 0)"));
  test(!Util::isPermutation(1, 0, 1, 1), string("(1, 1) not permutation of (1, 0)"));
  test(!Util::isPermutation(1, 0, 1, 2), string("(1, 1) not permutation of (1, 0)"));
  test(Util::isPermutation(1, 2, 3, 1, 2, 3), string("(1, 2, 3) permutation of (1, 2, 3)"));
  test(Util::isPermutation(1, 2, 3, 1, 3, 2), string("(1, 3, 2) permutation of (1, 2, 3)"));
  test(!Util::isPermutation(1, 2, 3, 1, 1, 3), string("(1, 1) not permutation of (1, 2, 3)"));
  test(!Util::isPermutation(1, 2, 3, 1, 2, 4), string("(1, 1) not permutation of (1, 2, 3)"));
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
