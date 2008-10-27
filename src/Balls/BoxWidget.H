
#if (!defined BOXWIDGET_H)
#define BOXWIDGET_H

#include "Box.H"


const unsigned max_dimension = 9, min_dimension = 3;


class BoxWidget: public QGLWidget {
  Q_OBJECT
public:
  BoxWidget( unsigned dim, unsigned nballs, double,
	     QWidget *parent=0, const char *name=0 );

  void setNumBalls (unsigned _n) { B->setNumBalls (_n); }

  void setElasticity (const double &e) { B->setElasticity (e); }
  void setFriction (const double &f) { B->setFriction (f); }
  void setGravitation (const double &g) { B->setGravitation (g); }

  void setRndSize (bool r) { B->setRndSize (r); }
  void setRMax (const double &r) { B->setRMax (r); }
  
  void setTMax (const double &t) { B->setMaxT (t); }
  void setDeltaT (const double &_dt) { dt = _dt; }
  void setSteps (unsigned _steps_between) { steps_between = _steps_between; }
  
  void setDisplay (bool _display) {
    display = _display;
    if (display) show (); else hide ();
  }
  void setSave(bool r) { save = r; }
  void setSaveName (const QString &n) { saveName = n; }

  void setXCam (const double &_Xcam) { B->setXCam (_Xcam); }
  double *getXCam () { return B->getXCam (); }

  void setDimension (unsigned d) { 
    if (d <= max_dimension && d >= min_dimension) 
      B = BoxArray[d];

    //    B->DefineHypercube ();
    //    B->DrawHypercube (d, vertices);
  
    //    B->setNumBalls (2);
 
  }

  void setRotation (unsigned axis1, unsigned axis2, double phi) {
    B->setRotation (axis1, axis2, phi);
  }
  double getRotation (unsigned axis1, unsigned axis2) {
    return B->getRotation (axis1, axis2);
  }
  
  unsigned getDimension () { return B->getDimension (); }
  unsigned getNumBalls () { return B->getNumBalls (); }

  double getElasticity () { return B->getElasticity (); }
  double getFriction () { return B->getFriction (); }
  double getGravitation () { return B->getGravitation (); }

  bool getRndSize () { return B->getRndSize (); }
  double getRMax () { return B->getRMax (); }
  
  double getTMax () { return B->getMaxT (); }
  double getDeltaT () { return dt; }
  double getSteps () { return steps_between; }
  
  bool getDisplay () { return display; }
  bool getSave() { return save; }
  QString getSaveName () { return saveName; }  

  double getTime () { return B->getT (); }
  unsigned getCollisions () { return B->getCollisions (); }
			
protected:
  void initializeGL();
  void resizeGL( int, int );
  void paintGL();
  void timerEvent( QTimerEvent * );

  void saveImage ();

  BoxBase *BoxArray[max_dimension+1];
  BoxBase *B;

  double dt;
  unsigned steps_between;

  bool save;
  bool display;

  QString saveName;
  
  static int timer_interval;
};

#endif
