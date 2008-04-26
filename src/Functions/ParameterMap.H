#ifndef PARAMETERMAP_H
#define PARAMETERMAP_H

#include <iostream>
#include <map>
#include <sstream>

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
    std::string print() const {
        std::ostringstream o;
        o << "[\n";
        for (std::map<std::string, FunctionParameter *>::const_iterator i = begin(); i != end(); ++i) {
            o << "    " << i->first << ": \t"
              << i->second->getName() << " = ";
            o << double(*(i->second));
            o << "\n";
        }
        o << "]\n" << std::ends;
        return o.str();
    }

};

#endif
