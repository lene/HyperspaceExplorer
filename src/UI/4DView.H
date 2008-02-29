
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#ifndef VIEW_H
#define VIEW_H


#include "XQGLWidget.H"

#include <qtimer.h> 
#include <qpoint.h> 
#include <qstatusbar.h>
//Added by qt3to4:
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPixmap>
#include <QMouseEvent>
#if (QT_VERSION < 400)
#include <q3popupmenu.h>
#else
#include <QMenu>
#endif
#include "ValuesDialogImpl.H"

template <unsigned D, typename N> class Vector;
class Function;

class C4DView : public XQGLWidget {

  Q_OBJECT

public:
  C4DView(QWidget * = 0, const char * = 0);
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
    m_rotX = rx; m_rotY = ry; m_rotZ = rz; }


  virtual void paintEvent (QPaintEvent *);
  virtual void initializeGL (void);

  double Size ();

  void RenderScene (unsigned Frame);
  
  void Transform (double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw,
					double Tx, double Ty, double Tz, double Tw);
  void Transform (void) { Transform (0, 0, 0, 0, 0, 0,  0, 0, 0, 0); }

  void Redraw ();

  double Benchmark4D (int, double, double, double, bool = true);
  double Benchmark3D (int, double, double, double, bool = true);

public slots:
  void ApplyChanges ();

  void ParametersChanged (double tmin, double tmax, unsigned tsteps,
			  double umin, double umax, unsigned usteps,
			  double vmin, double vmax, unsigned vsteps,
			  double a, double b, double c, double d,
			  QString &func);

protected: 

  virtual Q3PopupMenu * SetupMenu ();

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

# ifdef USE_AUTO_PTR 
    auto_ptr<Function> F;
# else
  Function *F;
# endif  

  QStatusBar *StatusBar;
  QString ObjectName;
  
  double dxy, dxz, dxw, dyz, dyw, dzw,
         dx, dy, dz;
  
  unsigned animation_fps;

  Vector<4> ***Data;

  Vector<3> ***Xscr;
  Vector<4> ***Xtrans;
  Vector<3> *XscrChunk;
  Vector<4> *XtransChunk;
	
	float ***R, ***G, ***B;
	float *RGBChunk;

	unsigned tsteps, usteps, vsteps;
	double CamW, ScrW;
	
	Vector<4> **Cross, **CrossTrans;
    Vector<3> **CrossScr;


  void UpdateStatus (QString = "");

  void AssignValues (const char *Title = 0,
		     const char *Parameter1 = 0,  const char *Parameter2 = 0,
		     const char *Parameter3 = 0,  const char *Parameter4 = 0);

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

protected slots:
  void OnTimer();
  void AnimationSettings();
  
public slots:
  //  menu items
  void Wireframe();
  void Coordinates();
  void HyperFog();
  void Light();
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

};

#endif // !defined(4DVIEW)
