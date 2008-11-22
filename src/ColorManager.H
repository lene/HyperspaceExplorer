#ifndef COLOR_MANAGER_H
#define COLOR_MANAGER_H

#include <vector>
#include <map>
#include <string>
#include <sstream>

#include "SingletonHolder.H"

#include "Color.H"
#include "Vector.H"
#include "Function.H"

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
        /// Create a ColorManager without a Function
        ColorManager();

        /// Create a ColorManager for a given Function
        ColorManager(const Function *);

        virtual ~ColorManager() { }

        /// Set the function we are managing
        virtual void setFunction(const Function *);

        /// Point (x, y, z) has color col. This may serve for interpolation.
        virtual void calibrateColor(const VecMath::Vector<4> &x,
                                    const Color &col = Color()) = 0;

        /// set the current OpenGL color
        void setRGB(const Color &);

        /// Set current OpenGL color at given point
        virtual void setColor(const VecMath::Vector<4> &);

        /// Find the color of a given point
        /** @param x four-dimensional coordinate for which the color is sought*/
        virtual Color getColor(const VecMath::Vector<4> &x) = 0;

        /// post-process color at given point to have 4D depth cue
        virtual void depthCueColor(double wmax, double wmin, double w,
                                   const VecMath::Vector<4> &x) = 0;

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

        /// \return Offset (minimum color) value for 4D depth cue
        double getoffset4Ddepthcue() { return offset4Ddepthcue; }

        /// \return alpha value for transparent display
        double getAlpha() { return ALPHA; }

    private:
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

/// Singleton to set the color scheme globally - proxies the color manager
/** The object also serves as a Factory for ColorManager s, instantiating a
 *  ColorManager when given a string that describes it. It stores creator
 *  functions for all ColorManager implementations in a std::map indexed by a
 *  string.
 *
 *  It also returns a list of registered ColorManager s, which can be used to
 *  set up a menu to change the ColorManager (for example :-).
 *
 *  \todo implement a map<Function *, ColorManager *> to store one ColorManager
 *  per function - this will probably break the existing interface
 *
 *  \ingroup Coloring                                                         */
class ColorManagerManager {
    public:
        /// Thrown by createColorManager() when \p name does not map to a ColorManager.
        struct BadColorManagerException: public std::runtime_error {
            /// Create a BadFunctionException
            BadColorManagerException(const std::string &);
        };

        /// callback function generating a ColorManager and returning a ColorManager*
        typedef ColorManager *(*CreateColMgrCallback)();

        /// determine which coloring scheme to use
        void setColorManager(ColorManager *cm) { colorManager.reset(cm); }

        /// proxy function for ColorManager::setFunction()
        void setFunction(const Function *_f) { colorManager->setFunction(_f); }

        /// proxy function for ColorManager::calibrateColor()
        void calibrateColor(const VecMath::Vector<4> &, const Color & = Color());

        /// proxy function for ColorManager::setColor()
        void setColor(const VecMath::Vector<4> &x) { colorManager->setColor(x); }

        /// proxy function for ColorManager::depthCueColor()
        void depthCueColor(double wmax, double wmin, double w,
                           const VecMath::Vector<4> &x);

        /// proxy function for ColorManager::setRGB()
        void setRGB(const Color &_col) { colorManager->setRGB(_col); }

        /// debugging output
        std::string getContents() { return colorManager->getContents(); }

        /// Register a ColorManager class with a name, so we can instantiate it
        bool registerColorManager(const std::string &, CreateColMgrCallback);

        /// Unregister a ColorManager with the given name
        bool unregisterColorManager(const std::string &);

        /// \todo implement me!
        std::vector<std::string> getRegisteredColorManagers();

        /// Set the ColorManager to a class registered by name
        void setColorManager(const std::string &);

    private:
        /// stores a creator function with a string containing the class name
        typedef std::map<std::string, CreateColMgrCallback> CallbackMap;

        /** disabled default constructor */
        ColorManagerManager(): callbacks() { }
        /** disabled copy constructor */
        ColorManagerManager(const ColorManagerManager &);
        /** disabled assignment operator */
        ColorManagerManager &operator=(const ColorManagerManager &);
        /** disabled destructor */
        ~ColorManagerManager() { }

        std::auto_ptr<ColorManager> colorManager;   ///< The proxied ColorManager

        CallbackMap callbacks;              ///< Stores the ColorManager creators

        /// Lets Loki::SingletonHolder instantiate a ColorManagerManager
        friend class Loki::CreateUsingNew<ColorManagerManager>;

};

typedef Loki::SingletonHolder<ColorManagerManager> ColMgrMgr;


/// maps x, y, z in parameter space to R, G, B
/** \ingroup Coloring                                                         */
class xyz2RGBColorManager: public ColorManager {
    public:
        xyz2RGBColorManager(): ColorManager(), col(colormap()) { }

        /// Given a Function to manage, construct a xyz2RGBColorManager
        /** \param _f Function to manage    */
        xyz2RGBColorManager(const Function *_f): ColorManager(_f), col(colormap()) { }

        virtual ~xyz2RGBColorManager() { }

        /// set the managed Function
        virtual void setFunction(const Function *);

        virtual void calibrateColor(const VecMath::Vector<4> &x,
                                    const Color &_col = Color());

        virtual Color getColor(const VecMath::Vector<4> &x);

        virtual void depthCueColor(double wmax, double wmin, double w,
                                   const VecMath::Vector<4> &);

        /// debugging output
        virtual std::string getContents();

    private:
        Color computeColorFromNeighbors(const VecMath::Vector<4> &x);
        std::pair<std::vector<VecMath::Vector<4> >, std::vector<double> >
                findClosestPoints(const VecMath::Vector<4> &, unsigned = 5);
        Color averageColors(const std::vector<Color> &);

        colormap col; ///< Here the colors for defined points re stored
};

namespace {
    ColorManager *createXYZ2RGB() { return new xyz2RGBColorManager(); }
    const bool registeredC0 =
            ColMgrMgr::Instance().registerColorManager("XYZ to RGB", createXYZ2RGB);
}

/// maps w coordinate to R, G, B
/** \ingroup Coloring                                                         */
class depth2RGBColorManager: public ColorManager {
    public:
        depth2RGBColorManager(): ColorManager(), _wmin(1e6), _wmax(-1e6) { }

        /// Given a Function to manage, construct a depth2RGBColorManager
        /** \param _f Function to manage    */
        depth2RGBColorManager(const Function *_f):
            ColorManager(_f), _wmin(1e6), _wmax(-1e6) { }

        virtual ~depth2RGBColorManager() { }

        /// set the managed Function
        virtual void setFunction(const Function *);

        virtual void calibrateColor(const VecMath::Vector<4> &,
                                    const Color & = Color());

        virtual Color getColor(const VecMath::Vector<4> &);

        virtual void depthCueColor(double wmax, double wmin, double w,
                                   const VecMath::Vector<4> &);

        /// debugging output
        virtual std::string getContents();

    private:
        /// Compute a spectral color for the normalized w coordinate
        Color computeColorFromW(double);

        double _wmin;   ///< Minimum w value of the managed Function
        double _wmax;   ///< Maximum w value of the managed Function
};

namespace {
    ColorManager *createDepth2RGB() { return new depth2RGBColorManager(); }
    const bool registeredC1 =
            ColMgrMgr::Instance().registerColorManager("W coordinate to RGB",
                                                       createDepth2RGB);
}

/// Plots all points in white
/** \ingroup Coloring                                                         */
class monochromeColorManager: public ColorManager {
    public:
        monochromeColorManager(): ColorManager() { }

        /// Given a Function to manage, construct a monochromeColorManager
        /** \param _f Function to manage    */
        monochromeColorManager(const Function *_f): ColorManager(_f) { }

        virtual ~monochromeColorManager() { }

        virtual void calibrateColor(const VecMath::Vector<4> &,
                                    const Color & = Color()) { }

        virtual Color getColor(const VecMath::Vector<4> &) {
            return Color(1., 1., 1.);
        }

        virtual void depthCueColor(double, double, double,
                                   const VecMath::Vector<4> &) { }
};

namespace {
    ColorManager *createMonochrome() { return new monochromeColorManager(); }
    const bool registeredC2 =
            ColMgrMgr::Instance().registerColorManager("Monochrome",
                                                       createMonochrome);
}

#endif
