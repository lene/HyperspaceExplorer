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

Rotope::Rotope(): Object("Rotope: Hypercube", 0, 0),
        _actions("EEEE"), _rotope(0) {
    Initialize();
}

Rotope::Rotope(const std::string &actions):
        Object(QString("Rotope: ")+actions.c_str(), 0, 0),
        _actions(actions), _rotope(0) {
    Initialize();
}

Rotope::~Rotope() {
    if (_rotope) delete _rotope;
}

void Rotope::Initialize() {
    try {
        _rotope = RotopeFactory::generate(_actions);
        declareParameter("Generator", _actions);
        for(unsigned i = 5; i <= _actions.length(); ++i) {
            string label = Globals::Instance().itoa(i)+string("D Rotation");
            std::cerr << label << std::endl;
            declareParameter(label,
                             VecMath::Rotation<5>());
        }
    } catch (BadRotopeOperation e) {
        declareParameter("Generator", string(DIM, 'E'));
        _rotope = new Extrude<DIM, 0, DIM-1>();
        /** \todo Show the warning in a QMessageBox. Currently that does not work
         *  because C4DView::RenderScene() is called before the object has been
         *  fully initialized.
         */
        /*
        QMessageBox::warning (NULL,
        QString("Rotope::Rotope(")+actions.c_str()+")",
        e.what());
        */
        std::cerr << e.what() << std::endl
                << "Rendering " << DIM << "-dimensional hypercube instead."
                << std::endl;
    } catch (NotYetImplementedException e) {
        declareParameter("Generator", string(DIM, 'E'));
        _rotope = new Extrude<DIM, 0, DIM-1>();
        /// \todo See above
        std::cerr << e.what() << std::endl;
    }

    setX(_rotope->vertices());

    Object::Initialize();

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

    unsigned currentPolygonSize = 0;
    for (unsigned i = 0; i < _rotope->surface().size(); i++) {
        if (currentPolygonSize != _rotope->surface()[i].size()) {
            if (currentPolygonSize) glEnd ();
            currentPolygonSize = _rotope->surface()[i].size();
            if (currentPolygonSize == 4) glBegin (GL_QUADS);
            else if (currentPolygonSize == 3) glBegin (GL_TRIANGLES);
            else throw NotYetImplementedException("Rotope::Draw(): Polygons");
        }
        for (unsigned j = 0; j < currentPolygonSize; j++) {
            setVertex(X[_rotope->surface()[i][j]],
                      Xscr[_rotope->surface()[i][j]]);
        }
    }
    glEnd ();
}

