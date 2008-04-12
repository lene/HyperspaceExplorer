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

using VecMath::Vector;
using std::vector;

/** set the current OpenGL color
 *  uses HARDCODED simple algorithm to set ambient and specular values for a
 *  specific color: if halves resp. dobles them, clipping at 1.0
 *  @todo make the agorithm which computes the ambient and specular values
 *        variable
 *  @param rgb color value to be set                                          */
void ColorManager::setColor(const Vector<4> &x) {
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
                                         const Vector<4> &x) {
    col.insert(std::make_pair(x, _col));
}

Color xyz2RGBColorManager::getColor(const Vector<4> &x) {
    if (!col.count(x)) col[x] = computeColorFromNeighbors(x);
    return col[x];
}

Color xyz2RGBColorManager::computeColorFromNeighbors(const Vector<4> &x) {
    //  maintain a list of the five closest points and their distances to x
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

Color xyz2RGBColorManager::averageColors(const vector<Color> &RGBA) {
    Color tmp;
    for (vector<Color>::const_iterator i = RGBA.begin(); i != RGBA.end(); ++i)
        tmp += *i;
    return tmp*(1./RGBA.size());
}

template <typename T> T min(T a, T b) { return (a < b? a: b); }

/// find the closest points in the map of colors
/** @param x point whose neighbors are wanted
 *  @param num number of neighboring points
 *  @return two vectors containing the closest points and their distances to x*/
std::pair<vector<Vector<4> >, vector<double> >
        xyz2RGBColorManager::findClosestPoints(const Vector<4> &x,
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
                //  insert distance in current place in distances and
                //  i->first in current place in points
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
                                        const Vector<4> &x) {
    float DepthCueFactor = (wmax-w)/(wmax-wmin)*(1.0-offset4Ddepthcue)
                            +offset4Ddepthcue;
    col[x] = ((col[x]+(-offset4Ddepthcue))
                        + offset4Ddepthcue)*DepthCueFactor;
}
