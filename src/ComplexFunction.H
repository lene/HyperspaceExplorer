
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COMPLEXFUNCTION_H
#define COMPLEXFUNCTION_H 1


#include <complex> 

#include "Surface.H"

class ComplexFunction: public Surface {
public:
	ComplexFunction (double _umin, double _umax, double _du,
		 			 double _vmin, double _vmax, double _dv);
	virtual ~ComplexFunction ();
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
	virtual Vector &f (double, double);
	virtual complex<double> g (complex <double>) = 0;
	void Initialize (void);
};


class z2: public ComplexFunction {
public:
	z2 (double _umin, double _umax, double _du,
		double _vmin, double _vmax, double _dv);
	virtual ~z2();
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
	virtual complex<double> g (complex <double>);
};

class z3: public ComplexFunction {
public:
	z3 (double _umin, double _umax, double _du,
		double _vmin, double _vmax, double _dv);
	virtual ~z3();
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
	virtual complex<double> g (complex <double>);
};

class zA: public ComplexFunction {
public:
	zA (double _umin, double _umax, double _du,
		double _vmin, double _vmax, double _dv,
		double _alpha);
	virtual ~zA ();
	virtual void SetParameters (double _a = 0, double = 0, double = 0, double = 0) { 
		alpha = _a; }

protected:
	virtual complex<double> g (complex <double>);

	double alpha;
};

class ez: public ComplexFunction {
public:
	ez (double _umin, double _umax, double _du,
		double _vmin, double _vmax, double _dv,
		double _alpha);
	virtual ~ez();
	virtual void SetParameters (double _a = 0, double = 0, double = 0, double = 0) { 
		alpha = _a; }

protected:
	virtual complex<double> g (complex <double>);
	double alpha;
};

class emz2: public ComplexFunction {
public:
	emz2 (double _umin, double _umax, double _du,
		  double _vmin, double _vmax, double _dv,
		  double _alpha);
	virtual ~emz2();
	virtual void SetParameters (double _a = 0, double = 0, double = 0, double = 0) { 
		alpha = _a; }

protected:
	virtual complex<double> g (complex <double>);
	double alpha;
};

class zm1: public ComplexFunction {
public:
	zm1 (double _umin, double _umax, double _du,
		 double _vmin, double _vmax, double _dv);
	virtual ~zm1 ();
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
	virtual complex<double> g (complex <double>);
};

class zm2: public ComplexFunction {
public:
	zm2 (double _umin, double _umax, double _du,
		 double _vmin, double _vmax, double _dv);
	virtual ~zm2 ();
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
	virtual complex<double> g (complex <double>);
};

class sqrtz: public ComplexFunction {
public:
	sqrtz (double _umin, double _umax, double _du,
		   double _vmin, double _vmax, double _dv);
	virtual ~sqrtz ();
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
	virtual complex<double> g (complex <double>);
};

class lnz: public ComplexFunction {
public:
	lnz (double _umin, double _umax, double _du,
		 double _vmin, double _vmax, double _dv);
	virtual ~lnz ();
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
	virtual complex<double> g (complex <double>);
};

class sinz: public ComplexFunction {
public:
	sinz (double _umin, double _umax, double _du,
		 double _vmin, double _vmax, double _dv);
	virtual ~sinz ();
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
	virtual complex<double> g (complex <double>);
};

class cosz: public ComplexFunction {
public:
	cosz (double _umin, double _umax, double _du,
		 double _vmin, double _vmax, double _dv);
	virtual ~cosz ();
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
	virtual complex<double> g (complex <double>);
};

class sinhz: public ComplexFunction {
public:
	sinhz (double _umin, double _umax, double _du,
		 double _vmin, double _vmax, double _dv);
	virtual ~sinhz ();
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
	virtual complex<double> g (complex <double>);
};

class coshz: public ComplexFunction {
public:
	coshz (double _umin, double _umax, double _du,
		 double _vmin, double _vmax, double _dv);
	virtual ~coshz ();
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
	virtual complex<double> g (complex <double>);
};

class tanz: public ComplexFunction {
public:
	tanz (double _umin, double _umax, double _du,
		 double _vmin, double _vmax, double _dv);
	virtual ~tanz ();
	virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
	virtual complex<double> g (complex <double>);
};
#if 0
class Polynomial: public ComplexFunction {
public:
	Polynomial (double _umin, double _umax, double _du,
				double _vmin, double _vmax, double _dv,
				double _a1, double _a2, double _a3, double _a4);
	virtual ~Polynomial ();
	virtual void SetParameters (double _a = 0, double _b = 0, double _c = 0, double _d = 0) {
		a[1] = _a; a[2] = _b; a[3] = _c; a[4] = _d; }

protected:
	virtual complex<double> g (complex <double>);
	double a[5];
};
#endif
#endif
