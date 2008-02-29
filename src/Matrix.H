
//      project:      hyperspace explorer
//      module:       Matrix.H
//      contains:     template declaration and definition of a matrix class
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#if !defined(MATRIX_H)
#define MATRIX_H


#include "Vector.H"

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
  Vector<D> operator * (const Vector<D> &);

  matrix<D> operator - ();

  std::string Print ();

protected:
  double M[D][D];
};


/*******************************************************************************
 *  default constructor: creates a unity DxD matrix
 */
template<unsigned D> matrix<D>::matrix () {
  for (unsigned i = 0; i < D; i++) {					//	i: row
    for (unsigned j = 0; j < D; j++) 				//	j: col
      M[i][j] = 0;
    M[i][i] = 1;
  }
}


/*******************************************************************************
 *  creates a DxD rotation matrix, where D=4, nyi
 *  @param Rxy	rotation around xy plane (z axis)
 *  @param Rxz	rotation around xz plane (y axis)
 *  @param Rxw	rotation around xw plane
 *  @param Ryz	rotation around xy plane (x axis)
 *  @param Ryw	rotation around yw plane
 *  @param Rzw	rotation around zw plane
 */
template <unsigned D> matrix<D>::matrix (double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw) {
  std::cerr << "matrix<" << D <<">::matrix<" << D 
	    <<"> (Rxy, Rxz, Rxw, Ryz, Ryw, Rzw) not yet implemented!" << std::endl;
  abort();
}


/*******************************************************************************
 *  creates a rotation about axes ii and jj of angle Theta
 *  @param ii		first (row) index
 *  @param jj		second (column) index
 *  @param Theta	rotation angle
 */
template<unsigned D> matrix<D>::matrix (unsigned ii, unsigned jj, double Theta) {
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


/*******************************************************************************
 *  matrix multiplication
 *  @param B	matrix to multiply with
 *  @return	*this * B
 */
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


/*******************************************************************************
 *  apply the matrix on a vector
 *  @param V	Vector to multiply with (project)
 *  @return	*this * V
 */
template <unsigned D> Vector<D> matrix<D>::operator * (const Vector<D> &V) {
    Vector<D> W;
    for (unsigned i = 0; i < D; i++) {				//	i: row
        double s = 0;
        for (unsigned j = 0; j < D; j++)			//	j: col
            s += M[i][j]*V[j];
        W[i] = s;
    }
    return W;
}


/*******************************************************************************
 *  matrix negation
 *  @return	- *this
 */
template <unsigned D> matrix<D> matrix<D>::operator - () {
  matrix<D> B (*this);
  for (unsigned i = 0; i < D; i++)					//	i: row
    for (unsigned j = 0; j < D; j++) {				//	j: col
      B.M[i][j] = -M[i][j];
    }
  return B;
}

#include <sstream>
#include <iomanip>


/*******************************************************************************
 *  output, mainly for debugging purposes
 */
template <unsigned D> std::string matrix<D>::Print () {
  std::ostringstream o;
  for (unsigned i = 0; i < D; i++) {
    o << "|";
    for (unsigned j = 0; j < D; j++) 
      o << std::setw (10) << std::setprecision (3) << M[i][j];
    o << "|\n";
  }
  o << std::ends;
  return o.str ();
}

#endif // !defined(MATRIX_H)
