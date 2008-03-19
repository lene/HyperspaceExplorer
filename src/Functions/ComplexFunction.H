
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


////////////////////////////////////////////////////////////////////////////////

#ifndef COMPLEXFUNCTION_H
#define COMPLEXFUNCTION_H 1


#include <complex>

#include "Surface.H"

/** A surface defined as a function \f$ C \rightarrow C \f$, where the surface
 *  in four dimensions is defined as
    \f{eqnarray*}{
        F_0 & = & Real(z)    \\
        F_1 & = & Imag(z)    \\
        F_2 & = & Real(f(z)) \\
        F_3 & = & Imag(f(z))
    \f}
 *  \ingroup FunctionGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class ComplexFunction: public Surface {
    public:
        ComplexFunction (const QString &name,
                         double _umin, double _umax, double _du,
                         double _vmin, double _vmax, double _dv);
        virtual ~ComplexFunction ();
        virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

        typedef std::complex<double> function_type(std::complex <double>) ;

    protected:
        virtual VecMath::Vector<4> &f (double, double);
        virtual function_type g = 0;
        void Initialize (void);
};

/** \f$ f(z) = z^2 \f$
 *  \ingroup FunctionGroup                                                    */
class z2: public ComplexFunction {
    public:
	z2 (double _umin, double _umax, double _du,
	    double _vmin, double _vmax, double _dv);
	virtual ~z2() { }
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

    protected:
	virtual function_type g;
};

/** \f$ f(z) = z^3 \f$
 *  \ingroup FunctionGroup                                                    */
class z3: public ComplexFunction {
    public:
	z3 (double _umin, double _umax, double _du,
	    double _vmin, double _vmax, double _dv);
	virtual ~z3() { }
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

    protected:
        virtual function_type g;
};

/** \f$ f(z) = z^\alpha \f$
 *  \ingroup FunctionGroup                                                    */
class zA: public ComplexFunction {
    public:
	zA (double _umin, double _umax, double _du,
	    double _vmin, double _vmax, double _dv,
	    double _alpha = 2);
	virtual ~zA () { }
	virtual void SetParameters(double _a = 0, double = 0, double = 0, double = 0) {
	   alpha = _a;
        }

    protected:
        virtual function_type g;

	double alpha;
};

/** \f$ f(z) = e^{\alpha*z} \f$
 *  \ingroup FunctionGroup                                                    */
class ez: public ComplexFunction {
    public:
	ez (double _umin, double _umax, double _du,
	    double _vmin, double _vmax, double _dv,
	    double _alpha = 2);
	virtual ~ez() { }
	virtual void SetParameters(double _a = 0, double = 0, double = 0, double = 0) {
            alpha = _a;
        }

    protected:
        virtual function_type g;
        double alpha;
};

/** \f$ f(z) = e^{-\alpha*z^2} \f$
 *  \ingroup FunctionGroup                                                    */
class emz2: public ComplexFunction {
    public:
	emz2 (double _umin, double _umax, double _du,
	      double _vmin, double _vmax, double _dv,
	      double _alpha = 1);
	virtual ~emz2() { }
	virtual void SetParameters(double _a = 0, double = 0, double = 0, double = 0) {
	   alpha = _a;
        }

    protected:
        virtual function_type g;
        double alpha;
};

/** \f$ f(z) = \frac{1}{z} \f$
 *  \ingroup FunctionGroup                                                    */
class zm1: public ComplexFunction {
    public:
	zm1 (double _umin, double _umax, double _du,
	     double _vmin, double _vmax, double _dv);
	virtual ~zm1 () { }
	virtual void SetParameters(double = 0, double = 0, double = 0, double = 0) { }

    protected:
        virtual function_type g;
};

/** \f$ f(z) = \frac{1}{z^2} \f$
 *  \ingroup FunctionGroup                                                    */
class zm2: public ComplexFunction {
    public:
	zm2 (double _umin, double _umax, double _du,
	     double _vmin, double _vmax, double _dv);
	virtual ~zm2 () { }
	virtual void SetParameters(double = 0, double = 0, double = 0, double = 0) { }

    protected:
        virtual function_type g;
};

/** \f$ f(z) = \sqrt{z} \f$
 *  \ingroup FunctionGroup                                                    */
class sqrtz: public ComplexFunction {
    public:
	sqrtz (double _umin, double _umax, double _du,
	       double _vmin, double _vmax, double _dv);
	virtual ~sqrtz () { }
	virtual void SetParameters(double = 0, double = 0, double = 0, double = 0) { }

    protected:
        virtual function_type g;
};

/** \f$ f(z) = \ln{z} \f$
 *  \ingroup FunctionGroup                                                    */
class lnz: public ComplexFunction {
    public:
	lnz (double _umin, double _umax, double _du,
	     double _vmin, double _vmax, double _dv);
	virtual ~lnz () { }
	virtual void SetParameters(double = 0, double = 0, double = 0, double = 0) { }

    protected:
        virtual function_type g;
};

/** \f$ f(z) = \sin{z} \f$
 *  \ingroup FunctionGroup                                                    */
class sinz: public ComplexFunction {
    public:
	sinz (double _umin, double _umax, double _du,
	      double _vmin, double _vmax, double _dv);
	virtual ~sinz () { }
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

    protected:
        virtual function_type g;
};

/** \f$ f(z) = \cos{z} \f$
 *  \ingroup FunctionGroup                                                    */
class cosz: public ComplexFunction {
    public:
	cosz (double _umin, double _umax, double _du,
	      double _vmin, double _vmax, double _dv);
	virtual ~cosz () { }
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

    protected:
        virtual function_type g;
};

/** \f$ f(z) = \sinh{z} \f$
 *  \ingroup FunctionGroup                                                    */
class sinhz: public ComplexFunction {
    public:
	sinhz (double _umin, double _umax, double _du,
	       double _vmin, double _vmax, double _dv);
	virtual ~sinhz () { }
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

    protected:
        virtual function_type g;
};

/** \f$ f(z) = \cosh{z} \f$
 *  \ingroup FunctionGroup                                                    */
class coshz: public ComplexFunction {
    public:
	coshz (double _umin, double _umax, double _du,
	       double _vmin, double _vmax, double _dv);
	virtual ~coshz () { }
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

    protected:
        virtual function_type g;
};

/** \f$ f(z) = \tan{z} \f$
 *  \ingroup FunctionGroup                                                    */
class tanz: public ComplexFunction {
    public:
	tanz (double _umin, double _umax, double _du,
		 double _vmin, double _vmax, double _dv);
	virtual ~tanz () { }
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

    protected:
        virtual function_type g;
};

/** a third-order polynomial of z, not yet implemented
 *  \ingroup FunctionGroup                                                    */
class Polynomial: public ComplexFunction {
    public:
	Polynomial(double _umin, double _umax, double _du,
		   double _vmin, double _vmax, double _dv,
		   double _a1, double _a2, double _a3, double _a4);
	virtual ~Polynomial () { }
	virtual void SetParameters(double _a = 0, double _b = 0,
                                   double _c = 0, double _d = 0) {
		a[1] = _a; a[2] = _b; a[3] = _c; a[4] = _d; }

    protected:
        virtual function_type g;
	double a[5];
};
#endif
