#ifndef PARAMETERMAP_H
#define PARAMETERMAP_H

#include <iostream>
#include <map>

#include "FunctionParameter.H"
#include "Log.H"

/// A class to store and manage FunctionParameter s
/**
    \author Helge Preuss <scout@hyperspace-travel.de>
    \ingroup FunctionParameterGroup
*/
class ParameterMap : public std::map<std::string, FunctionParameter *> {
public:
    ParameterMap(): std::map<std::string, FunctionParameter *> () { }
    template<typename T1> ParameterMap(const std::string &_name1,
                                       const T1 &_value1):
            std::map<std::string, FunctionParameter *> () {
        SingletonLog::Instance() << "ParameterMap::ParameterMap(" << _name1
                                 << ", " << _value1 << ")\n";
        insertByValue(_name1, _value1);
    }
    ~ParameterMap() { }

    template <typename T> void insertByValue(const std::string _name,
                                             const T &_value) {
            insert(
                std::make_pair(_name,
                    ParameterFactory::Instance().
                            createParameterWithValue(_name, _value)));
        }
    template <typename T> void insertByDefault(const std::string _name,
                                               const T &_default) {
            insert(
                std::make_pair(_name,
                    ParameterFactory::Instance().
                            createParameterWithDefault(_name, _default)));
        }

};

#endif
