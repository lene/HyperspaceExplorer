/*

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

#include "Test_Realm.h"

#include "Rotopes/Realm.h"

#include <stdexcept>

std::vector<Realm> createUintVec();

void Test_Realm::push_back() {
    Realm realm;
    realm.push_back(1);
    realm.push_back(2);

    QVERIFY(realm.contains(1));
    QVERIFY(realm.contains(2));
    QVERIFY(realm.dimension() == 1);
    
    try {
        realm.push_back(realm);
    } catch (std::invalid_argument e) {
        return;
    }
    QFAIL("Expected invalid_argument");
}

void Test_Realm::add() {
    Realm realm;
    realm.push_back(1);

    realm.addOffset(1);
    
    QVERIFY(realm.contains(2));
}

void Test_Realm::clear() {
    Realm realm;
    realm.push_back(1);
    
    realm.clear();
    
    QVERIFY(realm.size() == 0);
    QVERIFY(realm.dimension() == 0);
}

void Test_Realm::contains() {
    Realm containedRealm(createUintVec());
    Realm realm2D;
    realm2D.push_back(containedRealm);
    containedRealm.addOffset(2);
    realm2D.push_back(containedRealm);
    
    QVERIFY(realm2D.dimension() == 2);

    QVERIFY(realm2D.contains(createUintVec()));
    QVERIFY(realm2D.contains(containedRealm));
    
    QVERIFY(realm2D.contains(1));
    QVERIFY(realm2D.contains(2));
    QVERIFY(realm2D.contains(3));
    QVERIFY(realm2D.contains(4));
    
    Realm realm3D;
    realm3D.push_back(realm2D);
    realm2D.addOffset(4);
    realm3D.push_back(realm2D);
    
    QVERIFY(realm3D.dimension() == 3);
    
    QVERIFY(realm3D.contains(realm2D));

    QVERIFY(realm3D.contains(createUintVec()));
    QVERIFY(realm3D.contains(containedRealm));
    
    QVERIFY(realm3D.contains(1));
    QVERIFY(realm3D.contains(8));
    
}

void Test_Realm::fromStdVector() {
    
    Realm fromUintVec(createUintVec());
    
    QVERIFY(fromUintVec.contains(1));
    QVERIFY(fromUintVec.contains(2));
    QVERIFY(fromUintVec.dimension() == 1);
}

void Test_Realm::toIndex() {
    Realm realm(1);
    QVERIFY(realm.toIndex() == 1);
    Realm line(createUintVec());
    try {
        unsigned int_value = line.toIndex();
    } catch (std::logic_error e) {
        return;
    }
    QFAIL("expected logic_error");
}

void Test_Realm::extrude() {
    Realm line(createUintVec());
    line = line.extruded(2);
    QVERIFY(line.dimension() == 2);
    QVERIFY(line.contains(4));
    QVERIFY(line.contains(3));
}

void Test_Realm::taper() {
  Realm line(createUintVec());
  line = line.tapered(3);
  QVERIFY(line.dimension() == 2);
  QVERIFY(line.contains(3));
}

void Test_Realm::rotate() {
  Realm line(createUintVec());
  line = line.rotated(2, 2);
  QVERIFY(line.dimension() == 2);
  QVERIFY(line.contains(3));
  QVERIFY(line.contains(4));
  QVERIFY(line.contains(5));
  QVERIFY(line.contains(6));
}

void Test_Realm::toString() {
  Realm fromUintVec(createUintVec());
  std::string stringRepresentation = fromUintVec.toString();
  
  QVERIFY(stringRepresentation.find("[1]") != std::string::npos);
  for (std::vector<Realm>::const_iterator it = fromUintVec.cbegin(); it != fromUintVec.cend(); ++ it) {
    QVERIFY(stringRepresentation.find(QString::number(it->toIndex()).toStdString()) != std::string::npos);
  }
  
  Realm realm2D;
  realm2D.push_back(fromUintVec);
  realm2D.push_back(fromUintVec);
  
  stringRepresentation = realm2D.toString();
  QVERIFY(stringRepresentation.find("[2]") != std::string::npos);
}

void Test_Realm::merge() {
  Realm fromUintVec(createUintVec());
  fromUintVec.merge(createUintVec());
  
  QVERIFY(fromUintVec.dimension() == 1);
  QVERIFY(fromUintVec.size() == 4);
}

std::vector<Realm> createUintVec() {
  std::vector<Realm> unsigneds;
  unsigneds.push_back(1);
  unsigneds.push_back(2);
  return unsigneds;
}