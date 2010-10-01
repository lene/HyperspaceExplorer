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

#include "RotationSlider.h"

#include <cmath>

namespace UI {

    RotationSlider::RotationSlider(unsigned precision, QWidget *parent):
            QSlider(parent), _precision(1.) {
        while(precision--) _precision *= 10;
        setMaximum(180*_precision);
        setMinimum(-180*_precision);
        //  change value by 1 degree when pressing an arrow key
        setSingleStep(_precision);
        //  change value by 10 degrees when pressing PgUp/PgDn
        setPageStep(10*_precision);

        setTickPosition(QSlider::TicksBelow);
        setTickInterval(10*_precision);
    }

    double RotationSlider::value() const {
        return (double)QSlider::value()/180./_precision*M_PI;
    }

    void RotationSlider::setValue(double rot) {
        QSlider::setValue(rot/M_PI*180.*_precision);
    }

}
