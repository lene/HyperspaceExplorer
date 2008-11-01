
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
    /** @param D dimension of the vector
     *  @param N numerical type of the vector elements
     *  \ingroup VecMath
     *  @author Helge Preuss <scout@hyperspace-travel.de>                     */
    template <unsigned D, typename N = double> class Vector {

        public:

        //----------  management  ----------
        /// Default constructor
        /** Doesn't do anything, the lazy bastard! */
        Vector<D, N> ();
        /// Constructor with variable arglist
        /** @param x0  the vector's first element
         *  @param ... the vector's other elements                            */
        Vector<D, N> (N x0, ... );

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

        /** @return the squared norm of the vector, |V|²                      */
        N sqnorm (void) const;

        /// Comparison operator
        bool operator==(const Vector<D, N> &other) const {
            for (unsigned i = 0; i < D; i++) {
                if (x[i] != other[i]) return false;
            }
            return true;
        }

        /// Ordering needed to use Vector as key for a std::map
        /** @return whether absolute value of this is less than the other
         *  Vector's                                                          */
        bool operator<(const Vector<D, N> &other) const {
            if (sqnorm() == other.sqnorm()) {
                for (unsigned i = 0; i < D; i++) {
                    if (x[i] < other[i]) return true;
                    if (x[i] > other[i]) return false;
                }
            }
            return sqnorm() < other.sqnorm();
        }

        /// Direct access to the array storing the components
        /** Needed by glVertex3dv   */
        N *data () { return x; }

        /// Convert the Vector into an array of arbitrary objects
        /** Array of floats is needed by glLightfv() */
        template <typename T>
            operator const T * () const {
                static T data[D];
                for (unsigned i = 0; i < D; i++) data[i] = (T)x[i];
                return data;
            }

    private:
        N x[D]; ///< A static array storing the components
    };

    template <unsigned D, typename N>
            std::ostream &operator << (std::ostream &, const Vector<D, N> &);

    //------------  Vector member functions

        //  ------------  management  ------------

    template <unsigned D, typename N>
            Vector<D, N>::Vector() : x () {
        for (unsigned i = 0; i < D; i++) x[i] = 0;
    }

    template <unsigned D, typename N>
            Vector<D, N>::Vector (N x0, ... ) :
            x () {
        x[0] = x0;
        unsigned i = 0;
        va_list argp;
        va_start (argp, x0);
        for (i = 1; i < D; i++) {
            x[i] = va_arg (argp, N);
        }
        va_end (argp);
    }

    //----------  access      ----------

    template <unsigned D, typename N>
            N &Vector<D, N>::operator[] (unsigned i) {
        assert(i < D);
        return x[i];
    }

    template <unsigned D, typename N>
            N Vector<D, N>::operator[] (unsigned i) const {
        assert(i < D);
        return x[i];
    }

    template <unsigned D, typename N>
            unsigned Vector<D, N>::dimension (void) {
        return D;
    }

        //----------  arithmetics ----------

    template <unsigned D, typename N>
            Vector<D, N> &Vector<D, N>::operator+= (const Vector<D, N> &Y) {
        for (unsigned i = 0; i < D; i++) x[i] += Y.x[i];
        return *this;
    }

    template <unsigned D, typename N>
            Vector<D, N> &Vector<D, N>::operator-= (const Vector<D, N> &Y) {
        for (unsigned i = 0; i < D; i++) x[i] -= Y.x[i];
        return *this;
    }

    template <unsigned D, typename N>
            Vector<D, N> &Vector<D, N>::operator*= (const N &s) {
    for (unsigned i = 0; i < D; i++) x[i] *= s;
    return *this;
    }

    template <unsigned D, typename N>
            Vector<D, N> Vector<D, N>::operator- (void) const {
        static Vector<D, N> Z;
        Z = *this;
        for (unsigned i = 0; i < D; i++) Z.x[i] = -x[i] ;
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
    for (unsigned i = 0; i < D; i++)
        if (x[i]) dot += x[i]*Y.x[i];

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
            tmp[i] = x[i]/X[i];
        return tmp;
    }


    template <unsigned D, typename N>
            N Vector<D, N>::sqnorm (void) const {
        return operator* (*this);
    }


    //------------  important non-member functions for class Vector

    /// Vector output operator
    /** \ingroup VecMath
     *  @param o ostream to push into
     *  @param v Vector to print
     *  @return a new ostream to push Vectors and stuff into                  */
    template <unsigned D, typename N>
            std::ostream &operator << (std::ostream &o, const Vector<D, N> &v) {
        //  i might want to use other brackets one day
        o << "<";
        for (unsigned i = 0; i < v.dimension ()-1; i++) o << v[i] << ",";
        o << v[v.dimension ()-1] << ">";
        return o;
    }

    /// Vector input operator
    /** \ingroup VecMath
     *  @param o istream to read from
     *  @param v Vector to read
     *  @return a new istream to read stuff from                              */
    template <unsigned D, typename N>
            std::istringstream &operator >> (std::istringstream &in, Vector<D, N> &v) {
        char bracket;
        while (bracket != '<' && !in.eof()) { in >> bracket; }
        for (unsigned i = 0; i < v.dimension ()-1; i++) {
            in >> v[i] >> bracket;
        }
        in >> v[v.dimension ()-1] >> bracket;
        return in;
    }

    /// cross product of two Vectors
    /** fails for dimensions other than 3 due to lack of template
     *  specialization
     *  \ingroup VecMath
     *  @param a	first operand of cross product
     *  @param b	second operand of cross product
     *  @return	a x b                                                         */
    template <unsigned D, typename N>
            Vector<D> cross (const Vector<D> &, const Vector<D> &);

    /// specialization for cross product of three 4-Vectors
    /** fails for dimensions other than 4 due to lack of template
     *  specialization
     *  \ingroup VecMath
     *  @param a	first operand of cross product
     *  @param b	second operand of cross product
     *  @param c	third operand of cross product
     *  @return	a x b x c                                                     */
    template <unsigned D, typename N>
            Vector<D> cross (const Vector<D> &, const Vector<D> &, const Vector<D> &);

    /// specialization for cross product of two 3-Vectors
    /** \ingroup VecMath
     *  @param a first operand of cross product
     *  @param b second operand of cross product
     *  @return a x b                                                         */
    template <typename N>
            Vector<3, N> vcross (Vector<3, N> a, Vector<3, N> b) {
        static Vector<3, N> c;

        c[0] = a[1]*b[2]-a[2]*b[1];
        c[1] = a[2]*b[0]-a[0]*b[2];
        c[2] = a[0]*b[1]-a[1]*b[0];

        return c;
    }

    /// specialization for cross product of three 4-Vectors
    /** \ingroup VecMath
     * @param a	first operand of cross product
     * @param b	second operand of cross product
     * @param c	third operand of cross product
     * @return	a x b x c                                                     */
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

    /// normalizes a 3-Vector out-of-place
    /** \ingroup VecMath
     *  @param x Vector to be normalized
     *  @return its normalized value                                          */
    template <unsigned D, typename N>
            Vector<D, N> vnormalize( const Vector<D, N> &x ) {
        static Vector<D, N> n;
        N norm = sqrt ( x.sqnorm() );
        for ( unsigned i = 0; i < D; i++ ) n[i] = x[i]/norm;
        return n;
    }
}
#endif                                                //  VECTOR_H
