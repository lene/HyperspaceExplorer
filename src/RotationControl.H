#ifndef UIROTATIONCONTROL_H
#define UIROTATIONCONTROL_H

#include <QWidget>

#include <vector>

#include "Rotation.H"
#include "RotationSlider.H"

namespace UI {

/**
	@author Helge Preuss <scout@hyperspace-travel.de>
*/
class RotationControl : public QWidget
{
Q_OBJECT
public:
    RotationControl(VecMath::RotationBase r, QWidget *parent = 0);

    std::vector<RotationSlider *> _sliders;
};

}

#endif
