// OptionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LLServer.h"
#include "OptionDlg.h"
#include "afxdialogex.h"


// COptionDlg dialog

IMPLEMENT_DYNAMIC(COptionDlg, CDialogEx)

COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
: CBase_Dlg(COptionDlg::IDD, pParent)
{

}

COptionDlg::~COptionDlg()
{
}

void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_DEPARTMENT, m_btnDepartment);
	DDX_Control(pDX, IDC_BTN_ACCOUNT, m_btnAccount);
}


BEGIN_MESSAGE_MAP(COptionDlg, CBase_Dlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_DEPARTMENT, &COptionDlg::OnBnClickedBtnDepartment)
	ON_BN_CLICKED(IDC_BTN_ACCOUNT, &COptionDlg::OnBnClickedBtnAccount)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// COptionDlg message handlers


BOOL COptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	m_btnDepartment.SetImageName(IDB_PNG_DEPARTMENT);
	m_btnDepartment.SetButtonType(BUTTON_TYPE_CUSTOM);
	m_btnDepartment.SetFontColor(COLOR_BLACK);
	m_btnAccount.SetImageName(IDB_PNG_ACCOUNT);
	m_btnAccount.SetButtonType(BUTTON_TYPE_CUSTOM);
	m_btnAccount.SetFontColor(COLOR_BLACK);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void COptionDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	CRect rc;
	GetClientRect(rc);
	dc.FillSolidRect(rc, RGB(255, 255, 255));
}


void COptionDlg::OnBnClickedBtnDepartment()
{
	// TODO: Add your control notification handler code here
	::SendMessage(GetParent()->m_hWnd, MSG_CHILD2FATHER_DEPARTMENT,NULL,NULL);
}


void COptionDlg::OnBnClickedBtnAccount()
{
	// TODO: Add your control notification handler code here
	::SendMessage(GetParent()->m_hWnd, MSG_CHILD2FATHER_ACCOUNT, NULL, NULL);
}


HBRUSH COptionDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = __super::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
