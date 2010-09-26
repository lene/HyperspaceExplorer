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

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <string>

/// A list of elements of arbitrary type defined at compile time.
/** \tparam size Number of elements in the ArrayList.
 *  \tparam T Type of the stored elements.
 */
template <unsigned size, typename T> class ArrayList {
  public:
    /// Create an ArrayList with default-constructed elements.
    ArrayList(): _elements() { }
    /// Create an ArrayList with all elements initialized to \p x.
    ArrayList(const T &x);

    /// Return the first element of an ArrayList.
    T head() const { return _elements.first; }
    /// Return an ArrayList that contains all but the first element.
    ArrayList<size-1, T> tail() const { return _elements.second; }

    /// Read-write access to an element of the ArrayList.
    T &operator[](unsigned i);
    /// Read-only access to an element of the ArrayList.
    const T &operator[](unsigned i) const;

    /// String representation.
    std::string toString() const;

  private:
    /// Stores the elements of the list in a pair of an element and a shorter list.
    std::pair<T, ArrayList<size-1, T> > _elements;
};

/// An empty ArrayList. Specialization to end recursion.
/** \tparam T Type of the stored elements.
 */
template <typename T> class ArrayList<0, T> {
  public:
    /// Empty List.
    ArrayList() { }
    /// Empty List.
    ArrayList(T) { }
    /// Empty String.
    std::string toString() const;

};

#endif // ARRAYLIST_H
