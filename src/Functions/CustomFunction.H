
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "Function.H"
#include "ComplexFunction.H"
#include "Surface.H"

class QString;

template<class function_type>
        class CustomFunctionBase {
    public:
        CustomFunctionBase(): handle (NULL) {}
        QString symbolic ();
        bool isValid() const { return valid; }
        
    protected:
        bool loadFunction (const QString &);
        void setValid() { valid = true; }
        void setInvalid() { valid = false; }
        
        function_type *func;
        void *handle;
        bool valid;
};

class CustomFunction: 
        public Function, 
        public CustomFunctionBase<Function::raw_function_type> {
    public:
        CustomFunction (double _tmin, double _tmax, double _dt,
                        double _umin, double _umax, double _du,
                        double _vmin, double _vmax, double _dv,
                        bool final = true);
        virtual ~CustomFunction();

    protected:
        virtual VecMath::Vector<4> &f (double, double, double);
};


class CustomPolarFunction: public CustomFunction {
    public:
        CustomPolarFunction (double _tmin, double _tmax, double _dt,
                             double _umin, double _umax, double _du,
                             double _vmin, double _vmax, double _dv);
        virtual ~CustomPolarFunction();

    protected:
        virtual VecMath::Vector<4> &f (double, double, double);
};


class CustomComplexFunction:
        public ComplexFunction,
        public CustomFunctionBase<ComplexFunction::function_type> {
    public:
        CustomComplexFunction (double _umin, double _umax, double _du,
                               double _vmin, double _vmax, double _dv);
        virtual ~CustomComplexFunction();

    protected:
        ComplexFunction::function_type g;
};

class CustomSurface:
        public Surface,
        public CustomFunctionBase<Surface::raw_function_type> {
    public:
        CustomSurface ( double _umin, double _umax, double _du,
                        double _vmin, double _vmax, double _dv);
        virtual ~CustomSurface();

    protected:
        virtual Surface::function_type f;
};


#include <dlfcn.h>

/** try to load a DLL and the f() in it
 *  @param libName name of the plugin DLL file
 *  @return success                                                       */
template<class function_type>
        bool CustomFunctionBase<function_type>::loadFunction(const QString &libName) {
    static char *error;

    handle = dlopen (libName, RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error opening library: " << dlerror() << std::endl;
        return false;
    }

    func = (function_type *)dlsym(handle, "f");
    if ((error = dlerror()) != NULL)  {
        std::cerr << "Error finding function: " << error << std::endl;
        return false;
    }

    return true;
}

/** @param handle an opened DLL handle
 *  @return custom function in symbolic notation                              */
template<class function_type>
        QString CustomFunctionBase<function_type>::symbolic () {
    typedef char* STRING;
    STRING (*sym)();
    sym = (STRING (*)())dlsym(handle, "symbolic");
    char *error;
    static char *ret;
    
    if ((error = dlerror()) != NULL)  {
        std::cerr << "Error finding symbolic description in " << error << std::endl;
        return QString ("something");
    }
    ret=(*sym)();
    return QString (ret);
}
