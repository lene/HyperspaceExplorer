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

#ifndef TEST_MULTITHREADING_H
#define	TEST_MULTITHREADING_H

#include <QtTest/QtTest>

class Test_Multithreading: public QObject {
    
    Q_OBJECT
    
private slots:

    void test_mapped();
    void test_partitionedMap();
    void test_partitionedMapInPlace();
    void test_partitionedMapped();
    
private:
    
    const unsigned CONTAINER_SIZE = 1024;
    
};

#endif	/* TEST_MULTITHREADING_H */

