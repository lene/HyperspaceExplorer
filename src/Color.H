///
/// C++ Interface: Color
///
/// Description:
///
//
/// @author Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///

#if !defined(COLOR_H)
#define COLOR_H

#include <string>
#include <sstream>

/// a class to represent a color value by its RGBA components \n
/// This class provides a single-stop interface to handle a color. It also
/// provides some utility functions to work with colors. \n
/// The color's components are stored as an array of floats. Access to the raw
/// array is provided, because the OpenGL functions I use to set a color need
/// an array of floats as parameter.
class Color {
    public:
        Color() { r() = g() = b() = a() = 0.; }
        Color(float, float, float, float = 0.);

        float &r() { return RGBA[0]; }  /// the red component of the color
        float &g() { return RGBA[1]; }  /// the green component of the color
        float &b() { return RGBA[2]; }  /// the blue component of the color
        float &a() { return RGBA[3]; }  /// the alpha component of the color

        /// direct access to the array of components, needed by OpenGL functions
        operator float *() { return RGBA; }
        Color operator *=(float);
        Color operator *(float);
        Color operator +=(float);
        Color operator +(float);
        void setComponentLowerLimit(float);
        void setComponentUpperLimit(float);

        operator std::string() const {
            std::ostringstream o;
            o <<"[ "<< RGBA[0] << ", "<< RGBA[1]<< ", "<< RGBA[2]<< " ]"
              << std::ends;
            return o.str();
        }

    private:
        float RGBA[4];  /// the components stored as an array of floats
};

/// construct a color from its R, G, B and alpha values
/// @param _r R value of the color
/// @param _g G value of the color
/// @param _b B value of the color
/// @param _a Alpha value of the color
inline Color::Color(float _r, float _g, float _b, float _a) {
    r() = _r;
    g() = _g;
    b() = _b;
    a() = _a;
}

/// scale the color by a float, keeping the RGB components between 0.0 and 1.0
/// @param x scaling factor
inline Color Color::operator *=(float x) {
    for (unsigned i = 0; i < 3; i++) {
        RGBA[i] *= x;
        if (RGBA[i] > 1.) RGBA[i] = 1.;
        if (RGBA[i] < 0.) RGBA[i] = 0.;
    }
    return *this;
}

/// scale the color by a float, keeping the RGB components between 0.0 and 1.0
/// @param x scaling factor
inline Color Color::operator *(float x) {
    Color tmp(*this);
    return (tmp *= x);
}

/// add a float to the color, keeping the RGB components between 0.0 and 1.0
/// @param x added term
inline Color Color::operator +=(float x) {
    for (unsigned i = 0; i < 3; i++) {
        RGBA[i] += x;
        if (RGBA[i] > 1.) RGBA[i] = 1.;
        if (RGBA[i] < 0.) RGBA[i] = 0.;
    }
    return *this;
}

/// add a float to the color, keeping the RGB components between 0.0 and 1.0
/// @param x added term
inline Color Color::operator +(float x) {
    Color tmp(*this);
    return (tmp += x);
}

/// make sure that none of the color components is less than the provided limit
/// @param l the lower limit for all color components
inline void Color::setComponentLowerLimit(float l) {
    for (unsigned i = 0; i < 3; i++) if (RGBA[i] < l) RGBA[i] = l;
}

/// make sure that none of the color components is more than the provided limit
/// @param u the upper limit for all color components
inline void Color::setComponentUpperLimit(float u) {
    for (unsigned i = 0; i < 3; i++) if (RGBA[i] > u) RGBA[i] = u;
}

#endif
