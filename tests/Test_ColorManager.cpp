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

#include "Test_ColorManager.h"

#include "GlobalFunctions.h"

#include "ColorManager.h"
#include "LSystems/LSystem_old.h"

using namespace UnitTests;

void Test_ColorManager::initTestCase() {
}

void Test_ColorManager::testgetRegisteredColorManagers() {
    test (!ColMgrMgr::Instance().getRegisteredColorManagers().empty(), "found some registered color managers");
}

void Test_ColorManager::testisColorManagerSet() {
    test(!ColMgrMgr::Instance().isColorManagerSet(), "Color Manager should be unset initially");
    ColMgrMgr::Instance().setColorManager(new monochromeColorManager());
    test(ColMgrMgr::Instance().isColorManagerSet(), "Color Manager should be set now");
}

void Test_ColorManager::testFastxyz2RGBColorManager() {
    ColMgrMgr::Instance().setColorManager(new Fastxyz2RGBColorManager());
    
    // cannot test anything sensible really
}

void Test_ColorManager::testdepth2RGBColorManager() {
    ColMgrMgr::Instance().setColorManager(new depth2RGBColorManager());

    // cannot test anything sensible really
}

void Test_ColorManager::testmonochromeColorManager() {
    ColMgrMgr::Instance().setColorManager(new monochromeColorManager());
    test(ColMgrMgr::Instance().getColor(VecMath::Vector<4>(0., 0., 0., 0.)) == Color(1, 1, 1), "monochrome color manager should return white");
}
