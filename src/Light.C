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

#include "Light.h"
#include "Vector.impl.h"

/// Includes all OpenGL headers in a system-independent way
#include <QGLWidget>

/** \todo GL_LIGHT0 is hardcoded, make this variable. To quote from the OpenGL
 *        API docs: "It is always the case that GL_LIGHTi = GL_LIGHT0 + i."
 */
void LightOpenGL::render() const {
    if (!glIsEnabled(GL_LIGHTING)) glEnable(GL_LIGHTING);

    glLightfv (GL_LIGHT0, GL_AMBIENT, getAmbient()); // set the light properties
    glLightfv (GL_LIGHT0, GL_DIFFUSE, getDiffuse());
    glLightfv (GL_LIGHT0, GL_SPECULAR, getSpecular());
    glLightfv (GL_LIGHT0, GL_POSITION, getPosition());
    glEnable  (GL_LIGHT0);   // turn on the light
}
