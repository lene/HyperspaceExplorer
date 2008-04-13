
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


//      project:      GL/Qt interface
//      module:       XQGLWidget.H
//      compile with: make all
//      contains:     class definition for the extended OpenGL widget

#ifndef XQGLW_H
#define XQGLW_H

#include <QGLWidget>

#include "Vector.H"
#include "GLObject.H"

class Q3PopupMenu;
class QMouseEvent;

/** class XQGLWidget:
 *  implements a QGLWidget
 *  \ingroup UIGroup                                                          */
class XQGLWidget: public QGLWidget {

    Q_OBJECT

    public slots:                               //  called when:
        void ViewPos (double, double, double);  //  - viewing angle is changed
        void ViewPos (double);                  //  - distance of viewpoint is changed

    public:
        XQGLWidget (QWidget * = 0);
        bool SetDrawObject (GLObject *obj) {
            DrawObject = obj;
            return *DrawObject;
        }
        bool SetDrawObject (GLuint list) {
            DrawObject = new GLObject (list);
            return *DrawObject;
        }

        void SetBackgroundColor (const VecMath::Vector<4> &RGBA) {
            Background = RGBA;
        }

        void SetBackgroundColor (float R, float G, float B, float A) {
            Background = VecMath::Vector<4> (R, G, B, A);
        }
        /// @return whether to use colors in rendering or not
        bool &getColors() { return colors; }
        /// @return whether to use shading in rendering or not
        bool &getShade() { return shade; }
        /// @return whether to use depth cue/fog in rendering or not
        bool &getFog() { return fog; }
        /// @return whether to use lighting in rendering or not
        bool &getLight() { return light; }
        /// @return whether to use transparence/line antialiasing or not
        bool &getTransparent() { return transparent; }


    protected slots:
        void Rotate ();
        void Help ();

        void SetAlpha (int);

        //  key acceleration handling
        void Left ();
        void Right ();
        void Up ();
        void Down ();
        void SLeft ();
        void SRight ();
        void SUp ();
        void SDown ();
        void CALeft ();
        void CARight ();
        void CAUp ();
        void CADown ();

        void Plus ();
        void Minus ();

        void A ();

        void about ();
        void aboutQt ();

    protected:                                  //  OpenGL interface
        void initializeGL (void);
        void paintGL (void);
        void resizeGL (int, int);
        void Draw (void);

        void mousePressEvent (QMouseEvent *);
        void mouseReleaseEvent (QMouseEvent *);
        void mouseMoveEvent (QMouseEvent *);
        void SetupDepthCue (float, float);
        void InitLight (void);
        void InitShade (void);
        void InitFog  (void);
        void InitTransparence (void);

    private:
        GLObject *DrawObject;
        //  geometry states
        double R,                       ///< viewpoint distance
               psi,                     ///< rotation about x-axis
               theta,                   ///< rotation about y-axis
               phi;                     ///< rotation about z-axis
               VecMath::Vector<4> Background;
        GLfloat Alpha;

        //  drawing realism states
        bool light, fog, transparent, shade, colors;
        int xpressed, ypressed;

};

#endif
