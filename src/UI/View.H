//
// C++ Interface: View
//
// Description: 
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef VIEW_H
#define VIEW_H 1

#include "ParameterMap.H"

class Function;

/// User interface elements
namespace UI {

    /// Interface to display four-dimensional objects
    /** Provides functions to display Function objects, transform them and
     *  animate them. Also to set various viewing states.
     *
     *  \ingroup UIGroup
     */
    class View {
        /// Thrown when a function is not supported by a View implementation
        class FunctionNotSupportedException: public std::runtime_error {
            public:
                /// Constructor; delegates to std::runtime_error constructor
                FunctionNotSupportedException(const std::string &what):
                    std::runtime_error(what) { }
        };

        public:
            View(): numFrames(1), numLoops(1) { }

            /// Set the currently displayed object to the given Function
            /** \param f The object to be set */
            virtual void setFunction(Function *f) = 0;

            /// Set the currently displayed object to a hypercube
            /** Necessary because I don't see a way to set the displayed object
             *  to a generic Object, only to Function s                       */
            virtual void ObjectHypercube() = 0;
            /// Set the currently displayed object to a hypersimplex
            /** Necessary because I don't see a way to set the displayed object
             *  to a generic Object, only to Function s                       */
            virtual void ObjectHyperpyramid() = 0;
            /// Set the currently displayed object to a hyper-menger sponge
            /** Necessary because I don't see a way to set the displayed object
             *  to a generic Object, only to Function s                       */
            virtual void ObjectHypersponge() = 0;
            /// Set the currently displayed object to a hyper-sierpinski gasket
            /** Necessary because I don't see a way to set the displayed object
             *  to a generic Object, only to Function s                       */
            virtual void ObjectGasket() = 0;

            /// Makes setting a parameter from the outside possible
            /** \param parmName Name of the parameter, as defined in the Function
             *  \param value Parameter value. Type must match exactly.            */
            template <typename T>
                    void setParameter(const std::string &parmName, const T &value) {
                ApplyChanges(ParameterMap(parmName, value));
            }

            /// Apply the given Transformation to the currently displayed object
            /** The object is redrawn after the Transformation.
             *  \param R Rotation to be performed on the object
             *  \param T Translation to be applied to the object
             */
            virtual void applyTransform(const VecMath::Rotation<4> &R,
                                        const VecMath::Vector<4> &T) = 0;
            /// Set the rotation step between frames for anumations
            /** \param _dr The rotation step between two frames of an animation
             */
            virtual void setdR(const VecMath::Rotation<4> &_dr) = 0;

            /// Set the number of frames for an animation
            virtual void setNumFrames(unsigned _numFrames) { numFrames =_numFrames; }
            /// Set the number of times \p _numFrames are repeated
            virtual void setNumLoops(unsigned _numLoops) { numLoops =_numLoops; }

            /// Start the animation with the currently active values
            virtual void animate() = 0;

            /// Set the width and height of the viewport
            virtual void setSize(unsigned, unsigned) = 0;

            /// Set the directory where to store image files
            virtual void setImgDir(const std::string &) = 0;
            /// Set the prefix of image file names, before the frame number and the extension
            virtual void setImgPrefix(const std::string &) = 0;

            /// Set the background color
            virtual void setBackground(const Color &) = 0;
            /// Turn display of colors on or off
            virtual void setColors(bool) = 0;
            /// Turn display of coordinate crosss on or off
            virtual void setCoordinates(bool) = 0;
            /// Turn depth cue on or off
            virtual void setFog(bool) = 0;
            /// Turn depth cue in four dimensions on or off
            virtual void setHyperfog(bool) = 0;
            /// Turn lighting on or off
            virtual void setLighting(bool) = 0;
            /// Turn gouraud shading on or off
            virtual void setShading(bool) = 0;
            /// Turn transparenc/line antialiasing on or off
            virtual void setTransparence(bool) = 0;
            /// Turn wireframe display on or off
            /// \param wire if true, displays wireframe model; else solid
            virtual void setWireframe(bool wire) = 0;

        protected:
            /// Apply changes in parameters and display them
            virtual void ApplyChanges(const ParameterMap &) = 0;

            /// Number of frames for animations
            virtual unsigned getNumFrames() { return numFrames; }
            /// Number of loops to repeat an animation
            virtual unsigned getNumLoops() { return numLoops; }
            /// Set a default background color
            virtual void setDefaultBackground() {
                static Color defaultBackground(0.1, 0.1, 0.1, 1.0);
                setBackground(defaultBackground);
            }

        private:
            unsigned numFrames; ///< number of frames for animations
            unsigned numLoops;  ///< number of loops to repeat an animation
    };

}

#endif
