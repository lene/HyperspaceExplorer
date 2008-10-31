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

    Color ViewImpl::_defaultBackground(0.1, 0.1, 0.1, 1.0);
    GLfloat ViewImpl::_lightPos[4] = { 4., 4., 8., 0. };

    ViewImpl::ViewImpl():
        View(),
        _F(std::auto_ptr<Function>()),
        _colors(true), _coordinates(false), _fog(true), _hyperfog(false),
        _lighting(true), _shading(true), _solid(true), _transparence(false),
        _background (0.25, 0.25, 0.25, 1.),
        _dR(0.,0.,0.,0.,0.,0.),
        _T(0.,0.,0.,0.), _R(0.,0.,0.,0.,0.,0.),
        _camW (-3.), _scrW (0.), _distance(1.),
        _numFrames(1), _numLoops(1),
        _writeImages (false),
        _imageDir("/tmp"),
        _imagePrefix("HyperspaceExplorer_Image") { }

    /** \param s Directory where to store image files */
    void ViewImpl::setImgDir(const std::string &s) {
        _imageDir = s;
        setWriteImages(true);
    }

    /** \param s Filename prefix for saved images */
    void ViewImpl::setImgPrefix(const std::string &s) {
        _imagePrefix = s;
        setWriteImages(true);
    }

    void ViewImpl::setDefaultBackground() {
        setBackground(_defaultBackground);
    }

    /** \param ddr Rotation to be added to the current Rotation state */
    void ViewImpl::adddR(const VecMath::Rotation<4> &ddR) {
        setdR(getdR() + ddR);
    }
}
