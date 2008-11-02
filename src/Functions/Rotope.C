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
    const unsigned DIM = 10;
    Extrude<DIM, 0, DIM-1> E;
    std::cerr << "Extrude: "; E.print();

    const unsigned BASE = 0;
    Extrude<DIM, 0, BASE> E2;
    Taper<DIM, BASE, DIM-1> T(E2);
    std::cerr << "Taper: "; T.print();
    throw NotYetImplementedException("Rotope::Rotope()");
}

Rotope::~Rotope() { }
