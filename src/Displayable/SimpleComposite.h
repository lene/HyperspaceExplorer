/*
 * Hyperspace Explorer - visualizing higher-dimensional geometry
 * Copyright (C) 2011  Lene Preuss <lene.preuss@gmail.com>
 *
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

#ifndef SIMPLECOMPOSITE_H
#define SIMPLECOMPOSITE_H

#define TEST_COMPOSITE_SCALING

#include <Composite.h>


/// A simple Composite object, consisting of two Hypercube s. Meant only to develop the idea.
class SimpleComposite : public Composite {

  public:

    SimpleComposite();

    virtual std::string getFunctionName() const;

};

namespace {
    Displayable *createSimpleComposite() { return new SimpleComposite; }
    const bool registeredSC = TheFunctionFactory::Instance().registerFunction(createSimpleComposite, "Object");
}

#endif // SIMPLECOMPOSITE_H
