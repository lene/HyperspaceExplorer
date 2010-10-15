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

#if !defined(COLOR_H)
#define COLOR_H

#include <string>
#include <sstream>

#include <QColor>

#include "Vector.h"

/// A class to represent a color value by its RGBA components
/** This class provides a single-stop interface to handle a color. It also
 *  provides some utility functions to work with colors.
 *
 *  The color's components are stored as an array of floats. Access to the raw
 *  array is provided, because the OpenGL functions I use to set a color need
 *  an array of floats as parameter.
 *  \ingroup Coloring                                                         */
class Color {
    public:
        Color() { r() = g() = b() = a() = 0.; }
        Color(float, float, float, float = 1.);
        Color(const VecMath::Vector<4> &);
        Color(const QColor &);

        float &r() { return RGBA[0]; }      ///< the red component of the color
        float r() const { return RGBA[0]; } ///< the red component of the color
        float &g() { return RGBA[1]; }      ///< the green component of the color
        float g() const { return RGBA[1]; } ///< the green component of the color
        float &b() { return RGBA[2]; }      ///< the blue component of the color
        float b() const { return RGBA[2]; } ///< the blue component of the color
        float &a() { return RGBA[3]; }      ///< the alpha component of the color
        float a() const { return RGBA[3]; } ///< the alpha component of the color

        /// direct access to the array of components, needed by OpenGL functions
        operator float *() { return RGBA; }
        /// direct access to the array of components, needed by OpenGL functions
        operator const float *() const { return RGBA; }
        Color operator *=(float);
        Color operator *=(const Color &);
        Color operator *(float);
        Color operator *(const Color &);
        Color operator +=(float);
        Color operator +(float);
        Color operator +=(const Color &);
        Color operator +(const Color &);
        void setComponentLowerLimit(float);
        void setComponentUpperLimit(float);

        /// converts the color's RGB values to a string
        operator std::string() const {
            std::ostringstream o;
            o <<"[ "<< RGBA[0] << ", "<< RGBA[1]<< ", "<< RGBA[2]<< " ]"
              << std::ends;
            return o.str();
        }

    private:
        float RGBA[4];  ///< the components stored as an array of floats
};

/// construct a Color from its R, G, B and alpha values
/** @param _r R value of the color
 *  @param _g G value of the color
 *  @param _b B value of the color
 *  @param _a Alpha value of the color                                        */
inline Color::Color(float _r, float _g, float _b, float _a) {
    r() = _r;
    g() = _g;
    b() = _b;
    a() = _a;
}

/// construct a Color from a Vector containing its R, G, B and alpha values
/** @param x RGBA values of the color                                         */
inline Color::Color(const VecMath::Vector<4> &x) {
    r() = x[0];
    g() = x[1];
    b() = x[2];
    a() = x[3];
}

/// construct a Color from a QColor
/** @param col RGBA values of the color                                       */
inline Color::Color(const QColor &col) {
    qreal qr, qg, qb, qa;
    col.getRgbF(&qr, &qg, &qb, &qa);
    r() = qr;
    g() = qg;
    b() = qb;
    a() = qa;
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

/// Multiply two colors, component by component
/// @param x scaling factor
inline Color Color::operator *=(const Color &x) {
    for (unsigned i = 0; i < 3; i++) {
        RGBA[i] *= x.RGBA[i];
#if 0
        if (RGBA[i] > 1.) RGBA[i] = 1.;
        if (RGBA[i] < 0.) RGBA[i] = 0.;
#endif
    }
    return *this;
}

/// scale the color by a float, keeping the RGB components between 0.0 and 1.0
/// @param x scaling factor
inline Color Color::operator *(float x) {
    Color tmp(*this);
    return (tmp *= x);
}

/// Multiply two colors, component by component
/// @param x scaling factor
inline Color Color::operator *(const Color &x) {
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

/// add a float to the color, keeping the RGB components between 0.0 and 1.0
/// @param x added term
inline Color Color::operator +=(const Color &x) {
    for (unsigned i = 0; i < 3; i++) {
        RGBA[i] += x.RGBA[i];
#       if 0
            if (RGBA[i] > 1.) RGBA[i] = 1.;
            if (RGBA[i] < 0.) RGBA[i] = 0.;
#       endif
    }
    return *this;
}

/// add a float to the color, keeping the RGB components between 0.0 and 1.0
/// @param x added term
inline Color Color::operator +(const Color &x) {
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
