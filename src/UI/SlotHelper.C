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

#include "Menu4D.h"

#include "SlotHelper.h"
#include "4DView.h"

void SlotHelper::slot() {

  UI::Dialogs::ValuesDialogImpl *values = view_->Values();
  Displayable *new_displayable = TheFunctionFactory::Instance().createFunction(displayable_name_);
  new_displayable->ReInit(
    values->tmin (), values->tmax (), values->dt (),
    values->umin (), values->umax (), values->du (),
    values->vmin (), values->vmax (), values->dv ());

  view_->setF(new_displayable);

  view_->Menu()->updateFunctionMenu(view_->F()->getFunctionName().c_str());
  view_->AssignValues(view_->F());
  view_->Redraw();

}
