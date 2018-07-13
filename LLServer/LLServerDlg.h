
// LLServerDlg.h : header file
//

#pragma once
#include "../Controls/ImgButton.h"
#include "../Controls/StaticText.h"
#include "OptionDlg.h"
#include "DepartmentDlg.h"
#include "AccountDlg.h"
// CLLServerDlg dialog
class CLLServerDlg : public CDialogEx
{
// Construction
public:
	CLLServerDlg(CWnd* pParent = NULL);	// standard constructor


// Dialog Data
	enum { IDD = IDD_LLSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	CImgButton                   m_btnLog;
	CStaticText                  m_staTitle;

	CAccountDlg                  m_accountDlg;
	CDepartmentDlg               m_departmentDlg;
	COptionDlg                   m_optionDlg;
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
protected:
	afx_msg LRESULT OnDepartmentWndSwitch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAccountWndSwitch(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedBtnLog();
};
