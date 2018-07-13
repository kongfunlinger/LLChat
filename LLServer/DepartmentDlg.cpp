// DepartmentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LLServer.h"
#include "DepartmentDlg.h"
#include "afxdialogex.h"


// CDepartmentDlg dialog

IMPLEMENT_DYNAMIC(CDepartmentDlg, CDialogEx)

CDepartmentDlg::CDepartmentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDepartmentDlg::IDD, pParent)
{

}

CDepartmentDlg::~CDepartmentDlg()
{
}

void CDepartmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_DEPARTMENT, m_treeDepartment);
	DDX_Control(pDX, IDC_CUR_NODE, m_staCurNode);
	DDX_Control(pDX, IDC_CUR_DEPATMENT_NAME, m_staCurDepartment);
	DDX_Control(pDX, IDC_CUR_NODE_INFO, m_editCurNodeInfo);
	DDX_Control(pDX, IDC_CUR_DEPATMENT_INFO, m_editCurDepartmentInfo);
}


BEGIN_MESSAGE_MAP(CDepartmentDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD_DEPATMENT, &CDepartmentDlg::OnBnClickedBtnAddDepatment)
END_MESSAGE_MAP()


// CDepartmentDlg message handlers


BOOL CDepartmentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_staCurNode.SetFontSize(10);
	m_staCurDepartment.SetFontSize(10);
	



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDepartmentDlg::OnBnClickedBtnAddDepatment()
{
	// TODO: Add your control notification handler code here
	DepartmentInfo info;
	info.nDepartID = 2;
	info.nParentId = 0;
	info.strDepartName = "≤‚ ‘≤ø";
	m_mysqlOperate.InsertDepartmentInfo(info);
	
}
