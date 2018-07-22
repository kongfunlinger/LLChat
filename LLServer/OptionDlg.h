#pragma once

#include "../Controls/ImgGlassButton.h"
#include "../Controls/Base_Dlg.h"
// COptionDlg dialog

class COptionDlg : public CBase_Dlg
{
	DECLARE_DYNAMIC(COptionDlg)

public:
	COptionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionDlg();

// Dialog Data
	enum { IDD = IDD_OPTION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

protected:
	CImgGlassButton                    m_btnDepartment;
	CImgGlassButton                    m_btnAccount;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnDepartment();
	afx_msg void OnBnClickedBtnAccount();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
