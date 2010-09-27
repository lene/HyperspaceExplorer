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

#ifndef VECTOR_H
#define VECTOR_H 1

#include <cstdarg>
#include <cassert>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

# if (!defined __PI)
#   include <cmath>
    const double pi = 4.*atan (1.);
#   define __PI 3_14
# endif

/// \defgroup VecMath Vector and Matrix algebra

/// Vector and Matrix algebra
namespace VecMath {

    ///  Vector<D, N>: a D-dimensional vector of numbers of type N
    /** @tparam D dimension of the vector
     *  @tparam N numerical type of the vector elements
     *  \ingroup VecMath
     *  @author Lene Preuss <lene.preuss@gmail.com>                     */
    template <unsigned D, typename N = double> class Vector {

        public:

        //----------  management  ----------
        /// Default constructor.
        /** Doesn't do anything, the lazy bastard! */
        Vector<D, N> ();
        /// Make all elements have the same size.
        /** \param x The number all Vector components are set to. */
        Vector<D, N> (const N &x);
        /// Constructor with variable argument list.
        /** @param x0  the vector's first element.
         *  @param x1  the vector's second element.
         *  @param ... the vector's other elements.                           */
        Vector<D, N> (N x0, N x1, ... );

        //----------  access      ----------

        /// Returns a reference to component i
        /** @param i index of the element
         *  @return non-const reference to the accessed element               */
        N &operator[] (unsigned i);
        /// Returns component i by value
        /** @param i index of the element
         *  @return the accessed element                                      */
        N operator[] (unsigned i) const;

        /** @return dimension of the Vector (the template parameter D)        */
        static unsigned dimension (void);

        //----------  arithmetics ----------

        /** @param Y other Vector
         *  @return *this+Y                                                   */
        Vector<D, N> &operator+= (const Vector<D, N> &Y);
        /** @param Y other Vector
         *  @return *this-Y                                                   */
        Vector<D, N> &operator-= (const Vector<D, N> &Y);
        /** @param s scalar type
         *  @return *this*s                                                   */
        Vector<D, N> &operator*= (const N &s);

        /** @return -*this                                                    */
        Vector<D, N> operator- (void) const;
        /** @param Y other Vector
         *  @return *this+Y                                                   */
        Vector<D, N> operator+ (const Vector<D, N> &Y) const;
        /** @param Y other Vector
         *  @return *this-Y                                                   */
        Vector<D, N> operator- (const Vector<D, N> &Y) const;
        /** @param s scalar type
         *  @return *this*s                                                   */
        Vector<D, N> operator* (const N &s) const;
        /// scalar multiplication between two Vectors (dot product)
        /** @param X other Vector
         *  @return dot product < *this, Y >                                  */
        N operator* (const Vector<D, N> &X) const;
        /** @param s scalar type
         *  @return *this/s                                                   */
        Vector<D, N> operator/ (const N &s) const;
        /// divide every component of one vector by same component of another
        /** @param X other Vector
         *  @return scaled vector                                             */
        Vector<D, N> operator/ (const Vector<D, N> &X) const;

        /** @return the squared norm of the vector, |V|�                      */
        N sqnorm (void) const;

        /// Comparison operator: Test for equality
        bool operator==(const Vector<D, N> &other) const {
            for (unsigned i = 0; i < D; i++) {
                if (_x[i] != other[i]) return false;
            }
            return true;
        }

        /// Comparison operator: Test for inequality
        bool operator!=(const Vector<D, N> &other) const { return !operator ==(other); }

        /// Ordering needed to use Vector as key for a std::map
        /** \return whether absolute value of this is less than the other
         *  Vector's                                                          */
        bool operator<(const Vector<D, N> &other) const {
            if (sqnorm() == other.sqnorm()) {
                for (unsigned i = 0; i < D; i++) {
                    if (_x[i] < other[i]) return true;
                    if (_x[i] > other[i]) return false;
                }
            }
            return sqnorm() < other.sqnorm();
        }

        /// Direct access to the array storing the components
        /** Needed by glVertex3dv   */
        const N *data () const { return _x; }

        /// Convert the Vector into an array of arbitrary objects
        /** Array of floats is needed by glLightfv()
         *  \tparam T The type of objects the vector elements are converted to.
         *      A cast operator to \p T objects must exist for type \p N.
         */
        template <typename T>
            operator const T * () const {
                static T data[D];
                for (unsigned i = 0; i < D; i++) data[i] = (T)_x[i];
                return data;
            }

        /// Convert Vector to a std::string.
        std::string toString() const;

    private:
        N _x[D]; ///< A static array storing the components
    };

    /// Vector output operator
    template <unsigned D, typename N>
    std::ostream &operator << (std::ostream &s, const Vector<D, N> &v);

    /// Vector input operator
    template <unsigned D, typename N>
    std::istringstream &operator >> (std::istringstream &in, Vector<D, N> &v);

    /// Cross product of two Vector s. This is only mathematically defined for \p D = 3.
    /** Fails for dimensions other than 3 due to lack of template specialization.
     *
     *  \ingroup VecMath
     *  @tparam D dimension of the vector
     *  @tparam N numerical type of the vector elements
     *  \param a First operand of cross product.
     *  \param b Second operand of cross product.
     *  \return \p a \c x \p b
     */
    template <unsigned D, typename N>
            Vector<D, N> cross (const Vector<D, N> &a, const Vector<D, N> &b);

    /// Cross product of three Vector s. This is only mathematically defined for \p D = 4.
    /** Fails for dimensions other than 4 due to lack of template specialization.
     *
     *  \ingroup VecMath
     *  @tparam D dimension of the vector
     *  @tparam N numerical type of the vector elements
     *  \param a First operand of cross product.
     *  \param b Second operand of cross product.
     *  \param c Third operand of cross product.
     *  \return \p a \c x \p b \c x \p c
     */
     template <unsigned D, typename N>
            Vector<D, N> cross (const Vector<D, N> &a, const Vector<D, N> &b, const Vector<D, N> &c);

    /// Cross product of two 3-Vectors.
    /** Specialization of the function template for \p D = 3.
     *
     *  \ingroup VecMath
     *  @tparam N numerical type of the vector elements
     *  @param a first operand of cross product
     *  @param b second operand of cross product
     *  \return \p a \c x \p b
     */
     template <typename N>
            Vector<3, N> vcross (Vector<3, N> a, Vector<3, N> b) {
        static Vector<3, N> c;

        c[0] = a[1]*b[2]-a[2]*b[1];
        c[1] = a[2]*b[0]-a[0]*b[2];
        c[2] = a[0]*b[1]-a[1]*b[0];

        return c;
    }

    /// Cross product of three 4-Vectors
    /** Specialization of the function template for \p D = 4.
     *
     *  \ingroup VecMath
     *  @tparam N numerical type of the vector elements.
     *  @param a first operand of cross product.
     *  @param b second operand of cross product.
     *  @param c third operand of cross product.
     *  \return \p a \c x \p b \c x \p c
     */
     template <typename N>
            Vector<4, N> vcross (Vector<4, N> a, Vector<4, N> b, Vector<4, N> c) {
        static Vector<4, N> d;
        N A = b[0]*c[1]-b[1]*c[0],
        B = b[0]*c[2]-b[2]*c[0],
        C = b[0]*c[3]-b[3]*c[0],
        D = b[1]*c[2]-b[2]*c[1],
        E = b[1]*c[3]-b[3]*c[1],
        F = b[2]*c[3]-b[3]*c[2];

        d[0] =  a[1]*F - a[2]*E + a[3]*D;
        d[1] = -a[0]*F + a[2]*C - a[3]*B;
        d[2] =  a[0]*E - a[1]*C + a[3]*A;
        d[3] = -a[0]*D + a[1]*B - a[2]*A;

        return d;
    }

    /// Normalizes a 3-Vector out-of-place
    /** \ingroup VecMath
     *  @tparam D dimension of the vector
     *  @tparam N numerical type of the vector elements
     *  @param x Vector to be normalized
     *  @return its normalized value
     */
    template <unsigned D, typename N>
            Vector<D, N> vnormalize( const Vector<D, N> &x ) {
        static Vector<D, N> n;
        N norm = sqrt ( x.sqnorm() );
        for ( unsigned i = 0; i < D; i++ ) n[i] = x[i]/norm;
        return n;
    }

    //------------  functions that generate a Vector without taking resort to variable arglists

    /// Generator function for a 2-dimensional Vector
    /** \ingroup VecMath
     *  \tparam N numerical type of the vector elements.
     *  \param x0 first element of the Vector.
     *  \param x1 second element of the Vector.
     */
    template <typename N> Vector<2, N> makeVector(N const &x0, N const &x1) {
        Vector<2, N> x;

        x[0] = x0;
        x[1] = x1;

        return x;
    }

    /// Generator function for a 3-dimensional Vector
    /** \ingroup VecMath
     *  \tparam N numerical type of the vector elements.
     *  \param x0 first element of the Vector.
     *  \param x1 second element of the Vector.
     *  \param x2 third element of the Vector.
     */
    template <typename N> Vector<3, N> makeVector(
            N const &x0, N const &x1, N const &x2) {

        Vector<3, N> x;

        x[0] = x0;
        x[1] = x1;
        x[2] = x2;

        return x;
    }

    /// Generator function for a 4-dimensional Vector
    /** \ingroup VecMath
     *  \tparam N numerical type of the vector elements.
     *  \param x0 first element of the Vector.
     *  \param x1 second element of the Vector.
     *  \param x2 third element of the Vector.
     *  \param x3 fourth element of the Vector.
     */
    template <typename N> Vector<4, N> makeVector(
            N const &x0, N const &x1, N const &x2, N const &x3) {

        Vector<4, N> x;

        x[0] = x0;
        x[1] = x1;
        x[2] = x2;
        x[3] = x3;

        return x;
    }

    /// Generator function for a 5-dimensional Vector
    /** \ingroup VecMath
     *  \tparam N numerical type of the vector elements.
     *  \param x0 first element of the Vector.
     *  \param x1 second element of the Vector.
     *  \param x2 third element of the Vector.
     *  \param x3 fourth element of the Vector.
     *  \param x4 fifth element of the Vector.
     */
    template <typename N> Vector<5, N> makeVector(
            N const &x0, N const &x1, N const &x2, N const &x3, N const &x4) {

        Vector<5, N> x;

        x[0] = x0;
        x[1] = x1;
        x[2] = x2;
        x[3] = x3;
        x[4] = x4;

        return x;
    }

    /// Generator function for a 6-dimensional Vector
    /** \ingroup VecMath
     *  \tparam N numerical type of the vector elements.
     *  \param x0 first element of the Vector.
     *  \param x1 second element of the Vector.
     *  \param x2 third element of the Vector.
     *  \param x3 fourth element of the Vector.
     *  \param x4 fifth element of the Vector.
     *  \param x5 sixth element of the Vector.
     */
    template <typename N> Vector<6, N> makeVector(
            N const &x0, N const &x1, N const &x2, N const &x3, N const &x4,
            N const &x5) {

        Vector<6, N> x;

        x[0] = x0;
        x[1] = x1;
        x[2] = x2;
        x[3] = x3;
        x[4] = x4;
        x[5] = x5;

        return x;
    }

    /// Generator function for a 7-dimensional Vector
    /** \ingroup VecMath
     *  \tparam N numerical type of the vector elements.
     *  \param x0 first element of the Vector.
     *  \param x1 second element of the Vector.
     *  \param x2 third element of the Vector.
     *  \param x3 fourth element of the Vector.
     *  \param x4 fifth element of the Vector.
     *  \param x5 sixth element of the Vector.
     *  \param x6 seventh element of the Vector.
     */
    template <typename N> Vector<7, N> makeVector(
            N const &x0, N const &x1, N const &x2, N const &x3, N const &x4,
            N const &x5, N const &x6) {

        Vector<7, N> x;

        x[0] = x0;
        x[1] = x1;
        x[2] = x2;
        x[3] = x3;
        x[4] = x4;
        x[5] = x5;
        x[6] = x6;

        return x;
    }

    /// Generator function for a 8-dimensional Vector
    /** \ingroup VecMath
     *  \tparam N numerical type of the vector elements.
     *  \param x0 first element of the Vector.
     *  \param x1 second element of the Vector.
     *  \param x2 third element of the Vector.
     *  \param x3 fourth element of the Vector.
     *  \param x4 fifth element of the Vector.
     *  \param x5 sixth element of the Vector.
     *  \param x6 seventh element of the Vector.
     *  \param x7 eighth element of the Vector.
     */
    template <typename N> Vector<8, N> makeVector(
            N const &x0, N const &x1, N const &x2, N const &x3, N const &x4,
            N const &x5, N const &x6, N const &x7) {

        Vector<8, N> x;

        x[0] = x0;
        x[1] = x1;
        x[2] = x2;
        x[3] = x3;
        x[4] = x4;
        x[5] = x5;
        x[6] = x6;
        x[7] = x7;

        return x;
    }

    /// Generator function for a 9-dimensional Vector
    /** \ingroup VecMath
     *  \tparam N numerical type of the vector elements.
     *  \param x0 first element of the Vector.
     *  \param x1 second element of the Vector.
     *  \param x2 third element of the Vector.
     *  \param x3 fourth element of the Vector.
     *  \param x4 fifth element of the Vector.
     *  \param x5 sixth element of the Vector.
     *  \param x6 seventh element of the Vector.
     *  \param x7 eighth element of the Vector.
     *  \param x8 ninth element of the Vector.
     */
    template <typename N> Vector<9, N> makeVector(
            N const &x0, N const &x1, N const &x2, N const &x3, N const &x4,
            N const &x5, N const &x6, N const &x7, N const &x8) {

        Vector<9, N> x;

        x[0] = x0;
        x[1] = x1;
        x[2] = x2;
        x[3] = x3;
        x[4] = x4;
        x[5] = x5;
        x[6] = x6;
        x[7] = x7;
        x[8] = x8;

        return x;
    }

    /// Generator function for a 10-dimensional Vector
    /** \ingroup VecMath
     *  \tparam N numerical type of the vector elements.
     *  \param x0 first element of the Vector.
     *  \param x1 second element of the Vector.
     *  \param x2 third element of the Vector.
     *  \param x3 fourth element of the Vector.
     *  \param x4 fifth element of the Vector.
     *  \param x5 sixth element of the Vector.
     *  \param x6 seventh element of the Vector.
     *  \param x7 eighth element of the Vector.
     *  \param x8 ninth element of the Vector.
     *  \param x9 tenth element of the Vector.
     */
    template <typename N> Vector<10, N> makeVector(
            N const &x0, N const &x1, N const &x2, N const &x3, N const &x4,
            N const &x5, N const &x6, N const &x7, N const &x8, N const &x9) {

        Vector<10, N> x;

        x[0] = x0;
        x[1] = x1;
        x[2] = x2;
        x[3] = x3;
        x[4] = x4;
        x[5] = x5;
        x[6] = x6;
        x[7] = x7;
        x[8] = x8;
        x[9] = x9;

        return x;
    }

}
#endif                                                //  VECTOR_H
