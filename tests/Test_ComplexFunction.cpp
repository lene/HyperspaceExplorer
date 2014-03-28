/* 
 * File:   Test_ComplexFunction.cpp
 * Author: lene
 * 
 * Created on March 28, 2014, 7:54 PM
 */

#include "Test_ComplexFunction.h"

#include "Surface/ComplexFunction.h"

void Test_ComplexFunction::t_z2() {
  performSurfaceTest<z2, 0>("z2");
}
void Test_ComplexFunction::t_z3() {
  performSurfaceTest<z3, 0>("z3");
}
void Test_ComplexFunction::t_zA() {
  performSurfaceTest<zA, 1>("zA");
}
void Test_ComplexFunction::t_ez() {
  performSurfaceTest<ez, 1>("e^a*z");
}
void Test_ComplexFunction::t_emz2() {
  performSurfaceTest<emz2, 1>("emz2");
}
void Test_ComplexFunction::t_zm1() {
  performSurfaceTest<zm1, 0>("zm1");
}
void Test_ComplexFunction::t_zm2() {
  performSurfaceTest<zm2, 0>("zm2");
}
void Test_ComplexFunction::t_sqrtz() {
  performSurfaceTest<sqrtz, 0>("sqrtz");
}
void Test_ComplexFunction::t_lnz() {
  performSurfaceTest<lnz, 0>("lnz");
}
void Test_ComplexFunction::t_sinz() {
  performSurfaceTest<sinz, 0>("sinz");
}
void Test_ComplexFunction::t_cosz() {
  performSurfaceTest<cosz, 0>("cosz");
}
void Test_ComplexFunction::t_sinhz() {
  performSurfaceTest<sinhz, 0>("sinhz");
}
void Test_ComplexFunction::t_coshz() {
  performSurfaceTest<coshz, 0>("coshz");
}
void Test_ComplexFunction::t_tanz() {
  performSurfaceTest<tanz, 0>("tanz");
}

