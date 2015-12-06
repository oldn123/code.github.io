// base.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "base.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CBaseApp

BEGIN_MESSAGE_MAP(CBaseApp, CWinApp)
	//{{AFX_MSG_MAP(CBaseApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseApp construction

CBaseApp::CBaseApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBaseApp object

CBaseApp theApp;


HHOOK g_hMouse=NULL;
HHOOK g_hKeyboard=NULL;

CRect g_keyRect[50];
enum{SK_0 = 0,
SK_1, 
SK_2,
SK_3,
SK_4,
SK_5,
SK_6,
SK_7,
SK_8,
SK_9,

SK_A,
SK_B,
SK_C,
SK_D,
SK_E,
SK_F,
SK_G,

SK_H,
SK_I,
SK_J,
SK_K,
SK_L,
SK_M,
SK_N,

SK_O,
SK_P,
SK_Q,

SK_R,
SK_S,
SK_T,

SK_U,
SK_V,
SK_W,

SK_X,
SK_Y,
SK_Z,

SK_BACKSPASE,
SK_ENTER,
SK_SHIFT,
SK_CAPSLOOK
};

#pragma data_seg("MySec")
HWND g_hWnd=NULL;
#pragma data_seg()

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CRect rectWnd;
	CRect rectBtn;
	CPoint point;

	GetClientRect(g_hWnd, rectWnd);

	point.x = rectWnd.left;
	point.y = rectWnd.top;

	ClientToScreen(g_hWnd, &point);
	if (wParam  == WM_LBUTTONDOWN)//µ¥»÷
	{
		rectWnd.top    = point.y;
		rectWnd.left   = point.x;
		rectWnd.right  = rectWnd.right + point.x;
		rectWnd.bottom = rectWnd.right + point.y;

		if (rectWnd.PtInRect(((MOUSEHOOKSTRUCT*)lParam)->pt))//ÔÚÆÁÄ»¼üÅÌÉÏ
		{
			for (int i=0; i<12; i++)
			{
				rectBtn.top    = g_keyRect[i].top  + rectWnd.top;
				rectBtn.left   = g_keyRect[i].left + rectWnd.left;
				rectBtn.bottom = rectBtn.top  + 70;
				rectBtn.right  = rectBtn.left + 74;

				if (rectBtn.PtInRect(((MOUSEHOOKSTRUCT*)lParam)->pt))//ÔÚÆÁÄ»¼üÅÌÉÏ
				{
					switch (i)
					{
					case 0:
						{
							keybd_event(0x37, 0, 0, 0);
							keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
						}
					break;
					case 1:
						{
							keybd_event(0x38, 0, 0, 0);
							keybd_event(0x38, 0, KEYEVENTF_KEYUP, 0);
						}
					break;
					case 2:
						{
							keybd_event(0x39, 0, 0, 0);
							keybd_event(0x39, 0, KEYEVENTF_KEYUP, 0);
						}
					break;
					case 3:
						{
							keybd_event(0x34, 0, 0, 0);
							keybd_event(0x34, 0, KEYEVENTF_KEYUP, 0);
						}
					break;
					case 4:
						{
							keybd_event(0x35, 0, 0, 0);
							keybd_event(0x35, 0, KEYEVENTF_KEYUP, 0);
						}
					break;
					case 5:
						{
							keybd_event(0x36, 0, 0, 0);
							keybd_event(0x36, 0, KEYEVENTF_KEYUP, 0);
						}
					break;
					case 6:
						{
							keybd_event(0x31, 0, 0, 0);
							keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
						}
					break;
					case 7:
						{
							keybd_event(0x32, 0, 0, 0);
							keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
						}
					break;
					case 8:
						{
							keybd_event(0x33, 0, 0, 0);
							keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
						}
					break;
					case 9:
						{
							keybd_event(VK_BACK, 0, 0, 0);
							keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0);
						}
					break;
					case 10:
						{
							keybd_event(0x30, 0, 0, 0);
							keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
						}
					break;
					case 11:
						{
							keybd_event(VK_RETURN, 0, 0, 0);
							keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
						}
					break;

					default:
						break;
					}
				}
			}
			return 1;
		}
	}
	return CallNextHookEx(g_hMouse, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if(VK_F2==wParam)
	{
		SendMessage(g_hWnd, WM_CLOSE, 0, 0);
		UnhookWindowsHookEx(g_hMouse);
		UnhookWindowsHookEx(g_hKeyboard);
	}
	return CallNextHookEx(g_hKeyboard, code, wParam, lParam);
}

_declspec(dllexport) void SetHook(HWND hwnd)
{
	g_hWnd=hwnd;
	g_hMouse=SetWindowsHookEx(WH_MOUSE, MouseProc, GetModuleHandle("base"), 0);
	g_hKeyboard=SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, GetModuleHandle("base"), 0);
}

_declspec(dllexport) void SetKeyRect(int index, CRect rect)
{
	g_keyRect[index] = rect;
}