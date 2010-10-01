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

#ifndef UIROTATIONSLIDER_H
#define UIROTATIONSLIDER_H

#include <QSlider>

namespace UI {

    /// A QSlider which represents a rotation from -180 to 180 degrees
    /** The rotation value is displayed in degrees, but returned in radians.
     *  The number of digits behind the dot is passed to the constructor as
     *  integer parameter.
     *
     *  \author Lene Preuss <lene.preuss@gmail.com>
     */
    class RotationSlider : public QSlider {
        public:

            /// Constructs a RotationSlider with given stepsize in degrees.
            RotationSlider(unsigned precision = 2, QWidget *parent = 0);

            /// Returns the value of the slider.
            virtual double value() const;
            /// Sets the value to \p rot.
            virtual void setValue(double rot);

        private:
            /// How big the stepsize is (in degrees).
            double _precision;
    };

}

#endif
