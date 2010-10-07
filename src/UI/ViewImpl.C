/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2008-2010  Lene Preuss <lene.preuss@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include "ViewImpl.h"

#include "Vector.impl.h"
#include "MultiDimensionalVector.impl.h"
#include "Rotation.impl.h"

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

    struct ViewImpl::Impl {

      Impl():
        _F(std::tr1::shared_ptr<Displayable>()),
        _colors(true), _coordinates(false), _fog(true), _hyperfog(false),
        _lighting(true), _shading(true), _solid(true), _transparence(false),
        _background (0.25, 0.25, 0.25, 1.),
        _dR(), _T(), _R(),
        _camW (-3.), _scrW (0.),
        _numFrames(1), _numLoops(1),
        _writeImages (false),
        _imageDir("/tmp"),
        _imagePrefix("HyperspaceExplorer_Image") { }

      std::tr1::shared_ptr<Displayable> _F;  ///< the Function object currently displayed

      bool _colors;       ///< whether to use colors in rendering
      bool _coordinates;  ///< whether to display the 4D coordinate cross
      bool _fog;          ///< whether to use depth cue/fog in rendering
      bool _hyperfog;     ///< whether to use four-dimensional depth cue
      bool _lighting;     ///< whether to use lighting in rendering
      bool _shading;      ///< whether to use shading in rendering
      bool _solid;        ///< whether to draw the objects' surfaces
      bool _transparence; ///< whether to use transparence/line antialiasing

      /// Stores all the lights in the scene
      /** \todo Abstract from std::vector and use a generic container */
      std::vector<Light *> _lights;
      Color _background;  ///< background color

      /// delta values in angles for 4D rotation for animations
      VecMath::Rotation<4> _dR;
      VecMath::Vector<4> _T;      ///< coordinates for 4D translation
      VecMath::Rotation<4> _R;    ///< angles for 4D rotation

      double _camW;        ///< W coordinate of the camera
      double _scrW;        ///< W coordinate of the screen

      unsigned _numFrames; ///< number of frames for animations
      unsigned _numLoops;  ///< number of loops to repeat an animation

      bool _writeImages;  ///< whether to save images to file system
      std::string _imageDir;      ///< directory to save images to
      std::string _imagePrefix;   ///< filename prefix for saved images

    };

    ViewImpl::ViewImpl():
        View(), pImpl_(new Impl) { }

    const std::tr1::shared_ptr< Displayable >& ViewImpl::F() const { return pImpl_->_F; }

    void ViewImpl::setF(Displayable* _f) { pImpl_->_F.reset(_f); }

    const VecMath::Rotation< 4 >& ViewImpl::getdR() { return pImpl_->_dR; }

    void ViewImpl::setdR(const VecMath::Rotation< 4 >& _dr) { pImpl_->_dR = _dr; }

    void ViewImpl::setNumFrames(unsigned int frames) { pImpl_->_numFrames = frames; }

    void ViewImpl::setNumLoops(unsigned int loops) { pImpl_->_numLoops = loops; }

    const std::string& ViewImpl::getImgDir() { return pImpl_->_imageDir; }

    /** \param s Directory where to store image files */
    void ViewImpl::setImgDir(const std::string &s) {
        pImpl_->_imageDir = s;
        setWriteImages(true);
    }

    const std::string& ViewImpl::getImgPrefix() { return pImpl_->_imagePrefix; }

    /** \param s Filename prefix for saved images */
    void ViewImpl::setImgPrefix(const std::string &s) {
        pImpl_->_imagePrefix = s;
        setWriteImages(true);
    }

    const Color& ViewImpl::getBackground() { return pImpl_->_background; }

    void ViewImpl::setBackground(const Color& bg) { pImpl_->_background = bg; }

    void ViewImpl::addLight(Light* l) { pImpl_->_lights.push_back(l); }

    void ViewImpl::removeLight(std::vector<Light *>::iterator i) {
        if (i >= pImpl_->_lights.end())
            throw std::logic_error("Tried to remove a light beyond the end of \
                    the list of lights");
        pImpl_->_lights.erase(i);
    }

    const std::vector< Light* >& ViewImpl::getLights() { return pImpl_->_lights; }

    bool ViewImpl::getColors() const { return pImpl_->_colors; }

    void ViewImpl::setColors(bool on) { pImpl_->_colors = on; }

    bool ViewImpl::getCoordinates() const { return pImpl_->_coordinates; }

    void ViewImpl::setCoordinates(bool on) { pImpl_->_coordinates = on; }

    bool ViewImpl::getFog() const { return pImpl_->_fog; }

    void ViewImpl::setFog(bool on) { pImpl_->_fog = on; }

    bool ViewImpl::getHyperfog() const { return pImpl_->_hyperfog; }

    void ViewImpl::setHyperfog(bool on) { pImpl_->_hyperfog = on; }

    bool ViewImpl::getLighting() const { return pImpl_->_lighting; }

    void ViewImpl::setLighting(bool on) { pImpl_->_lighting = on; }

    bool ViewImpl::getShading() const { return pImpl_->_shading; }

    void ViewImpl::setShading(bool on) { pImpl_->_shading = on; }

    bool ViewImpl::getSolid() const { return pImpl_->_solid; }

    void ViewImpl::setSolid(bool on) { pImpl_->_solid = on; }

    bool ViewImpl::getTransparence() const { return pImpl_->_transparence; }

    void ViewImpl::setTransparence(bool on) { pImpl_->_transparence = on; }

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

    void ViewImpl::drawCube(const VecMath::MultiDimensionalVector< VecMath::Vector< 4 >, 3 >& X,
                            unsigned int t, unsigned int u, unsigned int v,
                            const VecMath::Vector< 3 >& v0, const VecMath::Vector< 3 >& v1,
                            const VecMath::Vector< 3 >& v2, const VecMath::Vector< 3 >& v3,
                            const VecMath::Vector< 3 >& v4, const VecMath::Vector< 3 >& v5,
                            const VecMath::Vector< 3 >& v6, const VecMath::Vector< 3 >& v7) {
  if (t == 0) {
    drawQuadrangle(X[t][u][v], X[t][u][v+1], X[t][u+1][v+1], X[t][u+1][v],
                   v0, v1, v3, v2);
  }

  drawQuadrangle(X[t][u+1][v], X[t][u+1][v+1], X[t+1][u+1][v+1], X[t+1][u+1][v],
                 v2, v3, v7, v6);
  drawQuadrangle(X[t+1][u+1][v], X[t+1][u+1][v+1], X[t+1][u][v+1], X[t+1][u][v],
                 v6, v7, v5, v4);

  if (u == 0) {
    drawQuadrangle(X[t+1][u][v], X[t+1][u][v+1], X[t][u][v+1], X[t][u][v],
                   v4, v5, v1, v0);
  }

  if (v == 0) {
    drawQuadrangle(X[t][u][v], X[t][u+1][v], X[t+1][u+1][v], X[t+1][u][v],
                   v0, v2, v6, v4);
  }

  drawQuadrangle(X[t][u][v+1], X[t][u+1][v+1], X[t+1][u+1][v+1], X[t+1][u][v+1],
                 v1, v3, v7, v5);
}

    unsigned int ViewImpl::getNumFrames() { return pImpl_->_numFrames; }

    unsigned int ViewImpl::getNumLoops() { return pImpl_->_numLoops; }

    bool ViewImpl::getWriteImages() { return pImpl_->_writeImages; }

    void ViewImpl::setWriteImages(bool on) { pImpl_->_writeImages = on; }

    void ViewImpl::setDefaultBackground() { setBackground(_defaultBackground); }

    void ViewImpl::setT(const VecMath::Vector< 4 >& _t) { pImpl_->_T = _t; }

    const VecMath::Vector< 4 >& ViewImpl::T() { return pImpl_->_T; }

    void ViewImpl::addT(const VecMath::Vector< 4 >& _dT) { pImpl_->_T += _dT; }

    void ViewImpl::setR(const VecMath::Rotation< 4 >& _r) { pImpl_->_R = _r; }

    const VecMath::Rotation< 4 >& ViewImpl::R() { return pImpl_->_R; }

    void ViewImpl::addR(const VecMath::Rotation< 4 >& _dR) { pImpl_->_R += _dR; }

    /** \param ddR Rotation to be added to the current Rotation state */
    void ViewImpl::adddR(const VecMath::Rotation<4> &ddR) {
        /// Make sure temporary is not optimized away
        VecMath::Rotation<4> newR = ddR + getdR();
        setdR(newR);
    }

    double ViewImpl::CamW() const { return pImpl_->_camW; }

    void ViewImpl::setCamW(const double& _cw) { pImpl_->_camW = _cw; }

    double ViewImpl::ScrW() const { return pImpl_->_scrW; }

    void ViewImpl::setScrW(const double& _sw) { pImpl_->_scrW = _sw; }

    double ViewImpl::distance() { return 1.; }

    const LightSource& ViewImpl::getDefaultLightSource() { return _defaultLightSource; }

    const LightSource& ViewImpl::getFlatLightSource() { return _flatLightSource; }

}
