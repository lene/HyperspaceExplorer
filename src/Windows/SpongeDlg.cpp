// SpongeDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "4D.h"
#include "SpongeDlg.h"
#include "4DDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld SpongeDlg 


SpongeDlg::SpongeDlg(C4DDoc* _pParent)
	: CDialog(), pParent (_pParent) {
	//{{AFX_DATA_INIT(SpongeDlg)
	m_stmax = _T("1");
	m_stmin = _T("-1");
	m_tsteps = 10;
	m_ststeps = _T("");

	m_sumax = _T("1");
	m_sumin = _T("-1");
	m_usteps = 10;
	m_susteps = _T("");

	m_svmax = _T("1");
	m_svmin = _T("-1");
	m_vsteps = 10;
	m_svsteps = _T("");

	m_sa = _T("1");
	m_sb = _T(".5");
	m_sc = _T(".25");
	m_sd = _T("0");
	//}}AFX_DATA_INIT
	Create (SpongeDlg::IDD, NULL);
//	InitModalIndirect (SpongeDlg::IDD);
}


void SpongeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SpongeDlg)
	DDX_Slider(pDX, IDC_TSTEPS, m_tsteps);
	DDX_Text(pDX, IDC_TSTEXT, m_ststeps);
	DDX_Slider(pDX, IDC_USTEPS, m_usteps);
	DDX_Text(pDX, IDC_USTEXT, m_susteps);
	DDX_Slider(pDX, IDC_VSTEPS, m_vsteps);
	DDX_Text(pDX, IDC_VSTEXT, m_svsteps);
	DDX_Text(pDX, IDC_TMAX, m_stmax);
	DDX_Text(pDX, IDC_TMIN, m_stmin);
	DDX_Text(pDX, IDC_UMAX, m_sumax);
	DDX_Text(pDX, IDC_UMIN, m_sumin);
	DDX_Text(pDX, IDC_VMAX, m_svmax);
	DDX_Text(pDX, IDC_VMIN, m_svmin);
	DDX_Text(pDX, IDC_PARAMETER, m_sa);
	DDX_Text(pDX, IDC_PARAMETER_B, m_sb);
	DDX_Text(pDX, IDC_PARAMETER_C, m_sc);
	DDX_Text(pDX, IDC_PARAMETER_D, m_sd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SpongeDlg, CDialog)
	//{{AFX_MSG_MAP(SpongeDlg)
	ON_BN_CLICKED(IDC_CHANGE, OnChange)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten SpongeDlg 


BOOL SpongeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CSliderCtrl *SC = (CSliderCtrl *)GetDlgItem (IDC_TSTEPS);
	SC->SetRange (0, 50);
	SC->SetTicFreq (10);
	SC->SetPageSize (10);

	SC = (CSliderCtrl *)GetDlgItem (IDC_USTEPS);
	SC->SetRange (0, 50);
	SC->SetTicFreq (10);
	SC->SetPageSize (10);

	SC = (CSliderCtrl *)GetDlgItem (IDC_VSTEPS);
	SC->SetRange (0, 50);
	SC->SetTicFreq (10);
	SC->SetPageSize (10);

	UpdateData (false);

 	SetTimer (ID_UPDATE_TIMER, 100, NULL); 

	ShowWindow (SW_SHOW);

	return TRUE;  
}

void SpongeDlg::OnChange(UINT nIDEvent) {
	static double oldtmin = 0, oldtmax = 0, oldumin = 0, oldumax = 0, oldvmin = 0, oldvmax = 0, 
				  olda = 0, oldb = 0, oldc = 0, oldd = 0;
	static unsigned oldtsteps = 0, oldusteps = 0, oldvsteps = 0;

	bool Changed = false;
	UpdateData (true);								//	get variables from screen

	if (oldtsteps != m_tsteps) { oldtsteps = m_tsteps; Changed = true; }
	if (oldusteps != m_usteps) { oldusteps = m_usteps; Changed = true; }
	if (oldvsteps != m_vsteps) { oldvsteps = m_vsteps; Changed = true; }
	if (oldtmin != atod (m_stmin)) {				//	check if any value has changed
		oldtmin = atod (m_stmin); Changed = true; }	//	restore marker and set flag
	if (oldtmax != atod (m_stmax)) {				
		oldtmax = atod (m_stmax); Changed = true; }	
	if (oldumin != atod (m_sumin)) {
		oldumin = atod (m_sumin); Changed = true; }
	if (oldumax != atod (m_sumax)) {
		oldumax = atod (m_sumax); Changed = true; }
	if (oldvmin != atod (m_svmin)) {
		oldvmin = atod (m_svmin); Changed = true; }
	if (oldvmax != atod (m_svmax)) {
		oldvmax = atod (m_svmax); Changed = true; }
	if (olda != atod (m_sa)) { olda = atod (m_sa); Changed = true; }
	if (oldb != atod (m_sb)) { oldb = atod (m_sb); Changed = true; }
	if (oldc != atod (m_sc)) { oldc = atod (m_sc); Changed = true; }
	if (oldd != atod (m_sd)) { oldd = atod (m_sd); Changed = true; }

	if (Changed) {									//	
		if (tmax () <= tmin ())
			Swap (m_stmax, m_stmin);					//	
		if (umax () <= umin ())
			Swap (m_stmax, m_stmin);					//	
		if (vmax () == vmin ())
			Swap (m_stmax, m_stmin);					//		
	
		UpdateData (false);								//	update screen

		pParent->OnNewDocument ();
	}
}

void SpongeDlg::SetParameterText (CString A, CString B, CString C, CString D) {
	if (A == "") GetDlgItem (IDC_PARAMETER)->EnableWindow (false);
	else 		 GetDlgItem (IDC_PARAMETER)->EnableWindow (true);

	if (B == "") GetDlgItem (IDC_PARAMETER_B)->EnableWindow (false);
	else 		 GetDlgItem (IDC_PARAMETER_B)->EnableWindow (true);

	if (C == "") GetDlgItem (IDC_PARAMETER_C)->EnableWindow (false);
	else 		 GetDlgItem (IDC_PARAMETER_C)->EnableWindow (true);

	if (D == "") GetDlgItem (IDC_PARAMETER_D)->EnableWindow (false);
	else 		 GetDlgItem (IDC_PARAMETER_D)->EnableWindow (true);
	
	GetDlgItem (IDC_PARAMETER_A_STRING)->SetWindowText (A.GetBuffer (16));
	GetDlgItem (IDC_PARAMETER_B_STRING)->SetWindowText (B.GetBuffer (16));
	GetDlgItem (IDC_PARAMETER_C_STRING)->SetWindowText (C.GetBuffer (16));
	GetDlgItem (IDC_PARAMETER_D_STRING)->SetWindowText (D.GetBuffer (16));
}

void SpongeDlg::OnOK() {
	OnChange (0); 
}

//	timer driven function to ch
void SpongeDlg::OnTimer(UINT nIDEvent) {
	static unsigned oldtsteps = 0, oldusteps = 0;

	if (nIDEvent == ID_UPDATE_TIMER) {
		UpdateData (true);							//	get variables from screen

		if (m_tsteps < 2) m_tsteps = 2;				//	for safety against zero divides
		if (m_usteps < 2) m_usteps = 2;				//	2 is the smallest sensible grid size.
		if (m_vsteps < 2) m_vsteps = 2;				

		//	for memory management reasons (read: sloppy coding, *blush*) we have to keep 
		//	tsteps <= usteps <= vsteps.
		//	we want usteps & vsteps to grow if tsteps grows, and usteps and tsteps to
		//	shrink if vsteps shrinks. analogously with usteps.

		bool tsgrown = false, usgrown = false;		
		if (oldtsteps != m_tsteps) {				
			if (oldtsteps < m_tsteps) tsgrown = true;
			oldtsteps = m_tsteps; 
		}
		if (oldusteps != m_usteps) {
			if (oldusteps < m_usteps) usgrown = true;
			oldusteps = m_usteps; 
		}

		if (m_usteps < m_tsteps) {					
			if (tsgrown) m_usteps = m_tsteps;
			else		 m_tsteps = m_usteps;		
		}
		if (m_vsteps < m_usteps) {					
			if (tsgrown || usgrown) m_vsteps = m_usteps;
			else					m_usteps = m_vsteps;
		}	

		m_ststeps.Format ("%d", m_tsteps);			//	print slide setting
		m_susteps.Format ("%d", m_usteps);			//	print slide setting
		m_svsteps.Format ("%d", m_vsteps);			//	print slide setting
	
		UpdateData (false);							//	update screen
	}

	CDialog::OnTimer(nIDEvent);
}