//
// C++ Implementation: uintvec
//
// Description:
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "uintvec.H"

namespace VecMath {

    template<> std::ostream& operator<<(std::ostream& s,
                                        uintvec<1> const& v) {
        s << "(";
        copy(v.begin(), v.end(), std::ostream_iterator<unsigned>(s, " "));
        s << ")";
        return s;
    }

}