#ifndef UIROTATIONCONTROL_H
#define UIROTATIONCONTROL_H

#include <QWidget>

#include <vector>

#include "Rotation.h"
#include "RotationSlider.h"

namespace UI {

/// QWidget to edit the value of a VecMath::Rotation.
/** @author Helge Preuss <lene.preuss@gmail.com>
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
