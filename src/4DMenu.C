
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include "4DView.H"
#include "Function.H"
#include "Surface.H"
#include "Object.H"
#include "ComplexFunction.H"

#include <qmessagebox.h>

#include <sstream>
#include <iomanip>
/*
struct FunctionTableEntry {
  QString FunctionName;
  Function *FunctionPtr;
};

FunctionTableEntry FuncTable[] = {
  "Hypersphere", new 
*/

//#define TESTFEATURES 1
#undef TESTFEATURES

inline void TESTED_FEATURE (QPopupMenu *menu, int item) {
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

QPopupMenu * C4DView::SetupMenu () {
    menu = XQGLWidget::SetupMenu ();

    functions = new QPopupMenu;
    animation = new QPopupMenu;

    QPopupMenu *fr3r = new QPopupMenu,
               *objects = new QPopupMenu,
               *surfaces = new QPopupMenu,
               *fcc = new QPopupMenu;

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


void C4DView::Coordinates() {
  DisplayCoordinates = !DisplayCoordinates;
  appear->setItemChecked (crossID, DisplayCoordinates); 
  
  Redraw ();
}

void C4DView::HyperFog() {
  DepthCue4D = !DepthCue4D;
  appear->setItemChecked (hyperfogID, DepthCue4D);
  
  Redraw ();
}

void C4DView::Light() {
  Lighting = !Lighting;
  if (Lighting) {
    glEnable(GL_LIGHTING);					//      turn on the light
 
    static GLfloat LightAmbient[]  = { 0.3f, 0.3f, 0.3f, 1.0f },
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

void C4DView::RenderToImages() {
  RenderToPixmap = !RenderToPixmap; 
  animation->setItemChecked (pixmapID, RenderToPixmap);   
}

void C4DView::AnimationSettings() {
  cerr << "C4DView::AnimationSettings() is not yet implemented!" << endl;
}

void C4DView::Benchmark() {
  clock_t stime = clock ();					//  record start time
  const double DegreeStep=1;
  
  for (double Rxw = 0.01; Rxw <= 360.01; Rxw += DegreeStep) { 
    Transform (0,0,Rxw,0,Rxw,Rxw,0,0,0,0);
    Redraw ();
    UpdateStatus (QString::number (unsigned (50*Rxw/360.))+"% done");
  }
	
  float xtime = float (clock ()-stime)/CLOCKS_PER_SEC; 
  
  ostringstream Time;
  Time << "4D viewpoint rotation: " << xtime << " sec." 
       << " (" << 360/DegreeStep/xtime << " fps)" << endl;
  
  stime = clock ();
  for (double Rz = 0; Rz <= 360; Rz += DegreeStep) {
    m_rotZ = Rz;
    OnPaint ();
    UpdateStatus (QString::number (unsigned (50*Rz/360.)+50)+"% done");
  }
  
  xtime = float (clock ()-stime)/CLOCKS_PER_SEC; 
  
  Time << "3D viewpoint rotation: " << xtime << " sec." 
       << " (" << 360/DegreeStep/xtime << " fps)" << ends;
  
  QMessageBox::information (NULL, "Benchmark results", Time.str ().c_str ());
  UpdateStatus ();
}

void C4DView::UpdateFunctionMenu (int Item) {
  /*  for (unsigned i = 0; i < 32; i++)
      functions->setItemChecked (i, false);
  */
  functions->setItemChecked (Item, true);
}

void C4DView::FunctionFr3r() {
  UpdateFunctionMenu (0);

  if (F) delete F;
  F = new Fr3r (Values->tmin (), Values->tmax (), Values->dt (),
		Values->umin (), Values->umax (), Values->du (),
		Values->vmin (), Values->vmax (), Values->dv ());

  AssignValues ("Some Function");
	 
  Redraw ();
}

void C4DView::FunctionHypersphere() {
  UpdateFunctionMenu (2);

  if (F) delete F;
  F = new Hypersphere (Values->tmin (), Values->tmax (), Values->dt (),
		       Values->umin (), Values->umax (), Values->du (),
		       Values->vmin (), Values->vmax (), Values->dv (),
		       Values->a ());

  AssignValues ("Hypersphere", "Radius");

  Redraw ();
}


void C4DView::FunctionTorus1() {
  UpdateFunctionMenu (3);

  if (F) delete F;
  F = new Torus1 (Values->tmin (), Values->tmax (), Values->dt (),
		  Values->umin (), Values->umax (), Values->du (),
		  Values->vmin (), Values->vmax (), Values->dv (),
		  Values->a (), Values->b (), Values->c ());
  
  AssignValues ("Torus 1", "Major Radius", "Minor Radius", "Micro Radius");
  
  Redraw ();
}

 
void C4DView::FunctionTorus2() {
  UpdateFunctionMenu (4);

  if (F) delete F;
  F = new Torus2 (Values->tmin (), Values->tmax (), Values->dt (),
		  Values->umin (), Values->umax (), Values->du (),
		  Values->vmin (), Values->vmax (), Values->dv (),
		  Values->a (), Values->b ());
  
  AssignValues ("Torus 2", "Major Radius", "Minor Radius");
  
  Redraw ();
}

void C4DView::FR3R(){
  UpdateFunctionMenu (4);

  if (F) delete F;
  F = new Fr3r (Values->tmin (), Values->tmax (), Values->dt (),
		Values->umin (), Values->umax (), Values->du (),
		Values->vmin (), Values->vmax (), Values->dv ());
  
  AssignValues ("f (r) = 1/(r²+1/4)");
  
  Redraw ();
}
void C4DView::GravPotential(){
  UpdateFunctionMenu (4);

  if (F) delete F;
  F = new GravitationPotential (Values->tmin (), Values->tmax (), Values->dt (),
				Values->umin (), Values->umax (), Values->du (),
				Values->vmin (), Values->vmax (), Values->dv (),
				Values->a (), Values->b ());
  
  AssignValues ("Gravitation Potential", "M", "R");
  
  Redraw ();
}
void C4DView::SinR(){
  UpdateFunctionMenu (4);

  if (F) delete F;
  F = new Fr3rSin (Values->tmin (), Values->tmax (), Values->dt (),
		   Values->umin (), Values->umax (), Values->du (),
		   Values->vmin (), Values->vmax (), Values->dv ());
  
  AssignValues ("sin (r²)");
  
  Redraw ();
}
void C4DView::ExpR(){
  UpdateFunctionMenu (4);

  if (F) delete F;
  F = new Fr3rExp (Values->tmin (), Values->tmax (), Values->dt (),
		   Values->umin (), Values->umax (), Values->du (),
		   Values->vmin (), Values->vmax (), Values->dv ());
  
  AssignValues ("exp (r²)");
  
  Redraw ();
}
void C4DView::Sin(){
  UpdateFunctionMenu (4);

  if (F) delete F;
  F = new PolarSin (Values->tmin (), Values->tmax (), Values->dt (),
		    Values->umin (), Values->umax (), Values->du (),
		    Values->vmin (), Values->vmax (), Values->dv (),
		    Values->a ());
  
  AssignValues ("r = sin (...)", "Phase");
  
  Redraw ();
}
void C4DView::Sin2(){
  UpdateFunctionMenu (4);

  if (F) delete F;
  F = new PolarSin2 (Values->tmin (), Values->tmax (), Values->dt (),
		     Values->umin (), Values->umax (), Values->du (),
		     Values->vmin (), Values->vmax (), Values->dv ());
  
  AssignValues ("r = sin (...)");
  
  Redraw ();
}
void C4DView::FunctionR(){
  UpdateFunctionMenu (4);

  if (F) delete F;
  F = new PolarR (Values->tmin (), Values->tmax (), Values->dt (),
		  Values->umin (), Values->umax (), Values->du (),
		  Values->vmin (), Values->vmax (), Values->dv (),
		  Values->a ());
  
  AssignValues ("r", "Phase");
  
  Redraw ();
}

void C4DView::ObjectHypercube() {
  UpdateFunctionMenu (1);

  if (F) delete F;
  F = new Hypercube (Vector (4, 0., 0., 0., 0.), Values->a ());

  AssignValues ("Hypercube", "Size");
  
  Redraw ();
}

void C4DView::ObjectHyperpyramid() {
  UpdateFunctionMenu (1);

  if (F) delete F;
  F = new Pyramid (Vector (4, 0., 0., 0., 0.), 2.*Values->a ());

  AssignValues ("Hyperpyramid", "Size");
  
  Redraw ();
} 

void C4DView::ObjectHypersponge() {
  UpdateFunctionMenu (1);

  if (F) delete F;
  F = new Sponge (unsigned (Values->a ()), int (Values->b ()), Values->c (), Vector (4, 0., 0., 0., 0.));

  AssignValues ("4-dimensional Menger Sponge", "Level", "Distance", "Size");
  
  Redraw ();
}

void C4DView::ObjectGasket() {
  UpdateFunctionMenu (1);

  if (F) delete F;
  F = new Gasket (unsigned (Values->a ()), 2.*Values->b (), Vector (4, 0., 0., 0., 0.));

  AssignValues ("4-dimensional Sierpinski Gasket", "Level", "Size");
  
  Redraw ();
} 


void C4DView::Surface_1() {
  if (F) delete F;
  F = new Surface1 (Values->tmin (), Values->tmax (), Values->dt (),
		    Values->umin (), Values->umax (), Values->du ());

  AssignValues ("Surface");
  
  Redraw ();
} 

void C4DView::SurfaceHorizon() {
  if (F) delete F;
  F = new Horizon (Values->tmin (), Values->tmax (), Values->dt (),
		   Values->umin (), Values->umax (), Values->du ());

  AssignValues ("Horizon");
  
  Redraw ();
} 

void C4DView::SurfaceTorus3() {
  if (F) delete F;
  F = new Torus3 (Values->tmin (), Values->tmax (), Values->dt (),
		  Values->umin (), Values->umax (), Values->du ());

  AssignValues ("Torus");
  
  Redraw ();
} 

void C4DView::ComplexZ2() {
  if (F) delete F;
  F = new z3 (Values->tmin (), Values->tmax (), Values->dt (),
	      Values->umin (), Values->umax (), Values->du ());

  AssignValues ("z²");
  
  Redraw ();
} 

void C4DView::ComplexZ3() {
  if (F) delete F;
  F = new z3 (Values->tmin (), Values->tmax (), Values->dt (),
	      Values->umin (), Values->umax (), Values->du ());

  AssignValues ("z³");
  
  Redraw ();
} 

void C4DView::ComplexZA() {
  if (F) delete F;
  F = new zA (Values->tmin (), Values->tmax (), Values->dt (),
	      Values->umin (), Values->umax (), Values->du (),
	      Values->a ());

  AssignValues ("z^a", "a");
  
  Redraw ();
} 

void C4DView::ComplexEZ() {
  if (F) delete F;
  F = new ez (Values->tmin (), Values->tmax (), Values->dt (),
	      Values->umin (), Values->umax (), Values->du (),
	      Values->a ());

  AssignValues ("e^a*z", "a");
  
  Redraw ();
} 

void C4DView::ComplexEMZ2() {
  if (F) delete F;
  F = new emz2 (Values->tmin (), Values->tmax (), Values->dt (),
		Values->umin (), Values->umax (), Values->du (),
		Values->a ());

  AssignValues ("e^-a*z²", "a");
  
  Redraw ();
} 

void C4DView::ComplexZM1() {
  if (F) delete F;
  F = new zm1 (Values->tmin (), Values->tmax (), Values->dt (),
	       Values->umin (), Values->umax (), Values->du ());

  AssignValues ("1/z");
  
  Redraw ();
} 

void C4DView::ComplexZM2() {
  if (F) delete F;
  F = new zm2 (Values->tmin (), Values->tmax (), Values->dt (),
	       Values->umin (), Values->umax (), Values->du ());

  AssignValues ("1/z²");
  
  Redraw ();
} 

void C4DView::ComplexSqrtZ() {
  if (F) delete F;
  F = new sqrtz (Values->tmin (), Values->tmax (), Values->dt (),
		 Values->umin (), Values->umax (), Values->du ());

  AssignValues ("sqrt (z)");
  
  Redraw ();
} 

void C4DView::ComplexLnZ() {
  if (F) delete F;
  F = new lnz (Values->tmin (), Values->tmax (), Values->dt (),
	       Values->umin (), Values->umax (), Values->du ());

  AssignValues ("ln z");
  
  Redraw ();
} 

void C4DView::ComplexSinZ() {
  if (F) delete F;
  F = new sinz (Values->tmin (), Values->tmax (), Values->dt (),
		Values->umin (), Values->umax (), Values->du ());

  AssignValues ("sin z");
  
  Redraw ();
} 

void C4DView::ComplexCosZ() {
  if (F) delete F;
  F = new cosz (Values->tmin (), Values->tmax (), Values->dt (),
		Values->umin (), Values->umax (), Values->du ());

  AssignValues ("cos z");
  
  Redraw ();
} 

void C4DView::ComplexSinhZ() {
  if (F) delete F;
  F = new sinhz (Values->tmin (), Values->tmax (), Values->dt (),
		 Values->umin (), Values->umax (), Values->du ());

  AssignValues ("sinh z");
  
  Redraw ();
} 

void C4DView::ComplexCoshZ() {
  if (F) delete F;
  F = new coshz (Values->tmin (), Values->tmax (), Values->dt (),
		 Values->umin (), Values->umax (), Values->du ());

  AssignValues ("cosh z");
  
  Redraw ();
} 

void C4DView::ComplexTanZ() {
  if (F) delete F;
  F = new tanz (Values->tmin (), Values->tmax (), Values->dt (),
		Values->umin (), Values->umax (), Values->du ());

  AssignValues ("tan z");
  
  Redraw ();
} 


#include "FunctionDialogImpl.H"
#include "PolarDialogImpl.H"
#include "ComplexDialogImpl.H"
#include "SurfaceDialogImpl.H"

#include "CustomFunction.H"

void C4DView::customFunction() {
  if (F) delete F;
  F = new CustomFunction (Values->tmin (), Values->tmax (), Values->dt (),
			  Values->umin (), Values->umax (), Values->du (),
			  Values->vmin (), Values->vmax (), Values->dv ());
  QString sym (((CustomFunction *)F)->symbolic());
  AssignValues (sym);
  
  Redraw ();
}

void C4DView::customPolarFunction() {
  if (F) delete F;
  F = new CustomPolarFunction (Values->tmin (), Values->tmax (), Values->dt (),
			       Values->umin (), Values->umax (), Values->du (),
			       Values->vmin (), Values->vmax (), Values->dv ());
  QString sym (((CustomPolarFunction *)F)->symbolic());
  AssignValues (sym);
  
  Redraw ();
  //  PolarDialog *PolarDlg = new PolarDialogImpl;
}
void C4DView::customComplexFunction() {
  if (F) delete F;
  F = new CustomComplexFunction (Values->tmin (), Values->tmax (), Values->dt (),
				 Values->umin (), Values->umax (), Values->du ());
  QString sym (((CustomComplexFunction *)F)->symbolic());
  AssignValues (sym);
  
  Redraw ();
  //  ComplexDialog *ComplexDlg = new ComplexDialogImpl;
}
void C4DView::customSurface() {
  if (F) delete F;
  F = new CustomSurface (Values->tmin (), Values->tmax (), Values->dt (),
			 Values->umin (), Values->umax (), Values->du ());
  QString sym (((CustomSurface *)F)->symbolic());
  AssignValues (sym);
  
  Redraw ();
  //  SurfaceDialog *SurfaceDlg = new SurfaceDialogImpl;
}

/*
void C4DView::OnUpdateFunctionFr3r () {
    menu->setItemEnabled (0, dynamic_cast <Fr3r *> (F) != NULL);
}
*/

