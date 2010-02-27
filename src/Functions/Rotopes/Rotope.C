///
/// C++ Implementation: Rotope
///
/// Description:
///
///
/// \author Lene Preuss <lene.preuss@gmail.com>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///

#include "Matrix.h"

#include "Rotope.h"
#include "Extrude.h"
#include "Taper.h"
#include "Rotate.h"
#include "Torate.h"
#include "RotopeFactory.h"

using std::vector;
using std::cerr;
using std::endl;

using VecMath::Vector;
using VecMath::Matrix;
using VecMath::Rotation;

Rotope::Rotope(): Object("Rotope: Hypercube", 0, 0),
        _actions("EEEE"), _rotope(0) {
    Initialize();
}

Rotope::Rotope(const std::string &actions):
        Object(QString("Rotope: ")+actions.c_str(), 0, 0),
         _rot5D(), _rot6D(), _rot7D(), _rot8D(), _rot9D(), _rot10D(),
        _numSegments(6), _actions(actions), _rotope(0) {
    Initialize();
}

Rotope::~Rotope() {
    if (_rotope) delete _rotope;
}

void Rotope::Initialize() {
    SingletonLog::Instance().log(__PRETTY_FUNCTION__);

    try {
        _rotope = RotopeFactory::generate(_actions);
        declareParameter("Generator", _actions);
        for(unsigned i = 5; i <= _actions.length(); ++i) {
            string label = Globals::Instance().itoa(i)+string("D Rotation");
            switch(i) {
                case 5:
                    declareParameter(label, _rot5D);
                    break;
                case 6:
                    declareParameter(label, _rot6D);
                    break;
                case 7:
                    declareParameter(label, _rot7D);
                    break;
                case 8:
                    declareParameter(label, _rot8D);
                    break;
                case 9:
                    declareParameter(label, _rot9D);
                    break;
                case 10:
                    declareParameter(label, _rot10D);
                    break;
            }
        }
        declareParameter("Rotation segments", _numSegments);
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
        cerr << e.what() << endl
                << "Rendering " << DIM << "-dimensional hypercube instead."
                << endl;
    } catch (NotYetImplementedException e) {
        declareParameter("Generator", string(DIM, 'E'));
        _rotope = new Extrude<DIM, 0, DIM-1>();
        /// \todo See above
        cerr << e.what() << endl;
    }

    SingletonLog::Instance() << getParameters().print();
    for (unsigned i = 5; i <= _rotope->dimension(); ++i) {
        _rotope->addTransform(i, new VecMath::Rotation<5>());
    }

    setX(_rotope->vertices());

    Object::Initialize();

}

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

void Rotope::Draw () {
    if (!_rotope) {
        throw std::logic_error("Rotope::Draw(): _rotope is NULL!");
    }

    if (_rotope->realm().size()) {
        Draw(_rotope->realm());
        _rotope->print();
    } else {
        throw new std::logic_error("Rotope has no Realm member");
#       if false
        cerr << "Drawing surfaces" << endl;
        unsigned currentPolygonSize = 0;
        for (unsigned i = 0; i < _rotope->surface().size(); i++) {
            if (currentPolygonSize != _rotope->surface()[i].size()) {
                if (currentPolygonSize) glEnd ();
                currentPolygonSize = _rotope->surface()[i].size();
                if (currentPolygonSize == 4) glBegin (GL_QUADS);
                else if (currentPolygonSize == 3) glBegin (GL_TRIANGLES);
                else glBegin(GL_POLYGON);
            }
            for (unsigned j = 0; j < currentPolygonSize; j++) {
                setVertex(X[_rotope->surface()[i][j]],
                        Xscr[_rotope->surface()[i][j]]);
            }
            if (currentPolygonSize > 4) glEnd();
        }
        glEnd ();
#       endif
    }
}

void Rotope::Draw(const Realm &realm) {
    switch (realm.dimension()) {
        case 0:
            /** Dimension 0 is a point. Easy to draw ;-) */
            glBegin(GL_POINTS);
                setVertex(X[realm], Xscr[realm]);
            glEnd();
            break;
        case 1:
            /** In one dimension draw a line containing all points the Realm has
             *  (i.e. 2 points)
             */
            glBegin(GL_LINES);
                for (vector<Realm>::const_iterator i = realm.getSubrealms().begin();
                    i != realm.getSubrealms().end(); ++i) {
                   setVertex(X[*i], Xscr[*i]);
                }
            glEnd();
            break;
        case 2:
            /** In two dimensions, draw a surface. The current implementation
             *  represents two dimensional surfaces as vector of the form
             *  \code (0, 1, ..., n) \endcode
             */
            if (realm.getSubrealms().begin()->dimension() == 0) {
                glBegin(GL_POLYGON);
                    for (vector<Realm>::const_iterator i = realm.getSubrealms().begin();
                         i != realm.getSubrealms().end(); ++i) {
                        setVertex(X[*i], Xscr[*i]);
                    }
                glEnd();
            } else if (realm.getSubrealms().begin()->dimension() == 1) {
                for (vector<Realm>::const_iterator i = realm.getSubrealms().begin();
                     i != realm.getSubrealms().end(); ++i) {
                    Draw(*i);
                }
            }
            else throw std::logic_error("Realm contains a subrealm whose dimension is equal or greater than its own. Duh.");
            break;
        default:
            /** OpenGL does not allow to draw anything above the dimension of a
             *  surface. Recurse to draw the lower order realms, until we find
             *  surfaces.
             */
            for (vector<Realm>::const_iterator i = realm.getSubrealms().begin();
                 i != realm.getSubrealms().end(); ++i) {
                Draw(*i);
            }
            break;
    }
}

void Rotope::SetParameters(const ParameterMap &parms) {
#   if 1
        for (ParameterMap::const_iterator i = parms.begin();
             i != parms.end(); ++i) {
            if (i->second->getName() == "Generator") {
                _actions = std::string(*i->second);
            }
            if (i->second->getName() == "Rotation segments") {
                _numSegments = unsigned(*i->second);
            }
            if (i->second->getName() == "5D Rotation") {
                _rot5D =  VecMath::Rotation<5>(*i->second);
                std::cerr << "5D Rotation : " << _rot5D << "\n";
            }
            if (i->second->getName() == "6D Rotation") {
                _rot6D =  VecMath::Rotation<6>(*i->second);
                std::cerr << "6D Rotation : " << _rot6D << "\n";
            }
            if (i->second->getName() == "7D Rotation") {
                _rot7D =  VecMath::Rotation<7>(*i->second);
                std::cerr << "7D Rotation : " << _rot7D << "\n";
            }
            if (i->second->getName() == "8D Rotation") {
                _rot8D =  VecMath::Rotation<8>(*i->second);
                std::cerr << "8D Rotation : " << _rot8D << "\n";
            }
            if (i->second->getName() == "9D Rotation") {
                _rot9D =  VecMath::Rotation<9>(*i->second);
                std::cerr << "9D Rotation : " << _rot9D << "\n";
            }
            if (i->second->getName() == "10D Rotation") {
                _rot5D =  VecMath::Rotation<5>(*i->second);
                std::cerr << "10D Rotation : " << _rot10D << "\n";
            }

        }
#   else
        setParameter(parms, this->_actions, "Generator");
#   endif
}
