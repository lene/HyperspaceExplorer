// Matrix.h: Schnittstelle für die Klasse Matrix.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX_H__0E3DA8B3_FBE9_11D3_B3AF_004005A4A929__INCLUDED_)
#define AFX_MATRIX_H__0E3DA8B3_FBE9_11D3_B3AF_004005A4A929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>

#include <string>
#include <ostream>
#include <strstream>
#include <iomanip>

using namespace std;

#include "Vektor.h"

#ifndef pi
//const double pi = 4*atan (1);
#endif 

template <int D> class Matrix {
public:
	Matrix<D> ();
	Matrix<D> (double, double, double, double, double, double);
	Matrix<D> (unsigned, unsigned, double);
	virtual ~Matrix<D> () { }

	double &operator () (unsigned i, unsigned j) {
		return M[i][j]; }

	Matrix<D> operator * (const Matrix<D> &) const;
	Vector operator * (const Vector &);

	string Print ();

protected:
	double M[D][D];
};

template <int D> ostream &operator << (const Matrix<D> M, ostream &o);

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

template<unsigned D> Matrix<D>::Matrix<D> () {
	for (unsigned i = 0; i < D; i++) {					//	i: row
		for (unsigned j = 0; j < D; j++) 				//	j: col
			M[i][j] = 0;
		M[i][i] = 1;
	}
}

template <unsigned D> Matrix<D>::Matrix<D> (double Rxy, double Rxz, double Rxw, 
											double Ryz, double Ryw, double Rzw) {
	Matrix Mxy (0, 1, Rxy);
	Mxy *= Matrix (0, 2, Rxz); 
	Mxy *= Matrix (0, 3, Rxw); 
	Mxy *= Matrix (1, 2, Ryz); 
	Mxy *= Matrix (1, 3, Ryw); 
	Mxy *= Matrix (2, 3, Rzw); 
	for (unsigned i = 0; i < D; i++) 					//	i: row
		for (unsigned j = 0; j < D; j++) 				//	j: col
			M[i][j] = Mxy (i,j);
}

template<unsigned D> Matrix<D>::Matrix<D> (unsigned ii, unsigned jj, double Theta) {
	double c = cos (Theta*pi/180.), s = sin (Theta*pi/180.);

	for (unsigned i = 0; i < D; i++) {					//	i: row
		for (unsigned j = 0; j < D; j++) 				//	j: col
			M[i][j] = 0;
		M[i][i] = 1;
	}

	M[ii][ii] =  M[jj][jj] = c;
	
	if ((ii+jj) & 1) {									//	ii+jj odd
		M[ii][jj] = -s;
		M[jj][ii] = s;
	}
	else {												//	ii+jj even
		M[ii][jj] = s;
		M[jj][ii] = -s;
	}
}

template <unsigned D> Matrix<D> Matrix<D>::operator * (const Matrix<D> &B) const {
	Matrix<D> C;
	for (unsigned i = 0; i < D; i++)					//	i: row
		for (unsigned j = 0; j < D; j++) {				//	j: col

			double s = 0;
			for (unsigned k = 0; k < D; k++)
				s += M[i][k]*B.M[k][j];
			
			C.M[i][j] = s;
		}
	return C;
}

template <unsigned D> Vector Matrix<D>::operator * (const Vector &V) {
	if (D != V.D ()) {
		MessageBox (NULL, ("Matrix.D != Vector.D:\n"+itoa (D)+" != "+itoa (V.D ())).c_str (),
					"Vector Matrix<D>::operator * (const Vector &V)", MB_ICONSTOP);
		exit (1);
	}

	Vector W (D);
	for (unsigned i = 0; i < D; i++) {				//	i: row
		double s = 0;
		for (unsigned j = 0; j < D; j++)			//	j: col
			s += M[i][j]*V[j];
		W[i] = s;
	}
	return W;
}

template <unsigned D> string Matrix<D>::Print () {
	ostrstream o;
	for (unsigned i = 0; i < D; i++) {
		o << "|";
		for (unsigned j = 0; j < D; j++) 
			o << setw (10) << setprecision (3) << M[i][j];
		o << "|\n";
	}
	o << ends;
	return o.str ();
}

template <int D> ostream &operator << (const Matrix<D> &M, ostream &o) {
	o << M.Print ();
	return o;
}

#endif // !defined(AFX_MATRIX_H__0E3DA8B3_FBE9_11D3_B3AF_004005A4A929__INCLUDED_)
