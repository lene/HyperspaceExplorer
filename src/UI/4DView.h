/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef C4DVIEW_H
#define C4DVIEW_H

#include <QTimer>
#include <QGLWidget>

#include "ViewImpl.h"
#include "ValuesDialogImpl.h"
#include "Rotation.h"

class QPaintEvent;
class QStatusBar;

class C4DView;
class Displayable;
class RealFunction;
class Surface;

class CustomFunction;
class CustomPolarFunction;
class CustomSurface;
class CustomComplexFunction;

/// \defgroup UIGroup User Interface
/// \defgroup UIHelpers Helper classes for User Interface classes
/// \ingroup UIGroup

/// Displays and manipulates four-dimensional Functions in a QGLWidget
/** This class is much too fat and will be split into parts wherever possible
 *  \ingroup UIGroup
 *  @author Helge Preuss <lene.preuss@gmail.com>                         */
class C4DView : public QGLWidget, public UI::ViewImpl {


    private:
        /// Class template to outsource redundant code for customized functions
        /** Redundant code for the generation of customized functions is moved
         *  to a slot called by QActions from the QMenu
         *  \tparam function the Function to be created in the slot
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

        virtual void drawVertex(const VecMath::Vector< 4 > &x, const VecMath::Vector< 3 > &xscr);
        virtual void drawLine(const VecMath::Vector< 4 > &x0, const VecMath::Vector< 4 > &x1,
                              const VecMath::Vector< 3 > &xscr0, const VecMath::Vector< 3 > &xscr1);
        virtual void drawQuadrangle(const VecMath::Vector< 4 > &x0, const VecMath::Vector< 4 > &x1,
                                    const VecMath::Vector< 4 > &x2, const VecMath::Vector< 4 > &x3,
                                    const VecMath::Vector< 3 > &xscr0, const VecMath::Vector< 3 > &xscr1,
                                    const VecMath::Vector< 3 > &xscr2, const VecMath::Vector< 3 > &xscr3);
        virtual void drawPolygon(const std::vector< VecMath::Vector< 4 > >&x ,
                                 const std::vector< VecMath::Vector< 3 > >&xscr );

        ////////////////////////////////////////////////////////////////////////

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

        /// Wrapper for displaying OpenGL display lists
        void RenderScene();

        /// Initialize structures to display a four-dimensional coordinate cross
        void InitCross();
        void SetupDepthCue(bool);
        void DrawCoordinates(void);

        void StartAnimation();
        void StopAnimation();
        void RandomAnimation(bool);

        QPixmap makePixmap();
        void writeFrame();

        void checkAnglesForOverflow();
        void UpdateStatus(QString = "");

        void AssignValues(const std::tr1::shared_ptr<Displayable> &);

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
        virtual void paintEvent(QPaintEvent * = 0);
        /// Resizing routine, reimplemented from QGLWidget
        virtual void resizeEvent( QResizeEvent * );
        /// Called once before the first call to paintGL() or resizeGL(), reimplemented from QGLWidget
        virtual void initializeGL(void);
        /// GL stuff needed in addition to resizeEvent(). Reimplemented from QGLWidget
        virtual void resizeGL (int, int);

        /// Set the current 3D rotation state
        void setm_rot(const VecMath::Rotation<3, GLdouble> &_r) {
            _rot = _r;
        }
        /// \return The current 3D rotation state
        const VecMath::Rotation<3, GLdouble> &m_rot() {
            return _rot;
        }
        /// Add a translation to the current 3D rotation state
        void addm_rot(const VecMath::Rotation<3, GLdouble> &_dmr) {
            _rot += _dmr;
        }

        /// Set the current 3D translation state
        void setm_trans(const VecMath::Vector<3, GLdouble> &_t) {
            _trans = _t;
        }
        /// \return The current 3D translation state
        const VecMath::Vector<3, GLdouble> &m_trans() {
            return _trans;
        }
        /// Add a translation to the current 3D translation state
        void addm_trans(const VecMath::Vector<3, GLdouble> &_dmt) {
            _trans += _dmt;
        }

        /// Set current frame in animation
        void setanimationFrame(unsigned b) { _animationFrame = b; }
        /// \return current frame in animation
        unsigned animationFrame() const { return _animationFrame; }
        /// Set limit for saved animation frames
        void setanimationMaxFrames(unsigned b) { _animationMaxFrames = b; }
        /// \return limit for saved animation frames
        unsigned animationMaxFrames() const { return _animationMaxFrames; }
        /// \return frames per second for animations
        unsigned animation_fps() const { return _animation_fps; }

        /// Set a GLList for the display of the object
        void setObjectList(GLint b) { _objectList = b; }
        /// \return GLList for the display of the object
        GLint ObjectList() const { return _objectList; }
        /// Set a GLList for the display of the coordinates
        void setCoordinateCross(GLint b) { _coordinateCross = b; }
        /// \return GLList for the display of the coordinates
        GLint CoordinateCross() const { return _coordinateCross; }

        /// Set if image is currently animated
        void setAnimated(bool b) { _animated = b; }
        /// \return whether image is currently animated
        bool Animated() const { return _animated; }
        /// Set if currently rendering an image
        void setCurrentlyRendering(bool b) { _currentlyRendering = b; }
        /// \return whether currently rendering an image
        bool CurrentlyRendering() const { return _currentlyRendering; }

        /// Set timer that times out every X ms to draw new animation frame
        void setAnimationTimer(QTimer * b) { _animationTimer = b; }
        /// \return Timer that times out every X ms to draw new animation frame
        QTimer * AnimationTimer() const { return _animationTimer; }
        /// Set timer that times out to change rotation direction
        void setAnimateRandomTimer(QTimer * b) { _animateRandomTimer = b; }
        /// \return Timer that times out to change rotation direction
        QTimer * AnimateRandomTimer() const { return _animateRandomTimer; }

        /// Set dialog to enter function parameters
        void setValues(UI::Dialogs::ValuesDialogImpl * b) { _values = b; }
        /// \return Dialog to enter function parameters
        UI::Dialogs::ValuesDialogImpl * Values() const { return _values; }

        /// Set the popup menu and menu bar
        void setMenu(Menu4D *b) { _menu = b; }
        /// \return The popup menu and menu bar
        Menu4D *Menu() const { return _menu; }
        /// Set handler to delegate mouse events to
        void setMouseHandler(MouseHandler4D *m) { _mouseHandler = m; }
        /// \return Handler to delegate mouse events to
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

        bool _animated;             ///< if true, image is currently animated

        bool _currentlyRendering;   ///< if true, currently rendering an image

        GLint _objectList;      ///< a GLList for the display of the object
        GLint _coordinateCross; ///< a GLList for the display of the coordinates

        /// times out every X ms to draw new animation frame
        QTimer *_animationTimer;
        /// times out to change rotation direction
        QTimer *_animateRandomTimer;

        /// dialog to enter function parameters
        UI::Dialogs::ValuesDialogImpl *_values;

        Menu4D *_menu;                  ///< the popup menu and menu bar
        MouseHandler4D *_mouseHandler;  ///< handler to delegate mouse events to

        /// endpoints of the lines constituting the 4D coordinate cross
        std::vector<std::vector<VecMath::Vector<4> > > _cross;
        /// endpoints of the lines constituting the transformed 4D coordinates
        std::vector<std::vector<VecMath::Vector<4> > > _crossTrans;
        /// endpoints of the lines constituting the projected 4D coordinates
        std::vector<std::vector<VecMath::Vector<3> > > _crossScr;

        static std::string _helpFile;   ///< Path to the user docs HTML file

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
    friend class SlotHelper;

};

#endif // !defined(C4DVIEW)
