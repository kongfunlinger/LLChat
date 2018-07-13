
// LLServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LLServer.h"
#include "LLServerDlg.h"
#include "afxdialogex.h"
#include "../commonclass/BufferMemDC.h"
#include "MysqlConn.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLLServerDlg dialog



CLLServerDlg::CLLServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLLServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLLServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_LOG, m_btnLog);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_staTitle);

}

BEGIN_MESSAGE_MAP(CLLServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(MSG_CHILD2FATHER_DEPARTMENT,&CLLServerDlg::OnDepartmentWndSwitch)
	ON_MESSAGE(MSG_CHILD2FATHER_ACCOUNT,&CLLServerDlg::OnAccountWndSwitch)
	ON_BN_CLICKED(IDC_BTN_LOG, &CLLServerDlg::OnBnClickedBtnLog)
END_MESSAGE_MAP()


// CLLServerDlg message handlers

BOOL CLLServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	//获取本地IP
	//char chName[MAX_PATH] = { 0 };
	//gethostname(chName, MAX_PATH);
	//hostent *phost = gethostbyname(chName);
	//char *chIP = inet_ntoa(*(in_addr *)phost->h_addr_list[0]);

	m_btnLog.SetImage(IDB_PNG_LOG);
	m_btnLog.SetFillBK(FALSE);

	m_staTitle.SetFontSize(28);
	m_staTitle.SetFontStyle(FontStyleBold);
	m_staTitle.SetFontType(_T("宋体"));
	m_staTitle.SetFontColor(RGB(255,255,255));

	
	CRect rect;
	GetClientRect(rect);
	rect.top += g_dpi.ScaleY(140);
	//创建子窗口
	
	m_departmentDlg.Create(IDD_DEPARTMENT_DIALOG);
	m_departmentDlg.MoveWindow(rect);
	m_departmentDlg.ShowWindow(SW_HIDE);

	m_optionDlg.Create(IDD_OPTION_DIALOG);
	m_optionDlg.MoveWindow(rect);
	m_optionDlg.ShowWindow(SW_SHOW);

	m_accountDlg.Create(IDD_ACCOUNT_DIALOG);
	m_accountDlg.MoveWindow(rect);
	m_accountDlg.ShowWindow(SW_HIDE);

	/*CMysqlConn Con;
	Con.OpenCon("127.0.0.1", "root", "wangluling!012");
	Con.SetSchema("liaoliaodb");
	vector<string> vecStr;
	Con.GetTables(vecStr);*/


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLLServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLLServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect rectClient;
		GetClientRect(rectClient);

		dc.FillSolidRect(rectClient, RGB(255,255,255));

		rectClient.bottom = rectClient.top + g_dpi.ScaleY(140);
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
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLLServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//父窗口与子窗口的切换显示
LRESULT CLLServerDlg::OnDepartmentWndSwitch(WPARAM wParam, LPARAM lParam)
{
	
	m_accountDlg.ShowWindow(SW_HIDE);
	m_departmentDlg.ShowWindow(SW_SHOW);
	m_optionDlg.ShowWindow(SW_HIDE);
	return 0;
}

LRESULT CLLServerDlg::OnAccountWndSwitch(WPARAM wParam, LPARAM lParam)
{
	m_accountDlg.ShowWindow(SW_SHOW);
	m_departmentDlg.ShowWindow(SW_HIDE);
	m_optionDlg.ShowWindow(SW_HIDE);
	return 0;
}


void CLLServerDlg::OnBnClickedBtnLog()
{
	// TODO: Add your control notification handler code here
	m_accountDlg.ShowWindow(SW_HIDE);
	m_departmentDlg.ShowWindow(SW_HIDE);
	m_optionDlg.ShowWindow(SW_SHOW);
	Invalidate();
}

