
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include "Globals.H"

#include "ComplexFunction.H"

using std::complex;

using VecMath::Vector;

///////////////////////////////////////////////////////////////////////////////

/** ComplexFunction c'tor given a definition set in R² (as parameter space)
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v                                         */
ComplexFunction::ComplexFunction (double _umin, double _umax, double _du,
				  double _vmin, double _vmax, double _dv):
  Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {
}


/** ComplexFunction destructor                                                */
ComplexFunction::~ComplexFunction () { }


/** allocate and initialize X[][] with values of f()
 *  call Surface::InitMem ()                                                  */
void ComplexFunction::Initialize () {
    X = new Vector<4> * [usteps+2];
    Xchunk = new Vector<4>   [(usteps+2)*(vsteps+2)];
  
  for (unsigned u = 0; u <= usteps+1; u++) {
    X[u]  =  Xchunk+u*(vsteps+2);
    for (unsigned v = 0; v <= vsteps+1; v++) {
      X[u][v] = f (umin+u*du, vmin+v*dv);
    }
  }
  
  InitMem ();
}


/** ComplexFunction defining function calling g () and returning (z, g (z))
 *  @param uu		Re (z)
 *  @param vv		Im (z)
 *  @return		value of defining function at point in question       */
Vector<4> &ComplexFunction::f (double uu, double vv) {
  complex<double> z (uu, vv), w = g (z);
  F[0] = uu;
  F[1] = vv;
  F[2] = w.real ();
  F[3] = w.imag ();
  
  return F; 
}

///////////////////////////////////////////////////////////////////////////////


/** z² c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z) 
 *  @param _du		stepsize in Re (z) 
 *  @param _vmin	minimal value in Im (z) 
 *  @param _vmax	maximal value in Im (z) 
 *  @param _dv		stepsize in Im (z)                                    */
z2::z2 (double _umin, double _umax, double _du,
	double _vmin, double _vmax, double _dv):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** z² defining function
 *  @param z		operand
 *  @return		z²                                                    */
complex<double> z2::g (complex<double> z) {
  return z*z; 
}

///////////////////////////////////////////////////////////////////////////////


/** z³ c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z) 
 *  @param _du		stepsize in Re (z) 
 *  @param _vmin	minimal value in Im (z) 
 *  @param _vmax	maximal value in Im (z) 
 *  @param _dv		stepsize in Im (z) 
 */
z3::z3 (double _umin, double _umax, double _du,
	double _vmin, double _vmax, double _dv):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** z³ defining function
 *  @param z		operand
 *  @return		z³
 */
complex<double> z3::g (complex<double> z) {
  return z*z*z; 
}


///////////////////////////////////////////////////////////////////////////////


/** z^a c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z) 
 *  @param _du		stepsize in Re (z) 
 *  @param _vmin	minimal value in Im (z) 
 *  @param _vmax	maximal value in Im (z) 
 *  @param _dv		stepsize in Im (z) 
 *  @param _alpha	exponent
 */
zA::zA (double _umin, double _umax, double _du,
	double _vmin, double _vmax, double _dv,
	double _alpha):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv),
  alpha (_alpha) {
  Initialize ();
}

/** z^a defining function
 *  @param z		operand
 *  @return		z^alpha
 */
complex<double> zA::g (complex<double> z) {
  return pow (z, alpha); 
}


///////////////////////////////////////////////////////////////////////////////


/** e^z c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z) 
 *  @param _du		stepsize in Re (z) 
 *  @param _vmin	minimal value in Im (z) 
 *  @param _vmax	maximal value in Im (z) 
 *  @param _dv		stepsize in Im (z) 
 *  @param _alpha	exponent multiplicator
 */
ez::ez (double _umin, double _umax, double _du,
	double _vmin, double _vmax, double _dv,
	double _alpha):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv),
  alpha (_alpha) {
  Initialize ();
}

/** e^z defining function
 *  @param z		operand
 *  @return		e^(alpha*z)
 */
complex<double> ez::g (complex<double> z) {
  return exp (alpha*z); 
}


///////////////////////////////////////////////////////////////////////////////


/** e^-z² c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z) 
 *  @param _du		stepsize in Re (z) 
 *  @param _vmin	minimal value in Im (z) 
 *  @param _vmax	maximal value in Im (z) 
 *  @param _dv		stepsize in Im (z) 
 *  @param _alpha	exponent multiplicator
 */
emz2::emz2 (double _umin, double _umax, double _du,
	    double _vmin, double _vmax, double _dv,
	    double _alpha):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv),
  alpha (_alpha) {
  Initialize ();
}

/** e^-z² defining function
 *  @param z		operand
 *  @return		e^-(alpha*z²)
 */
complex<double> emz2::g (complex<double> z) {
  return exp (-alpha*z*z); 
}


///////////////////////////////////////////////////////////////////////////////


/** z^-1 c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z) 
 *  @param _du		stepsize in Re (z) 
 *  @param _vmin	minimal value in Im (z) 
 *  @param _vmax	maximal value in Im (z) 
 *  @param _dv		stepsize in Im (z) 
 */
zm1::zm1 (double _umin, double _umax, double _du,
	  double _vmin, double _vmax, double _dv):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** z^-1 defining function
 *  @param z		operand
 *  @return		1/z
 */
complex<double> zm1::g (complex<double> z) {
  return 1./z; 
}


///////////////////////////////////////////////////////////////////////////////


/** z^-2 c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z) 
 *  @param _du		stepsize in Re (z) 
 *  @param _vmin	minimal value in Im (z) 
 *  @param _vmax	maximal value in Im (z) 
 *  @param _dv		stepsize in Im (z) 
 */
zm2::zm2 (double _umin, double _umax, double _du,
	  double _vmin, double _vmax, double _dv):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** z^-2 defining function
 *  @param z		operand
 *  @return		1/z²
 */
complex<double> zm2::g (complex<double> z) {
  return 1./(z*z); 
}


///////////////////////////////////////////////////////////////////////////////


/** sqrt(z) c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z) 
 *  @param _du		stepsize in Re (z) 
 *  @param _vmin	minimal value in Im (z) 
 *  @param _vmax	maximal value in Im (z) 
 *  @param _dv		stepsize in Im (z) 
 */
sqrtz::sqrtz (double _umin, double _umax, double _du,
	      double _vmin, double _vmax, double _dv):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** sqrt (z) defining function
 *  @param z		operand
 *  @return		sqrt (z)
 */
complex<double> sqrtz::g (complex<double> z) {
  return sqrt (z); 
}


///////////////////////////////////////////////////////////////////////////////


/** ln(z) c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z) 
 *  @param _du		stepsize in Re (z) 
 *  @param _vmin	minimal value in Im (z) 
 *  @param _vmax	maximal value in Im (z) 
 *  @param _dv		stepsize in Im (z) 
 */
lnz::lnz (double _umin, double _umax, double _du,
	  double _vmin, double _vmax, double _dv):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** ln(z) defining function
 *  @param z		operand
 *  @return		ln(z)
 */
complex<double> lnz::g (complex<double> z) {
  return log (z); 
}


///////////////////////////////////////////////////////////////////////////////


/** sin(z) c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z) 
 *  @param _du		stepsize in Re (z) 
 *  @param _vmin	minimal value in Im (z) 
 *  @param _vmax	maximal value in Im (z) 
 *  @param _dv		stepsize in Im (z) 
 */
sinz::sinz (double _umin, double _umax, double _du,
	    double _vmin, double _vmax, double _dv):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** sin(z) defining function
 *  @param z		operand
 *  @return		sin(pi*z)
 */
complex<double> sinz::g (complex<double> z) {
  return sin (pi*z); 
}


///////////////////////////////////////////////////////////////////////////////


/** cos(z) c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z) 
 *  @param _du		stepsize in Re (z) 
 *  @param _vmin	minimal value in Im (z) 
 *  @param _vmax	maximal value in Im (z) 
 *  @param _dv		stepsize in Im (z) 
 */
cosz::cosz (double _umin, double _umax, double _du,
	    double _vmin, double _vmax, double _dv):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/*******************************************************************************
 *  cos(z) defining function
 *  @param z		operand
 *  @return		cos (pi*z)
 */
complex<double> cosz::g (complex<double> z) {
  return cos (pi*z); 
}


///////////////////////////////////////////////////////////////////////////////


/** sinh(z) c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z) 
 *  @param _du		stepsize in Re (z) 
 *  @param _vmin	minimal value in Im (z) 
 *  @param _vmax	maximal value in Im (z) 
 *  @param _dv		stepsize in Im (z) 
 */
sinhz::sinhz (double _umin, double _umax, double _du,
	      double _vmin, double _vmax, double _dv):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** sinh(z) defining function
 *  @param z		operand
 *  @return		sinh(pi*z)
 */
complex<double> sinhz::g (complex<double> z) {
  return sinh (pi*z); 
}


///////////////////////////////////////////////////////////////////////////////


/** cosh(z) c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z) 
 *  @param _du		stepsize in Re (z) 
 *  @param _vmin	minimal value in Im (z) 
 *  @param _vmax	maximal value in Im (z) 
 *  @param _dv		stepsize in Im (z) 
 */
coshz::coshz (double _umin, double _umax, double _du,
	      double _vmin, double _vmax, double _dv):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** cosh(z) defining function
 *  @param z		operand
 *  @return		cosh(pi*z)
 */
complex<double> coshz::g (complex<double> z) {
  return cosh (pi*z); 
}


///////////////////////////////////////////////////////////////////////////////


/** tan(z) c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z) 
 *  @param _du		stepsize in Re (z) 
 *  @param _vmin	minimal value in Im (z) 
 *  @param _vmax	maximal value in Im (z) 
 *  @param _dv		stepsize in Im (z) 
 */
tanz::tanz (double _umin, double _umax, double _du,
	    double _vmin, double _vmax, double _dv):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** tan(z) defining function
 *  @param z		operand
 *  @return		tan (pi*z)
 */
complex<double> tanz::g (complex<double> z) {
  return sin (pi*z)/cos (pi*z); 
}


///////////////////////////////////////////////////////////////////////////////

Polynomial::Polynomial (double _umin, double _umax, double _du,
                        double _vmin, double _vmax, double _dv,
                        double _a1, double _a2, double _a3, double _a4):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  a[0] = 0; a[1] = _a1; a[2] = _a2; a[3] = _a3; a[4] = _a4;
  Initialize ();
}

complex<double> Polynomial::g (complex<double> z) {
  return ((((a[4]*z)+a[3])*z+a[2])*z+a[1])*z; 
}
