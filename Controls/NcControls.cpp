#include "stdafx.h"
#include "NcControls.h"
#include "../commonclass/BufferMemDC.h"
CNcControl_Base::CNcControl_Base()
{
	m_pParentWnd = NULL;
	m_crtWnd = CRect(0,0,0,0);
	m_unResID = 0;
	m_bIsShowWindow = TRUE;
	m_strWindowText = L"";
	m_bIsHover = FALSE;
	m_bIsFillBK = TRUE;
	m_corBK = RGB(255,255,255);
	m_bIsAsBackground = FALSE;
}

CNcControl_Base::~CNcControl_Base()
{

}

BOOL CNcControl_Base::Create( UINT unResID,CRect crtWnd,CWnd *pParent )
{
	if(pParent == NULL) return FALSE;
	m_unResID = unResID;
	m_pParentWnd = pParent;
	m_crtWnd = crtWnd;
	return TRUE;
}

BOOL CNcControl_Base::IsInControl( CPoint point )
{
	return m_crtWnd.PtInRect(point);
}

BOOL CNcControl_Base::IsWindowShow()
{
	return m_bIsShowWindow;
}

BOOL CNcControl_Base::IsHover()
{
	return m_bIsHover;
}

void CNcControl_Base::MoveWindow( CRect crt ,BOOL bIsRefresh/* = FALSE*/)
{
	m_crtWnd = crt;
	if(bIsRefresh)
		OnNcPaint();
}

void CNcControl_Base::MoveWindow( INT nl, INT nT, INT nR, INT nB,BOOL bIsRefresh/* = FALSE*/ )
{
	m_crtWnd = CRect(nl,nT,nR,nB);
	if(bIsRefresh)
		OnNcPaint();
}

void CNcControl_Base::ShowWindow( BOOL bIsShow )
{
	if(m_bIsShowWindow == bIsShow) return;
	m_bIsShowWindow = bIsShow;
	OnNcPaint();
}

void CNcControl_Base::SetWindowText( CString strText )
{
	m_strWindowText = strText;
	OnNcPaint();
}

void CNcControl_Base::SetWindowText( UINT unResID )
{
	m_strWindowText.LoadString(unResID);
	OnNcPaint();
}

void CNcControl_Base::SetFontInfo( CFontInfo fontInfo )
{
	m_fontInfo = fontInfo;
}

CFontInfo CNcControl_Base::GetFontInfo()
{
	return m_fontInfo;
}

void CNcControl_Base::OnNcPaint()
{
	CWindowDC dc(CWnd::FromHandle(m_pParentWnd->m_hWnd));
	CBufferMemDC memDC(&dc, &m_crtWnd, m_corBK, m_bIsFillBK);	
	Graphics graphics(memDC);
	SmoothingMode smOriginal = graphics.GetSmoothingMode();
	TextRenderingHint trOriginal = graphics.GetTextRenderingHint();
	graphics.SetSmoothingMode(SmoothingModeHighQuality);
	graphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
	OnNcPaint(&graphics);
	graphics.SetSmoothingMode(smOriginal);
	graphics.SetTextRenderingHint(trOriginal);

}

void CNcControl_Base::SetBKCor( COLORREF cor )
{
	m_corBK = cor;
}

void CNcControl_Base::SetFillBK( BOOL bIsFill )
{
	m_bIsFillBK = bIsFill;
}

UINT CNcControl_Base::GetCtrlID()
{
	return m_unResID;
}

void CNcControl_Base::SetAsBackground( BOOL bIsAsBackground )
{
	m_bIsAsBackground = bIsAsBackground;
}

BOOL CNcControl_Base::GetAsBackground()
{
	return m_bIsAsBackground;
}

//////////////////////////////////////////////////////////////////////////
//link button

CNcControl_LinkButton::CNcControl_LinkButton()
{

	m_bIsPressed = FALSE;
	m_strWindowText = L"";
	m_fontInfo.fFontSize = 9.0;
	m_fontInfo.nFontCor = RGB(0,0,255);
	m_fontInfo.nFontStyle = FontStyleUnderline;
	m_fontInfo.saH = StringAlignmentCenter;
	m_fontInfo.saV = StringAlignmentCenter;
	m_fontInfo.strFontName = DRAW_FONT_NAME;
	m_hCursor = LoadCursor(NULL,IDC_HAND);
	m_bIsFillBK = TRUE;
	m_corBK = RGB(255,255,255);
}

CNcControl_LinkButton::~CNcControl_LinkButton()
{

}
void CNcControl_LinkButton::OnNcPaint(Graphics *g)
{
	CString strText = m_strWindowText;
	if(!m_bIsShowWindow) strText = L"";
	DrawText(g,m_crtWnd,strText,m_fontInfo);

}

BOOL CNcControl_LinkButton::OnNcLButtonDown( WPARAM /*wParam*/,LPARAM lParam )
{
	if(!m_bIsShowWindow) return FALSE;
	CPoint point(SHORT(LOWORD(lParam)),SHORT(HIWORD(lParam)));
	CRect crtParent;
	m_pParentWnd->GetWindowRect(crtParent);
	point.Offset(crtParent.left * (-1),crtParent.top * (-1));

	if(!IsInControl(point)) return FALSE;
	m_bIsPressed = TRUE;
	return TRUE;
}

void CNcControl_LinkButton::OnNcLButtonUp( UINT /*nHitTest*/, CPoint point )
{
	if(!m_bIsShowWindow) return;
	if(IsInControl(point) && m_bIsPressed)
	{
		::SendMessage(m_pParentWnd->m_hWnd,WM_COMMAND,
			MAKELPARAM(m_unResID,BN_CLICKED),NULL);
	}
	m_bIsPressed = FALSE;
}

BOOL CNcControl_LinkButton::OnSetCursor( CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/ )
{
	if(!m_bIsShowWindow) return FALSE;
	CRect crtParent;
	m_pParentWnd->GetWindowRect(crtParent);
	CPoint point;
	GetCursorPos( &point );
	point.Offset(crtParent.left * (-1),crtParent.top * (-1));
	if(IsInControl(point))
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
void CNcControl_Static::OnNcPaint(Graphics *g)
{
	CString strText = m_strWindowText;
	if(!m_bIsShowWindow) strText = L"";

	DrawText(g,m_crtWnd,strText,m_fontInfo);

}

BOOL CNcControl_Static::OnNcLButtonDown( WPARAM /*wParam*/,LPARAM lParam )
{
	if(!m_bIsShowWindow) return FALSE;
	if(m_bIsAsBackground) return FALSE;
	CPoint point(SHORT(LOWORD(lParam)),SHORT(HIWORD(lParam)));
	CRect crtParent;
	m_pParentWnd->GetWindowRect(crtParent);
	point.Offset(crtParent.left * (-1),crtParent.top * (-1));

	if(!IsInControl(point)) return FALSE;
	return TRUE;

}

CNcControl_Static::CNcControl_Static()
{
	m_strWindowText = L"";
	m_fontInfo.fFontSize = 9.0;
	m_fontInfo.nFontCor = RGB(0,0,0);
	m_fontInfo.nFontStyle = FontStyleRegular;
	m_fontInfo.saH = StringAlignmentCenter;
	m_fontInfo.saV = StringAlignmentCenter;
	m_fontInfo.strFontName = DRAW_FONT_NAME;
	m_bIsFillBK = TRUE;
	m_corBK = RGB(255,255,255);

}

CNcControl_Static::~CNcControl_Static()
{

}

//////////////////////////////////////////////////////////////////////////
void CNcControl_ToolBtn::OnNcPaint(Graphics *g)
{
	DrawToolBtn(g,BTN_STATE_NORMAL);
}

BOOL CNcControl_ToolBtn::OnNcLButtonDown( WPARAM /*wParam*/,LPARAM lParam )
{
	if(!m_bIsShowWindow) return FALSE;

	CPoint point(SHORT(LOWORD(lParam)),SHORT(HIWORD(lParam)));
	CRect crtParent;
	m_pParentWnd->GetWindowRect(crtParent);
	point.Offset(crtParent.left * (-1),crtParent.top * (-1));

	if(!IsInControl(point)) return FALSE;
	m_bIsPressed = TRUE;
	return TRUE;

}

void CNcControl_ToolBtn::OnNcLButtonUp( UINT /*nHitTest*/, CPoint point )
{
	if(!m_bIsShowWindow) return;
	if(IsInControl(point) && m_bIsPressed)
	{
		::SendMessage(m_pParentWnd->m_hWnd,WM_COMMAND,
			MAKELPARAM(m_unResID,BN_CLICKED),NULL);
	}
	m_bIsPressed = FALSE;

}

void CNcControl_ToolBtn::OnNcMouseMove(WPARAM /*wParam*/,LPARAM lParam)
{
	if(!m_bIsShowWindow) return;

	CPoint point(SHORT(LOWORD(lParam)),SHORT(HIWORD(lParam)));
	CRect crtParent;
	m_pParentWnd->GetWindowRect(crtParent);
	point.Offset(crtParent.left * (-1),crtParent.top * (-1));

	CWindowDC dc(CWnd::FromHandle(m_pParentWnd->m_hWnd));

	if(IsInControl(point))
	{
		DrawToolBtn(&dc,BTN_STATE_HOVER);
		m_bIsHover = TRUE;
	}
	else
	{
		DrawToolBtn(&dc,BTN_STATE_NORMAL);
		m_bIsHover = FALSE;
	}


}

void CNcControl_ToolBtn::SetImage( Image *pImage )
{
	m_pImage = pImage;
}

void CNcControl_ToolBtn::SetSelected( BOOL bIsSelected )
{
	m_bIsSelected = bIsSelected;
	CNcControl_Base::OnNcPaint();
}

BOOL CNcControl_ToolBtn::IsSelected()
{
	return m_bIsSelected;
}

CNcControl_ToolBtn::CNcControl_ToolBtn()
{
	m_pImage = NULL;
	m_pImageNor = NULL;
	m_pImageHover = NULL;
	m_pImageSelected = NULL;
	m_bIsSelected = FALSE;
	m_strWindowText = L"";
	m_fontInfo.fFontSize = 8.5;
	m_fontInfo.nFontCor = RGB(255,255,255);
	m_fontInfo.nFontStyle = FontStyleBold;
	m_fontInfo.saH = StringAlignmentCenter;
	m_fontInfo.saV = StringAlignmentNear;
	m_fontInfo.strFontName = DRAW_FONT_NAME;
	m_fontInfo.bDontChangeAlias = TRUE;
	m_bIsPressed = FALSE;
}

CNcControl_ToolBtn::~CNcControl_ToolBtn()
{
	SAFE_DELETE(m_pImage)
		SAFE_DELETE(m_pImageNor)
		SAFE_DELETE(m_pImageHover)
		SAFE_DELETE(m_pImageSelected)
}
void CNcControl_ToolBtn::DrawToolBtn(Graphics *g,BTN_STATE nState )
{
	if(!m_pImage || !m_pImageHover || !m_pImageNor || !m_pImageSelected) return;
	//ÏÈ»­Ä¬ÈÏ±³¾°
	PixelOffsetMode pOMOld = g->GetPixelOffsetMode();
	g->SetPixelOffsetMode(PixelOffsetModeHalf);
	TextureBrush tBrush(m_pImageNor);
	tBrush.TranslateTransform(0 ,0);

	tBrush.ScaleTransform(g_dpi.GetDPIX() * 1.0f / 96,g_dpi.GetDPIY() * 1.0f / 96);
	g->FillRectangle(&tBrush,m_crtWnd.left,m_crtWnd.top,m_crtWnd.Width(),m_crtWnd.Height());
	g->SetPixelOffsetMode(pOMOld);

	g->SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
	COLORREF corBakText = RGB(0,0,139);
	if(m_bIsShowWindow)
	{
		Image *pImage = NULL;
		COLORREF corText = RGB(255,255,255);
		if(m_bIsSelected)
		{
			pImage = m_pImageSelected;
			corText = RGB(0,0,139);
			corBakText = RGB(204,204,204);
		}
		else
		{
			if(nState == BTN_STATE_HOVER)
			{
				pImage = m_pImageHover;
				corText = RGB(0,0,139);
				corBakText = RGB(204,204,204);
			}
			else if(nState == BTN_STATE_PRESS)
			{
				pImage = m_pImageHover;
				corText = RGB(0,0,139);	
				corBakText = RGB(204,204,204);
			}
		}
		m_fontInfo.nFontCor = corText;
		if(pImage)
			g->DrawImage(pImage,m_crtWnd.left,m_crtWnd.top,m_crtWnd.Width(),m_crtWnd.Height());
		CRect crtImage(m_crtWnd);
		crtImage.left += (m_crtWnd.Width() - g_dpi.ScaleX(m_pImage->GetWidth())) / 2;
		crtImage.right = crtImage.left + g_dpi.ScaleX(m_pImage->GetWidth());
		//crtImage.top += g_dpi.ScaleY(12);
		crtImage.bottom = crtImage.top + g_dpi.ScaleY(m_pImage->GetHeight());
		g->DrawImage(m_pImage,crtImage.left,crtImage.top,crtImage.Width(),crtImage.Height());
		CRect crtText(m_crtWnd);
		crtText.top = crtImage.bottom;
		crtText.OffsetRect(0,1);
		m_fontInfo.nFontCor = corBakText;
		DrawText(g,crtText,m_strWindowText,m_fontInfo);
		crtText.OffsetRect(0,-1);
		m_fontInfo.nFontCor = corText;
		DrawText(g,crtText,m_strWindowText,m_fontInfo);
	}
}

void CNcControl_ToolBtn::DrawToolBtn( CDC *pDC,BTN_STATE nState )
{
	CBufferMemDC memDC(pDC, &m_crtWnd, RGB(255,255,255), FALSE);	
	Graphics graphics(memDC);
	SmoothingMode smOriginal = graphics.GetSmoothingMode();
	TextRenderingHint trOriginal = graphics.GetTextRenderingHint();
	graphics.SetSmoothingMode(SmoothingModeHighQuality);
	graphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
	DrawToolBtn(&graphics,nState);
	graphics.SetSmoothingMode(smOriginal);
	graphics.SetTextRenderingHint(trOriginal);

}

void CNcControl_ToolBtn::SetNorImage( Image *pImage )
{
	m_pImageNor = pImage;
}

void CNcControl_ToolBtn::SetSelectedImage( Image *pImage )
{
	m_pImageSelected = pImage;
}

void CNcControl_ToolBtn::SetHoverImage( Image *pImage )
{
	m_pImageHover = pImage;
}


CNcControl_Picture::CNcControl_Picture()
{
	m_pImage = NULL;
}

CNcControl_Picture::~CNcControl_Picture()
{
	SAFE_DELETE(m_pImage)
}

void CNcControl_Picture::OnNcPaint( Graphics *g )
{
	if(m_pImage)
		g->DrawImage(m_pImage,m_crtWnd.left,m_crtWnd.top,m_crtWnd.Width(),m_crtWnd.Height());
}

void CNcControl_Picture::SetImageID( UINT unImage )
{
	SAFE_DELETE(m_pImage)
	m_pImage = LoadImageInResource(unImage);
}

CNcControl_ImageBtn::CNcControl_ImageBtn()
{
	m_pImage = NULL;
	m_bIsPressed = FALSE;
	m_hCursor = LoadCursor(NULL,IDC_HAND);
}

CNcControl_ImageBtn::~CNcControl_ImageBtn()
{
	SAFE_DELETE(m_pImage)
}

void CNcControl_ImageBtn::OnNcPaint( Graphics *g )
{
	if(m_pImage)
		g->DrawImage(m_pImage,m_crtWnd.left,m_crtWnd.top,m_crtWnd.Width(),m_crtWnd.Height());
}

void CNcControl_ImageBtn::SetImageID( UINT unImage )
{
	SAFE_DELETE(m_pImage)
	m_pImage = LoadImageInResource(unImage);
}

BOOL CNcControl_ImageBtn::OnNcLButtonDown( WPARAM /*wParam*/,LPARAM lParam )
{
	if(!m_bIsShowWindow) return FALSE;
	CPoint point(SHORT(LOWORD(lParam)),SHORT(HIWORD(lParam)));
	CRect crtParent;
	m_pParentWnd->GetWindowRect(crtParent);
	point.Offset(crtParent.left * (-1),crtParent.top * (-1));

	if(!IsInControl(point)) return FALSE;
	m_bIsPressed = TRUE;
	return TRUE;

}

void CNcControl_ImageBtn::OnNcLButtonUp( UINT /*nHitTest*/, CPoint point )
{
	if(!m_bIsShowWindow) return;
	if(IsInControl(point) && m_bIsPressed)
	{
		::SendMessage(m_pParentWnd->m_hWnd,WM_COMMAND,
			MAKELPARAM(m_unResID,BN_CLICKED),NULL);
	}
	m_bIsPressed = FALSE;

}

BOOL CNcControl_ImageBtn::OnSetCursor( CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/ )
{
	if(!m_bIsShowWindow) return FALSE;
	CRect crtParent;
	m_pParentWnd->GetWindowRect(crtParent);
	CPoint point;
	GetCursorPos( &point );
	point.Offset(crtParent.left * (-1),crtParent.top * (-1));
	if(IsInControl(point))
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}
	return FALSE;

}
