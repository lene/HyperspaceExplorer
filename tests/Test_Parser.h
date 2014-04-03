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

#ifndef TEST_PARSER_H
#define	TEST_PARSER_H

#include <QtTest/QtTest>

#include "Auxiliary/MockView.h"

class MockView;

namespace Script {
    class Parser;
}

class Test_Parser: public QObject {

    Q_OBJECT
    
private slots:
    
    void initTestCase();
    
    void test_createParserFromLines();
    void test_boolStatementWithColor();

    void test_badStatement();
    void test_statementsAreCaseSensitive();

    void testObjectStatement();
    
private:
    
    Script::Parser *createEmptyParser();
    
    MockView *view_;
};

#endif	/* TEST_PARSER_H */

