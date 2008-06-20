#ifndef FUNCTIONFACTORY_H
#define FUNCTIONFACTORY_H

#include "SingletonHolder.H"
#include "Function.H"

/// Factory class creating Function objects given the name of their class
/** The factory is instantiated as singleton in the variable (in fact, class)
 *  TheFunctionFactory.
 *
 *  Classes which should be creatable by the FunctionFactory must add the
 *  following (exemplary) code after their declaration in the header file:
 *  \code
 *  namespace {
 *      Function *createHypercube() { return new Hypercube(); }
 *      const bool registered = TheFunctionFactory::Instance().registerFunction("Hypercube", createHypercube);
 *  }
 *  \endcode
 *  Objects are created with, e.g.:
 *  \code
 *  Function *f = TheFunctionFactory::Instance().createFunction("Hypercube");
 *  \endcode
 * \author Helge Preuss <scout@hyperspace-travel.de>                          */
class FunctionFactory {

    public:
        /// callback function generating a Function and returning a Function*
        typedef Function *(*CreateFunctionCallback)();

        /// Thrown by createFunction() when \p name does not map to a function.
        class BadFunctionException: public std::runtime_error {
            public:
                BadFunctionException(const std::string &what):
                    std::runtime_error(what) { }
        };

    private:
        /// stores a creator function with a string containing the class name
        typedef std::map<std::string, CreateFunctionCallback> CallbackMap;

    public:
        /// Registers a function creating a Function under the Function's class name
        /** \param name The class name of the created Function object
         *  \param creator Callback function creating an object of the desired class
         *  \return true if registration was successful                       */
        bool registerFunction(const std::string &name, CreateFunctionCallback creator);

        /// Remove a Function class from the factory
        /** \param name Name of the class which isn't available for creation any more
         *  \return true if unregistration was successful                     */
        bool unregisterFunction(const std::string &name);

        /// Create an object derived from Function, given the name of its class
        /** \param name The class name of the created Function object
         *  \return a newly created object of class "name"                    */
        Function *createFunction(const std::string &name);

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
