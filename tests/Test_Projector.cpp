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

#include "Test_Projector.h"

#include "GlobalFunctions.h"
#include "Rotopes/Projector.h"
using namespace UnitTests;

void Test_Projector::testProject3Dto2D() {
    VecMath::Vector<3> original(1., 0., 0.);
    std::vector<VecMath::Vector<3>> originals(1, original);
    Projector<3, 2> projector;
    VecMath::Vector<2> projected = projector(originals, 2., 4.).front();
    test(projected == VecMath::Vector<2>(0.5, 0.), "projected value wrong");
}

void Test_Projector::testProject4Dto2D() {
    VecMath::Vector<4> original(1., 0., 0., 0.);
    std::vector<VecMath::Vector<4>> originals(1, original);
    Projector<4, 2> projector;
    VecMath::Vector<2> projected = projector(originals, 2., 4.).front();
    test(projected == VecMath::Vector<2>(0.25, 0.), "projected value wrong");
}

void Test_Projector::testProject2Dto2D() {
    VecMath::Vector<2> original(1., 0.);
    std::vector<VecMath::Vector<2>> originals(1, original);
    Projector<2, 2> projector;
    VecMath::Vector<2> projected = projector(originals, 2., 4.).front();
    test(projected == original, "projected value wrong");
}

void Test_Projector::testProjectSingleVertex() {
    VecMath::Vector<3> original(1., 0., 0.);
    Projector<3, 2> projector;
    VecMath::Vector<2> projected = projector(original, 2., 4.);
    test(projected == VecMath::Vector<2>(0.5, 0.), "projected value wrong");
}

