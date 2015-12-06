// keyboardDlg.h : header file
//

#if !defined(AFX_KEYBOARDDLG_H__2E83B372_742E_4CE0_A6DC_6BFB369B8A4C__INCLUDED_)
#define AFX_KEYBOARDDLG_H__2E83B372_742E_4CE0_A6DC_6BFB369B8A4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


_declspec(dllimport) void SetHook(HWND hwnd);
_declspec(dllimport) void SetKeyRect(int index, CRect rect);


/////////////////////////////////////////////////////////////////////////////
// CKeyboardDlg dialog

class CKeyboardDlg : public CDialog
{
// Construction
public:
	CKeyboardDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CKeyboardDlg();

// Dialog Data
	//{{AFX_DATA(CKeyboardDlg)
	enum { IDD = IDD_KEYBOARD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyboardDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CRect m_rect[12];

	// Generated message map functions
	//{{AFX_MSG(CKeyboardDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnTouchMsg(WPARAM, LPARAM);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYBOARDDLG_H__2E83B372_742E_4CE0_A6DC_6BFB369B8A4C__INCLUDED_)
