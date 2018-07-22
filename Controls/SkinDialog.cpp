#include "stdafx.h"
#include "SkinDialog.h"
#include "../Controls/Base_Dlg.h"

CMap<HWND,HWND,CSkinDialog*,CSkinDialog*> CSkinDialog::m_map;
HHOOK CSkinDialog::m_hHook = NULL;
SKIN_RESOURCE CSkinDialog::m_skinRes;
CFontInfo CSkinDialog::m_fontInfo;
UINT CSkinDialog::m_nCaptionHOwnerFrame = g_dpi.ScaleY(80);
UINT CSkinDialog::m_nCaptionHOwnerDlg = g_dpi.ScaleY(24);
UINT CSkinDialog::m_nLeftWOwnerFrame = 4;
UINT CSkinDialog::m_nLeftWOwnerDlg = 1;
UINT CSkinDialog::m_nRightWOwnerFrame = 1;
UINT CSkinDialog::m_nRightWOwnerDlg = 1;
UINT CSkinDialog::m_nBottomHOwnerFrame = 4;
UINT CSkinDialog::m_nBottomHOwnerDlg = 1;
CSkinDialog::CSkinDialog(HWND hWnd)
:m_hWnd(hWnd)
{
	m_crtNC = CRect(0,0,0,0);
	m_bIsPressedMin = FALSE;
	m_bIsPressedMax = FALSE;
	m_bIsPressedClose = FALSE;
	m_bIsTrackingMouse = FALSE;
	m_bMinIsHover = FALSE;
	m_bMaxIsHover = FALSE;
	m_bCloseIsHover = FALSE;
}

CSkinDialog::~CSkinDialog(void)
{
	WNDPROC oldWndProc = (WNDPROC)::GetProp(m_hWnd, SkinDialogOldProcTag);
	if (oldWndProc != NULL)
	{
		SetWindowLong(m_hWnd, GWLP_WNDPROC, (DWORD)(ULONG)oldWndProc);
		RemoveProp(m_hWnd, SkinDialogOldProcTag);
	}
	m_map.RemoveKey(m_hWnd);

}

void CSkinDialog::Install( SKIN_RESOURCE skinRes,CFontInfo fontInfo,HWND hWnd)
{
	if(hWnd)
	{
		if (GetWindowLong(hWnd,GWL_STYLE)&WS_CAPTION)
		{
			CSkinDialog *pDlg = AddSubClass(hWnd,SkinDialogOldProcTag,(DWORD)(ULONG)SkinDialogProc);
			if(pDlg)
			{
				pDlg->m_skinResCustom = skinRes;
				pDlg->m_fontInfoCustom = fontInfo;
			}
		}

	}
	else
	{
		if (m_hHook == NULL )
			m_hHook = SetWindowsHookEx(WH_CALLWNDPROC, WindowHook,AfxGetApp()->m_hInstance,GetCurrentThreadId()); 
		m_skinRes = skinRes;
		m_fontInfo = fontInfo;
	}
}
void CSkinDialog::UnInstall()
{
	POSITION pos = m_map.GetStartPosition();
	while (pos != NULL)
	{
		HWND hwnd;
		CSkinDialog* pHook;
		m_map.GetNextAssoc(pos, hwnd, pHook);
		delete pHook;
		pHook = NULL;
	}
	m_map.RemoveAll();
	if (m_hHook != NULL) UnhookWindowsHookEx(m_hHook);
}

CSkinDialog* CSkinDialog::AddSubClass( HWND &hWnd,TCHAR * oldProcTag,DWORD Proc )
{
	CSkinDialog *pRet = NULL;
	if (GetProp(hWnd, oldProcTag) != NULL ) return pRet;//已被子类化
	pRet = AddWndHook(hWnd);
	WNDPROC oldWndProc = (WNDPROC)(long)::GetWindowLong(hWnd, GWLP_WNDPROC);// 取原来窗口过程
	if (oldWndProc == NULL) return pRet;
	ASSERT((DWORD)(ULONG)oldWndProc != Proc);
	if (!SetProp(hWnd, oldProcTag, oldWndProc) ) return pRet;// 保存到窗口属性
	if (!SetWindowLong(hWnd, GWLP_WNDPROC, Proc))// 子类化
		RemoveProp(hWnd, oldProcTag);
	return pRet;

}

CSkinDialog* CSkinDialog::AddWndHook( HWND hwnd )
{
	CSkinDialog* pWnd = NULL;
	if (m_map.Lookup(hwnd, pWnd)) return pWnd;//如果已有hwnd，返回得到的值。

	pWnd = new CSkinDialog(hwnd);
	if (pWnd != NULL)
	{
		DWORD style = GetWindowLong( hwnd, GWL_STYLE );
		pWnd->m_sizable = style & WS_SIZEBOX;
		pWnd->m_minable = style & WS_MINIMIZEBOX;
		pWnd->m_maxable = style & WS_MAXIMIZEBOX;
		pWnd->m_sysmenu = style & WS_SYSMENU;
		style &= ~(WS_MINIMIZEBOX);
		style &= ~WS_MAXIMIZEBOX;
		style &= ~WS_SYSMENU;
		SetWindowLong( hwnd, GWL_STYLE, style );

		pWnd->m_skinResCustom = m_skinRes;
		pWnd->m_fontInfoCustom = m_fontInfo;
		m_map.SetAt(hwnd, pWnd);
	}
	return pWnd;
}

CSkinDialog* CSkinDialog::GetWndHook( HWND hwnd )
{
	CSkinDialog* pWnd = NULL;
	if (m_map.Lookup(hwnd, pWnd))
	{
		return pWnd;
	}
	return NULL;
}

LRESULT CALLBACK CSkinDialog::SkinDialogProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	WNDPROC oldWndProc = (WNDPROC)GetProp(hWnd, SkinDialogOldProcTag);
	CSkinDialog* pWnd = GetWndHook(hWnd);
	UINT uMsg1=uMsg;
	if (pWnd == NULL) goto EndSkinDialogProc;
	switch (uMsg)
	{
	case WM_SETTEXT:
		return pWnd->OnSetText(oldWndProc,hWnd,uMsg1,wParam,lParam);
	case WM_NCPAINT:
		pWnd->OnNcPaint();
		return HTNOWHERE;
	case WM_NCCALCSIZE:
		pWnd->OnNcCalcSize((BOOL)wParam, (NCCALCSIZE_PARAMS*)lParam);
		break;
	case WM_NCLBUTTONDOWN:
		pWnd->OnNcLButtonDown(oldWndProc,hWnd,uMsg1,wParam,lParam);
		return 1;
	case WM_NCLBUTTONDBLCLK:
		pWnd->OnNcLButtonDblClk(UINT(wParam),CPoint(SHORT(LOWORD(lParam)),SHORT(HIWORD(lParam))));
		return 1;
	case WM_NCMOUSEMOVE:
		pWnd->OnNcMouseMove(oldWndProc,hWnd,uMsg1,wParam,lParam);
		return 1;
	case WM_NCHITTEST:
		return pWnd->OnNcHitTest(oldWndProc,hWnd,uMsg1,wParam,lParam);
	case WM_NCACTIVATE:
		pWnd->OnNcActivate((BOOL)LOWORD(wParam));
		return HTCAPTION;
	case WM_NCLBUTTONUP:
		pWnd->OnNcLButtonUp((UINT)wParam,CPoint(SHORT(LOWORD(lParam)),SHORT(HIWORD(lParam))));
		return 1;
	case WM_CREATE:
		pWnd->OnCreate((CREATESTRUCT *)lParam);
		break;
	case WM_INITMENUPOPUP:
		pWnd->OnInitMenuPopup((CMenu*)wParam,LOWORD(lParam),HIWORD(lParam));
		return 1;
	case WM_SHOWWINDOW:
		pWnd->OnShowWindow(wParam != NULL);
		break;
	case WM_DESTROY:
		pWnd->OnNcDestroy();
		break;
	case WM_MOVE:
		pWnd->OnMove(LOWORD(lParam),HIWORD(lParam));
		break;
	case WM_SIZE:
		pWnd->OnSize(wParam,LOWORD(lParam),HIWORD(lParam));
		break;
	case WM_NCMOUSELEAVE:
		pWnd->OnNcMouseLeave();
		break;
	case WM_SETCURSOR:
		if(pWnd->OnSetCursor((CWnd*)wParam,LOWORD(lParam),HIWORD(lParam)))
			return TRUE;
		break;
	}
EndSkinDialogProc:
	if(IsWindow(hWnd))
		return CallWindowProc(oldWndProc, hWnd, uMsg1, wParam, lParam);
	else
		return HTNOWHERE;

}

LRESULT CALLBACK CSkinDialog::WindowHook( int code, WPARAM wParam, LPARAM lParam )
{
	CWPSTRUCT* pStruct = (CWPSTRUCT*)lParam;
	if (code == HC_ACTION)
	{
		HWND hWnd = pStruct->hwnd;
		if (pStruct->message != WM_CREATE && pStruct->message != 0x01E2) goto EndProc;

		
		CString strClassName = L"";
		GetClassName (hWnd, strClassName.GetBuffer(MAX_PATH), MAX_PATH);
		strClassName.ReleaseBuffer();
#ifdef _DEBUG
		LPCSTR lpszClassName = CWnd::FromHandle(hWnd)->GetRuntimeClass()->m_lpszClassName; 
		TRACE(lpszClassName);TRACE("---------\r\n");
#endif

		//是CDialog类，无标题栏
		//if (_tcscmp(lpszClassName, _T("CDialog")) == 0 && GetWindowLong(hWnd,GWL_STYLE)&WS_CAPTION)

		if (strClassName.CompareNoCase(_T("#32770")) == 0 && GetWindowLong(hWnd,GWL_STYLE)&WS_CAPTION)
			AddSubClass(hWnd,SkinDialogOldProcTag,(DWORD)(ULONG)SkinDialogProc);
	}

EndProc:
	return CallNextHookEx (m_hHook, code, wParam, lParam);

}

void CSkinDialog::DrawNC(HWND hWnd,Graphics *g )
{
	if (!hWnd) return;
	CSkinDialog *pSkinDlg = GetWndHook(hWnd);
	if(!pSkinDlg) return;

	//CRect rtTitle;//
	//整个Window的相对于屏幕的矩形
	GetWindowRect(hWnd,pSkinDlg->m_rtWnd); 
	if(pSkinDlg->m_skinResCustom.nOwnerDrawType == OWNERDRAW_TYPE_NONE)
	{
		DrawCaption(g,pSkinDlg,pSkinDlg->m_bNCActive);
		DrawBorder(g,pSkinDlg,pSkinDlg->m_bNCActive);
	}
	else
	{
		DrawCaptionOwner(g,pSkinDlg,pSkinDlg->m_bNCActive);
		DrawBorderOwner(g,pSkinDlg,pSkinDlg->m_bNCActive);
	}
	DrawIconLogo(g,pSkinDlg);
	if(pSkinDlg->m_minable)
	{
		DrawButton(g,pSkinDlg,BTN_TYPE_MIN,CNcControl_Base::BTN_STATE_NORMAL);
	}
	if(pSkinDlg->m_maxable)
	{
		if(IsZoomed(hWnd))
		{
			DrawButton(g,pSkinDlg,BTN_TYPE_RESTORE,CNcControl_Base::BTN_STATE_NORMAL);
		}
		else
		{
			DrawButton(g,pSkinDlg,BTN_TYPE_MAX,CNcControl_Base::BTN_STATE_NORMAL);
		}
	
	}
	if(pSkinDlg->m_sysmenu || pSkinDlg->m_minable || pSkinDlg->m_maxable)
	{
		DrawButton(g,pSkinDlg,BTN_TYPE_CLOSE,CNcControl_Base::BTN_STATE_NORMAL);
	}

}

void CSkinDialog::OnNcCalcSize( BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp )
{
	if(bCalcValidRects && m_crtNC == CRect(0,0,0,0))
	{
		CRect crtWnd,crtClient;
		GetWindowRect(m_hWnd,crtWnd);
		GetClientRect(m_hWnd,crtClient);
		CWnd *pWnd = CWnd::FromHandle(m_hWnd);
		if(!pWnd) return;
		pWnd->ClientToScreen(crtClient);
		m_crtNC.top = crtClient.top - crtWnd.top;
		m_crtNC.bottom = crtWnd.bottom - crtClient.bottom;
		m_crtNC.left = crtClient.left - crtWnd.left;
		m_crtNC.right = crtWnd.right - crtClient.right;
	}
	if(m_crtNC != CRect(0,0,0,0))
	{
		LONG lCaptionH = 0;
		LONG lLeftW = 0;
		LONG lRightW = 0;
		LONG lBottomH = 0;
		if(m_skinResCustom.nOwnerDrawType == OWNERDRAW_TYPE_MAINFRAME)
		{
			lCaptionH = m_nCaptionHOwnerFrame;
			lLeftW = m_nLeftWOwnerFrame;
			lRightW = m_nRightWOwnerFrame;
			lBottomH = m_nBottomHOwnerFrame;
		}
		else if(m_skinResCustom.nOwnerDrawType == OWNERDRAW_TYPE_DLG)
		{
			lCaptionH = m_nCaptionHOwnerDlg;
			lLeftW = m_nLeftWOwnerDlg;
			lRightW = m_nRightWOwnerDlg;
			lBottomH = m_nBottomHOwnerDlg;

		}
		else
		{
			lCaptionH = g_dpi.ScaleY(m_skinResCustom.pCaptionAct->GetHeight());
			lLeftW = /*g_dpi.ScaleX*/(m_skinResCustom.pLeftAct->GetWidth());
			lRightW = /*g_dpi.ScaleX*/(m_skinResCustom.pRightAct->GetWidth());
			lBottomH = /*g_dpi.ScaleY*/(m_skinResCustom.pBottomAct->GetHeight());

		}
		lpncsp->rgrc[0].top += lCaptionH - m_crtNC.top;
		lpncsp->rgrc[0].bottom -= lBottomH - m_crtNC.bottom;
		lpncsp->rgrc[0].left += lLeftW - m_crtNC.left;
		lpncsp->rgrc[0].right -= lRightW - m_crtNC.right;
	}
}

void CSkinDialog::OnNcPaint()
{
	CWindowDC dc(CWnd::FromHandle(m_hWnd));
	CRect rtWnd(0,0,m_rtWnd.Width(),m_rtWnd.Height());
	CBufferMemDC memDC(&dc, &rtWnd, RGB(255,255,255), FALSE);	
	Graphics graphics(memDC);
	SmoothingMode smOriginal = graphics.GetSmoothingMode();
	TextRenderingHint trOriginal = graphics.GetTextRenderingHint();
	graphics.SetSmoothingMode(SmoothingModeHighQuality);
	graphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);

	DrawNC(m_hWnd,&graphics);
	if(m_skinResCustom.pAryControlPtr)
	{
		for(INT i=0;i<m_skinResCustom.pAryControlPtr->GetCount();i++)
		{
			CNcControl_Base *pControl = (CNcControl_Base*)(m_skinResCustom.pAryControlPtr->GetAt(i));
			if(!pControl) continue;
			pControl->OnNcPaint(&graphics);
		}
	}
	graphics.SetSmoothingMode(smOriginal);
	graphics.SetTextRenderingHint(trOriginal);
}

void CSkinDialog::OnNcLButtonDown( WNDPROC lpPrevWndFunc,HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	CPoint point(SHORT(LOWORD(lParam)),SHORT(HIWORD(lParam)));
	//检测最小，最大和关闭按钮是否按下,然后更换.
	CWindowDC dc(CWnd::FromHandle(m_hWnd));
	point.Offset(m_rtWnd.left * (-1),m_rtWnd.top * (-1));
	CRect crtClose,crtMax,crtMin;
	GetBtnPos(crtClose,BTN_TYPE_CLOSE);
	GetBtnPos(crtMax,BTN_TYPE_MAX);
	GetBtnPos(crtMin,BTN_TYPE_MIN);

	if(crtClose.PtInRect(point))
	{
		m_bIsPressedClose = TRUE;
		DrawButton(&dc,this,BTN_TYPE_CLOSE,CNcControl_Base::BTN_STATE_PRESS);
	}
	else if(crtMax.PtInRect(point))
	{
		m_bIsPressedMax = TRUE;
		if(IsZoomed(hWnd))
			DrawButton(&dc,this,BTN_TYPE_RESTORE,CNcControl_Base::BTN_STATE_PRESS);
		else
			DrawButton(&dc,this,BTN_TYPE_MAX,CNcControl_Base::BTN_STATE_PRESS);
	}
	else if(crtMin.PtInRect(point))
	{
		m_bIsPressedMin = TRUE;
		DrawButton(&dc,this,BTN_TYPE_MIN,CNcControl_Base::BTN_STATE_PRESS);
	}
	else
	{
		BOOL bIsInBtn = FALSE;
		if(m_skinResCustom.pAryControlPtr)
		{
			for(INT i=0;i<m_skinResCustom.pAryControlPtr->GetCount();i++)
			{
				CNcControl_Base *pControl = (CNcControl_Base*)(m_skinResCustom.pAryControlPtr->GetAt(i));
				if(!pControl) continue;
				if(pControl->OnNcLButtonDown(wParam,lParam))
				{
					bIsInBtn = TRUE;
				}
			}
		}

		if(bIsInBtn == FALSE)
			CallWindowProc(lpPrevWndFunc,hWnd,Msg,wParam,lParam);
	}
}

void CSkinDialog::OnNcMouseMove(WNDPROC /*lpPrevWndFunc*/,HWND hWnd,UINT /*Msg*/,WPARAM wParam,LPARAM lParam)
{
	if (!m_bIsTrackingMouse)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_NONCLIENT | TME_LEAVE;
		tme.hwndTrack = m_hWnd;

		if (::_TrackMouseEvent(&tme))
		{
			m_bIsTrackingMouse = TRUE;
		}
	}
	if(m_bIsPressedMin || m_bIsPressedMax || m_bIsPressedClose) return;
	CPoint point(SHORT(LOWORD(lParam)),SHORT(HIWORD(lParam)));
	//检测最小，最大和关闭按钮是否有鼠标悬停,然后更换.
	CWindowDC dc(CWnd::FromHandle(m_hWnd));
	CRect crtPosClose,crtPosMax,crtPosMin;
	GetBtnPos(crtPosClose,BTN_TYPE_CLOSE);
	GetBtnPos(crtPosMax,BTN_TYPE_MAX);
	GetBtnPos(crtPosMin,BTN_TYPE_MIN);
	point.Offset(m_rtWnd.left * (-1),m_rtWnd.top * (-1));
	m_bMinIsHover = FALSE;
	m_bMaxIsHover = FALSE;
	m_bCloseIsHover = FALSE;
	if(crtPosClose.PtInRect(point))
	{
		DrawButton(&dc,this,BTN_TYPE_CLOSE,CNcControl_Base::BTN_STATE_HOVER);
		DrawButton(&dc,this,BTN_TYPE_MIN,CNcControl_Base::BTN_STATE_NORMAL);
		if(IsZoomed(hWnd))
			DrawButton(&dc,this,BTN_TYPE_RESTORE,CNcControl_Base::BTN_STATE_NORMAL);
		else
			DrawButton(&dc,this,BTN_TYPE_MAX,CNcControl_Base::BTN_STATE_NORMAL);
		m_bCloseIsHover = TRUE;
	}
	else if(crtPosMax.PtInRect(point))
	{
		DrawButton(&dc,this,BTN_TYPE_CLOSE,CNcControl_Base::BTN_STATE_NORMAL);
		DrawButton(&dc,this,BTN_TYPE_MIN,CNcControl_Base::BTN_STATE_NORMAL);
		if(IsZoomed(hWnd))
			DrawButton(&dc,this,BTN_TYPE_RESTORE,CNcControl_Base::BTN_STATE_HOVER);
		else
			DrawButton(&dc,this,BTN_TYPE_MAX,CNcControl_Base::BTN_STATE_HOVER);
		m_bMaxIsHover = TRUE;
	}
	else if(crtPosMin.PtInRect(point))
	{
		DrawButton(&dc,this,BTN_TYPE_CLOSE,CNcControl_Base::BTN_STATE_NORMAL);
		DrawButton(&dc,this,BTN_TYPE_MIN,CNcControl_Base::BTN_STATE_HOVER);
		if(IsZoomed(hWnd))
			DrawButton(&dc,this,BTN_TYPE_RESTORE,CNcControl_Base::BTN_STATE_NORMAL);
		else
			DrawButton(&dc,this,BTN_TYPE_MAX,CNcControl_Base::BTN_STATE_NORMAL);
		m_bMinIsHover = TRUE;
	}
	else
	{
		DrawButton(&dc,this,BTN_TYPE_CLOSE,CNcControl_Base::BTN_STATE_NORMAL);
		DrawButton(&dc,this,BTN_TYPE_MIN,CNcControl_Base::BTN_STATE_NORMAL);
		if(IsZoomed(hWnd))
			DrawButton(&dc,this,BTN_TYPE_RESTORE,CNcControl_Base::BTN_STATE_NORMAL);
		else
			DrawButton(&dc,this,BTN_TYPE_MAX,CNcControl_Base::BTN_STATE_NORMAL);
	}
	if(m_skinResCustom.pAryControlPtr)
	{
		for(INT i=0;i<m_skinResCustom.pAryControlPtr->GetCount();i++)
		{
			CNcControl_Base *pControl = (CNcControl_Base*)(m_skinResCustom.pAryControlPtr->GetAt(i));
			if(!pControl) continue;
			pControl->OnNcMouseMove(wParam,lParam);
		}
	}

}

LRESULT CSkinDialog::OnNcHitTest( WNDPROC lpPrevWndFunc,HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	LRESULT lRet = 0;
	CPoint point(SHORT(LOWORD(lParam)),SHORT(HIWORD(lParam)));
	CRect tst;
	CRect tsb;
	CRect tsbr;
	CRect tstr;
	if(m_skinResCustom.nOwnerDrawType == OWNERDRAW_TYPE_MAINFRAME)
	{
		tst = CRect(m_nLeftWOwnerFrame,m_nBottomHOwnerFrame,
			m_rtWnd.Width() - m_nRightWOwnerFrame,m_nCaptionHOwnerFrame);
		tsb = CRect(m_nBottomHOwnerFrame,m_rtWnd.Height() - m_nBottomHOwnerFrame,
			m_rtWnd.Width() - m_nBottomHOwnerFrame,m_rtWnd.Height());
		tsbr = CRect(m_rtWnd.Width() - m_nBottomHOwnerFrame,m_rtWnd.Height() - m_nBottomHOwnerFrame,
			m_rtWnd.Width(),m_rtWnd.Height());
		tstr = CRect(m_rtWnd.Width() - m_nRightWOwnerFrame,0,
			m_rtWnd.Width(),m_nRightWOwnerFrame);
	}
	else if(m_skinResCustom.nOwnerDrawType == OWNERDRAW_TYPE_DLG)
	{
		tst = CRect(m_nLeftWOwnerDlg,m_nLeftWOwnerDlg,
			m_rtWnd.Width() - m_nRightWOwnerDlg,m_nCaptionHOwnerDlg);
		tsb = CRect(m_nLeftWOwnerDlg,m_rtWnd.Height() - m_nBottomHOwnerDlg,
			m_rtWnd.Width() - m_nRightWOwnerDlg,m_rtWnd.Height());
		tsbr = CRect(m_rtWnd.Width() - m_nRightWOwnerDlg,m_rtWnd.Height() - m_nBottomHOwnerDlg,
			m_rtWnd.Width(),m_rtWnd.Height());
		tstr = CRect(m_rtWnd.Width() - m_nRightWOwnerDlg,0,
			m_rtWnd.Width(),m_nRightWOwnerDlg);

	}
	else
	{
		tst = CRect(g_dpi.ScaleX(m_skinResCustom.pTopLeftAct->GetWidth()),
			g_dpi.ScaleX(m_skinResCustom.pLeftAct->GetWidth()),
			m_rtWnd.Width() - g_dpi.ScaleX(m_skinResCustom.pTopRightAct->GetWidth()),
			g_dpi.ScaleY(m_skinResCustom.pCaptionAct->GetHeight()));
		tsb = CRect(g_dpi.ScaleX(m_skinResCustom.pBottomLeftAct->GetWidth()),
			m_rtWnd.Height() - g_dpi.ScaleY(m_skinResCustom.pBottomAct->GetHeight()),
			m_rtWnd.Width() - g_dpi.ScaleX(m_skinResCustom.pBottomRightAct->GetWidth()),
			m_rtWnd.Height() - g_dpi.ScaleY(4));
		tsbr = CRect(m_rtWnd.Width() - g_dpi.ScaleX(m_skinResCustom.pBottomRightAct->GetWidth()),
					m_rtWnd.Height() - g_dpi.ScaleY(m_skinResCustom.pBottomRightAct->GetWidth()),//右下角以宽度为基准的正方形
					m_rtWnd.Width(), m_rtWnd.Height());
		tstr = CRect(m_rtWnd.Width() - g_dpi.ScaleX(m_skinResCustom.pTopRightAct->GetWidth()),
			0,m_rtWnd.Width(),g_dpi.ScaleX(m_skinResCustom.pTopRightAct->GetWidth()));

	}
	tst.OffsetRect(m_rtWnd.TopLeft());//原图标屏幕位置
	tsb.OffsetRect(m_rtWnd.TopLeft());
	tsbr.OffsetRect(m_rtWnd.TopLeft());
	CRect crtClose,crtMax,crtMin;
	GetBtnPos(crtClose,BTN_TYPE_CLOSE);
	GetBtnPos(crtMax,BTN_TYPE_MAX);
	GetBtnPos(crtMin,BTN_TYPE_MIN);
	crtClose.OffsetRect(m_rtWnd.TopLeft());
	crtMax.OffsetRect(m_rtWnd.TopLeft());
	crtMin.OffsetRect(m_rtWnd.TopLeft());
	if(crtClose.PtInRect(point)||
		crtMax.PtInRect(point)||
		crtMin.PtInRect(point))
		lRet = HTSYSMENU;//使此区域能够响应OnNcLButtonUp
	else if(tst.PtInRect(point))//最大最小关闭按钮位置.
		lRet = HTCAPTION;
	else if(tsb.PtInRect(point))
		lRet = HTBOTTOM/*HTBORDER*/;
	else if(tsbr.PtInRect(point) && m_sizable)
		lRet = HTBOTTOMRIGHT;
	else if(tstr.PtInRect(point) && m_sizable)
		lRet = HTTOPRIGHT;
	else
		lRet = CallWindowProc(lpPrevWndFunc,hWnd,Msg,wParam,lParam);

	if (lRet == HTZOOM || lRet == HTMINBUTTON || lRet == HTCLOSE)//屏蔽最大最小关闭消息.
		lRet = HTCAPTION;

	return lRet; 

}

BOOL CSkinDialog::OnNcActivate( BOOL bActive )
{
	m_bNCActive=bActive;
	OnNcPaint();
	return TRUE;
}

void CSkinDialog::OnNcLButtonUp( UINT nHitTest, CPoint point )
{
	CRect crtClose,crtMax,crtMin;
	GetBtnPos(crtClose,BTN_TYPE_CLOSE);
	GetBtnPos(crtMax,BTN_TYPE_MAX);
	GetBtnPos(crtMin,BTN_TYPE_MIN);
	point.Offset(m_rtWnd.left * (-1),m_rtWnd.top * (-1));
	if (crtClose.PtInRect(point) && m_bIsPressedClose && (m_sysmenu || m_minable || m_maxable))
	{
		SendMessage(m_hWnd,WM_CLOSE,0,0);
		if(!::IsWindow(m_hWnd)) return;
	}
	else if (crtMin.PtInRect(point) && m_bIsPressedMin && m_minable)
		SendMessage(m_hWnd,WM_SYSCOMMAND, SC_MINIMIZE, MAKELPARAM(point.x, point.y) );
	else if (crtMax.PtInRect(point) && m_bIsPressedMax && m_maxable)
	{
		DWORD style = GetWindowLong( m_hWnd, GWL_STYLE );
		style |= WS_MAXIMIZEBOX | WS_SYSMENU;
		SetWindowLong(m_hWnd,GWL_STYLE,style);
		if (IsZoomed(m_hWnd))
			SendMessage(m_hWnd,WM_SYSCOMMAND, SC_RESTORE, MAKELPARAM(point.x, point.y));
		else
			SendMessage(m_hWnd,WM_SYSCOMMAND, SC_MAXIMIZE, MAKELPARAM(point.x, point.y) );
		style = GetWindowLong( m_hWnd, GWL_STYLE );
		style &= ~WS_MAXIMIZEBOX;
		style &= ~WS_SYSMENU;
		SetWindowLong(m_hWnd,GWL_STYLE,style);
	}

	m_bIsPressedMin = FALSE;
	m_bIsPressedMax = FALSE;
	m_bIsPressedClose = FALSE;
	CWindowDC dc(CWnd::FromHandle(m_hWnd));
	DrawButton(&dc,this,BTN_TYPE_MIN,CNcControl_Base::BTN_STATE_NORMAL);
	if(IsZoomed(m_hWnd))
		DrawButton(&dc,this,BTN_TYPE_RESTORE,CNcControl_Base::BTN_STATE_NORMAL);
	else
		DrawButton(&dc,this,BTN_TYPE_MAX,CNcControl_Base::BTN_STATE_NORMAL);
	DrawButton(&dc,this,BTN_TYPE_CLOSE,CNcControl_Base::BTN_STATE_NORMAL);

	if(m_skinResCustom.pAryControlPtr)
	{
		for(INT i=0;i<m_skinResCustom.pAryControlPtr->GetCount();i++)
		{
			CNcControl_Base *pControl = (CNcControl_Base*)(m_skinResCustom.pAryControlPtr->GetAt(i));
			if(!pControl) continue;
			pControl->OnNcLButtonUp(nHitTest,point);
		}
	}

}

void CSkinDialog::OnCreate( LPCREATESTRUCT /*lpCreateStruct*/ )
{
	GetWindowText(m_hWnd,m_strCaption.GetBuffer(MAX_PATH),MAX_PATH);//为自绘的标题做准备.
	m_strCaption.ReleaseBuffer();
	//以下代码防止有些窗口不发送WM_NCCALCSIZE消息
	GetWindowRect(m_hWnd,m_rtWnd);
	::MoveWindow(m_hWnd,m_rtWnd.left,m_rtWnd.top,m_rtWnd.Width(),m_rtWnd.Height(),TRUE);
}

void CSkinDialog::OnInitMenuPopup( CMenu* /*pPopupMenu*/, UINT /*nIndex*/, BOOL bSysMenu )
{
	if (bSysMenu) OnNcPaint();//防止在任务栏右键图标时窗口出现最大最小关闭
}

void CSkinDialog::OnShowWindow( BOOL bShow )
{
	if(!bShow)
	{
		//delete this;
	}
}

void CSkinDialog::OnNcDestroy()
{
	delete this;
}

LRESULT CSkinDialog::OnSetText( WNDPROC lpPrevWndFunc,HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam )
{

	CallWindowProc(lpPrevWndFunc,hWnd,Msg,wParam,lParam);
	m_strCaption = CString((LPCTSTR)lParam);
	OnNcPaint();
	return 0;
}

void CSkinDialog::OnNcLButtonDblClk( UINT nHitTest,CPoint point )
{
	if(nHitTest == HTCAPTION && m_sizable)
	{
		CPoint pointTemp = point;
		pointTemp.Offset(m_rtWnd.left * (-1),m_rtWnd.top * (-1));
		for(INT i=0;i<m_skinResCustom.pAryControlPtr->GetCount();i++)
		{
			CNcControl_Base *pCon = (CNcControl_Base*)m_skinResCustom.pAryControlPtr->GetAt(i);
			if(pCon)
			{
				if(pCon->IsInControl(pointTemp) && !pCon->GetAsBackground() && pCon->IsWindowShow())
					return;
			}
		}
		DWORD style = GetWindowLong( m_hWnd, GWL_STYLE );
		style |= WS_MAXIMIZEBOX | WS_SYSMENU;
		SetWindowLong(m_hWnd,GWL_STYLE,style);
		if (IsZoomed(m_hWnd))
			SendMessage(m_hWnd,WM_SYSCOMMAND, SC_RESTORE, MAKELPARAM(point.x, point.y));
		else
			SendMessage(m_hWnd,WM_SYSCOMMAND, SC_MAXIMIZE, MAKELPARAM(point.x, point.y) );
		style = GetWindowLong( m_hWnd, GWL_STYLE );
		style &= ~WS_MAXIMIZEBOX;
		style &= ~WS_SYSMENU;
		SetWindowLong(m_hWnd,GWL_STYLE,style);
	}
}

void CSkinDialog::DrawCaption( Graphics *g,CSkinDialog *pDlg ,BOOL bIsActive)
{
	Image *pTopLeft = NULL;
	Image *pTopRight = NULL;
	Image *pCaption = NULL;
	if(bIsActive)
	{
		pTopLeft = pDlg->m_skinResCustom.pTopLeftAct;
		pTopRight = pDlg->m_skinResCustom.pTopRightAct;
		pCaption = pDlg->m_skinResCustom.pCaptionAct;
	}
	else
	{
		pTopLeft = pDlg->m_skinResCustom.pTopLeftNAct;
		pTopRight = pDlg->m_skinResCustom.pTopRightNAct;
		pCaption = pDlg->m_skinResCustom.pCaptionNAct;
	}
	if(!pTopLeft || !pTopRight || !pCaption) return;
	INT nCaptionHeight = g_dpi.ScaleY(pCaption->GetHeight());
	CRect rtTitle(0,0,pDlg->m_rtWnd.Width(),nCaptionHeight);

	//PixelOffsetMode pOMOld = g->GetPixelOffsetMode();
	//g->SetPixelOffsetMode(PixelOffsetModeHalf);
	//TextureBrush tBrush(pCaption);
	//tBrush.TranslateTransform((REAL)(g_dpi.ScaleX(pTopLeft->GetWidth())) ,0);
	////dpi变化时根据变化拉伸图像
	//tBrush.ScaleTransform(g_dpi.GetDPIX() * 1.0f / 96,g_dpi.GetDPIY() * 1.0f / 96);
	//g->FillRectangle(&tBrush,g_dpi.ScaleX(pTopLeft->GetWidth()),0,
	//	rtTitle.Width() - g_dpi.ScaleX(pTopLeft->GetWidth()) - g_dpi.ScaleX(pTopRight->GetWidth()),
	//	nCaptionHeight);
	//g->SetPixelOffsetMode(pOMOld);

	PixelOffsetMode pOMOld = g->GetPixelOffsetMode();
	g->SetInterpolationMode(InterpolationModeNearestNeighbor);
	g->SetPixelOffsetMode(PixelOffsetModeHalf);
	Rect	rectBanner(/*g_dpi.ScaleX*/(pTopLeft->GetWidth()), 0, 
		rtTitle.Width() - /*g_dpi.ScaleX*/(pTopLeft->GetWidth()) - /*g_dpi.ScaleX*/(pTopRight->GetWidth()),
		nCaptionHeight);
	g->SetClip(rectBanner);
	g->DrawImage(pCaption, (INT)rectBanner.X, (INT)rectBanner.Y, (INT)rectBanner.Width + g_dpi.ScaleX(10), (INT)rectBanner.Height);
	g->ResetClip();
	g->SetPixelOffsetMode(pOMOld);

	g->DrawImage(pTopLeft,0,0,/*g_dpi.ScaleX*/(pTopLeft->GetWidth()),g_dpi.ScaleY(pTopLeft->GetHeight()));
	g->DrawImage(pTopRight,rtTitle.Width() - /*g_dpi.ScaleX*/(pTopRight->GetWidth()),0,/*g_dpi.ScaleX*/(pTopRight->GetWidth()),g_dpi.ScaleY(pTopRight->GetHeight()));
	CRect crtText(rtTitle);
	crtText.left += g_dpi.ScaleX(pDlg->m_skinResCustom.pTopLeftAct->GetWidth()) * 2;
	if(pDlg->m_skinResCustom.bIsUseLogo && pDlg->m_skinResCustom.pCaptionLogo)
	{
		crtText.left += g_dpi.ScaleX(pDlg->m_skinResCustom.pCaptionLogo->GetWidth());
	}
	else
	{
		crtText.left += g_dpi.ScaleY(pDlg->m_skinResCustom.pCaptionAct->GetHeight()) - 2 * g_dpi.ScaleX(pDlg->m_skinResCustom.pLeftAct->GetWidth());
	}
	if(pDlg->m_skinResCustom.bIsNotDrawTitleText == FALSE)
		DrawText(g,crtText,pDlg->m_strCaption,pDlg->m_fontInfoCustom);


}

void CSkinDialog::DrawBorder( Graphics *g,CSkinDialog *pDlg,BOOL bIsActive )
{
	CRect crtWnd(pDlg->m_rtWnd);
	crtWnd.OffsetRect(pDlg->m_rtWnd.left * (-1),pDlg->m_rtWnd.top *(-1));

	Image *pLeft = NULL;
	Image *pRight = NULL;
	Image *pBottom = NULL;
	Image *pBottomLeft = NULL;
	Image *pBottomRight = NULL;
	if(bIsActive)
	{
		pLeft = pDlg->m_skinResCustom.pLeftAct;
		pRight = pDlg->m_skinResCustom.pRightAct;
		pBottom = pDlg->m_skinResCustom.pBottomAct;
		pBottomLeft = pDlg->m_skinResCustom.pBottomLeftAct;
		pBottomRight = pDlg->m_skinResCustom.pBottomRightAct;
	}
	else
	{
		pLeft = pDlg->m_skinResCustom.pLeftNAct;
		pRight = pDlg->m_skinResCustom.pRightNAct;
		pBottom = pDlg->m_skinResCustom.pBottomNAct;
		pBottomLeft = pDlg->m_skinResCustom.pBottomLeftNAct;
		pBottomRight = pDlg->m_skinResCustom.pBottomRightNAct;

	}
	//left border
	CRect rtLeft(0,g_dpi.ScaleY(pDlg->m_skinResCustom.pCaptionAct->GetHeight()),
		/*g_dpi.ScaleX*/(pLeft->GetWidth()),
		crtWnd.bottom - /*g_dpi.ScaleY*/(pBottom->GetHeight()));
	PixelOffsetMode pOMOld = g->GetPixelOffsetMode();
	g->SetPixelOffsetMode(PixelOffsetModeHalf);
	TextureBrush tBrushLeft(pLeft);
	tBrushLeft.TranslateTransform(0 ,0);
	//dpi变化时根据变化拉伸图像
	tBrushLeft.ScaleTransform(g_dpi.GetDPIX() * 1.0f / 96,g_dpi.GetDPIY() * 1.0f / 96);
	g->FillRectangle(&tBrushLeft,rtLeft.left,rtLeft.top,
		rtLeft.Width(),
		rtLeft.Height());
	//right border
	CRect rtRight(crtWnd.right - /*g_dpi.ScaleX*/(pRight->GetWidth()),
		g_dpi.ScaleY(pDlg->m_skinResCustom.pCaptionAct->GetHeight()),
		crtWnd.right,
		crtWnd.bottom - /*g_dpi.ScaleY*/(pBottom->GetHeight()));
	TextureBrush tBrushRight(pRight);
	tBrushRight.TranslateTransform((REAL)rtRight.left ,0);
	//dpi变化时根据变化拉伸图像
	tBrushRight.ScaleTransform(g_dpi.GetDPIX() * 1.0f / 96,g_dpi.GetDPIY() * 1.0f / 96);
	g->FillRectangle(&tBrushRight,rtRight.left,rtRight.top,
		/*g_dpi.ScaleX*/(pRight->GetWidth()),
		rtRight.Height());
	//bottom border
	CRect rtBottom(crtWnd.left,crtWnd.bottom - /*g_dpi.ScaleY*/(pBottom->GetHeight()),
		crtWnd.right,
		crtWnd.bottom);
	TextureBrush tBrushBottom(pBottom);
	tBrushBottom.TranslateTransform((REAL)(crtWnd.left + /*g_dpi.ScaleX*/(pBottomLeft->GetWidth())),
		(REAL)(crtWnd.bottom - /*g_dpi.ScaleY*/(pBottom->GetHeight())));
	//dpi变化时根据变化拉伸图像
	tBrushBottom.ScaleTransform(g_dpi.GetDPIX() * 1.0f / 96,g_dpi.GetDPIY() * 1.0f / 96);
	g->FillRectangle(&tBrushBottom,rtBottom.left,rtBottom.top,
		rtBottom.Width(),
		rtBottom.Height());
	g->DrawImage(pBottomLeft,(REAL)rtBottom.left,(REAL)rtBottom.top,(REAL)g_dpi.ScaleX(pBottomLeft->GetWidth()),(REAL)g_dpi.ScaleY(pBottomLeft->GetHeight()));
	g->DrawImage(pBottomRight,(REAL)(rtBottom.right - /*g_dpi.ScaleX*/(pBottomRight->GetWidth())),
		(REAL)rtBottom.top,
		(REAL)/*g_dpi.ScaleX*/(pBottomRight->GetWidth()),
		(REAL)/*g_dpi.ScaleY*/(pBottomRight->GetHeight()));
	g->SetPixelOffsetMode(pOMOld);

}

void CSkinDialog::DrawButton( Graphics *g,CSkinDialog *pDlg,BTN_TYPE nType,CNcControl_Base::BTN_STATE nState )
{
	CRect crt;
	Image *pImage = NULL;
	if(!pDlg) return;
	pDlg->GetBtnPos(crt,nType);
	if(nType == BTN_TYPE_CLOSE)
	{//close
		if(!pDlg->m_sysmenu && !pDlg->m_minable && !pDlg->m_maxable) return;
		pImage = pDlg->m_skinResCustom.pCloseBox;
	}
	if(nType == BTN_TYPE_MAX)
	{//max
		if(!pDlg->m_maxable) return;
		pImage = pDlg->m_skinResCustom.pMaxBox;
	}
	if(nType == BTN_TYPE_RESTORE)
	{//restore
		if(!pDlg->m_maxable) return;
		pImage = pDlg->m_skinResCustom.pRestoreBox;
	}
	if(nType == BTN_TYPE_MIN)
	{//min
		if(!pDlg->m_minable) return;
		pImage = pDlg->m_skinResCustom.pMinBox;
	}
	INT nX = 0;
	if(nState == CNcControl_Base::BTN_STATE_NORMAL)
	{//normal
		nX = 0;
	}
	else if(nState == CNcControl_Base::BTN_STATE_HOVER)
	{//hover
		nX = pImage->GetWidth()/3;
	}
	else if(nState == CNcControl_Base::BTN_STATE_PRESS)
	{//press
		nX = pImage->GetWidth() * 2 /3;
	}
	RectF rtf((REAL)crt.left,(REAL)crt.top,(REAL)crt.Width(),(REAL)crt.Height()); 
	g->DrawImage(pImage,rtf,(REAL)nX,0,(REAL)pImage->GetWidth()/3,(REAL)pImage->GetHeight(),UnitPixel);

}

void CSkinDialog::DrawButton( CDC* pDC,CSkinDialog *pDlg,BTN_TYPE nType,CNcControl_Base::BTN_STATE nState )
{
	CRect crtBtn;
	pDlg->GetBtnPos(crtBtn,nType);
	CBufferMemDC memDC(pDC, &crtBtn, RGB(255,255,255), FALSE);	
	Graphics graphics(memDC);
	SmoothingMode smOriginal = graphics.GetSmoothingMode();
	TextRenderingHint trOriginal = graphics.GetTextRenderingHint();
	graphics.SetSmoothingMode(SmoothingModeHighQuality);
	graphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);

	DrawButton(&graphics,pDlg,nType,nState);

	graphics.SetSmoothingMode(smOriginal);
	graphics.SetTextRenderingHint(trOriginal);

}

void CSkinDialog::GetBtnPos( CRect &crtBtn,BTN_TYPE nType )
{
	CRect crtWnd(m_rtWnd);
	crtWnd.OffsetRect(crtWnd.left * (-1),crtWnd.top * (-1));
	INT nRightSpace = m_skinResCustom.nBtnRightSpace;
	INT nTopSpace = m_skinResCustom.nBtnTopSpace;
	if(IsZoomed(m_hWnd))
	{
		nRightSpace = GetSystemMetrics(SM_CXSIZEFRAME);
		nTopSpace = GetSystemMetrics(SM_CYSIZEFRAME);
	}
	if(nType == BTN_TYPE_CLOSE)
	{//close
		crtBtn.right = crtWnd.right - nRightSpace;
		crtBtn.left = crtBtn.right - (g_dpi.ScaleX(m_skinResCustom.pCloseBox->GetWidth())/3);
		crtBtn.top = crtWnd.top + nTopSpace;
		crtBtn.bottom = crtBtn.top + g_dpi.ScaleY(m_skinResCustom.pCloseBox->GetHeight());
	}
	if(nType == BTN_TYPE_MAX || nType == BTN_TYPE_RESTORE)
	{//max || restore
		crtBtn.right = crtWnd.right - nRightSpace - g_dpi.ScaleX(m_skinResCustom.pCloseBox->GetWidth())/3 - /*g_dpi.ScaleX*/(1);
		crtBtn.left = crtBtn.right - g_dpi.ScaleX(m_skinResCustom.pMaxBox->GetWidth()) / 3;
		crtBtn.top = crtWnd.top + nTopSpace;
		crtBtn.bottom = crtBtn.top + g_dpi.ScaleY(m_skinResCustom.pMaxBox->GetHeight());
	}
	if(nType == BTN_TYPE_MIN)
	{//min
		crtBtn.right = crtWnd.right - nRightSpace - g_dpi.ScaleX(m_skinResCustom.pCloseBox->GetWidth())/3 - g_dpi.ScaleX(m_skinResCustom.pMaxBox->GetWidth()) / 3 - /*g_dpi.ScaleX*/(2);
		crtBtn.left = crtBtn.right - g_dpi.ScaleX(m_skinResCustom.pMinBox->GetWidth()) / 3;
		crtBtn.top = crtWnd.top + nTopSpace;
		crtBtn.bottom = crtBtn.top + g_dpi.ScaleY(m_skinResCustom.pMinBox->GetHeight());
	}
}

void CSkinDialog::DrawIconLogo( Graphics *g,CSkinDialog *pDlg )
{
	CRect crtWnd(pDlg->m_rtWnd);
	crtWnd.OffsetRect(pDlg->m_rtWnd.left * (-1),pDlg->m_rtWnd.top * (-1));
	if(pDlg->m_skinResCustom.bIsUseLogo && pDlg->m_skinResCustom.pCaptionLogo)
	{//image
		CRect crtIcon;
		crtIcon.left = crtWnd.left + g_dpi.ScaleX(8);
		crtIcon.top = crtWnd.top + g_dpi.ScaleY(10)/*pDlg->m_skinResCustom.pLeftAct->GetWidth()*/;
		crtIcon.right = crtIcon.left + g_dpi.ScaleX(pDlg->m_skinResCustom.pCaptionLogo->GetWidth());
		crtIcon.bottom = crtIcon.top + g_dpi.ScaleX(pDlg->m_skinResCustom.pCaptionLogo->GetHeight());
		g->DrawImage(pDlg->m_skinResCustom.pCaptionLogo,crtIcon.left,crtIcon.top,crtIcon.Width(),crtIcon.Height());
	}
	else if(pDlg->m_skinResCustom.pCaptionLogo)
	{//icon

		CRect crtIcon;
		INT nLeftSpace = g_dpi.ScaleX(8);
		INT nCapHeight = 0;
		if(pDlg->m_skinResCustom.nOwnerDrawType == OWNERDRAW_TYPE_MAINFRAME)
		{
			nCapHeight = CSkinDialog::m_nCaptionHOwnerFrame;
		}
		else if(pDlg->m_skinResCustom.nOwnerDrawType == OWNERDRAW_TYPE_DLG)
		{
			nCapHeight = CSkinDialog::m_nCaptionHOwnerDlg;
		}
		else
		{
			nCapHeight = pDlg->m_skinResCustom.pCaptionAct->GetHeight();
		}
		crtIcon.left = crtWnd.left + nLeftSpace;
		crtIcon.top = (nCapHeight - g_dpi.ScaleY(pDlg->m_skinResCustom.pCaptionLogo->GetHeight() ))/2;
		crtIcon.right = crtIcon.left + g_dpi.ScaleX(pDlg->m_skinResCustom.pCaptionLogo->GetWidth());
		crtIcon.bottom = crtIcon.top + g_dpi.ScaleY(pDlg->m_skinResCustom.pCaptionLogo->GetHeight());
		g->DrawImage(pDlg->m_skinResCustom.pCaptionLogo,crtIcon.left,crtIcon.top,crtIcon.Width(),crtIcon.Height());
	}

}

void CSkinDialog::OnMove( INT /*x*/,INT /*y*/ )
{
	GetWindowRect(m_hWnd,m_rtWnd);
}

void CSkinDialog::OnSize( UINT /*nType*/, int /*cx*/, int /*cy*/ )
{
	GetWindowRect(m_hWnd,m_rtWnd);
	CRect crtWnd(m_rtWnd);
	crtWnd.OffsetRect(m_rtWnd.left * (-1),m_rtWnd.top * (-1));
	CRgn newrgn;
	newrgn.CreateRectRgn(crtWnd.left,crtWnd.top,crtWnd.Width(),crtWnd.Height());
	SetWindowRgn(m_hWnd,(HRGN)newrgn.Detach(),TRUE);
}

BOOL CSkinDialog::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message )
{
	BOOL bRet = FALSE;
	if(m_skinResCustom.pAryControlPtr)
	{
		for(INT i=0;i<m_skinResCustom.pAryControlPtr->GetCount();i++)
		{
			CNcControl_Base *pControl = (CNcControl_Base*)(m_skinResCustom.pAryControlPtr->GetAt(i));
			if(!pControl) continue;
			if(pControl->OnSetCursor(pWnd,nHitTest,message))
				bRet = TRUE;
		}
	}
	
	return bRet;
}

void CSkinDialog::OnNcMouseLeave()
{
	m_bIsTrackingMouse = FALSE;
	CWindowDC dc(CWnd::FromHandle(m_hWnd));
	if(m_bIsPressedMin || m_bMinIsHover)
	{
		m_bIsPressedMin = FALSE;
		m_bMinIsHover = FALSE;
		DrawButton(&dc,this,BTN_TYPE_MIN,CNcControl_Base::BTN_STATE_NORMAL);
	}
	if(m_bIsPressedMax || m_bMaxIsHover)
	{
		m_bIsPressedMax = FALSE;
		m_bMaxIsHover = FALSE;
		if(IsZoomed(m_hWnd))
			DrawButton(&dc,this,BTN_TYPE_RESTORE,CNcControl_Base::BTN_STATE_NORMAL);
		else
			DrawButton(&dc,this,BTN_TYPE_MAX,CNcControl_Base::BTN_STATE_NORMAL);
	}
	if(m_bIsPressedClose || m_bCloseIsHover)
	{
		m_bIsPressedClose = FALSE;
		m_bCloseIsHover = FALSE;
		DrawButton(&dc,this,BTN_TYPE_CLOSE,CNcControl_Base::BTN_STATE_NORMAL);
	}
	if(m_skinResCustom.pAryControlPtr)
	{
		for(INT i=0;i<m_skinResCustom.pAryControlPtr->GetCount();i++)
		{
			CNcControl_Base *pCon = (CNcControl_Base*)m_skinResCustom.pAryControlPtr->GetAt(i);
			if(pCon && pCon->IsHover())
			{
				pCon->OnNcPaint();
			}
		}
	}
}

void CSkinDialog::DrawCaptionOwner( Graphics *g,CSkinDialog *pDlg,BOOL /*bIsActive*/ )
{
	if(!g || !pDlg) return;
	INT nCaptionHeight = 0;
	COLORREF clrTop = 0;
	COLORREF clrBottom = 0;
	COLORREF clrOutLine = 0;
	if(pDlg->m_skinResCustom.nOwnerDrawType == OWNERDRAW_TYPE_MAINFRAME)
	{
		nCaptionHeight = CSkinDialog::m_nCaptionHOwnerFrame;
		clrTop = CLR2ARGB(RGB(81,151,191));
		clrBottom = CLR2ARGB(RGB(14,66,124));
		clrOutLine = CLR2ARGB(RGB(0,0,139));
	}
	else if(pDlg->m_skinResCustom.nOwnerDrawType == OWNERDRAW_TYPE_DLG)
	{
		nCaptionHeight = CSkinDialog::m_nCaptionHOwnerDlg;
		clrTop = CLR2ARGB(RGB(0,134,199));
		clrBottom = CLR2ARGB(RGB(0,111,164));
		clrOutLine = CLR2ARGB(RGB(0,111,164));

	}
	SmoothingMode oldSm = g->GetSmoothingMode();
	g->SetSmoothingMode(SmoothingModeNone);
	CRect rtTitle(0,0,pDlg->m_rtWnd.Width(),nCaptionHeight);
	RectF rectFTop((REAL)rtTitle.left, (REAL)rtTitle.top, (REAL)rtTitle.Width(), (REAL)rtTitle.Height());
	LinearGradientBrush brushGradient(rectFTop, clrTop,clrBottom, LinearGradientModeVertical);
	REAL factors1[4] = {0.0f, 0.5f, 1.0f};
	REAL positions1[4] = {0.0f, 0.5f, 1.0f};
	brushGradient.SetBlend(factors1, positions1, 3);
	FillSolidRect(g, rtTitle, 0, &brushGradient, NULL);

	g->SetSmoothingMode(oldSm);
	CRect crtText(rtTitle);
	crtText.left += g_dpi.ScaleX(8);
	if(pDlg->m_skinResCustom.bIsUseLogo && pDlg->m_skinResCustom.pCaptionLogo)
	{
		crtText.left += g_dpi.ScaleX(pDlg->m_skinResCustom.pCaptionLogo->GetWidth());
	}
	else
	{
		crtText.left += g_dpi.ScaleX(24);
	}
	if(pDlg->m_skinResCustom.bIsNotDrawTitleText == FALSE)
		DrawText(g,crtText,pDlg->m_strCaption,pDlg->m_fontInfoCustom);

}

void CSkinDialog::DrawBorderOwner( Graphics *g,CSkinDialog *pDlg,BOOL /*bIsActive*/ )
{
	CRect crtWnd(pDlg->m_rtWnd);
	crtWnd.OffsetRect(pDlg->m_rtWnd.left * (-1),pDlg->m_rtWnd.top *(-1));
	COLORREF clrOutLine = 0;
	if(pDlg->m_skinResCustom.nOwnerDrawType == OWNERDRAW_TYPE_MAINFRAME)
	{
		CRect crtBottom(crtWnd);
		crtBottom.top = crtBottom.bottom - m_nBottomHOwnerFrame - 1;
		FillSolidRect(g,crtBottom,0,RGB(14,67,124),0);
		CRect crtLeft(crtWnd);
		crtLeft.right = crtLeft.left + m_nLeftWOwnerFrame;
		crtLeft.top += m_nCaptionHOwnerFrame - 1;
		crtLeft.bottom -= m_nBottomHOwnerFrame;
		FillSolidRect(g,crtLeft,0,RGB(14,67,124),0);
		clrOutLine = CLR2ARGB(RGB(0,0,139));
	}
	else if(pDlg->m_skinResCustom.nOwnerDrawType == OWNERDRAW_TYPE_DLG)
	{
		clrOutLine = CLR2ARGB(RGB(0,111,164));
	}
	Pen pen(clrOutLine,1.0f);
	g->DrawRectangle(&pen,crtWnd.left,crtWnd.top,crtWnd.Width()-1,crtWnd.Height()-1);
}







