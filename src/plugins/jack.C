#include "Vector.H"
    Vector f (double t, double u, double v) {
      static Vector F (4);
      double sinphi = sin (pi*t), cosphi = cos (pi*t),	
             sintht = sin (pi*u), costht = cos (pi*u),
             sinpsi = sin (pi*v), cospsi = cos (pi*v),
             Radius = sin(t);
 
      F[0] = Radius*sinpsi*sintht*cosphi;
      F[1] = Radius*sinpsi*sintht*sinphi;
      F[2] = Radius*sinpsi*costht;
      F[3] = Radius*cospsi;
 
      return F; }

    char *symbolic () { return "sin(t)"; }