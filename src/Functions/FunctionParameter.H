///
/// C++ Interface: FunctionParameter
///
/// Description:
///
///
/// @author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
/// \ingroup
///

#include <string>

class FunctionParameterBase {
    public:
        FunctionParameterBase(const std::string &_description = ""):
            description(_description) { }

        const std::string &getDescription() const { return description; }
        void setDescription(const std::string &_description) {
            description = _description;
        }
        /// cast to double is defined here because it is the most common case
        /** operator double() cannot be abstract because FunctionParameter
         *  objects are going to be stored in a std::map, and map doesn't allow
         *  abstact types as its mapped type. Thus, a dummy function.         */
        virtual operator double() { return 0.;};

    private:
        std::string description;
};

template <typename T> class FunctionParameter: public FunctionParameterBase {
    public:
        FunctionParameter<T>(const T &_defaultValue, const T &_value = 0.0,
                             const std::string &_description = ""):
                FunctionParameterBase(_description),
                defaultValue(_defaultValue), value(_value) {
                    if (!value) value = defaultValue;
                }

        virtual const T &getValue() const { return value; }
        virtual void setValue(const T &_value) { value = _value; }
        virtual const T &getDefaultValue() const { return defaultValue; }
        virtual void setDefaultValue(const T &_defaultValue) {
            defaultValue = _defaultValue;
        }
        virtual operator double() { return (double)value; }

    private:
        T defaultValue;
        T value;
};
