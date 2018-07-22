// AccountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LLServer.h"
#include "AccountDlg.h"
#include "afxdialogex.h"
#include "AccountDlg.h"
#include "LLMysqlOperate.h"
#include "Utils.h"
#define USER_STATE 65535
// CAccountDlg dialog

IMPLEMENT_DYNAMIC(CAccountDlg, CDialogEx)

CAccountDlg::CAccountDlg(CWnd* pParent /*=NULL*/)
	: CBase_Dlg(CAccountDlg::IDD, pParent)
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
	DDX_Control(pDX, IDC_STATIC_ACCOUNT_PASSWORD, m_staAccountPw);
	DDX_Control(pDX, IDC_STATIC_ACCOUNT_SEX, m_staAccountSex);
	DDX_Control(pDX, IDC_STATIC_ACCOUNT_HS, m_staAccountHs);
	DDX_Control(pDX, IDC_STATIC_CUR_ACCOUNT, m_staCurAccount);
	DDX_Control(pDX, IDC_STATIC_DEPARTMENT_ID, m_staCurDepartId);

	DDX_Control(pDX, IDC_EDIT_ACCOUNT_ID, m_editAccountId);

	DDX_Control(pDX, IDC_EDIT_ACCOUNT_NAME, m_editAccountName);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT_PASSWORD, m_editAccountPw);
	DDX_Control(pDX, IDC_COMBO_SEX, m_combAccountSex);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT_DEPATMENT, m_editCurDepartName);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT_HS, m_editAccountHs);
	DDX_Control(pDX, IDC_EDIT_CUR_ACCOUNT, m_editCurAccount);
	DDX_Control(pDX, IDC_EDIT_CUR_ID, m_editCurAccountId);
	DDX_Control(pDX, IDC_EDIT_DEPARTMENT_ID, m_editCurDepartId);

	DDX_Control(pDX, IDC_BUTTON_ADD_ACCOUNT, m_btnAddAccount);
	DDX_Control(pDX, IDC_BUTTON_DELETE_ACCOUNT, m_btnDeleteAccount);
}


BEGIN_MESSAGE_MAP(CAccountDlg, CBase_Dlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD_ACCOUNT, &CAccountDlg::OnBnClickedButtonAddAccount)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ACCOUNT, &CAccountDlg::OnBnClickedButtonDeleteAccount)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_ACCOUNT, &CAccountDlg::OnTvnSelchangedTreeAccount)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAccountDlg message handlers


BOOL CAccountDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_staAccountId.SetFontSize(10);
	m_staAccountName.SetFontSize(10);

	//初始化combox
	CString strMale;
	strMale.LoadStringW(IDS_MALE);
	m_combAccountSex.AddString(strMale);
	CString strFemale;
	strFemale.LoadStringW(IDS_FEMALE);
	m_combAccountSex.AddString(strFemale);
	
	//初始化树形控件
	m_ImageList.Create(16, 16, ILC_COLOR32 | ILC_MASK, 1, 0);
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_BITMAP_DEPART);
	m_ImageList.Add(&bmp, RGB(0, 0, 0));
	CBitmap bmpSel;
	bmpSel.LoadBitmapW(IDB_BITMAP_DEPART_SEL);
	m_ImageList.Add(&bmpSel, RGB(0, 0, 0));
	CBitmap malebmp;
	malebmp.LoadBitmapW(IDB_BITMAP_MALE);
	m_ImageList.Add(&malebmp, RGB(0, 0, 0));
	CBitmap malebmpSel;
	malebmpSel.LoadBitmapW(IDB_BITMAP_MALE_SEL);
	m_ImageList.Add(&malebmpSel, RGB(0, 0, 0));
	CBitmap femalebmp;
	femalebmp.LoadBitmapW(IDB_BITMAP_FEMALE);
	m_ImageList.Add(&femalebmp, RGB(0, 0, 0));
	CBitmap femalebmpSel;
	femalebmpSel.LoadBitmapW(IDB_BITMAP_FEMALE_SEL);
	m_ImageList.Add(&femalebmpSel, RGB(0, 0, 0));
	m_treeAccount.SetImageList(&m_ImageList, TVSIL_NORMAL);
	RefreshTreeCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAccountDlg::RefreshTreeCtrl()
{
	auto insertAccountinfo = [&](AccountInfo& info, HTREEITEM hParent)
	{
		if (hParent == NULL)
		{
			return;
		}
		HTREEITEM hItem;
		if (info.strSex == "男")
		{
			hItem = m_treeAccount.InsertItem(info.strName, 2, 3, hParent);
		}
		else
		{
			hItem = m_treeAccount.InsertItem(info.strName, 4, 5, hParent);
		}
		
		//将账户id和所属部门id加入节点数据,高位设为USER_STATE，表示此节点为用户节点
		DWORD dwData = MAKELPARAM(info.nAccountId, USER_STATE);
		m_treeAccount.SetItemData(hItem, dwData);

	};
	auto insertDepartinfo = [&](DepartmentInfo& info, HTREEITEM hParent)
	{
		if (hParent == NULL)
		{
			return;
		}
		HTREEITEM hItem = m_treeAccount.InsertItem(info.strDepartName, 1, 0, hParent);

		//将每一个节点关联一个数据，数据低字节表示当前部门id，高字节表示父部门的id
		DWORD dwData = MAKELPARAM(info.nDepartID, info.nParentId);
		m_treeAccount.SetItemData(hItem, dwData);

		//获取属于此部门的账户并插入到此部门下
		if (CLLMysqlOperate::getSingletonPtr())
		{
			vector<AccountInfo> AccountVec = CLLMysqlOperate::getSingletonPtr()->GetAccountVecByDepartId(info.nDepartID);
			for (int i = 0; i < AccountVec.size();++i)
			{
				insertAccountinfo(AccountVec.at(i), hItem);
			}
		}

		//将所有属于此节点的子节点添加进来
		InsertChildItem(hItem, info.nDepartID);
	};

	m_treeAccount.DeleteAllItems();

	CString strDepartOri;
	strDepartOri.LoadStringW(IDS_DEPART_ORGANIZATION);
	HTREEITEM hRoot = m_treeAccount.InsertItem(strDepartOri);
	if (CLLMysqlOperate::getSingletonPtr())
	{
		//获取以及部门信息
		vector<DepartmentInfo> vecDepartInfo = CLLMysqlOperate::getSingletonPtr()->GetDepartmentVecByParentId(0);
		for (int i = 0; i < vecDepartInfo.size(); ++i)
		{
			insertDepartinfo(vecDepartInfo.at(i), hRoot);
		}
		m_treeAccount.Expand(hRoot, TVE_EXPAND);
	}

}


void CAccountDlg::InsertChildItem(HTREEITEM hParent, int nId)
{
	auto insertAccountinfo = [&](AccountInfo& info, HTREEITEM hParent)
	{
		if (hParent == NULL)
		{
			return;
		}

		HTREEITEM hItem;
		if (info.strSex == "男")
		{
			hItem = m_treeAccount.InsertItem(info.strName, 2, 3, hParent);
		}
		else
		{
			hItem = m_treeAccount.InsertItem(info.strName, 4, 5, hParent);
		}

		//将账户id加入节点数据,高位设为USER_STATE，表示此节点为用户节点
		DWORD dwData = MAKELPARAM(info.nAccountId, USER_STATE);
		m_treeAccount.SetItemData(hItem, dwData);

	};
	if (hParent == nullptr)
	{
		return;
	}

	if (CLLMysqlOperate::getSingletonPtr())
	{
		vector<DepartmentInfo> vecDepart = CLLMysqlOperate::getSingletonPtr()->GetDepartmentVecByParentId(nId);
		for (int i = 0; i < vecDepart.size(); ++i)
		{
			DepartmentInfo& info = vecDepart.at(i);
			HTREEITEM hItem = m_treeAccount.InsertItem(info.strDepartName, 1, 0, hParent);

			//将每一个节点关联一个数据，数据第字节表示当前部门id，高字节表示父部门的id
			DWORD dwData = MAKELPARAM(info.nDepartID, info.nParentId);
			m_treeAccount.SetItemData(hItem, dwData);

			//获取属于此部门的账户并插入到此部门下
			if (CLLMysqlOperate::getSingletonPtr())
			{
				vector<AccountInfo> AccountVec = CLLMysqlOperate::getSingletonPtr()->GetAccountVecByDepartId(info.nDepartID);
				for (int i = 0; i < AccountVec.size(); ++i)
				{
					insertAccountinfo(AccountVec.at(i), hItem);
				}
			}

			InsertChildItem(hItem, info.nDepartID);

		}
	}

}

void CAccountDlg::OnBnClickedButtonDeleteAccount()
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeAccount.GetSelectedItem();
	if (hItem == NULL)
	{
		return;
	}
	DWORD dwData = m_treeAccount.GetItemData(hItem);
	if (HIWORD(dwData) != USER_STATE)
	{
		CString strInfo = _T("选择节点必须为用户节点");
		//strInfo.LoadStringW(IDS_SELECT_NOT_DEPART);
		CString strTitle;
		strTitle.LoadStringW(IDS_WARNING);
		MessageBox(strInfo, strTitle, MB_ICONWARNING);
		return;
	}

	int nAccountId = LOWORD(dwData);
	if (CLLMysqlOperate::getSingletonPtr())
	{
		CLLMysqlOperate::getSingletonPtr()->DeleteAccountById(nAccountId);
	}

	m_treeAccount.DeleteItem(hItem);
	m_treeAccount.Invalidate();
	
}

void CAccountDlg::OnBnClickedButtonAddAccount()
{
	// TODO: Add your control notification handler code here

	auto insertAccountinfo = [&](AccountInfo& info, HTREEITEM hParent)
	{
		if (hParent == NULL)
		{
			return;
		}
		HTREEITEM hItem;
		if (info.strSex == "男")
		{
			hItem = m_treeAccount.InsertItem(info.strName, 3, 2, hParent);
		}
		else
		{
			hItem = m_treeAccount.InsertItem(info.strName, 5, 4, hParent);
		}

		//将账户id加入节点数据,高位设为USER_STATE，表示此节点为用户节点
		DWORD dwData = MAKELPARAM(info.nAccountId, USER_STATE);
		m_treeAccount.SetItemData(hItem, dwData);

	};

	HTREEITEM hItem = m_treeAccount.GetSelectedItem();
	if (hItem == NULL)
	{
		return;
	}
	DWORD dwData = m_treeAccount.GetItemData(hItem);
	if (HIWORD(dwData) == USER_STATE)
	{
		CString strInfo=_T("选择节点必须为部门节点");
		//strInfo.LoadStringW(IDS_SELECT_NOT_DEPART);
		CString strTitle;
		strTitle.LoadStringW(IDS_WARNING);
		MessageBox(strInfo, strTitle, MB_ICONWARNING);
		return;
	}

	CString strAccountID;
	m_editAccountId.GetWindowText(strAccountID);

	CString strAccountName;
	m_editAccountName.GetWindowText(strAccountName);

	CString strAccountPW;
	m_editAccountPw.GetWindowText(strAccountPW);

	if (strAccountID.IsEmpty() || strAccountName.IsEmpty() || strAccountPW.IsEmpty())
	{
		CString strInfo;
		strInfo.LoadStringW(IDS_INCOMPLETE_INPUT);
		CString strTitle;
		strTitle.LoadStringW(IDS_WARNING);
		MessageBox(strInfo, strTitle, MB_ICONWARNING);
		return;
	}



	AccountInfo info;
	info.nAccountId = _ttoi(strAccountID);
	info.strName =strAccountName;
	info.strPassword = strAccountPW;
	CString strSex;
	m_combAccountSex.GetWindowText(strSex);
	info.strSex =strSex;
	CString strDepartId;
	m_editCurDepartId.GetWindowTextW(strDepartId);
	info.nDepartmentId = _ttoi(strDepartId);
	CString strDepartName;
	m_editCurDepartName.GetWindowTextW(strDepartName);
	info.strDepartmentName = strDepartName;
	CString strHeaderShip;
	m_editAccountHs.GetWindowTextW(strHeaderShip);
	info.strHeaderShip = strHeaderShip;


	//更新数据库
	if (CLLMysqlOperate::getSingletonPtr())
	{
		int nErrorCode = CLLMysqlOperate::getSingletonPtr()->InsertAccountInfo(info);
		if (nErrorCode != ERROR_SUCCESS)
		{
			CString strInfo;
			strInfo.LoadStringW(IDS_IDINVALID_INPUT);
			CString strTitle;
			strTitle.LoadStringW(IDS_WARNING);
			MessageBox(strInfo, strTitle, MB_ICONWARNING);
			return;
		}
	}

	insertAccountinfo(info,hItem);
	m_treeAccount.Invalidate();
}


void CAccountDlg::OnTvnSelchangedTreeAccount(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	HTREEITEM hItem = m_treeAccount.GetSelectedItem();
	if (hItem == NULL)
	{
		return;
	}

	DWORD dwData = m_treeAccount.GetItemData(hItem);
	if (dwData != 0 )
	{
		int nID = LOWORD(dwData);
		int nParentID = HIWORD(dwData);
		if (nParentID == USER_STATE)
		{
			AccountInfo info = CLLMysqlOperate::getSingletonPtr()->GetAccountInfoById(nID);
			m_editCurAccount.SetWindowTextW(info.strName);

			CString strId;
			strId.Format(_T("%d"), nID);
			m_editCurAccountId.SetWindowText(strId);

			m_editCurDepartName.SetWindowText(info.strDepartmentName);

			CString strDepartId;
			strDepartId.Format(_T("%d"), info.nDepartmentId);
			m_editCurDepartId.SetWindowTextW(strDepartId);
		}
		else 
		{
			DepartmentInfo info = CLLMysqlOperate::getSingletonPtr()->GetDepartmentInfoById(nID);

			m_editCurAccount.SetWindowTextW(_T(""));
			m_editCurAccountId.SetWindowTextW(_T(""));

			m_editCurDepartName.SetWindowTextW(info.strDepartName);

			CString strDepartId;
			strDepartId.Format(_T("%d"), info.nDepartID);
			m_editCurDepartId.SetWindowTextW(strDepartId);
		}
	}


	m_editAccountHs.SetWindowTextW(_T(""));
	m_editAccountId.SetWindowTextW(_T(""));
	m_editAccountName.SetWindowTextW(_T(""));
	m_editAccountPw.SetWindowTextW(_T(""));
	m_combAccountSex.SetCurSel(-1);

	*pResult = 0;
}


HBRUSH CAccountDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CBase_Dlg::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
