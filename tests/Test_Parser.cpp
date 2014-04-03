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

#include "Test_Parser.h"
#include "GlobalFunctions.h"
#include "MockView.h"

#include "Parser.h"

using Script::Parser;
using VecMath::Vector;
using namespace UnitTests;

void Test_Parser::initTestCase() {
    create_hypercube_statements_.push_back("object Tesseract");
    create_hypercube_statements_.push_back("parameter double Size 1");
    create_hypercube_statements_.push_back("start_animation");
    view_ = new MockView(false);
    setGlobalView(view_);
}


void Test_Parser::test_createParserFromLines() {
    Parser parser(create_hypercube_statements_);
    parser.setView(view_);
    
    test(parser.execute(), "parser executed statements");

    for (double x = -1.; x <= 1.; x += 2.)
        for (double y = -1.; y <= 1.; y += 2.)
            for (double z = -1.; z <= 1.; z += 2.)
                for (double w = -1.; w <= 1.; w += 2.)
                    checkVertexPresent(Vector<4>(x, y, z, w));
}
