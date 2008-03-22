
#if !defined(MATRIX_H)
#define MATRIX_H

#include <cassert>

#include <iostream>
#include <iomanip>
#include <string>


/** a matrix class speeding up matrix multiplications by using template
 *  metaprogramming to let the compiler unroll and optimize the multiplication
 *  loops
 *
    \todo{

    - why does the 100 fold speed increase come and go? why does it only work
      for dimensions up to 4?
      some clue:
      when print() is called after NLOOP multiplications, runtime performance
      drops significantly. this is the case for templatized version as well as
      with the for loop. roughly speaking, print() incurs an overhead of a
      second for both versions. funny thing is, print () is called AFTER the
      timing has taken place.
      the performance drop with print() has vanished after getting the
      initialization correct (looping from D-1 to 0 instead of looping from D)
      err well, this in not true... it has only vanished *sometimes*. I assume
      that gcc does the calculations only

    - a corresponding vector class and member function for transformation of
      vectors

    - const-correctness everywhere

    - templatize copy loop in Matrix (/*const// N a[D][D])

    - drop D_ as template parameter for inner classes where possible
      there is a problem with specializations in inner classes, which don't
      have any template parameters at all:

          template <>                                                 // error!
            struct ConstructLoop<0, 0> {
              static void row_loop (N a[D][D]) { a[0][0] = (N)1; }

      workaround <news:718f76ba.0305081256.6969e6ae@posting.google.com>

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

    - specializations of inner classes - do they really have to be declared?
      (seems so)

      whittle them down to the bare minimum anyways
    }
*/

namespace VecMath2 {
    struct NotYetImplementedException {
    NotYetImplementedException (std::string what) {
        std::cerr << what << ": Not yet implemented!" << std::endl;
    }
    };


    template<unsigned D, typename N = double>
    class Matrix {

    public:
    Matrix();
    Matrix(unsigned axis1, unsigned axis2, N alpha);
    Matrix(bool random);
    Matrix (const N a[D][D]);
    Matrix (const N *a);

    N  operator() (unsigned i, unsigned j) const;
    N &operator() (unsigned i, unsigned j);

    Matrix<D, N> operator*  (const Matrix<D, N>& other);
    Matrix<D, N> operator*= (const Matrix<D, N>& other);

    void print ();

    # if 0
    N det (){ return Det<D>::det (data_); }
    Matrix<D-1, N> matrix_minor (unsigned i, unsigned j);
    #endif


    private:
    /** initialization of a unity DxD matrix
        */
    template<unsigned D_, unsigned i, unsigned j>
    struct ConstructLoop {
        static void row_loop (N a[D][D]);
        static void col_loop (N a[D][D]);
    };

    /**
    */
    template <unsigned D_, unsigned j>
    struct ConstructLoop<D_, 0, j> {
        static void row_loop (N a[D][D]);
        static void col_loop (N a[D][D]);
    };

    /**
    */
    template <unsigned D_, unsigned i>
    struct ConstructLoop<D_, i, 0> {
        static void row_loop (N a[D][D]);
        static void col_loop (N a[D][D]);
    };

    template <unsigned D_>
        struct ConstructLoop<D_, 0, 0> {
        static void row_loop (N a[D][D]) {
    #     if (DEBUG)
            cerr << "Matrix<" << D << ">::ConstructLoop<" << D_ << ", "
                << 0 << ", " << 0 << ">::row_loop () : " << 1 << endl;
    #     endif
        a[0][0] = (N)1;
        }
        static void col_loop (N a[D][D]) {
    #     if (DEBUG)
            cerr << "Matrix<" << D << ">::ConstructLoop<" << D_ << ", "
                << 0 << ", " << 0 << ">::col_loop () : " << 1<< endl;
    #     endif
        a[0][0] = (N)1;
        }
    };

    /**
    */
    template <unsigned i, unsigned j, unsigned k, unsigned D_>
    struct MultiplyInnerLoop {
        static void loop (const N a[D][D], const N b[D][D], N c[D][D]);
    };

    /**
    */
    template <unsigned i, unsigned j, unsigned D_>
    struct MultiplyInnerLoop<i, j, 0, D_> {
        static void loop (const N a[D][D], const N b[D][D], N c[D][D]);
    };

    /**
    */
    template <unsigned i, unsigned j, unsigned D_>
    struct MultiplyColLoop {
        static void loop (const N a[D][D], const N b[D][D], N c[D][D]);
    };

    /**
    */
    template <unsigned i, unsigned D_>
    struct MultiplyColLoop<i, 0, D_> {
        static void loop (const N a[D][D], const N b[D][D], N c[D][D]);
    };

    /**
    */
    template <unsigned i, unsigned D_>
    struct MultiplyRowLoop {
        static void loop (const N a[D][D], const N b[D][D], N c[D][D]);
    };

    /**
    */
    template <unsigned D_>
    struct MultiplyRowLoop<0, D_> {
        static void loop (const N a[D][D], const N b[D][D], N c[D][D]);
    };

    /**
    */
    template <unsigned D_>
    struct Multiply {
        static void multiply (const N a[D][D], const N b[D][D], N c[D][D]);
    };

    #if 0
    template<unsigned D_>
    struct Det {
        static N det (/*const*/ N a[D][D]);
    };
    /*
    template<>
    struct Det<1> {
        static N_ det (/*const// N_ a[1][1]);
    };
    */
    template<unsigned D_, int i>
    struct SumLoop {
        static N sumloop (/*const*/ N a[D][D]);
    };

    template<unsigned D_>
    struct SumLoop <D_, 0> {
        static N sumloop (/*const*/ N a[D][D]);
    };
    /*
    template<>
    struct SumLoop <0, 0> {
        static N_ sumloop (const N a[1][1]);
    };
    */
    template<unsigned i, unsigned j, unsigned D_>
    struct Minor {
        static N **minor (/*const*/ N a[D][D]) {
        throw NotYetImplementedException ("Minor<i, j, D, N>::minor (N **)");
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

    #endif

    template<unsigned i, unsigned j, unsigned D_>
    struct CopyLoop {
        static void copy_row (N from[D][D], N to[D][D]);
        static void copy_col (N from[D][D], N to[D][D]);
    };
    template<unsigned j, unsigned D_>
    struct CopyLoop<0, j, D_> {
        static void copy_row (N from[D][D], N to[D][D]);
        static void copy_col (N from[D][D], N to[D][D]);
    };
    template<unsigned i, unsigned D_>
    struct CopyLoop<i, 0, D_> {
        static void copy_col (N from[D][D], N to[D][D]);
    };
    template<unsigned D_>
    struct CopyLoop<0, 0, D_> {
        static void copy_col (N from[D][D], N to[D][D]);
    };


    N data_[D][D];
    };
}


/**
 *  VecMath2::Matrix<D, N>::Matrix()
 *  construct a unity matrix
 *  @param D dimension of the matrix
 *  @param N (Neric) type of the elements
 */
template<unsigned D, typename N>
  inline VecMath2::Matrix<D, N>::Matrix() {
    ConstructLoop<D, D-1, D-1>::row_loop (data_);
  }


/**
 *  VecMath2::Matrix<D, N>::Matrix(axis1, axis2, alpha)
 *  construct a rotation matrix for the rotation angle alpha around the axis
 *  defined by axis1 and axis2
 *  e.g. in 3 dimensions: axis1 = 1, axis2 = 2 => rotation around dimension 0
 *  ( = x-axis)
 *  @param axis1 first dimension to define the rotation direction
 *  @param axis2 first dimension to define the rotation direction
 *  @param alpha rotation angle
 *  @param D dimension of the matrix
 *  @param N (Neric) type of the elements
 */
template<unsigned D, typename N>
    inline VecMath2::Matrix<D, N>::Matrix(unsigned axis1, unsigned axis2, N alpha) {
        ConstructLoop<D, D-1, D-1>::row_loop (data_);
        N s = sin (alpha), c = cos (alpha);
        data_[axis1][axis1] =  data_[axis2][axis2] = c;
        data_[axis1][axis2] = -s;
        data_[axis2][axis1] = s;

      }


/**
 *  VecMath2::Matrix<D, N>::Matrix(random)
 *  construct a unity matrix, if random == false, otherwise a matrix filled
 *  with random elements between (N)0 and (N)1
 *  @param random whether to fill matrix randomly
 *  @param D dimension of the matrix
 *  @param N (Neric) type of the elements
 */
template<unsigned D, typename N>
  inline VecMath2::Matrix<D, N>::Matrix(bool random) {
    if (random) {
      for(unsigned i = 0; i < D; i++) {
        for (unsigned j = 0; j < D; j++) data_[i][j] = random? N (rand ())/RAND_MAX: 0;
        if (!random) data_[i][i] = 1;
      }
    }
    else {
      ConstructLoop<D, D-1, D-1>::row_loop (data_);
    }
  }


/**
 *  VecMath2::Matrix<D, N>::Matrix(a[D][D])
 *  construct a matrix from a two-dimensional array of N's
 *  @param a[][] array elements to initialize matrix
 *  @param D dimension of the matrix
 *  @param N (Neric) type of the elements
 */
template<unsigned D, typename N>
    VecMath2::Matrix<D, N>::Matrix (const N a[D][D]) {
      CopyLoop<D-1, D-1, D>::copy_row (a, data_);
    }


/**
 *  VecMath2::Matrix<D, N>::Matrix(a[])
 *  construct a matrix from a one-dimensional array of N's
 *  this matrix will very probably not use the blessings and optimizations
 *  of template metaprogramming, because the compiler cannot see its contents
 *  @param a[] array elements to initialize matrix
 *  @param D dimension of the matrix
 *  @param N (Neric) type of the elements
 */
template<unsigned D, typename N>
  VecMath2::Matrix<D, N>::Matrix (const N *a) {
    for (unsigned i = 0; i < D; i++)
      for (unsigned j = 0; j < D; j++)
        data_[i][j] = a[i*D+j];
  }


template<unsigned D, typename N>
  inline N
    VecMath2::Matrix<D, N>::operator() (unsigned i, unsigned j) const {
      assert (i < D);
      assert (j < D);
      return data_[i][j];
    }


template<unsigned D, typename N>
  inline N &
    VecMath2::Matrix<D, N>::operator() (unsigned i, unsigned j) {
      assert (i < D);
      assert (j < D);
      return data_[i][j];
    }


template<unsigned D, typename N>
    inline VecMath2::Matrix<D, N>
    VecMath2::Matrix<D, N>::operator* (const Matrix<D, N>& other) {
      Matrix<D, N> tmp;
      Multiply<D>::multiply (data_, other.data_, tmp.data_);
      return tmp;
    }

template<unsigned D, typename N>
    inline VecMath2::Matrix<D, N>
    VecMath2::Matrix<D, N>::operator*= (const Matrix<D, N>& other) {
      Matrix<D, N> tmp (*this);
      Multiply<D>::multiply (tmp.data_, other.data_, data_);
      return *this;
    }

template<unsigned D, typename N>
  void
    VecMath2::Matrix<D, N>::print () {
      std::cout << D << "x" << D << ":";
      for (unsigned i = 0; i < D; i++) {
        std::cout << (i > 0? " |": "") << std::endl << "|";
        for (unsigned j = 0; j < D; j++)
          std::cout << std::setw (6) << std::setprecision (3)
                    << operator ()(i, j);
      }
      std::cout << " |" << std::endl;
    }


    /**
     * VecMath2::Matrix<D, N>::ConstructLoop<D_, i, j>
     * construction of a unity matrix with values which are known to the
     * compiler
     * functions and specializations for i == 0 and j == 0
     */

    /**
     * VecMath2::Matrix<D, N>::ConstructLoop<D_, i, j>::row_loop (N a[D][D])
     * initialize a matrix to unity
     * loop over all rows calling the column loop for each row
     * @param a the matrix (two-dimensional array) to initialize
     * @param i current row to initialize
     * @param j current column to initialize
     * @param D_ dimension of the matrix (dummy parameter)
     * @param D dimension of the matrix (encapsulating generic type Matrix)
     * @param N Neric type (encapsulating generic type Matrix)
     */
template<unsigned D, typename N>
  template<unsigned D_, unsigned i, unsigned j>
    inline void
      VecMath2::Matrix<D, N>::ConstructLoop<D_, i, j>::row_loop (N a[D][D]) {
#       if (DEBUG)
          cerr << "Matrix<" << D << ">::ConstructLoop<" << D_
               << ", " << i << ", " << j << ">::row_loop ()" << endl;
#       endif
        ConstructLoop<D, i, j>::col_loop(a);
        ConstructLoop<D, i-1, j>::row_loop(a);
      }


    /**
     * VecMath2::Matrix<D, N>::ConstructLoop<D_, i, j>::col_loop (N a[D][D])
     * initialize a matrix to unity
     * loop over all columns of a row setting current element either to 0 or 1
     * @param a the matrix (two-dimensional array) to initialize
     * @param i current row to initialize
     * @param j current column to initialize
     * @param D_ dimension of the matrix (dummy parameter)
     * @param D dimension of the matrix (encapsulating generic type Matrix)
     * @param N Neric type (encapsulating generic type Matrix)
     */
template<unsigned D, typename N>
  template<unsigned D_, unsigned i, unsigned j>
    inline void
      VecMath2::Matrix<D, N>::ConstructLoop<D_, i, j>::col_loop (N a[D][D]) {
#       if (DEBUG)
          cerr << "Matrix<" << D << ">::ConstructLoop<" << D_ << ", "
               << i << ", " << j << ">::col_loop () : "
               << (i == j? (N)1: (N)0) << endl;
#       endif
        ConstructLoop<D, i, j-1>::col_loop(a);
        a[i][j] = (i == j? (N)1: (N)0);
      }


    /**
     * VecMath2::Matrix<D, N>::ConstructLoop<D_, 0, j>::row_loop (N a[D][D])
     * initialize a matrix to unity
     * loop over all rows - specialization for the first row
     * @param a the matrix (two-dimensional array) to initialize
     * @param j current column to initialize
     * @param D_ dimension of the matrix (dummy parameter)
     * @param D dimension of the matrix (encapsulating generic type Matrix)
     * @param N Neric type (encapsulating generic type Matrix)
     */
template<unsigned D, typename N>
  template <unsigned D_, unsigned j>
    inline void
      VecMath2::Matrix<D, N>::ConstructLoop<D_, 0, j>::row_loop (N a[D][D]) {
#       if (DEBUG)
          cerr << "Matrix<" << D << ">::ConstructLoop<" << D_ << ", "
               << 0 << ", " << j << ">::row_loop ()" << endl;
#       endif
        ConstructLoop<D, 0, j>::col_loop(a);
      }


    /**
     * VecMath2::Matrix<D, N>::ConstructLoop<D_, 0, j>::col_loop (N a[D][D])
     * initialize a matrix to unity
     * loop over all columns - specialization for the first row
     * @param a the matrix (two-dimensional array) to initialize
     * @param j current column to initialize
     * @param D_ dimension of the matrix (dummy parameter)
     * @param D dimension of the matrix (encapsulating generic type Matrix)
     * @param N Neric type (encapsulating generic type Matrix)
     */
template<unsigned D, typename N>
  template <unsigned D_, unsigned j>
    inline void
      VecMath2::Matrix<D, N>::ConstructLoop<D_, 0, j>::col_loop (N a[D][D]) {
#       if (DEBUG)
          cerr << "Matrix<" << D << ">::ConstructLoop<" << D_ << ", "
               << 0 << ", " << j << ">::col_loop () : "
               << (0 == j? (N)1: (N)0) << endl;
#       endif
        ConstructLoop<D, 0, j-1>::col_loop(a);
        a[0][j] = (j == 0? (N)1: (N)0);
      }


    /**
     * VecMath2::Matrix<D, N>::ConstructLoop<D_, i, 0>::row_loop (N a[D][D])
     * initialize a matrix to unity
     * loop over all rows - specialization for the first column
     * @param a the matrix (two-dimensional array) to initialize
     * @param i current row to initialize
     * @param D_ dimension of the matrix (dummy parameter)
     * @param D dimension of the matrix (encapsulating generic type Matrix)
     * @param N Neric type (encapsulating generic type Matrix)
     */

template<unsigned D, typename N>
  template <unsigned D_, unsigned i>
    inline void
      VecMath2::Matrix<D, N>::ConstructLoop<D_, i, 0>::row_loop (N a[D][D]) {
#       if (DEBUG)
          cerr << "Matrix<" << D << ">::ConstructLoop<" << D_ << ", "
               << i << ", " << 0 << ">::row_loop ()" << endl;
#       endif
        ConstructLoop<D, i, 0>::col_loop(a);
        ConstructLoop<D, i-1, 0>::row_loop(a);
      }


    /**
     * VecMath2::Matrix<D, N>::ConstructLoop<D_, i, 0>::col_loop (N a[D][D])
     * initialize a matrix to unity
     * loop over all columns - specialization for the first column
     * @param a the matrix (two-dimensional array) to initialize
     * @param i current row to initialize
     * @param D_ dimension of the matrix (dummy parameter)
     * @param D dimension of the matrix (encapsulating generic type Matrix)
     * @param N Neric type (encapsulating generic type Matrix)
     */
template<unsigned D, typename N>
  template <unsigned D_, unsigned i>
    inline void
      VecMath2::Matrix<D, N>::ConstructLoop<D_, i, 0>::col_loop (N a[D][D]) {
#       if (DEBUG)
          cerr << "Matrix<" << D << ">::ConstructLoop<" << D_ << ", "
               << i << ", " << 0 << ">::col_loop ()" << endl;
#       endif
        a[i][0] = (i == 0? (N)1: (N)0);
      }


    /**
     * VecMath2::Matrix<D, N>::MultiplyInnerLoop<i, j, k, D_>
     * summation over the product of corresponding row and column elements to
     * calculate one element of the product of two matrices
     */

    /**
     * VecMath2::Matrix<D, N>::MultiplyInnerLoop<i, j, k, D_>::loop (N a[D][D], N b[D][D], N c[D][D])
     * calculate c(i,j) of c = a*b
     * @param a left operand of a*b
     * @param b right operand of a*b
     * @param c resulting matrix
     * @param i row of desired element
     * @param j column of desired element
     * @param k summation index
     * @param D_ dimension of the matrix (dummy parameter)
     * @param D dimension of the matrix (encapsulating generic type Matrix)
     * @param N_ Neric type (encapsulating generic type Matrix)
     */
template<unsigned D, typename N>
  template <unsigned i, unsigned j, unsigned k, unsigned D_>
    inline void
      VecMath2::Matrix<D, N>::MultiplyInnerLoop<i, j, k, D_>::loop (const N a[D][D], const N b[D][D], N c[D][D]) {
        c[i][j] += a[i][k]*b[k][j];
        MultiplyInnerLoop<i, j, k-1, D>::loop (a, b, c);
      }


   /**
    * VecMath2::Matrix<D, N>::MultiplyInnerLoop<i, j, 0, D_>::loop (N a[D][D], N b[D][D], N c[D][D])
    * calculate c(i,j) of c = a*b - first term of the sum
    * @param a left operand of a*b
    * @param b right operand of a*b
    * @param c resulting matrix
    * @param i row of desired element
    * @param k summation index
    * @param D_ dimension of the matrix (dummy parameter)
    * @param D dimension of the matrix (encapsulating generic type Matrix)
    * @param N_ Neric type (encapsulating generic type Matrix)
    */
template<unsigned D, typename N>
  template <unsigned i, unsigned j, unsigned D_>
    inline void
      VecMath2::Matrix<D, N>::MultiplyInnerLoop<i, j, 0, D_>::loop (const N a[D][D], const N b[D][D], N c[D][D]) {
        c[i][j] += a[i][0]*b[0][j];
      }


    /**
     * VecMath2::Matrix<D, N>::MultiplyColLoop<i, j, D_>
     * calculate one row of the product of two matrices
     */

    /**
     * VecMath2::Matrix<D, N>::MultiplyColLoop<i, j, D_>::loop (N a[D][D], N b[D][D], N c[D][D])
     * calculate row i of c = a*b
     * @param a left operand of a*b
     * @param b right operand of a*b
     * @param c resulting matrix
     * @param i row of desired element
     * @param j loop index - column of desired element
     * @param D_ dimension of the matrix (dummy)
     * @param D dimension of the matrix (encapsulating generic type Matrix)
     * @param N_ Neric type (encapsulating generic type Matrix)
     */
template<unsigned D, typename N>
  template <unsigned i, unsigned j, unsigned D_>
    inline void
      VecMath2::Matrix<D, N>::MultiplyColLoop<i, j, D_>::loop (const N a[D][D], const N b[D][D], N c[D][D]) {
        c[i][j] = 0;
        MultiplyInnerLoop<i, j, D-1, D>::loop (a, b, c);
        MultiplyColLoop<i, j-1, D>::loop (a, b, c);
      }

    /**
     * VecMath2::Matrix<D, N>::MultiplyColLoop<i, 0, D_>::loop (N a[D][D], N b[D][D], N c[D][D])
     * calculate row i of c = a*b - first element (j == 0)
     * @param a left operand of a*b
     * @param b right operand of a*b
     * @param c resulting matrix
     * @param i row of desired element
     * @param D_ dimension of the matrix (dummy)
     * @param D dimension of the matrix (encapsulating generic type Matrix)
     * @param N_ Neric type (encapsulating generic type Matrix)
     */
template<unsigned D, typename N>
  template <unsigned i, unsigned D_>
    inline void
      VecMath2::Matrix<D, N>::MultiplyColLoop<i, 0, D_>::loop (const N a[D][D], const N b[D][D], N c[D][D]) {
        c[i][0] = 0;
        MultiplyInnerLoop<i, 0, D-1, D>::loop (a, b, c);
      }


    /**
     * VecMath2::Matrix<D, N>::MultiplyRowLoop<i, D_>
     * calculate the product of two matrices looping over all rows
     */

    /**
     * VecMath2::Matrix<D, N>::MultiplyRowLoop<i, D_>::loop (N a[D][D], N b[D][D], N c[D][D])
     * @param a left operand of a*b
     * @param b right operand of a*b
     * @param c resulting matrix
     * @param i loop index - row of desired element
     * @param D_ dimension of the matrix (dummy)
     * @param D dimension of the matrix (encapsulating generic type Matrix)
     * @param N_ Neric type (encapsulating generic type Matrix)
     */
template<unsigned D, typename N>
  template <unsigned i, unsigned D_>
    inline void
        VecMath2::Matrix<D, N>::MultiplyRowLoop<i, D_>::loop (const N a[D][D], const N b[D][D], N c[D][D]) {
          MultiplyColLoop<i, D-1, D>::loop (a, b, c);
          MultiplyRowLoop<i-1, D>::loop (a, b, c);
        }

    /**
     * VecMath2::Matrix<D, N>::MultiplyRowLoop<0, D_>::loop (N a[D][D], N b[D][D], N c[D][D])
     * first row of the loop over all rows
     * @param a left operand of a*b
     * @param b right operand of a*b
     * @param c resulting matrix
     * @param D_ dimension of the matrix (dummy)
     * @param D dimension of the matrix (encapsulating generic type Matrix)
     * @param N_ Neric type (encapsulating generic type Matrix)
     */
template<unsigned D, typename N>
  template <unsigned D_>
    inline void
      VecMath2::Matrix<D, N>::MultiplyRowLoop<0, D_>::loop (const N a[D][D],
                                                          const N b[D][D], N c[D][D]) {
        MultiplyColLoop<0, D-1, D>::loop (a, b, c);
      }

    /**
     * VecMath2::Matrix<D, N>::Multiply<D_>
     * calculate the product of two matrices
     */

    /**
     * VecMath2::Matrix<D, N>::Multiply<D_>::loop (N a[D][D], N b[D][D], N c[D][D])
     * @param a left operand of a*b
     * @param b right operand of a*b
     * @param c resulting matrix
     * @param D_ dimension of the matrix (dummy)
     * @param D dimension of the matrix (encapsulating generic type Matrix)
     * @param N_ Neric type (encapsulating generic type Matrix)
     */

template<unsigned D, typename N>
  template <unsigned D_>
    inline void
      VecMath2::Matrix<D, N>::Multiply<D_>::multiply (const N a[D][D], const N b[D][D], N c[D][D]) {
        MultiplyRowLoop<D-1, D>::loop (a, b, c);
      }


#if 0

template<unsigned D, typename N>
  Matrix<D-1, N>
    VecMath2::Matrix<D, N>::matrix_minor (unsigned i, unsigned j) {
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
      VecMath2::Matrix<D, N>::Det<D_>::det (/*const*/ N a[D][D]) {
        return SumLoop<D, D-1>::sumloop (a);
      }
/*
template<unsigned D, typename N>
  template<typename N_>
    inline N_
      VecMath2::Matrix<D, N>::Det<1, N_>::det (/*const// N_ a[1][1]) {
        return a[0][0];
      }
*/
template<unsigned D, typename N>
  template<unsigned D_, int i>
    inline N
      VecMath2::Matrix<D, N>::SumLoop<D_, i>::sumloop (/*const*/ N a[D][D])  {
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
      VecMath2::Matrix<D, N>::SumLoop<D_, 0>::sumloop (/*const*/ N a[D][D]) {
        N **tmp1 = Minor<0, 0, D_>::minor (a);
        N tmp2 = a[0][0] * Det<D-1>::det (tmp1);
        delete [] tmp1;
        return tmp2;
      }
/*
template<unsigned D, typename N>
  template<typename N_>
    inline N_
      VecMath2::Matrix<D, N>::SumLoop <0, 0, N_>::sumloop (const N_ a[1][1]) {
        return a[0][0];
      }
*/
template<unsigned D, typename N>
    template<unsigned k, unsigned D_>
        inline void
            VecMath2::Matrix<D, N>::MinorLoop<k, D_>::minorloop (N ** a, N **tmp) {
              tmp[k-1] = a[k]+1;
              MinorLoop<k-1, D>::minorloop (a, tmp);
          }

template<unsigned D, typename N>
    template<unsigned D_>
        inline void
            VecMath2::Matrix<D, N>::MinorLoop<1, D_>::minorloop (N ** a, N **tmp) {
              tmp[0] = a[1]+1;
            }

template<unsigned D, typename N>
    template<unsigned i, unsigned D_>
        inline /*const*/ N **
            VecMath2::Matrix<D, N>::Minor<i, 0, D_>::minor (/*const*/ N **a) {
              /*const*/ N **tmp = new /*const*/ N* [D-1];  //  watch out for memory leaks here!
                                                        //  the caller must free this memory!
              for (unsigned k = 1; k < D; k++)
                tmp[k-1] = a[k]+1;
              //    MinorLoop<D-1, D>::minorloop (a, tmp);
              return tmp;
            }
#endif    //  0

template<unsigned D, typename N>
    template<unsigned i, unsigned j, unsigned D_>
        inline void
            VecMath2::Matrix<D, N>::CopyLoop<i, j, D_>::copy_row (N from[D][D], N to[D][D]) {
              CopyLoop<i-1, j, D>::copy_row (from, to);
              CopyLoop<i, j, D>::copy_col (from, to);
            }


template<unsigned D, typename N>
    template<unsigned i, unsigned j, unsigned D_>
        inline void
            VecMath2::Matrix<D, N>::CopyLoop<i, j, D_>::copy_col (N from[D][D], N to[D][D]) {
              to[i][j] = from[i][j];
              CopyLoop<i, j-1, D>::copy_col (from, to);
            }

template<unsigned D, typename N>
    template<unsigned j, unsigned D_>
        inline void
            VecMath2::Matrix<D, N>::CopyLoop<0, j, D_>::copy_row (N from[D][D], N to[D][D]) {
              CopyLoop<0, j, D>::copy_col (from, to);
            }


template<unsigned D, typename N>
    template<unsigned j, unsigned D_>
        inline void
            VecMath2::Matrix<D, N>::CopyLoop<0, j, D_>::copy_col (N from[D][D], N to[D][D]) {
              to[0][j] = from[0][j];
              CopyLoop<0, j-1, D>::copy_col (from, to);
            }

template<unsigned D, typename N>
    template<unsigned i, unsigned D_>
        inline void
            VecMath2::Matrix<D, N>::CopyLoop<i, 0, D_>::copy_col (N from[D][D], N to[D][D]) {
              to[i][0] = from[i][0];
            }

template<unsigned D, typename N>
    template<unsigned D_>
        inline void
            VecMath2::Matrix<D, N>::CopyLoop<0, 0, D_>::copy_col (N from[D][D], N to[D][D]) {
              to[0][0] = from[0][0];
            }

#endif    // #ifdef MATRIX_H
