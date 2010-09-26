/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
    Copyright (C) 2009-2010  Lene Preuss <lene.preuss@gmail.com>

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

#ifndef NESTED_VECTOR_H
#define NESTED_VECTOR_H

#include <vector>
#include <iostream>
#include <iterator>

#include <sstream>

namespace VecMath {

    /// A \p D -dimensionally nested std::vector of objects of type \p T
    /** As always, an example is more illustrative than a lengthy description:
    *  \code
    *    NestedVector<unsigned, 1> v1;
    *    v[i] = 1;
    *    uintvec<double, 2> v2;
    *    v[i][j] = 1.0;
    *    uintvec<std::string, 4> v4;
    *    v[i][j][k][l] = "hello, world!";
    *  \endcode
    *  This class emulates the std::vector interface to the extent that it is used
    *  in HyperspaceExplorer. It does not inherit from std::vector, but it behaves
    *  like one.
    *
    *  \tparam T Type that is eventually stored
    *  \tparam D Dimensionality (nesting depth) of the vector
    *
    *  \ingroup VecMath
    *  \author Helge Preuss <lene.preuss@gmail.com>
    */
    template <typename T, unsigned D> 
    class MultiDimensionalVector: public MultiDimensionalVector<T, D-1> {

        public:
            /// Iterator type to loop over elements, read/write - from std::vector
            typedef typename std::vector<MultiDimensionalVector<T, D-1> >::iterator iterator;

            /// Iterator type to loop over elements, read only - from std::vector
            typedef typename std::vector<MultiDimensionalVector<T, D-1> >::const_iterator
                    const_iterator;

            /// Construct an empty NestedVector
            MultiDimensionalVector(): _data() { }

            /// Construct an NestedVector with \p n empty elements
            MultiDimensionalVector(unsigned n): _data(n) { }

            /// Construct a NestedVector from an iterator range
            MultiDimensionalVector(typename std::vector<MultiDimensionalVector<T, D-1> >::iterator first,
                         typename std::vector<MultiDimensionalVector<T, D-1> >::iterator last):
                    MultiDimensionalVector<T, D-1>(),
                    _data(first, last) { }

            /// Copy construct a NestedVector
            MultiDimensionalVector(const MultiDimensionalVector<T, D> &v): 
              MultiDimensionalVector<T, D-1>(),
              _data(v.data()) { }

            /// Iterator that points to the first element in the vector
            iterator begin() { return data().begin(); }

            /// Iterator that points one past the last element in the vector
            iterator end() { return data().end(); }

            /// Read-only iterator that points to the first element in the vector
            const_iterator begin() const { return data().begin(); }

            /// Read-only iterator that points one past the last element in the vector
            const_iterator end() const { return data().end(); }

            /// Add data to the end of the vector
            /** \param x Data to be added */
            void push_back(const MultiDimensionalVector<T, D-1> &x) { data().push_back(x); }

            /// Remove element at given position
            /** \param position Iterator pointing to element to be erased
             *  \return An iterator pointing to the next element (or end())
             */
            iterator erase(iterator position) { return data().erase(position); }

            /// Remove elements at given range
            /** \param first Iterator pointing to first element to be erased
             *  \param last Iterator pointing to one past the last element to be erased.
             *  \return An iterator pointing to the next element (or end())
             */
            iterator erase(iterator first, iterator last) { return data().erase(first, last); }

            /// Subscript access to the data contained in the vector
            /** \param i The index of the element for which data should be accessed
             *  \return Read/write reference to data.
             */
            MultiDimensionalVector<T, D-1> &operator [] (unsigned i) {
                return data()[i];
            }

            /// Subscript access to the data contained in the vector
            /** \param i The index of the element for which data should be accessed
             *  \return Read-only (constant) reference to data.
             */
            const MultiDimensionalVector<T, D-1> &operator [] (unsigned i) const {
                return data()[i];
            }

            /// Returns the number of elements in the vector
            unsigned size() const { return data().size(); }

            /// Returns true if the vector is empty. (Thus begin() would equal end().)
            unsigned empty() const { return data().empty(); }

            /// Erases all the elements, and calls clear() on them recursively.
            void clear();

            /// Resizes the vector to the specified number of elements
            /** \param new_size Number of elements the vector should contain */
            void resize(unsigned new_size) { data().resize(new_size); }

            /// Resizes the vector to the specified number of elements
            /** \param new_size Number of elements the vector should contain
             *  \param x Data with which new elements should be populated
             */
            void resize(unsigned new_size, MultiDimensionalVector<T, D-1> x) {
            	data().resize(new_size, x);
            }

            /// Returns true if \p other is not equal to \p this
            /** \param other NestedVector<T, D> to compare to */
            bool operator == (const MultiDimensionalVector<T, D> &other) const {
                return data() == other.data();
            }

            /// Returns true if \p other is not equal to \p this
            /** \param other NestedVector<T, D> to compare to */
            bool operator != (const MultiDimensionalVector<T, D> &other) const {
                return data() != other.data();
            }

            /// Convert NestedVector to a std::string.
            std::string toString() const {
                std::ostringstream o;
                o << *this;
                return o.str();
            }

            /// Prints the elements of the vector
            void print() const {
                std::cerr << data().size() << " elements: " << "< ";
                for (typename std::vector<MultiDimensionalVector<T, D-1> >::const_iterator
                     i = data().begin();
                     i != data().end(); ++i) {
                        i->print();
                    }
                std::cerr << " >" << std::endl;
            }

        protected:
            /// Access to the stored vector
            std::vector<MultiDimensionalVector<T, D-1> > &data() { return _data; }

            /// Read-only access to the stored vector
            const std::vector<MultiDimensionalVector<T, D-1> > &data() const { return _data; }

        private:
            /// A std::vector of dimensionality \p D - 1
            /** All operations are delegated to this vector. */
            std::vector<MultiDimensionalVector<T, D-1> > _data;
    };

    /// Specialization of NestedVector<T, D> for \p D = 1
    template<typename T> class MultiDimensionalVector<T, 1> {
        public:
            /// See MultiDimensionalVector<T, D>::iterator
            typedef typename std::vector<T>::iterator iterator;
            /// See MultiDimensionalVector<T, D>::const_iterator
            typedef typename std::vector<T>::const_iterator const_iterator;

            /// See MultiDimensionalVector<T, D>::MultiDimensionalVector()
            MultiDimensionalVector(): _data() { }
            /// See MultiDimensionalVector<T, D>::MultiDimensionalVector()
            MultiDimensionalVector(unsigned n): _data(n) { }

            /// See MultiDimensionalVector<T, D>::begin()
            iterator begin() { return data().begin(); }
            /// See MultiDimensionalVector<T, D>::end()
            iterator end() { return data().end(); }
            /// See MultiDimensionalVector<T, D>::begin()
            const_iterator begin() const { return data().begin(); }
            /// See MultiDimensionalVector<T, D>::end()
            const_iterator end() const { return data().end(); }

            /// See MultiDimensionalVector<T, D>::push_back()
            void push_back(const T &x) { data().push_back(x); }

            /// See MultiDimensionalVector<T, D>::erase()
            iterator erase(iterator position) { return data().erase(position); }

            /// Remove elements at given range
            /** \param first Iterator pointing to first element to be erased
             *  \param last Iterator pointing to one past the last element to be erased.
             *  \return An iterator pointing to the next element (or end())
             */
            iterator erase(iterator first, iterator last) { return data().erase(first, last); }

            /// See MultiDimensionalVector<T, D>::operator []()
            T &operator [] (unsigned i) { return data()[i]; }
            /// See MultiDimensionalVector<T, D>::operator []()
            const T &operator [] (unsigned i) const {
                return data()[i];
            }

            /// See MultiDimensionalVector<T, D>::size()
            unsigned size() const { return data().size(); }
            /// See MultiDimensionalVector<T, D>::empty()
            unsigned empty() const { return data().empty(); }

            /// See MultiDimensionalVector<T, D>::clear()
            void clear() { data().clear(); }

            /// See MultiDimensionalVector<T, D>::resize()
            void resize(unsigned new_size) { data().resize(new_size); }

            /// Resizes the vector to the specified number of elements
            /** \param new_size Number of elements the vector should contain
             *  \param x Data with which new elements should be populated
             */
            void resize(unsigned new_size, T x) {
            	data().resize(new_size, x);
            }

            /// See MultiDimensionalVector<T, D>::operator ==()
            bool operator == (const MultiDimensionalVector<T, 1> &other) const {
                return data() == other.data();
            }

            /// See MultiDimensionalVector<T, D>::operator !=()
            bool operator != (const MultiDimensionalVector<T, 1> &other) {
                return data() != other.data();
            }

            /// Convert MultiDimensionalVector to a std::string.
            std::string toString() const {
                std::ostringstream o;
                o << *this;
                return o.str();
            }

            /// See MultiDimensionalVector<T, D>::print()
            void print() const {
                std::cerr << "< ";
                for (typename std::vector<T>::const_iterator i = data().begin();
                     i != data().end(); ++i) {
                        std::cerr << *i << " ";
                    }
                std::cerr << "> ";
            }

            /// Whether to print the number of elements with operator <<().
            static bool print_num_elements() { return PRINT_NUM_ELEMENTS; }
            /// How deep to insert maximally with operator <<().
            static unsigned max_dimension() { return MAX_DIMENSION; }

        protected:
            /// See MultiDimensionalVector<T, D>::data()
            std::vector<T> &data() { return _data; }
            /// See MultiDimensionalVector<T, D>::data()
            const std::vector<T> &data() const { return _data; }

        private:
            /// std::vector<T>. All operations are delegated to this vector.
            std::vector<T> _data;

            /// Compile-time configuration: Whether to print the number of elements with operator <<().
            static const bool PRINT_NUM_ELEMENTS = false;
            /// Compile-time configuration: How deep to insert maximally with operator <<().
            static const unsigned MAX_DIMENSION = 4;
    };

    /// Print a MultiDimensionalVector<T, D> on a std::ostream
    /** \param s The ostream to which \p v is sent
     *  \param v The vector to print
     *  \return \p s
     *  \ingroup VecMath
     */
    template<typename T, unsigned D> std::ostream& operator<<(std::ostream& s,
                                                  MultiDimensionalVector<T, D> const& v) {

        if (MultiDimensionalVector<T, 1>::print_num_elements()) s << v.size() << " elements: ";
        for (unsigned i = MultiDimensionalVector<T, 1>::max_dimension(); i > D; --i) s << "  ";
        s << "(\n";
        copy(v.begin(), v.end(), std::ostream_iterator<MultiDimensionalVector<T, D-1> >(s, "\n"));
        for (unsigned i = MultiDimensionalVector<T, 1>::max_dimension(); i > D; --i) s << "  ";
        s << ")";
        return s;
    }

    /// Print a MultiDimensionalVector<T, 1> on a std::ostream
    /** \param s The ostream to which \p v is sent
     *  \param v The vector to print
     *  \return \p s
     *  \ingroup VecMath
     */
    template<typename T> std::ostream& operator<<(std::ostream& s,
                                                  MultiDimensionalVector<T, 1> const& v) {
        if (MultiDimensionalVector<T, 1>::print_num_elements()) s << v.size() << " elements: ";
        for (unsigned i = MultiDimensionalVector<T, 1>::max_dimension(); i > 1; --i) s << "  ";
        s << "(";
        copy(v.begin(), v.end(), std::ostream_iterator<T>(s, " "));
        for (unsigned i = MultiDimensionalVector<T, 1>::max_dimension(); i > 1; --i) s << "  ";
        s << ")";
        return s;
    }

    /// Find an element in a MultiDimensionalVector
    /** \param find_me The element to find in the vector \p v
     *  \param v The vector to search for element \p find_me
     *  \return The \p MultiDimensionalVector<T,D>::iterator pointing to the element or
     *          \p v.end() if it is not in \p v
     *
     *  \ingroup VecMath
     */
    template <typename T, unsigned D>
            typename MultiDimensionalVector<T, D>::iterator find(MultiDimensionalVector<T, D-1> const &find_me,
                                                       MultiDimensionalVector<T, D> &v) {
        typename MultiDimensionalVector<T, D>::iterator i = v.begin();
        while(*i != find_me && i != v.end()) ++i;
        return i;
    }

    template <typename T, unsigned D> void MultiDimensionalVector<T, D>::clear() {
      for (typename MultiDimensionalVector<T, D>::iterator i = data().begin(); i != data().end(); ++i) {
        i->clear();
      }
      data().clear();
    }
}


#endif
