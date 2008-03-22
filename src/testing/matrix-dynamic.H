
//      project:      hyperspace explorer
//      module:       Matrix.H
//      contains:     template declaration and definition of a matrix class
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#if !defined(MATRIX_DYNAMIC_H)
#define MATRIX_DYNAMIC_H

#include <cmath>

//  matrix<D>: a DxD matrix
template <unsigned D, typename num = double> class matrix {
public:
  matrix<D, num> (bool random = false);
  matrix<D, num> (const num a[D][D]);
  matrix<D, num> (unsigned axis1, unsigned axis2, num alpha);

  double &operator () (unsigned i, unsigned j) {
    return M[i][j]; }
  double operator () (unsigned i, unsigned j) const {
    return M[i][j]; }

  matrix<D, num> operator * (const matrix<D, num> &) const;

  matrix<D, num> operator - ();

  void print ();

protected:
  num M[D][D];
};


/*******************************************************************************
 *  default constructor: creates a unity DxD matrix
 */
template<unsigned D, typename num> matrix<D, num>::matrix (bool random) {
  for (unsigned i = 0; i < D; i++) {					//	i: row
    for (unsigned j = 0; j < D; j++)				//	j: col
      M[i][j] = random? num (rand ())/RAND_MAX: 0;
    if (!random) M[i][i] = 1;
  }
}

/*******************************************************************************
 *  creates a rotation about axes ii and jj of angle Theta
 *  @param ii   first (row) index
 *  @param jj   second (column) index
 *  @param Theta  rotation angle
 */
template<unsigned D, typename num> 
    matrix<D, num>::matrix (unsigned ii, unsigned jj, num Theta) {
  num c = cos (Theta), s = sin (Theta);
  for (unsigned i = 0; i < D; i++) {          //  i: row
    for (unsigned j = 0; j < D; j++)        //  j: col
      M[i][j] = 0;
    M[i][i] = 1;
  }
  M[ii][ii] =  M[jj][jj] = c;
  M[ii][jj] = -s;
  M[jj][ii] = s;
}

template<unsigned D, typename num> 
    matrix<D, num>::matrix (const num a[D][D]) {
      for (unsigned i = 0; i < D; i++)
        for (unsigned j = 0; j < D; j++)
          M[i][j] = a[i][j];
    }

/*******************************************************************************
 *  matrix multiplication
 *  @param B	matrix to multiply with
 *  @return	*this * B
 */
template <unsigned D, typename num>
    inline matrix<D, num> 
        matrix<D, num>::operator * (const matrix<D, num> &B) const {
  matrix<D, num> C;
  for (unsigned i = 0; i < D; i++)					//	i: row
    for (unsigned j = 0; j < D; j++) {				//	j: col
      num s = 0;
      for (unsigned k = 0; k < D; k++)
	s += M[i][k]*B.M[k][j];
      C.M[i][j] = s;
    }
  return C;
}


/*******************************************************************************
 *  matrix negation
 *  @return	- *this
 */
template <unsigned D, typename num>
    inline matrix<D, num> 
        matrix<D, num>::operator - () {
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
template <unsigned D, typename num>
  void 
    matrix<D, num>::print () {
      std::cout << D << "x" << D << ":";
      for (unsigned i = 0; i < D; i++) {
        std::cout << (i > 0? " |": "") << std::endl << "|";
        for (unsigned j = 0; j < D; j++) 
          std::cout << std::setw (6) << std::setprecision (3) << operator ()(i, j);
      }
      std::cout << " |" << std::endl;
    }

#endif // !defined(MATRIX_H)
