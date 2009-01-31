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
/// \p D - dimensional surface
/**
 *  \param D Dimension of the vector space we're working in
 *
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D> class Realm {
    public:

        Realm(): _subrealm() { }

        /// Returns the number of subrealms the Realm is made of
        unsigned size() const { return _subrealm.size(); }
        /// Prints the elements of the Realm
        void print() const { _subrealm.print(); }

        Realm<D+1> rotate(double step);
        Realm<D> rotate_step(double angle);

        void add(Realm<D> realm);

    private:
        /// Subrealms the Realm is made of
        VecMath::uintvec<D> _subrealm;
};

#endif