///
/// C++ Interface: Realm
///
/// Description:
///
///
/// @author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2009
///
/// Copyright: See COPYING file that comes with this distribution
///
/// \ingroup RotopeGroup
///

#ifndef REALM_H
#define REALM_H

#include "uintvec.H"
#include "Vector.H"
class Rotope;

/// \p D - dimensional surface
/**
 *  \param D Dimension of the vector space we're working in
 *
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
class Realm {
    public:

        Realm(): _dimension(0), _subrealm(), _index(1) { }
        Realm(unsigned i): _dimension(0), _subrealm(), _index(i) { }
        Realm(const std::vector<Realm> &sr): _subrealm(sr), _index() {
            if(sr.empty()) _dimension = 0;
            else _dimension = sr[0].dimension()+1;
        }
        ~Realm() { }

        /// Returns the number of subrealms the Realm is made of
        unsigned size() const { return _subrealm.size(); }
        /// Returns the dimension of the realm
        unsigned dimension() const { return _dimension; }
        /// Sets the dimension of the realm
        void setDimension(unsigned d) { _dimension = d; }
        /// Prints the elements of the Realm
        void print() const;

        Realm extrude(unsigned delta);
        Realm taper(unsigned taper_index);
        Realm rotate(unsigned num_segments, unsigned size);
        Realm rotate_step(unsigned index, unsigned base, unsigned delta);

        void add(unsigned delta);

        const std::vector<Realm> &getSubrealms() const { return _subrealm; }
        void setSubrealms(std::vector<Realm> sr) { _subrealm = sr; }

        void push_back(const Realm &r);

        std::vector<Realm>::iterator begin() { return _subrealm.begin(); }
        std::vector<Realm>::iterator end() { return _subrealm.end(); }
        operator unsigned() const { return _index; }
        unsigned &dimension() { return _dimension; }

    private:
        /// Dimension of the realm
        unsigned _dimension;
        /// Subrealms the Realm is made of
        std::vector<Realm> _subrealm;
        /// If _dimension == 0, this is the index into the vertex array
        unsigned _index;
};

#endif