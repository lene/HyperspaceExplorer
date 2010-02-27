
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (lene.preuss@gmail.com)
//	license:      GPL (see License.txt)


////////////////////////////////////////////////////////////////////////////////

#ifndef COMPLEXFUNCTION_H
#define COMPLEXFUNCTION_H 1


#include <complex>

#include "Surface.h"

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
        ComplexFunction (const QString &name): Surface(name) { }
        ComplexFunction (const QString &name,
                         double _umin, double _umax, double _du,
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
        virtual VecMath::Vector<4> &f (double, double);
        virtual function_type g = 0;    ///< The actual function from C to C
        void Initialize (void);
};

/// \f$ f(z) = z^2 \f$
/** \ingroup ComplexGroup                                                    */
class z2: public ComplexFunction {
    public:
        z2 (): ComplexFunction("z2") { }
        z2 (double _umin, double _umax, double _du,
            double _vmin, double _vmax, double _dv);
        virtual ~z2() { }

    protected:
	virtual function_type g;
};

namespace {
    Function *createz2() { return new z2(); }
    const bool registered1 = TheFunctionFactory::Instance().registerFunction("z2", createz2);
}

/// \f$ f(z) = z^3 \f$
/** \ingroup ComplexGroup                                                    */
class z3: public ComplexFunction {
    public:
        z3 (): ComplexFunction("z3") { }
        z3 (double _umin, double _umax, double _du,
            double _vmin, double _vmax, double _dv);
        virtual ~z3() { }

    protected:
        virtual function_type g;
};

namespace {
    Function *createz3() { return new z3(); }
    const bool registered2 = TheFunctionFactory::Instance().registerFunction("z3", createz3);
}

/// \f$ f(z) = z^\alpha \f$
/** \ingroup ComplexGroup                                                    */
class zA: public ComplexFunction {
    public:
        zA (): ComplexFunction("zA"), alpha(2) { }
        zA (double _umin, double _umax, double _du,
            double _vmin, double _vmax, double _dv,
            double _alpha = 2);
        virtual ~zA () { }
        /// \see Function::SetParameters()
        virtual void SetParameters(const ParameterMap &parms) {
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "a") alpha = double(*i->second);
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
    Function *createzA() { return new zA(); }
    const bool registered3 = TheFunctionFactory::Instance().registerFunction("zA", createzA);
}

/// \f$ f(z) = e^{\alpha*z} \f$
/** \ingroup ComplexGroup                                                    */
class ez: public ComplexFunction {
    public:
        ez (): ComplexFunction("ez"), _alpha(2) { }
        ez (double _umin, double _umax, double _du,
            double _vmin, double _vmax, double _dv,
            double alpha = 2);
        virtual ~ez() { }
        virtual void SetParameters(const ParameterMap &parms) {
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "a") _alpha = double(*i->second);
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
    Function *createez() { return new ez(); }
    const bool registered4 = TheFunctionFactory::Instance().registerFunction("ez", createez);
}

/// \f$ f(z) = e^{-\alpha*z^2} \f$
/** \ingroup ComplexGroup                                                    */
class emz2: public ComplexFunction {
    public:
        emz2 (): ComplexFunction("emz2"), _alpha(1) { }
        emz2 (double _umin, double _umax, double _du,
              double _vmin, double _vmax, double _dv,
              double alpha = 1);
        virtual ~emz2() { }
        virtual void SetParameters(const ParameterMap &parms) {
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "a") _alpha = double(*i->second);
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
    Function *createemz2() { return new emz2(); }
    const bool registered5 = TheFunctionFactory::Instance().registerFunction("emz2", createemz2);
}

/// \f$ f(z) = \frac{1}{z} \f$
/** \ingroup ComplexGroup                                                    */
class zm1: public ComplexFunction {
    public:
        zm1 (): ComplexFunction("zm1") { }
        zm1 (double _umin, double _umax, double _du,
             double _vmin, double _vmax, double _dv);
        virtual ~zm1 () { }

    protected:
        virtual function_type g;
};

namespace {
    Function *createzm1() { return new zm1(); }
    const bool registered6 = TheFunctionFactory::Instance().registerFunction("zm1", createzm1);
}

/// \f$ f(z) = \frac{1}{z^2} \f$
/** \ingroup ComplexGroup                                                    */
class zm2: public ComplexFunction {
    public:
        zm2 (): ComplexFunction("zm2") { }
        zm2 (double _umin, double _umax, double _du,
             double _vmin, double _vmax, double _dv);
        virtual ~zm2 () { }

    protected:
        virtual function_type g;
};

namespace {
    Function *createzm2() { return new zm2(); }
    const bool registered7 = TheFunctionFactory::Instance().registerFunction("zm2", createzm2);
}

/// \f$ f(z) = \sqrt{z} \f$
/** \ingroup ComplexGroup                                                    */
class sqrtz: public ComplexFunction {
    public:
        sqrtz (): ComplexFunction("sqrtz") { }
        sqrtz (double _umin, double _umax, double _du,
               double _vmin, double _vmax, double _dv);
        virtual ~sqrtz () { }

    protected:
        virtual function_type g;
};

namespace {
    Function *createsqrtz() { return new sqrtz(); }
    const bool registered8 = TheFunctionFactory::Instance().registerFunction("sqrtz", createsqrtz);
}

/// \f$ f(z) = \ln{z} \f$
/** \ingroup ComplexGroup                                                    */
class lnz: public ComplexFunction {
    public:
        lnz (): ComplexFunction("lnz") { }
        lnz (double _umin, double _umax, double _du,
             double _vmin, double _vmax, double _dv);
        virtual ~lnz () { }

    protected:
        virtual function_type g;
};

namespace {
    Function *createlnz() { return new lnz(); }
    const bool registered9 = TheFunctionFactory::Instance().registerFunction("lnz", createlnz);
}

/// \f$ f(z) = \sin{z} \f$
/** \ingroup ComplexGroup                                                    */
class sinz: public ComplexFunction {
    public:
        sinz (): ComplexFunction("sinz") { }
        sinz (double _umin, double _umax, double _du,
              double _vmin, double _vmax, double _dv);
        virtual ~sinz () { }

    protected:
        virtual function_type g;
};

namespace {
    Function *createsinz() { return new sinz(); }
    const bool registered10 = TheFunctionFactory::Instance().registerFunction("sinz", createsinz);
}

/// \f$ f(z) = \cos{z} \f$
/** \ingroup ComplexGroup                                                    */
class cosz: public ComplexFunction {
    public:
        cosz (): ComplexFunction("cosz") { }
        cosz (double _umin, double _umax, double _du,
              double _vmin, double _vmax, double _dv);
        virtual ~cosz () { }

    protected:
        virtual function_type g;
};

namespace {
    Function *createcosz() { return new cosz(); }
    const bool registered11 = TheFunctionFactory::Instance().registerFunction("cosz", createcosz);
}

/// \f$ f(z) = \sinh{z} \f$
/** \ingroup ComplexGroup                                                    */
class sinhz: public ComplexFunction {
    public:
        sinhz (): ComplexFunction("sinhz") { }
        sinhz (double _umin, double _umax, double _du,
               double _vmin, double _vmax, double _dv);
        virtual ~sinhz () { }

    protected:
        virtual function_type g;
};

namespace {
    Function *createsinhz() { return new sinhz(); }
    const bool registered12 = TheFunctionFactory::Instance().registerFunction("sinhz", createsinhz);
}

/// \f$ f(z) = \cosh{z} \f$
/** \ingroup ComplexGroup                                                    */
class coshz: public ComplexFunction {
    public:
        coshz (): ComplexFunction("coshz") { }
        coshz (double _umin, double _umax, double _du,
               double _vmin, double _vmax, double _dv);
        virtual ~coshz () { }

    protected:
        virtual function_type g;
};

namespace {
    Function *createcoshz() { return new coshz(); }
    const bool registered13 = TheFunctionFactory::Instance().registerFunction("coshz", createcoshz);
}

/// \f$ f(z) = \tan{z} \f$
/** \ingroup ComplexGroup                                                    */
class tanz: public ComplexFunction {
    public:
        tanz (): ComplexFunction("tanz") { }
        tanz (double _umin, double _umax, double _du,
              double _vmin, double _vmax, double _dv);
        virtual ~tanz () { }

    protected:
        virtual function_type g;
};

namespace {
    Function *createtanz() { return new tanz(); }
    const bool registered14 = TheFunctionFactory::Instance().registerFunction("tanz", createtanz);
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
