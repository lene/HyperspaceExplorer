//
// C++ Implementation: ViewImpl
//
// Description: 
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "ViewImpl.H"

namespace UI {

    Color ViewImpl::defaultBackground(0.1, 0.1, 0.1, 1.0);

    ViewImpl::ViewImpl():
        View(),
        _colors(true), _coordinates(false), _fog(true), _hyperfog(false),
        _lighting(true), _shading(true), _solid(true), _transparence(false),
        _background (0.25, 0.25, 0.25, 1.),
        _dR(0.,0.,0.,0.,0.,0.),
        _numFrames(1), _numLoops(1) { }

}
