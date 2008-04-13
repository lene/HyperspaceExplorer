
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//      author:	      helge preuss (scout@hyperspace-travel.de)
//      license:      GPL (see License.txt)

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
class RealFunction;
class Surface;

class CustomFunction;
class CustomPolarFunction;
class CustomSurface;
class CustomComplexFunction;

/// \defgroup UIGroup User Interface
/// \defgroup UIHelpers Helper classes for User Interface classes
/// \ingroup UIGroup

/// Abstract base class for a factory creating Function's
/** Separate classes are needed for Functions and Surfaces, because their
 *  constructors differ.
 *  \ingroup UIHelpers                                                        */
class RealFunctionFactory {
    public:
        virtual ~RealFunctionFactory() { }
        virtual RealFunction *createFunction(C4DView *) = 0;
};

/// Abstract base class for a factory creating Surface's
/** Separate classes are needed for Functions and Surfaces, because their
 *  constructors differ.
 *  \ingroup UIHelpers                                                        */
class SurfaceFactory {
    public:
        virtual ~SurfaceFactory() { }
        virtual Surface *createSurface(C4DView *) = 0;
};

/// Displays and manipulates four-dimensional Functions in a QGLWidget
/** This class is much too fat and will be split into parts wherever possible
 *  \ingroup UIGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class C4DView : public XQGLWidget {

    public:
        /// Class template implementation for a factory creating Function's
        /** The type of the Function to be created by the factory method of this
         *  class is passed as a template parameter.
         *
         *  Separate classes are needed for Functions and Surfaces, because
         *  their constructors differ.
         *  \ingroup UIHelpers                                                */
        template <typename function>
            class TemplatedRealFunctionFactory: public RealFunctionFactory {
                public:
                    virtual RealFunction *createFunction(C4DView *);
            };

        /// Class template implementation for a factory creating Surface's
        /** The type of the Surface to be created by the factory method of this
         *  class is passed as a template parameter.
         *
         *  Separate classes are needed for Functions and Surfaces, because
         *  their constructors differ.
         *  \ingroup UIHelpers                                                */
        template <typename function>
            class TemplatedSurfaceFactory: public SurfaceFactory {
                public:
                    virtual Surface *createSurface(C4DView *);
            };

    protected:
        /// Class template to outsource redundant code for customized functions
        /** Redundant code for the generation of customized functions is moved
         *  to a slot called by QActions from the QMenu
         *  @param function the Function to be created in the slot
         *  \ingroup UIHelpers                                                 */
        template<class function> class CustomFunctionSlot {
            public:
                static void createCustomFunction(C4DView *view);
                static void createCustomSurface(C4DView *view);
        };

    Q_OBJECT

    public slots:
        //  menu items, must be public because called from Menu4D
        void Wireframe();
        void Coordinates();
        void HyperFog();
        void Light();
        void Colors();
        void Fog();
        void Transparent();
        void Shade();
        void Benchmark();
        void RenderToImages();

        void ObjectHypercube();
        void ObjectHyperpyramid();
        void ObjectHypersponge();
        void ObjectGasket();
        void customFunction();
        void customPolarFunction();
        void customSurface();
        void customComplexFunction();

    public:
        C4DView(QWidget * = 0);
        virtual ~C4DView();

        /// @param wire if true, displays wireframe model; else solid
        void setWireframe (bool wire) { DisplayPolygons = !wire; }
        /// @return whether to display the 4D coordinate cross or not
        bool getDisplayCoordinates() const { return DisplayCoordinates; }
        /// @return whether to save the rendered images to an image file
        bool getRenderToPixmap() const { return RenderToPixmap; }
        /// @return whether to draw the objects' surfaces or only the edges
        bool getDisplayPolygons() const { return DisplayPolygons; }

        double Benchmark3D(int, double, double, double, bool = true);
        double Benchmark4D(int, double, double, double, bool = true);

    protected slots:
        void OnTimer();
        void AnimationSettings();
        void ApplyChanges();

    protected:
        void Transform(double Rxy, double Rxz, double Rxw,
                       double Ryz, double Ryw, double Rzw,
                       double Tx, double Ty, double Tz, double Tw);
        /// Overloaded function executing the transform to the default state
        void Transform() { Transform (0, 0, 0, 0, 0, 0,  0, 0, 0, 0); }
        void Project();
        void Draw();

        void PreRedraw();
        void Redraw();
        void RenderScene(unsigned Frame);
        void OnPaint();

        void InitCross();
        void SetupDepthCue(bool);
        void DrawCoordinates(void);

        void StartAnimation();
        void StopAnimation();
        void RandomAnimation();

        QPixmap makePixmap();
        void writeFrame();

        void checkAnglesForOverflow();
        void UpdateStatus(QString = "");

        void AssignValues(const std::auto_ptr<Function> &);

        double Size();

        // event handlers reimplemented from QWidget or QGLWidget
        virtual void mouseMoveEvent(QMouseEvent *);
        virtual void mousePressEvent(QMouseEvent *);
        virtual void mouseReleaseEvent( QMouseEvent *);
        virtual void mouseDoubleClickEvent( QMouseEvent *);
        virtual void paintEvent(QPaintEvent *);
        virtual void resizeEvent( QResizeEvent * );
        virtual void initializeGL(void);

    private:                                    //  member variables
        std::auto_ptr<Function> F;  ///< the Function object currently displayed

        double Tx,  ///< X coordinate for the 4D translation of the object
               Ty,  ///< Y coordinate for the 4D translation of the object
               Tz,  ///< Z coordinate for the 4D translation of the object
               Tw;  ///< W coordinate for the 4D translation of the object
        double Rxy, ///< XY angle for the 4D rotation of the object
               Rxz, ///< XZ angle for the 4D rotation of the object
               Rxw, ///< XW angle for the 4D rotation of the object
               Ryz, ///< YZ angle for the 4D rotation of the object
               Ryw, ///< YW angle for the 4D rotation of the object
               Rzw; ///< ZW angle for the 4D rotation of the object

        GLdouble m_rotX;    ///< rotation in X
        GLdouble m_rotY;    ///< rotation in Y
        GLdouble m_rotZ;    ///< rotation in Z
        GLdouble m_transX;  ///< translation in X
        GLdouble m_transY;  ///< translation in Y
        GLdouble m_camZ;    ///< Z coordinate of camera (distance from object)

        double CamW;        ///< W coordinate of the camera
        double ScrW;        ///< W coordinate of the screen

        /// if true, draw lines antialiased, surfaces transparent
        bool AntiAlias;
        bool DisplayPolygons;       ///< if true, draw solid surfaces
        bool Lighting;              ///< if true, use lights in rendering
        bool DepthCue3D;            ///< if true, use depth cue
        bool DepthCue4D;            ///< if true, use depth cue in 4D

        bool DisplayCoordinates;    ///< if true, show the 4D coordinate cross
        bool RenderToPixmap;        ///< if true, save images

        QString animationDirectory; ///< where to save an animation's frames
        QString animationPrefix;    ///< prefix of animation frame filenames
        unsigned animationMaxFrames;    ///< limit for saved animation frames
        const unsigned animation_fps;   ///< frames per second for animations

        GLint ObjectList;       ///< a GLList for the display of the object
        GLint CoordinateCross;  ///< a GLList for the display of the coordinates

        bool Animated;              ///< if true, image is currently animated
        /// true while mouse button pressed & mouse moved to take movement speed
        bool TakingSpinValues;
        unsigned animationFrame;    ///< current frame in animation

        bool CurrentlyRendering;    ///< if true, currently rendering an image

        QPoint m_LeftDownPos,       ///< position where the LMB press started
               m_MidDownPos,        ///< position where the MMB press started
               m_RightDownPos;      ///< position where the RMB press started

        /// times out every X ms to draw new animation frame
        QTimer *AnimationTimer;
        /// times out to change rotation direction
        QTimer *AnimateRandomTimer;

        /// dialog to enter function parameters
        ValuesDialogImpl *Values;

        double dxy,     ///< delta values in xy rotation angle - for animations
               dxz,     ///< delta values in xz rotation angle - for animations
               dxw,     ///< delta values in xw rotation angle - for animations
               dyz,     ///< delta values in yz rotation angle - for animations
               dyw,     ///< delta values in yw rotation angle - for animations
               dzw,     ///< delta values in zw rotation angle - for animations
               dx,      ///< delta values in x translation - for animations
               dy,      ///< delta values in y translation - for animations
               dz;      ///< delta values in z translation - for animations

        /// endpoints of the lines constituting the 4D coordinate cross
        std::vector<std::vector<VecMath::Vector<4> > > Cross;
        /// endpoints of the lines constituting the transformed 4D coordinates
        std::vector<std::vector<VecMath::Vector<4> > > CrossTrans;
        /// endpoints of the lines constituting the projected 4D coordinates
        std::vector<std::vector<VecMath::Vector<3> > > CrossScr;

        Menu4D *menu;               ///< the popup menu

    friend class CustomFunctionSlot<CustomFunction>;
    friend class CustomFunctionSlot<CustomPolarFunction>;
    friend class CustomFunctionSlot<CustomComplexFunction>;
    friend class CustomFunctionSlot<CustomSurface>;

    friend class FunctionSlotHelper;
    friend class SurfaceSlotHelper;
};

#include "CustomFunctionSlot.impl.H"
#include "TemplatedFunctionFactory.impl.H"

#endif // !defined(4DVIEW)
