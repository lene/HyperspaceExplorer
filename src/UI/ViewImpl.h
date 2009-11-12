//
// C++ Interface: ViewImpl
//
// Description:
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef VIEW_IMPL_H
#define VIEW_IMPL_H 1

#include "View.h"
#include "Light.h"

namespace UI {

    /// Interface with attributes to display four-dimensional objects
    /** This class provides a partial implementation of the class View, with
     *  the class attributes and their getters and setters.
     *
     *  It also stores view states, which are common to all implementations,
     *  such as:
     *      - The object which is currently displayed
     *      - The 4D transformation of that object
     *      - The 4D viewport (camera and screen position)
     *
     *  \ingroup UIGroup
     */
    class ViewImpl: public View {

        public:

            /// Initialize the View with default values for all states
            ViewImpl();

            /// \return The currently displayed object
            virtual const std::auto_ptr<Function> &F() const { return _F; }
            /// Implementation of UI::View::setFunction
            virtual void setF(Function *_f) { _F.reset(_f); }

            /// \return delta values in angles for 4D rotation for animations
            virtual const VecMath::Rotation<4> &getdR() { return _dR; }
            /// Set the rotation step between frames for animations
            /** \param _dr Rotation step between two frames of an animation   */
            virtual void setdR(const VecMath::Rotation<4> &_dr) { _dR = _dr; }

            /// Set the number of frames for an animation
            virtual void setNumFrames(unsigned frames) { _numFrames = frames; }
            /// Set the number of times \p _numFrames are repeated
            virtual void setNumLoops(unsigned loops) { _numLoops = loops; }

            /// \return directory to save images to
            virtual const std::string &getImgDir() { return _imageDir; }
            /// Set the directory where to store image files
            virtual void setImgDir(const std::string &);
            /// \return filename prefix for saved images
            virtual const std::string &getImgPrefix() { return _imagePrefix; }
            /// Set the prefix of image file names, before the frame number and the extension
            virtual void setImgPrefix(const std::string &);

            /// \return The background color
            virtual const Color &getBackground() { return _background; }
            /// Set the background color
            virtual void setBackground(const Color &bg) { _background = bg; }

            /// Add a light source to the scene
            /** \param l Light source added to the scene */
            virtual void addLight(Light *l) { _lights.push_back(l); }
            /// Remove a light source from the scene
            virtual void removeLight(std::vector<Light *>::iterator);
            /// \return All lights in the scene
            /** \todo Abstract from std::vector and use a generic container */
            virtual const std::vector<Light *> &getLights() { return _lights; }

            /// \return whether to use colors in rendering or not
            virtual bool getColors() const { return _colors; }
            /// Turn display of colors on or off
            virtual void setColors(bool on) { _colors = on; }

            /// \return whether to display the 4D coordinate cross or not
            virtual bool getCoordinates() const { return _coordinates; }
            /// Turn display of coordinate cross on or off
            virtual void setCoordinates(bool on) { _coordinates = on; }

            /// \return whether to use depth cue/fog in rendering or not
            virtual bool getFog() const { return _fog; }
            /// Turn depth cue on or off
            virtual void setFog(bool on) { _fog = on; }

            /// \return whether to use four-dimensional depth cue or not
            virtual bool getHyperfog() const { return _hyperfog; }
            /// Turn depth cue in four dimensions on or off
            virtual void setHyperfog(bool on) { _hyperfog = on; }

            /// \return whether to use lighting in rendering or not
            virtual bool getLighting() const { return _lighting; }
            /// Turn lighting on or off
            virtual void setLighting(bool on) { _lighting = on; }

            /// \return whether to use shading in rendering or not
            virtual bool getShading() const { return _shading; }
            /// Turn gouraud shading on or off
            virtual void setShading(bool on) { _shading = on; }

            /// \return whether to draw the objects' surfaces
            virtual bool getSolid() const { return _solid; }
            /// Turn wireframe display on or off
            /** \param on if true, displays wireframe model; else solid       */
            virtual void setSolid(bool on) { _solid = on; }

            /// \return whether to use transparence/line antialiasing or not
            virtual bool getTransparence() const { return _transparence; }
            /// Turn transparenc/line antialiasing on or off
            virtual void setTransparence(bool on) { _transparence = on; }

        protected:

            /// Number of frames for animations
            virtual unsigned getNumFrames() { return _numFrames; }
            /// Number of loops to repeat an animation
            virtual unsigned getNumLoops() { return _numLoops; }

            /// \return whether to save images to file system
            virtual bool getWriteImages() { return _writeImages; }
            /// Turn saving images to file system on or off
            virtual void setWriteImages(bool on) { _writeImages = on; }

            /// Set a default background color
            virtual void setDefaultBackground();

            /// \param _t New translation state
            virtual void setT(const VecMath::Vector<4> &_t) { _T = _t; }
            /// \return Current translation state
            virtual const VecMath::Vector<4> &T() { return _T; }
            /// Add a Translation to the current translation state
            /** \param _dT Delta t */
            virtual void addT(const VecMath::Vector<4> &_dT) { _T += _dT; }

            /// \param _r New rotation state
            virtual void setR(const VecMath::Rotation<4> &_r) { _R = _r; }
            /// \return Current rotation state
            virtual const VecMath::Rotation<4> &R() { return _R; }
            /// Add a Rotation to the current rotation state
            virtual void addR(const VecMath::Rotation<4> &_dR) { _R += _dR; }

            /// Add a Rotation to the current rotation speed
            virtual void adddR(const VecMath::Rotation<4> &);

            /// \return W coordinate of the camera
            double CamW() const { return _camW; }
            /// \param _cw W coordinate of the camera
            void setCamW(const double &_cw) { _camW = _cw; }
            /// \return W coordinate of the screen to project onto
            double ScrW() const { return _scrW; }
            /// \param _sw W coordinate of the screen to project onto
            void setScrW(const double &_sw) { _scrW = _sw; }

            /// Viewport distance; currently fixed to 1
            double distance() { return 1.; }

            /// \return Point LightSource with sensible defaults for good light
            static const LightSource &getDefaultLightSource() {
                return _defaultLightSource;
            }
            /// \return LightSource for flat, all-ambient lighting
            static const LightSource &getFlatLightSource() {
                return _flatLightSource;
            }

        private:

            std::auto_ptr<Function> _F;  ///< the Function object currently displayed

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

            /// Default Color for the background
            static Color _defaultBackground;

            /// Point LightSource with sensible defaults for good light
            static LightSource _defaultLightSource;
            /// LightSource for flat, all-ambient lighting
            static LightSource _flatLightSource;

    };

}

#endif