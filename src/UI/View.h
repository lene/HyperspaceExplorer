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

#ifndef VIEW_H
#define VIEW_H 1

#include "ParameterMap.h"

#include <vector>

class Function;
class Light;
namespace VecMath {
  template <typename T, unsigned D> class MultiDimensionalVector;
}

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
            View() { }
            virtual ~View() { }

            /// \return The currently displayed object
            virtual const std::tr1::shared_ptr<Function> &F() const = 0;
            /// Set the currently displayed object to the given Function
            /** \param f The object to be set */
            virtual void setF(Function *f) = 0;

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
            /// Set the currently displayed object to a rotope
            /** Necessary because I don't see a way to set the displayed object
             *  to a generic Object, only to Function s                       */
            virtual void ObjectRotope() = 0;

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

            /// \return delta values in angles for 4D rotation for animations
            virtual const VecMath::Rotation<4> &getdR() = 0;
            /// Set the rotation step between frames for animations
            /** \param _dr Rotation step between two frames of an animation   */
            virtual void setdR(const VecMath::Rotation<4> &_dr) = 0;

            /// Set the number of frames for an animation
            virtual void setNumFrames(unsigned _numFrames) = 0;
            /// Set the number of times \p _numFrames are repeated
            virtual void setNumLoops(unsigned _numLoops) = 0;

            /// Start the animation with the currently active values
            virtual void animate() = 0;

            /// Set the width and height of the viewport
            virtual void setSize(unsigned, unsigned) = 0;

            /// \return directory to save images to
            virtual const std::string &getImgDir() = 0;
            /// Set the directory where to store image files
            virtual void setImgDir(const std::string &) = 0;

            /// \return filename prefix for saved images
            virtual const std::string &getImgPrefix() = 0;
            /// Set the prefix of image file names, before the frame number and the extension
            virtual void setImgPrefix(const std::string &) = 0;

            /// Set the background color
            virtual void setBackground(const Color &) = 0;
            /// \return The background color
            virtual const Color &getBackground() = 0;

            /// Add a light source to the scene
            virtual void addLight(Light *) = 0;
            /// Remove a light source from the scene
            virtual void removeLight(std::vector<Light *>::iterator) = 0;
            /// \return All lights in the scene
            /** \todo Abstract from std::vector and use a generic container */
            virtual const std::vector<Light *> &getLights() = 0;

            /// \return whether to use colors in rendering or not
            virtual bool getColors() const = 0;
            /// Turn display of colors in rendering on or off
            virtual void setColors(bool) = 0;

            /// \return whether to display the 4D coordinate cross or not
            virtual bool getCoordinates() const = 0;
            /// Turn display of 4D coordinate cross on or off
            virtual void setCoordinates(bool) = 0;

            /// \return whether to use depth cue/fog in rendering or not
            virtual bool getFog() const = 0;
            /// Turn depth cue on or off
            virtual void setFog(bool) = 0;

            /// \return whether to use four-dimensional depth cue or not
            virtual bool getHyperfog() const = 0;
            /// Turn depth cue in four dimensions on or off
            virtual void setHyperfog(bool) = 0;

            /// \return whether to use lighting in rendering or not
            virtual bool getLighting() const = 0;
            /// Turn lighting on or off
            virtual void setLighting(bool) = 0;

            /// \return whether to use shading in rendering or not
            virtual bool getShading() const = 0;
            /// Turn gouraud shading on or off
            virtual void setShading(bool) = 0;

            /// \return whether to draw the objects' surfaces
            virtual bool getSolid() const = 0;
            /// Turn wireframe display on or off
            /** \param on if true, displays wireframe model; else solid       */
            virtual void setSolid(bool on) = 0;

            /// \return whether to use transparence/line antialiasing or not
            virtual bool getTransparence() const = 0;
            /// Turn transparence/line antialiasing on or off
            virtual void setTransparence(bool) = 0;

            virtual void drawVertex(const VecMath::Vector< 4 > &x, const VecMath::Vector< 3 > &xscr) = 0;
            virtual void drawLine(const VecMath::Vector< 4 > &x0, const VecMath::Vector< 4 > &x1,
                                  const VecMath::Vector< 3 > &xscr0, const VecMath::Vector< 3 > &xscr1) = 0;
            virtual void drawTriangle(const VecMath::Vector< 4 > &x0, const VecMath::Vector< 4 > &x1,
                                      const VecMath::Vector< 4 > &x2,
                                      const VecMath::Vector< 3 > &xscr0, const VecMath::Vector< 3 > &xscr1,
                                      const VecMath::Vector< 3 > &xscr2) = 0;
            virtual void drawQuadrangle(const VecMath::Vector< 4 > &x0, const VecMath::Vector< 4 > &x1,
                                        const VecMath::Vector< 4 > &x2, const VecMath::Vector< 4 > &x3,
                                        const VecMath::Vector< 3 > &xscr0, const VecMath::Vector< 3 > &xscr1,
                                        const VecMath::Vector< 3 > &xscr2, const VecMath::Vector< 3 > &xscr3) = 0;
            virtual void drawPolygon(const std::vector< VecMath::Vector< 4 > > &x0,
                                     const std::vector< VecMath::Vector< 3 > > &xscr0) = 0;
            virtual void drawCube(const VecMath::MultiDimensionalVector< VecMath::Vector<4>, 3 > &X,
                                  unsigned t, unsigned u, unsigned v,
                                  const VecMath::Vector<3> &v0, const VecMath::Vector<3> &v1,
                                  const VecMath::Vector<3> &v2, const VecMath::Vector<3> &v3,
                                  const VecMath::Vector<3> &v4, const VecMath::Vector<3> &v5,
                                  const VecMath::Vector<3> &v6, const VecMath::Vector<3> &v7) = 0;
        protected:
            /// Apply changes in parameters and display them
            virtual void ApplyChanges(const ParameterMap &) = 0;

            /// Number of frames for animations
            virtual unsigned getNumFrames() = 0;
            /// Number of loops to repeat an animation
            virtual unsigned getNumLoops() = 0;

            /// \return whether to save images to file system
            virtual bool getWriteImages() = 0;
            /// Turn saving images to file system on or off
            virtual void setWriteImages(bool) = 0;

            /// Set a default background color
            virtual void setDefaultBackground() = 0;

    };

}

#endif
