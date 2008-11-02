///
/// C++ Implementation: Rotope
///
/// Description:
///
///
/// \author Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///

#include "Matrix.H"

#include "Rotope.H"
#include "Extrude.H"
#include "Taper.H"

using VecMath::Vector;
using VecMath::Matrix;

Rotope::Rotope(const QString &name): Object(name, 0, 0), _rotope(0) {
    const unsigned DIM = 4;
    Extrude<DIM, 0, DIM-1> E;
    std::cerr << "Extrude: "; E.print();

    const unsigned BASE = 0;
    Extrude<DIM, 0, BASE> E2;
    Taper<DIM, BASE+1, DIM-1> T(E2);
    std::cerr << "Taper: "; T.print();

//    throw NotYetImplementedException("Rotope::Rotope()");
    _rotope = new Extrude<4, 0, 3>();
}

Rotope::~Rotope() {
    if (_rotope) delete _rotope;
}

/// Transforms a Rotope
/** @param R Rotation
 *  @param T Translation
 */
void Rotope::Transform(const VecMath::Rotation<4> &R,
                       const VecMath::Vector<4> &T) {
    if (!_rotope) {
        throw std::logic_error("Rotope::Transform(): _rotope is NULL!");
    }
    Matrix<4> Rot(R);
    for (unsigned i = 0; i < _rotope->X().size(); i++) {
        X[i] = _rotope->X()[i];  /// \todo copy the vertices only once
        Xtrans[i] = (Rot*X[i])+T;
    }
}

/// Draw the projected Rotope (onto screen or into GL list, as it is)
void Rotope::Draw () {
    if (!_rotope) {
        throw std::logic_error("Rotope::Draw(): _rotope is NULL!");
    }
    glBegin (GL_QUADS); {
    for (unsigned i = 0; i < _rotope->_surface.size(); i++)
        for (unsigned j = 0; j < 4; j++) {
            setVertex(_rotope->X()[_rotope->_surface[j][i]],
                      Xscr[_rotope->_surface[j][i]]);
        }
    }
    glEnd ();
}
