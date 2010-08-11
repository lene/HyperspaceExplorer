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
