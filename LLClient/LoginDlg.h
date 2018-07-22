#pragma once
#include "../Controls/ImgButton.h"
#include "../Controls/StaticText.h"
#include "../Controls/GlassButton.h"
#include "../Controls/Base_Dlg.h"
#include "../Controls/ImgGlassButton.h"
// CLoginDlg dialog

class CLoginDlg : public CBase_Dlg
{
	DECLARE_DYNAMIC(CLoginDlg)
	
public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoginDlg();

// Dialog Data
	enum { IDD = IDD_LOGIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
protected:
	CImgButton			m_btnLog;
	CImgGlassButton     m_btnExit;
	CImgGlassButton		m_btnSetting;
	CImgButton			m_btnUser;
	CImgButton			m_btnPassword;
	CImgButton			m_btnIP;
	CImgButton			m_btnPort;

	CGlassButton		m_btnOk;
	CGlassButton		m_btnCancel;
	CGlassButton        m_btnLogin;

	CEdit               m_editUser;
	CEdit               m_editPW;
	CEdit				m_editPort;
	CIPAddressCtrl		m_ipAddressIp;

	CButton				m_checkAutoLogin;
	CButton             m_checkRemPw;

protected:
	enum ShowState
	{
		LOGIN_STATE=0,
		SETTING_STATE=1,
	};
	void				SetShowState(ShowState state);
	
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnSetting();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnLogin();
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnBnClickedCheckAutoLogin();
	afx_msg void OnBnClickedCheckRememberPw();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
