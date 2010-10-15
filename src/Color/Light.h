/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

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

#ifndef LIGHT_H
#define LIGHT_H

#include "Vector.h"
#include "Color.h"

/// An interface for the definition of light sources' attributes
/** This class is just a POD struct with getters and setters to the location of
 *  the light source, and the color for its ambient value, its diffuse light and
 *  the specular reflections caused by the light source.
 *
 *  \author Lene Preuss <lene.preuss@gmail.com>
 */
class LightSource {
    public:
        /// Construct a black light source
        LightSource():
            _position(0.,0.,0.,0.),
            _ambient(0.,0.,0.,0.),
            _diffuse(0.,0.,0.,0.),
            _specular(0.,0.,0.,0.) { }

        /// Construct a light source with a location and color values
        /** \param pos The light source's location in homogenous coordinates
         *  \param a The light source's ambient color
         *  \param d The light source's diffuse color
         *  \param s The light source's color for specular reflections
         */
        LightSource(const VecMath::Vector<4> &pos,
                    const Color &a, const Color &d, const Color &s):
            _position(pos), _ambient(a), _diffuse(d), _specular(s) { }

        /// Destroy a light source. Does nothing except releasing members.
        virtual ~LightSource() { }

        /// \return The light source's location in homogenous coordinates
        virtual const VecMath::Vector<4> &getPosition() const { return _position; }
        /// \param pos The light source's location in homogenous coordinates
        virtual void setPosition(const VecMath::Vector<4> &pos) { _position = pos; }

        /// \return The light source's ambient color
        virtual const Color &getAmbient() const { return _ambient; }
        /// \param col The light source's ambient color
        virtual void setAmbient(const Color &col) { _ambient = col; }

        /// \return The light source's diffuse color
        virtual const Color &getDiffuse() const { return _diffuse; }
        /// \param col The light source's diffuse color
        virtual void setDiffuse(const Color &col) { _diffuse = col; }

        /// \return The light source's color for specular reflections
        virtual const Color &getSpecular() const { return _specular; }
        /// \param col The light source's color for specular reflections
        virtual void setSpecular(const Color &col) { _specular = col; }

    private:
        /// The light source's location in homogenous coordinates
        VecMath::Vector<4> _position;
        Color _ambient;     ///< The light source's ambient color
        Color _diffuse;     ///< The light source's diffuse color
        Color _specular;    ///< The light source's color for specular reflections
};

/// An interface for the definition of light sources
/** In addition to managing the attributes of the light source, as defined in
 *  the class LightSource, Light provides an abstract method render() which must
 *  be implemented in descendants to put the light source into the scene.
 *
 *  \author Helge Preuss <lene.preuss@gmail.com>
 */
class Light {
    public:

        /// Construct a Light from a LightSource definition
        Light(const LightSource &s): _lightSource(s) { }

        /// Construct a light directly from location and color values
        /** \param pos The light source's location in homogenous coordinates
         *  \param a The light source's ambient color
         *  \param d The light source's diffuse color
         *  \param s The light source's color for specular reflections
         */
        Light(const VecMath::Vector<4> &pos,
              const Color &a, const Color &d, const Color &s):
            _lightSource(pos, a, d, s) { }

        /// Set the light source into the scene.
        /** The actual rendering of the light source is done in the class
         *  implementing this interface.
         */
        virtual void render() const = 0;

    protected:

        /// \return The light source's location in homogenous coordinates
        virtual const VecMath::Vector<4> &getPosition() const {
            return _lightSource.getPosition();
        }
        /// \return The light source's ambient color
        virtual const Color &getAmbient() const {
            return _lightSource.getAmbient();
        }
        /// \return The light source's diffuse color
        virtual const Color &getDiffuse() const {
            return _lightSource.getDiffuse();
        }
        /// \return The light source's color for specular reflections
        virtual const Color &getSpecular() const {
            return _lightSource.getSpecular();
        }

    private:
        /// The LightSource object defining the properties of the Light
        LightSource _lightSource;
};

/// Implementation of a Light for OpenGL
class LightOpenGL: public Light {
    public:
        /// Construct a LightOpenGL from a LightSource definition
        LightOpenGL(const LightSource &s): Light(s) { }

        /// Set the light source into the scene.
        virtual void render() const;
};

#endif
