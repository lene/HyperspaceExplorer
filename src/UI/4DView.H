
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#ifndef VIEW_H
#define VIEW_H

#include <QTimer>

#include "ValuesDialogImpl.H"
#include "XQGLWidget.H"

class QPaintEvent;
class QStatusBar;

class C4DView;
class Menu4D;
class Function;

class CustomFunction;
class CustomPolarFunction;
class CustomSurface;
class CustomComplexFunction;

class Fr3r;
class GravitationPotential;
class Fr3rSin;
class Fr3rExp;
class PolarSin;
class PolarSin2;
class PolarR;
class Surface1;
class Horizon;
class Torus3;
class z2;
class z3;
class zA;
class ez;
class emz2;
class zm1;
class zm2;
class sqrtz;
class lnz;
class sinz;
class cosz;
class sinhz;
class coshz;
class tanz;
class Hypersphere;
class Torus1;
class Torus2;


/** class C4DView:
 *  displays and manipulates four-dimensional @href Function in a QGLWidget   */
class C4DView : public XQGLWidget {

    /** class CustomFunctionSlot
     *  class template to outsource redundant code for the generation of
     *  customized functions in a slot called by QActions from the QMenu      */
    template<class function> class CustomFunctionSlot {
        public:
            static void createCustomFunction(C4DView *view);
            static void createCustomSurface(C4DView *view);
    };

    /** class FunctionSlot
     *  class template to outsource redundant code for the generation of
     *  functions in a slot called by QActions from the QMenu                 */
    template<class function> class FunctionSlot {
    //  Q_OBJECT
        public:
            static void createFunction(C4DView *view);
            static void createSurface(C4DView *view);
            static void createObject(C4DView *view);
    };

    Q_OBJECT

    public:
        C4DView(QWidget * = 0);
        virtual ~C4DView();

        void SetWireframe (bool wire) { DisplayPolygons = !wire; }
        bool GetWireframe (void) { return !DisplayPolygons; }
        void SetLighting (bool light) { Lighting = light; }
        bool GetLighting (void) { return Lighting; }
        void SetDepthCue (bool on) {
            SetupDepthCue (on);
            OnPaint ();
        }
        void SetRotation (double rx, double ry, double rz) {
            m_rotX = rx; m_rotY = ry; m_rotZ = rz;
        }

        virtual void paintEvent (QPaintEvent *);
        virtual void initializeGL (void);

        double Size ();

        void RenderScene (unsigned Frame);

        void Transform (double Rxy, double Rxz, double Rxw,
                        double Ryz, double Ryw, double Rzw,
                        double Tx, double Ty, double Tz, double Tw);
        void Transform (void) { Transform (0, 0, 0, 0, 0, 0,  0, 0, 0, 0); }

        void Redraw ();

        double Benchmark4D (int, double, double, double, bool = true);
        double Benchmark3D (int, double, double, double, bool = true);

        bool getColors() const { return colors; }
        bool getShade() const { return shade; }
        bool getFog() const { return fog; }
        bool getLight() const { return light; }
        bool getTransparent() const { return transparent; }
        bool getDisplayCoordinates() const { return DisplayCoordinates; }
        bool getRenderToPixmap() const { return RenderToPixmap; }
        bool getDisplayPolygons() const { return DisplayPolygons; }
        Menu4D *getMenu() const { return menu; }

    public slots:
        void ApplyChanges ();

        void ParametersChanged (double tmin, double tmax, unsigned tsteps,
                                double umin, double umax, unsigned usteps,
                                double vmin, double vmax, unsigned vsteps,
                                double a, double b, double c, double d,
                                QString &func);

    protected:

        Menu4D *menu;

        void Project ();
        void Draw ();
        void PreRedraw ();
        QPixmap makePixmap ();

        GLint ObjectList, CoordinateCross;

        void DrawCoordinates (void);
        void SetupDepthCue (bool);

        double Tx,  Ty,  Tz,  Tw,
               Rxy, Rxz, Rxw, Ryz, Ryw, Rzw;

        GLdouble m_rotX,   m_rotY,
                 m_transX, m_transY,
                 m_camZ, m_rotZ;

        QPoint m_LeftDownPos, m_MidDownPos, m_RightDownPos;

        bool AntiAlias, DisplayPolygons, Lighting,
             DepthCue3D, DepthCue4D;

        bool DisplayCoordinates;

        bool Animated,
             TakingSpinValues;

        bool RenderToPixmap, CurrentlyRendering;

        void StartAnimation ();
        void StopAnimation ();
        void RandomAnimation();
        QTimer *AnimationTimer, *AnimateRandomTimer;

        ValuesDialogImpl *Values;

#       ifdef USE_AUTO_PTR
            auto_ptr<Function> F;
#       else
            Function *F;
#       endif

        QString ObjectName;

        double dxy, dxz, dxw, dyz, dyw, dzw,
               dx, dy, dz;

        unsigned animation_fps;

        VecMath::Vector<4> ***Data;

        VecMath::Vector<3> ***Xscr;
        VecMath::Vector<4> ***Xtrans;
        VecMath::Vector<3> *XscrChunk;
        VecMath::Vector<4> *XtransChunk;

        float ***R, ***G, ***B;
        float *RGBChunk;

        unsigned tsteps, usteps, vsteps;
        double CamW, ScrW;

        VecMath::Vector<4> **Cross, **CrossTrans;
        VecMath::Vector<3> **CrossScr;

        void UpdateStatus (QString = "");

        void AssignValues (const QString &Title = 0,
                           const QString &Parameter1 = 0,  const QString &Parameter2 = 0,
                           const QString &Parameter3 = 0,  const QString &Parameter4 = 0);

        void OnPaint();

        virtual void resizeEvent ( QResizeEvent * );
        virtual void mousePressEvent (QMouseEvent *);
        virtual void mouseReleaseEvent ( QMouseEvent *);
        virtual void mouseMoveEvent(QMouseEvent *);
        virtual void mouseDoubleClickEvent ( QMouseEvent *);

        Q3PopupMenu *functions, *animation;
        int linesID, crossID, hyperfogID, pixmapID;
        int funcID[32];
        void UpdateFunctionMenu (int);
        void InitCross();

        unsigned animationMaxFrames,
                 animationFrame;
        QString animationDirectory;
        QString animationPrefix;

        void writeFrame();

    protected slots:
        void OnTimer();
        void AnimationSettings();

    public slots:
        //  menu items
        void Wireframe();
        void Coordinates();
        void HyperFog();
        void Light();
        void Colors ();
        void Fog ();
        void Transparent ();
        void Shade ();
        void Benchmark();
        void RenderToImages();

        void FunctionFr3r();
        void FunctionHypersphere();
        void FunctionTorus1();
        void FunctionTorus2();
        void FR3R();
        void GravPotential();
        void SinR();
        void ExpR();
        void Sin();
        void Sin2();
        void FunctionR();
        void ObjectHypercube();
        void ObjectHyperpyramid();
        void ObjectHypersponge();
        void ObjectGasket();
        void Surface_1();
        void SurfaceHorizon();
        void SurfaceTorus3();
        void ComplexZ2();
        void ComplexZ3();
        void ComplexZA();
        void ComplexEZ();
        void ComplexEMZ2();
        void ComplexZM1();
        void ComplexZM2();
        void ComplexSqrtZ();
        void ComplexLnZ();
        void ComplexSinZ();
        void ComplexCosZ();
        void ComplexSinhZ();
        void ComplexCoshZ();
        void ComplexTanZ();
        void customFunction();
        void customPolarFunction();
        void customComplexFunction();
        void customSurface();

        friend class FunctionSlot<Fr3r>;

        friend class FunctionSlot<Hypersphere>;
        friend class FunctionSlot<Torus1>;
        friend class FunctionSlot<Torus2>;
        friend class FunctionSlot<GravitationPotential>;
        friend class FunctionSlot<Fr3rSin>;
        friend class FunctionSlot<Fr3rExp>;
        friend class FunctionSlot<PolarSin>;
        friend class FunctionSlot<PolarSin2>;
        friend class FunctionSlot<PolarR>;
        friend class FunctionSlot<Surface1>;
        friend class FunctionSlot<Horizon>;
        friend class FunctionSlot<Torus3>;
        friend class FunctionSlot<z2>;
        friend class FunctionSlot<z3>;
        friend class FunctionSlot<zA>;
        friend class FunctionSlot<ez>;
        friend class FunctionSlot<emz2>;
        friend class FunctionSlot<zm1>;
        friend class FunctionSlot<zm2>;
        friend class FunctionSlot<sqrtz>;
        friend class FunctionSlot<lnz>;
        friend class FunctionSlot<sinz>;
        friend class FunctionSlot<cosz>;
        friend class FunctionSlot<sinhz>;
        friend class FunctionSlot<coshz>;
        friend class FunctionSlot<tanz>;
        friend class CustomFunctionSlot<CustomFunction>;
        friend class CustomFunctionSlot<CustomPolarFunction>;
        friend class CustomFunctionSlot<CustomComplexFunction>;
        friend class CustomFunctionSlot<CustomSurface>;

};

#endif // !defined(4DVIEW)
