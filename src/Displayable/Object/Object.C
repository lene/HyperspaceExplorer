/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

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

#define USE_OUTDATED_CLASS 1

#include <iostream>

#include "Object.h"

#include "Globals.h"
#include "ColorManager.h"
#include "Log.h"

#include "View.h"
#if USE_OUTDATED_CLASS
# include "Transform.h"
#else
# include "TransformationFactory.h"

# include "Transformation.impl.h"
#endif
#include "Matrix.impl.h"
#include "MultiDimensionalVector.impl.h"
#include "Vector.impl.h"
#include "SurfaceType.impl.h"

using std::cerr;
using std::endl;

using VecMath::Vector;
using VecMath::Matrix;

///////////////////////////////////////////////////////////////////////////////


/** generic Object constructor; only allocates necessary arrays, children must
 *  fill them in their c'tor
 *  @param vertices number of vertices
 *  @param surfaces number of surfaces                                        */
Object::Object (unsigned vertices, unsigned surfaces):
        Displayable(),
        Surface(surfaces),
        X_(vec4vec1D(vertices)), Xtrans_(vec4vec1D(vertices)), Xscr_(vec3vec1D()),
        X_in_new_format_(), Xscr_in_new_format_() {

    for (unsigned i = 0; i < surfaces; i++) Surface[i].resize(4);
}

/// Actually create the Object, this method is overridden in child classes
/** Calibrates the color manager from the vertices of the object.
 *
 *  In child classes, this method should be reimplemented to set up the arrays
 *  \p X and \p Surface. When that is finished, the reimplementation should
 *  call \code Object::Initialize() \endcode at the end of its own Initialize()
 *  routine to calibrate the color manager.
 */
void Object::Initialize() {
    calibrateColors();
}

void Object::calibrateColors() const {
    for (unsigned i = 0; i < X_.size(); i++) {
        ColMgrMgr::Instance().calibrateColor(
            X_[i],
            Color((X_[i][0]+1)/2, (X_[i][1]+1)/2, (X_[i][2]+1)/2,
                  .75-(X_[i][3]+1)/4));
    }
}

const VecMath::MultiDimensionalVector< Object::vertex_type, 1 > &Object::X() const {
    X_in_new_format_.clear();
    for (auto i = X_.begin(); i != X_.end(); ++i) {
        X_in_new_format_.push_back(*i);
    }
    return X_in_new_format_;
}

Displayable::vec4vec1D Object::X_as_old_format() const {
    return X_;
}

void Object::resizeX(unsigned size) {
    X_.resize(size);
}

/** \param newX The array of vertices to be copied to \p X */
void Object::setX(const vec4vec1D &newX) {
    X_ = newX;
    Xtrans_.resize(X_.size());
    Xscr_.resize(X_.size());
}

void Object::setX(int i, const Object::vertex_type &x) {
    X_[i] = x;
}

void Object::X_push_back(const Object::vertex_type& x) {
    X_.push_back(x);
}

void Object::setXtrans(const VecMath::MultiDimensionalVector< Object::vertex_type, 1 > &xtrans) {
    Xtrans_.clear();
    Xtrans_.resize(xtrans.size());
    for (auto i = xtrans.begin(); i != xtrans.end(); ++i) {
        Xtrans_.push_back(*i);
    }
}

const VecMath::MultiDimensionalVector< Object::vertex_type, 1 > &Object::Xtrans() const {
    Xtrans_in_new_format_.clear();
    for (auto i = Xtrans_.begin(); i != Xtrans_.end(); ++i) {
        Xtrans_in_new_format_.push_back(*i);
    }
    return Xtrans_in_new_format_;    
}

void Object::resizeXtrans(unsigned size) {
    Xtrans_.resize(size);
}

const VecMath::MultiDimensionalVector< Object::projected_vertex_type, 1 > &Object::Xscr() const {
    Xscr_in_new_format_.clear();
    for (auto i = Xscr_.begin(); i != Xscr_.end(); ++i) {
        Xscr_in_new_format_.push_back(*i);
    }
    return Xscr_in_new_format_;    
}

void Object::resizeXscr(unsigned size) {
    Xscr_.resize(size);
}

void Object::setXscr(int i, const Object::projected_vertex_type &x) {
    Xscr_[i] = x;
}

/// Transforms an Object
/** @param R Rotation
 *  @param T Translation
 */
void Object::Transform(const VecMath::Rotation<4> &R,
                       const VecMath::Vector<4> &T,
                       const VecMath::Vector<4> &scale) {
# if USE_OUTDATED_CLASS
    Matrix<4> Rot(R);
    resizeXtrans(X().size());
    transform<vec4vec1D, 4>::xform(Rot, T, scale, X_, Xtrans_);
# else  
    const Transformation<4, 1> &xform = TransformationFactory<4, 1>::create(R, T, scale);
    setXtrans(xform.transform(X()));
# endif    
}

/// Projects an Object into three-space
/** @param scr_w w coordinate of screen
 *  @param cam_w w coordinate of camera
 *  @param depthcue4d wheter to use hyperfog/dc                               */
void Object::Project (double scr_w, double cam_w, bool depthcue4d) {

    resizeXscr(Xtrans().size());
    for (unsigned i = 0; i < Xtrans().size(); i++) {
        double ProjectionFactor = (scr_w-cam_w)/(Xtrans()[i][3]-cam_w);

        projected_vertex_type x_scr;
        for (unsigned j = 0; j <= 2; j++) {
            x_scr[j] = ProjectionFactor*Xtrans()[i][j];
        }
        setXscr(i, x_scr);
    }

    if (!depthcue4d) return;

    double Wmax = 0, Wmin = 0;
    for (unsigned i = 0; i < Xtrans().size(); i++) {
        if (depthcue4d) {
            if (Xtrans()[i][3] < Wmin) Wmin = Xtrans()[i][3];
            if (Xtrans()[i][3] > Wmax) Wmax = Xtrans()[i][3];
        }
    }
    //  apply hyperfog
    for (unsigned i = 0; i < X().size(); i++) {
        ColMgrMgr::Instance().depthCueColor(Wmax, Wmin, Xtrans()[i][3], X()[i]);
    }
}

/// Draw the projected Object (onto screen or into GL list, as it is)
void Object::Draw(UI::View *view) {
  for (unsigned i = 0; i < Surface.size(); ++i) {
    view->drawQuadrangle(X()[Surface[i][0]], X()[Surface[i][1]], X()[Surface[i][2]], X()[Surface[i][3]],
                         Xscr()[Surface[i][0]], Xscr()[Surface[i][1]], Xscr()[Surface[i][2]], Xscr()[Surface[i][3]]);
  }
  view->commitDraw();
}

/** Reinitialize an Object. This function is called when the initialization is
 *  done outside the constructor.
 *
 *  Currently it does not differ from Initialize(). In fact, it simply calls
 *  Initialize().
 */
void Object::ReInit (double, double, double,
                     double, double, double,
                     double, double, double) {
    SingletonLog::Instance() << "Object::ReInit()\n";
    Initialize();
}

void Object::for_each_vertex(Displayable::function_on_fourspace_vertex apply) {
  std::for_each(X_.begin(), X_.end(), apply);
}

void Object::for_each_vertex_transformed(function_on_fourspace_and_transformed_vertex apply) {
  size_t max_element = std::min(X_.size(), Xtrans_.size());
  for (size_t i = 0; i < max_element; ++i) {
      apply(X_[i], Xtrans_[i]);
  }
}

void Object::for_each_projected(Displayable::function_on_projected_vertex apply) {
  std::for_each(Xscr_.begin(), Xscr_.end(), apply);
}

void Object::for_each_vertex_transformed_projected(function_on_fourspace_transformed_and_projected_vertex apply) {
  size_t max_element = std::min(std::min(X_.size(), Xtrans_.size()), Xscr_.size());
  for (size_t i = 0; i < max_element; ++i) {
      apply(X_[i], Xtrans_[i], Xscr_[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////

