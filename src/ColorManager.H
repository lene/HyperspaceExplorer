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

        virtual void calibrateColor(const Color &,
                                    float, float, float) = 0;
        virtual void setColor(const VecMath::Vector<4> &);
        virtual Color getColor(const VecMath::Vector<4> &) = 0;
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

        const Function* f;

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

        colorvec3D col;
};

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

class ColorManagerManager {
    public:
        void setColorManager(ColorManager *cm) {
            colorManager.reset(cm);
        }
        std::auto_ptr<ColorManager> getColorManager() { return colorManager; }

        void calibrateColor(const Color &_col, float x, float y, float z) {
            colorManager->calibrateColor(_col, x, y, z);
        }
        void setColor(const VecMath::Vector<4> &x) { colorManager->setColor(x); }
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
