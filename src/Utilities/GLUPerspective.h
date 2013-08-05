/* 
 * File:   GLUPerspective.h
 * Author: lene
 *
 * Created on August 3, 2013, 5:23 PM
 */

#ifndef GLUPERSPECTIVE_H
#define	GLUPERSPECTIVE_

#include "Vector.h"

#include <cmath>
#include <GL/gl.h>

class GLUPerspective {
public:
    GLUPerspective(float fov, float aspect, float znear, float zfar);
    void set();
    void setLookAt(
        const VecMath::Vector<3> & eye, 
        const VecMath::Vector<3> & center, 
        const VecMath::Vector<3> & up
    );
    
private:
    const GLfloat PI_OVER_360 = M_PI/360.;
    static bool use_new_gl_;
    GLfloat perpective_projection_matrix_[16];
    GLfloat fov_, aspect_, znear_, zfar_;
    
};

#endif	/* GLUPERSPECTIVE_H */

