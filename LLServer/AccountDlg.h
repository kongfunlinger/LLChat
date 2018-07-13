#pragma once
#include "..//Controls///StaticText.h"
#include "..//Controls//GlassButton.h"

// CAccountDlg dialog

class CAccountDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAccountDlg)

public:
	CAccountDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAccountDlg();

// Dialog Data
	enum { IDD = IDD_ACCOUNT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

protected:
	CTreeCtrl           m_treeAccount;

	CStaticText         m_staAccountId;
	CEdit               m_editAccountId;
	CStaticText         m_staAccountName;
	CEdit				m_editAccountName;
	CStaticText         m_staAccountPw;
	CEdit				m_editAccountPw;
	CStaticText         m_staAccountSex;
	CComboBox			m_combAccountSex;
	CStaticText         m_staAccountDep;
	CEdit				m_editAccountDep;
	CStaticText         m_staAccountHs;
	CEdit				m_editAccountHs;
	CStaticText			m_staCurAccount;
	CEdit				m_editCurAccount;
	CEdit				m_editCurAccountId;
	CStaticText			m_staCurDepartId;
	CEdit				m_editCurDepartId;



	CGlassButton        m_btnAddAccount;
	CGlassButton        m_btnDeleteAccount;


	CImageList          m_ImageList;
protected:
	void                RefreshTreeCtrl();
	void				InsertChildItem(HTREEITEM hItem, int nId);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAddAccount();
	afx_msg void OnBnClickedButtonDeleteAccount();
	afx_msg void OnTvnSelchangedTreeAccount(NMHDR *pNMHDR, LRESULT *pResult);
};
