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
            RotationSlider(unsigned precision = 2, QWidget *parent = 0);

            ~RotationSlider() { }

            virtual double value() const;
            virtual void setValue(double rot);

        private:
            double _precision;
    };

}

#endif
