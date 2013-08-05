/* 
 * File:   GLUPerspective.cpp
 * Author: lene
 * 
 * Created on August 3, 2013, 5:23 PM
 */

#include "GLUPerspective.h"

#include "Vector.impl.h"
#include "NotYetImplementedException.h"

#include <GL/glu.h>

bool GLUPerspective::use_new_gl_;

GLUPerspective::GLUPerspective(float fov, float aspect, float znear, float zfar):
        fov_(fov), aspect_(aspect), znear_(znear), zfar_(zfar) {
//    const GLubyte * gl_version = glGetString(GL_VERSION);
//    if (gl_version[0] <= '2') 
        use_new_gl_ = false;
    
    if (!use_new_gl_) return;
    
    GLfloat ymax = znear * tan(fov * PI_OVER_360),
            ymin = -ymax,
            xmax = ymax * aspect,
            xmin = ymin * aspect;

    GLfloat width = xmax - xmin,
            height = ymax - ymin;

    GLfloat depth = zfar - znear;
    GLfloat q = -(zfar + znear) / depth;
    GLfloat qn = -2 * (zfar * znear) / depth;

    GLfloat w = 2 * znear / width;
    w = w / aspect;
    GLfloat h = 2 * znear / height;
  
    perpective_projection_matrix_[1] = perpective_projection_matrix_[2] = perpective_projection_matrix_[3] = 
    perpective_projection_matrix_[4] = perpective_projection_matrix_[6] = perpective_projection_matrix_[7] =
    perpective_projection_matrix_[8] = perpective_projection_matrix_[9] = 
    perpective_projection_matrix_[12] = perpective_projection_matrix_[13] = perpective_projection_matrix_[15] = 0.;
    perpective_projection_matrix_[0] = w;
    perpective_projection_matrix_[5] = h;
    perpective_projection_matrix_[10] = q;
    perpective_projection_matrix_[11] = -1;
    perpective_projection_matrix_[14] = qn;
}

void GLUPerspective::set() {
    if (use_new_gl_) {
        throw NotYetImplementedException("GLUPerspective::set() for OpenGL >= 3.0");
/*        
      GLint shader_id = 0; // insert shader id here!
      GLint location = glGetUniformLocation(shader_id, "u_proj_matrix");
      glUniformMatrix4fv(location,
                     1, GL_FALSE, perpective_projection_matrix_);
*/      
    } else {
        gluPerspective(fov_, aspect_, znear_, zfar_);
    }
    
}

void GLUPerspective::setLookAt(
        const VecMath::Vector<3>& eye, 
        const VecMath::Vector<3>& center, 
        const VecMath::Vector<3>& up) {
    if (use_new_gl_) {
        throw NotYetImplementedException("GLUPerspective::setLookAt() for OpenGL >= 3.0");
    } else {
        gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
    }
}