/*
    Hyperspace Explorer - visualizing higher-dimensional geometry
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
    ArrayList();
    /// Create an ArrayList with all elements initialized to \p x.
    ArrayList(const T &x);
    /// Create an ArrayList from a smaller ArrayList and an additional element.
    ArrayList(const T &head, const ArrayList<size-1, T> &tail);

    /// Return the first element of an ArrayList.
    const T &head() const;
    T &head();
    /// Return an ArrayList that contains all but the first element.
    const ArrayList<size-1, T> &tail() const;
    ArrayList<size-1, T> &tail();

    /// Read-only access to an element of the ArrayList.
    const T &operator[](unsigned i) const;
    /// Read-write access to an element of the ArrayList.
    T &operator[](unsigned i);

    /// Return an ArrayList that contains all but the given element.
    ArrayList<size-1, T> minusElement(unsigned i) const;

    bool contains(const T &x) const;
    
    /// String representation.
    std::string toString() const;

  private:

    /// Stores the elements of the list in a pair of an element and a shorter list.
    std::pair<T, ArrayList<size-1, T> > _elements;
};

/// An empty ArrayList. Specialization to end recursion.
/** \tparam T Type of the stored elements.
 */
template <typename T> class ArrayList<1, T> {

  public:

    /// Create an ArrayList with a default-constructed element.
    ArrayList();
    /// Create an ArrayList with element initialized to \p x.
    ArrayList(const T &x);
    ArrayList(T x, ArrayList<0, T>);
    
    /// Return the first element of an ArrayList.
    const T &head() const;
    T &head();
    ArrayList<0, T> tail() const;
    
    /// Read-write access to an element of the ArrayList.
    T &operator[](unsigned);
    /// Read-only access to an element of the ArrayList.
    const T &operator[](unsigned) const;

    /// Return an ArrayList that contains all but the given element.
    ArrayList<0, T> minusElement(unsigned) const;

    bool contains (const T &x) const;
    
    /// Empty String.
    std::string toString() const;

  private:
    
    T element_;
    
};

/// An empty ArrayList. Specialization to end recursion.
/** \tparam T Type of the stored elements.
 */
template <typename T> class ArrayList<0, T> {

  public:

    /// Create an ArrayList with a default-constructed element.
    ArrayList();
    /// Create an ArrayList with element initialized to \p x.
    ArrayList(const T &);
    
    /// Empty String.
    std::string toString() const;
    
};

template<unsigned size, typename T>
bool isPermutation(const ArrayList<size, T> &list1, const ArrayList<size, T> &list2);
template<typename T>
bool isPermutation(const ArrayList<1, T> &list1, const ArrayList<1, T> &list2);

template<typename T> 
ArrayList<1, T> makeArrayList(const T &x0);
template<typename T> 
ArrayList<2, T> makeArrayList(const T &x0, const T &x1);
template<typename T> 
ArrayList<3, T> makeArrayList(const T &x0, const T &x1, const T &x2);
template<typename T> 
ArrayList<4, T> makeArrayList(const T &x0, const T &x1, const T &x2, const T &x3);
template<typename T> 
ArrayList<5, T> makeArrayList(const T &x0, const T &x1, const T &x2, const T &x3, const T &x4);
template<typename T> 
ArrayList<6, T> makeArrayList(const T &x0, const T &x1, const T &x2, const T &x3, const T &x4,
                              const T &x5);
template<typename T> 
ArrayList<7, T> makeArrayList(const T &x0, const T &x1, const T &x2, const T &x3, const T &x4,
                              const T &x5, const T &x6);
template<typename T> 
ArrayList<8, T> makeArrayList(const T &x0, const T &x1, const T &x2, const T &x3, const T &x4,
                              const T &x5, const T &x6, const T &x7);
template<typename T> 
ArrayList<9, T> makeArrayList(const T &x0, const T &x1, const T &x2, const T &x3, const T &x4,
                              const T &x5, const T &x6, const T &x7, const T &x8);
template<typename T> 
ArrayList<10, T> makeArrayList(const T &x0, const T &x1, const T &x2, const T &x3, const T &x4,
                               const T &x5, const T &x6, const T &x7, const T &x8, const T &x9);

#endif // ARRAYLIST_H
