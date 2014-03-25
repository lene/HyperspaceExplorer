/* 
 * File:   FunctionDLL.h
 * Author: lene
 *
 * Created on March 25, 2014, 9:01 PM
 */

#ifndef FUNCTIONDLL_H
#define	FUNCTIONDLL_H

#include <string>

class FunctionDLL {
public:
  
  FunctionDLL();
  FunctionDLL(const std::string &lib_name);
  virtual ~FunctionDLL();
    
  bool isValid() { return valid_; }
  std::string getError() { return lib_name_ + ": " + error_; }
    
  void *getSymbol(const std::string &symbol);
  
private:
  void Initialize(const std::string &lib_name);
    
  std::string lib_name_;
  void *handle_;
  bool valid_;
  std::string error_;
  
};

#endif	/* FUNCTIONDLL_H */

