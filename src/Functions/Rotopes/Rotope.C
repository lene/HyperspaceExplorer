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

Rotope::Rotope(): Object(0, 0),
        _actions("EEEE"), _rotope(0) {
    Initialize();
}

Rotope::Rotope(const std::string &actions):
        Object(0, 0),
         _rot5D(), _rot6D(), _rot7D(), _rot8D(), _rot9D(), _rot10D(),
        _numSegments(RotopeInterface::DEFAULT_NUM_SEGMENTS), _actions(actions), _rotope(0) {
    Initialize();
}

Rotope::~Rotope() {
    if (_rotope) delete _rotope;
}

std::string Rotope::getFunctionName() const {
    return "Rotope: "+_actions;
}

void Rotope::Initialize() {
    SingletonLog::Instance().log(__PRETTY_FUNCTION__);

    try {
        RotopeInterface::setRotationSegments(_numSegments);
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
                default:
                    throw BadRotopeOperation("Rotope::Initialize()",
                                             "Rotopes of dimension higher than 10 not supported.");
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

    SingletonLog::Instance() << getParameters().toString();
    for (unsigned i = 5; i <= _rotope->dimension(); ++i) {
        _rotope->addTransform(i, new VecMath::Rotation<5>());
    }

    setX(_rotope->projected_vertices());

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

void Rotope::Draw (UI::View *view) {
    if (!_rotope) {
        throw std::logic_error("Rotope::Draw(): _rotope is NULL!");
    }

    if (_rotope->realm().size()) {
        Draw(_rotope->realm());
//        _rotope->print();
    } else {
        throw new std::logic_error("Rotope has no Realm member");
    }
}

void Rotope::Draw(const Realm &realm) {
    switch (realm.dimension()) {
        case 0:
            /** Dimension 0 is a point. Easy to draw ;-) */
            glBegin(GL_POINTS);
                setVertex(X[realm.toIndex()], Xscr[realm.toIndex()]);
            glEnd();
            break;
        case 1:
            /** In one dimension draw a line containing all points the Realm has
             *  (i.e. 2 points)
             */
            glBegin(GL_LINES);
                for (Realm::realm_container_type::const_iterator i = realm.getSubrealms().begin();
                    i != realm.getSubrealms().end(); ++i) {
                   setVertex(X[i->toIndex()], Xscr[i->toIndex()]);
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
                    for (Realm::realm_container_type::const_iterator i = realm.getSubrealms().begin();
                         i != realm.getSubrealms().end(); ++i) {
                        setVertex(X[i->toIndex()], Xscr[i->toIndex()]);
                    }
                glEnd();
            } else if (realm.getSubrealms().begin()->dimension() == 1) {
                for (Realm::realm_container_type::const_iterator i = realm.getSubrealms().begin();
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
            for (Realm::realm_container_type::const_iterator i = realm.getSubrealms().begin();
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
                _actions = i->second->toString();
            }
            if (i->second->getName() == "Rotation segments") {
                _numSegments = i->second->toUnsigned();
            }
            if (i->second->getName() == "5D Rotation") {
                _rot5D =  i->second->toRotation5();
                std::cerr << "5D Rotation : " << _rot5D << "\n";
            }
            if (i->second->getName() == "6D Rotation") {
                _rot6D =  i->second->toRotation6();
                std::cerr << "6D Rotation : " << _rot6D << "\n";
            }
            if (i->second->getName() == "7D Rotation") {
                _rot7D =  i->second->toRotation7();
                std::cerr << "7D Rotation : " << _rot7D << "\n";
            }
            if (i->second->getName() == "8D Rotation") {
                _rot8D =  i->second->toRotation8();
                std::cerr << "8D Rotation : " << _rot8D << "\n";
            }
            if (i->second->getName() == "9D Rotation") {
                _rot9D =  i->second->toRotation9();
                std::cerr << "9D Rotation : " << _rot9D << "\n";
            }
            if (i->second->getName() == "10D Rotation") {
                _rot10D =  i->second->toRotation10();
                std::cerr << "10D Rotation : " << _rot10D << "\n";
            }

        }
#   else
        setParameter(parms, this->_actions, "Generator");
#   endif
}
