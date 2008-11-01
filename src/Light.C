///
/// C++ Implementation: Light
///
/// Description:
///
///
/// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///
#include "Light.H"

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
