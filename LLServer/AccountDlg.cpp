// AccountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LLServer.h"
#include "AccountDlg.h"
#include "afxdialogex.h"
#include "AccountDlg.h"

// CAccountDlg dialog

IMPLEMENT_DYNAMIC(CAccountDlg, CDialogEx)

CAccountDlg::CAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAccountDlg::IDD, pParent)
{

}

CAccountDlg::~CAccountDlg()
{
}

void CAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_ACCOUNT, m_treeAccount);
	DDX_Control(pDX, IDC_STATIC_ACCOUNT_ID, m_staAccountId);
	DDX_Control(pDX, IDC_STATIC_ACCOUNT_NAME, m_staAccountName);
	DDX_Control(pDX, IDC_BUTTON_ADD_ACCOUNT, m_btnAddAccount);
	DDX_Control(pDX, IDC_BUTTON_DELETE_ACCOUNT, m_btnDeleteAccount);
}


BEGIN_MESSAGE_MAP(CAccountDlg, CDialogEx)
END_MESSAGE_MAP()


// CAccountDlg message handlers


BOOL CAccountDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_staAccountId.SetFontSize(10);
	m_staAccountName.SetFontSize(10);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
