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

#ifndef VIEWPOINTLIST_H
#define VIEWPOINTLIST_H

#include "Vector.h"

/// A list of Vector s of dimension \p Nnew+1 through \p N.
/** These are used in storing the view points and camera positions when projecting
 *  a point in \p N space into \p Nnew dimensions. Every projection from one
 *  dimension to the next lower dimension needs a Vector of the original dimension
 *  as camera position and one as view point.

 *  \tparam N The dimension of the original vector space.
 *  \tparam Nnew The dimension of the vector space into which is projected.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, unsigned Nnew, typename NUM = double> class ViewpointList {

  public:

    /// Creates a ViewpointList with all elements at the origin.
    ViewpointList();

    /// Creates a list of Vector s whose highest element is set to \p camW.
    ViewpointList(NUM camW);

    /// Construct a ViewpointList with a single element.
    ViewpointList(const VecMath::Vector<N, NUM> &single_element);
    /// Construct a ViewpointList from an element and another ViewpointList.
    ViewpointList(const VecMath::Vector<N, NUM> &head, const ViewpointList<N-1, Nnew, NUM> &tail);

    /// Return the first element of a ViewpointList.
    const VecMath::Vector<N, NUM> &head() const { return _elements.first; }
    /// Return the first element of a ViewpointList.
    VecMath::Vector<N, NUM> &head() { return _elements.first; }
    /// Return a ViewpointList that contains all but the first element.
    const ViewpointList<N-1, Nnew, NUM> &tail() const { return _elements.second; }
    /// Return a ViewpointList that contains all but the first element.
    ViewpointList<N-1, Nnew, NUM> &tail() { return _elements.second; }

    /// Returns element \p i from the list.
    /** \tparam i The index of the requested element.
     */
    template <unsigned i> VecMath::Vector<N-i, NUM> get() {
      if (i == 0) return head();
      return tail().get<i-1>();
    }
//    template <> VecMath::Vector<N> get<0>() { return head(); }

    /// String representation.
    std::string toString() const { return _elements.first.toString()+", "+_elements.second.toString(); }

    /// Constructs a ViewpointList with one Member.
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0);
    /// Constructs a ViewpointList with two Members.
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1);
    /// Constructs a ViewpointList with three Members.
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2);
    /// Constructs a ViewpointList with four Members.
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3);
    /// Constructs a ViewpointList with five Members.
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
                              const VecMath::Vector<N-4, NUM> &x4);
    /// Constructs a ViewpointList with six Members.
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
                              const VecMath::Vector<N-4, NUM> &x4, const VecMath::Vector<N-5, NUM> &x5);
    /// Constructs a ViewpointList with seven Members.
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
                              const VecMath::Vector<N-4, NUM> &x4, const VecMath::Vector<N-5, NUM> &x5,
                              const VecMath::Vector<N-6, NUM> &x6);
    /// Constructs a ViewpointList with eight Members.
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
                              const VecMath::Vector<N-4, NUM> &x4, const VecMath::Vector<N-5, NUM> &x5,
                              const VecMath::Vector<N-6, NUM> &x6, const VecMath::Vector<N-7, NUM> &x7);

  private:

    /// The elements of the list are stored as a tuple, recursively defined.
    std::pair< VecMath::Vector<N, NUM>, ViewpointList<N-1, Nnew, NUM> > _elements;
};

/// Specialization of ViewpointList for a projection from \p N space to \p N space - which does nothing.
/** Needed to end recursion.
 *  \tparam N The dimension of the vector space.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, typename NUM> class ViewpointList<N, N, NUM> {
  public:
    /// Constructs empty ViewpointList.
    ViewpointList() { }
    /// Constructs empty ViewpointList.
    ViewpointList(NUM) { }
    /// Empty string representation.
    std::string toString() const { return ""; }
};

#endif