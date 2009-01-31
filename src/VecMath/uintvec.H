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

#include <vector>
#include <iostream>
#include <iterator>

template <unsigned D> class uintvec: public uintvec<D-1> {

    public:
        typedef typename std::vector<uintvec<D-1> >::iterator iterator;
        typedef typename std::vector<uintvec<D-1> >::const_iterator const_iterator;

        iterator begin() { return data().begin(); }
        iterator end() { return data().end(); }
        const_iterator begin() const { return data().begin(); }
        const_iterator end() const { return data().end(); }

        void push_back(const uintvec<D-1> &x) { data().push_back(x); }

        iterator erase(iterator position) { return data().erase(position); }

        uintvec<D-1> &operator [] (unsigned i) {
            return data()[i];
        }
        const uintvec<D-1> &operator [] (unsigned i) const {
            return data()[i];
        }

        unsigned size() const { return data().size(); }
        unsigned empty() const { return data().empty(); }

        bool operator != (const uintvec<D> &other) {
            return data() != other.data();
        }

        void print() const {
            for (typename std::vector<uintvec<D-1> >::const_iterator i = data().begin();
                 i != data().end(); ++i) {
                     i->print();
                 }
        }

    protected:
        std::vector<uintvec<D-1> > &data() { return _data; }
        const std::vector<uintvec<D-1> > &data() const { return _data; }

    private:
        std::vector<uintvec<D-1> > _data;
};

template<> class uintvec<1> {
    public:
        typedef std::vector<unsigned>::iterator iterator;
        typedef std::vector<unsigned>::const_iterator const_iterator;

        iterator begin() { return data().begin(); }
        iterator end() { return data().end(); }
        const_iterator begin() const { return data().begin(); }
        const_iterator end() const { return data().end(); }

        void push_back(const unsigned &x) { data().push_back(x); }

        iterator erase(iterator position) { return data().erase(position); }

        unsigned &operator [] (unsigned i) {
            return data()[i];
        }
        const unsigned &operator [] (unsigned i) const {
            return data()[i];
        }

        unsigned size() const { return data().size(); }
        unsigned empty() const { return data().empty(); }

        bool operator != (const uintvec<1> &other) {
            return data() != other.data();
        }

        void print() const {
            for (std::vector<unsigned>::const_iterator i = data().begin();
                 i != data().end(); ++i) {
                     std::cerr << *i << " ";
                 }
        }

    protected:
        std::vector<unsigned> &data() { return _data; }
        const std::vector<unsigned> &data() const { return _data; }

    private:
        std::vector<unsigned> _data;
};

/// Print a std::vector on a std::ostream
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

template<> std::ostream& operator<<(std::ostream& s, uintvec<1> const& v);

/// Find an element in a vector
/** \param find_me The element to find in the vector \p v
 *  \param v The vector to search for element \p find_me
 *  \return The \p vector<T>::iterator pointing to the element or \p v.end() if it is not in \p v
 */
template <unsigned D> typename uintvec<D>::iterator find(uintvec<D-1> find_me, uintvec<D> &v) {
    typename uintvec<D>::iterator i = v.begin();
    while(*i != find_me && i != v.end()) ++i;
    return i;
}
