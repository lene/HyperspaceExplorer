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
    LightSource ViewImpl::_defaultLightSource (
        VecMath::Vector<4>( 4., 4., 8., 0.),
        Color(0.3, 0.3, 0.3, 1.),
        Color(0.9, 0.9, 0.9, 1.),
        Color(1., 1., 1., 1.));
    LightSource ViewImpl::_flatLightSource (
        VecMath::Vector<4>( 4., 4., 8., 0.),
        Color(1., 1., 1., 1.),
        Color(1., 1., 1., 1.),
        Color(1., 1., 1., 1.));

    ViewImpl::ViewImpl():
        View(),
        _F(std::auto_ptr<Function>()),
        _colors(true), _coordinates(false), _fog(true), _hyperfog(false),
        _lighting(true), _shading(true), _solid(true), _transparence(false),
        _background (0.25, 0.25, 0.25, 1.),
        _dR(0.,0.,0.,0.,0.,0.),
        _T(0.,0.,0.,0.), _R(0.,0.,0.,0.,0.,0.),
        _camW (-3.), _scrW (0.),
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

    void ViewImpl::removeLight(std::vector<Light *>::iterator i) {
        if (i >= _lights.end())
            throw std::logic_error("Tried to remove a light beyond the end of \
                    the list of lights");
        _lights.erase(i);
    }

    void ViewImpl::setDefaultBackground() {
        setBackground(_defaultBackground);
    }

    /** \param ddR Rotation to be added to the current Rotation state */
    void ViewImpl::adddR(const VecMath::Rotation<4> &ddR) {
        setdR(getdR() + ddR);
    }
}