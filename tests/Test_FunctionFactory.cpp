/*
Hyperspace Explorer - visualizing higher-dimensional geometry
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

#include "Test_FunctionFactory.h"

#include <vector>

using std::string;
using std::vector;

const std::string Test_FunctionFactory::TEST_FUNCTION_NAME = "Test_FunctionFactory";

Function *createTest() { return new Test_FunctionFactory::FunctionTestImplementation(); }

void Test_FunctionFactory::registerFunction() {
    TheFunctionFactory::Instance().registerFunction(createTest);

    vector<string> registeredFunctions = TheFunctionFactory::Instance().listFunctions();
    if (std::find(registeredFunctions.begin(), registeredFunctions.end(), TEST_FUNCTION_NAME) == registeredFunctions.end()) {
        QFAIL((TEST_FUNCTION_NAME+" not found in registeredFunctions").c_str());
    }
}

void Test_FunctionFactory::unregisterFunction() {

    TheFunctionFactory::Instance().registerFunction(createTest);

    TheFunctionFactory::Instance().unregisterFunction(TEST_FUNCTION_NAME);

    vector<string> registeredFunctions = TheFunctionFactory::Instance().listFunctions();
    if (std::find(registeredFunctions.begin(), registeredFunctions.end(), TEST_FUNCTION_NAME) != registeredFunctions.end()) {
        QFAIL((TEST_FUNCTION_NAME+" still found in registeredFunctions after a call to unregisterFunction()").c_str());
    }

    try {
        Function *f = TheFunctionFactory::Instance().createFunction(TEST_FUNCTION_NAME);
        QFAIL((TEST_FUNCTION_NAME+" not present in callback list, but it's still possible to create one").c_str());
    } catch (FunctionFactory::BadFunctionException &e) { }
}


void Test_FunctionFactory::createFunction(){

    TheFunctionFactory::Instance().registerFunction(createTest);

    Function *f = TheFunctionFactory::Instance().createFunction(TEST_FUNCTION_NAME);

    QVERIFY(dynamic_cast<Test_FunctionFactory::FunctionTestImplementation *>(f) == f);
}

/// Check whether adding another function increases the number of registered function by 1.
/** Kinda lame test, yeah. Everything else I can think of has been covered before, though. */
void Test_FunctionFactory::listFunctions() {

    TheFunctionFactory::Instance().unregisterFunction(TEST_FUNCTION_NAME);

    unsigned previousSize = TheFunctionFactory::Instance().listFunctions().size();

    TheFunctionFactory::Instance().registerFunction(createTest);

    QVERIFY(TheFunctionFactory::Instance().listFunctions().size() == previousSize+1);
}

void Test_FunctionFactory::printRegisteredFunctions() {
    vector<string> registeredFunctions = TheFunctionFactory::Instance().listFunctions();
    for (vector<string>::iterator i = registeredFunctions.begin(); i != registeredFunctions.end(); ++i) {
        qDebug() << i->c_str() << " ";
    }
}
