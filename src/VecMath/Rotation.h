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
#ifndef VECMATHROTATION_H
#define VECMATHROTATION_H

#include "Vector.h"
#include "Matrix.h"
#include "NotYetImplementedException.h"
#include "Util.h"

namespace VecMath {

    /// Determine number of rotation axes in D-dimensional space
    /** The number of rotation axes is computed at compile time. It is accessed
     *  as NumAxes<D>::num.
     *  \tparam D dimension of the vector space
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
     *  \tparam D dimension of the vector space
     *  \ingroup VecMath                                                      */
    template <unsigned D> class RotationAxes {
        public:
            static unsigned axis(unsigned which, unsigned index);
        private:
            /// explicitly stores the values for \p ii and \p jj
            static unsigned _axis[2][NumAxes<D>::num];
    };

    /// Rotation axes in three dimensions, manually specified
    template <> class RotationAxes<3> {
        public:
            static unsigned axis(unsigned which, unsigned index);
        private:
            static const unsigned _axis[2][3];  ///< values for \p ii and \p jj
    };

    /// Rotation axes in four dimensions, manually specified
    template <> class RotationAxes<4> {
        public:
            static unsigned axis(unsigned which, unsigned index);
        private:
            static const unsigned _axis[2][6];  ///< values for \p ii and \p jj
    };

    /// Interface Rotation<D, N> implements
    /** Currently empty because I need nothing else than he information whether
     *  a specific object is a Rotation or not
     */
    class RotationBase { };

    /// Rotation in D-dimensional space defined by angles about the main axes
    /** @tparam D dimension of the vector space
     *  @tparam N numerical type of the rotation angles
     *  \ingroup VecMath
     *  @author Helge Preuss <lene.preuss@gmail.com>                     */
    template <unsigned D, typename N = double> class Rotation:
            public RotationBase {

        public:
          
            /// default constructor, zero rotation
            Rotation<D, N>();

            /// Constructor with variable arglist
            Rotation<D, N> (N r0, ... );

            /// Returns a reference to component i
            N &operator[] (unsigned i);
            /// Returns component i by value
            N operator[] (unsigned i) const;

            /// Creates a rotation Matrix from the angles
            operator Matrix<D, N>() const;

            /// Adds another Rotation to \c this.
            Rotation<D, N> &operator+= (const Rotation<D, N> &that);
            /// Returns the sum of two Rotation s.
            Rotation<D, N> operator+ (const Rotation<D, N> &that) const;

            /// true if rotation is nonzero
            operator bool() const;

            /// access the stored values (needed by output operator <<())
            const Vector<NumAxes<D>::num, N> &r() const;

            /// write access the stored values (needed by input operator >>())
            Vector<NumAxes<D>::num, N> &r();

            /// Convert Rotation to a std::string.
            std::string toString() const;

        private:
          
            /// Rotation angles are stored as a Vector, operations are delegated
            Vector<NumAxes<D>::num, N> axis;
    };


    //------------  important non-member functions for class Rotation


    /// RotationBase output operator
    std::ostream &operator << (std::ostream &o, const RotationBase &);

    /// Rotation output operator
    template <unsigned D, typename N>
    std::ostream &operator << (std::ostream &o, const Rotation<D, N> &v);

    /// Rotation input operator
    template <unsigned D, typename N>
    std::istringstream &operator >> (std::istringstream &in, Rotation<D, N> &v);

    //------------  functions that generate a Rotation without resorting to variable arglists

    /// Generator function for a 3-dimensional Rotation
    template <typename N> 
    Rotation<3, N> makeRotation(N const &r0, N const &r1, N const &r2);

    /// Generator function for a 4-dimensional Rotation
    template <typename N> 
    Rotation<4, N> makeRotation(N const &r0, N const &r1, N const &r2, 
                                N const &r3, N const &r4, N const &r5);
}

#endif
