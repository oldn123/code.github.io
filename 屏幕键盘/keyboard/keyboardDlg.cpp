// keyboardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "keyboard.h"
#include "keyboardDlg.h"
#include "vector"
#include "map"
using namespace  std;

typedef UINT* LPUINT;		
#include <GdiPlus.h>
using namespace Gdiplus;
#pragma comment( lib, "gdiplus.lib" )

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CPaintBtn;
std::vector<CPaintBtn*>				g_arrBtns;
std::map<UINT, CPaintBtn*>			g_mapTimer;

#define OFFSET_X 5
#define OFFSET_Y 5
void DrawRoundRectange(Graphics &g,Color pens,int x,int y,int width,int height)
{
	//设置画图时的滤波模式为消除锯齿现象
	g.SetSmoothingMode(SmoothingModeAntiAlias);

	//创建一个红色的画笔
	Pen po(pens,1);
	Pen *pen = &po;

	//画矩形上面的边
	g.DrawLine(pen,x+OFFSET_X,y,width-OFFSET_X,y);

	//画矩形下面的边
	g.DrawLine(pen,x+OFFSET_X,y+height,width-OFFSET_X,y+height);

	//画矩形左面的边
	g.DrawLine(pen,x,y+OFFSET_Y,x,y+height-OFFSET_Y);

	//画矩形右面的边
	g.DrawLine(pen,x+width,y+OFFSET_Y,x+width,y+height-OFFSET_Y);

	//画矩形左上角的圆角
	g.DrawArc(pen,x,y,OFFSET_X*2,OFFSET_Y*2,180,90);

	//画矩形右下角的圆角
	g.DrawArc(pen,x+width-OFFSET_X*2,y+height-OFFSET_Y*2,OFFSET_X*2,OFFSET_Y*2,360,90);

	//画矩形右上角的圆角
	g.DrawArc(pen,x+width-OFFSET_X*2,y,OFFSET_X*2,OFFSET_Y*2,270,90);

	//画矩形左下角的圆角
	g.DrawArc(pen,x,y+height-OFFSET_Y*2,OFFSET_X*2,OFFSET_Y*2,90,90);

}

/* 填充颜色 */
void FillRoundRectangle(Graphics &g,Color color,int x,int y,int width,int height)
{
	//矩形填充的步骤：
	//1、把圆角矩形画分为四个圆角上分成四个同等的扇形外加三个直角矩形
	//2、先填充三个直角矩形
	//3、然后填充四个角上的扇形
	SolidBrush sb(color);

	//创建画刷
	Brush *brush = &sb;

	//填充三个直角矩形

	g.FillRectangle(brush,x,y+OFFSET_Y,width,height-OFFSET_Y*2);
	g.FillRectangle(brush,x+OFFSET_X,y,width-OFFSET_X*2,height);

	//填充四个角上的扇形区
	//填充左上角扇形
#define PIE_OFFSET 2
	g.FillPie(brush,x,y,OFFSET_X*2+PIE_OFFSET,OFFSET_Y*2+PIE_OFFSET,180,90);

	//填充右下角的扇形
	g.FillPie(brush,x+width-(OFFSET_X*2+PIE_OFFSET),y+height-(OFFSET_Y*2+PIE_OFFSET),OFFSET_X*2+PIE_OFFSET,OFFSET_Y*2+PIE_OFFSET,360,90);

	//填充右上角的扇形
	g.FillPie(brush,x+width-(OFFSET_X*2+PIE_OFFSET),y,(OFFSET_X*2+PIE_OFFSET),(OFFSET_Y*2+PIE_OFFSET),270,90);

	//填充左下角的扇形
	g.FillPie(brush,x,y+height-(OFFSET_X*2+PIE_OFFSET),(OFFSET_X*2+PIE_OFFSET),(OFFSET_Y*2+PIE_OFFSET),90,90);

}


class CPaintBtn
{
public:
	CPaintBtn(CWnd * p, int id){
		m_pHotBtn = NULL;
		m_pWnd = p;
		m_strText = L"";
		m_nTouchStatus = -1;
		m_ntid = 0;
		m_nleaveCnt = 0;
		m_nId = id;
	}
	~CPaintBtn(){

	}

	void SetBtnRect(CString strText, CRect rc){m_rcBtn = rc;}
	void OnPaint(Graphics & graphics){

		//DrawRoundRectange(graphics, m_colBtn, m_rcBtn.left, m_rcBtn.top, m_rcBtn.Width(), m_rcBtn.Height());
		
		FillRoundRectangle(graphics, m_colBtn, m_rcBtn.left, m_rcBtn.top, m_rcBtn.Width(), m_rcBtn.Height());

		Gdiplus::Font ff(L"Arial", 16);
		Color cl(255,255,255);
		SolidBrush sb(cl);
		RectF rcText(m_rcBtn.left + 10, m_rcBtn.top + 10, 50, 30);
		StringFormat sf;
		graphics.DrawString((LPCTSTR)m_strText, _tcslen((LPCTSTR)m_strText), &ff, rcText, &sf, &sb);
	}

	BOOL TestPoint(CPoint pt){
		if (m_rcBtn.PtInRect(pt))
		{
			return TRUE;
		}
		return FALSE;
	}

	void OnTouchDown( CPoint pt ){
		
		m_pHotBtn = this;
		m_nTouchStatus = 1;
		m_colBtn.SetFromCOLORREF(RGB(90,90,90));
		m_pWnd->InvalidateRect(&m_rcBtn);
		if (m_pWnd)
		{
			m_ntid = m_pWnd->SetTimer(100, 60, NULL);
			g_mapTimer[m_ntid] = this;
		}
	}

	void OnTouchIn( CPoint pt ){
		if (m_pHotBtn)
		{
			m_pHotBtn->OnTouchOut(pt);
		}
		m_pHotBtn = this;
		m_nTouchStatus = 3;
		m_colBtn.SetFromCOLORREF(RGB(90,90,90));
		m_pWnd->InvalidateRect(&m_rcBtn);
		if (m_pWnd && m_ntid == 0)
		{
			m_ntid = m_pWnd->SetTimer(100, 60, NULL);
		}
	}

	void OnTouchUp( CPoint pt ){
		m_nTouchStatus = 2;
		m_pHotBtn = NULL;
	}

	void OnTouchOut( CPoint pt ){
		m_nTouchStatus = 4;
	}

	void OnTouchMove( CPoint pt ){
		if (!m_rcBtn.PtInRect(pt))
		{
			return;
		}
		if (m_nTouchStatus == -1)
		{
			OnTouchIn(pt);
		}
	}

	void OnTimer(UINT utid)
	{
		if (m_pWnd && utid == m_ntid)
		{
			int nr = m_colBtn.GetR();
			int ng = m_colBtn.GetG();
			int nb = m_colBtn.GetB();

			if (m_nTouchStatus == 2 ||
				m_nTouchStatus == 4)
			{	
				nr = --nr < 0 ? 0 : nr;
				ng = --ng < 0 ? 0 : ng;
				nb = --nb < 0 ? 0 : nb;
				m_colBtn.SetFromCOLORREF(RGB(nr, ng, nb));

				m_nleaveCnt++;
				if (m_nleaveCnt > 100)
				{
					g_mapTimer.erase(m_ntid);
					m_pWnd->KillTimer(m_ntid);
					m_ntid = 0;
					m_nleaveCnt = 0;			
				}
			}
			else
			{
				nr = ++nr > 200 ? 200 : nr;
				ng = ++ng > 200 ? 200 : ng;
				nb = ++nb > 200 ? 200 : nb;
				m_colBtn.SetFromCOLORREF(RGB(nr, ng, nb));
			}
			m_pWnd->InvalidateRect(&m_rcBtn);
		}
	}
protected:
	CString		m_strText;
	CRect		m_rcBtn;
	int			m_nTouchStatus;
	CWnd*		m_pWnd;
	UINT		m_ntid;
	Color		m_colBtn;
	int			m_nleaveCnt;
	int			m_nId;
	static CPaintBtn* m_pHotBtn;
};

CPaintBtn* CPaintBtn::m_pHotBtn = NULL;

CPaintBtn* BtnFromPoint(CPoint pt)
{
	int nCnt = g_arrBtns.size();
	for (int i = 0; i < nCnt; i++)
	{
		if (g_arrBtns[i]->TestPoint(pt))
		{
			return g_arrBtns[i];
		}
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


GdiplusStartupInput g_GdiPlusStartupInput;
ULONG_PTR g_GdiPlusToken = 0;

void InitGDIPlus()
{
	GdiplusStartup(&g_GdiPlusToken, &g_GdiPlusStartupInput, NULL);
}

void UnInitGDIPlus()
{
	GdiplusShutdown(g_GdiPlusToken);
}

/////////////////////////////////////////////////////////////////////////////
// CKeyboardDlg dialog


CKeyboardDlg::CKeyboardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyboardDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKeyboardDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for (int y=0; y<4; y++)
	{
		for (int x=0; x<3; x++)
		{
			m_rect[3*y+x].left   = 4 + 78*x;
			m_rect[3*y+x].top    = 4 + 74*y;
			m_rect[3*y+x].right  = 4 + 78*x + 74;
			m_rect[3*y+x].bottom = 4 + 74*y + 70;
		}
	}

	InitGDIPlus();
}

CKeyboardDlg::~CKeyboardDlg()
{
	UnInitGDIPlus();
}

void CKeyboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyboardDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKeyboardDlg, CDialog)
	//{{AFX_MSG_MAP(CKeyboardDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_MESSAGE(0x240, OnTouchMsg)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyboardDlg message handlers88



BOOL CKeyboardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	RegisterTouchWindow();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);

	for (int i=0; i<12; i++)
	{
		CPaintBtn * ppb = new CPaintBtn(this, i);
		g_arrBtns.push_back(ppb);

		CString ss;
		ppb->SetBtnRect(ss, m_rect[i]);
		SetKeyRect(i, m_rect[i]);
	}

	//SetHook(this->m_hWnd);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKeyboardDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKeyboardDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}

	CPaintDC dc(this); 
	Graphics graphics( dc.m_hDC );
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
	int ncnt = g_arrBtns.size();
	for (int i = 0; i < ncnt; i++)
	{
		g_arrBtns[i]->OnPaint(graphics);
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKeyboardDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


HWND  g_hFocusWnd = 0;

BOOL CKeyboardDlg::PreTranslateMessage(MSG* pMsg)
{

	return CDialog::PreTranslateMessage(pMsg);

	HWND wnd = ::GetForegroundWindow();
	if(IsWindow(wnd))
	{
		if(wnd != m_hWnd)
		{
			if(g_hFocusWnd != wnd)
			{
				if(!IsWindow(g_hFocusWnd))
				{
					AttachThreadInput(
						GetWindowThreadProcessId(m_hWnd, NULL),
						GetWindowThreadProcessId(g_hFocusWnd, NULL),
						FALSE);
				}

				g_hFocusWnd = wnd;
				AttachThreadInput(
					GetWindowThreadProcessId(m_hWnd, NULL),
					GetWindowThreadProcessId(g_hFocusWnd, NULL),
					TRUE);
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CKeyboardDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnTimer(nIDEvent);

	if (g_mapTimer.count(nIDEvent))
	{
		g_mapTimer[nIDEvent]->OnTimer(nIDEvent);
	}
}

LRESULT CKeyboardDlg::OnTouchMsg(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = GetSafeHwnd();
	CPoint ptNow;
	UINT msg = 0;
	static HMODULE hUserDll = GetModuleHandleW(L"user32.dll");
	if(!hUserDll){
		return false;
	}

	typedef	BOOL (__stdcall *PFNGETTOUCHINPUTINFO)(HANDLE, UINT, PTOUCHINPUT, int);
	static PFNGETTOUCHINPUTINFO pfGetTouchInputInfo = (PFNGETTOUCHINPUTINFO)GetProcAddress(hUserDll, "GetTouchInputInfo");

	if (pfGetTouchInputInfo == NULL)
	{
		return false;
	}

	unsigned int numInputs = (unsigned int) wParam; 
	TOUCHINPUT* ti = new TOUCHINPUT[numInputs]; 
	if((*pfGetTouchInputInfo)((HTOUCHINPUT)lParam, numInputs, ti, sizeof(TOUCHINPUT)))
	{
		// For each contact, dispatch the message to the appropriate message handler.
		for(unsigned int i=0; i< numInputs; ++i)
		{
			ptNow.x = TOUCH_COORD_TO_PIXEL(ti[i].x);
			ptNow.y = TOUCH_COORD_TO_PIXEL(ti[i].y);
			::ScreenToClient(hWnd, &ptNow);

			int ncnt = g_arrBtns.size();
			if(ti[i].dwFlags & 0x0002/*TOUCHEVENTF_DOWN*/)
			{
				for (int i = 0; i < ncnt; i++)
				{
					g_arrBtns[i]->OnTouchDown(ptNow);
				}
			}
			else if(ti[i].dwFlags & 0x0001/*TOUCHEVENTF_MOVE*/)
			{
				for (int i = 0; i < ncnt; i++)
				{
					g_arrBtns[i]->OnTouchMove(ptNow);
				}
			}
			else if(ti[i].dwFlags & 0x0004/*TOUCHEVENTF_UP*/)
			{
				for (int i = 0; i < ncnt; i++)
				{
					g_arrBtns[i]->OnTouchUp(ptNow);
				}
			}

		}
	}

	delete [] ti;

	CloseTouchInputHandle((HTOUCHINPUT)lParam);

	MSG mm;
	while (::PeekMessage(&mm, m_hWnd, 0x201, 0x203, PM_REMOVE))
	{
		TRACE(L"PeekMessage\n");
	}
	return 1;
}


void CKeyboardDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnLButtonDown(nFlags, point);

	CPaintBtn * pBtn = BtnFromPoint(point);
	if (pBtn)
	{
		pBtn->OnTouchDown(point);
	}

}


void CKeyboardDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnLButtonUp(nFlags, point);

	CPaintBtn * pBtn = BtnFromPoint(point);
	if (pBtn)
	{
		pBtn->OnTouchUp(point);
	}
}


void CKeyboardDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnMouseMove(nFlags, point);

	CPaintBtn * pBtn = BtnFromPoint(point);
	if (pBtn)
	{
		pBtn->OnTouchMove(point);
	}
}


LRESULT CKeyboardDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	LRESULT l = CDialog::OnNcHitTest(point);

	if (!BtnFromPoint(point))
	{
		l = HTCAPTION;
	}
	else
	{
		l = HTCLIENT;
	}
	return l;
}
