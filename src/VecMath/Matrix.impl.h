/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
    Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef MATRIX_IMPL_H
#define MATRIX_IMPL_H

#include "Matrix.h"

#include "Vector.h"

namespace VecMath {

template<unsigned D, typename N> 
Matrix<D, N>::Matrix () {
  for (unsigned i = 0; i < D; i++) {                  //  i: row
    for (unsigned j = 0; j < D; j++) {                //  j: col
      _M[i][j] = 0;
    }
    _M[i][i] = 1;
  }
}

/** @param ii   first (row) index
 *  @param jj   second (column) index
 *  @param theta  rotation angle                                        
 */
template<unsigned D, typename N>
Matrix<D, N>::Matrix (unsigned ii, unsigned jj, N theta) {
  N c = cos (theta*pi/180.), s = sin (theta*pi/180.);
  for (unsigned i = 0; i < D; i++) {          //  i: row
    for (unsigned j = 0; j < D; j++) {       //  j: col
      _M[i][j] = 0;
    }
    _M[i][i] = 1;
  }
  _M[ii][ii] =  _M[jj][jj] = c;
  _M[ii][jj] = -s;
  _M[jj][ii] = s;
}

/** \param i row index
 *  \param j column index
 *  \return \f$ M_{ij} \f$                                        
 */
template<unsigned D, typename N> 
N &Matrix<D, N>::operator () (unsigned i, unsigned j) { 
  return _M[i][j]; 
}

/** \param i row index
 *  \param j column index
 *  \return \f$ M_{ij} \f$                                        
 */
template<unsigned D, typename N> 
const N &Matrix<D, N>::operator () (unsigned i, unsigned j) const { 
  return _M[i][j]; 
}

/** @param B Matrix to multiply with
 *  @return *this * \p B
 */
template <unsigned D, typename N> 
Matrix<D, N> Matrix<D, N>::operator *=(const Matrix<D, N> &B) {
  for (unsigned i = 0; i < D; i++) {            //  i: row
    for (unsigned j = 0; j < D; j++) {      //  j: col
      N s = 0;
      for (unsigned k = 0; k < D; k++) {
        s += _M[i][k]*B._M[k][j];
      }
      _M[i][j] = s;
    }
  }
  return *this;
}

/** @return - *this                                                       
 */
template <unsigned D, typename N>
Matrix<D, N> Matrix<D, N>::operator - () {
  Matrix<D, N> B (*this);
  for (unsigned i = 0; i < D; i++) {                    //  i: row
    for (unsigned j = 0; j < D; j++) {              //  j: col
      B._M[i][j] = -_M[i][j];
    }
  }
  return B;
}

/** \param s Scaling factor.
 */
template <unsigned D, typename N>
void Matrix<D, N>::scale(const Vector<D, N> &s) {
  for (unsigned i = 0; i < s.dimension(); ++i) {
    for (unsigned j = 0; j < s.dimension(); ++j) {
      _M[i][j] *= s[i];
    }
  }
}

template <unsigned D, typename N> 
std::string Matrix<D, N>::toString() const {
   std::ostringstream o;
   o << *this << std::ends;
   return o.str();
}

template<unsigned D, typename N> 
Matrix<D, N>::operator std::string() const {
  return toString();
}

/** \ingroup VecMath
 *  \tparam D dimension of the matrix
 *  \tparam N numerical type of the matrix elements
 *  \param A  Matrix that is multiplied upon
 *  \param B  Matrix to multiply with
 *  @return \p A * \p B                                                     
 */
template <unsigned D, typename N> 
Matrix<D, N> operator *(const Matrix<D, N> &A, const Matrix<D, N> &B) {
  Matrix<D, N> C;
  for (unsigned i = 0; i < D; i++) {
    for (unsigned j = 0; j < D; j++) {        //  j: col
      N s = 0;
      for (unsigned k = 0; k < D; k++) {
        s += A(i, k)*B(k, j);
      }
      C(i, j) = s;
    }
  }
  return C;
}

/** \ingroup VecMath
 *  \tparam D dimension of the matrix
 *  \tparam N numerical type of the matrix elements
 *  \param V Vector to multiply with (project)
 *  \param M Matrix to print
 *  \return \p M * \p V
 */
template <unsigned D, typename N>
Vector<D, N> operator * (const Matrix<D, N> &M, const Vector<D, N> &V) {
  Vector<D, N> W;
  for (unsigned i = 0; i < D; i++) {              //  i: row
    N s = 0;
    for (unsigned j = 0; j < D; j++) {           //  j: col
      s += M(i, j)*V[j];
    }
    W[i] = s;
  }
  return W;
}

/** \ingroup VecMath
 *  \tparam D dimension of the matrix
 *  \tparam N numerical type of the matrix elements
 *  \param o ostream to push into
 *  \param M Matrix to print
 *  \return a new ostream to push Matrices and stuff into
 */
template <unsigned D, typename N>
std::ostream &operator << (std::ostream &o, const Matrix<D, N> &M) {
  for (unsigned i = 0; i < D; i++) {
    o << "|";
    for (unsigned j = 0; j < D; j++) {
      o << std::setw (10) << std::setprecision (3) << M(i, j);
    }
    o << "|" << std::endl;
  }
  return o;
}

}

#endif