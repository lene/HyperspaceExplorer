///
/// C++ Implementation: ColorManager
///
/// Description:
///
///
/// \author Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///
#include "RotationControl.H"

#include <iostream>

namespace UI {

    RotationControl::RotationControl(VecMath::RotationBase *r, QWidget *parent):
            QWidget(parent) {
        std::cout << "RotationControl::RotationControl(" << *r << ")\n";
    }

}
