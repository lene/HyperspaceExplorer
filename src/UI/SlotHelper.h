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

/// \ingroup UIHelpers

#include <QObject>

#include "4DView.h"

#include "FunctionFactory.h"

/// Single-stop slot for menu QActions generating Displayable objects
/** Your mission, should you choose to accept it, is to have a single function
 *  to serve as slot for all menu Actions which generate a new Displayable. After
 *  all, this could be done with a template.
 *
 *  In fact, it's not quite so easy and we need an indirection. Because moc can't
 *  compile class templates, we need another class to stand between the QAction
 *  triggered by (e.g.) menu item selection and the creation of a Function object.
 *
 *  This class provides a single slot, which calls the factory method of the
 *  FunctionFactory that was passed to the SlotHelper object during construction.
 *
 *  This way, a single slot function can create all Function objects. The
 *  drawback is that now many SlotHelper objects exist, one for every type of
 *  Function that is present in the menus.
 *
 *  \ingroup UIHelpers
 */
class SlotHelper: public QObject {

  Q_OBJECT

  public:

    SlotHelper(C4DView *view, const std::string &displayable_name):
      view_(view), displayable_name_(displayable_name) {}              ///< Construction
    virtual ~SlotHelper() { }   ///< Cleanup

  public slots:

    void slot();

  private:
    /// The C4DView which wants to instantiate Function's
    C4DView* view_;
    /// The name of the Displayable as taken by the FunctionFactory
    std::string displayable_name_;
};
