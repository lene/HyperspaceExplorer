
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//      author:	      helge preuss (scout@hyperspace-travel.de)
//      license:      GPL (see License.txt)

#ifndef VIEW_H
#define VIEW_H

#include <QTimer>
#include <QGLWidget>

#include "ValuesDialogImpl.H"

class QPaintEvent;
class QStatusBar;

class C4DView;
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
/** Defines the interface a TemplatedRealFunctionFactory<> implements
 *
 *  Separate classes are needed for Functions and Surfaces, because their
 *  constructors differ.
 *  \ingroup UIHelpers                                                        */
class RealFunctionFactory {
    public:
        virtual ~RealFunctionFactory() { }
        /// Template Method to create a RealFunction
        RealFunction *createFunction(C4DView *view) {
            return doCreateFunction(view);
        }

    private:
        /// Implementation of TemplateMethod createFunction()
        virtual RealFunction *doCreateFunction(C4DView *) = 0;
};

/// Abstract base class for a factory creating Surface's
/** Defines the interface a TemplatedSurfaceFactory<> implements
 *
 *  Separate classes are needed for Functions and Surfaces, because their
 *  constructors differ.
 *  \ingroup UIHelpers                                                        */
class SurfaceFactory {
    public:
        virtual ~SurfaceFactory() { }
        /// Template Method to create a Surface
        Surface *createSurface(C4DView *view) {
            return doCreateSurface(view);
        }

    private:
        /// Implementation of TemplateMethod createSurface()
        virtual Surface *doCreateSurface(C4DView *) = 0;
};

/// Displays and manipulates four-dimensional Functions in a QGLWidget
/** This class is much too fat and will be split into parts wherever possible
 *  \ingroup UIGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class C4DView : public QGLWidget {

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
                private:
                    /// Implementation of TemplateMethod createFunction()
                    virtual RealFunction *doCreateFunction(C4DView *);
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
                private:
                    /// Implementation of TemplateMethod createSurface()
                    virtual Surface *doCreateSurface(C4DView *);
            };

    private:
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

        class Menu4D;
        class MouseHandler4D;

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
        void setWireframe (bool wire) { setDisplayPolygons(!wire); }
        /// @return whether to display the 4D coordinate cross or not
        bool getDisplayCoordinates() const { return DisplayCoordinates(); }
        /// @return whether to save the rendered images to an image file
        bool getRenderToPixmap() const { return RenderToPixmap(); }
        /// @return whether to draw the objects' surfaces or only the edges
        bool getDisplayPolygons() const { return DisplayPolygons(); }
        /// @return whether to use colors in rendering or not
        bool &getColors() { return pImpl->colors; }
        /// @return whether to use shading in rendering or not
        bool &getShade() { return pImpl->shade; }
        /// @return whether to use depth cue/fog in rendering or not
        bool &getFog() { return pImpl->fog; }
        /// @return whether to use lighting in rendering or not
        bool &getLight() { return pImpl->light; }
        /// @return whether to use transparence/line antialiasing or not
        bool &getTransparent() { return pImpl->transparent; }

        double Benchmark3D(int, double, double, double, bool = true);
        double Benchmark4D(int, double, double, double, bool = true);

    private slots:
        void OnTimer();
        void AnimationSettings();
        void ApplyChanges(const ParameterMap &);
        void Help();
        void about ();
        void aboutQt ();

    private:
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
        void resizeGL (int, int);

        void setF(Function *_f) { pImpl->F.reset(_f); }
        const std::auto_ptr<Function> &F() const { return pImpl->F; }

        void setTx(double _tx) { pImpl->Tx = _tx; }
        double Tx() const { return pImpl->Tx; }
        void setTy(double _ty) { pImpl->Ty = _ty; }
        double Ty() const { return pImpl->Ty; }
        void setTz(double _tz) { pImpl->Tz = _tz; }
        double Tz() const { return pImpl->Tz; }
        void setTw(double _tw) { pImpl->Tw = _tw; }
        double Tw() const { return pImpl->Tw; }
        void setRxy(double _rxy) { pImpl->Rxy = _rxy; }
        double Rxy() const { return pImpl->Rxy; }
        void setRxz(double _rxz) { pImpl->Rxz = _rxz; }
        double Rxz() const { return pImpl->Rxz; }
        void setRxw(double _rxw) { pImpl->Rxw = _rxw; }
        double Rxw() const { return pImpl->Rxw; }
        void setRyz(double _ryz) { pImpl->Ryz = _ryz; }
        double Ryz() const { return pImpl->Ryz; }
        void setRyw(double _ryw) { pImpl->Ryw = _ryw; }
        double Ryw() const { return pImpl->Ryw; }
        void setRzw(double _rzw) { pImpl->Rzw = _rzw; }
        double Rzw() const { return pImpl->Rzw; }

        void setm_rotX(GLdouble _rx) { pImpl->m_rotX = _rx; }
        GLdouble m_rotX() const { return pImpl->m_rotX; }
        void setm_rotY(GLdouble _ry) { pImpl->m_rotY = _ry; }
        GLdouble m_rotY() const { return pImpl->m_rotY; }
        void setm_rotZ(GLdouble _rz) { pImpl->m_rotZ = _rz; }
        GLdouble m_rotZ() const { return pImpl->m_rotZ; }
        void setm_transX(GLdouble _tx) { pImpl->m_transX = _tx; }
        GLdouble m_transX() const { return pImpl->m_transX; }
        void setm_transY(GLdouble _ty) { pImpl->m_transY = _ty; }
        GLdouble m_transY() const { return pImpl->m_transY; }
        void setm_camZ(GLdouble _cz) { pImpl->m_camZ = _cz; }
        GLdouble m_camZ() const { return pImpl->m_camZ; }

        void setCamW(double _cw) { pImpl->CamW = _cw; }
        double CamW() const { return pImpl->CamW; }
        void setScrW(double _sw) { pImpl->ScrW = _sw; }
        double ScrW() const { return pImpl->ScrW; }

        void setAntiAlias(bool b) { pImpl->AntiAlias = b; }
        bool AntiAlias() const { return pImpl->AntiAlias; }
        void setDisplayPolygons(bool b) { pImpl->DisplayPolygons = b; }
        bool DisplayPolygons() const { return pImpl->DisplayPolygons; }
        void setLighting(bool b) { pImpl->Lighting = b; }
        bool Lighting() const { return pImpl->Lighting; }
        void setDepthCue3D(bool b) { pImpl->DepthCue3D = b; }
        bool DepthCue3D() const { return pImpl->DepthCue3D; }
        void setDepthCue4D(bool b) { pImpl->DepthCue4D = b; }
        bool DepthCue4D() const { return pImpl->DepthCue4D; }
        void setDisplayCoordinates(bool b) { pImpl->DisplayCoordinates = b; }
        bool DisplayCoordinates() const { return pImpl->DisplayCoordinates; }
        void setRenderToPixmap(bool b) { pImpl->RenderToPixmap = b; }
        bool RenderToPixmap() const { return pImpl->RenderToPixmap; }

        double R() {return pImpl->R; }

        void setanimationDirectory(const QString &b) { pImpl->animationDirectory = b; }
        const QString & animationDirectory() const { return pImpl->animationDirectory; }
        void setanimationPrefix(const QString &b) { pImpl->animationPrefix = b; }
        const QString & animationPrefix() const { return pImpl->animationPrefix; }

        void setanimationFrame(unsigned b) { pImpl->animationFrame = b; }
        unsigned animationFrame() const { return pImpl->animationFrame; }
        void setanimationMaxFrames(unsigned b) { pImpl->animationMaxFrames = b; }
        unsigned animationMaxFrames() const { return pImpl->animationMaxFrames; }
        const unsigned animation_fps() const { return pImpl->animation_fps; }

        void setObjectList(GLint b) { pImpl->ObjectList = b; }
        GLint ObjectList() const { return pImpl->ObjectList; }
        void setCoordinateCross(GLint b) { pImpl->CoordinateCross = b; }
        GLint CoordinateCross() const { return pImpl->CoordinateCross; }

        void setAnimated(bool b) { pImpl->Animated = b; }
        bool Animated() const { return pImpl->Animated; }
        void setTakingSpinValues(bool b) { pImpl->TakingSpinValues = b; }
        bool TakingSpinValues() const { return pImpl->TakingSpinValues; }
        void setCurrentlyRendering(bool b) { pImpl->CurrentlyRendering = b; }
        bool CurrentlyRendering() const { return pImpl->CurrentlyRendering; }

        void setm_LeftDownPos(QPoint b) { pImpl->m_LeftDownPos = b; }
        QPoint m_LeftDownPos() const { return pImpl->m_LeftDownPos; }
        void setm_MidDownPos(QPoint b) { pImpl->m_MidDownPos = b; }
        QPoint m_MidDownPos() const { return pImpl->m_MidDownPos; }
        void setm_RightDownPos(QPoint b) { pImpl->m_RightDownPos = b; }
        QPoint m_RightDownPos() const { return pImpl->m_RightDownPos; }

        void setAnimationTimer(QTimer * b) { pImpl->AnimationTimer = b; }
        QTimer * AnimationTimer() const { return pImpl->AnimationTimer; }
        void setAnimateRandomTimer(QTimer * b) { pImpl->AnimateRandomTimer = b; }
        QTimer * AnimateRandomTimer() const { return pImpl->AnimateRandomTimer; }

        void setValues(ValuesDialogImpl * b) { pImpl->Values = b; }
        ValuesDialogImpl * Values() const { return pImpl->Values; }

        void setdxy(double _dxy) { pImpl->dxy = _dxy; }
        double dxy() const { return pImpl->dxy; }
        void setdxz(double _dxz) { pImpl->dxz = _dxz; }
        double dxz() const { return pImpl->dxz; }
        void setdxw(double _dxw) { pImpl->dxw = _dxw; }
        double dxw() const { return pImpl->dxw; }
        void setdyz(double _dyz) { pImpl->dyz = _dyz; }
        double dyz() const { return pImpl->dyz; }
        void setdyw(double _dyw) { pImpl->dyw = _dyw; }
        double dyw() const { return pImpl->dyw; }
        void setdzw(double _dzw) { pImpl->dzw = _dzw; }
        double dzw() const { return pImpl->dzw; }
        void setdx(double _dx) { pImpl->dx = _dx; }
        double dx() const { return pImpl->dx; }
        void setdy(double _dy) { pImpl->dy = _dy; }
        double dy() const { return pImpl->dy; }
        void setdz(double _dz) { pImpl->dz = _dz; }
        double dz() const { return pImpl->dz; }

        void setMenu(Menu4D *b) { pImpl->menu = b; }
        Menu4D *Menu() const { return pImpl->menu; }
        void setMouseHandler(MouseHandler4D *m) { pImpl->mouseHandler = m; }
        MouseHandler4D *MouseHandler() const { return pImpl->mouseHandler; }

        void SetupDepthCue (float, float);
        void InitLight (void);
        void InitShade (void);
        void InitFog  (void);
        void InitTransparence (void);

    private:                                    //  member variables
        /// Private class containing the member data for the Pimpl idiom
        /** I thought it would be a good idea to switch to the Pimpl idiom
         *  (all data in a private inner class, to which the outer class keeps
         *  only a pointer) to cleanly separate implementation and interface.
         *
         *  Turns out the idea is not so great, at least not in this case. I
         *  had to define a gazillion getters and setters first (none of which
         *  were supported by KDevelop or Eclipse/CDT in any way), thereby
         *  introducing a gazillion possibilities for typos, which may or may
         *  not be detected by the compiler. Then I had to go and change every
         *  occurrence of the member variable in the class implementation to
         *  its corresponding accessor. Granted, this had been less annoying if
         *  I had used Pimpl in the first place, but replacing \code x++ \endcode
         *  with \code setx(x()+1) \endcode is \em not increasing readability in
         *  any way.
         *
         *  For that reason I left the two-dimensional vector<>s Cross,
         *  CrossTrans and CrossScr out of the inner class.
         *
         *  A slight improvement in readability comes from the fact that all
         *  member variables are now visible as such, because they are called
         *  as a function.
         *
         *  Moral: I think the Pimpl idiom does not make sense in all
         *  circumstances.                                                    */
        struct Impl {
            Impl(C4DView *parent):
                Background (0.25, 0.25, 0.25, 1.),
                F(std::auto_ptr<Function>()),

                Tx (0), Ty (0), Tz (0), Tw (0),
                Rxy (0), Rxz (0), Rxw (0), Ryz (0), Ryw (0), Rzw (0),

                m_rotX (15), m_rotY (15), m_rotZ (0.),
                m_transX (0), m_transY (0), m_camZ (-10.),

                CamW (-3.), ScrW (0.),

                AntiAlias (false), DisplayPolygons (false), Lighting (true),
                DepthCue3D (false), DepthCue4D (false),
                light (true), fog (true), transparent (false), shade (true), colors (true),
                DisplayCoordinates (false),
                RenderToPixmap (false),
                animationDirectory("/tmp"),
                animationPrefix("HyperspaceExplorer_Image"),
                animationMaxFrames((unsigned)-1),
                animation_fps (50),

                ObjectList (0), CoordinateCross (0),

                Animated (false), TakingSpinValues (false),
                CurrentlyRendering (false),

                m_LeftDownPos (0,0), m_MidDownPos (0,0), m_RightDownPos (0,0),

                Values (new ValuesDialogImpl (parent)),
                dxy (0), dxz (0), dxw (0), dyz (0), dyw (0), dzw (0),
                dx (0), dy (0), dz (0) {}

            Color Background;  ///< background color

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
            bool light, fog, transparent, shade, colors;
            double R;                       ///< viewpoint distance

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

            Menu4D *menu;               ///< the popup menu and menu bar
            MouseHandler4D *mouseHandler; ///< handler to delegate mouse events to
        };

    std::auto_ptr<C4DView::Impl> pImpl;

    static GLfloat LightPos[4]; ///< position of the light

    /// endpoints of the lines constituting the 4D coordinate cross
    std::vector<std::vector<VecMath::Vector<4> > > Cross;
    /// endpoints of the lines constituting the transformed 4D coordinates
    std::vector<std::vector<VecMath::Vector<4> > > CrossTrans;
    /// endpoints of the lines constituting the projected 4D coordinates
    std::vector<std::vector<VecMath::Vector<3> > > CrossScr;

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
