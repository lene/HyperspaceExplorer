

#include <qapp.h>
#include <qdesktopwidget.h>

#include "Matrix.H"

#include "BoxWidget.H"
#include "BallsUIImpl.H"


GLint /* ball, */ box;
double t = 0.;

double  rot[][8] = { { 0.0 },
		     { 0.0, 0.0 },
		     { 0.0, 0.0, 0.0 },
		     { 0.0, 0.0, 0.0, 0.0 },
		     { 0.0, 0.0, 0.0, 0.0, 0.0 },
		     { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
		     { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
		     { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } },
       drot[][8] = { { 0.0 },		//  rotation about Z
	 	     { 0.1, 0.0 },	//
		     { 0.4, 0.2, 0.1 },
		     { 0.4, 0.3, 0.2, 0.10 },
		     { 0.4, 0.3, 0.2, 0.10, 0.05 },
		     { 0.5, 0.4, 0.3, 0.20, 0.10, 0.05 },
		     { 0.5, 0.4, 0.3, 0.25, 0.20, 0.10, 0.05 },
		     { 0.5, 0.4, 0.3, 0.25, 0.20, 0.15, 0.10, 0.05 } };
  
GLdouble &view_rotx=rot[1][1], &view_roty=rot[1][0], &view_rotz=rot[0][0],
          &drotx = drot[1][1],  &droty = drot[1][0],  &drotz = drot[0][0];
double  &rot_xw = rot[2][0],  &rot_yw = rot[2][1],  &rot_zw = rot[2][2],
       &drot_xw = rot[2][0], &drot_yw = rot[2][1], &drot_zw = rot[2][2],
       &rot_xyz = rot[3][3], &rot_xyw = rot[3][2], &rot_xzw = rot[3][1],
       &rot_yzw = rot[3][0],
       &drot_xyz = rot[3][3], &drot_xyw = rot[3][2], &drot_xzw = rot[3][1],
       &drot_yzw = rot[3][0];

double rnd () { return double (rand ())/double (RAND_MAX); }

void glMaterial (GLfloat r,GLfloat g,GLfloat b, GLfloat a = 1.0) {
  static GLfloat rgb[4];
  rgb[0] = r;  rgb[1] = g;  rgb[2] = b; rgb[3] = a;
  glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rgb );
}

void help (int argc, char *argv[]) {
  cout << argv[0] << " [--options]\n"
    "--num-balls n				(default 25)\n"
    "--dimension				(default 3)\n"
    "--no-display | --display			(default --display)\n"
    "--delta-t dt				(default 0.001)\n"
    "--steps-between ns				(default 10)\n"
    "--gravity g				(default 0.0)\n"
    "--friction f				(default 0.0)\n"
    "--elasticity e				(default 0.0)\n"
    "--no-random-size | --random-size 		(default --random-size)\n"
    "--rmax R					(default 0.2)\n"
    "--tmax t					(default 100.0)\n"
    "--sloppy-collisions | exact-collisions	(default exact)\n"
    "--no-controls			\n"
    "--xcam	                        	(default 6.0)\n"
    "--drotx dx|--droty dy|--drotz dy 		(default 0.0, 0.1, 0.0)\n"
    "--drotxw dx|--drotyw dy|--drotzw dy 	(default 0.0, 0.0, 0.0)\n"
    "--drotxyz d|--drotxyw d|--drotxzw d|--drotyzw d(default 0.0, 0.0, 0.0, 0.0)\n"
    "--help\n" << endl;
}


void parse (int argc, char *argv[],
	    bool &display, bool &controls, bool &save, bool &fullscreen,
	    unsigned &n, unsigned &dim,
	    double &dt, unsigned &steps_between, double &xcam) {
  for (unsigned i = 1; i < argc; i++) {
    if (QString (argv[i]) == "--num-balls")
      n = QString (argv[++i]).toUInt ();
    else if (QString (argv[i]) == "--dimension")
      dim = QString (argv[++i]).toUInt ();
    else if (QString (argv[i]) == "--xcam")
      xcam = QString (argv[++i]).toDouble ();
    else if (QString (argv[i]) == "--display")
      display = true;
    else if (QString (argv[i]) == "--no-display")
      display = false;
    else if (QString (argv[i]) == "--no-controls")
      controls = false;
    else if (QString (argv[i]) == "--save")
      save = true;
    else if (QString (argv[i]) == "--fullscreen")
      fullscreen = true;
    else if (QString (argv[i]) == "--delta-t")
      dt = QString (argv[++i]).toDouble ();
    else if (QString (argv[i]) == "--steps-between")
      steps_between = QString (argv[++i]).toUInt ();
    else if (QString (argv[i]) == "--gravity")
      BoxBase::setGravitation (QString (argv[++i]).toDouble ());
    else if (QString (argv[i]) == "--friction")
      BoxBase::setFriction (QString (argv[++i]).toDouble ());
    else if (QString (argv[i]) == "--elasticity")
      BoxBase::setElasticity (QString (argv[++i]).toDouble ());
    else if (QString (argv[i]) == "--random-size")
      BoxBase::setRndSize (true);
    else if (QString (argv[i]) == "--no-random-size")
      BoxBase::setRndSize (true);
    else if (QString (argv[i]) == "--rmax")
      BoxBase::setRMax (QString (argv[++i]).toDouble ());
    else if (QString (argv[i]) == "--tmax")
      BoxBase::setMaxT (QString (argv[++i]).toDouble ());
    else if (QString (argv[i]) == "--sloppy-collisions")
      BoxBase::setSloppy (true);
    else if (QString (argv[i]) == "--exact-collisions")
      BoxBase::setSloppy (false);
    else if (QString (argv[i]) == "--drotx")
      ::drotx = QString (argv[++i]).toDouble ();
    else if (QString (argv[i]) == "--droty")
      ::droty = QString (argv[++i]).toDouble ();
    else if (QString (argv[i]) == "--drotz")
      ::drotz = QString (argv[++i]).toDouble ();
    else if (QString (argv[i]) == "--drotxw")
      ::drot_xw = QString (argv[++i]).toDouble ();
    else if (QString (argv[i]) == "--drotyw")
      ::drot_yw = QString (argv[++i]).toDouble ();
    else if (QString (argv[i]) == "--drotzw")
      ::drot_zw = QString (argv[++i]).toDouble ();
    else if (QString (argv[i]) == "--drotxyz")
      ::drot_xyz = QString (argv[++i]).toDouble ();
    else if (QString (argv[i]) == "--drotxyw")
      ::drot_xyw = QString (argv[++i]).toDouble ();
    else if (QString (argv[i]) == "--drotxzw")
      ::drot_xzw = QString (argv[++i]).toDouble ();
    else if (QString (argv[i]) == "--drotyzw")
      ::drot_yzw = QString (argv[++i]).toDouble ();

    else if (QString (argv[i]) == "--help") {
      help (argc, argv); exit (0); }
    
    else {
      cout << "usage:" << endl;
      help (argc,argv);
      cout << "there has been an error ("<< argv[i] << ") in the command line:\n";
      for (unsigned j = 0; j < argc; j++) cout << argv[j] << " ";
      cout << "\ncontinuing anyway. hope this suits you ;-)" << endl;
    }
  }
}


int main (int argc, char *argv[]) {
  QApplication a (argc, argv);

  unsigned n = 10, dim = 3, steps_between = 10;
  double dt = 0.001, _Xcam = 6.;
  bool display = true, controls = true, save = false, fullscreen = false;

  parse (argc, argv, display, controls, save, fullscreen,
	 n, dim, dt, steps_between, _Xcam);

  
  BoxWidget *BW = new BoxWidget (dim, n, _Xcam);
  BW->setDimension (dim);
  BW->setDeltaT (dt);
  BW->setSteps (steps_between);
  BW->setSave (save);
  BW->setDisplay (display);

  BallsUIImpl *UI = new BallsUIImpl (BW);;
  if (!controls) UI->hide ();
  
  if (fullscreen) {
    QDesktopWidget *root = new QDesktopWidget ();
    BW->showFullScreen ();
    BW->setGeometry (root->screenGeometry ());
  }
  a.setMainWidget (BW);

  UI->NumSpheresChanged (n);

  return a.exec ();
}
