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

Rotope::Rotope(const QString &name): Object(name, 0, 0) {
    Extrude<3,0,2> cube;
    std::cerr << "cube: "; cube.print();

    const unsigned DIM = 4;
    Extrude<DIM, 0, DIM-1> E;
    std::cerr << "Extrude: "; E.print();

    const unsigned BASE = 0;
    Extrude<DIM, 0, BASE> E2;
    Taper<DIM, BASE+1, DIM-1> T(E2);
    std::cerr << "Taper: "; T.print();

    throw NotYetImplementedException("Rotope::Rotope()");
}

Rotope::~Rotope() { }

/// Transforms a Rotope
/** @param R Rotation
 *  @param T Translation
 */
void Rotope::Transform (const VecMath::Rotation<4> &R,
                        const VecMath::Vector<4> &T) {
    Matrix<4> Rot(R);
    for (unsigned i = 0; i < _rotope->X().size(); i++) {
        X[i] = _rotope->X()[i];  /// \todo copy the vertices only once
        Xtrans[i] = (Rot*X[i])+T;
    }
}

/// Draw the projected Rotope (onto screen or into GL list, as it is)
void Rotope::Draw () {
    glBegin (GL_QUADS); {
    for (unsigned i = 0; i < _rotope->_surface.size(); i++)
        for (unsigned j = 0; j < 4; j++) {
            setVertex(_rotope->X()[_rotope->_surface[j][i]],
                      Xscr[_rotope->_surface[j][i]]);
        }
    }
    glEnd ();
}
