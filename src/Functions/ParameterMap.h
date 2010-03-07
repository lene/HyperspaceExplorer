#ifndef PARAMETERMAP_H
#define PARAMETERMAP_H

#include <iostream>
#include <map>
#include <sstream>

#include "FunctionParameter.h"
#include "Log.h"

/// A class to store and manage FunctionParameter s
/**
    \author Helge Preuss <lene.preuss@gmail.com>
    \ingroup FunctionParameterGroup
*/
class ParameterMap : public std::map<std::string, FunctionParameter *> {
public:

    class NonexistentParameterAccessed: public std::invalid_argument {
    public:
      NonexistentParameterAccessed(const std::string &which):
        std::invalid_argument("Tried to access parameter \""+which+"\"") { }
    };
    
    ParameterMap(): std::map<std::string, FunctionParameter *> () { }
    
    /// Create a ParameterMap containing one parameter
    template<typename T1> ParameterMap(const std::string &name,
                                       const T1 &value):
            std::map<std::string, FunctionParameter *> () {
        insertByValue(name, value);
    }
    
    ~ParameterMap() { }
    
    /// Insert a parameter with a name and an actual value
    template <typename T> void insertByValue(const std::string name,
                                             const T &value) {
      insert(
        std::make_pair(
          name,
          ParameterFactory::Instance().createParameterWithValue(name, value)));
        }
        
    /// Insert a parameter with a name and a default value
    template <typename T> void insertByDefault(const std::string name,
                                               const T &defaultValue) {
      insert(
        std::make_pair(
          name,
          ParameterFactory::Instance().createParameterWithDefault(name, defaultValue)));
        }

    FunctionParameter *operator[](const std::string &name);
    
    FunctionParameterValueBase *get(const std::string &name) {
      return (*this)[name]->value();
    }

    template <typename T> void set(const std::string &name, const T &value) {
      ParameterMap::iterator it = findOrThrow(name);
      it->second->setValue(value.toString());
    }
    
    /// return a string representation for debugging purposes
    std::string print() const;
    
    ParameterMap::iterator findOrThrow(const std::string &name);
    
};

template <> void ParameterMap::set(const std::string &name, const double &value);
template <> void ParameterMap::set(const std::string &name, const unsigned &value);
template <> void ParameterMap::set(const std::string &name, const int &value);
template <> void ParameterMap::set(const std::string &name, const std::string &value);

#endif
