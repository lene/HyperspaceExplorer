/* 
 * File:   FunctionDLL.C
 * Author: lene
 * 
 * Created on March 25, 2014, 9:01 PM
 */

#include "FunctionDLL.h"

#include <QFile>
#include <dlfcn.h>

FunctionDLL::FunctionDLL(): lib_name_(), handle_(), valid_(false), error_() { }

FunctionDLL::FunctionDLL(const std::string &lib_name): 
        lib_name_(lib_name), handle_(), valid_(false), error_() {
    Initialize(lib_name);
}

FunctionDLL::~FunctionDLL() {
    if (handle_) dlclose(handle_);
}
#include <iostream>
void *FunctionDLL::getSymbol(const std::string& symbol) {
    if (!valid_) return NULL;
    
    void *function = dlsym(handle_, symbol.c_str());
    if(!error_.empty()) std::cerr << error_ << std::endl;
    if (function == NULL) {
        const char *err = dlerror();
        std::cerr << err << std::endl;
        error_ =  err;
        valid_ = false;
    }
    
    return function;
}

void FunctionDLL::Initialize(const std::string& lib_name) {
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