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

#ifndef COMPLEXFUNCTION_H
#define COMPLEXFUNCTION_H 1


#include "Surface.h"

#include <complex>

/// A surface defined as a function \f$ C \rightarrow C \f$
/** The surface in four dimensions is defined as
    \f{eqnarray*}{
        F_0 & = & Real(z)    \\
        F_1 & = & Imag(z)    \\
        F_2 & = & Real(f(z)) \\
        F_3 & = & Imag(f(z))
    \f}
 *  \ingroup FunctionGroup
 *  @author Helge Preuss <lene.preuss@gmail.com>                         */
class ComplexFunction: public Surface {
public:
        /// Minimal constructor, sets the function name
        ComplexFunction (): Surface() { }
        ComplexFunction (double _umin, double _umax, double _du,
                         double _vmin, double _vmax, double _dv);
        virtual ~ComplexFunction ();
        /// Set up to 4 parameters
        /** Defaults to do nothing, so implementations need not implement it by
         *  default.
         */
        virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

        /// A function from \f$ C \rightarrow C \f$
        typedef std::complex<double> function_type(std::complex <double>);

protected:

  virtual function_type g = 0;    ///< The actual function from C to C

  /// "²" as QString
  const static QString sup2;
  /// "³" as QString
  const static QString sup3;

private:

  /// ParametricFunction that defines this function
  struct DefiningFunction: public ParametricFunction<4, 2> {

    DefiningFunction(ComplexFunction *parent): _complex_function(parent) { }
    virtual return_type f(const argument_type &x);

  private:

    /// Not a smart pointer because it's initialized to \c this and mustn't be deleted
    ComplexFunction * _complex_function;
  };

};

namespace {
  static DisplayableClass displayable_class_complex_function(
    "ComplexFunction", "Functions C -> C", "Surface"
  );
}

/// \f$ f(z) = z^2 \f$
/** \ingroup ComplexGroup                                                    */
class z2: public ComplexFunction {
    public:
        z2 (): ComplexFunction() { }
        z2 (double _umin, double _umax, double _du,
            double _vmin, double _vmax, double _dv);
        virtual ~z2() { }

        virtual std::string getFunctionName() const { return "z2"; } //"z"+ComplexFunction::sup2,

    protected:
	virtual function_type g;
};

namespace {
    Displayable *createz2() { return new z2(); }
    const bool registered1 = TheFunctionFactory::Instance().registerFunction(createz2, "ComplexFunction");
}

/// \f$ f(z) = z^3 \f$
/** \ingroup ComplexGroup                                                    */
class z3: public ComplexFunction {
    public:
        z3 (): ComplexFunction() { }
        z3 (double _umin, double _umax, double _du,
            double _vmin, double _vmax, double _dv);
        virtual ~z3() { }

        virtual std::string getFunctionName() const { return "z3"; } //"z"+ComplexFunction::sup3,

    protected:
        virtual function_type g;
};

namespace {
    Displayable *createz3() { return new z3(); }
    const bool registered2 = TheFunctionFactory::Instance().registerFunction(createz3, "ComplexFunction");
}

/// \f$ f(z) = z^\alpha \f$
/** \ingroup ComplexGroup                                                    */
class zA: public ComplexFunction {
    public:
        zA (): ComplexFunction(), alpha(2) { }
        zA (double _umin, double _umax, double _du,
            double _vmin, double _vmax, double _dv,
            double _alpha = 2);
        virtual ~zA () { }

        virtual std::string getFunctionName() const { return "zA"; }

        /// \see Function::SetParameters()
        virtual void SetParameters(const ParameterMap &parms) {
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "a") alpha = i->second->toDouble();
            }
#       else
            setParameter(parms, this->Phase, "a");
#       endif
        }

    protected:
        virtual function_type g;

    private:
        double alpha;   ///< Exponent
};

namespace {
    Displayable *createzA() { return new zA(); }
    const bool registered3 = TheFunctionFactory::Instance().registerFunction(createzA, "ComplexFunction");
}

/// \f$ f(z) = e^{\alpha*z} \f$
/** \ingroup ComplexGroup                                                    */
class ez: public ComplexFunction {
    public:
        ez (): ComplexFunction(), _alpha(2) { }
        ez (double _umin, double _umax, double _du,
            double _vmin, double _vmax, double _dv,
            double alpha = 2);
        virtual ~ez() { }

        virtual std::string getFunctionName() const { return "e^a*z"; }

        virtual void SetParameters(const ParameterMap &parms) {
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "a") _alpha = i->second->toDouble();
            }
#       else
            setParameter(parms, this->Phase, "a");
#       endif
        }

    protected:
        virtual function_type g;

    private:
        double _alpha;          ///< Factor of the exponent
};

namespace {
    Displayable *createez() { return new ez(); }
    const bool registered4 = TheFunctionFactory::Instance().registerFunction(createez, "ComplexFunction");
}

/// \f$ f(z) = e^{-\alpha*z^2} \f$
/** \ingroup ComplexGroup                                                    */
class emz2: public ComplexFunction {
    public:
        emz2 (): ComplexFunction(), _alpha(1) { }
        emz2 (double _umin, double _umax, double _du,
              double _vmin, double _vmax, double _dv,
              double alpha = 1);
        virtual ~emz2() { }

        virtual std::string getFunctionName() const { return "emz2"; } // "e^-a*z"+ComplexFunction::sup2,

        virtual void SetParameters(const ParameterMap &parms) {
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "a") _alpha = i->second->toDouble();
            }
#       else
            setParameter(parms, this->Phase, "a");
#       endif
        }

    protected:
        virtual function_type g;

    private:
        double _alpha;          ///< Factor of the exponent
};

namespace {
    Displayable *createemz2() { return new emz2(); }
    const bool registered5 = TheFunctionFactory::Instance().registerFunction(createemz2, "ComplexFunction");
}

/// \f$ f(z) = \frac{1}{z} \f$
/** \ingroup ComplexGroup                                                    */
class zm1: public ComplexFunction {
    public:
        zm1 (): ComplexFunction() { }
        zm1 (double _umin, double _umax, double _du,
             double _vmin, double _vmax, double _dv);
        virtual ~zm1 () { }

        virtual std::string getFunctionName() const { return "zm1"; }

    protected:
        virtual function_type g;
};

namespace {
    Displayable *createzm1() { return new zm1(); }
    const bool registered6 = TheFunctionFactory::Instance().registerFunction(createzm1, "ComplexFunction");
}

/// \f$ f(z) = \frac{1}{z^2} \f$
/** \ingroup ComplexGroup                                                    */
class zm2: public ComplexFunction {
    public:
        zm2 (): ComplexFunction() { }
        zm2 (double _umin, double _umax, double _du,
             double _vmin, double _vmax, double _dv);
        virtual ~zm2 () { }

        virtual std::string getFunctionName() const { return "zm2"; } // "1/z"+ComplexFunction::sup2,

    protected:
        virtual function_type g;
};

namespace {
    Displayable *createzm2() { return new zm2(); }
    const bool registered7 = TheFunctionFactory::Instance().registerFunction(createzm2, "ComplexFunction");
}

/// \f$ f(z) = \sqrt{z} \f$
/** \ingroup ComplexGroup                                                    */
class sqrtz: public ComplexFunction {
    public:
        sqrtz (): ComplexFunction() { }
        sqrtz (double _umin, double _umax, double _du,
               double _vmin, double _vmax, double _dv);
        virtual ~sqrtz () { }

        virtual std::string getFunctionName() const { return "sqrtz"; }

    protected:
        virtual function_type g;
};

namespace {
    Displayable *createsqrtz() { return new sqrtz(); }
    const bool registered8 = TheFunctionFactory::Instance().registerFunction(createsqrtz, "ComplexFunction");
}

/// \f$ f(z) = \ln{z} \f$
/** \ingroup ComplexGroup                                                    */
class lnz: public ComplexFunction {
    public:
        lnz (): ComplexFunction() { }
        lnz (double _umin, double _umax, double _du,
             double _vmin, double _vmax, double _dv);
        virtual ~lnz () { }

        virtual std::string getFunctionName() const { return "lnz"; }

    protected:
        virtual function_type g;
};

namespace {
    Displayable *createlnz() { return new lnz(); }
    const bool registered9 = TheFunctionFactory::Instance().registerFunction(createlnz, "ComplexFunction");
}

/// \f$ f(z) = \sin{z} \f$
/** \ingroup ComplexGroup                                                    */
class sinz: public ComplexFunction {
    public:
        sinz (): ComplexFunction() { }
        sinz (double _umin, double _umax, double _du,
              double _vmin, double _vmax, double _dv);
        virtual ~sinz () { }

        virtual std::string getFunctionName() const { return "sinz"; }

    protected:
        virtual function_type g;
};

namespace {
    Displayable *createsinz() { return new sinz(); }
    const bool registered10 = TheFunctionFactory::Instance().registerFunction(createsinz, "ComplexFunction");
}

/// \f$ f(z) = \cos{z} \f$
/** \ingroup ComplexGroup                                                    */
class cosz: public ComplexFunction {
    public:
        cosz (): ComplexFunction() { }
        cosz (double _umin, double _umax, double _du,
              double _vmin, double _vmax, double _dv);
        virtual ~cosz () { }

        virtual std::string getFunctionName() const { return "cosz"; }

    protected:
        virtual function_type g;
};

namespace {
    Displayable *createcosz() { return new cosz(); }
    const bool registered11 = TheFunctionFactory::Instance().registerFunction(createcosz, "ComplexFunction");
}

/// \f$ f(z) = \sinh{z} \f$
/** \ingroup ComplexGroup                                                    */
class sinhz: public ComplexFunction {
    public:
        sinhz (): ComplexFunction() { }
        sinhz (double _umin, double _umax, double _du,
               double _vmin, double _vmax, double _dv);
        virtual ~sinhz () { }

        virtual std::string getFunctionName() const { return "sinhz"; }

    protected:
        virtual function_type g;
};

namespace {
    Displayable *createsinhz() { return new sinhz(); }
    const bool registered12 = TheFunctionFactory::Instance().registerFunction(createsinhz, "ComplexFunction");
}

/// \f$ f(z) = \cosh{z} \f$
/** \ingroup ComplexGroup                                                    */
class coshz: public ComplexFunction {
    public:
        coshz (): ComplexFunction() { }
        coshz (double _umin, double _umax, double _du,
               double _vmin, double _vmax, double _dv);
        virtual ~coshz () { }

        virtual std::string getFunctionName() const { return "coshz"; }

    protected:
        virtual function_type g;
};

namespace {
    Displayable *createcoshz() { return new coshz(); }
    const bool registered13 = TheFunctionFactory::Instance().registerFunction(createcoshz, "ComplexFunction");
}

/// \f$ f(z) = \tan{z} \f$
/** \ingroup ComplexGroup                                                    */
class tanz: public ComplexFunction {
    public:
        tanz (): ComplexFunction() { }
        tanz (double _umin, double _umax, double _du,
              double _vmin, double _vmax, double _dv);
        virtual ~tanz () { }

        virtual std::string getFunctionName() const { return "tanz"; }

    protected:
        virtual function_type g;
};

namespace {
    Displayable *createtanz() { return new tanz(); }
    const bool registered14 = TheFunctionFactory::Instance().registerFunction(createtanz, "ComplexFunction");
}

/// a third-order polynomial of z, not yet implemented
/**  \ingroup ComplexGroup                                                    */
class Polynomial: public ComplexFunction {
    public:
        Polynomial(double _umin, double _umax, double _du,
                   double _vmin, double _vmax, double _dv,
                   double _a1, double _a2, double _a3, double _a4);
        virtual ~Polynomial () { }

    protected:
        virtual function_type g;    ///< function implementation

    private:
        double a[5];                ///< coefficients
};
#endif
