#include "Vector.H"

using namespace VecMath;

    Vector<4> f (double x, double y, double z) {
      static Vector<4> F;
      F[0] = x;
      F[1] = y;
      F[2] = z;
      F[3] = x*x*pow(y*y,sin(z*z));

      return F; }

    char *symbolic () { return "x*x*pow(y*y,sin(z*z))"; }