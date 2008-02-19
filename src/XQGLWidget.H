
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

#undef DEBUG

#include <qgl.h>
//Added by qt3to4:
#include <QMouseEvent>
#include <Q3PopupMenu>

#include <numclass.H>
#include "GLObject.H"

class Q3PopupMenu;

 ////////////////////////////////////////////////////////////////////////////
//  class XQGLWidget:                                                       //
//  implements a QGLWidget                                                  //
 ////////////////////////////////////////////////////////////////////////////

class XQGLWidget: public QGLWidget {
  Q_OBJECT

  public:
    XQGLWidget (QWidget * = 0, const char *name = 0);
    bool SetDrawObject (GLObject *obj) { 
      DrawObject = obj; return *DrawObject; }
    bool SetDrawObject (GLuint list) { 
      DrawObject = new GLObject (list); return *DrawObject; }

    void SetBackgroundColor (const Vector &RGBA) { Background = RGBA; }

    void SetBackgroundColor (float R, float G, float B, float A) {
      Background = Vector (4, R, G, B, A); }

  public slots:                                    //  called when:
    void ViewPos (double, double, double);         //  - viewing angle is changed
    void ViewPos (double);                         //  - distance of viewpoint is changed

  protected:                                       //  OpenGL interface
    void initializeGL (void);
    void paintGL (void);
    void resizeGL (int, int);
    void Draw (void);

    void InitLight (void);
    void InitShade (void); 
    void InitFog  (void); 
    void InitTransparence (void); 

    GLObject *DrawObject;

  protected:
  //  geometry states
    double R,                       //  viewpoint distance
           psi, theta, phi;         //  rotation about x-, y- & z-axis
    Vector Background;
    GLfloat Alpha;

  //  drawing realism states
    bool light, fog, transparent, shade, colors;
  
  protected:
    void mousePressEvent (QMouseEvent *);
    void mouseReleaseEvent (QMouseEvent *);
    void mouseMoveEvent (QMouseEvent *);
    int xpressed, ypressed;
    void SetupDepthCue (float, float);

  //  popup menu handling
    Q3PopupMenu *menu;                              //  menu identifiers
    virtual Q3PopupMenu *SetupMenu (void);
    void SetupAccel (void);

  protected:
    Q3PopupMenu *appear, *help;                            //  menu identifiers

    int lightID, fogID, transparentID, shadeID,    //  appearance items
        colorsID;

  protected slots:
    void Rotate ();
    void Help ();

    void Light ();                                 //  appearance submenu handlers
    void Colors ();
    void Fog ();
    void Transparent ();
    void Shade ();

    void SetAlpha (int);

  //  key acceleration handling
  protected slots:
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
   };

#endif
