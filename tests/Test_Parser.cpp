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
#include "Statement.h"
#include "ExpectException.h"

using VecMath::Vector;
using std::vector;
using std::string;
using namespace UnitTests;
using namespace Script;

void Test_Parser::initTestCase() {
    view_ = new MockView(false);
    setGlobalView(view_);
}


void Test_Parser::test_createParserFromLines() {
    std::vector<std::string> create_hypercube_statements;
    create_hypercube_statements.push_back("object Tesseract");
    create_hypercube_statements.push_back("parameter double Size 1");
    create_hypercube_statements.push_back("start_animation");

    Parser parser(create_hypercube_statements);
    parser.setView(view_);
    
    test(parser.execute(), "parser executed statements");

    for (double x = -1.; x <= 1.; x += 2.)
        for (double y = -1.; y <= 1.; y += 2.)
            for (double z = -1.; z <= 1.; z += 2.)
                for (double w = -1.; w <= 1.; w += 2.)
                    checkVertexPresent(Vector<4>(x, y, z, w));
}

void Test_Parser::test_boolStatementWithColor() {
    Parser *parser = createEmptyParser();
    
    StatementFactory::createStatement(parser, "colors off")->execute();
    test(!view_->getColors(), "colors off");

    StatementFactory::createStatement(parser, "colors on")->execute();
    test(view_->getColors(), "colors on");
    
    StatementFactory::createStatement(parser, "colors 0")->execute();
    test(!view_->getColors(), "colors off");

    StatementFactory::createStatement(parser, "colors 1")->execute();
    test(view_->getColors(), "colors on");
    
    StatementFactory::createStatement(parser, "colors false")->execute();
    test(!view_->getColors(), "colors off");

    StatementFactory::createStatement(parser, "colors true")->execute();
    test(view_->getColors(), "colors on");
    
    StatementFactory::createStatement(parser, "colors nonsensical stuff")->execute();
    test(!view_->getColors(), "colors off");
}

void Test_Parser::test_badStatement() {
    Parser *parser = createEmptyParser();
    
    expectException<BadStatementException>(
        [&]() { StatementFactory::createStatement(parser, "hurglarglarblbaaah"); }
    );
}

void Test_Parser::test_statementsAreCaseSensitive() {
    Parser *parser = createEmptyParser();

    expectException<BadStatementException>(
        [&]() { StatementFactory::createStatement(parser, "Colors off")->execute(); }
    );
}

void Test_Parser::testObjectStatement() {

}

Script::Parser* Test_Parser::createEmptyParser() {
    vector<string> empty;
    Parser *parser = new Parser(empty);
    parser->setView(view_);
    return parser;
}
