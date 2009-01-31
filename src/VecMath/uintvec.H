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

#include <vector>
#include <iostream>
#include <iterator>

namespace VecMath {

    /// A \p D -dimensionally nested vector of unsigned ints
    /** As always, an example is more illustrative than a lengthy description:
    *  \code
    *    uintvec<1> v1;
    *    v[i] = 1;
    *    uintvec<2> v2;
    *    v[i][j] = 1;
    *    uintvec<4> v4;
    *    v[i][j][k][l] = 1;
    *  \endcode
    *  This class emulates the std::vector interface to the extent that it is used
    *  in HyperspaceExplorer. It does not inherit from std::vector, but it behaves
    *  like one.
    *
    *  \param D Dimensionality (nesting depth) of the vector
    *
    *  \ingroup VecMath
    *  \author Helge Preuss <scout@hyperspace-travel.de>
    */
    template <unsigned D> class uintvec: public uintvec<D-1> {

        public:
            /// Construct an empty uintvec
            uintvec(): _data() { }

            /// Iterator type to loop over elements, read/write - from std::vector
            typedef typename std::vector<uintvec<D-1> >::iterator iterator;

            /// Iterator type to loop over elements, read only - from std::vector
            typedef typename std::vector<uintvec<D-1> >::const_iterator const_iterator;

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
            void push_back(const uintvec<D-1> &x) { data().push_back(x); }

            /// Remove element at given position
            /** \param position Iterator pointing to element to be erased
            *  \return An iterator pointing to the next element (or end())
            */
            iterator erase(iterator position) { return data().erase(position); }

            /// Subscript access to the data contained in the vector
            /** \param i The index of the element for which data should be accessed
            *  \return Read/write reference to data.
            */
            uintvec<D-1> &operator [] (unsigned i) {
                return data()[i];
            }

            /// Subscript access to the data contained in the vector
            /** \param i The index of the element for which data should be accessed
            *  \return Read-only (constant) reference to data.
            */
            const uintvec<D-1> &operator [] (unsigned i) const {
                return data()[i];
            }

            /// Returns the number of elements in the vector
            unsigned size() const { return data().size(); }

            /// Returns true if the vector is empty. (Thus begin() would equal end().)
            unsigned empty() const { return data().empty(); }

            /// Returns true if \p other is not equal to \p this
            /** \param other uintvec<D> to compare to */
            bool operator != (const uintvec<D> &other) {
                return data() != other.data();
            }

            /// Prints the elements of the vector
            void print() const {
                for (typename std::vector<uintvec<D-1> >::const_iterator i = data().begin();
                    i != data().end(); ++i) {
                        i->print();
                    }
            }

        protected:
            /// Access to the stored vector
            std::vector<uintvec<D-1> > &data() { return _data; }

            /// Read-only access to the stored vector
            const std::vector<uintvec<D-1> > &data() const { return _data; }

        private:
            /// A std::vector of dimensionality \p D - 1
            /** All operations are delegated to this vector. */
            std::vector<uintvec<D-1> > _data;
    };

    /// Specialization of uintvec<D> for \p D = 1
    template<> class uintvec<1> {
        public:
            /// See uintvec<D>::uintvec()
            uintvec(): _data() { }

            /// See uintvec<D>::iterator
            typedef std::vector<unsigned>::iterator iterator;
            /// See uintvec<D>::const_iterator
            typedef std::vector<unsigned>::const_iterator const_iterator;

            /// See uintvec<D>::begin()
            iterator begin() { return data().begin(); }
            /// See uintvec<D>::end()
            iterator end() { return data().end(); }
            /// See uintvec<D>::begin()
            const_iterator begin() const { return data().begin(); }
            /// See uintvec<D>::end()
            const_iterator end() const { return data().end(); }

            /// See uintvec<D>::push_back()
            void push_back(const unsigned &x) { data().push_back(x); }

            /// See uintvec<D>::erase()
            iterator erase(iterator position) { return data().erase(position); }

            /// See uintvec<D>::operator []()
            unsigned &operator [] (unsigned i) { return data()[i]; }
            /// See uintvec<D>::operator []()
            const unsigned &operator [] (unsigned i) const {
                return data()[i];
            }

            /// See uintvec<D>::size()
            unsigned size() const { return data().size(); }
            /// See uintvec<D>::empty()
            unsigned empty() const { return data().empty(); }

            /// See uintvec<D>::operator !=()
            bool operator != (const uintvec<1> &other) {
                return data() != other.data();
            }

            /// See uintvec<D>::print()
            void print() const {
                for (std::vector<unsigned>::const_iterator i = data().begin();
                    i != data().end(); ++i) {
                        std::cerr << *i << " ";
                    }
            }

        protected:
            /// See uintvec<D>::data()
            std::vector<unsigned> &data() { return _data; }
            /// See uintvec<D>::data()
            const std::vector<unsigned> &data() const { return _data; }

        private:
            /// std::vector<unsigned>. All operations are delegated to this vector
            std::vector<unsigned> _data;
    };

    /// Print a uintvec<D> on a std::ostream
    /** \param s The ostream to which \p v is sent
     *  \param v The vector to print
     *  \return \p s
     */
    template<unsigned D> std::ostream& operator<<(std::ostream& s,
                                                  uintvec<D> const& v) {
        s << "(";
        copy(v.begin(), v.end(), std::ostream_iterator<uintvec<D-1> >(s, " "));
        s << ")";
        return s;
    }

    /// Print a uintvec<1> on a std::ostream
    /** \param s The ostream to which \p v is sent
     *  \param v The vector to print
     *  \return \p s
     */
    template<> std::ostream& operator<<(std::ostream& s, uintvec<1> const& v);

    /// Find an element in a uintvec
    /** \param find_me The element to find in the vector \p v
    *  \param v The vector to search for element \p find_me
    *  \return The \p uintvec<D>::iterator pointing to the element or \p v.end() if
    *          it is not in \p v
    */
    template <unsigned D> typename uintvec<D>::iterator find(uintvec<D-1> const &find_me,
                                                             uintvec<D> &v) {
        typename uintvec<D>::iterator i = v.begin();
        while(*i != find_me && i != v.end()) ++i;
        return i;
    }
}
#endif
