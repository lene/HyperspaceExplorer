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

#if !defined(MATRIX_H)
#define MATRIX_H

#include <string>

namespace VecMath {

  template <unsigned D, typename N> class Vector;
  
  ///  Matrix<D, N>: a \a D x \a D matrix of numbers of type \a N
  /** \tparam D dimension of the matrix
   *  \tparam N numerical type of the matrix elements
   *  \ingroup VecMath
   *  \author Lene Preuss <lene.preuss@gmail.com>                     
   */
  template <unsigned D, typename N = double> class Matrix {
    
    public:
    
      /// default constructor: creates a unit DxD Matrix
      Matrix<D, N> ();
      /// creates a rotation about axes \p ii and \p jj of angle \p theta
      Matrix<D, N> (unsigned ii, unsigned jj, N theta);

      /// Access operator
      N &operator () (unsigned i, unsigned j);
      /// Constant access operator
      const N &operator () (unsigned i, unsigned j) const;

      /// In-place Matrix multiplication
      Matrix<D, N> operator *=(const Matrix<D, N> &);

      /// Negate every single element
      Matrix<D, N> operator - ();

      /// Scale the Matrix separately for each dimension
      void scale(const Vector<D, N> &);

      /// String output, mainly for debugging purposes
      std::string toString() const;
      /// Alias for toString()
      operator std::string() const;

    private:
      
      /// A static two-dimensional array storing the components
      N _M[D][D];

  };

  /// Matrix multiplication
  template <unsigned D, typename N>
  Matrix<D, N> operator *(const Matrix<D, N> &A, const Matrix<D, N> &B);

  /// Apply the Matrix on a vector
  template <unsigned D, typename N>
  Vector<D, N> operator *(const Matrix<D, N> &M, const Vector<D, N> &V);
  
  /// Matrix output operator  
  template <unsigned D, typename N>
  std::ostream &operator << (std::ostream &, const Matrix<D, N> &);

}       // namespace VecMath

#endif  // !defined(MATRIX_H)
