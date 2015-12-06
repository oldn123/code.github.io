; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CKeyboardDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "keyboard.h"

ClassCount=4
Class1=CKeyboardApp
Class2=CKeyboardDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_KEYBOARD_DIALOG

[CLS:CKeyboardApp]
Type=0
HeaderFile=keyboard.h
ImplementationFile=keyboard.cpp
Filter=N

[CLS:CKeyboardDlg]
Type=0
HeaderFile=keyboardDlg.h
ImplementationFile=keyboardDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=keyboardDlg.h
ImplementationFile=keyboardDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_KEYBOARD_DIALOG]
Type=1
Class=CKeyboardDlg
ControlCount=3
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC,static,1342177294

