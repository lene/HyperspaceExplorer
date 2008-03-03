
//      project:      hyperspace explorer
//      module:       4DMenu.C
//      contains:     menu definitions unique to this application (functions,
//		      4D manipulations, the like)
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include "4DView.H"
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

inline void TESTED_FEATURE (Q3PopupMenu *menu, int item) {
# ifdef TESTFEATURES
    menu->setItemEnabled (item, true);
# else
    menu->setItemEnabled (item, false);
#endif
}

    ////////////////////////////////////////////////////////////////////////////////
    //
    //	C4DView menu handling
    //
    ////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *  create the menu 
 *  @return		the menu
 */
Q3PopupMenu * C4DView::SetupMenu () {
    menu = XQGLWidget::SetupMenu ();

    functions = new Q3PopupMenu;
    animation = new Q3PopupMenu;

    Q3PopupMenu *fr3r = new Q3PopupMenu,
               *objects = new Q3PopupMenu,
               *surfaces = new Q3PopupMenu,
               *fcc = new Q3PopupMenu;

    fr3r->insertItem ("1/(r²+1)", this, SLOT(FR3R()));
    fr3r->insertItem ("Gravitation Potential", this, SLOT(GravPotential()));
    fr3r->insertItem ("sin (r²)", this, SLOT(SinR()));
    fr3r->insertItem ("exp (r²)", this, SLOT(ExpR()));
    int tmp = fr3r->insertItem ("Custom function", this, SLOT(customFunction()));    
    //    TESTED_FEATURE (fr3r, tmp);

    fr3r->insertItem ("Polar: r = sin (pi/3.*(t+u+v))", this, SLOT(Sin2()));
    fr3r->insertItem ("Polar: r = 1/2+sin (Phase*pi*t*u*v)", this, SLOT(Sin()));
    fr3r->insertItem ("Polar: r = sqrt (t²+u²+v²)", this, SLOT(FunctionR()));
    tmp = fr3r->insertItem ("Custom polar function", this, SLOT(customPolarFunction()));
    //    TESTED_FEATURE (fr3r, tmp);

    objects->insertItem ("Hypersphere", this, SLOT(FunctionHypersphere()));
    objects->insertItem ("Hypercube", this, SLOT(ObjectHypercube()));
    objects->insertItem ("Hyperpyramid", this, SLOT(ObjectHyperpyramid()));
    objects->insertItem ("Menger Sponge", this, SLOT(ObjectHypersponge()));
    objects->insertItem ("Sierpinski Gasket", this, SLOT(ObjectGasket()));
    objects->insertItem ("Torus 1", this, SLOT(FunctionTorus1()));
    objects->insertItem ("Torus 2", this, SLOT(FunctionTorus2()));
    surfaces->insertItem ("Surface1", this, SLOT(Surface_1()));
    surfaces->insertItem ("Horizon", this, SLOT(SurfaceHorizon()));
    surfaces->insertItem ("Torus 3", this, SLOT(SurfaceTorus3()));
    tmp = surfaces->insertItem ("Custom surface", this, SLOT(customSurface()));
    TESTED_FEATURE (surfaces, tmp);

    fcc->insertItem ("z²", this, SLOT(ComplexZ2()));
    fcc->insertItem ("z³", this, SLOT(ComplexZ3()));
    fcc->insertItem ("z^a", this, SLOT(ComplexZA()));
    fcc->insertItem ("e^z", this, SLOT(ComplexEZ()));
    fcc->insertItem ("e^-z²", this, SLOT(ComplexEMZ2()));
    fcc->insertItem ("1/z", this, SLOT(ComplexZM1()));
    fcc->insertItem ("1/z²", this, SLOT(ComplexZM2()));
    fcc->insertItem ("sqrt (z)", this, SLOT(ComplexSqrtZ()));
    fcc->insertItem ("ln (z)", this, SLOT(ComplexLnZ()));
    fcc->insertItem ("sin (z)", this, SLOT(ComplexSinZ()));
    fcc->insertItem ("cos (z)", this, SLOT(ComplexCosZ()));
    fcc->insertItem ("sinh (z)", this, SLOT(ComplexSinhZ()));
    fcc->insertItem ("cosh (z)", this, SLOT(ComplexCoshZ()));
    fcc->insertItem ("tan (z)", this, SLOT(ComplexTanZ()));
    tmp = fcc->insertItem ("Custom complex function", this, SLOT(customComplexFunction()));
    TESTED_FEATURE (fcc, tmp);

    functions->insertItem ("f: R³ -> R", fr3r, -1, 0);
    functions->insertItem ("Objects", objects, -1, 1);
    surfaces->insertItem ("f: C -> C", fcc, -1, 0);
    functions->insertItem ("Surfaces", surfaces, -1, 2);
    
    functions->setCheckable (true);
    
    linesID = appear->insertItem ("Wireframe", this, SLOT(Wireframe()));
    crossID = appear->insertItem ("Coordinate Cross", this, SLOT(Coordinates()));
    appear->setItemChecked (crossID, DisplayCoordinates); 
    pixmapID = animation->insertItem ("Render to Images", this, SLOT(RenderToImages()));
    animation->setItemChecked (pixmapID, RenderToPixmap);
    TESTED_FEATURE (animation, pixmapID);

    tmp = animation->insertItem ("Animation Settings", this, SLOT(AnimationSettings()));
    TESTED_FEATURE (animation, tmp);
    
#   if (QT_VERSION < 300)
      animation->insertItem ("Benchmark", this, SLOT (Benchmark()), 0, -1, 2);
#   else
      animation->insertItem ("Benchmark", this, SLOT (Benchmark()), (const QKeySequence &)0, -1, 2);
#   endif      

#   if (QT_VERSION < 300)
      hyperfogID = appear->insertItem ("4D Depth Cue", this, SLOT(HyperFog()), 0, -1, 3);
#   else
      hyperfogID = appear->insertItem ("4D Depth Cue", this, SLOT(HyperFog()), (const QKeySequence &)0, -1, 3);
#   endif
    
    menu->insertItem ("Object", functions, -1, 0);
      
    menu->insertItem ("Animation", animation, -1, 2);

      if (DisplayPolygons) {
	appear->changeItem (linesID, "Solid");
	appear->changeItem (transparentID, "Line Antialiasing");
	appear->setItemEnabled (transparentID, true);
      }
      else {
	appear->changeItem (linesID, "Wireframe");
	appear->changeItem (transparentID, "Transparence");
	TESTED_FEATURE (appear, transparentID);	
      }
      //      appear->setItemEnabled (transparentID, DisplayPolygons);
      SetWireframe (DisplayPolygons);

      return menu;
}


/*******************************************************************************
 *  menu callback functions
 */


/*******************************************************************************
 *  switch between wireframe and solid display
 *  account for antialiasing only in WF mode
 *  change menu items accordingly
 */
void C4DView::Wireframe() {
  if (DisplayPolygons) {
    appear->changeItem (linesID, "Solid");
    appear->changeItem (transparentID, "Line Antialiasing");
  }
  else {
    transparent = true;;
    Transparent ();
    appear->changeItem (linesID, "Wireframe");
    appear->changeItem (transparentID, "Transparence");
    glDisable (GL_CULL_FACE);
  }
  appear->setItemEnabled (transparentID, DisplayPolygons);
  SetWireframe (DisplayPolygons);

  OnPaint ();
}


/*******************************************************************************
 *  switch coordinate cross on or off
 *  change menu items accordingly
 */
void C4DView::Coordinates() {
  DisplayCoordinates = !DisplayCoordinates;
  appear->setItemChecked (crossID, DisplayCoordinates); 
  
  Redraw ();
}


/*******************************************************************************
 *  switch 4D depth cue on or off
 *  change menu items accordingly
 */
void C4DView::HyperFog() {
  DepthCue4D = !DepthCue4D;
  appear->setItemChecked (hyperfogID, DepthCue4D);
  
  Redraw ();
}

/*******************************************************************************
 *  switch lighting on or off
 *  change menu items accordingly
 */
void C4DView::Light() {
  Lighting = !Lighting;
  if (Lighting) {
    glEnable(GL_LIGHTING);					//      turn on the light
 
    static GLfloat LightAmbient[]  = { 0.3f, 0.3f, 0.3f, 1.0f }, //	HARDCODED VALUES
      LightDiffuse[]  = { 0.9f, 0.9f, 0.9f, 1.0f },
	LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f },
	  LightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f }; //      light properties
 
	  glLightfv (GL_LIGHT0, GL_AMBIENT, LightAmbient); 		//     set the light properties
	  glLightfv (GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	  glLightfv (GL_LIGHT0, GL_SPECULAR, LightSpecular);
	  glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);
	  glEnable  (GL_LIGHT0);					//      turn on the light
  }
  else {
    static GLfloat LightAmbient[]  = { 1.0f, 1.0f, 1.0f, 0.0f },
      LightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f }; //      light properties
      
      glEnable  (GL_LIGHTING);
      glLightfv (GL_LIGHT0, GL_AMBIENT, LightAmbient); 		//     set the light properties
      glLightfv (GL_LIGHT0, GL_DIFFUSE, LightAmbient); 
      glLightfv (GL_LIGHT0, GL_SPECULAR, LightAmbient); 
      glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);
      glEnable  (GL_LIGHT0);					//      turn on the light
  }
  
  OnPaint (); 
}


/*******************************************************************************
 *  switch rendering to files on or off
 *  change menu items accordingly
 */
void C4DView::RenderToImages() {
  RenderToPixmap = !RenderToPixmap; 
  animation->setItemChecked (pixmapID, RenderToPixmap);   
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
 *  rotate in 3D 360 degrees
 */
void C4DView::UpdateFunctionMenu (int Item) {
  /*  for (unsigned i = 0; i < 32; i++)
      functions->setItemChecked (i, false);
  */
  functions->setItemChecked (Item, true);
}


/*******************************************************************************
 *  display a Fr3r object
 */
void C4DView::FunctionFr3r() {
  UpdateFunctionMenu (0);

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
  UpdateFunctionMenu (2);


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
  UpdateFunctionMenu (3);

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
  UpdateFunctionMenu (4);

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
  UpdateFunctionMenu (4);

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
  UpdateFunctionMenu (4);

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
  UpdateFunctionMenu (4);

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
  UpdateFunctionMenu (4);

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
  UpdateFunctionMenu (4);

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
  UpdateFunctionMenu (4);

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
  UpdateFunctionMenu (4);

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
  UpdateFunctionMenu (1);

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
  UpdateFunctionMenu (1);

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
  UpdateFunctionMenu (1);

# ifdef USE_AUTO_PTR
  F.reset
# else
    if (F) delete F;
    F =
#endif
            (new Sponge (unsigned (Values->a ()), int (Values->b ()), Values->c (), Vector<4>(0., 0., 0., 0.))); 	// valgrind bemoans "601248 bytes in 1 blocks are indirectly lost"


  AssignValues ("4-dimensional Menger Sponge", "Level", "Distance", "Size");
  
  Redraw ();
}


/*******************************************************************************
 *  display a ObjectGasket object
 */
void C4DView::ObjectGasket() {
  UpdateFunctionMenu (1);

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

