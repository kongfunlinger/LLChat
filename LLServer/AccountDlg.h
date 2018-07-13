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
	CStaticText         m_staAccountName;
	CGlassButton        m_btnAddAccount;
	CGlassButton        m_btnDeleteAccount;

public:
	virtual BOOL OnInitDialog();
};
