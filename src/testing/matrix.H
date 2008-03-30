
#if !defined(MATRIX_H)
#define MATRIX_H

#include <cassert>

#include <iostream>
#include <iomanip>
#include <string>

#include "Vector.H"

/// \defgroup VecMathTest Vector and Matrix algebra optimized, in test state

namespace VecMath {

    /// \ingroup VecMathTest
    struct NotYetImplementedException {
        NotYetImplementedException (std::string what) {
            std::cerr << what << ": Not yet implemented!" << std::endl;
        }
    };

/// Matrix class that uses template metaprogramming to speed up multiplications
/** A matrix class speeding up matrix multiplications by using template
 *  metaprogramming to let the compiler unroll and optimize the multiplication
 *  loops
 *

    \todo why does the 100 fold speed increase come and go? why does it only work
        for dimensions up to 4? \n
        some clue: \n
        when print() is called after NLOOP multiplications, runtime performance
        drops significantly. this is the case for templatized version as well as
        with the for loop. roughly speaking, print() incurs an overhead of a
        second for both versions. funny thing is, print () is called AFTER the
        timing has taken place. \n
        the performance drop with print() has vanished after getting the
        initialization correct (looping from \p D-1 to 0 instead of looping from
        \p D) \n
        err well, this in not true... it has only vanished *sometimes*. I assume
        that gcc does the calculations only when the elements are in fact
        accessed after the calculation, otherwise it optimizes them away. \n

    \todo a corresponding vector class and member function for transformation of
        vectors

    \todo const-correctness everywhere

    \todo  templatize copy loop in <tt>Matrix (const N a[D][D])</tt>

    \todo drop \p D_ as template parameter for inner classes where possible \n
        there is a problem with specializations in inner classes, which don't
        have any template parameters at all:
        \code
            template <>                                             // error!
                struct ConstructLoop<0, 0> {
                  static void row_loop (N a[D][D]) { a[0][0] = (N)1;
                }
        \endcode
        workaround <news:718f76ba.0305081256.6969e6ae@posting.google.com>
        \code
            // workaround class
            template <typename S> struct inner {
                template <typename T> static int apply(int) { generic action here }
            };

            template <typename T> struct outer {
                template <typename S> int specialized(int a) {
                    return inner<S>::template apply<T>(a);
                }
            };

            // specialize your workaround class for each type
            template <> struct inner< double > {
                template <typename T> static int apply(int) {
                    // code for outer<T>::specialized< double >
                }
            };

            // more specialization's of inner<> as necessary.
        \endcode
    \todo specializations of inner classes - do they really have to be declared?
        (seems so)\n
       whittle them down to the bare minimum anyways

 * \ingroup VecMathTest
 */
    template<unsigned D, typename N = double>
        class Matrix {

        public:
            Matrix();
            Matrix(unsigned, unsigned, N);
            Matrix(bool random);
            Matrix (const N a[D][D]);
            Matrix (const N *a);

            N  operator() (unsigned i, unsigned j) const;
            N &operator() (unsigned i, unsigned j);

            Matrix<D, N> operator*  (const Matrix<D, N>& other);
            Matrix<D, N> operator*= (const Matrix<D, N>& other);
            VecMath::Vector<D, N> operator* (const VecMath::Vector<D, N> &);

            void print ();

            N det () {
#               if 0
                    return Det<D>::det (data_);
#               else
                    throw NotYetImplementedException("Matrix<D, N>::det()");
#               endif
            }
            Matrix<D-1, N> matrix_minor (unsigned i, unsigned j);


        protected:
            /// Initialization of a unity \p D x \p D matrix
            /** construction of a unity matrix with values which are known to
             *  the compiler \n
             *  functions and specializations for \p i == 0 and \p j == 0     */
            template<unsigned D_, unsigned i, unsigned j>
                struct ConstructLoop {
                    static void row_loop (N a[D][D]);
                    static void col_loop (N a[D][D]);
            };

            /// Initialization of a unity \p D x \p D matrix
            /** Specialization for row = 0        */
            template <unsigned D_, unsigned j>
                struct ConstructLoop<D_, 0, j> {
                    static void row_loop (N a[D][D]);
                    static void col_loop (N a[D][D]);
                };

            /// Initialization of a unity \p D x \p D matrix
            /** Specialization for column = 0        */
            template <unsigned D_, unsigned i>
                struct ConstructLoop<D_, i, 0> {
                    static void row_loop (N a[D][D]);
                    static void col_loop (N a[D][D]);
                };

            /// Initialization of a unity \p D x \p D matrix
            /** Specialization for row = 0, column = 0 */
            template <unsigned D_>
                struct ConstructLoop<D_, 0, 0> {
                    /// Sets element[0][0] to 1
                    /** element[0][0] is on the diagonal, so setting it to 1 is
                     *  what we need in a unity matrix                        */
                    static void row_loop (N a[D][D]) {
                        a[0][0] = (N)1;
                    }
                    /// Sets element[0][0] to 1
                    /** element[0][0] is on the diagonal, so setting it to 1 is
                     *  what we need in a unity matrix                        */
                    static void col_loop (N a[D][D]) {
                        a[0][0] = (N)1;
                    }
            };

            /// Calculate an element of the product of two matrices
            /** Inner loop of a matrix multiplication \n
             *  Summation over the product of corresponding row and column
             *  elements to calculate one element of the product of two
             *  matrices. \n
             *  The loop() function in this class loops over all rows and
             *  columns of two matrices, then for all elements multiplies
             *  the row vector corresponding to the first matrix's element
             *  with the column vector of the second matrix's element,
             *  necessitating a third, inner, loop.                           */
            template <unsigned i, unsigned j, unsigned k, unsigned D_>
                struct MultiplyInnerLoop {
                    static void loop (const N a[D][D], const N b[D][D], N c[D][D]);
            };

            /// Calculate an element of the product of two matrices
            /** Inner loop of a matrix multiplication \n
             *  Specialization for \p k = 0 (the first element of the row
             *  vector by col vector multiplication).                         */
            template <unsigned i, unsigned j, unsigned D_>
                struct MultiplyInnerLoop<i, j, 0, D_> {
                    static void loop (const N a[D][D], const N b[D][D], N c[D][D]);
            };

            /// Calculate one row of the product of two matrices
            /** Loop over the columns of two matrices to multiply them in
             *  loop()                                                        */
            template <unsigned i, unsigned j, unsigned D_>
                struct MultiplyColLoop {
                    static void loop (const N a[D][D], const N b[D][D], N c[D][D]);
            };

            /// Calculate one row of the product of two matrices
            /** Loop over the columns of two matrices to multiply them in
             *  loop() \n
             *  Specialization for \p j = 0       */
            template <unsigned i, unsigned D_>
                struct MultiplyColLoop<i, 0, D_> {
                    static void loop (const N a[D][D], const N b[D][D], N c[D][D]);
            };

            /// Loop over the rows of two matrices to multiply them in loop()
            template <unsigned i, unsigned D_>
                struct MultiplyRowLoop {
                    static void loop (const N a[D][D], const N b[D][D], N c[D][D]);
            };

            /// Calculate the product of two matrices looping over all rows
            /** Loop over the rows of two matrices to multiply them in loop() \n
             *  Specialization for \p i = 0       */
            template <unsigned D_>
                struct MultiplyRowLoop<0, D_> {
                    static void loop (const N a[D][D], const N b[D][D], N c[D][D]);
            };

            /// Multiply two matrices in the function multiply()
            /** */
            template <unsigned D_>
                struct Multiply {
                    static void multiply (const N a[D][D], const N b[D][D], N c[D][D]);
            };

#           if 0
                template<unsigned D_>
                    struct Det {
                        static N det (/*const*/ N a[D][D]);
                };

                template<>
                    struct Det<1> {
                        static N_ det (/*const*/ N_ a[1][1]);
                };

                template<unsigned D_, int i>
                    struct SumLoop {
                        static N sumloop (/*const*/ N a[D][D]);
                };

                template<unsigned D_>
                    struct SumLoop <D_, 0> {
                        static N sumloop (/*const*/ N a[D][D]);
                };

                template<>
                    struct SumLoop <0, 0> {
                        static N_ sumloop (const N a[1][1]);
                };

                template<unsigned i, unsigned j, unsigned D_>
                    struct Minor {
                        static N **minor (/*const*/ N a[D][D]) {
                            throw NotYetImplementedException (
                                "Minor<i, j, D, N>::minor (N **)");
                        }
                };

                template<unsigned k, unsigned D_>
                    struct MinorLoop {
                        static void minorloop (N ** a, N **tmp);
                };

                template<unsigned D_>
                    struct MinorLoop<1, D_> {
                        static void minorloop (N ** a, N **tmp);
                };

                template<unsigned i, unsigned D_>
                    struct Minor<i, 0, D_> {
                        static /*const*/ N **minor (/*const*/ N **a);
                };

                template<unsigned i>
                    struct Minor<i, 0, 0> {
                        static N **minor (/*const*/ N **a) { return a; }
                };

#           endif

            /// Copy a matrix to another, element by element
            /** A template metaprogramming version of a copy loop is necessary
             *  to make sure that the compiler knows all elements of the
             *  matrix.                                                       */
            template<unsigned i, unsigned j, unsigned D_>
                struct CopyLoop {
                    static void copy_row (N from[D][D], N to[D][D]);
                    static void copy_col (N from[D][D], N to[D][D]);
            };
            /// Copy a matrix to another, element by element
            /** Specialization for row = 0 */
            template<unsigned j, unsigned D_>
                struct CopyLoop<0, j, D_> {
                    static void copy_row (N from[D][D], N to[D][D]);
                    static void copy_col (N from[D][D], N to[D][D]);
            };
            /// Copy a matrix to another, element by element
            /** Specialization for column = 0 */
            template<unsigned i, unsigned D_>
                struct CopyLoop<i, 0, D_> {
                    static void copy_col (N from[D][D], N to[D][D]);
            };
            /// Copy a matrix to another, element by element
            /** Specialization for row = 0, column = 0 */
            template<unsigned D_>
                struct CopyLoop<0, 0, D_> {
                    static void copy_col (N from[D][D], N to[D][D]);
            };

            /// A static two-dimensional array storing the components
            N data_[D][D];
    };
}


////////////////////////////////////////////////////////////////////////////////
////                                                                        ////
////        END DECLARATION, BEGIN DEFINITIONS                              ////
////                                                                        ////
////////////////////////////////////////////////////////////////////////////////


/// Construct a unity matrix
/** @param D dimension of the matrix
 *  @param N (Numeric) type of the elements */
template<unsigned D, typename N>
    inline VecMath::Matrix<D, N>::Matrix() {
        ConstructLoop<D, D-1, D-1>::row_loop (data_);
    }

/// Construct a rotation matrix
/** For the rotation angle alpha around the axis defined by \p axis1 and
 *  \p axis2. \n
 *  e.g. in 3 dimensions: \p axis1 = 1, \p axis2 = 2 => rotation around
 *  dimension 0 ( = \em x -axis)
 *  @param axis1 first dimension to define the rotation direction
 *  @param axis2 first dimension to define the rotation direction
 *  @param alpha rotation angle
 *  @param D dimension of the matrix
 *  @param N (Numeric) type of the elements                                   */
template<unsigned D, typename N>
    inline VecMath::Matrix<D, N>::Matrix(unsigned axis1, unsigned axis2, N alpha) {
        // costruct a unity matrix first
        ConstructLoop<D, D-1, D-1>::row_loop (data_);
        // then replace the appropriate elements by sin/cos of the rotation angle
        N s = sin (alpha), c = cos (alpha);
        data_[axis1][axis1] =  data_[axis2][axis2] = c;
        data_[axis1][axis2] = -s;
        data_[axis2][axis1] = s;

      }

/// Construct a randomized matrix
/** construct a unity matrix, if \p random == false, otherwise a matrix filled
 *  with random elements between (\p N)0 and (\p N)1
 *  @param random whether to fill matrix randomly
 *  @param D dimension of the matrix
 *  @param N (Numeric) type of the elements                                   */
template<unsigned D, typename N>
    inline VecMath::Matrix<D, N>::Matrix(bool random) {
        if (random) {
            for(unsigned i = 0; i < D; i++) {
                for (unsigned j = 0; j < D; j++)
                    data_[i][j] = random? N (rand ())/RAND_MAX: 0;
                if (!random) data_[i][i] = 1;
            }
        }
        else {
            ConstructLoop<D, D-1, D-1>::row_loop (data_);
        }
    }

/// construct a matrix from a two-dimensional array of \p N 's
/** @param a[][] array elements to initialize matrix
 *  @param D dimension of the matrix
 *  @param N (Numeric) type of the elements                                   */
template<unsigned D, typename N>
    VecMath::Matrix<D, N>::Matrix (const N a[D][D]) {
        CopyLoop<D-1, D-1, D>::copy_row (a, data_);
    }


/// construct a matrix from a one-dimensional array of \p N 's
/** this matrix will very probably not use the blessings and optimizations
 *  of template metaprogramming, because the compiler cannot see its contents
 *  @param a[] array elements to initialize matrix
 *  @param D dimension of the matrix
 *  @param N (Numeric) type of the elements                                   */
template<unsigned D, typename N>
    VecMath::Matrix<D, N>::Matrix (const N *a) {
        for (unsigned i = 0; i < D; i++)
            for (unsigned j = 0; j < D; j++)
                data_[i][j] = a[i*D+j];
    }

/// Const access operator
/** \param i row index
 *  \param j column index */
template<unsigned D, typename N>
    inline N
        VecMath::Matrix<D, N>::operator() (unsigned i, unsigned j) const {
            assert (i < D);
            assert (j < D);
            return data_[i][j];
        }

/// Non-const access operator
/** \param i row index
 *  \param j column index */
template<unsigned D, typename N>
    inline N &
        VecMath::Matrix<D, N>::operator() (unsigned i, unsigned j) {
            assert (i < D);
            assert (j < D);
            return data_[i][j];
        }

/// Matrix multiplication
/** Uses the class static function Multiply<D>::multiply() to do the loop over
 *  the elements and perform the multiplications. \n
 *  Does not change \em this.
 *  \return \em this multiplied by \p other
 *  \param other The matrix with which to multiply \em this                   */
template<unsigned D, typename N>
    inline VecMath::Matrix<D, N>
        VecMath::Matrix<D, N>::operator* (const Matrix<D, N>& other) {
            Matrix<D, N> tmp;
            Multiply<D>::multiply (data_, other.data_, tmp.data_);
            return tmp;
        }

/// Matrix multiplication
/** Uses the class static function Multiply<D>::multiply() to do the loop over
 *  the elements and perform the multiplications.\n
 *  Replaces \em this with \em this * \p other
 *  \param other The matrix with which to multiply \em this                   */
template<unsigned D, typename N>
    inline VecMath::Matrix<D, N>
    VecMath::Matrix<D, N>::operator*= (const Matrix<D, N>& other) {
        Matrix<D, N> tmp (*this);
        Multiply<D>::multiply (tmp.data_, other.data_, data_);
        return *this;
     }

/// Apply the Matrix on a vector
/** \todo use template metaprogramming here too
 *  @param V Vector to multiply with (project)
 *  @return *this * V                                                     */
template <unsigned D, typename N>
    VecMath::Vector<D, N>
    VecMath::Matrix<D, N>::operator * (const VecMath::Vector<D, N> &V) {
        Vector<D, N> W;
        for (unsigned i = 0; i < D; i++) {                              //      i: row
            N s = 0;
            for (unsigned j = 0; j < D; j++)                    //      j: col
                s += data_[i][j]*V[j];
            W[i] = s;
        }
        return W;
    }

/// Print the matrix on \p std::cout
/** \todo flexible output stream
 *  \todo flexible printing format  */
template<unsigned D, typename N>
    void
        VecMath::Matrix<D, N>::print () {
            std::cout << D << "x" << D << ":";
            for (unsigned i = 0; i < D; i++) {
                std::cout << (i > 0? " |": "") << std::endl << "|";
                for (unsigned j = 0; j < D; j++)
                    std::cout << std::setw (6) << std::setprecision (3)
                              << operator ()(i, j);
            }
            std::cout << " |" << std::endl;
        }


////////////////////////////////////////////////////////////////////////////////
////                                                                        ////
////        DEFINITION ConstructLoop AND ITS SPECIALIZATIONS                ////
////                                                                        ////
////////////////////////////////////////////////////////////////////////////////


/// Initialize a matrix to unity
/** Loop over all rows calling the column loop for each row, then calls
 *  itself again with a decreased row number.
 *  @param a the matrix (two-dimensional array) to initialize
 *  @param i current row to initialize
 *  @param j current column to initialize
 *  @param D_ dimension of the matrix (dummy parameter)
 *  @param D dimension of the matrix (encapsulating generic type Matrix)
 *  @param N Numeric type (encapsulating generic type Matrix)             */
template<unsigned D, typename N>
    template<unsigned D_, unsigned i, unsigned j>
        inline void
        VecMath::Matrix<D, N>::ConstructLoop<D_, i, j>::row_loop (N a[D][D]) {
            ConstructLoop<D, i, j>::col_loop(a);
            ConstructLoop<D, i-1, j>::row_loop(a);
        }

/// Initialize a matrix row to unity vector
/** Loop over all columns of a row setting current element either to 0 or 1. \n
 *  Calls itself again with a column number decreased by one.
 *  @param a the matrix (two-dimensional array) to initialize
 *  @param i current row to initialize
 *  @param j current column to initialize
 *  @param D_ dimension of the matrix (dummy parameter)
 *  @param D dimension of the matrix (encapsulating generic type Matrix)
 *  @param N Numeric type (encapsulating generic type Matrix)             */
template<unsigned D, typename N>
    template<unsigned D_, unsigned i, unsigned j>
        inline void
        VecMath::Matrix<D, N>::ConstructLoop<D_, i, j>::col_loop (N a[D][D]) {
            ConstructLoop<D, i, j-1>::col_loop(a);
            a[i][j] = (i == j? (N)1: (N)0);
        }

/// Initialize a matrix to unity
/** Loop over all rows calling the column loop for each row \n
 *  Specialization for the first row, does not call row_loop() for a
 *  decreased row number
 *  @param a the matrix (two-dimensional array) to initialize
 *  @param j current column to initialize
 *  @param D_ dimension of the matrix (dummy parameter)
 *  @param D dimension of the matrix (encapsulating generic type Matrix)
 *  @param N Numeric type (encapsulating generic type Matrix)             */
template<unsigned D, typename N>
    template <unsigned D_, unsigned j>
        inline void
        VecMath::Matrix<D, N>::ConstructLoop<D_, 0, j>::row_loop (N a[D][D]) {
            ConstructLoop<D, 0, j>::col_loop(a);
        }


/// Initialize a matrix to unity
/** Loop over all columns - specialization for the first row
 *  @param a the matrix (two-dimensional array) to initialize
 *  @param j current column to initialize
 *  @param D_ dimension of the matrix (dummy parameter)
 *  @param D dimension of the matrix (encapsulating generic type Matrix)
 *  @param N Numeric type (encapsulating generic type Matrix)             */
template<unsigned D, typename N>
    template <unsigned D_, unsigned j>
        inline void
        VecMath::Matrix<D, N>::ConstructLoop<D_, 0, j>::col_loop (N a[D][D]) {
            ConstructLoop<D, 0, j-1>::col_loop(a);
            a[0][j] = (j == 0? (N)1: (N)0);
        }


/// initialize a matrix to unity
/** loop over all rows - specialization for the first column
 *  @param a the matrix (two-dimensional array) to initialize
 *  @param i current row to initialize
 *  @param D_ dimension of the matrix (dummy parameter)
 *  @param D dimension of the matrix (encapsulating generic type Matrix)
 *  @param N Numeric type (encapsulating generic type Matrix)             */
template<unsigned D, typename N>
    template <unsigned D_, unsigned i>
        inline void
        VecMath::Matrix<D, N>::ConstructLoop<D_, i, 0>::row_loop (N a[D][D]) {
            ConstructLoop<D, i, 0>::col_loop(a);
            ConstructLoop<D, i-1, 0>::row_loop(a);
        }


/// Initialize a matrix to unity
/** Loop over all columns - specialization for the first column
 * @param a the matrix (two-dimensional array) to initialize
 * @param i current row to initialize
 * @param D_ dimension of the matrix (dummy parameter)
 * @param D dimension of the matrix (encapsulating generic type Matrix)
 * @param N Numeric type (encapsulating generic type Matrix)
 */
template<unsigned D, typename N>
    template <unsigned D_, unsigned i>
        inline void
        VecMath::Matrix<D, N>::ConstructLoop<D_, i, 0>::col_loop (N a[D][D]) {
            a[i][0] = (i == 0? (N)1: (N)0);
        }



////////////////////////////////////////////////////////////////////////////////
////                                                                        ////
////        VecMath::Matrix<D, N>::MultiplyInnerLoop<i, j, k, D_>           ////
////                                                                        ////
////////////////////////////////////////////////////////////////////////////////

/// calculate \f$ C_ij \f$ of \f$ C = A*B \f$
/** @param a left operand of \f$ A*B \f$
 *  @param b right operand of \f$ A*B \f$
 *  @param c resulting matrix
 *  @param i row of desired element
 *  @param j column of desired element
 *  @param k summation index
 *  @param D_ dimension of the matrix (dummy parameter)
 *  @param D dimension of the matrix (encapsulating generic type Matrix)
 *  @param N Numeric type (encapsulating generic type Matrix)                */
template<unsigned D, typename N>
    template <unsigned i, unsigned j, unsigned k, unsigned D_>
    inline void
    VecMath::Matrix<D, N>::MultiplyInnerLoop<i, j, k, D_>::loop (
            const N a[D][D], const N b[D][D], N c[D][D]) {
        c[i][j] += a[i][k]*b[k][j];
        MultiplyInnerLoop<i, j, k-1, D>::loop (a, b, c);
      }


/// calculate first term of the sum for \f$ C_ij \f$ of \f$ C = A*B \f$
/** @param a left operand of \f$ A*B \f$
 *  @param b right operand of \f$ A*B \f$
 *  @param c resulting matrix
 *  @param i row of desired element
 *  @param k summation index
 *  @param D_ dimension of the matrix (dummy parameter)
 *  @param D dimension of the matrix (encapsulating generic type Matrix)
 *  @param N Numeric type (encapsulating generic type Matrix)              */
template<unsigned D, typename N>
    template <unsigned i, unsigned j, unsigned D_>
        inline void
        VecMath::Matrix<D, N>::MultiplyInnerLoop<i, j, 0, D_>::loop (
                const N a[D][D], const N b[D][D], N c[D][D]) {
        c[i][j] += a[i][0]*b[0][j];
      }


////////////////////////////////////////////////////////////////////////////////
////                                                                        ////
////        VecMath::Matrix<D, N>::MultiplyColLoop<i, j, D_>                ////
////                                                                        ////
////////////////////////////////////////////////////////////////////////////////


/// Calculate row \p i of \f$ C = A*B \f$
/** @param a left operand of \f$ A*B \f$
 *  @param b right operand of \f$ A*B \f$
 *  @param c resulting matrix
 *  @param i row of desired element
 *  @param j loop index - column of desired element
 *  @param D_ dimension of the matrix (dummy)
 *  @param D dimension of the matrix (encapsulating generic type Matrix)
 *  @param N Numeric type (encapsulating generic type Matrix)                 */
template<unsigned D, typename N>
    template <unsigned i, unsigned j, unsigned D_>
        inline void
        VecMath::Matrix<D, N>::MultiplyColLoop<i, j, D_>::loop (
                const N a[D][D], const N b[D][D], N c[D][D]) {
            c[i][j] = 0;
            MultiplyInnerLoop<i, j, D-1, D>::loop (a, b, c);
            MultiplyColLoop<i, j-1, D>::loop (a, b, c);
        }

/// calculate first element (\p j == 0) of row \p i of \f$ C = A*B \f$
/** @param a left operand of \f$ A*B \f$
 * @param b right operand of \f$ A*B \f$
     * @param c resulting matrix
     * @param i row of desired element
     * @param D_ dimension of the matrix (dummy)
     * @param D dimension of the matrix (encapsulating generic type Matrix)
     * @param N Numeric type (encapsulating generic type Matrix)   */
template<unsigned D, typename N>
    template <unsigned i, unsigned D_>
        inline void
        VecMath::Matrix<D, N>::MultiplyColLoop<i, 0, D_>::loop (
                const N a[D][D], const N b[D][D], N c[D][D]) {
            c[i][0] = 0;
            MultiplyInnerLoop<i, 0, D-1, D>::loop (a, b, c);
        }


////////////////////////////////////////////////////////////////////////////////
////                                                                        ////
////        VecMath::Matrix<D, N>::MultiplyRowLoop<i, D_>                   ////
////                                                                        ////
////////////////////////////////////////////////////////////////////////////////


/** @param a left operand of \f$ A*B \f$
 *  @param b right operand of \f$ A*B \f$
 *  @param c resulting matrix
 *  @param i loop index - row of desired element
 *  @param D_ dimension of the matrix (dummy)
 *  @param D dimension of the matrix (encapsulating generic type Matrix)
 *  @param N Numeric type (encapsulating generic type Matrix)                */
template<unsigned D, typename N>
    template <unsigned i, unsigned D_>
        inline void
        VecMath::Matrix<D, N>::MultiplyRowLoop<i, D_>::loop (
                const N a[D][D], const N b[D][D], N c[D][D]) {
            MultiplyColLoop<i, D-1, D>::loop (a, b, c);
            MultiplyRowLoop<i-1, D>::loop (a, b, c);
        }

/** first row of the loop over all rows
 * @param a left operand of \f$ A*B \f$
 * @param b right operand of \f$ A*B \f$
 * @param c resulting matrix
 * @param D_ dimension of the matrix (dummy)
 * @param D dimension of the matrix (encapsulating generic type Matrix)
 * @param N Numeric type (encapsulating generic type Matrix)        */
template<unsigned D, typename N>
    template <unsigned D_>
        inline void
        VecMath::Matrix<D, N>::MultiplyRowLoop<0, D_>::loop (
            const N a[D][D], const N b[D][D], N c[D][D]) {
            MultiplyColLoop<0, D-1, D>::loop (a, b, c);
        }

////////////////////////////////////////////////////////////////////////////////
////                                                                        ////
////        VecMath::Matrix<D, N>::Multiply<D_>                             ////
////                                                                        ////
////////////////////////////////////////////////////////////////////////////////


/** @param a left operand of \f$ A*B \f$
 * @param b right operand of \f$ A*B \f$
 * @param c resulting matrix
 * @param D_ dimension of the matrix (dummy)
 * @param D dimension of the matrix (encapsulating generic type Matrix)
 * @param N Numeric type (encapsulating generic type Matrix)                  */

template<unsigned D, typename N>
    template <unsigned D_>
        inline void
        VecMath::Matrix<D, N>::Multiply<D_>::multiply (
            const N a[D][D], const N b[D][D], N c[D][D]) {
            MultiplyRowLoop<D-1, D>::loop (a, b, c);
        }

#if 0

template<unsigned D, typename N>
  Matrix<D-1, N>
    VecMath::Matrix<D, N>::matrix_minor (unsigned i, unsigned j) {
      throw new NotYetImplementedException ();
      Matrix<D-1, N> tmp;
      for (unsigned I = 0, II = 0; I < D; I++)
        if (I != i) {
        for (unsigned J = 0, JJ = 0; J < D; J++)
          if (J != j) {
          tmp (II, JJ) = *this (I, J);
          JJ++;
          }
          II++;
        }
        return tmp;
  }

template<unsigned D, typename N>
  template<unsigned D_>
    inline N
      VecMath::Matrix<D, N>::Det<D_>::det (/*const*/ N a[D][D]) {
        return SumLoop<D, D-1>::sumloop (a);
      }

template<unsigned D, typename N>
  template<typename N_>
    inline N_
      VecMath::Matrix<D, N>::Det<1, N_>::det (/*const*/ N_ a[1][1]) {
        return a[0][0];
      }

template<unsigned D, typename N>
  template<unsigned D_, int i>
    inline N
      VecMath::Matrix<D, N>::SumLoop<D_, i>::sumloop (/*const*/ N a[D][D])  {
        N **tmp1 = Minor<i, 0, D>::minor(a);
        N tmp2 = a[i][0]
                  * Det<D-1>::det(tmp1)
                  * ( (i&1)? -1: 1 )
                  + SumLoop<D, i-1>::sumloop (a);
        delete[] tmp1;
        return tmp2;
      }

template<unsigned D, typename N>
  template<unsigned D_>
    inline N
      VecMath::Matrix<D, N>::SumLoop<D_, 0>::sumloop (/*const*/ N a[D][D]) {
        N **tmp1 = Minor<0, 0, D_>::minor (a);
        N tmp2 = a[0][0] * Det<D-1>::det (tmp1);
        delete [] tmp1;
        return tmp2;
      }
/*
template<unsigned D, typename N>
  template<typename N_>
    inline N_
      VecMath::Matrix<D, N>::SumLoop <0, 0, N_>::sumloop (const N_ a[1][1]) {
        return a[0][0];
      }
*/
template<unsigned D, typename N>
    template<unsigned k, unsigned D_>
        inline void
            VecMath::Matrix<D, N>::MinorLoop<k, D_>::minorloop (N ** a, N **tmp) {
              tmp[k-1] = a[k]+1;
              MinorLoop<k-1, D>::minorloop (a, tmp);
          }

template<unsigned D, typename N>
    template<unsigned D_>
        inline void
            VecMath::Matrix<D, N>::MinorLoop<1, D_>::minorloop (N ** a, N **tmp) {
              tmp[0] = a[1]+1;
            }

template<unsigned D, typename N>
    template<unsigned i, unsigned D_>
        inline /*const*/ N **
            VecMath::Matrix<D, N>::Minor<i, 0, D_>::minor (/*const*/ N **a) {
              /*const*/ N **tmp = new /*const*/ N* [D-1];  //  watch out for memory leaks here!
                                                        //  the caller must free this memory!
              for (unsigned k = 1; k < D; k++)
                tmp[k-1] = a[k]+1;
              //    MinorLoop<D-1, D>::minorloop (a, tmp);
              return tmp;
            }
#endif    //  0

/// Copies a row of a matrix to another matrix
/** Calls itself with decreased row index   */
template<unsigned D, typename N>
    template<unsigned i, unsigned j, unsigned D_>
        inline void
        VecMath::Matrix<D, N>::CopyLoop<i, j, D_>::copy_row (
                N from[D][D], N to[D][D]) {
            CopyLoop<i-1, j, D>::copy_row (from, to);
            CopyLoop<i, j, D>::copy_col (from, to);
        }

/// Copies a column of a matrix to another matrix
/** Calls itself with decreased column index   */
template<unsigned D, typename N>
    template<unsigned i, unsigned j, unsigned D_>
        inline void
        VecMath::Matrix<D, N>::CopyLoop<i, j, D_>::copy_col (
                N from[D][D], N to[D][D]) {
            to[i][j] = from[i][j];
            CopyLoop<i, j-1, D>::copy_col (from, to);
        }

/// Copies a row of a matrix to another matrix
/** Specialization for row = 0                                                */
template<unsigned D, typename N>
    template<unsigned j, unsigned D_>
        inline void
        VecMath::Matrix<D, N>::CopyLoop<0, j, D_>::copy_row (
                N from[D][D], N to[D][D]) {
            CopyLoop<0, j, D>::copy_col (from, to);
        }

/// Copies a column of a matrix to another matrix
/** Specialization for row = 0                                                */
template<unsigned D, typename N>
    template<unsigned j, unsigned D_>
        inline void
        VecMath::Matrix<D, N>::CopyLoop<0, j, D_>::copy_col (
                N from[D][D], N to[D][D]) {
            to[0][j] = from[0][j];
            CopyLoop<0, j-1, D>::copy_col (from, to);
        }

/// Copies a column of a matrix to another matrix
/** Specialization for column = 0                                             */
template<unsigned D, typename N>
    template<unsigned i, unsigned D_>
        inline void
        VecMath::Matrix<D, N>::CopyLoop<i, 0, D_>::copy_col (
                N from[D][D], N to[D][D]) {
            to[i][0] = from[i][0];
        }

/// Copies a column of a matrix to another matrix
/** Specialization for row = 0, column = 0                                    */
template<unsigned D, typename N>
    template<unsigned D_>
        inline void
        VecMath::Matrix<D, N>::CopyLoop<0, 0, D_>::copy_col (
                N from[D][D], N to[D][D]) {
            to[0][0] = from[0][0];
        }

#endif    // #ifdef MATRIX_H
