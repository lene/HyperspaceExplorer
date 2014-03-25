/* 
 * File:   FunctionDLL.C
 * Author: lene
 * 
 * Created on March 25, 2014, 9:01 PM
 */

#include "FunctionDLL.h"

#include <QFile>
#include <dlfcn.h>

FunctionDLL::FunctionDLL(const std::string &lib_name): 
        handle_(), valid_(false), error_() {
    if (!QFile::exists(lib_name.c_str())) {
        error_ = "File does not exist: "+lib_name;
        return;
    }

    handle_ = dlopen(lib_name.c_str(), RTLD_LAZY);
    if (!handle_) {
        error_ = dlerror();
        return;
    }
    
    valid_ = true;
}

FunctionDLL::~FunctionDLL() {
    dlclose(handle_);
}

void *FunctionDLL::getSymbol(const std::string& symbol) {
    void *function = dlsym(handle_, symbol.c_str());

    if (function == NULL) {
        error_ = dlerror();
        valid_ = false;
    }
    
    return function;
}
