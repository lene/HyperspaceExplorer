#include "numclass.H"
#include <complex>

    Vector f (double u, double v) {
      static Vector F (4);
      complex<double> z (u, v), w = z*z+1;
      F[0] = u; 
      F[1] = v;
      F[2] = w.real ();
      F[3] = w.imag ();

      return F; }

    char *symbolic () { return "z*z+1"; }