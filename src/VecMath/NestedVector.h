//
// C++ Interface: NestedVector
//
// Description:
//
//
// Author: Helge Preuss <lene.preuss@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef NESTED_VECTOR_H
#define NESTED_VECTOR_H

#include <vector>
#include <iostream>
#include <iterator>

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
    *  \param T Type that is eventually stored
    *  \param D Dimensionality (nesting depth) of the vector
    *
    *  \ingroup VecMath
    *  \author Helge Preuss <lene.preuss@gmail.com>
    */
    template <typename T, unsigned D> class NestedVector: public NestedVector<T, D-1> {

        public:
            /// Iterator type to loop over elements, read/write - from std::vector
            typedef typename std::vector<NestedVector<T, D-1> >::iterator iterator;

            /// Iterator type to loop over elements, read only - from std::vector
            typedef typename std::vector<NestedVector<T, D-1> >::const_iterator
                    const_iterator;

            /// Construct an empty NestedVector
            NestedVector(): _data() { }

            /// Construct an NestedVector with \p n empty elements
            NestedVector(unsigned n): _data(n) { }

            /// Construct a NestedVector from an iterator range
            NestedVector(typename std::vector<NestedVector<T, D-1> >::iterator first,
                         typename std::vector<NestedVector<T, D-1> >::iterator last):
                    NestedVector<T, D-1>(),
                    _data(first, last) { }

            /// Copy construct a NestedVector
            NestedVector(const NestedVector<T, D> &v): NestedVector<T, D-1>(),
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
            void push_back(const NestedVector<T, D-1> &x) { data().push_back(x); }

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
            NestedVector<T, D-1> &operator [] (unsigned i) {
                return data()[i];
            }

            /// Subscript access to the data contained in the vector
            /** \param i The index of the element for which data should be accessed
             *  \return Read-only (constant) reference to data.
             */
            const NestedVector<T, D-1> &operator [] (unsigned i) const {
                return data()[i];
            }

            /// Returns the number of elements in the vector
            unsigned size() const { return data().size(); }

            /// Returns true if the vector is empty. (Thus begin() would equal end().)
            unsigned empty() const { return data().empty(); }

            /// Resizes the vector to the specified number of elements
            /** \param new_size Number of elements the vector should contain */
            void resize(unsigned new_size) { data().resize(new_size); }

            /// Resizes the vector to the specified number of elements
            /** \param new_size Number of elements the vector should contain
             *  \param x Data with which new elements should be populated
             */
            void resize(unsigned new_size, NestedVector<T, D-1> x) {
            	data().resize(new_size, x);
            }

            /// Returns true if \p other is not equal to \p this
            /** \param other NestedVector<T, D> to compare to */
            bool operator == (const NestedVector<T, D> &other) const {
                return data() == other.data();
            }

            /// Returns true if \p other is not equal to \p this
            /** \param other NestedVector<T, D> to compare to */
            bool operator != (const NestedVector<T, D> &other) const {
                return data() != other.data();
            }

            /// Prints the elements of the vector
            void print() const {
                std::cerr << "< ";
                for (typename std::vector<NestedVector<T, D-1> >::const_iterator
                     i = data().begin();
                     i != data().end(); ++i) {
                        i->print();
                    }
                std::cerr << " >";
            }

        protected:
            /// Access to the stored vector
            std::vector<NestedVector<T, D-1> > &data() { return _data; }

            /// Read-only access to the stored vector
            const std::vector<NestedVector<T, D-1> > &data() const { return _data; }

        private:
            /// A std::vector of dimensionality \p D - 1
            /** All operations are delegated to this vector. */
            std::vector<NestedVector<T, D-1> > _data;
    };

    /// Specialization of NestedVector<T, D> for \p D = 1
    template<typename T> class NestedVector<T, 1> {
        public:
            /// See NestedVector<T, D>::iterator
            typedef typename std::vector<T>::iterator iterator;
            /// See NestedVector<T, D>::const_iterator
            typedef typename std::vector<T>::const_iterator const_iterator;

            /// See NestedVector<T, D>::NestedVector()
            NestedVector(): _data() { }
            /// See NestedVector<T, D>::NestedVector()
            NestedVector(unsigned n): _data(n) { }

            /// See NestedVector<T, D>::begin()
            iterator begin() { return data().begin(); }
            /// See NestedVector<T, D>::end()
            iterator end() { return data().end(); }
            /// See NestedVector<T, D>::begin()
            const_iterator begin() const { return data().begin(); }
            /// See NestedVector<T, D>::end()
            const_iterator end() const { return data().end(); }

            /// See NestedVector<T, D>::push_back()
            void push_back(const T &x) { data().push_back(x); }

            /// See NestedVector<T, D>::erase()
            iterator erase(iterator position) { return data().erase(position); }

            /// Remove elements at given range
            /** \param first Iterator pointing to first element to be erased
             *  \param last Iterator pointing to one past the last element to be erased. 
             *  \return An iterator pointing to the next element (or end())
             */
            iterator erase(iterator first, iterator last) { return data().erase(first, last); }

            /// See NestedVector<T, D>::operator []()
            T &operator [] (unsigned i) { return data()[i]; }
            /// See NestedVector<T, D>::operator []()
            const T &operator [] (unsigned i) const {
                return data()[i];
            }

            /// See NestedVector<T, D>::size()
            unsigned size() const { return data().size(); }
            /// See NestedVector<T, D>::empty()
            unsigned empty() const { return data().empty(); }

            /// See NestedVector<T, D>::resize()
            void resize(unsigned new_size) { data().resize(new_size); }

            /// Resizes the vector to the specified number of elements
            /** \param new_size Number of elements the vector should contain
             *  \param x Data with which new elements should be populated
             */
            void resize(unsigned new_size, unsigned x) {
            	data().resize(new_size, x);
            }

            /// See NestedVector<T, D>::operator ==()
            bool operator == (const NestedVector<T, 1> &other) const {
                return data() == other.data();
            }

            /// See NestedVector<T, D>::operator !=()
            bool operator != (const NestedVector<T, 1> &other) {
                return data() != other.data();
            }

            /// See NestedVector<T, D>::print()
            void print() const {
                std::cerr << "< ";
                for (typename std::vector<T>::const_iterator i = data().begin();
                     i != data().end(); ++i) {
                        std::cerr << *i << " ";
                    }
                std::cerr << "> ";
            }

        protected:
            /// See NestedVector<T, D>::data()
            std::vector<T> &data() { return _data; }
            /// See NestedVector<T, D>::data()
            const std::vector<T> &data() const { return _data; }

        private:
            /// std::vector<T>. All operations are delegated to this vector
            std::vector<T> _data;
    };

    /// Print a NestedVector<T, D> on a std::ostream
    /** \param s The ostream to which \p v is sent
     *  \param v The vector to print
     *  \return \p s
     *  \ingroup VecMath
     */
    template<typename T, unsigned D> std::ostream& operator<<(std::ostream& s,
                                                  NestedVector<T, D> const& v) {
        s << "(";
        copy(v.begin(), v.end(), std::ostream_iterator<NestedVector<T, D-1> >(s, " "));
        s << ")";
        return s;
    }

    /// Print a NestedVector<T, 1> on a std::ostream
    /** \param s The ostream to which \p v is sent
     *  \param v The vector to print
     *  \return \p s
     *  \ingroup VecMath
     */
    template<typename T> std::ostream& operator<<(std::ostream& s,
                                                  NestedVector<T, 1> const& v) {
        s << "(";
        copy(v.begin(), v.end(), std::ostream_iterator<T>(s, " "));
        s << ")";
        return s;
    }

    /// Find an element in a NestedVector
    /** \param find_me The element to find in the vector \p v
     *  \param v The vector to search for element \p find_me
     *  \return The \p NestedVector<T,D>::iterator pointing to the element or
     *          \p v.end() if it is not in \p v
     *
     *  \ingroup VecMath
     */
    template <typename T, unsigned D>
            typename NestedVector<T, D>::iterator find(NestedVector<T, D-1> const &find_me,
                                                       NestedVector<T, D> &v) {
        typename NestedVector<T, D>::iterator i = v.begin();
        while(*i != find_me && i != v.end()) ++i;
        return i;
    }

}


#endif
