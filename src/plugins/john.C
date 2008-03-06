#include "Vector.H"
#include <complex>

    Vector<4> f (double u, double v) {
      static Vector<4> F;
      std::complex<double> z (u, v), w = z;
      F[0] = u; 
      F[1] = v;
      F[2] = w.real ();
      F[3] = w.imag ();

      return F; }

    char *symbolic () { return "z"; }