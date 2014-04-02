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

#ifndef TEST_COLORMANAGER_H
#define	TEST_COLORMANAGER_H

#include <QtTest/QtTest>
class Test_ColorManager: public QObject {

    Q_OBJECT
    
private slots:
    
    void initTestCase();
    
    void testgetRegisteredColorManagers();
    void testisColorManagerSet();
    
    void testFastxyz2RGBColorManager();
    void testdepth2RGBColorManager();
    void testmonochromeColorManager();
    
};

#endif	/* TEST_COLORMANAGER_H */

