
//      project:      hyperspace explorer
//      module:       Matrix.H
//      contains:     template declaration and definition of a Matrix class
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#if !defined(MATRIX_H)
#define MATRIX_H

#include <sstream>
#include <iomanip>

#include "Vector.H"
#include "NotYetImplementedException.H"
#include "Globals.H"

namespace VecMath {
    ///  Matrix<D, N>: a \a D x \a D matrix of numbers of type \a N
    /** \param D dimension of the matrix
     *  \param N numerical type of the matrix elements
     *  \ingroup VecMath
     *  \author Helge Preuss <scout@hyperspace-travel.de>                     */
    template <unsigned D, typename N = double> class Matrix {
        public:
            Matrix<D, N> ();
            Matrix<D, N> (N, N, N, N, N, N);
            Matrix<D, N> (unsigned, unsigned, N);
            virtual ~Matrix<D, N> () { }

            /** access operator
             *  \param i row index
             *  \param j column index
             *  \return \f$ M_{ij} \f$                                        */
            N &operator () (unsigned i, unsigned j) { return M[i][j]; }

            Matrix<D, N> operator *=(const Matrix<D, N> &);
            Matrix<D, N> operator *(const Matrix<D, N> &) const;
            Vector<D, N> operator *(const Vector<D, N> &);

            Matrix<D, N> operator - ();

            std::string Print () const;

        private:
            /// A static two-dimensional array storing the components
            N M[D][D];
    };

    template <unsigned D, typename N>
            std::ostream &operator << (std::ostream &, const Matrix<D, N> &);


    /** default constructor: creates a unit DxD Matrix                        */
    template<unsigned D, typename N> Matrix<D, N>::Matrix () {
        for (unsigned i = 0; i < D; i++) {					//	i: row
            for (unsigned j = 0; j < D; j++) 				//	j: col
                M[i][j] = 0;
            M[i][i] = 1;
        }
    }

    /** creates a DxD rotation Matrix, where D=4, not yet implemented
     *  @param Rxy	rotation around xy plane (z axis)
     *  @param Rxz	rotation around xz plane (y axis)
     *  @param Rxw	rotation around xw plane
     *  @param Ryz	rotation around xy plane (x axis)
     *  @param Ryw	rotation around yw plane
     *  @param Rzw	rotation around zw plane                                  */
    template <unsigned D, typename N>
            Matrix<D, N>::Matrix (N Rxy, N Rxz, N Rxw, N Ryz, N Ryw, N Rzw) {
        throw NotYetImplementedException(
            "Matrix<"+Global::itoa(D)+">::Matrix<"+Global::itoa(D)+
                "> (Rxy, Rxz, Rxw, Ryz, Ryw, Rzw)");
        abort();
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
                M[i][j] = 0;
            M[i][i] = 1;
        }
        M[ii][ii] =  M[jj][jj] = c;
        M[ii][jj] = -s;
        M[jj][ii] = s;
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
                    s += M[i][k]*B.M[k][j];
                M[i][j] = s;
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
                    s += M[i][k]*B.M[k][j];
                C.M[i][j] = s;
            }
        return C;
    }

    /** apply the Matrix on a vector
     *  @param V Vector to multiply with (project)
     *  @return *this * V                                                     */
    template <unsigned D, typename N>
            Vector<D, N> Matrix<D, N>::operator * (const Vector<D, N> &V) {
        Vector<D, N> W;
        for (unsigned i = 0; i < D; i++) {              //  i: row
            N s = 0;
            for (unsigned j = 0; j < D; j++)            //  j: col
                s += M[i][j]*V[j];
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
                B.M[i][j] = -M[i][j];
            }
        return B;
    }


    /** output, mainly for debugging purposes                                 */
    template <unsigned D, typename N> std::string Matrix<D, N>::Print () const {
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
    /// Matrix output operator
    /** \ingroup VecMath
     *  \param o ostream to push into
     *  \param M Matrix to print
     *  \return a new ostream to push Matrices and stuff into
     */
    template <unsigned D, typename N>
        std::ostream &operator << (std::ostream &o, const Matrix<D, N> &M) {
            o << M.Print() << std::endl;
            return o;
        }

}       // namespace VecMath

#endif  // !defined(MATRIX_H)
