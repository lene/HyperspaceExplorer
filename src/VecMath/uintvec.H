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

#include "NestedVector.H"

namespace VecMath {

    template <unsigned D> struct uintvec: public NestedVector<unsigned, D> {
        uintvec(): NestedVector<unsigned, D> () { }
        uintvec(NestedVector<unsigned, D> v): NestedVector<unsigned, D>(v) { }
    };

    template <unsigned D>
            typename uintvec<D>::iterator find(uintvec<D-1> const &find_me,
                                               uintvec<D> &v) {
        typename uintvec<D>::iterator i = v.begin();
        while(*i != find_me && i != v.end()) ++i;
        return i;
    }
}


#endif
