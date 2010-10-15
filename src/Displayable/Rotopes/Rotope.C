/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2008-2010  Lene Preuss <lene.preuss@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

/// \author Lene Preuss <lene.preuss@gmail.com>, (C) 2008

#include "Rotope.h"
#include "Extrude.h"
#include "Taper.h"
#include "Rotate.h"
#include "Torate.h"
#include "RotopeFactory.h"

#include "Matrix.impl.h"
#include "Rotation.impl.h"

using std::vector;
using std::cerr;
using std::endl;
using std::string;

using VecMath::Vector;
using VecMath::Matrix;
using VecMath::Rotation;

Rotope::Rotope():
    Object(0, 0),
    rot5D_(), rot6D_(), rot7D_(), rot8D_(), rot9D_(), rot10D_(),
    numSegments_(RotopeInterface::DEFAULT_NUM_SEGMENTS),
    actions_("EEEE"), rotope_(0) {
  Initialize();
}

Rotope::Rotope(const std::string &actions):
        Object(0, 0),
        rot5D_(), rot6D_(), rot7D_(), rot8D_(), rot9D_(), rot10D_(),
        numSegments_(RotopeInterface::DEFAULT_NUM_SEGMENTS),
        actions_(actions), rotope_(0) {
    Initialize();
}

Rotope::~Rotope() {
    if (rotope_) delete rotope_;
}

std::string Rotope::getFunctionName() const {
    return "Rotope: "+actions_;
}

void Rotope::Initialize() {
    SingletonLog::Instance().log(__PRETTY_FUNCTION__);

    try {
      generateRotopeAndParameters();
    } catch (BadRotopeOperation e) {
      generateDefaultRotope(e);
    } catch (NotYetImplementedException e) {
      generateDefaultRotope(e);
    }

    addNDimensionalTransforms();

    setX(rotope_->projected_vertices());

    Object::Initialize();

}

void Rotope::generateRotopeAndParameters() throw (BadRotopeOperation) {
  RotopeInterface::setRotationSegments(numSegments_);
  rotope_ = RotopeFactory::generate(actions_);
  declareParameter("Generator", actions_);
  for(unsigned i = 5; i <= actions_.length(); ++i) {
    string label = Util::itoa(i)+string("D Rotation");
    switch(i) {
      case 5:
        declareParameter(label, rot5D_);
        break;
      case 6:
        declareParameter(label, rot6D_);
        break;
      case 7:
        declareParameter(label, rot7D_);
        break;
      case 8:
        declareParameter(label, rot8D_);
        break;
      case 9:
        declareParameter(label, rot9D_);
        break;
      case 10:
        declareParameter(label, rot10D_);
        break;
      default:
        throw BadRotopeOperation("Rotope::Initialize()",
                                 "Rotopes of dimension higher than 10 not supported.");
    }
  }
  declareParameter("Rotation segments", numSegments_);
}

void Rotope::generateDefaultRotope(const std::logic_error& e) throw () {
  declareParameter("Generator", string(DIM, 'E'));
  rotope_ = new Extrude<DIM, 0, DIM-1>();
  /** \todo Show the warning in a QMessageBox. Currently that does not work
   *  because C4DView::RenderScene() is called before the object has been
   *  fully initialized.
   */
  /*
   *        QMessageBox::warning (NULL,
   *        QString("Rotope::Rotope(")+actions.c_str()+")",
   *        e.what());
   */
  cerr << e.what() << endl
       << "Rendering " << DIM << "-dimensional hypercube instead." << endl;
}

void Rotope::addNDimensionalTransforms() {
  SingletonLog::Instance() << getParameters().toString();
  for (unsigned i = 5; i <= rotope_->dimension(); ++i) {
    rotope_->addTransform(i, new VecMath::Rotation<5>());
  }
}

/** @param R Rotation
 *  @param T Translation
 */
void Rotope::Transform(const VecMath::Rotation<4> &R,
                       const VecMath::Vector<4> &T) {
    if (!rotope_) {
        throw std::logic_error("Rotope::Transform(): _rotope is NULL!");
    }
    Matrix<4> Rot(R);

    for (unsigned i = 0; i < X.size(); i++) {
        Xtrans[i] = (Rot*X[i])+T;
    }

}

void Rotope::Draw (UI::View *view) {
    if (!rotope_) {
        throw std::logic_error("Rotope::Draw(): _rotope is NULL!");
    }

    if (rotope_->realm().size()) {
        drawRealm(rotope_->realm(), view);
//        _rotope->print();
    } else {
        throw new std::logic_error("Rotope has no Realm member");
    }
}

#include "View.h"

void Rotope::drawRealm(const Realm &realm, UI::View *view) {
    switch (realm.dimension()) {
        case 0:
          /** Dimension 0 is a point. Easy to draw ;-) */
          view->drawVertex(X[realm.toIndex()], Xscr[realm.toIndex()]);
            break;
        case 1:
            /** In one dimension draw a line containing all points the Realm has
             *  (i.e. 2 points)
             */
            for (unsigned i = 0; i < realm.getSubrealms().size()-1; ++i) {
              Realm current = realm.getSubrealms()[i];
              Realm next = realm.getSubrealms()[i+1];
              view->drawLine(X[current.toIndex()], X[next.toIndex()],
                             Xscr[current.toIndex()], Xscr[next.toIndex()]);
            }
            break;
        case 2:
            /** In two dimensions, draw a surface. The current implementation
             *  represents two dimensional surfaces as vector of the form
             *  \code (0, 1, ..., n) \endcode
             */
            if (realm.getSubrealms().begin()->dimension() == 0) {
              vector< Vector<4> > original_vertices;
              vector< Vector<3> > projected_vertices;
              for (Realm::realm_container_type::const_iterator i = realm.getSubrealms().begin();
                   i != realm.getSubrealms().end(); ++i) {
                original_vertices.push_back(X[i->toIndex()]);
                projected_vertices.push_back(Xscr[i->toIndex()]);
              }
              view->drawPolygon(original_vertices, projected_vertices);
            } else if (realm.getSubrealms().begin()->dimension() == 1) {
                for (Realm::realm_container_type::const_iterator i = realm.getSubrealms().begin();
                     i != realm.getSubrealms().end(); ++i) {
                    drawRealm(*i, view);
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
              drawRealm(*i, view);
            }
            break;
    }
}

void Rotope::SetParameters(const ParameterMap &parms) {
#   if 1
        for (ParameterMap::const_iterator i = parms.begin();
             i != parms.end(); ++i) {
            if (i->second->getName() == "Generator") {
                actions_ = i->second->toString();
            }
            if (i->second->getName() == "Rotation segments") {
                numSegments_ = i->second->toUnsigned();
            }
            if (i->second->getName() == "5D Rotation") {
                rot5D_ =  i->second->toRotation5();
            }
            if (i->second->getName() == "6D Rotation") {
                rot6D_ =  i->second->toRotation6();
            }
            if (i->second->getName() == "7D Rotation") {
                rot7D_ =  i->second->toRotation7();
            }
            if (i->second->getName() == "8D Rotation") {
                rot8D_ =  i->second->toRotation8();
            }
            if (i->second->getName() == "9D Rotation") {
                rot9D_ =  i->second->toRotation9();
            }
            if (i->second->getName() == "10D Rotation") {
                rot10D_ =  i->second->toRotation10();
            }

        }
#   else
        setParameter(parms, this->actions_, "Generator");
#   endif
}
