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

#include "FunctionFactory.h"
#include "ColorManager.h"

#include <memory>

/** \param creator Callback function creating an object of the desired class
 *  \param parent_category Category the Function is under in the inheritance
 *    hierarchy and the menu structure
 *  \return true if registration was successful
 */
bool FunctionFactory::registerFunction(CreateFunctionCallback creator,
                                       const std::string &parent_category) {
    std::tr1::shared_ptr<Displayable> theFunction(creator());

    std::string functionName = theFunction->getFunctionName();

    bool insertSuccessful = callbacks.insert(CallbackMap::value_type(functionName, creator)).second;

    if (insertSuccessful) {
      DisplayableClass::findClass(parent_category).addDisplayable(functionName);
    }
    
    return insertSuccessful;
}

/** \param name Name of the class which isn't available for creation any
 *      more
 *  \return true if unregistration was successful
 */
bool FunctionFactory::unregisterFunction(const std::string &name) {
    return callbacks.erase(name) == 1;
}

/** \param name The class name of the created Function object
 *  \return a newly created object of class "name"
 */
Displayable *FunctionFactory::createFunction(const std::string &name) {
    auto i = callbacks.find(name);
    if (i == callbacks.end()) throw BadFunctionException(name);
    return (i->second)();
}

std::vector< std::string > FunctionFactory::listFunctions() {
    std::vector<std::string> list;
    for (auto i = callbacks.begin(); i != callbacks.end(); ++i) {
        list.push_back(i->first);
    }
    return list;
}
