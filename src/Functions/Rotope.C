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

using VecMath::Vector;
using VecMath::Matrix;

class RotopeFactory {
    vertex_data<4> *generate(unsigned extrude, unsigned taper = 0,
                             unsigned rotate = 0, unsigned torate = 0) {
        if (extrude+taper+rotate+torate != 4)
            throw std::logic_error("Sum of extrusion operations must be 4");

        vertex_data<4> *tmp;
        switch(extrude) {
            case 0:
                tmp = new Extrude<4, 0, 0>();
                break;
            case 1:
                tmp = new Extrude<4, 0, 1>();
                break;
            case 2:
                tmp = new Extrude<4, 0, 2>();
                break;
            case 3:
                tmp = new Extrude<4, 0, 3>();
                break;
        }
        switch(taper) {
            case 1:
                tmp = new Taper<4, 3, 3>(*tmp);
                break;
            case 2:
                tmp = new Taper<4, 2, 3>(*tmp);
                break;
            case 3:
                tmp = new Taper<4, 1, 3>(*tmp);
                break;
        }
    }
};

Rotope::Rotope(): Object("Generic Rotope", 0, 0), _rotope(0) {
/*
    Extrude<DIM, 0, DIM-1> E;
    std::cerr << "Extrude: "; E.print();

    const unsigned BASE = 0;
    Extrude<DIM, 0, BASE> E2;
    Taper<DIM, BASE+1, DIM-1> T(E2);
    std::cerr << "Taper: "; T.print();
*/
    _rotope = new Extrude<DIM, 0, DIM-1>();
    setX(project<4>(_rotope->X(), 0., 0.));

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
        Xtrans.at(i) = (Rot*X.at(i))+T;
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
            setVertex(X[_rotope->_surface[i][j]],
                      Xscr[_rotope->_surface[i][j]]);
        }
    }
    glEnd ();
}
