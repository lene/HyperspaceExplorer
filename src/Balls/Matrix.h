
//      project:      hyperspace explorer
//      module:       Matrix.H
//      contains:     template declaration and definition of a matrix class
//      compile with: make all
//	author:	      lene preuss (lene.preuss@gmail.com)
//	license:      GPL (see License.txt)


#if !defined(MATRIX_H)
#define MATRIX_H


#include "Vec.H"

//  matrix<D>: a DxD matrix
template <unsigned D> class matrix {
public:
	matrix<D> ();
	matrix<D> (double, double, double, double, double, double);
	matrix<D> (unsigned, unsigned, double);
	virtual ~matrix<D> () { }

	double &operator () (unsigned i, unsigned j) {
		return M[i][j]; }

	matrix<D> operator * (const matrix<D> &) const;
	Vec<D> operator * (const Vec<D> &);

  //	string Print ();

protected:
	double M[D][D];
};

//  default constructor: creates a unity DxD matrix
template<unsigned D> matrix<D>::matrix<D> () {
	for (unsigned i = 0; i < D; i++) {					//	i: row
		for (unsigned j = 0; j < D; j++) 				//	j: col
			M[i][j] = 0;
		M[i][i] = 1;
	}
}

template <unsigned D> matrix<D>::matrix<D> (double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw) {
  cerr << "matrix<" << D <<">::matrix<" << D <<"> (Rxy, Rxz, Rxw, Ryz, Ryw, Rzw) not yet implemented!" << endl;
  abort();
}

//  matrix<D> (ii, jj, Theta): creates a rotation about axes ii and jj of angle Theta
template<unsigned D> matrix<D>::matrix<D> (unsigned ii, unsigned jj, double Theta) {
	double c = cos (Theta*pi/180.), s = sin (Theta*pi/180.);
	for (unsigned i = 0; i < D; i++) {					//	i: row
		for (unsigned j = 0; j < D; j++) 				//	j: col
			M[i][j] = 0;
		M[i][i] = 1;
	}
	M[ii][ii] =  M[jj][jj] = c;
	M[ii][jj] = -s;
	M[jj][ii] = s;
}

//  matrix multiplication
template <unsigned D> matrix<D> matrix<D>::operator * (const matrix<D> &B) const {
	matrix<D> C;
	for (unsigned i = 0; i < D; i++)					//	i: row
		for (unsigned j = 0; j < D; j++) {				//	j: col
			double s = 0;
			for (unsigned k = 0; k < D; k++)
				s += M[i][k]*B.M[k][j];
			C.M[i][j] = s;
		}
	return C;
}

//  apply the matrix on a vector
template <unsigned D> Vec<D> matrix<D>::operator * (const Vec<D> &V) {
  Vec<D> W;
  for (unsigned i = 0; i < D; i++) {				//	i: row
    double s = 0;
    for (unsigned j = 0; j < D; j++)			//	j: col
      s += M[i][j]*V[j];
    W[i] = s;
  }
  return W;
}
/*
#include <strstream>
#include <iomanip>
//  output, mainly for debugging purposes
template <unsigned D> string matrix<D>::Print () {
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
*/
#endif // !defined(MATRIX_H)
