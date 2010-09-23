//
// C++ Implementation: ViewImpl
//
// Description:
//
//
// Author: Helge Preuss <lene.preuss@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "ViewImpl.h"

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
        _F(std::tr1::shared_ptr<Function>()),
        _colors(true), _coordinates(false), _fog(true), _hyperfog(false),
        _lighting(true), _shading(true), _solid(true), _transparence(false),
        _background (0.25, 0.25, 0.25, 1.),
        _dR(), _T(), _R(),
        _camW (-3.), _scrW (0.),
        _numFrames(1), _numLoops(1),
        _writeImages (false),
        _imageDir("/tmp"),
        _imagePrefix("HyperspaceExplorer_Image") { }

    const std::tr1::shared_ptr< Function >& ViewImpl::F() const { return _F; }

    void ViewImpl::setF(Function* _f) { _F.reset(_f); }
    
    const VecMath::Rotation< 4 >& ViewImpl::getdR() { return _dR; }
    
    void ViewImpl::setdR(const VecMath::Rotation< 4 >& _dr) { _dR = _dr; }
    
    void ViewImpl::setNumFrames(unsigned int frames) { _numFrames = frames; }
    
    void ViewImpl::setNumLoops(unsigned int loops) { _numLoops = loops; }    

    const std::string& ViewImpl::getImgDir() { return _imageDir; }

    /** \param s Directory where to store image files */
    void ViewImpl::setImgDir(const std::string &s) {
        _imageDir = s;
        setWriteImages(true);
    }

    const std::string& ViewImpl::getImgPrefix() { return _imagePrefix; }

    /** \param s Filename prefix for saved images */
    void ViewImpl::setImgPrefix(const std::string &s) {
        _imagePrefix = s;
        setWriteImages(true);
    }

    const Color& ViewImpl::getBackground() { return _background; }

    void ViewImpl::setBackground(const Color& bg) { _background = bg; }

    void ViewImpl::addLight(Light* l) { _lights.push_back(l); }

    void ViewImpl::removeLight(std::vector<Light *>::iterator i) {
        if (i >= _lights.end())
            throw std::logic_error("Tried to remove a light beyond the end of \
                    the list of lights");
        _lights.erase(i);
    }

    const std::vector< Light* >& ViewImpl::getLights() { return _lights; }

    bool ViewImpl::getColors() const { return _colors; }
    
    void ViewImpl::setColors(bool on) { _colors = on; }
    
    bool ViewImpl::getCoordinates() const { return _coordinates; }
    
    void ViewImpl::setCoordinates(bool on) { _coordinates = on; }

    bool ViewImpl::getFog() const { return _fog; }

    void ViewImpl::setFog(bool on) { _fog = on; }
    
    bool ViewImpl::getHyperfog() const { return _hyperfog; }
    
    void ViewImpl::setHyperfog(bool on) { _hyperfog = on; }
    
    bool ViewImpl::getLighting() const { return _lighting; }    

    void ViewImpl::setLighting(bool on) { _lighting = on; }

    bool ViewImpl::getShading() const { return _shading; }

    void ViewImpl::setShading(bool on) { _shading = on; }
    
    bool ViewImpl::getSolid() const { return _solid; }
    
    void ViewImpl::setSolid(bool on) { _solid = on; }
    
    bool ViewImpl::getTransparence() const { return _transparence; }
    
    void ViewImpl::setTransparence(bool on) { _transparence = on; }

    void ViewImpl::drawTriangle(const VecMath::Vector< 4 >&, const VecMath::Vector< 4 >&, 
                                const VecMath::Vector< 4 >&,
                                const VecMath::Vector< 3 >&, const VecMath::Vector< 3 >&, 
                                const VecMath::Vector< 3 >&) {
      throw NotYetImplementedException("drawTriangle()");
    }

    void ViewImpl::drawPolygon(const std::vector< VecMath::Vector< 4 > >&, 
                               const std::vector< VecMath::Vector< 3 > >&) {
      throw NotYetImplementedException("drawPolygon()");
    }

    unsigned int ViewImpl::getNumFrames() { return _numFrames; }
    
    unsigned int ViewImpl::getNumLoops() { return _numLoops; }
    
    bool ViewImpl::getWriteImages() { return _writeImages; }

    void ViewImpl::setWriteImages(bool on) { _writeImages = on; }

    void ViewImpl::setDefaultBackground() { setBackground(_defaultBackground); }
    
    void ViewImpl::setT(const VecMath::Vector< 4 >& _t) { _T = _t; }

    const VecMath::Vector< 4 >& ViewImpl::T() { return _T; }

    void ViewImpl::addT(const VecMath::Vector< 4 >& _dT) { _T += _dT; }
    
    void ViewImpl::setR(const VecMath::Rotation< 4 >& _r) { _R = _r; }

    const VecMath::Rotation< 4 >& ViewImpl::R() { return _R; }

    void ViewImpl::addR(const VecMath::Rotation< 4 >& _dR) { _R += _dR; }

    /** \param ddR Rotation to be added to the current Rotation state */
    void ViewImpl::adddR(const VecMath::Rotation<4> &ddR) {
        /// Make sure temporary is not optimized away
        VecMath::Rotation<4> newR = ddR + getdR();
        setdR(newR);
    }
    
    double ViewImpl::CamW() const { return _camW; }
    
    void ViewImpl::setCamW(const double& _cw) { _camW = _cw; }
    
    double ViewImpl::ScrW() const { return _scrW; }
    
    void ViewImpl::setScrW(const double& _sw) { _scrW = _sw; }
    
    double ViewImpl::distance() { return 1.; }
    
    const LightSource& ViewImpl::getDefaultLightSource() { return _defaultLightSource; }
    
    const LightSource& ViewImpl::getFlatLightSource() { return _flatLightSource; }

}
