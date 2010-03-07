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
    template<typename T1> ParameterMap(const std::string &_name1,
                                       const T1 &_value1):
            std::map<std::string, FunctionParameter *> () {
        insertByValue(_name1, _value1);
    }
    
    ~ParameterMap() { }
    
    /// Insert a parameter with a name and an actual value
    template <typename T> void insertByValue(const std::string _name,
                                             const T &_value) {
        insert(
                std::make_pair(_name,
                    ParameterFactory::Instance().
                            createParameterWithValue(_name, _value)));
        }
        
    /// Insert a parameter with a name and a default value
    template <typename T> void insertByDefault(const std::string _name,
                                               const T &_default) {
            insert(
                std::make_pair(_name,
                    ParameterFactory::Instance().
                            createParameterWithDefault(_name, _default)));
        }

    FunctionParameter *operator[](const std::string &_name);

    /// return a string representation for debugging purposes
    std::string print() const;
};

#endif
