
//      project:      hyperspace explorer
//      module:       Matrix.H
//      contains:     template declaration and definition of a Matrix class
//      compile with: make all
//	author:	      lene preuss (lene.preuss@gmail.com)
//	license:      GPL (see License.txt)


#if !defined(MATRIX_H)
#define MATRIX_H

#include <sstream>
#include <iomanip>

#include "Vector.h"
#include "NotYetImplementedException.h"
#include "Globals.h"

namespace VecMath {

  ///  Matrix<D, N>: a \a D x \a D matrix of numbers of type \a N
  /** \tparam D dimension of the matrix
   *  \tparam N numerical type of the matrix elements
   *  \ingroup VecMath
   *  \author Lene Preuss <lene.preuss@gmail.com>                     */
  template <unsigned D, typename N = double> class Matrix {
    public:
      Matrix<D, N> ();
      Matrix<D, N> (unsigned, unsigned, N);
      virtual ~Matrix<D, N> () { }

      /// Access operator
      /** \param i row index
       *  \param j column index
       *  \return \f$ M_{ij} \f$                                        */
      N &operator () (unsigned i, unsigned j) { return _M[i][j]; }
      /// Constant access operator
      /** \param i row index
       *  \param j column index
       *  \return \f$ M_{ij} \f$                                        */
      const N &operator () (unsigned i, unsigned j) const { return _M[i][j]; }

      Matrix<D, N> operator *=(const Matrix<D, N> &);
      Matrix<D, N> operator *(const Matrix<D, N> &) const;
      Vector<D, N> operator *(const Vector<D, N> &) const;

      Matrix<D, N> operator - ();

      void scale(const Vector<D, N> &);

      /// output, mainly for debugging purposes
      std::string toString() const;
      /// Alias for toString()
      operator std::string() const { return toString(); }

    private:
      /// A static two-dimensional array storing the components
      N _M[D][D];

  };

  template <unsigned D, typename N>
  std::ostream &operator << (std::ostream &, const Matrix<D, N> &);

}       // namespace VecMath

#endif  // !defined(MATRIX_H)
