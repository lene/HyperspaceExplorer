// 4DView.cpp : Implementierung der Klasse C4DView
//

#include "stdafx.h"

#include "4D.h"
#include "4DDoc.h"
#include "4DView.h"

#include <strstream>
#include <iomanip>


/////////////////////////////////////////////////////////////////////////////
// C4DView

IMPLEMENT_DYNCREATE(C4DView, CView)

BEGIN_MESSAGE_MAP(C4DView, CView)
	//{{AFX_MSG_MAP(C4DView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_COMMAND(ID_VIEW_ANIMATE_RANDOM, OnAnimateRandom)
	ON_COMMAND(ID_LIGHTING, OnLighting)
	ON_UPDATE_COMMAND_UI(ID_LIGHTING, OnUpdateLighting)
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C4DView Konstruktion/Destruktion

C4DView::C4DView(): 
		m_RightDownPos (0,0), m_LeftDownPos (0,0), 
		m_hGLContext (NULL), m_GLPixelIndex (0),

		m_RightButtonDown (false), m_MidButtonDown (false), m_LeftButtonDown (false),
		
		AntiAlias (false), DisplayPolygons (false), Lighting (false), DepthCue3D (false),
		Animated (false), TakingSpinValues (false),

		m_rotX (15), m_rotY (15), m_transX (0), m_transY (2.5), 
		m_camZ (-10.), m_rotZ (0.),

		Tx (0), Ty (0), Tz (0), Tw (0), 
		Rxy (0), Rxz (0), Rxw (0), Ryz (0), Ryw (0), Rzw (0),
	
		dxy (0), dxz (0), dxw (0), dyz (0), dyw (0), dzw (0), 
		dx (0), dy (0), dz (0) {

}

C4DView::~C4DView() {
}

void C4DView::OnMouseMove (UINT nFlags, CPoint point) {
	bool ViewChanged = false;

	RECT ClientRect;
	GetClientRect (&ClientRect);
	double xsize = ClientRect.right - ClientRect.left,
	       ysize = ClientRect.bottom - ClientRect.top;
	if (xsize == 0 || ysize == 0) return;				//	pathological case better taken care of

	if (::GetKeyState (VK_CONTROL) < 0) {				//	translate 4D viewpoint with CTRL pressed

		if (m_LeftButtonDown || m_MidButtonDown || m_RightButtonDown) {

			ViewChanged = true;							//	mark 4D viewpointz as changed

			double Size = GetDocument ()->Size ();		//	reference size for the translations

			//	translate x / y with LMB
			if (m_LeftButtonDown && !m_MidButtonDown && !m_RightButtonDown) {	//	LMB pressed

				CSize translate = m_LeftDownPos-point;	//	store difference from button press position

				if (TakingSpinValues) {	} else {		//	no translation animation (yet?)
					m_LeftDownPos = point;				//	reset start position for next mouse move

					Tx -= translate.cx*Size/xsize;		//	add x translation
					Ty += translate.cy*Size/ysize;		//	add y translation

					UpdateStatus ("translate x/y");
				}			//	if (TakingSpinValues) 

			}				//	if (m_LeftButtonDown && !m_MidButtonDown && !m_RightButtonDown) 

			//	translate z / w with MMB
			if (m_MidButtonDown && !m_LeftButtonDown && !m_RightButtonDown) {	//	MMB pressed

				CSize translate = m_MidDownPos-point;	//	store difference from button press position
				
				if (TakingSpinValues) {	} else {		//	no translation animation (yet?)	
					m_MidDownPos = point;				//	reset start position for next mouse move

					Tz -= translate.cx*Size/xsize;		//	add z translation
					Tw += translate.cy*Size/ysize;		//	add w translation
				
					UpdateStatus ("translate z/w");
				}			//	if (TakingSpinValues) 

			}				//	if (m_MidButtonDown && !m_LeftButtonDown && !m_RightButtonDown) 

		}					//	if (m_LeftButtonDown || m_MidButtonDown || m_RightButtonDown)

	}						//	if (::GetKeyState (VK_CONTROL) < 0)

	if (::GetKeyState (VK_SHIFT) < 0) {					//	rotate 4D viewpoint with SHIFT pressed

		if (m_LeftButtonDown || m_MidButtonDown || m_RightButtonDown) {

			ViewChanged = true;							//	mark 4D viewpoint as changed

			//	rotate xy / xz with LMB
			if (m_LeftButtonDown && !m_MidButtonDown && !m_RightButtonDown) {
				
				CSize rotate = m_LeftDownPos-point;		//	store difference from button press position
				ViewChanged = false;					//	takes only xy/xz values, which are 
														//	equivalent to z/y 3D rotation
				if (TakingSpinValues) {					//
					dz = rotate.cx/xsize*10; 
					dy = rotate.cy/ysize*10;					//
					UpdateStatus ("taking xy / xz rotation speed");
				}
				else {									//	immediate movement
					m_LeftDownPos = point;				//	reset start position for next mouse move

					m_rotZ -= rotate.cx/xsize*180;			//	add xy rotation ( = z in 3D)
					m_rotY -= rotate.cy/ysize*180;			//	add xz rotation ( = y in 3D)

					UpdateStatus ("rotate xy/xz");
				}		//	if (TakingSpinValues) 
			}			//	if (m_LeftButtonDown && !m_MidButtonDown && !m_RightButtonDown) 

			//	rotate xw / yz with MMB
			if (!m_LeftButtonDown && m_MidButtonDown && !m_RightButtonDown) {

				CSize rotate = m_MidDownPos-point;		//	store difference from button press position
				
				if (TakingSpinValues) {					//
					dxw = rotate.cx/xsize*10; 
					dx = rotate.cy/ysize*10;			//
					if (dxw == 0.) ViewChanged = false;
					UpdateStatus ("taking xw / yz rotation speed");
				}
				else {									//	immediate movement
					m_MidDownPos = point;				//	reset start position for next mouse move

					Rxw -= rotate.cx/xsize*180;			//	add xw rotation
					m_rotX -= rotate.cy/ysize*180;		//	add yz ( = x in 3D) rotation
					if (Rxw == 0.) ViewChanged = false;
	
					UpdateStatus ("rotate xw/yz");
				}		//	if (TakingSpinValues) 

			}			//	if (!m_LeftButtonDown && m_MidButtonDown && !m_RightButtonDown) 

			//	rotate yw / zw with RMB
			if (!m_LeftButtonDown && !m_MidButtonDown && m_RightButtonDown) {	//	RMB pressed

				CSize rotate = m_RightDownPos-point;	//	store difference from button press position
				
				if (TakingSpinValues) {					//
					dyw = rotate.cx/xsize*10; 
					dzw = rotate.cy/ysize*10;					//
					UpdateStatus ("taking yw / zw rotation speed");
				}
				else {									//	immediate movement
					m_RightDownPos = point;				//	reset start position for next mouse move

					Ryw -= rotate.cx/xsize*180;			//	add yw rotation
					Rzw += rotate.cy/ysize*180;			//	add zw rotation
	
					UpdateStatus ("rotate yw/zw");
				}		//	if (TakingSpinValues) 

			}			//	if (!m_LeftButtonDown && !m_MidButtonDown && m_RightButtonDown) 

		}				//	if (m_LeftButtonDown || m_MidButtonDown || m_RightButtonDown)

	}					//	if (::GetKeyState (VK_SHIFT) < 0)

	if (ViewChanged) {									//	4D viewpoint has changed

		C4DDoc *Doc = dynamic_cast<C4DDoc *> (GetDocument ());
		if (!Doc) throw GeneralException ("dynamic_cast<C4DDoc> (GetDocument ()) failed!");
	
		Doc->Transform (Rxy, Rxz, Rxw, Ryz, Ryw, Rzw, Tx, Ty, Tz, Tw);	//	apply the 4D transformation
		Doc->Redraw ();
	}

	else {
		if (m_LeftButtonDown || m_MidButtonDown) {

			double Size = GetDocument ()->Size ();			//	reference size for the translations

			//	pan the view with MMB
			if (m_MidButtonDown && !m_LeftButtonDown) {

				CSize translate = m_MidDownPos-point;	//	store difference from button press position

				if (TakingSpinValues) {	} else {		//	no translation animation (yet?)
					m_MidDownPos = point;				//	reset start position for next mouse move
	
					m_transX += translate.cx*Size/xsize*m_camZ/3; //	add x translation
					m_transY -= translate.cy*Size/ysize*m_camZ/3; //	add y translation

					UpdateStatus ("translate x/y");
				}			//	if (TakingSpinValues) 

			}				//	if (m_MidButtonDown && !m_LeftButtonDown)

			//	rotate the view with LMB
			if (m_LeftButtonDown && !m_MidButtonDown) {

				CSize rotate = m_LeftDownPos-point;		//	store difference from button press position
				
				if (TakingSpinValues) {					//
					dx = rotate.cx/xsize*10; 
					dy = rotate.cy/ysize*10;					//
					UpdateStatus ("taking x / y rotation speed");
				}
				
				else {									//	immediate movement
					m_LeftDownPos = point;				//	reset start position for next mouse move

					m_rotX -= rotate.cy/ysize*180;		//	add x rotation 
					m_rotY -= rotate.cx/xsize*180;		//	add y rotation
				
					UpdateStatus ("rotate x/y");
				}			//	if (TakingSpinValues) 

			}				//	if (m_LeftButtonDown && !m_MidButtonDown) 
	
			//	zoom with LMB+RMB
			if (m_LeftButtonDown && m_MidButtonDown) {

				CSize zoom = m_LeftDownPos-point;		//	store difference from button press position
				
				if (TakingSpinValues) {					//
					dz = zoom.cx/xsize*20; 
					UpdateStatus ("taking z rotation speed");
				}

				else {									//	immediate movement
					m_LeftDownPos = point;				//	reset start position for next mouse move
					
					if (zoom.cx != 0) {
						m_camZ *= 1+zoom.cx/xsize;		//	scale camera z position
						SetupDepthCue (DepthCue3D);
					}
					m_rotZ -= zoom.cy/ysize*180;		//	add z rotation

					UpdateStatus ("translate/rotate z");
				}			//	if (TakingSpinValues) 

			}				//	if (m_LeftButtonDown && m_MidButtonDown)

			InvalidateRect (NULL, false);				//	redraw the window

		}					//	if (m_LeftButtonDown || m_MidButtonDown) 

	}						//	if (ViewChanged)

	CView::OnMouseMove(nFlags, point);
}


void C4DView::OnLButtonDown(UINT nFlags, CPoint point) {	
	m_LeftButtonDown = true;
	m_LeftDownPos = point;

	if (::GetKeyState (' ') < 0) TakingSpinValues = true;
	else						 TakingSpinValues = false;
	
	CView::OnLButtonDown(nFlags, point);
}

void C4DView::OnLButtonUp(UINT nFlags, CPoint point) {
	m_LeftButtonDown = false;

	if (TakingSpinValues) {

		StartAnimation ();
		TakingSpinValues = false;
	}

	UpdateStatus (" ");
	CView::OnLButtonUp(nFlags, point);
}

void C4DView::OnMButtonDown(UINT nFlags, CPoint point) {	
	m_MidButtonDown = true;
	m_MidDownPos = point;

	if (::GetKeyState (' ') < 0) TakingSpinValues = true;
	else						 TakingSpinValues = false;

	CView::OnMButtonDown(nFlags, point);
}

void C4DView::OnMButtonUp(UINT nFlags, CPoint point) {
	m_MidButtonDown = false;

	if (TakingSpinValues) {

		StartAnimation ();
		TakingSpinValues = false;
	}

	UpdateStatus (" ");
	CView::OnMButtonUp(nFlags, point);
}

void C4DView::OnRButtonDown(UINT nFlags, CPoint point) {
	m_RightButtonDown = true;
	m_RightDownPos = point;
	
	if (::GetKeyState (' ') < 0) TakingSpinValues = true;
	else						 TakingSpinValues = false;

	CView::OnRButtonDown(nFlags, point);
}

void C4DView::OnRButtonUp(UINT nFlags, CPoint point) {
	m_RightButtonDown = false;

	if (TakingSpinValues) {

		StartAnimation ();
		TakingSpinValues = false;
	}

	UpdateStatus (" ");
	CView::OnRButtonUp(nFlags, point);
}

void C4DView::OnRButtonDblClk(UINT nFlags, CPoint point) {
	if (Animated) StopAnimation ();
	else { 
		Tx = Ty = Tz = Tw = 0;
		Rxy = Rxz = Rxw = Ryz = Ryw = Rzw = 0;

		C4DDoc *Doc = dynamic_cast<C4DDoc *> (GetDocument ());
		if (!Doc) throw GeneralException ("dynamic_cast<C4DDoc> (GetDocument ()) failed!");

		Doc->Transform (Rxy, Rxz, Rxw, Ryz, Ryw, Rzw, Tx, Ty, Tz, Tw);	//	transform
		Doc->Redraw ();									//	implicit OnPaint ()
	}

	CView::OnRButtonDblClk(nFlags, point);
}

void C4DView::StartAnimation () {
	Animated = true;
	SetTimer (ID_ANIMATION_TIMER, 20, NULL);			//	go for 50 fps
}
		
void C4DView::StopAnimation () {
	Animated = false;
	dxy = dxz = dxw = dyz = dyw = dzw = dx = dy = dz = 0.;
	KillTimer (ID_ANIMATION_TIMER);
	KillTimer (ID_ANIMATION_TIMER_2);
}


void C4DView::OnTimer(UINT nIDEvent) {

 	if (nIDEvent == ID_ANIMATION_TIMER_2)				//	time to
		OnAnimateRandom();								//	change rotation direction

	if (nIDEvent == ID_ANIMATION_TIMER) {

		m_rotX += dx; m_rotY += dy; m_rotZ += dz;		//	update 3D viewpoint values

		if (dxy != 0 || dxz != 0 || dxw != 0 ||			//	4D viewpoint animated?
			dyz != 0 || dyw != 0 || dzw != 0 ) {

			Rxy += dxy;	Rxz += dxz;	Rxw += dxw;			//	update values
			Ryz += dyz;	Ryw += dyw;	Rzw += dzw;
		
			C4DDoc *Doc = dynamic_cast<C4DDoc *> (GetDocument ());
			if (!Doc) throw GeneralException ("dynamic_cast<C4DDoc> (GetDocument ()) failed!");

			Doc->Transform (Rxy, Rxz, Rxw, Ryz, Ryw, Rzw, Tx, Ty, Tz, Tw);	//	transform
			Doc->Redraw ();								//	implicit OnPaint ()
		}
		else OnPaint ();								//	explicit OnPaint ()
	
		UpdateStatus ("Double-click RMB to stop animation");
	}

	CView::OnTimer(nIDEvent);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//	from here on it gets pretty boring OpenGL management stuff
//

void C4DView::OnPaint() {								//	object drawing routine
	C4DDoc *Doc = GetDocument ();
	if (!Doc) throw GLException ("Well actually it is not a GL problem,\n"
								 "as stated above, i's just too lazy to\n"
								 "define another ecxeption class  which\n"
								 "does just the same. 	  what actually\n"
								 "happened is just that  GetDocument ()\n"
								 "returned a NULL pointer... bye!");
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	//	clear the window

	if (DisplayPolygons)								//	this might move to a special routine
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//	"SwitchWireframe ()"
	else 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPushMatrix();										//	save the transformation matrix
	glTranslated(0.0, -Doc->Size ()*.75, 0);			//	set the camera position

	glTranslated (m_transX, m_transY, m_camZ);			//	apply object translation
	glRotated(m_rotX, 1.0, 0.0, 0.0);					//	 -"-	-"-	 rotation
	glRotated(m_rotY, 0.0, 1.0, 0.0);
	glRotated(m_rotZ, 0.0, 0.0, 1.0);

	Doc->RenderScene (0);								//	draw current frame

	glPopMatrix();										//	restore transformation matrix

	CPaintDC dc(this);									//	device context for painting
	SwapBuffers(dc.m_ps.hdc);							//	swap the buffers
}

void C4DView::OnSize(UINT nType, int cx, int cy) {		//	resizing routine
														//	also, the definition of the
														//	GL viewport is done here
	if (cx == 0 && cy == 0) return;						//	zero size window taken care of

	C4DDoc *Doc = GetDocument ();

	CView::OnSize(nType, cx, cy);						//	window resizing
	
	GLsizei width = cx, height = cy;
	GLdouble aspect = GLdouble (width > 0? width: 1);	//	calculate aspect ratio
	if (height != 0) aspect /= GLdouble (height);

	glViewport (0, 0, width, height);					//	define the viewport
	glMatrixMode (GL_PROJECTION);						//	perspective view
	glLoadIdentity ();									//	reset any transforms
	gluPerspective (45, aspect,							//	set FOV, aspect,
					.01*Doc->Size (),					//  front clipping plane
					100.*Doc->Size ());					//  & back clipping plane

	glMatrixMode (GL_MODELVIEW);						//	return to model view
	glLoadIdentity ();									//	reset

	glDrawBuffer (GL_BACK);								//	dump the buffer

//	::SendMessage (m_hStatusBar, WM_DESTROY, 0, 0); 
//	m_hStatusBar = CreateStatusWindow (WS_CHILD|WS_VISIBLE, "", m_hWnd, 1723);
}

/////////////////////////////////////////////////////////////////////////////
// C4DView Zeichnen

void C4DView::OnDraw(CDC* pDC)
{
	C4DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->RenderScene (0);
}

/////////////////////////////////////////////////////////////////////////////
// C4DView Diagnose

#ifdef _DEBUG
void C4DView::AssertValid() const {
	CView::AssertValid();
}

void C4DView::Dump(CDumpContext& dc) const {
	CView::Dump(dc);
}
#endif //_DEBUG
 
C4DDoc* C4DView::GetDocument() {	// Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
 	if (m_pDocument->IsKindOf(RUNTIME_CLASS(C4DDoc)))
 		return (C4DDoc *)m_pDocument; 
 	else return NULL;
}
/////////////////////////////////////////////////////////////////////////////
// C4DView Nachrichten-Handler

void C4DView::Redisplay (void) {
	OnPaint ();
} 


void C4DView::OnInitialUpdate() {
	glEnable (GL_DEPTH_TEST);							//	enable depth buffer
	glDisable (GL_CULL_FACE);							//	disable face culling
	glEnable (GL_NORMALIZE);							//	auto-normalize surface normals

	glClearColor (0.05f, 0.05f, 0.05f, 1.);				//	set background color
 
	if (AntiAlias) {
		glHint (GL_LINE_SMOOTH_HINT, GL_FASTEST);
		glHint (GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

		glEnable (GL_BLEND);							//	turn on blending
//		glEnable (GL_LINE_SMOOTH);						//	anti-alias lines
//		glEnable (GL_POLYGON_SMOOTH);					//	anti-alias faces

		glBlendFunc (GL_SRC_ALPHA_SATURATE, GL_ONE);	//	STILL FUCKS UP
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//	NOT ANY BETTER
		glDisable   (GL_DEPTH_TEST);						//	just try it, dunno if works
	}
	else { 
		glDisable (GL_BLEND);							//	turn it all off
		glDisable (GL_LINE_SMOOTH);
		glDisable (GL_POLYGON_SMOOTH); 
		glEnable  (GL_DEPTH_TEST);
 		glEnable   (GL_ALPHA_TEST);						//	just try it, dunno if works
	}

 	Lighting = true;								//	because OnLighting toggles Lighting too
 	OnLighting ();										//	initialize lighting
 
	m_hStatusBar = CreateStatusWindow (WS_CHILD|WS_VISIBLE, "", m_hWnd, 1723);	
}

void C4DView::OnDestroy() {							//	clean up before death
	if (wglGetCurrentContext () != NULL) 
		wglMakeCurrent (NULL,NULL);						//	make rendering context not current

	if (m_hGLContext != NULL) {							
		wglDeleteContext (m_hGLContext);				//	delete rendering context
		m_hGLContext = NULL; 
	}

	CView::OnDestroy();							//	now the associated DC can be released
}

int C4DView::OnCreate(LPCREATESTRUCT lpCreateStruct) {	//	create new view
	if (CView::OnCreate(lpCreateStruct) == -1)			//	create base class
		return -1;

	//	initialization of GL lists has to be done in this function,
	//	because OpenGL itself is not yet initialized at the call of
	//	the constructor.

	hDC = ::GetDC (GetSafeHwnd ());						//	get a DC for a window handle to this

	if (SetWindowPixelFormat(hDC) == false)	{			//	couldn't set Pixel format
		throw GLException ("Sorry,  I was unable to create a\n"
						   "Pixel Format   which  makes  any\n"
						   "sense.\n"
						   "There's probably nothing you can\n"
						   "do about this except complaining\n"
						   "to:			  metal.dog@gmx.net.");
		return 0; 
	}

	if (CreateViewGLContext (hDC) == false)	{			//	couldn't create GL context
		throw GLException ("Sorry, I couldn't create an OpenGL\n"
						   "View Context,  or couldn't make it\n"
						   "the current context.\n"
						   "There is probably nothing  you can\n"
						   "do about this,  except complaining\n"
						   "to:				metal.dog@gmx.net.");
		return 0;
	}

#if 0													//	can't implement this because sscanf () 
	const GLubyte *version;								//	won't take GLubyte * as argument
	int major, minor;
	version = glGetString (GL_VERSION);
	if (sscanf (version, "%d.%d", &major, &minor) != 2) {
		throw GLException ("Malformed GL_VERSION string!\n"
						   "You seem to have a badly braindamaged\n"
						   "OpenGL implementation on your system.\n"
						   "Do yourself a favour and throw it out.");
		return 0;
	}

	if (major <= 1 && minor < 1)
		throw GLException ("You have an antique version of OpenGL\n"
						   "on your system (Version < 1.1). Please\n"
						   "upgrade to a modern version.");
#endif

	return 0;
}

BOOL C4DView::PreCreateWindow(CREATESTRUCT& cs) {
	//	opengl requires the window to have the followings flags set
	cs.style |= (WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

	return CView::PreCreateWindow(cs);					//	call base method
}

bool C4DView::SetWindowPixelFormat(HDC hDC) {			//	supply all necessary info
	PIXELFORMATDESCRIPTOR pixelDesc;					//	to define a pixel format

	pixelDesc.nSize = sizeof (PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;

	//	define devices & interfaces with which pixel format is compatible
	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW|				//	draw to window or device surface
						PFD_DRAW_TO_BITMAP|				//	draw to bitmap
						PFD_SUPPORT_OPENGL|				//	enable OpenGL calls
						PFD_DOUBLEBUFFER|				//	enable double duffering
						PFD_STEREO_DONTCARE;			//

	pixelDesc.iPixelType = PFD_TYPE_RGBA;				//	define pixel type
	pixelDesc.cColorBits = 32;							//	define number and
	pixelDesc.cRedBits = 8;								//	order of the color bits
	pixelDesc.cRedShift = 16;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cGreenShift = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 8;
	pixelDesc.cAlphaShift = 24;
	pixelDesc.cAccumBits = 64;							//	same with accumulator bits
	pixelDesc.cAccumRedBits = 16;
	pixelDesc.cAccumGreenBits = 16;
	pixelDesc.cAccumBlueBits = 16;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 64;							//	and depth buffer bits
	pixelDesc.cStencilBits = 8;
	pixelDesc.cAuxBuffers = 0;							//	some other definitions
	pixelDesc.iLayerType = PFD_MAIN_PLANE;				//	i don't understand
	pixelDesc.bReserved = 0;							//	nor really care about
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;

	//  find best possible system pixel format
	m_GLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);

	if (m_GLPixelIndex == 0) {							//	no system pixel format?
		m_GLPixelIndex = 1;								//	let's choose a default index
		if (DescribePixelFormat (hDC, m_GLPixelIndex,
			sizeof (PIXELFORMATDESCRIPTOR), 
			&pixelDesc) == 0) 
				return false;					 		//	bad luck
	}
	//	set the pixel format and return success or failure
	return (SetPixelFormat (hDC, m_GLPixelIndex, &pixelDesc) != 0)? true: false;
}


bool C4DView::CreateViewGLContext(HDC hDC) {
	m_hGLContext = wglCreateContext (hDC);				//	create a WGL context
	
	if (m_hGLContext == 0) return false;				//	shit

	return (wglMakeCurrent (hDC, m_hGLContext) != 0)? true: false;	//	try to make it current
}

void C4DView::UpdateStatus (string status) {			//	write a text to the status bar

	if (m_rotX > 360) m_rotX -= 360;
	if (m_rotX <-360) m_rotX += 360;
	if (fabs (m_rotX) < 1e-3) m_rotX = 0;
	if (m_rotY > 360) m_rotY -= 360;
	if (m_rotY <-360) m_rotY += 360;
	if (fabs (m_rotY) < 1e-3) m_rotY = 0;
	if (m_rotZ > 360) m_rotZ -= 360;
	if (m_rotZ <-360) m_rotZ += 360;
	if (fabs (m_rotZ) < 1e-3) m_rotZ = 0;
	if (Rxw > 360) Rxw -= 360;
	if (Rxw <-360) Rxw += 360;
	if (Ryw > 360) Ryw -= 360;
	if (Ryw <-360) Ryw += 360;
	if (Rzw > 360) Rzw -= 360;
	if (Rzw <-360) Rzw += 360;
	
	ostrstream o;
	o << "  cam_z = " << setw (4) << setprecision (3) << m_camZ 
	  << "  r_x = " << setw (4) << setprecision (3) << m_rotX << "°"
	  << "  r_y = " << setw (4) << setprecision (3) << m_rotY << "°"
	  << "  r_z = " << setw (4) << setprecision (3) << m_rotZ << "°" << "   |  "
	  << "  cam_w = " << setw (4) << setprecision (3) << -Tw - 2.
	  << "  R_xw ="  << setw (4) << setprecision (3) << Rxw << "°"
	  << "  R_yw ="  << setw (4) << setprecision (3) << Ryw << "°"
	  << "  R_zw ="  << setw (4) << setprecision (3) << Rzw << "°"
	  << ends;

	for (unsigned i = status.size (); i <= 24; i++) status += " ";
	status += o.str ();

	::SendMessage (m_hStatusBar, SB_SETTEXT, (WPARAM) (0 | 0), (LPARAM) (LPSTR) status.c_str ()); 
}

void C4DView::SetupDepthCue (bool on) {	
 	const double SR3 = sqrt (3.);
 	static float fog_color[]  = { 0.1f, 0.1f, 0.1f, 1.0f };
 	C4DDoc *Doc = dynamic_cast<C4DDoc *> (GetDocument ());
 	float size = Doc->Size ();
 
	DepthCue3D = on;
 	if (on) {
 		glFogi  (GL_FOG_MODE,  GL_LINEAR);
 		glFogfv (GL_FOG_COLOR, fog_color);
 		glFogf  (GL_FOG_START, fabs (m_camZ)-size/2.); 
 		glFogf  (GL_FOG_END,   fabs (m_camZ)+size/2.*SR3); 
 	    glEnable (GL_FOG);
 	}
 	else glDisable (GL_FOG);
}
 
void C4DView::OnLighting() {
 	Lighting = !Lighting;
 	if (Lighting) {										//	this might move to a special routine
 														//	"SwitchLighting ()"
 	    glEnable(GL_LIGHTING);							//	turn on the light
 
 		static GLfloat LightAmbient[]  = { 0.3f, 0.3f, 0.3f, 1.0f },
 					   LightDiffuse[]  = { 0.9f, 0.9f, 0.9f, 1.0f },
 					   LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f },
 					   LightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };	//	light properties
 
 		glLightfv (GL_LIGHT0, GL_AMBIENT, LightAmbient); //	set the light properties
 		glLightfv (GL_LIGHT0, GL_DIFFUSE, LightDiffuse); //	set the light properties
 	    glLightfv (GL_LIGHT0, GL_SPECULAR, LightSpecular);
 		glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);
 	    glEnable  (GL_LIGHT0);							//	turn on the light
 	}
	else {
 		static GLfloat LightAmbient[]  = { 1.0f, 1.0f, 1.0f, 0.0f },
 					   LightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };	//	light properties
 
 		glEnable  (GL_LIGHTING);
		glLightfv (GL_LIGHT0, GL_AMBIENT, LightAmbient); //	set the light properties
 		glLightfv (GL_LIGHT0, GL_DIFFUSE, LightAmbient); 
 		glLightfv (GL_LIGHT0, GL_SPECULAR, LightAmbient); 
 		glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);
 	    glEnable  (GL_LIGHT0);							//	turn on the light
	}
 
 	Redisplay ();
}
 
void C4DView::OnUpdateLighting(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (Lighting);	
}

void C4DView::OnAnimateRandom() {
 	KillTimer (ID_ANIMATION_TIMER);
 	KillTimer (ID_ANIMATION_TIMER_2);
 	dxw = float (rand ())/RAND_MAX;
 	dyw = float (rand ())/RAND_MAX; 
 	dzw = float (rand ())/RAND_MAX;
 	StartAnimation ();
 	SetTimer (ID_ANIMATION_TIMER_2, 10000, NULL); 
}
 
