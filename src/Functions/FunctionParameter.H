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

#include "SingletonHolder.H"

class FunctionParameterValueBase {
    public:
        /* It seems I have to declare the getters and setters for every type of
        derived classes that will be instantiated. PITA.
        what's worse, i have to define no-ops as default implementation. that
        totally breaks type-safety during compilation.                         */
        virtual const double &getValue() const { static double x = 0; return x; }
        //  "templates may not be virtual". blah.
        virtual void setValue(const double &) { }
        virtual operator double() = 0;
};

template <typename T> class FunctionParameterValue:
        public FunctionParameterValueBase {
    public:
        FunctionParameterValue<T>(const T &_value): value(_value) { }

        virtual const T &getValue() const { return value; }
        virtual void setValue(const T &_value) { value = _value; }
        virtual operator double() { return (double)value; }

    private:
        T value;
};

class FunctionParameter {
    public:
        FunctionParameter(const std::string &_name,
                          const std::string &_description = ""):
            pImpl(new Impl(_name, _description)) {}
        ~FunctionParameter() { delete pImpl; }

        const std::string &getName() const { return pImpl->name; }
        void setName(const std::string &_name) { pImpl->name = _name; }
        const std::string &getDescription() const { return pImpl->description; }
        void setDescription(const std::string &_description) {
            pImpl->description = _description;
        }
        operator double() { return (double)(*(pImpl->value));}
        template<typename T> void setValue(FunctionParameterValue<T> *_value) {
            if (!pImpl->value) delete pImpl->value;
            pImpl->value = _value;
        }
        const double &getValue() { return pImpl->value->getValue(); }

        const double &getDefaultValue() const {
            return pImpl->defaultValue->getValue();
        }
        template<typename T> void setDefaultValue(
                FunctionParameterValue<T> *_defaultValue) {
            if (!pImpl->defaultValue) delete pImpl->defaultValue;
            pImpl->defaultValue = _defaultValue;
        }

        std::string &name() { return pImpl->name; }
        std::string &name() const { return pImpl->name; }
        std::string &description() { return pImpl->description; }
        std::string &description() const { return pImpl->description; }
        FunctionParameterValueBase *value() { return pImpl->value; }
        const FunctionParameterValueBase *value() const { return pImpl->value; }
        FunctionParameterValueBase *defaultValue() {
            return pImpl->defaultValue;
        }
        FunctionParameterValueBase *defaultValue() const {
            return pImpl->defaultValue;
        }

    private:
        struct Impl {
            Impl(const std::string &_name,
                          const std::string &_description = ""):
                    name(_name), description(_description), value(0),
                    defaultValue(0) {}
            ~Impl() {
                delete value;
                delete defaultValue;
            }
            std::string name;
            std::string description;
            FunctionParameterValueBase *value;
            FunctionParameterValueBase *defaultValue;
        };
        Impl *pImpl;
};

class ParameterFac {
    public:
        template <typename T>
                FunctionParameter *createParameterWithValue(const std::string &_name,
                                                            const T &_value) {
            FunctionParameter *tmp = new FunctionParameter(_name);
            tmp->setValue(new FunctionParameterValue<T>(_value));

            return tmp;
        }

        template <typename T>
                FunctionParameter *createParameterWithDefault(const std::string &_name,
                                                              const T &_default,
                                                              const std::string &_description = "") {
            FunctionParameter *tmp = new FunctionParameter(_name, _description);
            // ...

            return tmp;
        }
    private:

};

typedef Loki::SingletonHolder<ParameterFac> ParameterFactory;
