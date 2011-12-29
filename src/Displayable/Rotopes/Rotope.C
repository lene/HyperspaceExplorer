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

#include "FunctionHolder.impl.h"
#include "Matrix.impl.h"
#include "Rotation.impl.h"
#include "MultiDimensionalVector.impl.h"

using std::vector;
using std::cerr;
using std::endl;
using std::string;

using VecMath::Vector;
using VecMath::Matrix;
using VecMath::Rotation;

/** \param caller The function name throwing the BadRotopeOperation
 *  \param op The unsupported operation \p caller wanted to perform
 */
BadRotopeOperation::BadRotopeOperation(const std::string& caller, const std::string& op):
std::logic_error(caller+": "+"Unsupported action \""+op+"\"") {}

struct Rotope::Impl {

  Impl(Rotope *parent, const std::string &actions):
    rot5D_(), rot6D_(), rot7D_(), rot8D_(), rot9D_(), rot10D_(),
    numSegments_(RotopeInterface::DEFAULT_NUM_SEGMENTS),
    actions_(actions), rotope_(NULL), parent_(parent) { }

  void generateRotope() throw(BadRotopeOperation);
  void generateParameters() throw(BadRotopeOperation);
  void generateDefaultRotope(const std::logic_error &e) throw();
  void addNDimensionalTransforms();

  void readParameter(std::shared_ptr<FunctionParameter> parameter);

  /// Rotation in 5-space (for objects of dimension >= 5)
  VecMath::Rotation<5> rot5D_;
  /// Rotation in 6-space (for objects of dimension >= 6)
  VecMath::Rotation<6> rot6D_;
  /// Rotation in 7-space (for objects of dimension >= 7)
  VecMath::Rotation<7> rot7D_;
  /// Rotation in 8-space (for objects of dimension >= 8)
  VecMath::Rotation<8> rot8D_;
  /// Rotation in 9-space (for objects of dimension >= 9)
  VecMath::Rotation<9> rot9D_;
  /// Rotation in 10-space (for objects of dimension >= 10)
  VecMath::Rotation<10> rot10D_;
  /// Number of segments approximating the object in rotation operations
  unsigned numSegments_;

  /// Sequence of extrusion actions needed to generate the Rotope
  std::string actions_;
  /// Actual rotope object to which all functions are delegated
  RotopeInterface *rotope_;

  Rotope *parent_;

};

Rotope::Rotope():
    Object(0, 0), pImpl_(new Impl(this, "EEEE")) {
  Initialize();
}

Rotope::Rotope(const std::string &actions):
    Object(0, 0), pImpl_(new Impl(this, actions)) {
  Initialize();
}

Rotope::~Rotope() {
  if (pImpl_->rotope_) delete pImpl_->rotope_;
}

std::string Rotope::getFunctionName() const {
  return "Rotope: "+pImpl_->actions_;
}

void Rotope::Initialize() {

  try {
    pImpl_->generateRotope();
    pImpl_->generateParameters();
  } catch (BadRotopeOperation e) {
    pImpl_->generateDefaultRotope(e);
  } catch (NotYetImplementedException e) {
    pImpl_->generateDefaultRotope(e);
  }

  pImpl_->addNDimensionalTransforms();

  setX(
      VertexGrid<4, 1, double>(
          MultiDimensionalVector< Vector<4> , 1>(
              pImpl_->rotope_->projected_vertices()
          )
      )
  );

  Object::Initialize();

}

#include "Transformation.impl.h"
#include "TransformationFactory.impl.h"

void Rotope::Transform(const VecMath::Rotation<4> &R,
                       const VecMath::Vector<4> &T) {
  assert(pImpl_->rotope_);
/*
  Matrix<4> Rot(R);

  for (unsigned i = 0; i < X().size(); i++) {
    Xtrans_[i] = (Rot*X()[i])+T;
  }
 */
    const Transformation<4, 1> &xform = TransformationFactory<4, 1>::create(R, T, 1.);
    setXtrans(xform.transform(X()));

}

void Rotope::Draw (UI::View *view) {
  assert(pImpl_->rotope_);
  assert(pImpl_->rotope_->realm().size());

  drawRealm(pImpl_->rotope_->realm(), view);
}


void Rotope::SetParameters(const ParameterMap &parms) {
  for (ParameterMap::const_iterator i = parms.begin(); i != parms.end(); ++i) {
    pImpl_->readParameter(i->second);
  }
}

void Rotope::Impl::generateRotope() throw (BadRotopeOperation) {
  RotopeInterface::setRotationSegments(numSegments_);
  rotope_ = RotopeFactory::generate(actions_);
}

void Rotope::Impl::generateParameters() throw (BadRotopeOperation) {
  parent_->declareParameter("Generator", actions_);
  for(unsigned i = 5; i <= actions_.length(); ++i) {
    string label = Util::itoa(i)+string("D Rotation");
    switch(i) {
      case 5:
        parent_->declareParameter(label, rot5D_);
        break;
      case 6:
        parent_->declareParameter(label, rot6D_);
        break;
      case 7:
        parent_->declareParameter(label, rot7D_);
        break;
      case 8:
        parent_->declareParameter(label, rot8D_);
        break;
      case 9:
        parent_->declareParameter(label, rot9D_);
        break;
      case 10:
        parent_->declareParameter(label, rot10D_);
        break;
      default:
        throw BadRotopeOperation("Rotope::Initialize()",
                                 "Rotopes of dimension higher than 10 not supported.");
    }
  }
  parent_->declareParameter("Rotation segments", numSegments_);
}

void Rotope::Impl::generateDefaultRotope(const std::logic_error& e) throw () {
  parent_->declareParameter("Generator", string(DIM, 'E'));
  rotope_ = new Extrude<DIM, 0, DIM-1>();
  /** \todo Show the warning in a QMessageBox. Currently that does not work
   *  because C4DView::RenderScene() is called before the object has been
   *  fully initialized:
   *  \code
   *  QMessageBox::warning (NULL, QString("Rotope::Rotope(")+actions.c_str()+")", e.what());
   *  \endcode
   */
  cerr << e.what() << endl
  << "Rendering " << DIM << "-dimensional hypercube instead." << endl;
}

void Rotope::Impl::addNDimensionalTransforms() {
  SingletonLog::Instance() << __PRETTY_FUNCTION__ << parent_->getParameters().toString();
  for (unsigned i = 5; i <= rotope_->dimension(); ++i) {
    rotope_->addTransform(i, new VecMath::Rotation<5>());
  }
}

void Rotope::Impl::readParameter(std::shared_ptr<FunctionParameter> parameter) {
  string name = parameter->getName();
  if (name == "Generator") {
    actions_ = parameter->toString();
  }
  if (name == "Rotation segments") {
    numSegments_ = parameter->toUnsigned();
  }
  if (name == "5D Rotation") {
    rot5D_ =  parameter->toRotation5();
  }
  if (name == "6D Rotation") {
    rot6D_ =  parameter->toRotation6();
  }
  if (name == "7D Rotation") {
    rot7D_ =  parameter->toRotation7();
  }
  if (name == "8D Rotation") {
    rot8D_ =  parameter->toRotation8();
  }
  if (name == "9D Rotation") {
    rot9D_ =  parameter->toRotation9();
  }
  if (name == "10D Rotation") {
    rot10D_ =  parameter->toRotation10();
  }
}

/** Helper function for Draw(void). Calls itself recursively until the
 *  Rotope is broken down to a sufficiently small dimension.
 *  \param realm The Realm to draw.
 *  \param view The View on which to draw.
 *  \todo Actually, this function belongs more into the Realm realm...
 */
void Rotope::drawRealm(const Realm &realm, UI::View *view) const {
  switch (realm.dimension()) {
    case 0:
      drawPoint(realm, view);
      break;
    case 1:
      drawLine(realm, view);
      break;
    case 2:
      drawSurface(realm, view);
      break;
    default:
      drawVolume(realm, view);
  }
}

#include "View.h"

void Rotope::drawPoint(const Realm& realm, UI::View* view) const {
  assert(realm.dimension() == 0);
  view->drawVertex(X()[realm.toIndex()], Xscr()[realm.toIndex()]);
}

void Rotope::drawLine(const Realm& realm, UI::View* view) const {
  assert(realm.dimension() == 1);
  for (unsigned i = 0; i < realm.getSubrealms().size()-1; ++i) {
    Realm current = realm.getSubrealms()[i];
    Realm next = realm.getSubrealms()[i+1];
    view->drawLine(X()[current.toIndex()], X()[next.toIndex()],
                   Xscr()[current.toIndex()], Xscr()[next.toIndex()]);
  }
}

/** The current implementation represents two dimensional surfaces as vector of
 *  the form \code (0, 1, ..., n) \endcode.
 */
void Rotope::drawSurface(const Realm& realm, UI::View* view) const {
  assert(realm.dimension() == 2);
  if (realm.getSubrealms().begin()->dimension() == 0) {
    vector< Vector<4> > original_vertices;
    vector< Vector<3> > projected_vertices;
    for (Realm::realm_container_type::const_iterator i = realm.getSubrealms().begin();
         i != realm.getSubrealms().end(); ++i) {
      original_vertices.push_back(X()[i->toIndex()]);
      projected_vertices.push_back(Xscr()[i->toIndex()]);
    }
    view->drawPolygon(original_vertices, projected_vertices);
  } else if (realm.getSubrealms().begin()->dimension() == 1) {
    for (Realm::realm_container_type::const_iterator i = realm.getSubrealms().begin();
         i != realm.getSubrealms().end(); ++i) {
      drawRealm(*i, view);
    }
  }
}

/** Recurse to draw the lower order realms, until we find surfaces.
 */
void Rotope::drawVolume(const Realm& realm, UI::View* view) const {
  assert(realm.dimension() > 2);
  for (Realm::realm_container_type::const_iterator i = realm.getSubrealms().begin();
       i != realm.getSubrealms().end(); ++i) {
    drawRealm(*i, view);
  }
}

