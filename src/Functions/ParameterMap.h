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
    /// return a string representation for debugging purposes
    std::string print() const {
        std::ostringstream o;
        o << "[\n";
        for (std::map<std::string, FunctionParameter *>::const_iterator i = begin();
             i != end(); ++i) {
                o << "    " << i->first << ": \t"
                  << i->second->getName() << " = ";
                // try casting to every known type, only print if cast succeeds
                try {
                    o << "(double)" << double(*(i->second)) << std::endl;
                }  catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
                try {
                    o << "(unsigned)" << unsigned(*(i->second)) << std::endl;
                }  catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
                try {
                    o << "(int)" << int(*(i->second)) << std::endl;
                }  catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
                try {
                    o << "(string)" << std::string(*(i->second)) << std::endl;
                }  catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
        }
        o << "]" << std::endl << std::ends;

        return o.str();
    }

};

#endif
