/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
    Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

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

#ifndef REALMTEST_H
#define REALMTEST_H

#include <QtTest/QtTest>

/// Unit tests for class Realm
class Test_Realm: public QObject {
  
    Q_OBJECT

private slots:

    void push_back();
    void add();
    void clear();
    void contains();
    void fromStdVector();
    void toIndex();
    void toString();
    void merge();
    
    void extrude();
    void taper();
    void rotate();
    
    
};

#endif // REALMTEST_H
