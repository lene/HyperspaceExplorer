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

    template <unsigned D, typename N>
            Vector<D, N>::Vector(const N &x) : _x() {
        for (unsigned i = 0; i < D; i++) _x[i] = x;
    }

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

    template <unsigned D, typename N>
            N &Vector<D, N>::operator[] (unsigned i) {
        assert(i < D);
        return _x[i];
    }

    template <unsigned D, typename N>
            N Vector<D, N>::operator[] (unsigned i) const {
        assert(i < D);
        return _x[i];
    }

    template <unsigned D, typename N>
            unsigned Vector<D, N>::dimension (void) {
        return D;
    }

        //----------  arithmetics ----------

    template <unsigned D, typename N>
            Vector<D, N> &Vector<D, N>::operator+= (const Vector<D, N> &Y) {
        for (unsigned i = 0; i < D; i++) _x[i] += Y._x[i];
        return *this;
    }

    template <unsigned D, typename N>
            Vector<D, N> &Vector<D, N>::operator-= (const Vector<D, N> &Y) {
        for (unsigned i = 0; i < D; i++) _x[i] -= Y._x[i];
        return *this;
    }

    template <unsigned D, typename N>
            Vector<D, N> &Vector<D, N>::operator*= (const N &s) {
    for (unsigned i = 0; i < D; i++) _x[i] *= s;
    return *this;
    }

    template <unsigned D, typename N>
            Vector<D, N> Vector<D, N>::operator- (void) const {
        static Vector<D, N> Z;
        Z = *this;
        for (unsigned i = 0; i < D; i++) Z._x[i] = -_x[i] ;
        return Z;
    }

    template <unsigned D, typename N>
            Vector<D, N> Vector<D, N>::operator+ (const Vector<D, N> &Y) const {
    static Vector<D, N> Z;
    Z = *this;
    return (Z += Y);
    }

    template <unsigned D, typename N>
            Vector<D, N> Vector<D, N>::operator- (const Vector<D, N> &Y) const {
    static Vector<D, N> Z;
    Z = *this;
    return (Z -= Y);
    }

    template <unsigned D, typename N>
            Vector<D, N> Vector<D, N>::operator* (const N &s) const {
    Vector <D, N>Z;
    Z = *this;
    return Z *= s;
    }

    template <unsigned D, typename N>
            N Vector<D, N>::operator* (const Vector<D, N> &Y) const {
    N dot = 0.;
    for (unsigned i = 0; i < D; i++) dot += _x[i]*Y._x[i];

    return dot;
    }

    template <unsigned D, typename N>
            Vector<D, N> Vector<D, N>::operator/ (const N &s) const {
    return operator* (1./s);
    }

    template <unsigned D, typename N>
            Vector<D, N> Vector<D, N>::operator/ (const Vector<D, N> &X) const {
        Vector<D, N> tmp;
        for (unsigned i = 0; i < D; i++)
            tmp[i] = _x[i]/X[i];
        return tmp;
    }


    template <unsigned D, typename N>
            N Vector<D, N>::sqnorm (void) const {
        return operator* (*this);
    }

    template <unsigned D, typename N>
    std::string Vector<D, N>::toString() const {
        std::ostringstream o;
        o << *this << std::ends;
        return o.str();
    }

    //------------  important non-member functions for class Vector

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

}

#endif