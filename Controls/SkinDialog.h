#pragma once
#include "NcControls.h"
#include <wincrypt.h>
#include <wintrust.h> 
#define SkinDialogOldProcTag _T("CDialog_oldProc")
#define MAX_TOOLBTN_NUM		(16)
#define MAX_BOTTOM_BTN_NUM	(8)
enum OWNERDRAW_TYPE
{
	OWNERDRAW_TYPE_NONE = 0,
	OWNERDRAW_TYPE_MAINFRAME,
	OWNERDRAW_TYPE_DLG
};
struct SKIN_RESOURCE
{
	Image *pCaptionAct;//激活状态标题栏
	Image *pCaptionNAct;//非激活状态标题栏
	Image *pTopLeftAct;//激活状态左上角
	Image *pTopLeftNAct;//非激活状态左上角
	Image *pTopRightAct;
	Image *pTopRightNAct;
	Image *pLeftAct;
	Image *pLeftNAct;
	Image *pRightAct;
	Image *pRightNAct;
	Image *pBottomAct;
	Image *pBottomNAct;
	Image *pBottomLeftAct;
	Image *pBottomLeftNAct;
	Image *pBottomRightAct;
	Image *pBottomRightNAct;
	Image *pMinBox;
	Image *pMaxBox;
	Image *pRestoreBox;
	Image *pCloseBox;
	HICON hIcon;
	Image *pCaptionLogo;
	BOOL  bIsUseLogo;
	BOOL  bIsNotDrawTitleText;
	CPtrArray *pAryControlPtr;
	INT nBtnRightSpace;
	INT nBtnTopSpace;
	INT nOwnerDrawType;
	SKIN_RESOURCE()
	{
		memset(this,0,sizeof(SKIN_RESOURCE));
		nBtnRightSpace = 10;
		nBtnTopSpace = 5;
	}
};

class CSkinDialog
{
private:
	enum BTN_TYPE
	{
		BTN_TYPE_CLOSE = 0,
		BTN_TYPE_MAX,
		BTN_TYPE_RESTORE,
		BTN_TYPE_MIN
	};
public:
	CSkinDialog(HWND hWnd);
	~CSkinDialog(void);
	static void Install(SKIN_RESOURCE skinRes,CFontInfo fontInfo,HWND hWnd = NULL);
	static void UnInstall();
	static CSkinDialog* AddSubClass( HWND &hWnd,TCHAR * oldProcTag,DWORD Proc);

	static CSkinDialog* AddWndHook(HWND hwnd);
	static CSkinDialog* GetWndHook(HWND hwnd);

	static LRESULT CALLBACK SkinDialogProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WindowHook (int code, WPARAM wParam, LPARAM lParam);
	static void DrawNC(HWND hWnd,Graphics *g);//画非客户区.
	static void DrawCaption(Graphics *g,CSkinDialog *pDlg,BOOL bIsActive);
	static void DrawCaptionOwner(Graphics *g,CSkinDialog *pDlg,BOOL bIsActive);
	static void DrawIconLogo(Graphics *g,CSkinDialog *pDlg);
	static void DrawBorder(Graphics *g,CSkinDialog *pDlg,BOOL bIsActive);
	static void DrawBorderOwner(Graphics *g,CSkinDialog *pDlg,BOOL bIsActive);
	static void DrawButton(Graphics *g,CSkinDialog *pDlg,BTN_TYPE nType,CNcControl_Base::BTN_STATE nState);
	static void DrawButton(CDC* pDC,CSkinDialog *pDlg,BTN_TYPE nType,CNcControl_Base::BTN_STATE nState);
	//static void DrawToolBtn(CDC *pDC,CSkinDialog *pDlg,INT nIndex,BTN_STATE nState);
	
	
	//message
	void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	void OnNcPaint();
	void OnNcLButtonDown(WNDPROC lpPrevWndFunc,HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	void OnNcMouseMove(WNDPROC lpPrevWndFunc,HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	LRESULT OnNcHitTest(WNDPROC lpPrevWndFunc,HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	BOOL OnNcActivate(BOOL bActive);
	void OnNcLButtonUp(UINT nHitTest, CPoint point);
	void OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	void OnShowWindow(BOOL bShow);
	void OnNcDestroy();
	LRESULT OnSetText(WNDPROC lpPrevWndFunc,HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	void OnNcLButtonDblClk(UINT nHitTest,CPoint point);
	void OnNcMouseLeave();
	void OnMove(INT x,INT y);
	void OnSize(UINT nType, int cx, int cy );
	BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	void GetBtnPos(CRect &crtBtn,BTN_TYPE nType);

	
protected:
	HWND m_hWnd;
	CString m_strCaption;//标题.
	CRect m_rtWnd;//整个窗体Rect.
	BOOL    m_bNCActive;//窗体活动.
	BOOL		m_sizable;
	BOOL		m_minable;
	BOOL		m_maxable;
	BOOL		m_sysmenu;
	CRect		m_crtNC;
	BOOL		m_bMinIsHover;
	BOOL		m_bMaxIsHover;
	BOOL		m_bCloseIsHover;

	static CMap<HWND,HWND,CSkinDialog*,CSkinDialog*> m_map;
	static HHOOK m_hHook;
	static SKIN_RESOURCE m_skinRes;
	SKIN_RESOURCE m_skinResCustom;
	static CFontInfo m_fontInfo;
	CFontInfo m_fontInfoCustom;
	BOOL m_bIsPressedMin;
	BOOL m_bIsPressedMax;
	BOOL m_bIsPressedClose;
	BOOL m_bIsTrackingMouse;

	static UINT m_nCaptionHOwnerFrame;
	static UINT m_nCaptionHOwnerDlg;
	static UINT m_nLeftWOwnerFrame;
	static UINT m_nLeftWOwnerDlg;
	static UINT m_nRightWOwnerFrame;
	static UINT m_nRightWOwnerDlg;
	static UINT m_nBottomHOwnerFrame;
	static UINT m_nBottomHOwnerDlg;

};
