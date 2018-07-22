// DepartmentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LLServer.h"
#include "DepartmentDlg.h"
#include "afxdialogex.h"
#include "Utils.h"

// CDepartmentDlg dialog

IMPLEMENT_DYNAMIC(CDepartmentDlg, CDialogEx)

CDepartmentDlg::CDepartmentDlg(CWnd* pParent /*=NULL*/)
: CBase_Dlg(CDepartmentDlg::IDD, pParent)
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


void CDepartmentDlg::RefreshTreeCtrl()
{
	auto insertDepartinfo = [&](DepartmentInfo& info,HTREEITEM hParent)
	{
		HTREEITEM hItem = m_treeDepartment.InsertItem(info.strDepartName, 1, 0, hParent);
		
		//将每一个节点关联一个数据，数据第字节表示当前部门id，高字节表示父部门的id
		DWORD dwData = MAKELPARAM(info.nDepartID, info.nParentId);
		m_treeDepartment.SetItemData(hItem, dwData);

		//将所有属于此节点的子节点添加进来
		InsertChildItem(hItem, info.nDepartID);
	};

	m_treeDepartment.DeleteAllItems();

	CString strDepartOri;
	strDepartOri.LoadStringW(IDS_DEPART_ORGANIZATION);
	HTREEITEM hRoot = m_treeDepartment.InsertItem(strDepartOri);
	if (CLLMysqlOperate::getSingletonPtr())
	{
		//获取以及部门信息
		vector<DepartmentInfo> vecDepartInfo = CLLMysqlOperate::getSingletonPtr()->GetDepartmentVecByParentId(0);
		for (int i = 0; i < vecDepartInfo.size();++i)
		{
			insertDepartinfo(vecDepartInfo.at(i),hRoot);
		}
		m_treeDepartment.Expand(hRoot, TVE_EXPAND);
	}


}

void CDepartmentDlg::InsertChildItem(HTREEITEM hParent, int nId)
{
	if (hParent == nullptr)
	{
		return;
	}

	if (CLLMysqlOperate::getSingletonPtr())
	{
		vector<DepartmentInfo> vecDepart = CLLMysqlOperate::getSingletonPtr()->GetDepartmentVecByParentId(nId);
		for (int i = 0; i < vecDepart.size();++i)
		{
			DepartmentInfo& info = vecDepart.at(i);
			HTREEITEM hItem = m_treeDepartment.InsertItem(info.strDepartName, 1, 0, hParent);

			//将每一个节点关联一个数据，数据第字节表示当前部门id，高字节表示父部门的id
			DWORD dwData = MAKELPARAM(info.nDepartID, info.nParentId);
			m_treeDepartment.SetItemData(hItem, dwData);

			InsertChildItem(hItem, info.nDepartID);

		}
	}

}

BEGIN_MESSAGE_MAP(CDepartmentDlg, CBase_Dlg)
	ON_BN_CLICKED(IDC_BTN_ADD_DEPATMENT, &CDepartmentDlg::OnBnClickedBtnAddDepatment)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_DEPARTMENT, &CDepartmentDlg::OnTvnSelchangedTreeDepartment)
	ON_BN_CLICKED(IDC_BTN_DELETE_DEPATMENT, &CDepartmentDlg::OnBnClickedBtnDeleteDepatment)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDepartmentDlg message handlers


BOOL CDepartmentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_staCurNode.SetFontSize(10);
	m_staCurDepartment.SetFontSize(10);
	
	m_ImageList.Create(16, 16, ILC_COLOR32 | ILC_MASK, 1, 0);
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_BITMAP_DEPART);
	m_ImageList.Add(&bmp, RGB(0, 0, 0));
	CBitmap bmpSel;
	bmpSel.LoadBitmapW(IDB_BITMAP_DEPART_SEL);
	m_ImageList.Add(&bmpSel, RGB(0, 0, 0));
	m_treeDepartment.SetImageList(&m_ImageList, TVSIL_NORMAL);
	RefreshTreeCtrl();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDepartmentDlg::OnBnClickedBtnAddDepatment()
{
	// TODO: Add your control notification handler code here

	CString strDepartName;
	m_editCurDepartmentInfo.GetWindowText(strDepartName);
	if (strDepartName.IsEmpty())
	{
		return;
	}

	DepartmentInfo info;
	info.strDepartName = strDepartName;

	HTREEITEM hItem = m_treeDepartment.GetSelectedItem();
	if (hItem ==NULL)
	{
		return;
	}

	DWORD dwData = m_treeDepartment.GetItemData(hItem);
	info.nParentId = LOWORD(dwData);
	info.nDepartID = CLLMysqlOperate::getSingletonPtr()->GetNewDepartId();

	hItem = m_treeDepartment.InsertItem(strDepartName, 1, 0, hItem);

	

	dwData = MAKELPARAM(info.nDepartID, info.nParentId);
	m_treeDepartment.SetItemData(hItem, dwData);

	if (CLLMysqlOperate::getSingletonPtr())
	{
		CLLMysqlOperate::getSingletonPtr()->InsertDepartmentInfo(info);

	}

	m_editCurDepartmentInfo.SetWindowTextW(_T(""));
	m_treeDepartment.Invalidate();
	
	
}


void CDepartmentDlg::OnTvnSelchangedTreeDepartment(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeDepartment.GetSelectedItem();
	if (hItem != NULL)
	{
		m_editCurNodeInfo.SetWindowTextW(m_treeDepartment.GetItemText(hItem));
	}
	else
	{
		m_editCurNodeInfo.SetWindowTextW(_T(""));
	}
	*pResult = 0;
}


void CDepartmentDlg::OnBnClickedBtnDeleteDepatment()
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeDepartment.GetSelectedItem();
	if (hItem == NULL)
	{
		return;
	}
	DWORD dwData = m_treeDepartment.GetItemData(hItem);
	if (dwData == NULL)
	{
		CString strInfo;
		strInfo.LoadStringW(IDS_NOT_SELECT_NODE);
		CString strTitle;
		strTitle.LoadStringW(IDS_WARNING);
		MessageBox(strInfo, strTitle, MB_ICONWARNING);
		return;
	}

	int nDepartId = LOWORD(dwData);
	if (CLLMysqlOperate::getSingletonPtr())
	{
		CLLMysqlOperate::getSingletonPtr()->DeleteDepartmentById(nDepartId);
	}

	m_treeDepartment.DeleteItem(hItem);

	m_treeDepartment.Invalidate();
	
	
	
}


HBRUSH CDepartmentDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CBase_Dlg::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
