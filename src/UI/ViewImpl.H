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

#include "View.H"

namespace UI {

    /// Interface with attributes to display four-dimensional objects
    /** This class provides a partial implementation of the class View, with
     *  the class attributes and their getters and setters
     *
     *  \ingroup UIGroup
     */
    class ViewImpl: public View {

        public:
            ViewImpl():
                View(),
                _colors(true), _coordinates(false), _fog(true), _hyperfog(false),
                _lighting(true), _shading(true), _solid(true), _transparence(false),
                _numFrames(1), _numLoops(1) { }

            /// Set the rotation step between frames for anumations
            /** \param _dr The rotation step between two frames of an animation
             */
            virtual void setdR(const VecMath::Rotation<4> &_dr) = 0;

            /// Set the number of frames for an animation
            virtual void setNumFrames(unsigned frames) { _numFrames = frames; }
            /// Set the number of times \p _numFrames are repeated
            virtual void setNumLoops(unsigned loops) { _numLoops = loops; }

            /// Set the directory where to store image files
            virtual void setImgDir(const std::string &) = 0;
            /// Set the prefix of image file names, before the frame number and the extension
            virtual void setImgPrefix(const std::string &) = 0;

            /// Set the background color
            virtual void setBackground(const Color &) = 0;
            
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
            /// Apply changes in parameters and display them
            virtual void ApplyChanges(const ParameterMap &) = 0;

            /// Number of frames for animations
            virtual unsigned getNumFrames() { return _numFrames; }
            /// Number of loops to repeat an animation
            virtual unsigned getNumLoops() { return _numLoops; }

            /// Set a default background color
            virtual void setDefaultBackground() {
                static Color defaultBackground(0.1, 0.1, 0.1, 1.0);
                setBackground(defaultBackground);
            }

        private:
            bool _colors;       ///< whether to use colors in rendering
            bool _coordinates;  ///< whether to display the 4D coordinate cross
            bool _fog;          ///< whether to use depth cue/fog in rendering
            bool _hyperfog;     ///< whether to use four-dimensional depth cue
            bool _lighting;     ///< whether to use lighting in rendering
            bool _shading;      ///< whether to use shading in rendering
            bool _solid;        ///< whether to draw the objects' surfaces
            bool _transparence; ///< whether to use transparence/line antialiasing

            unsigned _numFrames; ///< number of frames for animations
            unsigned _numLoops;  ///< number of loops to repeat an animation
    };

}

#endif
