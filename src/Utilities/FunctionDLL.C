/* 
 * File:   FunctionDLL.C
 * Author: lene
 * 
 * Created on March 25, 2014, 9:01 PM
 */

#include "FunctionDLL.h"

#include <fstream>
#include <dlfcn.h>

FunctionDLL::FunctionDLL(): lib_name_(), handle_(), valid_(false), error_() { }

FunctionDLL::FunctionDLL(const std::string &lib_name): 
        lib_name_(lib_name), handle_(), valid_(false), error_() {
    Initialize(lib_name);
}

FunctionDLL::~FunctionDLL() {
    if (handle_) dlclose(handle_);
}
void *FunctionDLL::getSymbol(const std::string& symbol) {
    if (!valid_) return NULL;
    
    dlerror();    /* Clear any existing error */
    void *function = dlsym(handle_, symbol.c_str());
    char *error = dlerror();

    if (error != NULL) {
        error_ =  error;
        return NULL;
    }
    
    return function;
}

bool file_exists(const std::string& name) {
    std::ifstream f(name.c_str());
    bool exists =f.good();
    f.close();
    return exists;
}

void FunctionDLL::Initialize(const std::string& lib_name) {
    if (!file_exists(lib_name)) {
        error_ = "File does not exist: "+lib_name;
        return;
    }
    
    // double call to dlopen(). fuck if i know why this is sometimes necessary, but it is.
    dlopen(lib_name.c_str(), RTLD_LAZY);
    handle_ = dlopen(lib_name.c_str(), RTLD_LAZY);
    if (!handle_) {
        error_ = dlerror();
        return;
    }
    
    valid_ = true;
}
