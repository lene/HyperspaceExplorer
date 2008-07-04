
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

#include "View.H"
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
class C4DView : public QGLWidget, public UI::View {

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

        virtual void ObjectHypercube();
        virtual void ObjectHyperpyramid();
        virtual void ObjectHypersponge();
        virtual void ObjectGasket();
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

        virtual void applyTransform(const VecMath::Rotation<4> &R,
                                    const VecMath::Vector<4> &T) {
            Transform(R, T);
            Redraw();
        }

        virtual void animate() {
            for (unsigned i = 0; i < getNumLoops(); i++) {
                for (unsigned i = 0; i < getNumFrames(); i++) {
                    addR(dR());
                    std::cerr << R() << std::endl;
                    Transform(R(), VecMath::Vector<4>());
                    Project();
                    Redraw();
                }
            }
        }

        virtual void setImgDir(const std::string &s) {
            setanimationDirectory(QString(s.c_str()));
            setRenderToPixmap(true);
        }
        virtual void setImgPrefix(const std::string &s) {
            setanimationPrefix(QString(s.c_str()));
            setRenderToPixmap(true);
        }

        virtual void setSize(unsigned w, unsigned h);

        virtual void setColors(bool);
        virtual void setShading(bool);
//        virtual void setLighting(bool);
        virtual void setTransparence(bool);
//        virtual void setWireframe(bool);
        virtual void setFog(bool);
        virtual void setHyperfog(bool);
        virtual void setCoordinates(bool);
        virtual void setBackground(const Color &);
        
        virtual void setFunction(Function *_f) { setF(_f); }

    private slots:
        void OnTimer();
        void AnimationSettings();
        virtual void ApplyChanges(const ParameterMap &);
        void Help();
        void about ();
        void aboutQt ();

    private:
        void Transform(const VecMath::Rotation<4> &R, const VecMath::Vector<4> &T);
        /// Overloaded function executing the transform to the default state
        /** Four-dimensional transform is set to no rotation, no translation.
         *
         *  Three-dimensional transform is 15 degrees about x and y axis, and
         *  10 units distance from the camera.                                */
        void Transform() {
            setT(VecMath::Vector<4>());
            setR(VecMath::Rotation<4>());

            setm_rot(VecMath::Rotation<3, GLdouble>(15., 15., 0.));
            setm_trans(VecMath::Vector<3, GLdouble>(0.,0.,-10.));

            Transform (R(), T());   //  apply 4D transformation
        }
        void Project();

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

        void setT(const VecMath::Vector<4> &_t) { pImpl->T = _t; }
        const VecMath::Vector<4> &T() { return pImpl->T; }
        void addT(const VecMath::Vector<4> &_dT) { pImpl->T += _dT; }

        void setR(const VecMath::Rotation<4> &_r) { pImpl->R = _r; }
        const VecMath::Rotation<4> &R() { return pImpl->R; }
        void addR(const VecMath::Rotation<4> &_dR) { pImpl->R += _dR; }

        void setdR3(const VecMath::Rotation<3> &_dr) { pImpl->dR3 = _dr; }
        const VecMath::Rotation<3> &dR3() { return pImpl->dR3; }
        void adddR3(const VecMath::Rotation<3> &_ddr) { pImpl->dR3 += _ddr; }

        virtual void setdR(const VecMath::Rotation<4> &_dr) { pImpl->dR = _dr; }
        const VecMath::Rotation<4> &dR() { return pImpl->dR; }
        void adddR(const VecMath::Rotation<4> &_ddR) { pImpl->dR += _ddR; }

        void setm_rot(const VecMath::Rotation<3, GLdouble> &_r) {
            pImpl->m_rot = _r;
        }
        const VecMath::Rotation<3, GLdouble> &m_rot() {
            return pImpl->m_rot;
        }
        void addm_rot(const VecMath::Rotation<3, GLdouble> &_dmr) {
            pImpl->m_rot += _dmr;
        }

        void setm_trans(const VecMath::Vector<3, GLdouble> &_t) {
            pImpl->m_trans = _t;
        }
        const VecMath::Vector<3, GLdouble> &m_trans() {
            return pImpl->m_trans;
        }
        void addm_trans(const VecMath::Vector<3, GLdouble> &_dmt) {
            pImpl->m_trans += _dmt;
        }

        void setCamW(const double &_cw) { pImpl->CamW = _cw; }
        double CamW() const { return pImpl->CamW; }
        void setScrW(const double &_sw) { pImpl->ScrW = _sw; }
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

        double distance() {return pImpl->distance; }

        void setanimationDirectory(const QString &b) {
            pImpl->animationDirectory = b;
        }
        const QString & animationDirectory() const {
            return pImpl->animationDirectory;
        }
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
        void setCurrentlyRendering(bool b) { pImpl->CurrentlyRendering = b; }
        bool CurrentlyRendering() const { return pImpl->CurrentlyRendering; }

        void setAnimationTimer(QTimer * b) { pImpl->AnimationTimer = b; }
        QTimer * AnimationTimer() const { return pImpl->AnimationTimer; }
        void setAnimateRandomTimer(QTimer * b) { pImpl->AnimateRandomTimer = b; }
        QTimer * AnimateRandomTimer() const { return pImpl->AnimateRandomTimer; }

        void setValues(ValuesDialogImpl * b) { pImpl->Values = b; }
        ValuesDialogImpl * Values() const { return pImpl->Values; }

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

                T(0.,0.,0.,0.), R(0.,0.,0.,0.,0.,0.), dR(0.,0.,0.,0.,0.,0.),
                m_rot(15., 15., 0.), dR3(0.,0.,0.), m_trans(0., 0.,-10.),

                CamW (-3.), ScrW (0.),

                AntiAlias (false), DisplayPolygons (false), Lighting (true),
                DepthCue3D (false), DepthCue4D (false),
                light (true), fog (true), transparent (false), shade (true), colors (true),
                DisplayCoordinates (false),
                RenderToPixmap (false),
                animationDirectory("/tmp"),
                animationPrefix("HyperspaceExplorer_Image"),
                animationFrame(0),
                animationMaxFrames((unsigned)-1),
                animation_fps (50),

                ObjectList (0), CoordinateCross (0),

                Animated (false), CurrentlyRendering (false),

                Values (new ValuesDialogImpl (parent)) {}

            Color Background;  ///< background color

            std::auto_ptr<Function> F;  ///< the Function object currently displayed

            VecMath::Vector<4> T;   ///< coordinates for 4D translation
            VecMath::Rotation<4> R;   ///< angles for 4D rotation

            /// delta values in angles for 4D rotation - for animations
            VecMath::Rotation<4> dR;

            /// rotation in X, Y and Z
            VecMath::Rotation<3, GLdouble> m_rot;
            /// delta values in 3D rotation - for animations
            VecMath::Rotation<3, GLdouble> dR3;
            /// translation in X and Y, Z coordinate of camera (distance from object)
            VecMath::Vector<3, GLdouble> m_trans;

            double CamW;        ///< W coordinate of the camera
            double ScrW;        ///< W coordinate of the screen

            /// if true, draw lines antialiased, surfaces transparent
            bool AntiAlias;
            bool DisplayPolygons;       ///< if true, draw solid surfaces
            bool Lighting;              ///< if true, use lights in rendering
            bool DepthCue3D;            ///< if true, use depth cue
            bool DepthCue4D;            ///< if true, use depth cue in 4D
            bool light, fog, transparent, shade, colors;
            double distance;                       ///< viewpoint distance

            bool DisplayCoordinates;    ///< if true, show the 4D coordinate cross
            bool RenderToPixmap;        ///< if true, save images

            QString animationDirectory; ///< where to save an animation's frames
            QString animationPrefix;    ///< prefix of animation frame filenames
            unsigned animationFrame;    ///< current frame in animation
            unsigned animationMaxFrames;    ///< limit for saved animation frames
            const unsigned animation_fps;   ///< frames per second for animations

            GLint ObjectList;       ///< a GLList for the display of the object
            GLint CoordinateCross;  ///< a GLList for the display of the coordinates

            bool Animated;              ///< if true, image is currently animated

            bool CurrentlyRendering;    ///< if true, currently rendering an image

            /// times out every X ms to draw new animation frame
            QTimer *AnimationTimer;
            /// times out to change rotation direction
            QTimer *AnimateRandomTimer;

            /// dialog to enter function parameters
            ValuesDialogImpl *Values;

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

#endif // !defined(C4DVIEW)
