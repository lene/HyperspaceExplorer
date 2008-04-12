#ifndef COLOR_MANAGER_H
#define COLOR_MANAGER_H

#include <vector>
#include <map>
#include <string>
#include <sstream>

#include "SingletonHolder.H"

#include "Color.H"
#include "Vector.H"

class Function;

///
/// C++ Interface: ColorManager
///
/// Description:
///
///
/// @author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
/// \defgroup Coloring Functionality for defining color schemes
/// \ingroup UIGroup

/// Interface for all color managers
/** sets some values common to all color managers, manages the function
 *  belonging to every color manager and has some typedefs for arrays of colors.
 *
 *  But above all, defines the interface every color manager must implement.
 *  \ingroup Coloring                                                         */
class ColorManager {
    public:
        ColorManager(const Function *_f):
            f(_f),
            ambientColorModifier(0.5), specularColorModifier(2.),
            specularColorMinimum(0.5), SHININESS(32.), ALPHA(0.9),
            offset4Ddepthcue(0.1) { }

        virtual ~ColorManager() { }

        virtual void setFunction(const Function *_f) {
            f = _f;
        }

        /// Point (x, y, z) has color col. This may serve for interpolation.
        virtual void calibrateColor(const Color &col,
                                    const VecMath::Vector<4> &x) = 0;
        /// Set current OpenGL color at given point
        /** @param x four-dimensional coordinate for which the color is sought*/
        virtual void setColor(const VecMath::Vector<4> &x);
        /// Find the color of a given point
        /** @param x four-dimensional coordinate for which the color is sought*/
        virtual Color getColor(const VecMath::Vector<4> &) = 0;
        /// post-process color at given point to have 4D depth cue
        virtual void depthCueColor(double wmax, double wmin, double w,
                                   const VecMath::Vector<4> &x) = 0;
        void setRGB(const Color &rgb);

        /// debugging output
        virtual std::string getContents() { return ""; }

    protected:
        /// one-dimensional Color array, implemented as a std::vector
        typedef std::vector<Color> colorvec1D;
        /// two-dimensional Color array, implemented as a nested std::vector
        typedef std::vector<colorvec1D> colorvec2D;
        /// three-dimensional Color array, implemented as a nested std::vector
        typedef std::vector<colorvec2D> colorvec3D;
        /// four-dimensional Color array, implemented as a nested std::vector
        typedef std::vector<colorvec3D> colorvec4D;
        /// map of Colors, indexed by 4D points
        typedef std::map<VecMath::Vector<4>, Color> colormap;

        const Function* f;      ///< Function for which to manage colors

        /// value to multiply a color with to get its ambient value
        double ambientColorModifier;
        /// value to multiply a color with to get its specular value
        double specularColorModifier;
        /// minimum value for the specular component of any color
        double specularColorMinimum;
        /// shininess value
        double SHININESS;
        /// alpha value for transparent display
        double ALPHA;
        /// offset (minimum color) value for 4D depth cue
        double offset4Ddepthcue;
};

/// maps x, y, z in parameter space to R, G, B
/** \ingroup Coloring                                                         */
class xyz2RGBColorManager: public ColorManager {
    public:
        xyz2RGBColorManager(Function *_f):
            ColorManager(_f), col(colormap()) { }
        virtual ~xyz2RGBColorManager() { }

        virtual void setFunction(Function *_f) {
            f = _f;
            col.clear();
        }

        virtual void calibrateColor(const Color &_col,
                                    const VecMath::Vector<4> &x);
        virtual Color getColor(const VecMath::Vector<4> &x);
        virtual void depthCueColor(double wmax, double wmin, double w,
                                   const VecMath::Vector<4> &);
        /// debugging output
        virtual std::string getContents() {
            std::ostringstream o;
            for (colormap::iterator i = col.begin(); i != col.end(); ++i) {
                o << i->first << " -> " << i->second.operator std::string()
                  << std::endl;
            }
            return o.str();
        }

    protected:
        Color computeColorFromNeighbors(const VecMath::Vector<4> &x);
        std::pair<std::vector<VecMath::Vector<4> >, std::vector<double> >
                findClosestPoints(const VecMath::Vector<4> &, unsigned = 5);
        Color averageColors(const std::vector<Color> &);

        colormap col; ///<
};

/// Plots all points in white
/** \ingroup Coloring                                                         */
class monochromeColorManager: public ColorManager {
    public:
        monochromeColorManager(Function *_f): ColorManager(_f) { }
        ~monochromeColorManager() { }
        virtual void calibrateColor(const Color &,
                                    const VecMath::Vector<4> &) { }
        virtual Color getColor(const VecMath::Vector<4> &) {
            return Color(1., 1., 1.);
        }
        virtual void depthCueColor(double, double, double,
                                   const VecMath::Vector<4> &) { }
};

/// Singleton to set the color scheme globally - proxies the color manager
/** \todo implement a map<Function *, ColorManager *> to store one ColorManager
 *  per function - this will probably break the existing interface
 *  \ingroup Coloring                                                         */
class ColorManagerManager {
    public:
        /// determine which coloring scheme to use
        void setColorManager(ColorManager *cm) {
            colorManager.reset(cm);
        }
        /// proxy function for ColorManager::setFunction()
        void setFunction(Function *_f) { colorManager->setFunction(_f); }
        /// proxy function for ColorManager::calibrateColor()
        void calibrateColor(const Color &_col, const VecMath::Vector<4> &x) {
            colorManager->calibrateColor(_col, x);
        }
        /// proxy function for ColorManager::setColor()
        void setColor(const VecMath::Vector<4> &x) { colorManager->setColor(x); }
        /// proxy function for ColorManager::depthCueColor()
        void depthCueColor(double wmax, double wmin, double w,
                           const VecMath::Vector<4> &x) {
            colorManager->depthCueColor(wmax, wmin, w, x);
        }
        void setRGB(const Color &_col) { colorManager->setRGB(_col); }
        /// debugging output
        std::string getContents() { return colorManager->getContents(); }

    private:
        /** disabled default constructor */
        ColorManagerManager() { }
        /** disabled copy constructor */
        ColorManagerManager(const ColorManagerManager &);
        /** disabled assignment operator */
        ColorManagerManager &operator=(const ColorManagerManager &);
        /** disabled destructor */
        ~ColorManagerManager() { }

        std::auto_ptr<ColorManager> colorManager;

        friend class Loki::CreateUsingNew<ColorManagerManager>;

};

typedef Loki::SingletonHolder<ColorManagerManager> ColMgrMgr;
#endif
