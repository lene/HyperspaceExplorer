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
    SingletonLog::Instance().log(__PRETTY_FUNCTION__);

    try {
        _rotope = RotopeFactory::generate(_actions);
        declareParameter("Generator", _actions);
        for(unsigned i = 5; i <= _actions.length(); ++i) {
            string label = Globals::Instance().itoa(i)+string("D Rotation");
            switch(i) {
                case 5:
                    declareParameter(label, VecMath::Rotation<5>());
                    break;
                case 6:
                    declareParameter(label, VecMath::Rotation<6>());
                    break;
                case 7:
                    declareParameter(label, VecMath::Rotation<7>());
                    break;
                case 8:
                    declareParameter(label, VecMath::Rotation<8>());
                    break;
                case 9:
                    declareParameter(label, VecMath::Rotation<9>());
                    break;
                case 10:
                    declareParameter(label, VecMath::Rotation<10>());
                    break;
            }
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
    std::cout << "Rotope::Draw()" << std::endl;

    if (_rotope->realm().size()) {
        for (std::vector<Realm>::const_iterator i = _rotope->realm().begin();
             i != _rotope->realm().end(); ++i) {
            i->draw(this);
        }
    } else {
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
    }
}

void Rotope::SetParameters(const ParameterMap &parms) {
#   if 1
        for (ParameterMap::const_iterator i = parms.begin();
             i != parms.end(); ++i) {
            if (i->second->getName() == "Generator") {
                _actions = std::string(*i->second);
            }
            if (i->second->getName() == "5D Rotation") {
                std::cerr << "5D Rotation : "
                        << VecMath::Rotation<5>(*i->second) << "\n";
            }
            if (i->second->getName() == "6D Rotation") {
                std::cerr << "6D Rotation : "
                        << VecMath::Rotation<5>(*i->second) << "\n";
            }
            if (i->second->getName() == "7D Rotation") {
                std::cerr << "7D Rotation : "
                        << VecMath::Rotation<5>(*i->second) << "\n";
            }
            if (i->second->getName() == "8D Rotation") {
                std::cerr << "8D Rotation : "
                        << VecMath::Rotation<5>(*i->second) << "\n";
            }
            if (i->second->getName() == "9D Rotation") {
                std::cerr << "9D Rotation : "
                        << VecMath::Rotation<5>(*i->second) << "\n";
            }
            if (i->second->getName() == "10D Rotation") {
                std::cerr << "10D Rotation : "
                        << VecMath::Rotation<5>(*i->second) << "\n";
            }

        }
#   else
        setParameter(parms, this->_actions, "Generator");
#   endif
}
