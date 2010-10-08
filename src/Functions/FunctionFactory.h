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

#ifndef FUNCTIONFACTORY_H
#define FUNCTIONFACTORY_H

#include "SingletonHolder.h"
#include "Displayable.h"

#include <map>

class Displayable;

/// Factory class creating Displayable objects given the name of their class
/** The factory is instantiated as singleton in the variable (in fact, class)
 *  TheFunctionFactory.
 *
 *  Classes which should be creatable by the FunctionFactory must add the
 *  following (exemplary) code after their declaration in the header file:
 *  \code
 *  namespace {
 *
 *      Displayable *createHypercube() {
 *          return new Hypercube();
 *      }
 *
 *      const bool registered =
 *          TheFunctionFactory::Instance().registerFunction(createHypercube,
 *                                                          "Hypercube");
 *  }
 *  \endcode
 *  Of course, the name of the class and the description passed to
 *  FunctionFactory::registerFunction() must be changed. The name of the
 *  variable <tt>registered</tt> must be chosen to be unique in the anonymous
 *  namespace.

 *  Objects are created with, e.g.:
 *  \code
 *  Displayable *f = TheFunctionFactory::Instance().createFunction("Hypercube");
 *  \endcode
 * \author Helge Preuss <lene.preuss@gmail.com>                          */
class FunctionFactory {

  public:

    /// callback function generating a Function and returning a Function*
    typedef Displayable *(*CreateFunctionCallback)();

    /// Thrown by createFunction() when \p name does not map to a function.
    struct BadFunctionException: public std::runtime_error {
      /// Create a BadFunctionException
      BadFunctionException(const std::string &what):
        std::runtime_error("\""+what+"\" is not the name of a registered Function") { }
    };

  private:

    /// stores a creator function with a string containing the class name
    typedef std::map<std::string, CreateFunctionCallback> CallbackMap;

  public:

    /// Registers a function creating a Function under the Function's class name
    bool registerFunction(CreateFunctionCallback creator,
                          const std::string &parent_category);

    /// Remove a Function class from the factory
    bool unregisterFunction(const std::string &name);

    /// Create an object derived from Function, given the name of its class
    Displayable *createFunction(const std::string &name);

    /// Return the names of the registered Displayable classes as a std::vector<std::string>
    std::vector<std::string> listFunctions();

  private:

    /// disabled default constructor
    FunctionFactory(): callbacks() { }
    /// disabled copy constructor
    FunctionFactory(const FunctionFactory &);
    /// disabled assignment operator
    FunctionFactory &operator=(const FunctionFactory &);
    /// disabled destructor
    ~FunctionFactory();

    CallbackMap callbacks;  ///< Stores the Function creators

  friend class Loki::CreateUsingNew<FunctionFactory>;

};

typedef Loki::SingletonHolder<FunctionFactory> TheFunctionFactory;

#endif
