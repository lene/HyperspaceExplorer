/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2009-2010  Lene Preuss <lene.preuss@gmail.com>

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

#ifndef ROTOPE_H
#define ROTOPE_H

#include "Object.h"
#include "VertexData.h"

/// Gets thrown when an operation is not yet (or will never be) supported
/** \ingroup RotopeGroup
 *  \author Lene Preuss <lene.preuss@gmail.com>
 */
struct BadRotopeOperation: public std::logic_error {
  /// Create a BadRotopeOperation
  BadRotopeOperation(const std::string &caller, const std::string &op);
};

/// A four-dimensional <a href="http://teamikaria.com/wiki/Rotope">Rotope</a>.
/** \ingroup RotopeGroup
 *  \author Lene Preuss <lene.preuss@gmail.com>
 */
class Rotope : public Object {

  const static unsigned DIM = 6;      ///< Default dimension of Rotope objects

  public:

    /// Construct a default Rotope (\p DIM -dimensional hypercube).
    Rotope();
    /// Execute a series of extrusions to construct a Rotope
    Rotope(const std::string &);

    virtual ~Rotope();

    virtual std::string getFunctionName() const;

    /// Execute the desired extrude actions and declare FunctionParameter s
    virtual void Initialize();

    /// Transforms a Rotope
    virtual void Transform (const VecMath::Rotation<4> &,
                                const VecMath::Vector<4> &);
    /// Draw the projected Rotope
    virtual void Draw (UI::View *view);

    /// Set parameters to the Function
    virtual void SetParameters(const ParameterMap &parms);

  private:

    /// Draw a Realm, which may be a surface of the Rotope or the entire Rotope
    void drawRealm(const Realm &realm, UI::View *view) const;
    /// Draw \p realm if it is a point.
    void drawPoint(const Realm &realm, UI::View *view) const;
    /// Draw \p realm if it is a line.
    void drawLine(const Realm &realm, UI::View *view) const;
    /// Draw \p realm if it is two-dimensional.
    void drawSurface(const Realm &realm, UI::View *view) const;
    /// Draw \p realm if it has more than two dimensions.
    void drawVolume(const Realm &realm, UI::View *view) const;

    class Impl;
    Impl *pImpl_;

};

namespace {
  Displayable *createRotope() { return new Rotope; }
  const bool registeredRotope = TheFunctionFactory::Instance().registerFunction(createRotope, "Object");
}

#endif
