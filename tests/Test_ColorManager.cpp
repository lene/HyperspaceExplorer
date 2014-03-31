/* 
 * File:   Test_ColorManager.cpp
 * Author: lene
 * 
 * Created on March 31, 2014, 1:16 PM
 */

#include "Test_ColorManager.h"

#include "GlobalFunctions.h"

#include "ColorManager.h"
#include "LSystems/LSystem_old.h"

using namespace UnitTests;

void Test_ColorManager::initTestCase() {
}

void Test_ColorManager::testgetRegisteredColorManagers() {
    test (!ColMgrMgr::Instance().getRegisteredColorManagers().empty(), std::string("found some registered color managers"));
}

void Test_ColorManager::testisColorManagerSet() {
    test(!ColMgrMgr::Instance().isColorManagerSet(), std::string("Color Manager should be unset initially"));
    ColMgrMgr::Instance().setColorManager(new monochromeColorManager());
    test(ColMgrMgr::Instance().isColorManagerSet(), std::string("Color Manager should be set now"));
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
    test(ColMgrMgr::Instance().getColor(VecMath::Vector<4>(0., 0., 0., 0.)) == Color(1, 1, 1), std::string("monochrome color manager should return white"));
}
