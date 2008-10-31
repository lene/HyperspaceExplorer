
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//      author:	      helge preuss (scout@hyperspace-travel.de)
//      license:      GPL (see License.txt)

#ifndef C4DVIEW_H
#define C4DVIEW_H

#include <QTimer>
#include <QGLWidget>

#include "ViewImpl.H"
#include "ValuesDialogImpl.H"
#include "Rotation.H"

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
class C4DView : public QGLWidget, public UI::ViewImpl {

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

    public:
        C4DView(QWidget * = 0);
        virtual ~C4DView();

        ////////        Implementations of the View interface        ////////

        /// Implementation of UI::View::ObjectHypercube
        virtual void ObjectHypercube();
        /// Implementation of UI::View::ObjectHyperpyramid
        virtual void ObjectHyperpyramid();
        /// Implementation of UI::View::ObjectHypersponge
        virtual void ObjectHypersponge();
        /// Implementation of UI::View::ObjectGasket
        virtual void ObjectGasket();

        /// Implementation of UI::View::applyTransform
        virtual void applyTransform(const VecMath::Rotation<4> &R,
                                    const VecMath::Vector<4> &T);

        /// Implementation of UI::View::animate
        virtual void animate();

        /// Implementation of UI::View::setSize
        virtual void setSize(unsigned w, unsigned h);

        /// Re-Implementation of UI::ViewImpl::setBackground
        virtual void setBackground(const Color &);
        /// Re-Implementation of UI::ViewImpl::setColors
        virtual void setColors(bool);
        /// Re-Implementation of UI::ViewImpl::setCoordinates
        virtual void setCoordinates(bool);
        /// Re-Implementation of UI::ViewImpl::setFog
        virtual void setFog(bool);
        /// Re-Implementation of UI::ViewImpl::setHyperfog
        virtual void setHyperfog(bool);
        /// Re-Implementation of UI::ViewImpl::setLighting
        virtual void setLighting(bool);
        /// Re-Implementation of UI::ViewImpl::setShading
        virtual void setShading(bool);
        /// Re-Implementation of UI::ViewImpl::setTransparence
        virtual void setTransparence(bool);

        ////////        getters for the setters defined in View         ////////

        /// rotate in 3D 360 degrees
        double Benchmark3D(int, double, double, double, bool = true);
        /// rotate in 4D 360 degrees
        double Benchmark4D(int, double, double, double, bool = true);

    private slots:
        /// Implementation of UI::View::ApplyChanges
        virtual void ApplyChanges(const ParameterMap &);

        /// Animation timer event handler
        void OnAnimationTimer();

    private:
        /// Set the transform for the displayed object (but don't draw it yet)
        void Transform(const VecMath::Rotation<4> &R, const VecMath::Vector<4> &T);
        /// Overloaded function executing the transform to the default state
        void Transform();

        /// Execute the projection into three-space (but don't draw it yet either)
        void Project();

        /// Draw the projection into an OpenGL display list, but not yet on screen
        void PreRedraw();
        /// Draw the transformed and projected function onto the screen
        void Redraw();

        /// Paint event handler, called whenever the object is transformed
        void OnPaint();

        /// Wrapper for displaying OpenGL display lists
        void RenderScene();

        /// Initialize structures to display a four-dimensional coordinate cross
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

        /// Mouse move event handler, reimplemented from QWidget
        virtual void mouseMoveEvent(QMouseEvent *);
        /// Mouse press event handler, reimplemented from QWidget
        virtual void mousePressEvent(QMouseEvent *);
        /// Mouse release event handler, reimplemented from QWidget
        virtual void mouseReleaseEvent( QMouseEvent *);
        /// Double click event handler, reimplemented from QWidget
        virtual void mouseDoubleClickEvent( QMouseEvent *);
        /// Paint event handler, reimplemented from QGLWidget
        virtual void paintEvent(QPaintEvent *);
        /// Resizing routine, reimplemented from QGLWidget
        virtual void resizeEvent( QResizeEvent * );
        /// Called once before the first call to paintGL() or resizeGL(), reimplemented from QGLWidget
        virtual void initializeGL(void);
        /// GL stuff needed in addition to resizeEvent(). Reimplemented from QGLWidget
        virtual void resizeGL (int, int);

        void setm_rot(const VecMath::Rotation<3, GLdouble> &_r) {
            _rot = _r;
        }
        const VecMath::Rotation<3, GLdouble> &m_rot() {
            return _rot;
        }
        void addm_rot(const VecMath::Rotation<3, GLdouble> &_dmr) {
            _rot += _dmr;
        }

        void setm_trans(const VecMath::Vector<3, GLdouble> &_t) {
            _trans = _t;
        }
        const VecMath::Vector<3, GLdouble> &m_trans() {
            return _trans;
        }
        void addm_trans(const VecMath::Vector<3, GLdouble> &_dmt) {
            _trans += _dmt;
        }

        void setanimationFrame(unsigned b) { _animationFrame = b; }
        unsigned animationFrame() const { return _animationFrame; }
        void setanimationMaxFrames(unsigned b) { _animationMaxFrames = b; }
        unsigned animationMaxFrames() const { return _animationMaxFrames; }
        const unsigned animation_fps() const { return _animation_fps; }

        void setObjectList(GLint b) { _ObjectList = b; }
        GLint ObjectList() const { return _ObjectList; }
        void setCoordinateCross(GLint b) { _CoordinateCross = b; }
        GLint CoordinateCross() const { return _CoordinateCross; }

        void setAnimated(bool b) { _Animated = b; }
        bool Animated() const { return _Animated; }
        void setCurrentlyRendering(bool b) { _CurrentlyRendering = b; }
        bool CurrentlyRendering() const { return _CurrentlyRendering; }

        void setAnimationTimer(QTimer * b) { _AnimationTimer = b; }
        QTimer * AnimationTimer() const { return _AnimationTimer; }
        void setAnimateRandomTimer(QTimer * b) { _AnimateRandomTimer = b; }
        QTimer * AnimateRandomTimer() const { return _AnimateRandomTimer; }

        void setValues(UI::Dialogs::ValuesDialogImpl * b) { _Values = b; }
        UI::Dialogs::ValuesDialogImpl * Values() const { return _Values; }

        void setMenu(Menu4D *b) { _menu = b; }
        Menu4D *Menu() const { return _menu; }
        void setMouseHandler(MouseHandler4D *m) { _mouseHandler = m; }
        MouseHandler4D *MouseHandler() const { return _mouseHandler; }

    private:
        void SetupDepthCue (float, float);
        void InitLight (void);
        void InitShade (void);
        void InitFog  (void);
        void InitTransparence (void);

    private:                                    //  member variables

        /// rotation in X, Y and Z
        VecMath::Rotation<3, GLdouble> _rot;
        /// translation in X and Y, Z coordinate of camera (distance from object)
        VecMath::Vector<3, GLdouble> _trans;

        unsigned _animationFrame;       ///< current frame in animation
        unsigned _animationMaxFrames;   ///< limit for saved animation frames
        const unsigned _animation_fps;  ///< frames per second for animations

        bool _Animated;             ///< if true, image is currently animated

        bool _CurrentlyRendering;   ///< if true, currently rendering an image

        GLint _ObjectList;      ///< a GLList for the display of the object
        GLint _CoordinateCross; ///< a GLList for the display of the coordinates

        /// times out every X ms to draw new animation frame
        QTimer *_AnimationTimer;
        /// times out to change rotation direction
        QTimer *_AnimateRandomTimer;

        /// dialog to enter function parameters
        UI::Dialogs::ValuesDialogImpl *_Values;

        Menu4D *_menu;                  ///< the popup menu and menu bar
        MouseHandler4D *_mouseHandler;  ///< handler to delegate mouse events to

        /// endpoints of the lines constituting the 4D coordinate cross
        std::vector<std::vector<VecMath::Vector<4> > > _Cross;
        /// endpoints of the lines constituting the transformed 4D coordinates
        std::vector<std::vector<VecMath::Vector<4> > > _CrossTrans;
        /// endpoints of the lines constituting the projected 4D coordinates
        std::vector<std::vector<VecMath::Vector<3> > > _CrossScr;

        static GLfloat _LightPos[4];    ///< position of the light
        static std::string _HelpFile;   ///< Path to the user docs HTML file

    /// Factory object, Menu callback, need access to ValuesDialog, F and Redraw
    friend class CustomFunctionSlot<CustomFunction>;
    /// Factory object, Menu callback, need access to ValuesDialog, F and Redraw
    friend class CustomFunctionSlot<CustomPolarFunction>;
    /// Factory object, Menu callback, need access to ValuesDialog, F and Redraw
    friend class CustomFunctionSlot<CustomComplexFunction>;
    /// Factory object, Menu callback, need access to ValuesDialog, F and Redraw
    friend class CustomFunctionSlot<CustomSurface>;

    friend class FunctionSlotHelper;
    friend class SurfaceSlotHelper;
};

#include "CustomFunctionSlot.impl.H"
#include "TemplatedFunctionFactory.impl.H"

#endif // !defined(C4DVIEW)
