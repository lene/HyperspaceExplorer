///
/// C++ Implementation: ColorManager
///
/// Description:
///
///
/// \author Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

#include "ColorManager.H"
#include "Function.H"

/** set the current OpenGL color
 *  uses HARDCODED simple algorithm to set ambient and specular values for a
 *  specific color: if halves resp. dobles them, clipping at 1.0
 *  @todo make the agorithm which computes the ambient and specular values
 *        variable
 *  @param rgb color value to be set                                          */
void ColorManager::setColor(const VecMath::Vector<4> &x) {
    Color RGB = getColor(x);

    glMaterialfv (GL_FRONT, GL_DIFFUSE, RGB);

    RGB *= ambientColorModifier;
    glMaterialfv (GL_FRONT, GL_AMBIENT, RGB);

    RGB *= specularColorModifier/ambientColorModifier;
    RGB.setComponentLowerLimit(specularColorMinimum);
    glMaterialfv (GL_FRONT, GL_SPECULAR, RGB);
    glMaterialf (GL_FRONT, GL_SHININESS, SHININESS);
}

void xyz2RGBColorManager::calibrateColor(const Color &_col,
                                         const VecMath::Vector<4> &x) {
    col.insert(std::make_pair(x, _col));
}

Color xyz2RGBColorManager::getColor(const VecMath::Vector<4> &x) {
    if (col.count(x)) {
        return col[x];
    } else {
        std::map<VecMath::Vector<4>, double> distances;
        for (colormap::iterator i = col.begin(); i != col.end(); ++i) {
            distances[i->first] = (x-i->first).sqnorm();
            std::cerr << distances[i->first] << std::endl;
        }
    }
}
void xyz2RGBColorManager::depthCueColor(double wmax, double wmin, double w,
                                        const VecMath::Vector<4> &x) {
    float DepthCueFactor = (wmax-w)/(wmax-wmin)*(1.0-offset4Ddepthcue)
                            +offset4Ddepthcue;
    col[x] = ((col[x]+(-offset4Ddepthcue))
                        + offset4Ddepthcue)*DepthCueFactor;
}
