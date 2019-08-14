
// MFCTrayIconDlg.h : header file
//

#pragma once


// CMFCTrayIconDlg dialog
class CMFCTrayIconDlg : public CDialogEx
{
// Construction
public:
	CMFCTrayIconDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTRAYICON_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
private:
	CMenu m_menu;
	NOTIFYICONDATA m_TrayData;
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnTrayNotify(WPARAM wp, LPARAM lp);
	afx_msg void OnItem1();
	afx_msg void OnItem2();
	afx_msg void OnItem3();
	afx_msg void OnExit();

	void OnTrayContextMenu();
};
