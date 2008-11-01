///
/// C++ Implementation: ColorManager
///
/// Description:
///
///
/// \author Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///
#include "Rotope.H"

Rotope::Rotope(const QString &name): Object(name, 0, 0) {
    Extrude<4, 0, 3> E;
    std::cerr << "Extrude: "; E.print();
    taper_base<4> t;
    t.taper(0,3);
    std::cerr << "taper_base: "; t.print();
    throw NotYetImplementedException("Rotope::Rotope()");
}


Rotope::~Rotope() { }


