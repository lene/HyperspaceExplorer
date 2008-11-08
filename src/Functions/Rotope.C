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
#include "Rotate.H"
#include "Torate.H"
#include "RotopeFactory.H"

using VecMath::Vector;
using VecMath::Matrix;

Rotope::Rotope(): Object("Rotope", 0, 0), _rotope(0) {
    _rotope = new Extrude<DIM, 0, DIM-1>();
    setX(_rotope->vertices());

    Object::Initialize();
}

Rotope::Rotope(const std::string &actions):
        Object(QString("Rotope: ")+actions.c_str(), 0, 0), _rotope(0) {
//    _rotope = RotopeFactory::generate(actions);
//    setX(_rotope->vertices());

    Object::Initialize();
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

    for (unsigned i = 0; i < X.size(); i++) {
        Xtrans[i] = (Rot*X[i])+T;
    }

}

/// Draw the projected Rotope (onto screen or into GL list, as it is)
void Rotope::Draw () {
    if (!_rotope) {
        throw std::logic_error("Rotope::Draw(): _rotope is NULL!");
    }
    glBegin (GL_QUADS); {
    for (unsigned i = 0; i < _rotope->surface().size(); i++)
        for (unsigned j = 0; j < 4; j++) {
            setVertex(X[_rotope->surface()[i][j]],
                      Xscr[_rotope->surface()[i][j]]);
        }
    }
    glEnd ();
}

