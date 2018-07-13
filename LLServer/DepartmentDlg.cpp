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


void CDepartmentDlg::RefreshTreeCtrl()
{
	auto insertDepartinfo = [&](DepartmentInfo& info,HTREEITEM hParent)
	{
		CString strName(info.strDepartName.c_str());
		HTREEITEM hItem = m_treeDepartment.InsertItem(strName, 0, 1, hParent);
		
		//将每一个节点关联一个数据，对部门结点来说，数据低字节表示当前部门id，高字节表示父部门的id
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
		//获取一级部门信息
		vector<DepartmentInfo> vecDepartInfo = CLLMysqlOperate::getSingletonPtr()->GetDepartmentVecByParentId(0);
		for (int i = 0; i < vecDepartInfo.size();++i)
		{
			insertDepartinfo(vecDepartInfo.at(i),hRoot);
		}
		m_treeDepartment.Expand(hRoot, TVE_EXPAND);
	}


}

//此函数是递归实现除一级部门外其它各层子部门的添加
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
			CString strName(info.strDepartName.c_str());
			HTREEITEM hItem = m_treeDepartment.InsertItem(strName, 0, 1, hParent);

			//将每一个节点关联一个数据，数据低字节表示当前部门id，高字节表示父部门的id
			DWORD dwData = MAKELPARAM(info.nDepartID, info.nParentId);
			m_treeDepartment.SetItemData(hItem, dwData);

			InsertChildItem(hItem, info.nDepartID);
		}
	}
}

BEGIN_MESSAGE_MAP(CDepartmentDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD_DEPATMENT, &CDepartmentDlg::OnBnClickedBtnAddDepatment)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_DEPARTMENT, &CDepartmentDlg::OnTvnSelchangedTreeDepartment)
	ON_BN_CLICKED(IDC_BTN_DELETE_DEPATMENT, &CDepartmentDlg::OnBnClickedBtnDeleteDepatment)
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
	info.strDepartName = CUtils::w2a(strDepartName.GetString());

	HTREEITEM hItem = m_treeDepartment.GetSelectedItem();
	if (hItem ==NULL)
	{
		return;
	}

	DWORD dwData = m_treeDepartment.GetItemData(hItem);
	//获取到所选择的树形控件中的ID。然后由于上面初始化的时候DWORD的规则是低字节代表部门ID，高字节代表的是父部门的ID。
	//这里取出来其中的低字节就代表获取到了所选择结点的部门ID值，然后要执行插入子部门操作就是以此部门ID为父节点进行插入。
	//然后插入的子部门的结点值计算是通过获取到当前数据库中的最大部门ID值加1来得到的。
	info.nParentId = LOWORD(dwData);
	info.nDepartID = CLLMysqlOperate::getSingletonPtr()->GetNewDepartId();

	hItem = m_treeDepartment.InsertItem(strDepartName, 0, 1, hItem);

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
