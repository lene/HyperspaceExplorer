#ifndef UIROTATIONCONTROL_H
#define UIROTATIONCONTROL_H

#include <QWidget>

#include <vector>

#include "Rotation.h"
#include "RotationSlider.h"

namespace UI {

/**
	@author Helge Preuss <lene.preuss@gmail.com>
*/
class RotationControl : public QWidget
{
Q_OBJECT
public:
    RotationControl(VecMath::RotationBase *r, QWidget *parent = 0);

    std::vector<RotationSlider *> _sliders;
};

}

#endif
