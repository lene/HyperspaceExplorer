#ifndef LIGHT_H
#define LIGHT_H

#include "Vector.H"
#include "Color.H"

/// An interface for the definition of light sources
/** This class is just a POD struct with getters and setters to the location of
 *  the light source, and the color for its ambient value, its diffuse light and
 *  the specular reflections caused by the light source.
 *
 *  In addition to managing the attributes of the light source, as defined in
 *  the class Light, LightSource provides an abstract method render() which must
 *  be implemented in descendants to put the light source into the scene.
 *
 *  \author Helge Preuss <scout@hyperspace-travel.de>
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

class Light {
    public:

        Light(const LightSource &s): _lightSource(s) { }

        /// Set the light source into the scene.
        /** The actual rendering of the light source is done in the class
         *  implementing this interface.
         */
        virtual void render() const {
            throw std::logic_error("If LightSource::render() is called, the\
                    developer has done something wrong!");
        }

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
        LightSource _lightSource;
};

class LightOpenGL: public Light {
    public:
        /// Construct a black light source
        LightOpenGL(const LightSource &s): Light(s) { }

        /// Construct a light source with a location and color values
        /** \param pos The light source's location in homogenous coordinates
         *  \param a The light source's ambient color
         *  \param d The light source's diffuse color
         *  \param s The light source's color for specular reflections
        LightOpenGL(const VecMath::Vector<4> &pos,
                    const Color &a, const Color &d, const Color &s):
            LightSource(pos, a, d, s) { }
         */

        virtual void render() const {
            glEnable(GL_LIGHTING);                  //  turn on the light

            glLightfv (GL_LIGHT0, GL_AMBIENT, getAmbient()); // set the light properties
            glLightfv (GL_LIGHT0, GL_DIFFUSE, getDiffuse());
            glLightfv (GL_LIGHT0, GL_SPECULAR, getSpecular());
            glLightfv (GL_LIGHT0, GL_POSITION, getPosition());
            glEnable  (GL_LIGHT0);   // turn on the light
        }
};

#endif
