
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
/** Base class for custom functions, which can be edited by the user \n
 *  CustomFunctionBase contains the functions common to all descendants, if
 *  necessary as a template to cater for the varying function types of the
 *  different implementations
 *  \ingroup FunctionGroup                                                    */
template<class function_type>
        class CustomFunctionBase {
    public:
        CustomFunctionBase(): handle (NULL) {}
        QString symbolic ();
        bool isValid() const { return valid; }

    protected:
        bool loadFunction (const QString &, QString = "f");
        void setValid() { valid = true; }
        void setInvalid() { valid = false; }

        function_type *func;
        void *handle;
        bool valid;
};

/** A Function \f$ f: R^3 \rightarrow R \f$, which the user can edit to
 *  have an arbitrary function.
 *  \ingroup RealGroup                                                        */
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

/** A Function \f$ f: R^3 \rightarrow R \f$, which the user can edit to
 *  have an arbitrary function. The function is interpreted as a four-
 *  dimensional polar function, \f$ r = r(\psi, \theta, \phi) \f$.
 *  \ingroup PolarGroup                                                    */
class CustomPolarFunction: public CustomFunction {
    public:
        CustomPolarFunction (double _tmin, double _tmax, double _dt,
                             double _umin, double _umax, double _du,
                             double _vmin, double _vmax, double _dv);
        virtual ~CustomPolarFunction();

    protected:
        virtual VecMath::Vector<4> &f (double, double, double);
};

/** A Function \f$ f: R^2 \rightarrow R^4 \f$, which the user can edit to
 *  have an arbitrary function.
 *  \ingroup SurfaceGroup                                                     */
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

/** A Function \f$ f: C \rightarrow C \f$, which the user can edit to
 *  have an arbitrary function.
 *  \ingroup ComplexGroup                                                     */
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


#include <dlfcn.h>

/** try to load a DLL and the f() in it
 *  @param libName name of the plugin DLL file
 *  @return success                                                       */
template<class function_type>
        bool CustomFunctionBase<function_type>::loadFunction(const QString &libName, QString funcName) {
    const char *error;

    handle = dlopen (libName.toStdString().c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error opening library: " << dlerror() << std::endl;
        return false;
    }

    func = (function_type *)dlsym(handle, funcName.toStdString().c_str());
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
    const char *error;
    static char *ret;

    if ((error = dlerror()) != NULL)  {
        std::cerr << "Error finding symbolic description in " << error << std::endl;
        return QString ("something");
    }
    ret=(*sym)();
    return QString (ret);
}
