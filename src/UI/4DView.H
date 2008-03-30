
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
class Surface;

class CustomFunction;
class CustomPolarFunction;
class CustomSurface;
class CustomComplexFunction;

/// \defgroup UIGroup User Interface
/// \defgroup UIHelpers Helper classes for User Interface classes
/// \ingroup UIGroup

/// Abstract base class for a factory creating Function's
/** \ingroup UIHelpers                                                */
class FunctionFactory {
    public:
        virtual Function *createFunction(C4DView *)=0;
};

/// Abstract base class for a factory creating Surface's
/** \ingroup UIHelpers                                                */
class SurfaceFactory {
    public:
        virtual Surface *createSurface(C4DView *)=0;
};

/// Displays and manipulates four-dimensional Functions in a QGLWidget
/** This class is much too fat and will be split into parts wherever possible
 *  \todo move all menu slots into one (or a few) factory methods
 *  \ingroup UIGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class C4DView : public XQGLWidget {

    public:
        /// Class template implementation for a factory creating Function's
        /** The type of the Function to be created by the factory method of this
         *  class is passed as a template parameter.
         *  \ingroup UIHelpers                                                */
        template <typename function>
            class TemplatedFunctionFactory: public FunctionFactory {
                public:
                    virtual Function *createFunction(C4DView *);
            };

        /// Class template implementation for a factory creating Surface's
        /** The type of the Surface to be created by the factory method of this
         *  class is passed as a template parameter.
         *  \ingroup UIHelpers                                                */
        template <typename function>
            class TemplatedSurfaceFactory: public SurfaceFactory {
                public:
                    virtual Surface *createSurface(C4DView *);
            };

    protected:
        /// Class template to outsource redundant code
        /** Class template to outsource redundant code for the generation of
        *  customized functions in a slot called by QActions from the QMenu
        *  @param function the Function to be created in the slot
        *  \ingroup UIHelpers                                                 */
        template<class function> class CustomFunctionSlot {
            public:
                static void createCustomFunction(C4DView *view);
                static void createCustomSurface(C4DView *view);
        };

        /// Class template to outsource redundant code
        /** Class template to outsource redundant code for the generation of
        *  functions in a slot called by QActions from the QMenu
        *  @param function the Function to be created in the slot
        *  \ingroup UIHelpers                                                 */
        template<class function> class FunctionSlot {
            public:
                static void createFunction(C4DView *view);
                static void createSurface(C4DView *view);
                static void createObject(C4DView *view);
        };

    Q_OBJECT

    public:
        C4DView(QWidget * = 0);
        virtual ~C4DView();

        /// @param wire if true, displays wireframe model; else solid
        void SetWireframe (bool wire) { DisplayPolygons = !wire; }
        /// @return true if display is set to wireframe, false if solid
        bool GetWireframe (void) { return !DisplayPolygons; }
        /// @param light whether to use lights in rendering or not
        void SetLighting (bool light) { Lighting = light; }
        /// @return whether to use lights in rendering or not
        bool GetLighting (void) { return Lighting; }
        /// Toggle depth cue in display and redraw
        /** @param on whether to use depth cue                                */
        void SetDepthCue (bool on) {
            SetupDepthCue (on);
            OnPaint ();
        }

        /// Set the three-space rotation of the object
        /** @param rx rotation about X-axis
         *  @param ry rotation about Y-axis
         *  @param rz rotation about Z-axis                                   */
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
        /// Overloaded function executing the transform to the default state
        void Transform (void) { Transform (0, 0, 0, 0, 0, 0,  0, 0, 0, 0); }

        void Redraw ();

        double Benchmark4D (int, double, double, double, bool = true);
        double Benchmark3D (int, double, double, double, bool = true);

        /// @return whether to use colors in rendering or not
        bool getColors() const { return colors; }
        /// @return whether to use shading in rendering or not
        bool getShade() const { return shade; }
        /// @return whether to use depth cue/fog in rendering or not
        bool getFog() const { return fog; }
        /// @return whether to use lighting in rendering or not
        bool getLight() const { return light; }
        /// @return whether to use transparence/line antialiasing or not
        bool getTransparent() const { return transparent; }
        /// @return whether to display the 4D coordinate cross or not
        bool getDisplayCoordinates() const { return DisplayCoordinates; }
        /// @return whether to save the rendered images to an image file
        bool getRenderToPixmap() const { return RenderToPixmap; }
        /// @return whether to draw the objects' surfaces or only the edges
        bool getDisplayPolygons() const { return DisplayPolygons; }

        /// @return a pointer to the popup menu
        Menu4D *getMenu() const { return menu; }

        /// Set the Function object associated with this view
        void setFunction(Function *_f) { F.reset(_f); }

    public slots:
        void ApplyChanges ();

        void ParametersChanged (double tmin, double tmax, unsigned tsteps,
                                double umin, double umax, unsigned usteps,
                                double vmin, double vmax, unsigned vsteps,
                                double a, double b, double c, double d,
                                QString &func);

    protected:

        void Project ();
        void Draw ();
        void PreRedraw ();
        QPixmap makePixmap();
        void writeFrame();

        void DrawCoordinates (void);
        void SetupDepthCue (bool);

        void StartAnimation ();
        void StopAnimation ();
        void RandomAnimation();

        void UpdateStatus (QString = "");

        void AssignValues (const std::auto_ptr<Function> &);

        void OnPaint();

        virtual void resizeEvent ( QResizeEvent * );
        virtual void mousePressEvent (QMouseEvent *);
        virtual void mouseReleaseEvent ( QMouseEvent *);
        virtual void mouseMoveEvent(QMouseEvent *);
        virtual void mouseDoubleClickEvent ( QMouseEvent *);

        void InitCross();

        /// a GLList for the display of the object
        GLint ObjectList;
        /// a GLList for the display of the coordinates
        GLint CoordinateCross;

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

        /// rotation in X
        GLdouble m_rotX;
        /// rotation in Y
        GLdouble m_rotY;
        /// rotation in Z
        GLdouble m_rotZ;
        /// translation in X
        GLdouble m_transX;
        /// translation in Y
        GLdouble m_transY;
        /// Z coordinate of the camera (distance from object)
        GLdouble m_camZ;

        QPoint m_LeftDownPos,   ///< position where the LMB press started
               m_MidDownPos,    ///< position where the MMB press started
               m_RightDownPos;  ///< position where the RMB press started

        /// whether to draw antialiased lines or transparent surfaces
        bool AntiAlias;
        /// whether to draw solid surfaces
        bool DisplayPolygons;
        /// whether to use lights in rendering
        bool Lighting;
        /// whether to use depth cue
        bool DepthCue3D;
        /// whether to use depth cue in 4D
        bool DepthCue4D;

        /// whether to show the 4D coordinate cross
        bool DisplayCoordinates;

        /// whether the image is currently animated
        bool Animated;
        /// true while mouse button pressed and mouse moved to take movement speed
        bool TakingSpinValues;

        /// whether to save images
        bool RenderToPixmap;
        /// whether currently rendering an image
        bool CurrentlyRendering;

        /// times out every X ms to draw new animation frame
        QTimer *AnimationTimer;
        /// times out to change rotation direction
        QTimer *AnimateRandomTimer;

        /// dialog to enter function parameters
        ValuesDialogImpl *Values;

        /// the Function object currently displayed
        std::auto_ptr<Function> F;

        /// name of current function for status bar
        QString ObjectName;

        double dxy,     ///< delta values in xy rotation angle - for animations
               dxz,     ///< delta values in xz rotation angle - for animations
               dxw,     ///< delta values in xw rotation angle - for animations
               dyz,     ///< delta values in yz rotation angle - for animations
               dyw,     ///< delta values in yw rotation angle - for animations
               dzw,     ///< delta values in zw rotation angle - for animations
               dx,      ///< delta values in x translation - for animations
               dy,      ///< delta values in y translation - for animations
               dz;      ///< delta values in z translation - for animations

        /// frames per second for animations
        const unsigned animation_fps;

        /// W coordinate of the camera
        double CamW;
        /// W coordinate of the screen
        double ScrW;

        /// endpoints of the lines constituting the 4D coordinate cross
        std::vector<std::vector<VecMath::Vector<4> > > Cross;
        /// endpoints of the lines constituting the transformed 4D coordinates
        std::vector<std::vector<VecMath::Vector<4> > > CrossTrans;
        /// endpoints of the lines constituting the projected 4D coordinates
        std::vector<std::vector<VecMath::Vector<3> > > CrossScr;

        /// limit for saved animation frames
        unsigned animationMaxFrames;
        /// current frame in animation
        unsigned animationFrame;
        /// where to save the images of an animation
        QString animationDirectory;
        /// prefix of animation frame filenames
        QString animationPrefix;

        /// the popup menu
        Menu4D *menu;


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

        void ObjectHypercube();
        void ObjectHyperpyramid();
        void ObjectHypersponge();
        void ObjectGasket();
        void customFunction();
        void customPolarFunction();
        void customComplexFunction();
        void customSurface();

        friend class CustomFunctionSlot<CustomFunction>;
        friend class CustomFunctionSlot<CustomPolarFunction>;
        friend class CustomFunctionSlot<CustomComplexFunction>;
        friend class CustomFunctionSlot<CustomSurface>;

        friend class FunctionSlotHelper;
        friend class SurfaceSlotHelper;
};

#include "Function.H"
#include "Menu4D.H"

/// Factory method to create a new Function of type R^3->R
/** This function template is called by each slot with the correct function
 *  type as template parameter. \n
 *  Sets F to the newly created Function, checks the corresponding menu item,
 *  updates the ValuesDialog and redraws.                                     */
template<class function>
        void C4DView::FunctionSlot<function>::createFunction(C4DView *view) {

        view->F.reset(new function (
            view->Values->tmin (), view->Values->tmax (), view->Values->dt (),
            view->Values->umin (), view->Values->umax (), view->Values->du (),
            view->Values->vmin (), view->Values->vmax (), view->Values->dv ()));

    SingletonLog::Instance() << "FunctionSlot<function>::createFunction(): "
            << view->F->getFunctionName().toStdString()
            << "(" << view->F->getParameterName(0).toStdString()
            << "," <<view->F->getParameterName(1).toStdString() <<","
            << view->F->getParameterName(2).toStdString() <<","
            << view->F->getParameterName(3).toStdString()<<")\n";

    view->menu->updateFunctionMenu (view->F->getFunctionName());
    view->AssignValues (view->F);
    view->Redraw ();
}

/// Factory method to create a new Function of type R^2->R^4
/** This function template is called by each slot with the correct function
 *  type as template parameter. \n
 *  Sets F to the newly created Function, checks the corresponding menu item,
 *  updates the ValuesDialog and redraws.                                     */
template<class function>
        void C4DView::FunctionSlot<function>::createSurface(C4DView *view) {

    view->F.reset(new function (
             view->Values->tmin (), view->Values->tmax (), view->Values->dt (),
             view->Values->umin (), view->Values->umax (), view->Values->du ()));

    try {
        view->menu->updateFunctionMenu (view->F->getFunctionName());
    } catch (QString error) {
        QMessageBox::information (NULL, "Error", error);

    }
    view->AssignValues (view->F);

    view->Redraw ();
}

#include "FunctionDialogImpl.H"
#include "PolarDialogImpl.H"
#include "ComplexDialogImpl.H"
#include "SurfaceDialogImpl.H"

#include "CustomFunction.H"

/// Factory method to create a new customized Function of type R^3->R
/** This function template is called by each slot with the correct function
 *  type as template parameter. \n
 *  Sets F to the newly created Function, checks the corresponding menu item,
 *  updates the ValuesDialog and redraws. Does some error handling in case the
 *  Function could not be loaded.                                             */
template<class function>
        void C4DView::CustomFunctionSlot<function>::createCustomFunction(
                 C4DView *view) {
            function *tmp = new function (
                view->Values->tmin (), view->Values->tmax (), view->Values->dt (),
                view->Values->umin (), view->Values->umax (), view->Values->du (),
                view->Values->vmin (), view->Values->vmax (), view->Values->dv ());
            if (tmp->isValid()) {
                    view->F.reset(tmp);
                    QString sym (((function *)(view->F).get ())->symbolic());

                view->AssignValues(view->F);
                view->Redraw ();
            } else {
                delete tmp;
                view->UpdateStatus("Failed to load custom function");
            }
        }

/// Factory method to create a new customized Function of type R^2->R^4
/** This function template is called by each slot with the correct function
 *  type as template parameter. \n
 *  Sets F to the newly created Function, checks the corresponding menu item,
 *  updates the ValuesDialog and redraws. Does some error handling in case the
 *  Function could not be loaded.                                             */
template<class function>
    void C4DView::CustomFunctionSlot<function>::createCustomSurface(
                C4DView *view) {
        function *tmp = new function (
            view->Values->tmin (), view->Values->tmax (), view->Values->dt (),
            view->Values->umin (), view->Values->umax (), view->Values->du ());
        if (tmp->isValid()) {
            view->F.reset(tmp);
            QString sym (((function *)(view->F).get ())->symbolic());

            view->AssignValues(view->F);
            view->Redraw ();
        } else {
            delete tmp;
            view->UpdateStatus("Failed to load custom function");
        }
    }

/// Factory method to create a Function object
/** The type of the created Function is supplied as template parameter to the
 *  TemplatedFunctionFactory object owning this method.                       */
template<class function>
    Function *C4DView::TemplatedFunctionFactory<function>::createFunction(
        C4DView *view) {
        return new function (
            view->Values->tmin (), view->Values->tmax (), view->Values->dt (),
            view->Values->umin (), view->Values->umax (), view->Values->du (),
            view->Values->vmin (), view->Values->vmax (), view->Values->dv ());
    }

/// Factory method to create a Surface object
/** The type of the created Surface is supplied as template parameter to the
 *  TemplatedSurfaceFactory object owning this method.                       */
template<class function>
    Surface *C4DView::TemplatedSurfaceFactory<function>::createSurface(
        C4DView *view) {
        return new function (
            view->Values->umin (), view->Values->umax (), view->Values->du (),
            view->Values->vmin (), view->Values->vmax (), view->Values->dv ());
    }


#endif // !defined(4DVIEW)
