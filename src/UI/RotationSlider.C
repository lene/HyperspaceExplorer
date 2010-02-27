///
/// C++ Implementation: ColorManager
///
/// Description:
///
///
/// \author Helge Preuss <lene.preuss@gmail.com>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///

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
