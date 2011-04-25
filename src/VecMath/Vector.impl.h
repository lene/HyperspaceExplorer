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

#ifndef VECMATH_VECTOR_IMPL_H
#define VECMATH_VECTOR_IMPL_H 1

#include "Vector.h"

namespace VecMath {
    //------------  Vector member functions

        //  ------------  management  ------------

template <unsigned D, typename N>
Vector<D, N>::Vector() : _x() {
        for (unsigned i = 0; i < D; i++) _x[i] = 0;
}

/** \param x The number all Vector components are set to. */
template <unsigned D, typename N>
Vector<D, N>::Vector(const N &x) : _x() {
        for (unsigned i = 0; i < D; i++) _x[i] = x;
}

/** To avoid using variable arglists, for \p D up to 10 you can use makeVector().
 *
 *  @param x0  the vector's first element.
 *  @param x1  the vector's second element.
 *  @param ... the vector's other elements.                           */
template <unsigned D, typename N>
Vector<D, N>::Vector (N x0, N x1, ... ) :
            _x () {
        _x[0] = x0;
        _x[1] = x1;
        va_list argp;
        va_start (argp, x1);
        for (unsigned i = 2; i < D; i++) {
            _x[i] = va_arg (argp, N);
        }
        va_end (argp);
}

    //----------  access      ----------

/** @param i index of the element
 *  @return non-const reference to the accessed element               */
template <unsigned D, typename N>
N &Vector<D, N>::operator[] (unsigned i) {
        assert(i < D);
        return _x[i];
}

/** @param i index of the element
 *  @return non-const reference to the accessed element               */
template <unsigned D, typename N>
N Vector<D, N>::operator[] (unsigned i) const {
        assert(i < D);
        return _x[i];
}

/** @return dimension of the Vector (the template parameter D)        */
template <unsigned D, typename N>
unsigned Vector<D, N>::dimension (void) {
        return D;
}

        //----------  arithmetics ----------

/** @param Y other Vector
 *  @return *this+Y                                                   */
template <unsigned D, typename N>
Vector<D, N> &Vector<D, N>::operator+= (const Vector<D, N> &Y) {
        for (unsigned i = 0; i < D; i++) _x[i] += Y._x[i];
        return *this;
}

/** @param Y other Vector
 *  @return *this-Y                                                   */
template <unsigned D, typename N>
Vector<D, N> &Vector<D, N>::operator-= (const Vector<D, N> &Y) {
        for (unsigned i = 0; i < D; i++) _x[i] -= Y._x[i];
        return *this;
}

/** @param s scalar type
 *  @return *this*s                                                   */
template <unsigned D, typename N>
Vector<D, N> &Vector<D, N>::operator*= (const N &s) {
    for (unsigned i = 0; i < D; i++) _x[i] *= s;
    return *this;
}

template <unsigned D, typename N>
Vector<D, N> &Vector<D, N>::scale(const Vector<D, N> &other) {
  for (unsigned i = 0; i < D; ++i) {
    _x[i] *= other[i];
  }
  return *this;
}

/** Needed by glVertex3dv   */
template <unsigned D, typename N>
const N *Vector<D, N>::data () const {
  return _x;
}

/** Array of floats is needed by glLightfv().
 *  Any other type can be a target type as long as a conversion exists from \p N
 *  to \p T.
 *
 *  \tparam T The type of objects the vector elements are converted to.
 *      A cast operator to \p T objects must exist for type \p N.
 */
template <unsigned D, typename N>
template <typename T>
Vector<D, N>::operator const T * () const {
  static T data[D];
  for (unsigned i = 0; i < D; i++) data[i] = (T)_x[i];
  return data;
}

template <unsigned D, typename N>
std::string Vector<D, N>::toString() const {
  std::ostringstream o;
  o << *this << std::ends;
  return o.str();
}

// -------- non-member functions -----------------------------------------------

/** \return \p -v */
template <unsigned D, typename N>
Vector<D, N> operator-(const Vector<D, N> &v) {
  Vector<D, N> Z(v);
  for (unsigned i = 0; i < D; i++) Z[i] = -v[i] ;
  return Z;
}

/** \param x first operand
 *  \param y second operand
 *  \return \p x+y
 */
template <unsigned D, typename N>
Vector<D, N> operator+(const Vector<D, N> &x, const Vector<D, N> &y) {
  Vector<D, N> z(x);
  return (z += y);
}

/** \param x first operand
 *  \param y second operand
 *  \return \p x-y
 */
template <unsigned D, typename N>
Vector<D, N> operator-(const Vector<D, N> &x, const Vector<D, N> &y) {
  Vector<D, N> z(x);
  return (z -= y);
}

/** \param x Vector
 *  @param s scalar type
 *  @return \p x*s
 */
template <unsigned D, typename N>
Vector<D, N> operator* (const Vector<D, N> &x, const N &s) {
  Vector<D, N> z(x);
  return z *= s;
}

/** \param x Vector
 *  @param s scalar type
 *  @return \p x*s
 */
template <unsigned D, typename N>
Vector<D, N> operator* (const N &s, const Vector<D, N> &x) {
  return x*s;
}

/** @param x First factor
 *  \param y Second factor
 *  @return dot product < \p x, \p y >
 */
template <unsigned D, typename N>
N operator*(const Vector<D, N> &x, const Vector<D, N> &y) {
    N dot = 0.;
    for (unsigned i = 0; i < D; i++) dot += x[i]*y[i];

    return dot;
}

/** \param x Dividend
 *  @param s Scalar divisor
 *  @return *this/s
 */
template <unsigned D, typename N>
Vector<D, N> operator/ (const Vector<D, N> &x, const N &s) {
    return x*(1./s);
}

/** \param X Dividend
 *  \param y Divisor
 *  @return scaled vector
 */
template <unsigned D, typename N>
Vector<D, N> operator/ (const Vector<D, N> &x, const Vector<D, N> &y) {
  Vector<D, N> tmp;
  for (unsigned i = 0; i < D; i++)
    tmp[i] = x[i]/y[i];
  return tmp;
}

template <unsigned D, typename N>
bool operator==(const Vector<D, N> &one, const Vector<D, N> &other) {
      for (unsigned i = 0; i < D; i++) {
        if (one[i] != other[i]) return false;
      }
      return true;
}

template <unsigned D, typename N>
bool operator!=(const Vector<D, N> &one, const Vector<D, N> &other) {
      return !(one == other);
}

/** \return whether absolute value of this is less than the other
 *  Vector's
 */
template <unsigned D, typename N>
bool operator<(const Vector<D, N> &one, const Vector<D, N> &other) {
      if (sqnorm(one) == sqnorm(other)) {
        for (unsigned i = 0; i < D; i++) {
          if (one[i] < other[i]) return true;
          if (one[i] > other[i]) return false;
        }
      }
      return sqnorm(one) < sqnorm(other);
}

/** @return the squared norm of the vector, \f$ |x|^2 \f$ */
template <unsigned D, typename N>
N sqnorm (const Vector<D, N> &x)  {
 return x*x;
}

    /** \ingroup VecMath
     *  @tparam D dimension of the vector
     *  @tparam N numerical type of the vector elements
     *  @param o ostream to push into
     *  @param v Vector to print
     *  @return \p o; a new ostream to push Vectors and stuff into
     */
    template <unsigned D, typename N>
            std::ostream &operator << (std::ostream &o, const Vector<D, N> &v) {
        //  i might want to use other brackets one day
        o << "<";
        for (unsigned i = 0; i < v.dimension ()-1; i++)
            o << std::setprecision(4) << v[i] << ",";
        o << std::setprecision(4) << v[v.dimension ()-1] << ">";
        return o;
    }

    /** \ingroup VecMath
     *  @tparam D dimension of the vector
     *  @tparam N numerical type of the vector elements
     *  \param in istringstream to read from
     *  \param v Vector to read
     *  \return \p in - a new istringstream to read stuff from
     */
    template <unsigned D, typename N>
            std::istringstream &operator >> (std::istringstream &in,
                                             Vector<D, N> &v) {
        char bracket = ' ';
        while (bracket != '<' && !in.eof()) { in >> bracket; }
        for (unsigned i = 0; i < v.dimension ()-1; i++) {
            in >> v[i] >> bracket;
        }
        in >> v[v.dimension ()-1] >> bracket;
        return in;
    }


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

    /** \ingroup VecMath
     *  @tparam D dimension of the vector
     *  @tparam N numerical type of the vector elements
     *  @param x Vector to be normalized
     *  @return its normalized value
     */
    template <unsigned D, typename N>
            Vector<D, N> vnormalize( const Vector<D, N> &x ) {
        static Vector<D, N> n;
        N norm = sqrt(sqnorm(x));
        for ( unsigned i = 0; i < D; i++ ) n[i] = x[i]/norm;
        return n;
    }

    //------------  functions that generate a Vector without taking resort to variable arglists

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

#endif