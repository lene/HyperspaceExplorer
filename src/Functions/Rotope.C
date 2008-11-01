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
#include "Extrusion.H"
#include "Taper.H"

Rotope::Rotope(const QString &name): Object(name, 0, 0) {
    Extrude<4, 0, 3> E;
    std::cerr << "Extrude: "; E.print();

    const unsigned DIM = 10;
    const unsigned BASE = 0;
    Extrude<DIM, 0, BASE> E2;
    taper_base<DIM> t(E2);
    for (unsigned i = BASE+1; i < DIM; i++) {
        t.taper(i);
        std::cerr << "taper_base::taper(" << i <<") "; t.print();
    }
    throw NotYetImplementedException("Rotope::Rotope()");
}

Rotope::~Rotope() { }
