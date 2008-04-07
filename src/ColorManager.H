#ifndef COLOR_MANAGER_H
#define COLOR_MANAGER_H

#include <vector>

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
/// \ingroup
///

/// Interface for all color managers
/** sets some values common to all color managers, manages the function
 *  belonging to every color manager and has some typedefs for arrays of colors.
 *
 *  But above all, defines the interface every color manager must implement.  */
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
                                    float x, float y, float z) = 0;
        /// Set current OpenGL color at given point
        /** @param x four-dimensional coordinate for which the color is sought*/
        virtual void setColor(const VecMath::Vector<4> &x);
        /// Find the color of a given point
        /** @param x four-dimensional coordinate for which the color is sought*/
        virtual Color getColor(const VecMath::Vector<4> &) = 0;
        /// post-process color at given point to have 4D depth cue
        virtual void depthCueColor(double wmax, double wmin, double w,
                                   float, float, float) = 0;

    protected:
        /// one-dimensional Color array, implemented as a std::vector
        typedef std::vector<Color> colorvec1D;
        /// two-dimensional Color array, implemented as a nested std::vector
        typedef std::vector<colorvec1D> colorvec2D;
        /// three-dimensional Color array, implemented as a nested std::vector
        typedef std::vector<colorvec2D> colorvec3D;
        /// four-dimensional Color array, implemented as a nested std::vector
        typedef std::vector<colorvec3D> colorvec4D;

        const Function* f;      ///< Function for which to manage colors

        /** value to multiply a color with to get its ambient value           */
        double ambientColorModifier;
        /** value to multiply a color with to get its specular value          */
        double specularColorModifier;
        /** minimum value for the specular component of any color             */
        double specularColorMinimum;
        /** shininess value                                                   */
        double SHININESS;
        /** alpha value for transparent display                               */
        double ALPHA;
        /** offset (minimum color) value for 4D depth cue                     */
        double offset4Ddepthcue;
};

/// maps x, y, z in parameter space to R, G, B
class xyz2RGBColorManager: public ColorManager {
    public:
        xyz2RGBColorManager(Function *_f):
            ColorManager(_f) {
            resizeCol();
        }
        virtual ~xyz2RGBColorManager() { }

        virtual void setFunction(Function *_f) {
            f = _f;
            resizeCol();
        }

        virtual void calibrateColor(const Color &_col,
                               float x, float y, float z);
        virtual Color getColor(const VecMath::Vector<4> &x);
        virtual void depthCueColor(double wmax, double wmin, double w,
                                   float, float, float);

    protected:
        void resizeCol();

        colorvec3D col; ///< this is stupid. you could compute values on the fly.
};

/// Plots all points in white
class monochromeColorManager: public ColorManager {
    public:
        monochromeColorManager(Function *_f): ColorManager(_f) { }
        ~monochromeColorManager() { }
        virtual void calibrateColor(const Color &, float, float, float) { }
        virtual Color getColor(const VecMath::Vector<4> &) {
            return Color(1., 1., 1.);
        }
        virtual void depthCueColor(double, double, double,
                                   float, float, float) { }
};

/// Singleton to set the color scheme globally - proxies the color manager
/** \todo implement a map<Function *, ColorManager *> to store one ColorManager
 *  per function - this will probably break the existing interface            */
class ColorManagerManager {
    public:
        /// determine which coloring scheme to use
        void setColorManager(ColorManager *cm) {
            colorManager.reset(cm);
        }
        std::auto_ptr<ColorManager> getColorManager() { return colorManager; }

        /// proxy function for ColorManager::calibrateColor()
        void calibrateColor(const Color &_col, float x, float y, float z) {
            colorManager->calibrateColor(_col, x, y, z);
        }
        /// proxy function for ColorManager::setColor()
        void setColor(const VecMath::Vector<4> &x) { colorManager->setColor(x); }
        /// proxy function for ColorManager::depthCueColor()
        void depthCueColor(double wmax, double wmin, double w,
                           float x, float y, float z) {
            colorManager->depthCueColor(wmax, wmin, w, x, y, z);
        }

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
