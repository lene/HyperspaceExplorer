#include "FunctionFactory.h"
#include "ColorManager.h"

#include <tr1/memory>

bool FunctionFactory::registerFunction(CreateFunctionCallback creator) {

    std::tr1::shared_ptr<Function> theFunction(creator());

    std::string functionName = theFunction->getFunctionName();

    return callbacks.insert(CallbackMap::value_type(functionName, creator)).second;
}


bool FunctionFactory::unregisterFunction(const std::string &name) {
    return callbacks.erase(name) == 1;
}


Function *FunctionFactory::createFunction(const std::string &name) {
    std::cerr << "FunctionFactory::createFunction(" << name << ")\n";
    CallbackMap::const_iterator i = callbacks.find(name);
    if (i == callbacks.end()) throw BadFunctionException(name);
    return (i->second)();
}

std::vector< std::string > FunctionFactory::listFunctions() {
    std::vector<std::string> list;
    for (CallbackMap::const_iterator i = callbacks.begin(); i != callbacks.end(); ++i) {
        list.push_back(i->first);
    }
    return list;
}
