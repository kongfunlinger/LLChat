// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LLClient.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "../commonclass/BufferMemDC.h"

#include "Utils.h"
// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CBase_Dlg(CLoginDlg::IDD, pParent)
{
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_LOG, m_btnLog);
	DDX_Control(pDX, IDC_BTN_EXIT, m_btnExit);
	DDX_Control(pDX, IDC_BTN_SETTING, m_btnSetting);
	DDX_Control(pDX, IDC_BTN_USER, m_btnUser);
	DDX_Control(pDX, IDC_BTN_PW, m_btnPassword);
	DDX_Control(pDX, IDC_BTN_LOGIN, m_btnLogin);
	DDX_Control(pDX, IDC_BTN_OK, m_btnOk);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_EDIT_USER, m_editUser);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPW);
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPort);
	DDX_Control(pDX, IDC_IPADDRESS_IP, m_ipAddressIp);
	DDX_Control(pDX, IDC_BTN_IP, m_btnIP);
	DDX_Control(pDX, IDC_BTN_PORT, m_btnPort);
	DDX_Control(pDX, IDC_CHECK_AUTO_LOGIN, m_checkAutoLogin);
	DDX_Control(pDX, IDC_CHECK_REMEMBER_PW, m_checkRemPw);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CBase_Dlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_EXIT, &CLoginDlg::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CLoginDlg::OnBnClickedBtnSetting)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BTN_OK, &CLoginDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CLoginDlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CLoginDlg::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_CHECK_AUTO_LOGIN, &CLoginDlg::OnBnClickedCheckAutoLogin)
	ON_BN_CLICKED(IDC_CHECK_REMEMBER_PW, &CLoginDlg::OnBnClickedCheckRememberPw)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLoginDlg message handlers


void CLoginDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages

	CRect rectClient;
	GetClientRect(rectClient);

	dc.FillSolidRect(rectClient, RGB(255, 255, 255));

	rectClient.bottom = rectClient.top + g_dpi.ScaleY(180);
	CBufferMemDC memDC(&dc, &rectClient, COLOR_TITLE_BK);
	Graphics graphics(memDC);
	SmoothingMode smOriginal = graphics.GetSmoothingMode();
	TextRenderingHint trOriginal = graphics.GetTextRenderingHint();
	graphics.SetSmoothingMode(SmoothingModeHighQuality);
	graphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);

	RectF rectF((REAL)rectClient.left, (REAL)rectClient.top, (REAL)rectClient.Width(), (REAL)g_dpi.ScaleY(140));
	SolidBrush brush(NULL_BRUSH);
	graphics.FillRectangle(&brush, rectF);

	CDialogEx::OnPaint();
}


void CLoginDlg::OnBnClickedBtnExit()
{
	// TODO: Add your control notification handler code here
	EndDialog(IDCANCEL);
}


void CLoginDlg::OnBnClickedBtnSetting()
{
	// TODO: Add your control notification handler code here
	SetShowState(SETTING_STATE);

}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_btnLog.SetImage(IDB_PNG_LOG);
	m_btnLog.SetFillBK(FALSE);

	m_btnSetting.SetImageName(IDB_PNG_SETTING);
	m_btnSetting.SetButtonType(BUTTON_TYPE_NORMAL);
	m_btnSetting.SetBkColor(COLOR_TITLE_BK);

	m_btnExit.SetImageName(IDB_PNG_EXIT);
	m_btnExit.SetButtonType(BUTTON_TYPE_NORMAL);
	m_btnExit.SetBkColor(COLOR_TITLE_BK);

	m_btnUser.SetImage(IDB_PNG_USER);
	m_btnUser.SetFillBK(FALSE);

	m_btnPassword.SetImage(IDB_PNG_PW);
	m_btnPassword.SetFillBK(FALSE);

	m_btnIP.SetImage(IDB_PNG_IP);
	m_btnIP.SetFillBK(FALSE);

	m_btnPort.SetImage(IDB_PNG_PORT);
	m_btnPort.SetFillBK(FALSE);

	m_btnLogin.SetButtonAutoSize(FALSE);
	m_btnLogin.SetButtonType(CGlassButton::BUTTON_TYPE_NORMAL);
	m_btnLogin.SetTextSize(12.0);

	m_btnOk.SetButtonAutoSize(FALSE);
	m_btnOk.SetButtonType(CGlassButton::BUTTON_TYPE_SQURE);
	m_btnOk.SetTextSize(8.0);
	m_btnCancel.SetButtonAutoSize(FALSE);
	m_btnCancel.SetButtonType(CGlassButton::BUTTON_TYPE_SQURE);
	m_btnCancel.SetTextSize(8.0);
	SetShowState(LOGIN_STATE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CLoginDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN,
		HTCAPTION,
		MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}



void CLoginDlg::OnBnClickedBtnOk()
{
	// TODO: Add your control notification handler code here
	SetShowState(LOGIN_STATE);
	ServerInfo info;
	m_ipAddressIp.GetWindowTextW(info.strIp);
	m_editPort.GetWindowTextW(info.strPort);
	CUtils::WriteServerInfo(info);
}


void CLoginDlg::OnBnClickedBtnLogin()
{
	// TODO: Add your control notification handler code here
	//如果登陆成功则执行以下操作
	UserInfo info;
	m_editUser.GetWindowTextW(info.strName);
	m_editPW.GetWindowTextW(info.strPW);
	CUtils::WriteUserInfo(info);
}


void CLoginDlg::OnBnClickedBtnCancel()
{
	// TODO: Add your control notification handler code here
	SetShowState(LOGIN_STATE);
}

void CLoginDlg::SetShowState(ShowState state)
{
	switch (state)
	{
	case LOGIN_STATE:
	{
						m_btnLogin.ShowWindow(SW_SHOW);
						m_btnOk.ShowWindow(SW_HIDE);
						m_btnCancel.ShowWindow(SW_HIDE);

						m_btnUser.ShowWindow(SW_SHOW);
						m_btnPassword.ShowWindow(SW_SHOW);
						m_btnIP.ShowWindow(SW_HIDE);
						m_btnPort.ShowWindow(SW_HIDE);
	

						m_editPort.ShowWindow(SW_HIDE);
						m_ipAddressIp.ShowWindow(SW_HIDE);

						m_editUser.ShowWindow(SW_SHOW);
						m_editPW.ShowWindow(SW_SHOW);

						m_checkAutoLogin.ShowWindow(SW_SHOW);
						m_checkRemPw.ShowWindow(SW_SHOW);
	}
		break;
	case SETTING_STATE:
	{
			
						  m_btnLogin.ShowWindow(SW_HIDE);
						  m_btnOk.ShowWindow(SW_SHOW);
						  m_btnCancel.ShowWindow(SW_SHOW);

						  m_btnUser.ShowWindow(SW_HIDE);
						  m_btnPassword.ShowWindow(SW_HIDE);
						  m_btnIP.ShowWindow(SW_SHOW);
						  m_btnPort.ShowWindow(SW_SHOW);
				
						  m_editPort.ShowWindow(SW_SHOW);
						  m_ipAddressIp.ShowWindow(SW_SHOW);

						  m_editUser.ShowWindow(SW_HIDE);
						  m_editPW.ShowWindow(SW_HIDE);

						  m_checkAutoLogin.ShowWindow(SW_HIDE);
						  m_checkRemPw.ShowWindow(SW_HIDE);


						  ServerInfo info = CUtils::ReadServerInfo();
						  m_ipAddressIp.SetWindowTextW(info.strIp);
						  m_editPort.SetWindowTextW(info.strPort);
	}
		break;
	default:
		break;
	}
}


void CLoginDlg::OnBnClickedCheckAutoLogin()
{
	// TODO: Add your control notification handler code here
	CString strPath = CUtils::GetAppPath() + _T("\\LLClient.ini");
	if (BST_CHECKED == m_checkAutoLogin.GetCheck())
	{
		
		WritePrivateProfileString(LLCLIENTINI::USERCONFIG, LLCLIENTINI::USERAUTOLOGIN, _T("1"), strPath);
	}
	else
	{
		WritePrivateProfileString(LLCLIENTINI::USERCONFIG, LLCLIENTINI::USERAUTOLOGIN, _T("0"), strPath);
	}
}


void CLoginDlg::OnBnClickedCheckRememberPw()
{
	// TODO: Add your control notification handler code here

	CString strPath = CUtils::GetAppPath() + _T("\\LLClient.ini");
	if (BST_CHECKED == m_checkAutoLogin.GetCheck())
	{

		WritePrivateProfileString(LLCLIENTINI::USERCONFIG, LLCLIENTINI::USERREMEMBERPW, _T("1"), strPath);
	}
	else
	{
		WritePrivateProfileString(LLCLIENTINI::USERCONFIG, LLCLIENTINI::USERREMEMBERPW, _T("0"), strPath);
	}
}


HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CBase_Dlg::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
