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

#ifndef UINTVEC_H
#define UINTVEC_H

#include "MultiDimensionalVector.h"

namespace VecMath {

    /// A MultiDimensionalVector of unsignd ints
    /** uintvec<D> is just a shortcut for writing MultiDimensionalVector<unsigned, D>.
     *  It is necessary to write a class for that because C++ does not support
     *  template typedefs.
     *
     *  \tparam D Dimensionality (nesting depth) of the vector
     *
     *  \ingroup VecMath
     *  \author Helge Preuss <lene.preuss@gmail.com>
     */
    template <unsigned D> struct uintvec: public MultiDimensionalVector<unsigned, D> {
        /// Construct an empty uintvec
        uintvec(): MultiDimensionalVector<unsigned, D> () { }
        /// Copy construct a uintvec from a MultiDimensionalVector<unsigned>
        uintvec(MultiDimensionalVector<unsigned, D> v): MultiDimensionalVector<unsigned, D>(v) { }

        /// Construct a MultiDimensionalVector from an iterator range
        uintvec(typename std::vector< uintvec<D-1> >::iterator first,
                typename std::vector< uintvec<D-1> >::iterator last):
            MultiDimensionalVector<unsigned, D>(first, last) { }
};

    /// Find an element in a uintvec
    /** \param find_me The element to find in the vector \p v
     *  \param v The vector to search for element \p find_me
     *  \return The \p uintvec<D>::iterator pointing to the element or
     *          \p v.end() if it is not in \p v
     *
     *  \ingroup VecMath
     */
    template <unsigned D>
            typename uintvec<D>::iterator find(uintvec<D-1> const &find_me,
                                               uintvec<D> &v) {
        typename uintvec<D>::iterator i = v.begin();
        while(*i != find_me && i != v.end()) ++i;
        return i;
    }
}


#endif
