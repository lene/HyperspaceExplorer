
//      project:      hyperspace explorer
//      module:       Vector.H
//      contains:     class definitions for class Vector
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#ifndef VECTOR_H
#define VECTOR_H 1

#include <cstdarg>
#include <cassert>

#include <iostream>
#include <string>

# if (!defined __PI)
#   include <cmath>
    const double pi = 4.*atan (1.);
#   define __PI 3_14
# endif

namespace VecMath {

    template <unsigned D, typename N = double> class Vector {

        public:

        //----------  management  ----------

        Vector<D, N> () { }
        Vector<D, N> (N, ... );

        //----------  access      ----------

        N &operator[] (unsigned i);
        N operator[] (unsigned i) const;

        static unsigned dimension (void);

        //----------  arithmetics ----------

        Vector<D, N> &operator+= (const Vector<D, N> &Y);
        Vector<D, N> &operator-= (const Vector<D, N> &Y);
        Vector<D, N> &operator*= (const N &s);

        Vector<D, N> operator- (void) const;
        Vector<D, N> operator+ (const Vector<D, N> &Y);
        Vector<D, N> operator- (const Vector<D, N> &Y);
        Vector<D, N> operator* (const N &s);
        N operator* (const Vector<D, N> &X) const;
        Vector<D, N> operator/ (const N &s);

        N sqnorm (void) const;

        N *data () { return _x; }

    private:
        N _x[D];
    };
    
    template <unsigned D, typename N> 
            std::ostream &operator << (std::ostream &, const Vector<D> &);

    //------------  Vector member functions

        //  ------------  management  ------------

    /** constructor with variable arglist
    *  @param x0 first element of the Vector
    *  @param ... the following elements                                      */
    template <unsigned D, typename N>
            Vector<D, N>::Vector (N x0, ... ) :
            _x () {
        _x[0] = x0;
        unsigned i = 0;
        va_list argp;
        va_start (argp, x0);
        for (i = 1; i < D; i++) {
            _x[i] = va_arg (argp, N);
        }
        va_end (argp);
    }

    //----------  access      ----------

    /** operator [] returns a reference to component i
    *  @param i index of the element
    *  @return non-const reference to the accessed element                    */
    template <unsigned D, typename N> 
            N &Vector<D, N>::operator[] (unsigned i) {
        assert(i < D);
        return _x[i];
    }

    /** operator [] returns component i by value
    *  @param i index of the element
    *  @return the accessed element                                           */
    template <unsigned D, typename N> 
            N Vector<D, N>::operator[] (unsigned i) const {
        assert(i < D);
        return _x[i];
    }

    /** @return dimension of the Vector (the template parameter D)             */
    template <unsigned D, typename N> 
            unsigned Vector<D, N>::dimension (void) {
        return D; 
    }

        //----------  arithmetics ----------

    /** @param Y other Vector
    *  @return *this+Y                                                        */
    template <unsigned D, typename N>
            Vector<D, N> &Vector<D, N>::operator+= (const Vector<D, N> &Y) {
    for (unsigned i = 0; i < D; i++) _x[i] += Y._x[i];
    return *this;
    }

    /** @param Y other Vector
    *  @return *this-Y                                                        */
    template <unsigned D, typename N> 
            Vector<D, N> &Vector<D, N>::operator-= (const Vector<D, N> &Y) {
    for (unsigned i = 0; i < D; i++) _x[i] -= Y._x[i];
    return *this;
    }

    /** @param s scalar type
    *  @return *this*s                                                        */
    template <unsigned D, typename N>
            Vector<D, N> &Vector<D, N>::operator*= (const N &s) {
    for (unsigned i = 0; i < D; i++) _x[i] *= s;
    return *this;
    }

    /** @return -*this                                                         */
    template <unsigned D, typename N>
            Vector<D, N> Vector<D, N>::operator- (void) const {
        static Vector<D, N> Z;
        Z = *this;
        for (unsigned i = 0; i < D; i++) Z._x[i] = -_x[i] ;
        return Z;
    }

    /** @param Y other Vector
    *  @return *this+Y                                                        */
    template <unsigned D, typename N>
            Vector<D, N> Vector<D, N>::operator+ (const Vector<D, N> &Y) {
    static Vector<D, N> Z;
    Z = *this;
    return (Z += Y);
    }

    /** @param Y other Vector
    *  @return *this-Y                                                        */
    template <unsigned D, typename N>
            Vector<D, N> Vector<D, N>::operator- (const Vector<D, N> &Y) {
    static Vector<D, N> Z;
    Z = *this;
    return (Z -= Y);
    }

    /** @param s scalar type
    *  @return *this*s                                                        */
    template <unsigned D, typename N> 
            Vector<D, N> Vector<D, N>::operator* (const N &s) {
    Vector <D, N>Z;
    Z = *this;
    return Z *= s;
    }

    /** scalar multiplication between two Vectors
    *  @param Y other Vector
    *  @return dot product < *this, Y >                                       */
    template <unsigned D, typename N>
            N Vector<D, N>::operator* (const Vector<D, N> &Y) const {
    N dot = 0.;
    for (unsigned i = 0; i < D; i++)
        if (_x[i]) dot += _x[i]*Y._x[i];

    return dot;
    }

    /** @param s scalar type
    *  @return *this/s                                                        */
    template <unsigned D, typename N>
            Vector<D, N> Vector<D, N>::operator/ (const N &s) {
    return operator* (1./s);
    }

    /** @return the squared norm of the vector, |V|�                           */
    template <unsigned D, typename N>
            N Vector<D, N>::sqnorm (void) const {
    return operator* (*this);
    }


    //------------  important non-member functions for class Vector

    /** Vector output operator
    *  @param o ostream to push into
    *  @param v Vector to print
    *  @return a new ostream to push Vectors and stuff into                   */
    template <unsigned D, typename N>
            std::ostream &operator << (std::ostream &o, const Vector<D, N> &v) {
        //  i might want to use other brackets one day
        o << "<";
        for ( unsigned i = 0; i < v.dimension ()-1; i++ )
        o << v[i] << ",";
        o << v[v.dimension ()-1] << ">";
        return o;
    }

    /** cross product of two 3-Vectors
    *  fails for dimensions other than 3 due to lack of template specialization
    *  @param a	first operand of cross product
    *  @param b	second operand of cross product
    *  @return	a x b                                                         */
    template <unsigned D, typename N>
            Vector<D> cross (const Vector<D> &, const Vector<D> &);

    /** cross product of three 4-Vectors
    *  fails for dimensions other than 4 due to lack of template specialization
    *  @param a	first operand of cross product
    *  @param b	second operand of cross product
    *  @param c	third operand of cross product
    *  @return	a x b x c                                                     */
    template <unsigned D, typename N>
            Vector<D> cross (const Vector<D> &, const Vector<D> &, const Vector<D> &);

    /** specialization for cross product of two 3-Vectors
    *  @param a	first operand of cross product
    *  @param b	second operand of cross product
    *  @return	a x b                                                         */
    template <typename N>
            Vector<3, N> vcross (Vector<3, N> a, Vector<3, N> b) {
        static Vector<3, N> c;

        c[0] = a[1]*b[2]-a[2]*b[1];
        c[1] = a[2]*b[0]-a[0]*b[2];
        c[2] = a[0]*b[1]-a[1]*b[0];

        return c; 
    }

    /** specialization for cross product of three 4-Vectors
    *  @param a	first operand of cross product
    *  @param b	second operand of cross product
    *  @param c	third operand of cross product
    *  @return	a x b x c                                                     */
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

    /** normalizes a 3-Vector out-of-place
    *  @param x	Vector to be normalized
    *  @return	its normalized value                                          */
    template <unsigned D, typename N> 
            Vector<D, N> vnormalize( const Vector<D, N> &x ) {
        static Vector<D, N> n;
        N norm = sqrt ( x.sqnorm() );
        for ( unsigned i = 0; i < D; i++ ) n[i] = x[i]/norm;
        return n;
    }
}
#endif                                                //  VECTOR_H
