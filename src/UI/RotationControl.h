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

#ifndef UIROTATIONCONTROL_H
#define UIROTATIONCONTROL_H

#include <QWidget>

#include <vector>

#include "Rotation.h"
#include "RotationSlider.h"

namespace UI {

/// QWidget to edit the value of a VecMath::Rotation.
/** @author Lene Preuss <lene.preuss@gmail.com>
*/
class RotationControl : public QWidget {
Q_OBJECT
public:

  /// Creates a RotationControl for a given Rotation object.
  RotationControl(VecMath::RotationBase *r, QWidget *parent = 0);

private:
  /// The actual RotationSlider widgets controlling rotation about each axis.
  std::vector<RotationSlider *> _sliders;
};

}

#endif
