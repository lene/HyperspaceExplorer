#ifndef LIGHT_H
#define LIGHT_H

#include "Vector.H"
#include "Color.H"

/// An interface for the definition and rendering of light sources
/**
    \author Helge Preuss <scout@hyperspace-travel.de>
*/
class Light {
    public:
        Light():
            _position(0.,0.,0.,0.),
            _ambient(0.,0.,0.,0.),
            _diffuse(0.,0.,0.,0.),
            _specular(0.,0.,0.,0.) { }

        virtual ~Light() { }

        virtual void render() = 0;

        virtual const VecMath::Vector<4> &getPosition() { return _position; }
        virtual void setPosition(const VecMath::Vector<4> &pos) { _position = pos; }

        virtual const Color &getAmbient() { return _ambient; }
        virtual void setAmbient(const Color &col) { _ambient = col; }

        virtual const Color &getDiffuse() { return _diffuse; }
        virtual void setDiffuse(const Color &col) { _diffuse = col; }

        virtual const Color &getSpecular() { return _specular; }
        virtual void setSpecular(const Color &col) { _specular = col; }

    private:
        VecMath::Vector<4> _position;
        Color _ambient;
        Color _diffuse;
        Color _specular;
};

#endif
