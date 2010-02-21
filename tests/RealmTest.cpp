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

#include "RealmTest.h"

#include "Rotopes/Realm.h"

#include <stdexcept>

std::vector<Realm> createUintVec();

void RealmTest::push_back() {
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

void RealmTest::add() {
    Realm realm;
    realm.push_back(1);

    realm.add(1);
    
    QVERIFY(realm.contains(2));
}

void RealmTest::clear() {
    Realm realm;
    realm.push_back(1);
    
    realm.clear();
    
    QVERIFY(realm.size() == 0);
    QVERIFY(realm.dimension() == 0);
}

void RealmTest::contains() {
    Realm containedRealm(createUintVec());
    Realm realm2D;
    realm2D.push_back(containedRealm);
    containedRealm.add(2);
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
    realm2D.add(4);
    realm3D.push_back(realm2D);
    
    QVERIFY(realm3D.dimension() == 3);
    
    QVERIFY(realm3D.contains(realm2D));

    QVERIFY(realm3D.contains(createUintVec()));
    QVERIFY(realm3D.contains(containedRealm));
    
    QVERIFY(realm3D.contains(1));
    QVERIFY(realm3D.contains(8));
    
}

void RealmTest::fromStdVector() {
    
    Realm fromUintVec(createUintVec());
    
    QVERIFY(fromUintVec.contains(1));
    QVERIFY(fromUintVec.contains(2));
    QVERIFY(fromUintVec.dimension() == 1);
}

void RealmTest::operatorUnsigned() {
    Realm realm(1);
    QVERIFY(unsigned(realm) == 1);
    Realm line(createUintVec());
    try {
        unsigned int_value = unsigned(line);
    } catch (std::logic_error e) {
        return;
    }
    QFAIL("expected logic_error");
}

void RealmTest::extrude() {
    Realm line(createUintVec());
    line = line.extrude(2);
    QVERIFY(line.dimension() == 2);
    QVERIFY(line.contains(4));
    QVERIFY(line.contains(3));
}

void RealmTest::taper() {
  Realm line(createUintVec());
  line.taper(3);
  QVERIFY(line.dimension() == 2);
  QVERIFY(line.contains(3));
}

void RealmTest::rotate() {
  Realm line(createUintVec());
  line.rotate(2, 2);
  QVERIFY(line.dimension() == 2);
  QVERIFY(line.contains(3));
  QVERIFY(line.contains(4));
  QVERIFY(line.contains(5));
  QVERIFY(line.contains(6));
}


std::vector<Realm> createUintVec() {
  std::vector<Realm> unsigneds;
  unsigneds.push_back(1);
  unsigneds.push_back(2);
  return unsigneds;
}