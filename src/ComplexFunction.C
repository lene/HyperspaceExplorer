
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include "Globals.H"

#include "ComplexFunction.H"

///////////////////////////////////////////////////////////////////////////////

ComplexFunction::ComplexFunction (double _umin, double _umax, double _du,
					  double _vmin, double _vmax, double _dv):
		Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {
}

ComplexFunction::~ComplexFunction () { }


void ComplexFunction::Initialize () {
		 X = new Vector * [usteps+2];
	Xchunk = new Vector   [(usteps+2)*(vsteps+2)];

	for (unsigned u = 0; u <= usteps+1; u++) {
		X[u]  =  Xchunk+u*(vsteps+2);
		for (unsigned v = 0; v <= vsteps+1; v++) {
			X[u][v] = f (umin+u*du, vmin+v*dv);
		}
	}

	InitMem ();
}


Vector &ComplexFunction::f (double uu, double vv) {
	complex<double> z (uu, vv), w = g (z);
	F[0] = uu;
	F[1] = vv;
	F[2] = w.real ();
	F[3] = w.imag ();

	return F; 
}

///////////////////////////////////////////////////////////////////////////////

z2::z2 (double _umin, double _umax, double _du,
		double _vmin, double _vmax, double _dv):
		ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
	Initialize ();
}

z2::~z2 () { }


complex<double> z2::g (complex<double> z) {
	return z*z; 
}

///////////////////////////////////////////////////////////////////////////////

z3::z3 (double _umin, double _umax, double _du,
		double _vmin, double _vmax, double _dv):
		ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
	Initialize ();
}

z3::~z3 () { }


complex<double> z3::g (complex<double> z) {
	return z*z*z; 
}


///////////////////////////////////////////////////////////////////////////////

zA::zA (double _umin, double _umax, double _du,
		double _vmin, double _vmax, double _dv,
		double _alpha):
		ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv),
		alpha (_alpha) {
	Initialize ();
}

zA::~zA () { }


complex<double> zA::g (complex<double> z) {
	return pow (z, alpha); 
}


///////////////////////////////////////////////////////////////////////////////

ez::ez (double _umin, double _umax, double _du,
		double _vmin, double _vmax, double _dv,
		double _alpha):
		ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv),
		alpha (_alpha) {
	Initialize ();
}

ez::~ez () { }


complex<double> ez::g (complex<double> z) {
	return exp (alpha*z); 
}


///////////////////////////////////////////////////////////////////////////////

emz2::emz2 (double _umin, double _umax, double _du,
			double _vmin, double _vmax, double _dv,
			double _alpha):
		ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv),
		alpha (_alpha) {
	Initialize ();
}

emz2::~emz2 () { }


complex<double> emz2::g (complex<double> z) {
	return exp (-alpha*z*z); 
}


///////////////////////////////////////////////////////////////////////////////

zm1::zm1 (double _umin, double _umax, double _du,
		  double _vmin, double _vmax, double _dv):
		ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
	Initialize ();
}

zm1::~zm1 () { }


complex<double> zm1::g (complex<double> z) {
	return 1./z; 
}


///////////////////////////////////////////////////////////////////////////////

zm2::zm2 (double _umin, double _umax, double _du,
		  double _vmin, double _vmax, double _dv):
		ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
	Initialize ();
}

zm2::~zm2 () { }


complex<double> zm2::g (complex<double> z) {
	return 1./(z*z); 
}


///////////////////////////////////////////////////////////////////////////////

sqrtz::sqrtz (double _umin, double _umax, double _du,
			  double _vmin, double _vmax, double _dv):
		ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
	Initialize ();
}

sqrtz::~sqrtz () { }


complex<double> sqrtz::g (complex<double> z) {
	return sqrt (z); 
}


///////////////////////////////////////////////////////////////////////////////

lnz::lnz (double _umin, double _umax, double _du,
		  double _vmin, double _vmax, double _dv):
		ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
	Initialize ();
}

lnz::~lnz () { }


complex<double> lnz::g (complex<double> z) {
	return log (z); 
}


///////////////////////////////////////////////////////////////////////////////

sinz::sinz (double _umin, double _umax, double _du,
			double _vmin, double _vmax, double _dv):
		ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
	Initialize ();
}

sinz::~sinz () { }


complex<double> sinz::g (complex<double> z) {
	return sin (pi*z); 
}


///////////////////////////////////////////////////////////////////////////////

cosz::cosz (double _umin, double _umax, double _du,
			double _vmin, double _vmax, double _dv):
		ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
	Initialize ();
}

cosz::~cosz () { }


complex<double> cosz::g (complex<double> z) {
	return cos (pi*z); 
}


///////////////////////////////////////////////////////////////////////////////

sinhz::sinhz (double _umin, double _umax, double _du,
			  double _vmin, double _vmax, double _dv):
		ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
	Initialize ();
}

sinhz::~sinhz () { }


complex<double> sinhz::g (complex<double> z) {
	return sinh (pi*z); 
}


///////////////////////////////////////////////////////////////////////////////

coshz::coshz (double _umin, double _umax, double _du,
			  double _vmin, double _vmax, double _dv):
		ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
	Initialize ();
}

coshz::~coshz () { }


complex<double> coshz::g (complex<double> z) {
	return cosh (pi*z); 
}


///////////////////////////////////////////////////////////////////////////////

tanz::tanz (double _umin, double _umax, double _du,
			double _vmin, double _vmax, double _dv):
		ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
	Initialize ();
}

tanz::~tanz () { }


complex<double> tanz::g (complex<double> z) {
	return sin (pi*z)/cos (pi*z); 
}


///////////////////////////////////////////////////////////////////////////////

/*
Polynomial::Polynomial (double _umin, double _umax, double _du,
			double _vmin, double _vmax, double _dv,
			double _a1, double _a2, double _a3, double _a4):
		ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
	a[0] = 0; a[1] = _a1; a[2] = _a2; a[3] = _a3; a[4] = _a4;
	Initialize ();
}

Polynomial::~Polynomial () { }


complex<double> Polynomial::g (complex<double> z) {
	return ((((a[4]*z)+a[3])*z+a[2])*z+a[1])*z; 
}
*/
