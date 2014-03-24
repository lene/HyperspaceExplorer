/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef CUSTOMFUNCTION_H
#define CUSTOMFUNCTION_H

#include <dlfcn.h>
#include <typeinfo>

#include "Displayable.h"
#include "RealFunction.h"
#include "Surface/ComplexFunction.h"
#include "Surface/Surface.h"

#include <QString>

class QString;
/// Base class for custom functions, which can be edited by the user
/** CustomFunctionBase contains the functions common to all descendants, if
 *  necessary as a template to cater for the varying function types of the
 *  different implementations
 *  \tparam function_type
 *  \ingroup FunctionGroup                                                    */
template<class function_type>
        class CustomFunctionBase {
    public:
        CustomFunctionBase(): handle (NULL) {}
        /// CustomFunction destructor, closes DLL if necessary
        ~CustomFunctionBase() { if (handle) dlclose (handle); }
        QString symbolic () const;

        /// \return Whether loading the library succeeded
        bool isValid() const { return valid; }

    protected:
        bool loadFunction (const QString &, QString = "f");

        /// Signify success in loading the function
        void setValid() { valid = true; }
        /// Signify failure in loading the function
        void setInvalid() { valid = false; }
        
        virtual QString defaultSymbolicName() const { return QString (typeid(*this).name()); }

        /// The function that is called
        function_type *func;

    private:
        void *handle;   ///< Temporary function handle returned by dlopen()
        bool valid;     ///< Whether loading the library succeeded
};

/// Function \f$ f: R^3 \rightarrow R \f$, editable to an arbitrary function.
/** \ingroup RealGroup                                                        */
class CustomFunction:
        public RealFunction,
        public CustomFunctionBase<RealFunction::raw_function_type> {
    public:
	CustomFunction() { }
        CustomFunction (double _tmin, double _tmax, double _dt,
                        double _umin, double _umax, double _du,
                        double _vmin, double _vmax, double _dv,
                        bool final = true);
        virtual ~CustomFunction() { }

        virtual std::string getFunctionName() const;

    protected:
        virtual QString defaultSymbolicName() const { return "Custom Function"; }
        
        virtual RealFunction::function_type f;
};

namespace {
    Displayable *createCustomFunction() { return new CustomFunction; }
    const bool registeredCF = TheFunctionFactory::Instance().registerFunction(createCustomFunction, "RealFunction");
}

/// Function \f$ f: R^3 \rightarrow R \f$, editable to an arbitrary function
/** The function is interpreted as a four-dimensional polar function,
 *  \f$ r = r(\psi, \theta, \phi) \f$.
 *  \ingroup PolarGroup                                                    */
class CustomPolarFunction: public CustomFunction {
    public:
	CustomPolarFunction() { }
        CustomPolarFunction (double _tmin, double _tmax, double _dt,
                             double _umin, double _umax, double _du,
                             double _vmin, double _vmax, double _dv);
        virtual ~CustomPolarFunction() { }

        virtual std::string getFunctionName() const;

    protected:
        virtual QString defaultSymbolicName() const { return "Custom Polar Function"; }
        virtual RealFunction::function_type f;
};

namespace {
    Displayable *createCustomPolarFunction() { return new CustomPolarFunction; }
    const bool registeredCPF = TheFunctionFactory::Instance().registerFunction(createCustomPolarFunction, "RealFunction");
}

/// Function \f$ f: R^2 \rightarrow R^4 \f$, editable to an arbitrary function
/** \ingroup SurfaceGroup                                                     */
class CustomSurface:
        public Surface,
        public CustomFunctionBase<Surface::raw_function_type> {
    public:
	CustomSurface() { }
        CustomSurface (double _umin, double _umax, double _du,
                       double _vmin, double _vmax, double _dv);
        virtual ~CustomSurface() { }

        virtual std::string getFunctionName() const;

    protected:
        virtual QString defaultSymbolicName() const { return "Custom Surface"; }
        virtual Surface::function_type f;
};

namespace {
    Displayable *createCustomSurface() { return new CustomSurface; }
    const bool registeredCS = TheFunctionFactory::Instance().registerFunction(createCustomSurface, "Surface");
}

/// Function \f$ f: C \rightarrow C \f$, editable to an arbitrary function
/** \ingroup ComplexGroup                                                     */
class CustomComplexFunction:
    public ComplexFunction,
    public CustomFunctionBase<ComplexFunction::function_type> {

public:

  CustomComplexFunction (): ComplexFunction() { }
  CustomComplexFunction (double _umin, double _umax, double _du,
                         double _vmin, double _vmax, double _dv);
        virtual ~CustomComplexFunction() { }

        virtual std::string getFunctionName() const;
                
    protected:
        virtual QString defaultSymbolicName() const { return "Custom Complex Function"; }
        ComplexFunction::function_type g;
};

namespace {
  Displayable *createCustomComplexfunction() { return new CustomComplexFunction(); }
  /// \todo make this work.
  const bool registeredCCF = TheFunctionFactory::Instance().registerFunction(createCustomComplexfunction, "ComplexFunction");
}

/** try to load a DLL and the f() in it
 *  \param libName name of the plugin DLL file
 *  \param funcName name of the function to load
 *  \return success                                                       */
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

/** \return Custom function in symbolic notation */
template<class function_type>
QString CustomFunctionBase<function_type>::symbolic () const {
    typedef char* STRING;
    STRING (*sym)();
    sym = (STRING (*)())dlsym(handle, "symbolic");
    const char *error;
    static char *ret;

    if ((error = dlerror()) != NULL)  {
        std::cerr << "Error finding symbolic description in " << error << std::endl;
        return defaultSymbolicName();
    }
    ret=(*sym)();
    return QString (ret);
}

#endif