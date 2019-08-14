
// MFCTrayIconDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCTrayIcon.h"
#include "MFCTrayIconDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCTrayIconDlg dialog

#define WM_TRAY_MESSAGE (WM_USER + 1)

CMFCTrayIconDlg::CMFCTrayIconDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTRAYICON_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_TrayData = { 0 };
}

void CMFCTrayIconDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCTrayIconDlg, CDialogEx)
	ON_WM_PAINT()
	ON_MESSAGE(WM_TRAY_MESSAGE, OnTrayNotify)
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_ITEM1, OnItem1)
	ON_COMMAND(ID_MENU_ITEM2, OnItem2)
	ON_COMMAND(ID_MENU_ITEM3, OnItem3)
	ON_COMMAND(ID_MENU_EXIT, OnExit)
	ON_BN_CLICKED(IDOK, &CMFCTrayIconDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCTrayIconDlg message handlers

BOOL CMFCTrayIconDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCTrayIconDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCTrayIconDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CMFCTrayIconDlg::OnTrayNotify(WPARAM wp, LPARAM lp)
{
	UINT uiMsg = (UINT)lp;

	switch (uiMsg)
	{
	case WM_RBUTTONUP:
		OnTrayContextMenu();
		return 1;
	case WM_LBUTTONUP:
		OnTrayContextMenu();
		return 1;
	case WM_LBUTTONDBLCLK:
		Shell_NotifyIcon(NIM_DELETE, &m_TrayData);
		ShowWindow(SW_SHOWNORMAL);
		return 1;
	}

	return 0;
}

void CMFCTrayIconDlg::OnItem1()
{
	MessageBox(_T("Item 1"));
}

void CMFCTrayIconDlg::OnItem2()
{
	MessageBox(_T("Item 2"));
}

void CMFCTrayIconDlg::OnItem3()
{
	MessageBox(_T("Item 3"));
}

void CMFCTrayIconDlg::OnExit()
{
	Shell_NotifyIcon(NIM_DELETE, &m_TrayData);
	DestroyWindow();
}

void CMFCTrayIconDlg::OnTrayContextMenu()
{
	if (!m_menu)
	{
		BOOL bMenu = FALSE;
		bMenu = m_menu.LoadMenu(IDR_MENU);
		if (!bMenu) MessageBox(_T("Unabled to load menu"));
	}
	CPoint pt;
	GetCursorPos(&pt);
	SetForegroundWindow();
	m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_BOTTOMALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, pt.x, pt.y, this);
}

void CMFCTrayIconDlg::OnBnClickedOk()
{
	m_TrayData.cbSize = sizeof(NOTIFYICONDATA);
	//Size of this structure, in bytes. 

	m_TrayData.hWnd = this->m_hWnd;
	//Handle to the window that receives notification 
	//messages associated with an icon in the taskbar 
	//status area. The Shell uses hWnd and uID to 
	//identify which icon to operate on when Shell_NotifyIcon is invoked. 

	m_TrayData.uID = 1;
	//Application-defined identifier of the taskbar icon.
	//The Shell uses hWnd and uID to identify which icon 
	//to operate on when Shell_NotifyIcon is invoked. You
	// can have multiple icons associated with a single 
	//hWnd by assigning each a different uID. 

	m_TrayData.uCallbackMessage = WM_TRAY_MESSAGE;
	//Application-defined message identifier. The system 
	//uses this identifier to send notifications to the 
	//window identified in hWnd. These notifications are 
	//sent when a mouse event occurs in the bounding 
	//rectangle of the icon, or when the icon is selected 
	//or activated with the keyboard. The wParam parameter 
	//of the message contains the identifier of the taskbar 
	//icon in which the event occurred. The lParam parameter 
	//holds the mouse or keyboard message associated with the
	// event. For example, when the pointer moves over a 
	//taskbar icon, lParam is set to WM_MOUSEMOVE. 

	m_TrayData.hIcon = this->m_hIcon;
	//Handle to the icon to be added, modified, or deleted

	_tcscpy_s(m_TrayData.szTip, _T("Tray Icon"));
	//Pointer to a null-terminated string with the text 
	//for a standard ToolTip. It can have a maximum of 64 
	//characters including the terminating NULL. 

	m_TrayData.uFlags = NIF_ICON | NIF_MESSAGE;
	//Flags that indicate which of the other members contain 
	//valid data.  

	BOOL bSuccess = FALSE;
	bSuccess = Shell_NotifyIcon(NIM_ADD, &m_TrayData);
	if (!bSuccess) MessageBox(_T("Unable to set tray icon"));
	else
	{
		this->ShowWindow(SW_MINIMIZE);
		this->ShowWindow(SW_HIDE);
	}
}
