// Base_Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Base_Dlg.h"
#include "../commonclass/GUI_Utils.h"

// CBase_Dlg dialog

CBase_Dlg::CBase_Dlg(UINT nIDTemplate,CWnd* pParent /*=NULL*/)
	: CDialogEx(nIDTemplate, pParent)
{

}

CBase_Dlg::~CBase_Dlg()
{
}

HBRUSH CBase_Dlg::OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor )
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor) 
	{
	case CTLCOLOR_DLG:
		hbr = (HBRUSH)CGUI_Utils::GetInstance()->m_brushDialogPageBackground;
		break;
	case CTLCOLOR_STATIC:
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)CGUI_Utils::GetInstance()->m_brushDialogPageBackground;/*::GetStockObject(NULL_BRUSH);*/
		break;
	default:
		break;
	}
	return hbr;

}

void CBase_Dlg::LoadMainFrameSkin(SKIN_RESOURCE &skinRes, CFontInfo &fontInfo)
{
	skinRes.hIcon = /*AfxGetApp()->LoadIcon(IDR_MAINFRAME)*/NULL;
	skinRes.pCloseBox = LoadImageInResource(140);
	skinRes.pMaxBox = LoadImageInResource(140);
	skinRes.pMinBox = LoadImageInResource(141);
	skinRes.pRestoreBox = NULL;
	skinRes.pCaptionLogo = NULL/*LoadImageInResource(IDB_PNG_MAIN_LOGO)*/;
	skinRes.bIsUseLogo = FALSE;
	skinRes.bIsNotDrawTitleText = TRUE;
	skinRes.nBtnRightSpace = /*g_dpi.ScaleX*/(1);
	skinRes.nBtnTopSpace = /*g_dpi.ScaleY*/(1);
	skinRes.nOwnerDrawType = OWNERDRAW_TYPE_MAINFRAME;

	fontInfo.strFontName = DRAW_FONT_NAME;
	fontInfo.fFontSize = 22.0;;
	fontInfo.nFontCor = RGB(255, 255, 255);
	fontInfo.nFontStyle = FontStyleRegular;
	fontInfo.saH = StringAlignmentNear;
	fontInfo.saV = StringAlignmentCenter;
}

BOOL CBase_Dlg::PreTranslateMessage(MSG* pMsg)
{
	BOOL bIsEdit = FALSE;
	if(pMsg->hwnd && IsWindow(pMsg->hwnd))
	{
		if(CWnd::FromHandle(pMsg->hwnd)->IsKindOf(RUNTIME_CLASS(CEdit)))
			bIsEdit = TRUE;
	}
	if (WM_KEYDOWN == pMsg->message &&
		(VK_RETURN == pMsg->wParam || VK_ESCAPE == pMsg->wParam
		|| VK_SPACE == pMsg->wParam))
	{
		if(bIsEdit && VK_SPACE == pMsg->wParam)
		{
			return CDialog::PreTranslateMessage(pMsg);
		}

		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CBase_Dlg::DrawTitleRect(CRect rc,CBufferMemDC& memDC,BOOL bIsTop /*= TRUE*/)
{
	Graphics g(memDC);
	SmoothingMode smOriginal = g.GetSmoothingMode();
	TextRenderingHint trOriginal = g.GetTextRenderingHint();
	g.SetSmoothingMode(SmoothingModeNone);
	g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
	//CRect rc(rectClient);
	//rc.bottom = rc.top + g_dpi.ScaleY(100);

	COLORREF clrTop = TITLE_BAR_COLOR_TOP;
	COLORREF clrBottom = TITLE_BAR_COLOR_BOTTOM;
	if(!bIsTop)
	{
		clrTop = CLR2ARGB(RGB(255,255,255));
		clrBottom = CLR2ARGB(RGB(153,204,255));
	}
	RectF rectFTop((REAL)rc.left, (REAL)rc.top-1, (REAL)rc.Width(), (REAL)rc.Height()+1);
	//LinearGradientBrush brushGradient(rectFTop, (ARGB)Color::White, (ARGB)Color::Black, LinearGradientModeVertical);
	LinearGradientBrush brushGradient(rectFTop, clrTop,clrBottom, LinearGradientModeVertical);
	REAL factors1[4] = {0.0f, 0.5f, 1.0f};
	REAL positions1[4] = {0.0f, 0.5f, 1.0f};
	brushGradient.SetBlend(factors1, positions1, 3);
	FillSolidRect(&g, rc, 0, &brushGradient, NULL);
	//g.FillRectangle(&brushGradient,rectFTop);

	// restore the original drawing mode
	g.SetSmoothingMode(smOriginal);
	g.SetTextRenderingHint(trOriginal);
}