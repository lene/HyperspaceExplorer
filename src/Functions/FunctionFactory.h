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

/// Factory class creating Function objects given the name of their class
/** The factory is instantiated as singleton in the variable (in fact, class)
 *  TheFunctionFactory.
 *
 *  Classes which should be creatable by the FunctionFactory must add the
 *  following (exemplary) code after their declaration in the header file:
 *  \code
 *  namespace {
 *
 *      Function *createHypercube() {
 *          return new Hypercube();
 *      }
 *
 *      const bool registered =
 *          TheFunctionFactory::Instance().registerFunction("Hypercube",
 *                                                          createHypercube);
 *  }
 *  \endcode
 *  Of course, the name of the class and the description passed to
 *  FunctionFactory::registerFunction() must be changed. The name of the
 *  variable <tt>registered</tt> must be chosen to be unique in the anonymous
 *  namespace.

 *  Objects are created with, e.g.:
 *  \code
 *  Function *f = TheFunctionFactory::Instance().createFunction("Hypercube");
 *  \endcode
 * \author Helge Preuss <lene.preuss@gmail.com>                          */
class FunctionFactory {

    public:
        /// callback function generating a Function and returning a Function*
        typedef Displayable *(*CreateFunctionCallback)();

        /// Thrown by createFunction() when \p name does not map to a function.
        class BadFunctionException: public std::runtime_error {
            public:
                /// Create a BadFunctionException
                BadFunctionException(const std::string &what):
                    std::runtime_error("\""+what+"\" is not the name of a registered"
                        " Function") { }
        };

    private:
        /// stores a creator function with a string containing the class name
        typedef std::map<std::string, CreateFunctionCallback> CallbackMap;

    public:
      
        /// Registers a category under which menu entries to select Functions are shown.
        /** This menu structure follows the inheritance hierarchy of Function
         *  classes.
         *  \param category_name The name of the newly registered category.
         *  \param parent_category The parent category, if applicable.
         */
        bool registerCategory(const std::string &category_name, 
                              const std::string &parent_category);
        
        /// Registers a function creating a Function under the Function's class name
        /** \param creator Callback function creating an object of the desired class
         *  \param parent_category Category the Function is under in the inheritance
         *    hierarchy and the menu structure
         *  \return true if registration was successful                       */
        bool registerFunction(CreateFunctionCallback creator,
                              const std::string &parent_category);

        /// Remove a Function class from the factory
        /** \param name Name of the class which isn't available for creation any
         *      more
         *  \return true if unregistration was successful                     */
        bool unregisterFunction(const std::string &name);

        /// Create an object derived from Function, given the name of its class
        /** \param name The class name of the created Function object
         *  \return a newly created object of class "name"                    */
        Displayable *createFunction(const std::string &name);

        /// \todo implement me!
        std::vector<std::string> listFunctions();

    private:
        /** disabled default constructor */
        FunctionFactory(): callbacks() { }
        /** disabled copy constructor */
        FunctionFactory(const FunctionFactory &);
        /** disabled assignment operator */
        FunctionFactory &operator=(const FunctionFactory &);
        /** disabled destructor */
        ~FunctionFactory();

        CallbackMap callbacks;  ///< Stores the Function creators

    friend class Loki::CreateUsingNew<FunctionFactory>;
};

typedef Loki::SingletonHolder<FunctionFactory> TheFunctionFactory;

#endif
