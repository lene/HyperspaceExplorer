#include "FunctionFactory.H"

bool FunctionFactory::registerFunction(const std::string &name,
                                       CreateFunctionCallback creator) {
    return callbacks.insert(CallbackMap::value_type(name, creator)).second;
}


bool FunctionFactory::unregisterFunction(const std::string &name) {
    return callbacks.erase(name) == 1;
}


Function *FunctionFactory::createFunction(const std::string &name) {
    CallbackMap::const_iterator i = callbacks.find(name);
    if (i == callbacks.end()) throw BadFunctionException(name);
    return (i->second)();
}
