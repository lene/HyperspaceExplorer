
//      project:      hyperspace explorer
//      module:       Object.C
//      contains:     four-dimensional objects which cannot be defined as a
//		      function
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)



#include "Globals.H"

#include "Object.H"
#include "Matrix.H"


///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  generic Object constructor; only allocates necessary arrays, children must
 *  fill them in their c'tor
 *  @param vertices	number of vertices
 *  @param surfaces	number of surfaces
 */
Object::Object (unsigned vertices, unsigned surfaces):
    Function (),
    NumVertices (vertices), NumSurfaces (surfaces) {
    X	   = new Vector [NumVertices];
    Xtrans = new Vector [NumVertices];
    Xscr   = new Vector [NumVertices];
    R = new float [NumVertices];
    G = new float [NumVertices];
    B = new float [NumVertices];
    for (unsigned i = 0; i < 4; i++)
	Surface[i] = new unsigned [NumSurfaces];
}		


/*******************************************************************************
 *  generic Object destructor; frees arrays
 */
Object::~Object () {
    delete [] X;
    delete [] Xtrans;
    delete [] Xscr;
    delete [] R;
    delete [] G;
    delete [] B;
    for (unsigned i = 0; i < 4; i++)
	delete [] Surface[i];
}


/*******************************************************************************
 *  transforms an Object
 *  as I look at it, i think this could be optimized by making the transformation
 *  matrices static and only canging the corresponding entries... but how to
 *  make this beautifully, i don't know
 *  @param thetaxy	rotation around xy plane (z axis); ignored because 3D rotation takes care of it
 *  @param thetaxz	rotation around xz plane (y axis); ignored because 3D rotation takes care of it
 *  @param thetaxw	rotation around xw plane
 *  @param thetayz	rotation around xy plane (x axis); ignored because 3D rotation takes care of it
 *  @param thetayw	rotation around yw plane
 *  @param thetazw	rotation around zw plane
 *  @param tx		translation in x direction
 *  @param ty		translation in y direction
 *  @param tz		translation in z direction
 *  @param tw		translation in w direction
 */
void Object::Transform (double thetaxy, double thetaxz, double thetaxw, double thetayz, double thetayw, double thetazw,
			double tx, double ty, double tz, double tw) {
    matrix<4> Rxw = matrix<4> (0, 3, thetaxw), Ryw = matrix<4> (1, 3, thetayw), Rzw = matrix<4> (2, 3, thetazw),
	Rxwyw = Rxw*Ryw, Rot = Rxwyw*Rzw;
    Vector trans = Vector (4, tx, ty, tz, tw);
		
    for (unsigned i = 0; i < NumVertices; i++) 
	Xtrans[i] = (Rot*X[i])+trans;
}


/*******************************************************************************
 *  projects an Object into three-space
 *  @param scr_w	w coordinate of screen
 *  @param cam_w	w coordinate of camera
 *  @param depthcue4d	wheter to use hyperfog/dc
 */
void Object::Project (double scr_w, double cam_w, bool depthcue4d) {
    double ProjectionFactor;
    double Wmax = 0, Wmin = 0;

    for (unsigned i = 0; i < NumVertices; i++) {
        if (depthcue4d) {
	    if (Xtrans[i][3] < Wmin) Wmin = Xtrans[i][3];
	    if (Xtrans[i][3] > Wmax) Wmax = Xtrans[i][3];
	}

	ProjectionFactor = (scr_w-cam_w)/(Xtrans[i][3]-cam_w);

	for (unsigned j = 0; j <= 2; j++) 
	    Xscr[i][j] = ProjectionFactor*Xtrans[i][j];

	R[i] = (X[i][0]+1)/2;							
	G[i] = (X[i][1]+1)/2;
	B[i] = (X[i][2]+1)/2;
    }
 	
    if (!depthcue4d) return;

    //  apply hyperfog
    for (unsigned i = 0; i < NumVertices; i++) {
	float DepthCueFactor = (Wmax-Xtrans[i][3])/(Wmax-Wmin)*0.9+0.1; 	//	HARDCODED! YUCK! VADE RETRO SATANAS!
	R[i] = 0.1+(R[i]-0.1)*DepthCueFactor;
	G[i] = 0.1+(G[i]-0.1)*DepthCueFactor;
	B[i] = 0.1+(B[i]-0.1)*DepthCueFactor;
    }
}


/*******************************************************************************
 *  draw the projected Object (onto screen or into GL list, as it is)
 */
void Object::Draw () {
    glBegin (GL_QUADS);
    for (unsigned i = 0; i < NumSurfaces; i++) 
	for (unsigned j = 0; j < 4; j++) {
	    SetColor (R[Surface[j][i]], G[Surface[j][i]], B[Surface[j][i]]);
	    glVertex (Xscr[Surface[j][i]]);
	}
    glEnd ();
}


    ///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Hypercube constructor
 *  @param center	center
 *  @param _a		side_length/2
 */
Hypercube::Hypercube (const Vector &center, double _a):
    Object (16, 24),
    a (_a) {
    for (int x = 0; x <= 1; x++)
	for (int y = 0; y <= 1; y++)
	    for (int z = 0; z <= 1; z++)
		for (int w = 0; w <= 1; w++) 
		    X[x+2*(y+2*(z+2*w))] = Vector (4, 2.*x-1., 2.*y-1., 2.*z-1., 2.*w-1.)*a+center;

    DeclareSquare (0,   0, 1, 3, 2);
    DeclareSquare (1,   0, 1, 5, 4);    
    DeclareSquare (2,   0, 1, 9, 8);    
    DeclareSquare (3,   0, 2, 6, 4);    
    DeclareSquare (4,   0, 2,10, 8);    
    DeclareSquare (5,   0, 4,12, 8);    
    DeclareSquare (6,   1, 3, 7, 5);    
    DeclareSquare (7,   1, 3,11, 9);    
    DeclareSquare (8,   1, 5,13, 9);    
    DeclareSquare (9,   2, 3, 7, 6);    
    DeclareSquare (10,  2, 3,11,10);    
    DeclareSquare (11,  2, 6,14,10);    
    DeclareSquare (12,  3, 7,15,11);    
    DeclareSquare (13,  4, 5, 7, 6);    
    DeclareSquare (14,  4, 5,13,12);    
    DeclareSquare (15,  4, 6,14,12);    
    DeclareSquare (16,  5, 7,15,13);    
    DeclareSquare (17,  6, 7,15,14);    
    DeclareSquare (18,  8, 9,11,10);    
    DeclareSquare (19,  8, 9,13,12);    
    DeclareSquare (20,  8,10,14,12);    
    DeclareSquare (21,  9,11,15,13);    
    DeclareSquare (22, 10,11,15,14);    
    DeclareSquare (23,12,13,15,14);    
}		


/*******************************************************************************
 *  Hypercube destructor
 *  @rant	really, i am so anal, idon't know why i even bother to document this
 *  		must be the virgo inheritance or what
 */
Hypercube::~Hypercube () { }


/*******************************************************************************
 *  declare a square in the surfaces array
 *  @param i	index of the square
 *  @param a	index of vertex 1	
 *  @param b	index of vertex 2
 *  @param c	index of vertex 3	
 *  @param d	index of vertex 4	
 */
void Hypercube::DeclareSquare (unsigned i, unsigned a, unsigned b, unsigned c, unsigned d) {
    Surface[0][i] = a;
    Surface[1][i] = b;
    Surface[2][i] = c;
    Surface[3][i] = d; 
}


    ///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Sponge constructor
 *  @param level	hypersponge level
 *  @param distance	distance of subcubes to center to be counted as part of the fractal
 *			= 0: solid hypercube
 *			= 1: foam
 *			= 2: sponge
 *			= 3: dust
 *			>= 4: nothing
 *  @param rad		side_length/2
 *  @param center	center
 */
Sponge::Sponge (unsigned level, int distance, double rad, Vector center):
    Level (level) {
    if (Level < 1)
	List.push_back (new Hypercube (center, rad*3./2.));
    else {
        if (distance > 3) distance = 3;				//  dunno if this is wise

	if (MemRequired (distance) > MaximumMemory) {		//  which is defined in Globals.C, yuck
	  cerr << "Menger sponge of level " << Level		//  but there seems to be no portable way to find it out
	       << " would require approx. " << MemRequired (distance)/1024/1024  //  and the rcfile-system is not ready yet
	       << " MB of memory." << endl;
	  if (check_memory) {
	    cerr << "This is more than your available Memory of "
		 << MaximumMemory/1024/1024 << "MB." << endl;
	    while (MemRequired (distance) > MaximumMemory) Level--;
	    cerr << "Using level " << Level << " instead." << endl;
	  }
	}
	for (int x = -1; x <= 1; x++)
	    for (int y = -1; y <= 1; y++)
		for (int z = -1; z <= 1; z++)
		    for (int w = -1; w <= 1; w++) {
			if (distance >= 0) {
			    if (abs (x)+abs (y)+abs (z)+abs (w) > distance) {
				Vector NewCen = Vector (4, double (x), double (y), double (z), double (w))*rad;
				NewCen += center;
				List.push_back (new Sponge (Level-1, distance, rad/3., NewCen));
			    }
			}
			else {
			    if (abs (x)+abs (y)+abs (z)+abs (w) < distance) {
				Vector NewCen = Vector (4, double (x), double (y), double (z), double (w))*rad;
				NewCen += center;
				List.push_back (new Sponge (Level-1, distance, rad/3., NewCen));
			    }
			}
		    }
    }
}


/*******************************************************************************
 *  return the approximate amount of memory needed to display a sponge of current
 *  level and given distance
 *  uses hardcoded and experimentally found value for memory per hypercube - ICK!
 *  @param distance	see c'tor
 *  @return		approx. mem required
 */
unsigned long Sponge::MemRequired (unsigned distance) {
    double SpongePerLevel = ((distance == 0)? 81:
			     (distance == 1)? 72:
			     (distance == 2)? 48:
			                      16);
    return (unsigned long) ((pow (SpongePerLevel, int (Level))*32)/1024+8)*1024*1024;
}


/*******************************************************************************
 *  Sponge destructor
 */
Sponge::~Sponge () { }


/*******************************************************************************
 *  transforms a Sponge
 *  @param thetaxy	rotation around xy plane (z axis); ignored because 3D rotation takes care of it
 *  @param thetaxz	rotation around xz plane (y axis); ignored because 3D rotation takes care of it
 *  @param thetaxw	rotation around xw plane
 *  @param thetayz	rotation around xy plane (x axis); ignored because 3D rotation takes care of it
 *  @param thetayw	rotation around yw plane
 *  @param thetazw	rotation around zw plane
 *  @param tx		translation in x direction
 *  @param ty		translation in y direction
 *  @param tz		translation in z direction
 *  @param tw		translation in w direction
 */
void Sponge::Transform (double Thetaxy, double Thetaxz, double Thetaxw, double Thetayz, double Thetayw, double Thetazw,
			double Tx, double Ty, double Tz, double Tw) {
    for (unsigned i = 0; i < List.size (); i++)
	List[i]->Transform (Thetaxy, Thetaxz, Thetaxw, Thetayz, Thetayw, Thetazw,
			    Tx, Ty, Tz, Tw);
}


/*******************************************************************************
 *  projects a Sponge into three-space
 *  @param scr_w	w coordinate of screen
 *  @param cam_w	w coordinate of camera
 *  @param depthcue4d	wheter to use hyperfog/dc
 */
void Sponge::Project (double scr_w, double cam_w, bool depthcue4d) {
    for (unsigned i = 0; i < List.size (); i++)
	List[i]->Project (scr_w, cam_w, depthcue4d);
}

/*******************************************************************************
 *  draw the projected Sponge (onto screen or into GL list, as it is)
 */
void Sponge::Draw (void) {
# if 0
    cerr << description () << endl;	//  clumsy debug output
# endif    
  
    //  usleep (200000);

  if (Level < 1) {
    List[0]->Draw ();
  }
  else 
    for (unsigned i = 0; i < List.size (); i++)
      List[i]->Draw ();
}


    ///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Pyramid (hypersimplex) constructor
 *  @param center	center
 *  @param _a		side_length/2
 */
Pyramid::Pyramid (const Vector &center, double _a):
    Object (5, 10),
    a (_a) {
    X[0] = Vector (4, 0.0, 0.0, 0.0, 0.0);
    X[1] = Vector (4, 1.0, 0.0, 0.0, 0.0);
    X[2] = Vector (4, 0.5, sqrt (3.)/2., 0.0, 0.0);
    X[3] = Vector (4, 0.5, sqrt (3.)/6., sqrt (2./3.), 0.0);
    X[4] = Vector (4, 0.5, sqrt (3.)/6., 1./sqrt (6.), 1./sqrt (2.));

    Vector center_of_mass (4, 0.5, sqrt (3.)/4., sqrt (1./6.), 1./sqrt (8.));
    for (unsigned i = 0; i < NumVertices; i++)
	X[i] = X[i]*a+center-center_of_mass*a;

    DeclareTriangle (0,  0, 1, 2);
    DeclareTriangle (1,  0, 1, 3);    
    DeclareTriangle (2,  0, 1, 4);    
    DeclareTriangle (3,  0, 2, 3);    
    DeclareTriangle (4,  0, 2, 4);    
    DeclareTriangle (5,  0, 3, 4);    
    DeclareTriangle (6,  1, 2, 3);    
    DeclareTriangle (7,  1, 2, 4);    
    DeclareTriangle (8,  1, 3, 4);    
    DeclareTriangle (9,  2, 3, 4);    
}		


/*******************************************************************************
 *  Pyramid destructor
 */
Pyramid::~Pyramid () { }


/*******************************************************************************
 *  declare a triangle in the surfaces array
 *  @param i	index of the square
 *  @param a	index of vertex 1	
 *  @param b	index of vertex 2
 *  @param c	index of vertex 3	
 */
void Pyramid::DeclareTriangle (unsigned i, unsigned a, unsigned b, unsigned c) {
    Surface[0][i] = a;
    Surface[1][i] = b;
    Surface[2][i] = c;
    Surface[3][i] = c; 
}


    ///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Gasket constructor
 *  @param level	hyper-sierpinski gasket level
 *  @param rad		side_length/2
 *  @param center	center
 */
Gasket::Gasket (unsigned level, double rad, Vector center):
    Level (level) {
    if (Level < 1)
	List.push_back (new Pyramid (center, rad));
    else {
	if (MemRequired () > MaximumMemory) {			//  which is defined in Globals.C
	  cerr << "Sierpinski gasket of level " << Level	//  see Sponge::Sponge (...)
	       << " would require approx. " << MemRequired ()/1024/1024
	       << " MB of memory." << endl;
	  if (check_memory) {
	    cerr << "This is more than your available Memory of "
		 << MaximumMemory/1024/1024 << "MB." << endl;
	    while (MemRequired () > MaximumMemory) Level--;
	    cerr << "Using level " << Level << " instead." << endl;
	  }
	}
	rad = rad/2;
	
	Vector NewCen = Vector (4, 0.0, 0.0, 0.0, 0.0);
	NewCen += center;
	List.push_back (new Gasket (Level-1, rad, NewCen));

	NewCen = Vector (4, 1.0, 0.0, 0.0, 0.0)*rad;
	NewCen += center;
	List.push_back (new Gasket (Level-1, rad, NewCen));

	NewCen = Vector (4, 0.5, sqrt (3.)/2., 0.0, 0.0)*rad;
	NewCen += center;
	List.push_back (new Gasket (Level-1, rad, NewCen));

	NewCen = Vector (4, 0.5, sqrt (3.)/6., sqrt (2./3.), 0.0)*rad;
	NewCen += center;
	List.push_back (new Gasket (Level-1, rad, NewCen));

	NewCen = Vector (4, 0.5, sqrt (3.)/6., 1./sqrt (6.), 1./sqrt (2.))*rad;
	NewCen += center;
	List.push_back (new Gasket (Level-1, rad, NewCen));
    }
}


/*******************************************************************************
 *  return the approximate amount of memory needed to display a gasket of current
 *  level
 *  uses hardcoded and experimentally found value for memory per simplex - ICK!
 *  @return		approx. mem required
 */
unsigned long Gasket::MemRequired (void) {
    return (unsigned long) ((pow (5., (int)Level)*14.5)/1024+8)*1024*1024;
}


/*******************************************************************************
 *  Gasket destructor
 */
Gasket::~Gasket () { }


/*******************************************************************************
 *  transforms a Gasket
 *  @param thetaxy	rotation around xy plane (z axis); ignored because 3D rotation takes care of it
 *  @param thetaxz	rotation around xz plane (y axis); ignored because 3D rotation takes care of it
 *  @param thetaxw	rotation around xw plane
 *  @param thetayz	rotation around xy plane (x axis); ignored because 3D rotation takes care of it
 *  @param thetayw	rotation around yw plane
 *  @param thetazw	rotation around zw plane
 *  @param tx		translation in x direction
 *  @param ty		translation in y direction
 *  @param tz		translation in z direction
 *  @param tw		translation in w direction
 */
void Gasket::Transform (double Thetaxy, double Thetaxz, double Thetaxw, double Thetayz, double Thetayw, double Thetazw,
			 double Tx, double Ty, double Tz, double Tw) {
    for (unsigned i = 0; i < List.size (); i++)
	List[i]->Transform (Thetaxy, Thetaxz, Thetaxw, Thetayz, Thetayw, Thetazw,
			    Tx, Ty, Tz, Tw);
}


/*******************************************************************************
 *  projects a Gasket into three-space
 *  @param scr_w	w coordinate of screen
 *  @param cam_w	w coordinate of camera
 *  @param depthcue4d	wheter to use hyperfog/dc
 */
void Gasket::Project (double scr_w, double cam_w, bool depthcue4d) {
    for (unsigned i = 0; i < List.size (); i++)
	List[i]->Project (scr_w, cam_w, depthcue4d);
}

/*******************************************************************************
 *  draw the projected Gasket (onto screen or into GL list, as it is)
 */
void Gasket::Draw (void) {
    for (unsigned i = 0; i < List.size (); i++)
	List[i]->Draw ();
}
