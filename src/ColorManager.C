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

void xyz2RGBColorManager::resizeCol() {
    if (f) {
        col.resize(f->getTsteps()+2);
        for (unsigned t = 0; t < col.size(); ++t) {
            col[t].resize(f->getUsteps()+2);
            for (unsigned u = 0; u < col[t].size(); ++u) {
                col[t][u].resize(f->getVsteps()+2);
            }
        }
    }
}

void xyz2RGBColorManager::calibrateColor(const Color &_col,
                                         float x, float y, float z) {
    unsigned ix = unsigned(x*f->getTsteps()),
             iy = unsigned(y*f->getUsteps()),
             iz = unsigned(z*f->getVsteps());
    col[ix][iy][iz] = _col;
}

Color xyz2RGBColorManager::getColor(const VecMath::Vector<4> &x) {
    float xscaled = (x[0]-f->getTmin())/(f->getTmax()-f->getTmin());
    if (xscaled < 0.) xscaled = 0.;
    if (xscaled > 1.) xscaled = 1.;
    float yscaled = (x[1]-f->getUmin())/(f->getUmax()-f->getUmin());
    if (yscaled < 0.) yscaled = 0.;
    if (yscaled > 1.) yscaled = 1.;
    float zscaled = (x[2]-f->getVmin())/(f->getVmax()-f->getVmin());
    if (zscaled < 0.) zscaled = 0.;
    if (zscaled > 1.) zscaled = 1.;
    unsigned ix = unsigned(xscaled*f->getTsteps()),
             iy = unsigned(yscaled*f->getUsteps()),
             iz = unsigned(zscaled*f->getVsteps());
    return col[ix][iy][iz];
}
void xyz2RGBColorManager::depthCueColor(double wmax, double wmin, double w,
                                        float x, float y, float z) {
    unsigned ix = unsigned(x*f->getTsteps()),
             iy = unsigned(y*f->getTsteps()),
             iz = unsigned(z*f->getTsteps());
    float DepthCueFactor = (wmax-w)/(wmax-wmin)*(1.0-offset4Ddepthcue)
                            +offset4Ddepthcue;
    col[ix][iy][iz] = ((col[ix][iy][iz]+(-offset4Ddepthcue))
                        + offset4Ddepthcue)*DepthCueFactor;
}
