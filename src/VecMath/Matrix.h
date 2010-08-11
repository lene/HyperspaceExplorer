
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
//            Matrix<D, N> operator *=(const N &);
            Matrix<D, N> operator *(const Matrix<D, N> &) const;
            Vector<D, N> operator *(const Vector<D, N> &) const;
//            Vector<D, N> operator *(const N &) const;

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


    /// default constructor: creates a unit DxD Matrix
    template<unsigned D, typename N> Matrix<D, N>::Matrix () {
        for (unsigned i = 0; i < D; i++) {                  //  i: row
            for (unsigned j = 0; j < D; j++)                //  j: col
                _M[i][j] = 0;
            _M[i][i] = 1;
        }
    }

    /** creates a rotation about axes ii and jj of angle Theta
     *  @param ii		first (row) index
     *  @param jj		second (column) index
     *  @param Theta	rotation angle                                        */
    template<unsigned D, typename N>
            Matrix<D, N>::Matrix (unsigned ii, unsigned jj, N Theta) {
        N c = cos (Theta*pi/180.), s = sin (Theta*pi/180.);
        for (unsigned i = 0; i < D; i++) {					//	i: row
            for (unsigned j = 0; j < D; j++) 				//	j: col
                _M[i][j] = 0;
            _M[i][i] = 1;
        }
        _M[ii][ii] =  _M[jj][jj] = c;
        _M[ii][jj] = -s;
        _M[jj][ii] = s;
    }

    /** Matrix multiplication
     *  @param B Matrix to multiply with
     *  @return *this * B                                                     */
    template <unsigned D, typename N> Matrix<D, N>
            Matrix<D, N>::operator *=(const Matrix<D, N> &B) {
        for (unsigned i = 0; i < D; i++)            //  i: row
            for (unsigned j = 0; j < D; j++) {      //  j: col
                N s = 0;
                for (unsigned k = 0; k < D; k++)
                    s += _M[i][k]*B._M[k][j];
                _M[i][j] = s;
            }
        return *this;
    }

    /** Matrix multiplication
     *  @param B	Matrix to multiply with
     *  @return	*this * B                                                     */
    template <unsigned D, typename N> Matrix<D, N>
            Matrix<D, N>::operator * (const Matrix<D, N> &B) const {
        Matrix<D, N> C;
        for (unsigned i = 0; i < D; i++)					//	i: row
            for (unsigned j = 0; j < D; j++) {				//	j: col
                N s = 0;
                for (unsigned k = 0; k < D; k++)
                    s += _M[i][k]*B._M[k][j];
                C._M[i][j] = s;
            }
        return C;
    }

    /** apply the Matrix on a vector
     *  @param V Vector to multiply with (project)
     *  @return *this * V
     */
    template <unsigned D, typename N>
            Vector<D, N> Matrix<D, N>::operator * (const Vector<D, N> &V) const{
        Vector<D, N> W;
        for (unsigned i = 0; i < D; i++) {              //  i: row
            N s = 0;
            for (unsigned j = 0; j < D; j++)            //  j: col
                s += _M[i][j]*V[j];
            W[i] = s;
        }
        return W;
    }

    /** Matrix negation
     *  @return	- *this                                                       */
    template <unsigned D, typename N>
            Matrix<D, N> Matrix<D, N>::operator - () {
        Matrix<D, N> B (*this);
        for (unsigned i = 0; i < D; i++)                    //  i: row
            for (unsigned j = 0; j < D; j++) {              //  j: col
                B._M[i][j] = -_M[i][j];
            }
        return B;
    }

    /** Scale the Matrix separately for each dimension
     *  \param s Scaling factor.
     */
    template <unsigned D, typename N>
            void Matrix<D, N>::scale(const Vector<D, N> &s) {
      for (unsigned i = 0; i < s.dimension(); ++i) {
        for (unsigned j = 0; j < s.dimension(); ++j) {
          _M[i][j] *= s[i];
        }
      }
    }

    /// output, mainly for debugging purposes
    template <unsigned D, typename N> std::string Matrix<D, N>::toString() const {
        std::ostringstream o;
        o << *this << std::ends;
        return o.str();
    }

    /// Matrix output operator
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
            for (unsigned j = 0; j < D; j++)
                o << std::setw (10) << std::setprecision (3) << M(i, j);
            o << "|" << std::endl;
        }
        return o;
    }

}       // namespace VecMath

#endif  // !defined(MATRIX_H)
