///
/// C++ Implementation: ColorManager
///
/// Description:
///
///
/// \author Helge Preuss <lene.preuss@gmail.com>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

#include "ColorManager.h"
#include "Function.h"
#include "Vector.impl.h"

using VecMath::Vector;
using std::vector;

template <typename T> T min(T a, T b) { return (a < b? a: b); }

ColorManager::ColorManager():
        f(0),
        ambientColorModifier(0.5), specularColorModifier(2.),
        specularColorMinimum(0.5), SHININESS(32.), ALPHA(0.8),
        offset4Ddepthcue(0.1) { }

/** \param _f The Function for which to manage colors */
ColorManager::ColorManager(Function *_f):
        f(_f),
        ambientColorModifier(0.5), specularColorModifier(2.),
        specularColorMinimum(0.5), SHININESS(32.), ALPHA(0.8),
        offset4Ddepthcue(0.1) { }

void ColorManager::setFunction(Function *_f) {
    f = _f;
    f->calibrateColors();
}

/** @param x four-dimensional coordinate for which the color is sought*/
void ColorManager::setColor(const VecMath::Vector<4> &x) {
    setRGB(getColor(x));
}

/** uses HARDCODED simple algorithm to set ambient and specular values for a
 *  specific color: if halves resp. dobles them, clipping at 1.0
 *  @todo make the agorithm which computes the ambient and specular values
 *        variable
 *  @param rgb color value to be set                                          */
void ColorManager::setRGB(const Color &rgb) {
    Color RGB(rgb);

    glMaterialfv (GL_FRONT, GL_DIFFUSE, RGB);

    RGB *= ambientColorModifier;
    glMaterialfv (GL_FRONT, GL_AMBIENT, RGB);

    RGB *= specularColorModifier/ambientColorModifier;
    RGB.setComponentLowerLimit(specularColorMinimum);
    glMaterialfv (GL_FRONT, GL_SPECULAR, RGB);
    glMaterialf (GL_FRONT, GL_SHININESS, SHININESS);
}

////////////////////////////////////////////////////////////////////////////////

ColorManagerManager::BadColorManagerException::BadColorManagerException(
        const std::string &what):
        std::runtime_error("\""+what+"\" is not the name of a registered"
        " ColorManager") { }

/** \param functionName Name of the function that was called
 */
ColorManagerManager::ColorManagerUnsetException::ColorManagerUnsetException(
    const std::string &functionName):
    std::logic_error("ColorManagerManager::"+functionName+"() called before a ColorManager was set") { }

void ColorManagerManager::setColorManager(ColorManager* cm) {
    Function *ftmp = 0;
    if (colorManager.get()) ftmp = colorManager->getFunction();
    colorManager.reset(cm);
    if (ftmp) cm->setFunction(ftmp);
}

bool ColorManagerManager::isColorManagerSet() const {
    return (bool)colorManager.get();
}

void ColorManagerManager::setFunction(Function* _f) {
    if (isColorManagerSet()) colorManager->setFunction(_f);
//    throw ColorManagerUnsetException("setFunction");
}

void ColorManagerManager::calibrateColor(const VecMath::Vector<4> &x,
                                         const Color &_col) {
    if (isColorManagerSet()) colorManager->calibrateColor(x, _col);
//    throw ColorManagerUnsetException("calibrateColor");
}

void ColorManagerManager::setColor(const VecMath::Vector< 4 >& x) {
    if (isColorManagerSet()) colorManager->setColor(x);
//    throw ColorManagerUnsetException("setColor");
}

Color ColorManagerManager::getColor(const VecMath::Vector< 4 >& x) {
    if (isColorManagerSet()) return colorManager->getColor(x);
//    throw ColorManagerUnsetException("getColor");
    return Color();
}

void ColorManagerManager::depthCueColor(double wmax, double wmin, double w,
                                        const VecMath::Vector<4> &x) {
    if (isColorManagerSet()) return colorManager->depthCueColor(wmax, wmin, w, x);
//    throw ColorManagerUnsetException("depthCueColor");
}

void ColorManagerManager::setRGB(const Color& _col)
{
    if (isColorManagerSet()) colorManager->setRGB(_col);
//    throw ColorManagerUnsetException("setRGB");
}

std::string ColorManagerManager::getContents() {
    if (isColorManagerSet()) return colorManager->getContents();
//    throw ColorManagerUnsetException("setRGB");
    return "";
}

/** \param name The name by which this class is called from outside. This name
 *              is passed to setColorManager() to select the desired
 *              ColorManager.
 *  \param creator A function which returns a new instance of the registered
 *                 ColorManager
 *  \return Whether the registration succeeded. This return value is
 *          needed because registration takes place by defining a
 *          <tt>const bool</tt> in a global anonymous namespace.
 *  \see <a href="classColorManager.html#_details">ColorManager</a> for an
 *       example usage of this function.
 */
bool ColorManagerManager::registerColorManager(const std::string &name,
                                               CreateColMgrCallback creator) {
    return callbacks.insert(CallbackMap::value_type(name, creator)).second;
}

/** I can't really think of a reason why one would want to unregister a
 *  ColorManager at runtime, so this function is just there for the sake
 *  of completeness. It's a one-liner anyway.
 *
 *  \param name The name by which the ColorManager is called from outside
 */
bool ColorManagerManager::unregisterColorManager(const std::string &name) {
    return callbacks.erase(name) == 1;
}

std::vector<std::string> ColorManagerManager::getRegisteredColorManagers() {
    std::vector<std::string> ret;
    for (CallbackMap::const_iterator i = callbacks.begin();
         i != callbacks.end(); ++i) {
        ret.push_back(i->first);
    }
    return ret;
}

/** \param name Name the ColorManager is known and registered by
 */
void ColorManagerManager::setColorManager(const std::string &name) {
    CallbackMap::const_iterator i = callbacks.find(name);
    if (i == callbacks.end()) throw BadColorManagerException(name);
    setColorManager((i->second)());
}

////////////////////////////////////////////////////////////////////////////////

/** \param _f new Function to manage    */
void xyz2RGBColorManager::setFunction(Function *_f) {
    col.clear();
    ColorManager::setFunction(_f);
}

void xyz2RGBColorManager::calibrateColor(const VecMath::Vector<4> &x,
                                         const Color &_col) {
    col.insert(std::make_pair(x, _col));
}

/// Find the color of a given point
/** If the point is not stored in the map of already defined points, calculate
 *  its color by averaging over the nearest neighboring points and store its
 *  value for future use
 *  @param x four-dimensional coordinate for which the color is sought        */
Color xyz2RGBColorManager::getColor(const VecMath::Vector<4> &x) {
    if (!col.count(x)) col[x] = computeColorFromNeighbors(x);
    return col[x];
}

std::string xyz2RGBColorManager::getContents() {
    std::ostringstream o;
    for (colormap::iterator i = col.begin(); i != col.end(); ++i) {
        o << i->first << " -> " << i->second.operator std::string()
          << std::endl;
    }
    return o.str();
}

/// Interpolate the color of a point from the colors of its neighbors
/** The RGBA values are interpolated from a list of five neighboring points,
 *  because in four dimensions you need five points to enclose a given point.
 *
 *  This gives 10 values:
 *      \f{eqnarray*}{
 *          R^1 & = & (R_2-R_1)*\frac{x-x_1}{x_2-x_1}+R_1 \\
 *          R^2 & = & (R_3-R_1)*\frac{x-x_1}{x_3-x_1}+R_1 \\
 *          \ldots  \\
 *          R^{10} & = & (R_5-R_4)*\frac{x-x_4}{x_5-x_4}+R_4
 *     \f}
 *  The interpolated \f$ R \f$
 *  value is the average of the temporary \f$ R \f$ values.
 *
 *  Analogous for \f$ G \f$ in \f$ y \f$, \f$ B \f$ in \f$ z \f$, and
 *  \f$ \alpha \f$ in \f$ w \f$.
 *  @param x four-dimensional coordinate for which the color is sought        */
Color xyz2RGBColorManager::computeColorFromNeighbors(
        const VecMath::Vector<4> &x) {
    std::pair<vector<Vector<4> >, vector<double> >
        pointsndistances = findClosestPoints(x, 5);
    vector<Vector<4> > points = pointsndistances.first;
    vector<double> distances = pointsndistances.second;
    vector<Color> RGBA;

    for (unsigned i = 0; i < points.size()-1; i++) {
        for (unsigned j = i+1; j < points.size(); j++) {
            Vector<4> x1 = points[i], x2 = points[j],
                      d = (x-x1)/(x2-x1);
            Color c1 = col[x1], c2 = col[x2],
                  scale = d;

            RGBA.push_back(scale*(c2-c1)+c1);
        }
    }

    return averageColors(RGBA);
}

/// Find the average RGBA values from the list of Colors supplied
Color xyz2RGBColorManager::averageColors(const vector<Color> &RGBA) {
    Color tmp;
    for (vector<Color>::const_iterator i = RGBA.begin(); i != RGBA.end(); ++i)
        tmp += *i;
    return tmp*(1./RGBA.size());
}

/// find the closest points in the map of colors
/** @param x point whose neighbors are wanted
 *  @param num number of neighboring points
 *  @return two vectors containing the closest points and their distances to x*/
std::pair<vector<Vector<4> >, vector<double> >
        xyz2RGBColorManager::findClosestPoints(const VecMath::Vector<4> &x,
                                               unsigned num) {
    vector<Vector<4> > points;
    vector<double> distances;

    for (colormap::iterator i = col.begin(); i != col.end(); ++i) {
        double distance = (x-i->first).sqnorm();
        if (distances.empty()) {                            //  first point
            distances.push_back(distance);
            points.push_back(i->first);
            continue;
        }
        //  current point is further away than the num closest ones, shove it
        if (distance > distances.back() && distances.size() >= num) continue;

        bool already_inserted = false;
        for (unsigned j = 0; j < min((unsigned)distances.size(), num); j++) {
            if (distances[j] > distance) {
                distances.insert(distances.begin()+j, 1, distance);
                points.insert(points.begin()+j, 1, i->first);
                already_inserted = true;
            }
        }
        if (!already_inserted) {
            distances.push_back(distance);
            points.push_back(i->first);
        }
    }
    //  make a pair to return both vectors, truncated to the first num elements
    return std::make_pair(
        vector<Vector<4> >(points.begin(), points.begin()+num),
        vector<double>(distances.begin(), distances.begin()+num));
}

void xyz2RGBColorManager::depthCueColor(double wmax, double wmin, double w,
                                        const VecMath::Vector<4> &x) {
    float DepthCueFactor = (wmax-w)/(wmax-wmin)*(1.0-getoffset4Ddepthcue());
//                            +getoffset4Ddepthcue();
    col[x] = ((col[x]+(-getoffset4Ddepthcue()))
                        + getoffset4Ddepthcue())*DepthCueFactor;
}

////////////////////////////////////////////////////////////////////////////////

Fastxyz2RGBColorManager::Fastxyz2RGBColorManager():
        ColorManager(),
        _xmin(0), _xmax(0), _ymin(0), _ymax(0), _zmin(0), _zmax (0), _wmin(0), _wmax (0),
        _opacityRange(0.6) { }

/** \param _f Function to manage    */
Fastxyz2RGBColorManager::Fastxyz2RGBColorManager(Function *_f):
        ColorManager(_f),
        _xmin(0), _xmax(0), _ymin(0), _ymax(0), _zmin(0), _zmax (0), _wmin(0), _wmax (0),
        _opacityRange(0.6) { }

/** \param _f new Function to manage    */
void Fastxyz2RGBColorManager::setFunction(Function *_f) {
    _xmin = _xmax = _ymin = _ymax = _zmin = _zmax = _wmin = _wmax = 0;
    ColorManager::setFunction(_f);
}

void Fastxyz2RGBColorManager::calibrateColor(const VecMath::Vector<4> &x,
                                             const Color &) {
    if (x[0] < _xmin) _xmin = x[0];
    if (x[0] > _xmax) _xmax = x[0];
    if (x[1] < _ymin) _ymin = x[1];
    if (x[1] > _ymax) _ymax = x[1];
    if (x[2] < _zmin) _zmin = x[2];
    if (x[2] > _zmax) _zmax = x[2];
    if (x[3] < _wmin) _wmin = x[3];
    if (x[3] > _wmax) _wmax = x[3];
                                             }

/// Find the color of a given point
/** If the point is not stored in the map of already defined points, calculate
 *  its color by averaging over the nearest neighboring points and store its
 *  value for future use
 *  @param x four-dimensional coordinate for which the color is sought        */
Color Fastxyz2RGBColorManager::getColor(const VecMath::Vector<4> &x) {
    float R = (x[0]-_xmin)/(_xmax-_xmin);
    float G = (x[1]-_ymin)/(_ymax-_ymin);
    float B = (x[2]-_zmin)/(_zmax-_zmin);
    float a = 1. - (x[3]-_wmin)/(_wmax-_wmin)*_opacityRange + _opacityRange/2.;
    return Color(R, G, B, a);
}

std::string Fastxyz2RGBColorManager::getContents() {
    std::ostringstream o;
    o << "xmin: " << _xmin << ", " << "xmax: " << _xmax << ", "
      << "ymin: " << _ymin << ", " << "ymax: " << _ymax << ", "
      << "zmin: " << _zmin << ", " << "zmax: " << _zmax
      << std::endl;

    return o.str();
}

/** \todo implement me! */
void Fastxyz2RGBColorManager::depthCueColor(double, double, double,
                                            const VecMath::Vector<4> &) { }

////////////////////////////////////////////////////////////////////////////////

/** \param _f new Function to manage    */
void depth2RGBColorManager::setFunction(Function *_f) {
    _wmin = 1e6; _wmax = -1e6;
    ColorManager::setFunction(_f);
}

void depth2RGBColorManager::calibrateColor(const VecMath::Vector<4> &x,
                                           const Color &) {
    if (x[3] < _wmin) _wmin = x[3];
    if (x[3] > _wmax) _wmax = x[3];
}

/// Find the color of a given point
/** If the point is not stored in the map of already defined points, calculate
 *  its color by computing its w coordinate
 *  @param x four-dimensional coordinate for which the color is sought        */
Color depth2RGBColorManager::getColor(const VecMath::Vector<4> &x) {
    return computeColorFromW((x[3]-_wmin)/(_wmax-_wmin));
}

void depth2RGBColorManager::depthCueColor(double, double, double,
                                        const VecMath::Vector<4> &) { }

std::string depth2RGBColorManager::getContents() {
    std::ostringstream o;
    o << "Wmin: " << _wmin << ", Wmax: " << _wmax << std::endl;
    return o.str();
}

/** \param w w coordinate, normalized to the interval [0..1]
 *  \return Spectral color, ranging from red for 0 to violet for 1
 *  \todo Rethink the transparence algorithm
 */
Color depth2RGBColorManager::computeColorFromW(double w) {
    float R = (w <= 0.2? 1.: (w <= 0.4? 1.-5.*(w-0.2): (w <= 0.8? 0.: 5.*(w-0.8))));
    float G = (w <= 0.2? 5.*w: (w <= 0.6? 1.: (w <= 0.8? 1.-5*(w-0.6): 0.)));
    float B = (w <= 0.4? 0.: (w <= 0.6? 5.*(w-0.4): 1.));

    return Color (R, G, B, (2.*getAlpha()-1.)*w+(1.-getAlpha()));
}

