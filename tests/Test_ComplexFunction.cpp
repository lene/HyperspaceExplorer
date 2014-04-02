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

