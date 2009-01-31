//
// C++ Interface: uintvec
//
// Description:
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef UINTVEC_H
#define UINTVEC_H

#include "NestedVector.H"

namespace VecMath {

    /// A NestedVector of unsignd ints
    /** uintvec<D> is just a shortcut for writing NestedVector<unsigned, D>.
     *  It is necessary to write a class for that because C++ does not support
     *  template typedefs.
     *
     *  \param D Dimensionality (nesting depth) of the vector
     *
     *  \ingroup VecMath
     *  \author Helge Preuss <scout@hyperspace-travel.de>
     */
    template <unsigned D> struct uintvec: public NestedVector<unsigned, D> {
        /// Construct an empty uintvec
        uintvec(): NestedVector<unsigned, D> () { }
        /// Copy construct a uintvec from a NestedVector<unsigned>
        uintvec(NestedVector<unsigned, D> v): NestedVector<unsigned, D>(v) { }
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
