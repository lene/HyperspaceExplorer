// Vector.cpp: Implementierung der Klasse Vector.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Vektor.h"
#ifdef _DEBUG
unsigned Vector::CopyConstructorCalled = 0,
		 Vector::OperatorEqualCalled = 0,
		 Vector::DestructorCalled = 0;
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Vector::Vector():
		X (new double [4]), dim (4), own (true) {
}

Vector::Vector (const Vector &V): 
		X (new double [V.dim]), dim (V.dim), own (true) {
#ifdef _DEBUG
	CopyConstructorCalled++;
#endif
	for (unsigned i = 0; i < dim; i++)
		X[i] = V.X[i];
}

Vector::Vector (unsigned d):
		X (new double [d]), dim (d), own (true) {
}

Vector::Vector (double w, double x, double y, double z):
		X (new double [4]), dim (4), own (true) {
	X[0] = w; X[1] = x; X[2] = y; X[3] = z; 
}

Vector::Vector (double x, double y, double z):
		X (new double [3]), dim (3), own (true) {
	X[0] = x; X[1] = y; X[2] = z; 
}

Vector::Vector (double *_X, unsigned d):
		X (_X), dim (d), own (false) {
}

Vector::~Vector() {
#ifdef _DEBUG
	DestructorCalled++;
#endif
	if (own && dim && X) {
		delete [] X;
		dim = 0; }
}

Vector &Vector::operator = (const Vector &V) {
#ifdef _DEBUG
	OperatorEqualCalled++;
#endif

	if (dim != V.dim) {
		if (X && dim && own) delete [] X;
		dim = V.dim;
		X = new double (dim);
  		own = true;
	}

	for (unsigned i = 0; i < dim; i++)
		X[i] = V.X[i];

	return *this;
}

Vector &Vector::operator+= (const Vector &V) {
	for (unsigned i = 0; i < dim; X[i] += V.X[i++]);
	return *this;
}

Vector &Vector::operator-= (const Vector &V) {
	for (unsigned i = 0; i < dim; X[i] -= V.X[i++]);
	return *this;
}

Vector &Vector::operator*= (const double &s) {
	for (unsigned i = 0; i < dim; X[i++] *= s);
	return *this;
}

Vector &Vector::operator/= (const double &s) {
	return operator*= (1./s);
}

Vector &Vector::operator+  (const Vector &V) const {
	static Vector T;
	T = *this;
	return T += V;
}

Vector &Vector::operator-  (const Vector &V) const { 
	static Vector T;
	T = *this;
	return T -= V;
}
Vector &Vector::operator*  (const double &s) const { 
	static Vector T;
	T = *this;
	return T *= s;
}
Vector &Vector::operator/  (const double &s) const { 	
	return operator * (1./s);
}

double  Vector::operator* (const Vector &V) const {
	if (dim != V.dim) {
		exit (1); }

	double s = 0;
	for (unsigned i = 0; i < dim; i++)
		s += X[i]*V.X[i];

	return s; 
}

#include <strstream>
#include <iomanip>

string Vector::Print () {
	ostrstream o;
	o << "|";
	for (unsigned i = 0; i < dim; i++)
		o << setw (10) << setprecision (3) << X[i];
	o << "|\n" << ends;

	return o.str ();
}


Vector vnormalize (const Vector &x) {
	static Vector n (3);
	double norm = sqrt (x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);

	if (norm == 0) return x;

	n[0] = x[0]/norm; n[1] = x[1]/norm; n[2] = x[2]/norm;
	return n;
}

Vector vnormalize (double xx, double yy, double zz) {
	static Vector x (3);

	x[0] = xx; x[1] = yy; x[2] = zz;
	return vnormalize (x);
}

Vector vcross (const Vector &a, const Vector &b) {
	static Vector c (3);
	
	c[0] = a[1]*b[2]-a[2]*b[1];
	c[1] = a[2]*b[0]-a[0]*b[2];
	c[2] = a[0]*b[1]-a[1]*b[0];

	return c; 
}

Vector vcross (const Vector &a, const Vector &b, const Vector &c) {
	static Vector d (4);
	double A = b[0]*c[1]-b[1]*c[0],
		   B = b[0]*c[2]-b[2]*c[0],
		   C = b[0]*c[3]-b[3]*c[0],
		   D = b[1]*c[2]-b[2]*c[1],
		   E = b[1]*c[3]-b[3]*c[1],
		   F = b[2]*c[3]-b[3]*c[2];
	
	d[0] =  a[1]*F - a[2]*E + a[3]*D;
	d[1] = -a[0]*F + a[2]*C - a[3]*B;
	d[2] =  a[0]*E - a[1]*C + a[3]*A;
	d[3] = -a[0]*D + a[1]*B - a[2]*A;
	
	return d; 
}
