#include "Vector.H"
Vector<4> f (double t, double u, double v) {
	static Vector<4> F;
	double sinphi = sin (pi*t), cosphi = cos (pi*t),
	sintht = sin (pi*u), costht = cos (pi*u),
	sinpsi = sin (pi*v), cospsi = cos (pi*v),
	Radius = sin (t)*cos (u)*tan (v);
	
	F[0] = Radius*sinpsi*sintht*cosphi;
	F[1] = Radius*sinpsi*sintht*sinphi;
	F[2] = Radius*sinpsi*costht;
	F[3] = Radius*cospsi;
	
	return F; 
}

char *symbolic () { return "sin (t)*cos (u)*tan (v)"; }