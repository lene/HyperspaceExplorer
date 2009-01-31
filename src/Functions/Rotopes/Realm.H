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
/// ...
/**
 *  \param D Dimension of the vector space we're working in
 *
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D> class Realm {
    public:
        unsigned size() const { return _subrealm.size(); }
        void print() const { _subrealm.print(); }

    private:
        uintvec<D> _subrealm;
};

#endif