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

    /// Exception that is thrown when a key is accessed that is not present in a ParameterMap.
    class NonexistentParameterAccessed: public std::invalid_argument {
    public:
      /// Constructs the exception.
      /** \param which Key to the parameter that was attempted to read or write.
       *  \param map The ParameterMap on which \p which was attemped to access.
       */
      NonexistentParameterAccessed(const std::string &which, const ParameterMap &map):
        std::invalid_argument("Tried to access parameter \""+which+"\" in ParameterMap "+map.toString()) { }
    };
    
    ParameterMap(): std::map<std::string, FunctionParameter *> () { }
    
    /// Create a ParameterMap containing one parameter
    template<typename T> ParameterMap(const std::string &name,
                                      const T &value):
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
          TheFunctionParameterFactory::Instance().createParameterWithValue(name, value)));
        }
        
    /// Insert a parameter with a name and a default value
    template <typename T> void insertByDefault(const std::string name,
                                               const T &defaultValue) {
      insert(
        std::make_pair(
          name,
          TheFunctionParameterFactory::Instance().createParameterWithDefault(name, defaultValue)));
        }

    /// \return The FunctionParameter * that is stored under the key \p name.
    FunctionParameter *getParameter(const std::string &name);
    
    /// \return The FunctionParameterValue * that is stored under the key \p name.
    FunctionParameterValueBase *getValue(const std::string &name);

    /// Sets the value of the parameter stored under the key \p name to \p value.
    /** \param T The type of parameter that is to be changed. \p T must be either
     *    of a class that has the toString() method, or one of the primitive types
     *    for which explicit specializations are listed below.
     *  \param name Key of the parameter that is to be set.
     *  \param value The new value for parameter \p name.
     *  \throw NonexistentParameterAccessed if \p name is not a key. 
     */
    template <typename T> void set(const std::string &name, const T &value) {
      getParameter(name)->setValue(value.toString());
    }
    
    /// \return String representation for debugging purposes
    std::string toString() const;
    
  private:
    /// \return iterator pointing to the element with key \p name.
    ParameterMap::iterator findOrThrow(const std::string &name);
    
};

/// Specialization for type \c double, which has no toString() method.
template <> void ParameterMap::set(const std::string &name, const double &value);
/// Specialization for type \c unsigned, which has no toString() method.
template <> void ParameterMap::set(const std::string &name, const unsigned &value);
/// Specialization for type \c int, which has no toString() method.
template <> void ParameterMap::set(const std::string &name, const int &value);
/// Specialization for type \c std::string, which has no toString() method.
template <> void ParameterMap::set(const std::string &name, const std::string &value);

#endif
