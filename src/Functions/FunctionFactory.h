#ifndef FUNCTIONFACTORY_H
#define FUNCTIONFACTORY_H

#include "SingletonHolder.h"
#include "Function.h"

#include <map>

class Function;

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
        typedef Function *(*CreateFunctionCallback)();

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
        /// Registers a function creating a Function under the Function's class name
        /** \param creator Callback function creating an object of the desired class
         *  \return true if registration was successful                       */
        bool registerFunction(CreateFunctionCallback creator);

        /// Remove a Function class from the factory
        /** \param name Name of the class which isn't available for creation any
         *      more
         *  \return true if unregistration was successful                     */
        bool unregisterFunction(const std::string &name);

        /// Create an object derived from Function, given the name of its class
        /** \param name The class name of the created Function object
         *  \return a newly created object of class "name"                    */
        Function *createFunction(const std::string &name);

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
