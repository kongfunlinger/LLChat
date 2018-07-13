#include "StdAfx.h"
#include "ImgGlassButton.h"
#include "../commonclass/BufferMemDC.h"
CImgGlassButton::CImgGlassButton(void)
{
	m_clrFont = DLG_BUTTON_NORMAL_FONT_COLOR;
	m_clrOutLine = CLRA2ARGB(COLOR_DLG_BUTTON_OUTLINE, 0xff000000);
	m_clrFill = CLRA2ARGB(COLOR_DLG_BUTTON_NORMAL_ENABLED, 0xff000000);
	m_clrButton = COLOR_DLG_BUTTON_NORMAL_ENABLED;
	m_clrGradientTop = CLRA2ARGB(COLOR_CENTER_BOX, 0xff000000);
	m_clrGradientBottom = CLRA2ARGB(COLOR_CENTER_BOX, 0xff000000);
	m_pImage = NULL;
	m_bOverControl = FALSE;
	m_bIsTrackingMouse = FALSE;
	m_hRgn = 0;
	m_nLeftSpaceIcon = g_dpi.ScaleX(16);
	m_nBottomSpaceText = g_dpi.ScaleX(8);
	m_nBtnType = BUTTON_TYPE_ACTION;
	m_fFontSize = 12.0;
	m_bIsPressed = FALSE;
	m_bSetFocusToParent = TRUE;
	m_nFontStyle = FontStyleBold;
}

CImgGlassButton::~CImgGlassButton(void)
{
	delete m_pImage;
}

BEGIN_MESSAGE_MAP(CImgGlassButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CImgGlassButton::SetImageName(UINT unResID)
{
	if ( m_pImage )
	{
		delete m_pImage;
	}
	m_pImage = LoadImageInResource( unResID );
}

void CImgGlassButton::SetGradient(COLORREF clrTop,COLORREF clrBottom)
{
	m_clrGradientTop = clrTop;
	m_clrGradientBottom = clrBottom;
}

void CImgGlassButton::SetOutLineColor(COLORREF clrOutLine)
{
	m_clrOutLine= clrOutLine;
}

void CImgGlassButton::SetFontColor(COLORREF clrFontColor)
{
	m_clrFont = clrFontColor;
}

void CImgGlassButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC*	pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rectClient;
	GetClientRect(rectClient);
	CBufferMemDC memDC(pDC, &rectClient, RGB(255,0,0), FALSE);	
	Graphics g(memDC);

	// Getthe right button font attributes
	CString  fontFamilyName = DLG_BUTTON_NORMAL_FONT_NAME;

	TextRenderingHint trOriginal = g.GetTextRenderingHint();
	SmoothingMode smOriginal = g.GetSmoothingMode();
	g.SetSmoothingMode(SmoothingModeHighQuality);
	g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit); 

	BOOL bIsSelected = (lpDIS->itemState & ODS_SELECTED);

	CRect rect;
	GetClientRect(rect);
	rect.top += 3;
	CRect rectImage = rect;

	RectF imageRect;
	if(m_pImage)
	{
		imageRect.Y = (REAL)(rectImage.Height()/2) - g_dpi.ScaleY(m_pImage->GetHeight()/2 - 3);
		imageRect.X = (REAL)m_nLeftSpaceIcon;
		imageRect.Width = (REAL)g_dpi.ScaleX(m_pImage->GetWidth());
		imageRect.Height = (REAL)g_dpi.ScaleY(m_pImage->GetHeight());
	}

	DrawImgGlassButton(&g);

	CString strText;
	GetWindowText(strText);

	if (m_pImage)
	{
		rect.left += INT(40);
		rect.top = INT(imageRect.Y + imageRect.Height + m_nBottomSpaceText);
		rect.bottom = rect.top + INT(40);
	}
	if (bIsSelected)
	{
		rect.OffsetRect(1,1);
		imageRect.Offset(1,1);
	}
	if(m_bOverControl)
	{
		rect.OffsetRect(-1,-1);
		imageRect.Offset(-1,-1);
	}
	
	// Draw button text, only draw outline when text color is non-distraction (Black)
	COLORREF clrFont = m_clrFont;
	if(m_nBtnType == BUTTON_TYPE_ACTION)
	{
		clrFont = RGB(255,255,255);
	}
	else if(m_nBtnType == BUTTON_TYPE_NON_DISTRACTION)
	{
		clrFont = RGB(0,0,139);
	}
	else if (m_nBtnType == BUTTON_TYPE_NEW_NON_DISTRACTION)
	{
		clrFont = RGB(51, 51, 51);
	}
	DrawText(&g, rect, strText, fontFamilyName, m_fFontSize, m_nFontStyle, clrFont, m_pImage ? StringAlignmentNear : StringAlignmentCenter, StringAlignmentCenter, 0, 0);
	
	if (m_pImage)
	{
//		g.DrawImage(m_pImage, (int)(rectImage.Height()/4), (int)(rectImage.Height()/2) - (m_pImage->GetHeight()/2), m_pImage->GetWidth(), m_pImage->GetHeight() );
		g.DrawImage(m_pImage, imageRect);
	}

	g.SetSmoothingMode(smOriginal);
	g.SetTextRenderingHint(trOriginal);


	// TODO:  Add your code to draw the specified item
}

void CImgGlassButton::DrawImgGlassButton(Graphics* g)
{
	CRect crtClient;
	GetClientRect(crtClient);
	crtClient.left += 3;
	crtClient.top += 3;
	crtClient.bottom -=3;
	crtClient.right -=3;

	Color corOutLine = CLR2ARGB(m_clrOutLine);
	Color corTop = CLR2ARGB(m_clrGradientTop);
	Color corBottom = CLR2ARGB(m_clrGradientBottom);
	if(m_nBtnType == BUTTON_TYPE_ACTION)
	{
		corOutLine = CLR2ARGB(RGB(0,64,0));
		corTop = CLR2ARGB(RGB(0,147,0));
		corBottom = CLR2ARGB(RGB(0,85,0));
	}
	else if(m_nBtnType == BUTTON_TYPE_NON_DISTRACTION)
	{
		corOutLine = CLR2ARGB(RGB(153,153,153));
		corTop = CLR2ARGB(RGB(255,255,255));
		corBottom = CLR2ARGB(RGB(204,204,204));
	}
	else if (m_nBtnType == BUTTON_TYPE_NEW_NON_DISTRACTION)
	{
		corOutLine = CLR2ARGB(RGB(153, 153, 153));
		corTop = CLR2ARGB(RGB(255, 255, 255));
		corBottom = CLR2ARGB(RGB(204, 204, 204));
	}
	
	CRect rectMiddle(crtClient);

	REAL radius =12.0;
	SolidBrush BrushCenter(m_clrFill);
	GraphicsPath gp;
	Pen pen(corOutLine, 1.5f);
	_CreateRectPath(&gp, rectMiddle, radius, CORNERS_ALL);
	DrawGradientBackground( &gp, crtClient, corTop, corBottom, g, radius, CORNERS_ALL);
	//g->DrawPath(&pen, &gp);
}

void CImgGlassButton::OnMouseMove(UINT /*nFlags*/, CPoint /*point*/)
{
	// TODO: Add your message handler code here and/or call default
	// start tracking mouse, if we haven't done so
	if (!m_bIsTrackingMouse)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = this->m_hWnd;

		if (::_TrackMouseEvent(&tme))
		{
			m_bIsTrackingMouse = TRUE;
		}

		
	}

	if(!m_bOverControl)
    {
        m_bOverControl = TRUE;
		Invalidate();
    }
}

void CImgGlassButton::OnMouseLeave()
{
	if (m_bIsTrackingMouse)
	{
		m_bIsTrackingMouse = FALSE;
		Invalidate();
	}
	m_bOverControl = FALSE;
	m_bIsPressed = FALSE;
}

void CImgGlassButton::OnLButtonUp(UINT /*nFlags*/, CPoint point)
{
	CRect crtClient;
	GetClientRect(crtClient);
	GetParent()->SetFocus();
	if(!PtInRect(crtClient,point)) return;
	if(m_bIsPressed)
	{
		::SendMessage(GetParent()->m_hWnd,WM_COMMAND,
			MAKELPARAM(GetDlgCtrlID(),BN_CLICKED),LPARAM(m_hWnd));
	}
	m_bIsPressed = FALSE;
	if(m_bSetFocusToParent)
		GetParent()->SetFocus();
}

void CImgGlassButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bIsPressed = TRUE;

	CButton::OnLButtonDown(nFlags, point);
}

void CImgGlassButton::DrawGradientBackground(GraphicsPath *pGP,CRect &rc, Color clrGradientTop, Color clrGradientBottom, Graphics* g, REAL /*radius*/, DWORD /*fCorners*/ )
{
	RectF rectFTop((REAL)rc.left, (REAL)rc.top, (REAL)rc.Width(), (REAL)rc.Height());
	LinearGradientBrush brushGradient(rectFTop, clrGradientTop, clrGradientBottom, LinearGradientModeVertical);
	REAL factors1[4] = {0.0f, 0.5f, 1.0f};
	REAL positions1[4] = {0.0f, 0.5f, 1.0f};
	brushGradient.SetBlend(factors1, positions1, 3);
	g->FillPath(&brushGradient,pGP);
}

BOOL CImgGlassButton::OnEraseBkgnd(CDC* /*pDC*/)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}

void CImgGlassButton::SetLeftSpace( INT nLeftSpaceIcon,INT nLeftSpaceText)
{
	m_nLeftSpaceIcon = nLeftSpaceIcon;
	m_nBottomSpaceText = nLeftSpaceText;
}

void CImgGlassButton::SetButtonType( BUTTON_TYPE nType )
{
	m_nBtnType = nType;
}

void CImgGlassButton::SetFontSize( REAL size )
{
	m_fFontSize = size;
}

void CImgGlassButton::SetFocusToParent( BOOL bSetFocus )
{
	m_bSetFocusToParent = bSetFocus;
}

void CImgGlassButton::SetFontStyle( FontStyle nFontStyle )
{
	m_nFontStyle = nFontStyle;
}


