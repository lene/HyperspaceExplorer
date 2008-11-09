#ifndef VECMATHROTATION_H
#define VECMATHROTATION_H

#include "Vector.H"
#include "Matrix.H"
#include "NotYetImplementedException.H"
#include "Globals.H"

namespace VecMath {

    /// Determine number of rotation axes in D-dimensional space
    /** The number of rotation axes is computed at compile time. It is accessed
     *  as NumAxes<D>::num.
     *  \param D dimension of the vector space
     *  \ingroup VecMath                                                      */
    template <unsigned D> struct NumAxes {
        enum { num = NumAxes<D-1>::num+D-1 };
    };
    /// Specialization for zero-dimensional space (no rotation possible)
    template <> struct NumAxes<0> { enum { num = 0 }; };
    /// Specialization for one-dimensional space (no rotation possible)
    template <> struct NumAxes<1> { enum { num = 0 }; };

    /// How to generate a Rotation matrix from a Rotation component
    /** A Rotation matrix about a coordinate axis is created with the c'tor
     *  Matrix<D, N>::Matrix (unsigned ii, unsigned jj, N Theta), where \p ii
     *  and \p jj describe the axis about which is rotated.
     *
     *  Unfortunately the position of the angle in the Rotation vector does not
     *  map to the axis indicators \p ii and \p jj straightforwardly. This class
     *  provides the static method axis(), which computes them.
     *
     *  In fact, though, it works only in the three- and four-dimensional cases.
     *  In these dimensions, I have manually specified the axes. For higher
     *  dimensions, a NotYetImplementedException is thrown.
     *  \todo Find a generic algorithm for \p D dimensions
     *  \param D dimension of the vector space
     *  \ingroup VecMath                                                      */
    template <unsigned D> class RotationAxes {
        public:
            /** Compute the row/column in a rotation Matrix from the dimension
             *  of the vector space and the position of the rotation angle in
             *  the Rotation vector.
             *  \param which 0 for \p ii or 1 for \p jj
             *  \param index position in the Rotation vector                  */
            static unsigned axis(unsigned which, unsigned index) {
                throw NotYetImplementedException(
                        "RotationAxes<"+Globals::Instance().itoa(D)+">::axis("+
                        Globals::Instance().itoa(which)+", "+
                        Globals::Instance().itoa(index)+")");
            }
        private:
            /// explicitly stores the values for \p ii and \p jj
            static unsigned _axis[2][NumAxes<D>::num];
    };

    /// Rotation axes in three dimensions, manually specified
    template <> class RotationAxes<3> {
        public:
            /** Compute the row/column in a rotation Matrix from the dimension
             *  of the vector space and the position of the rotation angle in
             *  the Rotation vector.
             *  \param which 0 for \p ii or 1 for \p jj
             *  \param index position in the Rotation vector                  */
            static unsigned axis(unsigned which, unsigned index) {
                return _axis[which][index];
            }
        private:
            static const unsigned _axis[2][3];  ///< values for \p ii and \p jj
    };

    /// Rotation axes in four dimensions, manually specified
    template <> class RotationAxes<4> {
        public:
            /** Compute the row/column in a rotation Matrix from the dimension
             *  of the vector space and the position of the rotation angle in
             *  the Rotation vector.
             *  \param which 0 for \p ii or 1 for \p jj
             *  \param index position in the Rotation vector                  */
            static unsigned axis(unsigned which, unsigned index) {
                return _axis[which][index];
            }
        private:
            static const unsigned _axis[2][6];  ///< values for \p ii and \p jj
    };

    /// Interface Rotation<D, N> implements
    /** Currently empty because I need nothing else than he information whether
     *  a specific object is a Rotation or not
     */
    class RotationBase { };

    /// Rotation in D-dimensional space defined by angles about the main axes
    /** @param D dimension of the vector space
     *  @param N numerical type of the rotation angles
     *  \ingroup VecMath
     *  @author Helge Preuss <scout@hyperspace-travel.de>                     */
    template <unsigned D, typename N = double> class Rotation:
            public RotationBase {

        public:
            /// default constructor, zero rotation
            Rotation<D, N>(): axis() { }

            /// Constructor with variable arglist
            /** @param r0  angle about first rotation axis
             *  @param ... angle about the other axes                         */
            Rotation<D, N> (N r0, ... );

            /// Returns a reference to component i
            /** @param i index of the element
             *  @return non-const reference to the accessed element           */
            N &operator[] (unsigned i);
            /// Returns component i by value
            /** @param i index of the element
             *  @return the accessed element                                  */
            N operator[] (unsigned i) const;

            /// Creates a rotation Matrix from the angles
            /** \todo default implementation does not work correctly yet
             *  \see the specializations for 3 and 4 dimensions in Rotation.C */
            operator Matrix<D, N>() const;

            /** @param that other Rotation
             *  @return *this+that                                               */
            Rotation<D, N> &operator+= (const Rotation<D, N> &);

            /// true if rotation is nonzero
            operator bool() const { return axis.sqnorm() != 0.; }

            /// access the stored values (needed by output operator <<())
            const Vector<NumAxes<D>::num, N> &r() const { return axis; }

            /// write access the stored values (needed by input operator >>())
            Vector<NumAxes<D>::num, N> &r() { return axis; }

        private:
            /// Rotation angles are stored as a Vector, operations are delegated
            Vector<NumAxes<D>::num, N> axis;
    };

    template <unsigned D, typename N> Rotation<D, N>::Rotation (N r0, ... ):
            axis() {
        axis[0] = r0;
        va_list argp;
        va_start (argp, r0);
        for (unsigned i = 1; i < NumAxes<D>::num; i++) {
            axis[i] = va_arg (argp, N);
        }
        va_end (argp);
    }

    template <unsigned D, typename N>
            N &Rotation<D, N>::operator[] (unsigned i) {
        assert(i < NumAxes<D>::num);
        return axis[i];
    }

    template <unsigned D, typename N>
            N Rotation<D, N>::operator[] (unsigned i) const {
        assert(i < NumAxes<D>::num);
        return axis[i];
    }

    template <unsigned D, typename N> Rotation<D, N>::operator Matrix<D, N>() const {
        Matrix<D, N> R;
        for (unsigned i = 0; i < NumAxes<D>::num; i++) {
            if (axis[i]) {
                R *= Matrix<D, N>(RotationAxes<D>::axis(0, i),
                                  RotationAxes<D>::axis(1, i),
                                  axis[i]);
            }
        }
        return R;
    }

    template <unsigned D, typename N>
            Rotation<D, N> &Rotation<D, N>::operator +=(const Rotation<D, N>& that) {
        axis += that.axis;
        return *this;
    }
    //------------  important non-member functions for class Rotation

    /// Rotation output operator
    /** \ingroup VecMath
     *  \param o ostream to push into
     *  \param v Rotation to print
     *  \return a new ostream to push Rotations and stuff into                */
    template <unsigned D, typename N>
            std::ostream &operator << (std::ostream &o, const Rotation<D, N> &v) {
        o << v.r();
        return o;
    }

    /// Rotation input operator
    /** \ingroup VecMath
     *  \param in istringstream to read from
     *  \param v Rotation to read
     *  \return a new istringstream to read stuff from
     */
    template <unsigned D, typename N>
            std::istringstream &operator >> (std::istringstream &in,
                                             Rotation<D, N> &v) {
        in >> v.r();
        return in;
    }

}

#endif
