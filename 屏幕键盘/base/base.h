// base.h : main header file for the BASE DLL
//

#if !defined(AFX_BASE_H__3368BC4D_7572_4B91_A550_9695B9B38236__INCLUDED_)
#define AFX_BASE_H__3368BC4D_7572_4B91_A550_9695B9B38236__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBaseApp
// See base.cpp for the implementation of this class
//

class CBaseApp : public CWinApp
{
public:
	CBaseApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CBaseApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASE_H__3368BC4D_7572_4B91_A550_9695B9B38236__INCLUDED_)
