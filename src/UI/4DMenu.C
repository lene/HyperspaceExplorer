
//      project:      hyperspace explorer
//      module:       4DMenu.C
//      contains:     menu definitions unique to this application (functions,
//		      4D manipulations, the like)
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include "4DView.H"
#include "Menu4D.H"

#include "Function.H"
#include "Surface.H"
#include "Object.H"
#include "ComplexFunction.H"

#include <qmessagebox.h>
//Added by qt3to4:
#include <Q3PopupMenu>

#include <sstream>
#include <iomanip>

#define TESTFEATURES 1
//#undef TESTFEATURES

using std::ostringstream;
using std::cerr;
using std::endl;
using std::ends;

using VecMath::Vector;

/*******************************************************************************
 *  menu callback functions
 */

/** toggle fog/depth cue */
void C4DView::Fog () {
  fog = !fog;
  menu->getAction("Depth Cue")->setChecked(fog);
  InitFog ();
  repaint (); }


/** toggle object transparency */
void C4DView::Transparent () {
  transparent = !transparent;
  menu->getAction("Transparence")->setChecked(transparent);
  InitTransparence ();
  repaint (); }


/** toggle shading */
void C4DView::Shade () {
  shade = !shade;
  menu->getAction("Shading")->setChecked(shade);
  InitShade ();
  repaint (); }


/** toggle colors */
void C4DView::Colors () {
  colors = !colors;
  menu->getAction("Colors")->setChecked(colors);
  initializeGL ();
  repaint (); }


/** switch between wireframe and solid display
 *  account for antialiasing only in WF mode
 *  change menu items accordingly                                             */
void C4DView::Wireframe() {
    if (DisplayPolygons) {
        menu->getAction("Wireframe")->setText("Solid");
        menu->getAction("Transparence")->setText("Line Antialiasing");
    } else {
        transparent = true;;
        Transparent ();
        menu->getAction("Wireframe")->setText("Wireframe");
        menu->getAction("Transparence")->setText("Transparence");
        glDisable (GL_CULL_FACE);
    }
    menu->getAction("Wireframe")->setChecked (DisplayPolygons);
    SetWireframe (DisplayPolygons);

    OnPaint ();
}


/*******************************************************************************
 *  switch coordinate cross on or off
 *  change menu items accordingly
 */
void C4DView::Coordinates() {
    DisplayCoordinates = !DisplayCoordinates;
    menu->getAction("Coordinate Cross")->setChecked (DisplayCoordinates);
  
    Redraw ();
}


/*******************************************************************************
 *  switch 4D depth cue on or off
 *  change menu items accordingly
 */
void C4DView::HyperFog() {
    DepthCue4D = !DepthCue4D;
    menu->getAction("4D Depth Cue")->setChecked (DepthCue4D);
  
    Redraw ();
}

/*******************************************************************************
 *  switch lighting on or off
 *  change menu items accordingly
 */
void C4DView::Light() {
    Lighting = !Lighting;
    if (Lighting) {
        glEnable(GL_LIGHTING);                  //  turn on the light
 
        static GLfloat LightAmbient[]  = { 0.3f, 0.3f, 0.3f, 1.0f }, //  HARDCODED VALUES
                       LightDiffuse[]  = { 0.9f, 0.9f, 0.9f, 1.0f },
	               LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f },
	               LightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f }; //  light properties
 
        glLightfv (GL_LIGHT0, GL_AMBIENT, LightAmbient); // set the light properties
        glLightfv (GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
        glLightfv (GL_LIGHT0, GL_SPECULAR, LightSpecular);
        glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);
        glEnable  (GL_LIGHT0);   // turn on the light
    } else {
        static GLfloat LightAmbient[]  = { 1.0f, 1.0f, 1.0f, 0.0f },
                       LightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f }; //      light properties
      
        glEnable  (GL_LIGHTING);
        glLightfv (GL_LIGHT0, GL_AMBIENT, LightAmbient); // set the light properties
        glLightfv (GL_LIGHT0, GL_DIFFUSE, LightAmbient);
        glLightfv (GL_LIGHT0, GL_SPECULAR, LightAmbient);
        glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);
        glEnable  (GL_LIGHT0);    //      turn on the light
    }
  
    OnPaint ();
}


/*******************************************************************************
 *  switch rendering to files on or off
 *  change menu items accordingly
 */
void C4DView::RenderToImages() {
  RenderToPixmap = !RenderToPixmap; 
  menu->getAction("Render to Images")->setChecked(RenderToPixmap);
}


/*******************************************************************************
 */
void C4DView::AnimationSettings() {
  cerr << "C4DView::AnimationSettings() is not yet implemented!" << endl;
}

/*******************************************************************************
 *  run a benchmark test
 */
void C4DView::Benchmark() {
  ostringstream Time;

  double time_4d = Benchmark4D (360, 1., 0., 0.);

  Time << "4D viewpoint rotation: " << time_4d << " sec." 
       << " (" << 360/1./time_4d << " fps)" << endl;
  
  float time_3d = Benchmark3D (360, 1., 0., 0.);
  
  Time << "3D viewpoint rotation: " << time_3d << " sec." 
       << " (" << 360/1./time_3d << " fps)" << ends;
  
  QMessageBox::information (NULL, "Benchmark results", Time.str ().c_str ());
  UpdateStatus ();
}


/*******************************************************************************
 *  rotate in 4D 360 degrees
 */
double C4DView::Benchmark4D (int num_steps,
			     double step_xw, double step_yw, double step_zw,
			     bool display) {
  clock_t stime = clock ();					//  record start time

  double Rxw = 0., Ryw = 0., Rzw = 0.; 
  
  for (int step = 0; step < num_steps; step++) {
    Rxw += step_xw; Ryw += step_yw; Rzw += step_zw; 
    Transform (0., 0. ,Rxw, 0. , Ryw, Rzw, 0., 0., 0., 0.);
    if (display) {
      Redraw ();
      UpdateStatus (QString::number ((100*step)/num_steps)+"% done");
    }
  }
  
  return double (clock ()-stime)/CLOCKS_PER_SEC;  
}


/*******************************************************************************
 *  rotate in 3D 360 degrees
 */
double C4DView::Benchmark3D (int num_steps,
			     double step_x, double step_y, double step_z,
			     bool display) {
  clock_t stime = clock ();					//  record start time

  double Rx = m_rotX, Ry = m_rotY, Rz = m_rotZ; 
  
  for (int step = 0; step < num_steps; step++) {
    m_rotX += step_x; m_rotY += step_y; m_rotZ += step_z; 
    if (display) {
      OnPaint ();
      UpdateStatus (QString::number ((100*step)/num_steps)+"% done");
    }
  }
  m_rotX = Rx; m_rotY = Ry;  m_rotZ = Rz;
	
  return double (clock ()-stime)/CLOCKS_PER_SEC;  
}

/*******************************************************************************
 *  display a Fr3r object
 */
void C4DView::FunctionFr3r() {
  menu->updateFunctionMenu (0);

# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new Fr3r (Values->tmin (), Values->tmax (), Values->dt (),
		 Values->umin (), Values->umax (), Values->du (),
		 Values->vmin (), Values->vmax (), Values->dv ()));

  AssignValues ("Some Function");
	 
  Redraw ();
}


/*******************************************************************************
 *  display a Hypersphere object
 */
void C4DView::FunctionHypersphere() {
  menu->updateFunctionMenu(2);


# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new Hypersphere (Values->tmin (), Values->tmax (), Values->dt (),
			Values->umin (), Values->umax (), Values->du (),
			Values->vmin (), Values->vmax (), Values->dv (),
			Values->a ()));

  AssignValues ("Hypersphere", "Radius");

  Redraw ();
}


/*******************************************************************************
 *  display a Torus1 object
 */
void C4DView::FunctionTorus1() {
  menu->updateFunctionMenu(3);

# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new Torus1 (Values->tmin (), Values->tmax (), Values->dt (),
		   Values->umin (), Values->umax (), Values->du (),
		   Values->vmin (), Values->vmax (), Values->dv (),
		   Values->a (), Values->b (), Values->c ()));
  
  AssignValues ("Torus 1", "Major Radius", "Minor Radius", "Micro Radius");
  
  Redraw ();
}

 
/*******************************************************************************
 *  display a Torus2 object
 */
void C4DView::FunctionTorus2() {
  menu->updateFunctionMenu(4);

# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new Torus2 (Values->tmin (), Values->tmax (), Values->dt (),
		   Values->umin (), Values->umax (), Values->du (),
		   Values->vmin (), Values->vmax (), Values->dv (),
		   Values->a (), Values->b ()));
  
  AssignValues ("Torus 2", "Major Radius", "Minor Radius");
  
  Redraw ();
}


/*******************************************************************************
 *  display a Fr3r object
 */
void C4DView::FR3R(){
  menu->updateFunctionMenu(4);

# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif 
      (new Fr3r (Values->tmin (), Values->tmax (), Values->dt (),
		 Values->umin (), Values->umax (), Values->du (),
		 Values->vmin (), Values->vmax (), Values->dv ()));
  
  AssignValues ("f (r) = 1/(r²+1/4)");
  
  Redraw ();
}


/*******************************************************************************
 *  display a GravPotential object
 */
void C4DView::GravPotential(){
  menu->updateFunctionMenu(4);

# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif 
       (new GravitationPotential (Values->tmin (), Values->tmax (), Values->dt (),
				  Values->umin (), Values->umax (), Values->du (),
				  Values->vmin (), Values->vmax (), Values->dv (),
				  Values->a (), Values->b ()));
  
  AssignValues ("Gravitation Potential", "M", "R");
  
  Redraw ();
}


/*******************************************************************************
 *  display a SinR object
 */
void C4DView::SinR(){
  menu->updateFunctionMenu(4);

# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new Fr3rSin (Values->tmin (), Values->tmax (), Values->dt (),
		    Values->umin (), Values->umax (), Values->du (),
		    Values->vmin (), Values->vmax (), Values->dv ()));
  
  AssignValues ("sin (r²)");
  
  Redraw ();
}


/*******************************************************************************
 *  display a ExpR object
 */
void C4DView::ExpR(){
  menu->updateFunctionMenu(4);

# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new Fr3rExp (Values->tmin (), Values->tmax (), Values->dt (),
		    Values->umin (), Values->umax (), Values->du (),
		    Values->vmin (), Values->vmax (), Values->dv ()));
  
  AssignValues ("exp (r²)");
  
  Redraw ();
}


/*******************************************************************************
 *  display a Sin object
 */
void C4DView::Sin(){
  menu->updateFunctionMenu(4);

# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif  
      (new PolarSin (Values->tmin (), Values->tmax (), Values->dt (),
		     Values->umin (), Values->umax (), Values->du (),
		     Values->vmin (), Values->vmax (), Values->dv (),
		     Values->a ()));
  
  AssignValues ("r = sin (...)", "Phase");
  
  Redraw ();
}


/*******************************************************************************
 *  display a Sin2 object
 */
void C4DView::Sin2(){
  menu->updateFunctionMenu(4);

# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new PolarSin2 (Values->tmin (), Values->tmax (), Values->dt (),
		      Values->umin (), Values->umax (), Values->du (),
		      Values->vmin (), Values->vmax (), Values->dv ()));
  
  AssignValues ("r = sin (...)");
  
  Redraw ();
}


/*******************************************************************************
 *  display a FunctionR object
 */
void C4DView::FunctionR(){
  menu->updateFunctionMenu(4);

# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new PolarR (Values->tmin (), Values->tmax (), Values->dt (),
		   Values->umin (), Values->umax (), Values->du (),
		   Values->vmin (), Values->vmax (), Values->dv (),
		   Values->a ()));
  
  AssignValues ("r", "Phase");
  
  Redraw ();
}


/*******************************************************************************
 *  display a ObjectHypercube object
 */
void C4DView::ObjectHypercube() {
  menu->updateFunctionMenu(1);

# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
            (new Hypercube (Vector<4>(0., 0., 0., 0.), Values->a ()));

  AssignValues ("Hypercube", "Size");
  
  Redraw ();
}


/*******************************************************************************
 *  display a ObjectHyperpyramid object
 */
void C4DView::ObjectHyperpyramid() {
  menu->updateFunctionMenu(1);

# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
            (new Pyramid (Vector<4>(0., 0., 0., 0.), 2.*Values->a ()));

  AssignValues ("Hyperpyramid", "Size");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a ObjectHypersponge object
 */
void C4DView::ObjectHypersponge() {
    menu->updateFunctionMenu(1);

#   ifdef USE_AUTO_PTR
        F.reset
#   else
        if (F) delete F;
        F =
#   endif
            (new Sponge (
                unsigned (Values->a ()), int (Values->b ()), 
                Values->c (), Vector<4>(0., 0., 0., 0.))
            );

    AssignValues ("4-dimensional Menger Sponge", "Level", "Distance", "Size");
  
    Redraw ();
}


/*******************************************************************************
 *  display a ObjectGasket object
 */
void C4DView::ObjectGasket() {
  menu->updateFunctionMenu(1);

# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
            (new Gasket (unsigned (Values->a ()), 2.*Values->b (), Vector<4>(0., 0., 0., 0.)));

  AssignValues ("4-dimensional Sierpinski Gasket", "Level", "Size");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a Surface object
 */
void C4DView::Surface_1() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new Surface1 (Values->tmin (), Values->tmax (), Values->dt (),
		     Values->umin (), Values->umax (), Values->du ()));

  AssignValues ("Surface");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a SurfaceHorizon object
 */
void C4DView::SurfaceHorizon() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif 
      (new Horizon (Values->tmin (), Values->tmax (), Values->dt (),
		    Values->umin (), Values->umax (), Values->du ()));

  AssignValues ("Horizon");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a SurfaceTorus3 object
 */
void C4DView::SurfaceTorus3() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif 
      (new Torus3 (Values->tmin (), Values->tmax (), Values->dt (),
		   Values->umin (), Values->umax (), Values->du ()));

  AssignValues ("Torus");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a ComplexZ2 object
 */
void C4DView::ComplexZ2() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new z3 (Values->tmin (), Values->tmax (), Values->dt (),
	       Values->umin (), Values->umax (), Values->du ()));

  AssignValues ("z²");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a ComplexZ3 object
 */
void C4DView::ComplexZ3() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new z3 (Values->tmin (), Values->tmax (), Values->dt (),
	       Values->umin (), Values->umax (), Values->du ()));

  AssignValues ("z³");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a ComplexZA object
 */
void C4DView::ComplexZA() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new zA (Values->tmin (), Values->tmax (), Values->dt (),
	       Values->umin (), Values->umax (), Values->du (),
	       Values->a ()));

  AssignValues ("z^a", "a");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a ComplexEZ object
 */
void C4DView::ComplexEZ() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new ez (Values->tmin (), Values->tmax (), Values->dt (),
	       Values->umin (), Values->umax (), Values->du (),
	       Values->a ()));

  AssignValues ("e^a*z", "a");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a ComplexEMZ2 object
 */
void C4DView::ComplexEMZ2() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif  
      (new emz2 (Values->tmin (), Values->tmax (), Values->dt (),
		 Values->umin (), Values->umax (), Values->du (),
		 Values->a ()));

  AssignValues ("e^-a*z²", "a");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a ComplexZM1 object
 */
void C4DView::ComplexZM1() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif 
      (new zm1 (Values->tmin (), Values->tmax (), Values->dt (),
		Values->umin (), Values->umax (), Values->du ()));

  AssignValues ("1/z");
  
  Redraw ();
}


/*******************************************************************************
 *  display a ComplexZM2 object
 */
void C4DView::ComplexZM2() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new zm2 (Values->tmin (), Values->tmax (), Values->dt (),
		Values->umin (), Values->umax (), Values->du ()));

  AssignValues ("1/z²");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a ComplexSqrtZ object
 */
void C4DView::ComplexSqrtZ() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif 
      (new sqrtz (Values->tmin (), Values->tmax (), Values->dt (),
		  Values->umin (), Values->umax (), Values->du ()));

  AssignValues ("sqrt (z)");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a ComplexLnZ object
 */
void C4DView::ComplexLnZ() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new lnz (Values->tmin (), Values->tmax (), Values->dt (),
		Values->umin (), Values->umax (), Values->du ()));

  AssignValues ("ln z");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a ComplexSinZ object
 */
void C4DView::ComplexSinZ() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new sinz (Values->tmin (), Values->tmax (), Values->dt (),
		 Values->umin (), Values->umax (), Values->du ()));

  AssignValues ("sin z");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a ComplexCosZ object
 */
void C4DView::ComplexCosZ() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new cosz (Values->tmin (), Values->tmax (), Values->dt (),
		 Values->umin (), Values->umax (), Values->du ()));

  AssignValues ("cos z");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a ComplexSinhZ object
 */
void C4DView::ComplexSinhZ() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new sinhz (Values->tmin (), Values->tmax (), Values->dt (),
		  Values->umin (), Values->umax (), Values->du ()));

  AssignValues ("sinh z");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a ComplexCoshZ object
 */
void C4DView::ComplexCoshZ() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new coshz (Values->tmin (), Values->tmax (), Values->dt (),
		  Values->umin (), Values->umax (), Values->du ()));

  AssignValues ("cosh z");
  
  Redraw ();
} 


/*******************************************************************************
 *  display a ComplexTanZ object
 */
void C4DView::ComplexTanZ() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif 
      (new tanz (Values->tmin (), Values->tmax (), Values->dt (),
		 Values->umin (), Values->umax (), Values->du ()));

  AssignValues ("tan z");
  
  Redraw ();
} 



#include "FunctionDialogImpl.H"
#include "PolarDialogImpl.H"
#include "ComplexDialogImpl.H"
#include "SurfaceDialogImpl.H"

#include "CustomFunction.H"


/*******************************************************************************
 *  display a customFunction object
 */
void C4DView::customFunction() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new CustomFunction (Values->tmin (), Values->tmax (), Values->dt (),
			   Values->umin (), Values->umax (), Values->du (),
			   Values->vmin (), Values->vmax (), Values->dv ()));
# ifdef USE_AUTO_PTR
    QString sym (((CustomFunction *)F.get ())->symbolic());
# else
    QString sym (((CustomFunction *)F)->symbolic());
# endif    
  AssignValues (sym);
  
  Redraw ();
}


/*******************************************************************************
 *  display a customPolarFunction object
 */
void C4DView::customPolarFunction() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new CustomPolarFunction (Values->tmin (), Values->tmax (), Values->dt (),
				Values->umin (), Values->umax (), Values->du (),
				Values->vmin (), Values->vmax (), Values->dv ()));
# ifdef USE_AUTO_PTR
    QString sym (((CustomPolarFunction *)F.get ())->symbolic());
# else
    QString sym (((CustomPolarFunction *)F)->symbolic());
# endif    
  AssignValues (sym);
  
  Redraw ();
  //  PolarDialog *PolarDlg = new PolarDialogImpl;
}


/*******************************************************************************
 *  display a customComplexFunction object
 */
void C4DView::customComplexFunction() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new CustomComplexFunction (Values->tmin (), Values->tmax (), Values->dt (),
				  Values->umin (), Values->umax (), Values->du ()));
# ifdef USE_AUTO_PTR
    QString sym (((CustomComplexFunction *)F.get ())->symbolic());
# else
    QString sym (((CustomComplexFunction *)F)->symbolic());
# endif    
  AssignValues (sym);
  
  Redraw ();
  //  ComplexDialog *ComplexDlg = new ComplexDialogImpl;
}


/*******************************************************************************
 *  display a customSurface object
 */
void C4DView::customSurface() {
# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
      (new CustomSurface (Values->tmin (), Values->tmax (), Values->dt (),
			  Values->umin (), Values->umax (), Values->du ()));
# ifdef USE_AUTO_PTR
    QString sym (((CustomSurface *)F.get ())->symbolic());
# else
    QString sym (((CustomSurface *)F)->symbolic());
# endif    
  AssignValues (sym);
  
  Redraw ();
  //  SurfaceDialog *SurfaceDlg = new SurfaceDialogImpl;
}

/*
void C4DView::OnUpdateFunctionFr3r () {
    menu->setItemEnabled (0, dynamic_cast <Fr3r *> (F) != NULL);
}
*/

