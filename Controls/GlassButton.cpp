// GlassButton.cpp : implementation file
//

#include "stdafx.h"
#include "GlassButton.h"
#include "../commonclass/BufferMemDC.h"
#include "../commonclass/GraphicsUtils.h"
// CGlassButton

IMPLEMENT_DYNAMIC(CGlassButton, CButton)

CGlassButton::CGlassButton()
{
	m_clrButton = COLOR_DLG_BUTTON_NORMAL_ENABLED;
	m_bUseImage = FALSE;
	m_pImage = NULL;
	m_bOverControl = FALSE;
	m_bOverSplit = FALSE;
	m_clrBKGrnd = COLOR_APP_PAGE_BACKGROUND;
	m_uiButtonType = BUTTON_TYPE_NORMAL;
	m_bIsTrackingMouse = FALSE;
	m_bIsInitSize = FALSE;
	m_hRgn = 0;
	m_reTextSize = 0.0;
	m_bIsSplitBtn = FALSE;
	m_bIsPressed = FALSE;
	m_bIsSplitPressed = FALSE;
	m_bIsRectangle = FALSE;
}

CGlassButton::~CGlassButton()
{
	if ( m_pImage )
	{
		delete m_pImage;
	}
	DeleteObject(m_hRgn);
}

BEGIN_MESSAGE_MAP(CGlassButton, CButton)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CGlassButton::SetImageName(CString strName)
{
	m_bUseImage = TRUE;
	if ( m_pImage )
	{
		delete m_pImage;
	}
	m_pImage = LoadImageInAppPath( strName );
}

BOOL CGlassButton::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void CGlassButton::SetButtonType(UINT	uiButtonType)
{
	m_uiButtonType = uiButtonType;
}

void CGlassButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC*	pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rectClient;
	GetClientRect(rectClient);
	/*m_hRgn = CreateRoundRectRgn(rectClient.left,rectClient.top,rectClient.right,rectClient.bottom,20,20);
	if (m_hRgn)
	{
		SetWindowRgn(m_hRgn,TRUE);
	}*/
	CBufferMemDC memDC(pDC, &rectClient, RGB(255,0,0), FALSE);	
	Graphics g(memDC);

	// Getthe right button font attributes
	CString		fontFamilyName;
	REAL		fontSize;
	INT			fontStytle;
	COLORREF	fontColor;

	switch (m_uiButtonType)
	{
	case BUTTON_TYPE_NORMAL:
		{
			fontFamilyName	= DLG_BUTTON_ACTION_FONT_NAME;
			fontSize		= 10.0;
			fontStytle		= DLG_BUTTON_ACTION_FONT_STYTLE;
			fontColor		= DLG_BUTTON_ACTION_FONT_COLOR;

		}
		break;
	case BUTTON_TYPE_ACTION:
		{
			fontFamilyName	= DLG_BUTTON_ACTION_FONT_NAME;
			fontSize		= DLG_BUTTON_ACTION_FONT_SIZE;
			fontStytle		= DLG_BUTTON_ACTION_FONT_STYTLE;
			fontColor		= DLG_BUTTON_ACTION_FONT_COLOR;
		}
		break;
	case BUTTON_TYPE_NON_DISTRACTION:
		{
			fontFamilyName	= DLG_BUTTON_NON_DISTRACTION_FONT_NAME;
			fontSize		= DLG_BUTTON_NON_DISTRACTION_FONT_SIZE;
			fontStytle		= DLG_BUTTON_NON_DISTRACTION_FONT_STYTLE;
			fontColor		= DLG_BUTTON_NON_DISTRACTION_FONT_COLOR;
		}
		break;
	case BUTTON_TYPE_RECT:
		{
			fontFamilyName	= DLG_BUTTON_ACTION_FONT_NAME;
			fontSize		= DLG_BUTTON_ACTION_FONT_SIZE;
			fontStytle		= DLG_BUTTON_ACTION_FONT_STYTLE;
			fontColor		= DLG_BUTTON_ACTION_FONT_COLOR;
		}
	     break;
	case BUTTON_TYPE_SQURE:
	{
		fontFamilyName = DLG_BUTTON_ACTION_FONT_NAME;
		fontSize = 12.0;
		fontStytle = DLG_BUTTON_ACTION_FONT_STYTLE;
		fontColor = DLG_BUTTON_ACTION_FONT_COLOR;
	}
	break;
	case BUTTON_TYPE_NON_SQURE:
	{
		fontFamilyName = DLG_BUTTON_ACTION_FONT_NAME;
		fontSize = 12.0;
		fontStytle = DLG_BUTTON_ACTION_FONT_STYTLE;
		fontColor = DLG_BUTTON_ACTION_FONT_COLOR;
	}
	break;
	default:
		{
			fontFamilyName	= DLG_BUTTON_NORMAL_FONT_NAME;
			fontSize		= DLG_BUTTON_NORMAL_FONT_SIZE;
			fontStytle		= DLG_BUTTON_NORMAL_FONT_STYTLE;
			fontColor		= DLG_BUTTON_NORMAL_FONT_COLOR;
		}
		break;
	}

	if(m_reTextSize >= 1.0)
		fontSize = m_reTextSize;
	// initialize the button size according to its type 
	// if it hasn't been done before
	if (!m_bIsInitSize)
	{
		CString		strBtnText;
		this->GetWindowText(strBtnText);
		CRect	rectClientOld, rectNewBtnBoundary;
		RectF	oldClientRect((REAL)rectClientOld.left, (REAL)rectClientOld.top, (REAL)rectClientOld.Width(), (REAL)rectClientOld.Height());
		RectF	newTextRect;
		GetClientRect(rectClientOld);
		//Get the bounding rect of based on the font used.
		Font	fontBtnText(fontFamilyName, fontSize, fontStytle);
		g.MeasureString(strBtnText, strBtnText.GetLength(), &fontBtnText, oldClientRect, &newTextRect);

		// now set the button boundary rect (in client rect)
		rectNewBtnBoundary.SetRect(0, 0, (int)newTextRect.Width+2*(int)newTextRect.Height, (int)newTextRect.Height*2+5);
		ClientToScreen(rectNewBtnBoundary);
		GetParent()->ScreenToClient(rectNewBtnBoundary);
		MoveWindow(rectNewBtnBoundary);
		m_bIsInitSize = TRUE;
		return;
	}

	TextRenderingHint trOriginal = g.GetTextRenderingHint();
	SmoothingMode smOriginal = g.GetSmoothingMode();
	g.SetSmoothingMode(SmoothingModeHighQuality);
	g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);

	m_bIsDisabled = (lpDIS->itemState & ODS_DISABLED);
	m_bIsPressed = (lpDIS->itemState & ODS_SELECTED);

	if(m_bIsSplitBtn)
	{
		if(m_bIsPressed)
		{
			if(m_bOverControl)
			{
				m_bIsSplitPressed = FALSE;
			}
			else if(m_bOverSplit)
			{
				m_bIsPressed = FALSE;
				m_bIsSplitPressed = TRUE;
			}
		}
		else
		{
			m_bIsSplitPressed = FALSE;
		}
	}
	CRect rect;
	GetClientRect(rect);

	CRect rectImage = rect;
	if ( m_bUseImage )
	{
		int iScaleAmnt = m_pImage->GetWidth() / 10;	
		rect.left += iScaleAmnt*2;
		rect.top += iScaleAmnt;
		rect.right -= iScaleAmnt*2;
		rect.bottom -=  iScaleAmnt;		
	}

	int iRadius = 25;
	if ( rect.Height() < 60 || rect.Width() < 60 )
	{
		iRadius = 20;
	}
	if ( m_bIsDisabled )
	{
		fontColor = COLOR_DLG_BUTTON_NORMAL_DISABLED;
	}

	//DrawEmbossedGlassButton(&g, rect, (REAL)iRadius, fontColor, CORNERS_ALL, m_bIsPressed, (m_bOverControl||bIsFocused), m_bOverControl);
	DrawGlassButton(&g);

	CString strText;
	GetWindowText(strText);

	if (m_bIsPressed)
	{
		rect.OffsetRect(1,1);
	}
	if(m_bOverControl)
	{
		rect.OffsetRect(-1,-1);
	}
	if ( m_bUseImage && m_pImage )
	{
		rect.left = m_pImage->GetWidth();
		rect.right = rectImage.Width() - m_pImage->GetWidth();
	}
	
	// Draw button text, only draw outline when text color is non-distraction (Black)
	rect.OffsetRect(0, (int)(0.05*rect.Height()));
	if(m_bIsSplitBtn)
	{
		rect.right -= int(rect.Height() * 0.70);
	}
	DrawText(&g, rect, strText, fontFamilyName, fontSize, fontStytle, fontColor, StringAlignmentCenter, StringAlignmentCenter, 0, (fontColor!=DLG_BUTTON_NON_DISTRACTION_FONT_COLOR));
	
	if ( m_bUseImage && m_pImage )
	{
		g.DrawImage(m_pImage, 0, (int)(rectImage.Height()/2) - (m_pImage->GetHeight()/2), m_pImage->GetWidth(), m_pImage->GetHeight() );
	}

	g.SetSmoothingMode(smOriginal);
	g.SetTextRenderingHint(trOriginal);
}

void CGlassButton::OnMouseLeave()
{
	if (m_bIsTrackingMouse)
	{
		m_bIsTrackingMouse = FALSE;
		/*
		// ask the parent window to paint so that
		// this button, which has transparent background
		// can be fully painted.
		CRect rectWindowRect;
		GetWindowRect(rectWindowRect);
		GetParent()->ScreenToClient(rectWindowRect);
		GetParent()->InvalidateRect(rectWindowRect);
		*/
		Invalidate();
	}
	m_bOverControl = FALSE;
	m_bOverSplit = FALSE;
}

void CGlassButton::OnMouseMove(UINT /*nFlags*/, CPoint /*point*/)
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

	if(m_bIsSplitBtn)
	{
		CRect rect;
		GetClientRect(rect);
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);
		CRect crtT(rect);
		crtT.right -= crtT.Height() - 6;
		CRect crtR(rect);
		crtR.left = crtT.right;
		if(crtT.PtInRect(point))
		{
			if(!m_bOverControl)
			{
				m_bOverControl = TRUE;
				m_bOverSplit = FALSE;
				Invalidate();
			}
		}
		else if(crtR.PtInRect(point))
		{
			if(!m_bOverSplit)
			{
				m_bOverSplit = TRUE;
				m_bOverControl = FALSE;
				Invalidate();
			}
		}
	}
	else
	{
		if(!m_bOverControl)
		{
			m_bOverControl = TRUE;
			/*
			// ask the parent window to paint so that
			// this button, which has transparent background
			// can be fully painted.
			CRect rectWindowRect;
			GetWindowRect(rectWindowRect);
			GetParent()->ScreenToClient(rectWindowRect);
			GetParent()->InvalidateRect(rectWindowRect);
			*/
			Invalidate();
		}
	}
    //CButton::OnMouseMove(nFlags, point);
}

void CGlassButton::OnLButtonUp(UINT /*nFlags*/, CPoint point)
{
	CRect crtClient;
	GetClientRect(crtClient);
	GetParent()->SetFocus();
	if(!PtInRect(crtClient,point)) return;
	if(m_bIsSplitBtn)
	{
		CRect rect;
		GetClientRect(rect);
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);
		CRect crtT(rect);
		crtT.right -= crtT.Height() - 6;
		CRect crtR(rect);
		crtR.left = crtT.right;
		if(crtT.PtInRect(point))
		{
		}
		else if(crtR.PtInRect(point))
		{
			::SendMessage(GetParent()->m_hWnd,m_unMsgSplit,0,0);
			return;
		}
	}
	::SendMessage(GetParent()->m_hWnd,WM_COMMAND,
		MAKELPARAM(GetDlgCtrlID(),BN_CLICKED),LPARAM(m_hWnd));
   // GetParent()->SetFocus();
}

void CGlassButton::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    CButton::OnLButtonDown(nFlags, point);
}

void CGlassButton::DrawEmbossedGlassButton( Graphics* g, CRect rect, REAL radius, COLORREF /*crBg*/, DWORD fCorners, BOOL bPressed, BOOL /*bFocused*/, BOOL bHover )
{
	CRect rc = rect;
	rc.left += 3;
	rc.top += 3;
	rc.bottom -=3;
	rc.right -=3;


	if (bPressed)
	{
		rc.OffsetRect(1,1);
	}

	Color colorDark, colorLight, colorOutline;
	switch (m_uiButtonType)
	{
	case BUTTON_TYPE_ACTION:
		colorDark = CLRA2ARGB(COLOR_DLG_BUTTON_ACTION_ENABLED, 0xff000000);
		colorLight = CLRA2ARGB(COLOR_DLG_BUTTON_ACTION_ENABLED_LIGHT, 0xff000000);
		colorOutline = CLRA2ARGB(COLOR_DLG_BUTTON_ACTION_ENABLED, 0xff000000);
		break;
	case BUTTON_TYPE_NON_DISTRACTION:
		colorDark = CLRA2ARGB(COLOR_DLG_BUTTON_NON_DISTRACTION_ENABLED, 0xff000000);
		colorLight = CLRA2ARGB(COLOR_DLG_BUTTON_NON_DISTRACTION_ENABLED_LIGHT, 0xff000000);
		colorOutline = CLRA2ARGB(COLOR_DLG_BUTTON_NON_DISTRACTION_ENABLED, 0xff000000);
		break;
	case BUTTON_TYPE_NORMAL:
		colorDark = CLRA2ARGB(COLOR_DLG_BUTTON_NORMAL_ENABLED, 0xff000000);
		colorLight = CLRA2ARGB(COLOR_DLG_BUTTON_NORMAL_ENABLED_LIGHT, 0xff000000);
		colorOutline = CLRA2ARGB(COLOR_DLG_BUTTON_NORMAL_ENABLED, 0xff000000);
		break;
	}

	// top highlight
	CRect rectTop = rc;
	rectTop.bottom = (int)(rc.Height() * (bHover ? 0.6f : 0.5f)); + 1;
	RectF rectFTop((REAL)rectTop.left, (REAL)rectTop.top, (REAL)rectTop.Width(), (REAL)rectTop.Height());
	LinearGradientBrush brushTop(rectFTop, colorLight, colorDark, LinearGradientModeVertical);
	REAL factors1[4] = {0.0f, 1.0f, 1.0f};
	REAL positions1[4] = {0.0f, 0.8f, 1.0f};
	brushTop.SetBlend(factors1, positions1, 3);
	FillSolidRect(g, rectTop, radius, &brushTop, (fCorners & CORNERS_TOPS) );

	// bottom highlight
	CRect rectBottom = rc;
	rectBottom.top = rectTop.bottom - 1;
	RectF rectFBottom((REAL)rectBottom.left, (REAL)rectBottom.top, (REAL)rectBottom.Width(), (REAL)rectBottom.Height());
	LinearGradientBrush brushBottom( rectFBottom, colorDark, colorLight, LinearGradientModeVertical );
	REAL factors2[4] = {0.0f, 0.0f, 0.5f};
	REAL positions2[4] = {0.0f, 0.7f, 1.0f};
	brushBottom.SetBlend(factors2, positions2, 3);
	FillSolidRect(g, rectBottom, radius, &brushBottom, (fCorners & CORNERS_BOTTOMS) );

	// middle section
	CRect rectMiddle = rc;
	rectMiddle.top = rectTop.bottom - 2;
	rectMiddle.bottom = rectBottom.top + 2;
	SolidBrush brushSolid(colorDark);
	RectF rectFMiddle((REAL)rectMiddle.left, (REAL)rectMiddle.top, (REAL)rectMiddle.Width(), (REAL)rectMiddle.Height());
	g->FillRectangle(&brushSolid, rectFMiddle);

	Pen pen(colorDark, 1.5f);
	GraphicsPath gp;
	_CreateRectPath(&gp, rc, radius, CORNERS_ALL);
	g->DrawPath(&pen, &gp);
}

void CGlassButton::DrawGlassButton(Graphics* g)
{
	CRect crtClient;
	GetClientRect(crtClient);
	crtClient.left += 3;
	crtClient.top += 3;
	crtClient.bottom -=3;
	crtClient.right -=3;

	CRect rectMiddle(crtClient);

	REAL radius =(REAL)rectMiddle.Height();
	if (m_bIsRectangle)
	{
		radius = 0.0f;
	}
	if (m_bIsPressed)
	{
//		rectMiddle.OffsetRect(1,1);
	}
	if(m_bOverControl)
	{
//		rectMiddle.OffsetRect(-1,-1);
	}
	Color colorDark, colorLight, colorOutline,colorUpLine,colorDownLine;
	switch (m_uiButtonType)
	{
	case BUTTON_TYPE_ACTION:
		colorDark = CLRA2ARGB(COLOR_DLG_BUTTON_ACTION_ENABLED, 0xff000000);
		colorLight = CLRA2ARGB(COLOR_DLG_BUTTON_ACTION_ENABLED_LIGHT, 0xff000000);
		colorOutline = CLRA2ARGB(COLOR_DLG_BUTTON_OUTLINE, 0xff000000);
		colorUpLine = CLRA2ARGB(COLOR_DLG_BUTTON_ACTION_UPLINE,0xff000000);
		colorDownLine = CLRA2ARGB(COLOR_DLG_BUTTON_ACTION_DOWNLINE,0xff000000);
		break;
	case BUTTON_TYPE_RECT:
		colorDark = CLRA2ARGB(COLOR_DLG_BUTTON_ACTION_ENABLED, 0xff000000);
		colorLight = CLRA2ARGB(COLOR_DLG_BUTTON_ACTION_ENABLED_LIGHT, 0xff000000);
		colorOutline = CLRA2ARGB(COLOR_DLG_BUTTON_OUTLINE, 0xff000000);
		colorUpLine = CLRA2ARGB(COLOR_DLG_BUTTON_ACTION_UPLINE,0xff000000);
		colorDownLine = CLRA2ARGB(COLOR_DLG_BUTTON_ACTION_DOWNLINE,0xff000000);
		radius = 0.0f;
		break;
	case BUTTON_TYPE_ACTION_EX:
		colorDark = CLRA2ARGB(COLOR_DLG_BUTTON_ACTION_ENABLED, 0xff000000);
		colorLight = CLRA2ARGB(COLOR_DLG_BUTTON_ACTION_ENABLED_LIGHT, 0xff000000);
		colorOutline = CLRA2ARGB(RGB(0,0,94), 0xff000000);
		colorUpLine = CLRA2ARGB(COLOR_DLG_BUTTON_ACTION_UPLINE,0xff000000);
		colorDownLine = CLRA2ARGB(COLOR_DLG_BUTTON_ACTION_DOWNLINE,0xff000000);
		break;
	case BUTTON_TYPE_NON_DISTRACTION:
		colorDark = CLRA2ARGB(COLOR_DLG_BUTTON_NON_DISTRACTION_ENABLED, 0xff000000);
		colorLight = CLRA2ARGB(COLOR_DLG_BUTTON_NON_DISTRACTION_ENABLED_LIGHT, 0xff000000);
		colorOutline = CLRA2ARGB(COLOR_DLG_BUTTON_OUTLINE, 0xff000000);
		colorUpLine = CLRA2ARGB(COLOR_DLG_BUTTON_NON_DISTRACTION_UPLINE,0xff000000);
		colorDownLine = CLRA2ARGB(COLOR_DLG_BUTTON_NON_DISTRACTION_DOWNLINE,0xff000000);
		break;
	case BUTTON_TYPE_NORMAL:
		colorDark = CLRA2ARGB(COLOR_DLG_BUTTON_NORMAL_ENABLED, 0xff000000);
		colorLight = CLRA2ARGB(COLOR_DLG_BUTTON_NORMAL_ENABLED_LIGHT, 0xff000000);
		colorOutline = CLRA2ARGB(COLOR_DLG_BUTTON_OUTLINE, 0xff000000);
		colorUpLine = CLRA2ARGB(COLOR_DLG_BUTTON_NORMAL_UPLINE,0xff000000);
		colorDownLine = CLRA2ARGB(COLOR_DLG_BUTTON_NORMAL_DOWNLINE,0xff000000);
		break;
	case BUTTON_TYPE_SQURE:
		colorDark = CLRA2ARGB(RGB(0, 128, 255), 0xff000000);
		colorLight = CLRA2ARGB(RGB(0, 105, 210), 0xff000000);
		colorOutline = CLRA2ARGB(RGB(0, 105, 210), 0xff000000);
		colorUpLine = CLRA2ARGB(RGB(0, 105, 210), 0xff000000);
		colorDownLine = CLRA2ARGB(RGB(0, 105, 210), 0xff000000);
		radius = 0.0f;
		break;
	case BUTTON_TYPE_NON_SQURE:
		colorDark = CLRA2ARGB(RGB(102, 102, 102), 0xff000000);
		colorLight = CLRA2ARGB(RGB(102, 102, 102), 0xff000000);
		colorOutline = CLRA2ARGB(RGB(102, 102, 102), 0xff000000);
		colorUpLine = CLRA2ARGB(RGB(102, 102, 102), 0xff000000);
		colorDownLine = CLRA2ARGB(RGB(102, 102, 102), 0xff000000);
		break;
	}

	if(m_bIsPressed || m_bIsSplitPressed)
	{
		Color clrTemp;
		clrTemp = colorDownLine;
		colorDownLine = colorUpLine;
		colorUpLine = clrTemp;
	}

	RectF rectFMiddle((REAL)rectMiddle.left, (REAL)rectMiddle.top, (REAL)rectMiddle.Width(), (REAL)rectMiddle.Height());
	SolidBrush BrushCenter(colorDark);
	if (m_bIsRectangle)
	{
		FillSolidRect(g, rectMiddle, radius, &BrushCenter, NULL );
	} 
	else
	{
			FillSolidRect(g, rectMiddle, radius, &BrushCenter, CORNERS_ALL );
	}
	GraphicsPath gp;
	Pen pen(colorOutline, 0.1f);
	if (m_bIsRectangle)
	{
           _CreateRectPath(&gp, rectMiddle, radius, NULL);
	} 
	else
	{
			_CreateRectPath(&gp, rectMiddle, radius, CORNERS_ALL);
	}
	g->DrawPath(&pen, &gp);

	for(INT i=0;i<2;i++)
	{
		rectMiddle.DeflateRect(1,1);
		rectFMiddle.X += 0.0f;
		rectFMiddle.Y += 0.0f;
		rectFMiddle.Width -= 0.0f;
		rectFMiddle.Height -= 0.0f;
		radius -= 0.1f;

		Pen penUp(colorUpLine, 0.1f);
		Pen penDown(colorDownLine, 0.1f);

		RectF rWork;
		rWork.Width		= radius;
		rWork.Height	= radius;

		rWork.X			= rectFMiddle.X;
		rWork.Y			= rectFMiddle.Y;
		if(m_bIsSplitBtn && m_bIsSplitPressed)
		{
			if (m_bIsRectangle)
			{
				
			} 
			else
			{
				g->DrawArc(&penUp,rWork,180.0f,90.0f);
				g->DrawArc(&penDown,rWork,90.0f,90.0f);
			}
			
		}
		else
		{

			if (m_bIsRectangle)
			{
			} 
			else
			{
				g->DrawArc(&penUp,rWork,180.0f,90.0f);
				g->DrawArc(&penDown,rWork,90.0f,90.0f);
			}
		}

		rWork.X			= rectFMiddle.X + (rectFMiddle.Width - radius);
		if(m_bIsSplitBtn && m_bIsPressed)
		{
			if (m_bIsRectangle)
			{
				g->DrawLine(&penUp,rectFMiddle.X,rectFMiddle.Y,rectFMiddle.X + rectFMiddle.Width,rectFMiddle.Y);
				g->DrawLine(&penUp,rectFMiddle.X,rectFMiddle.Y ,rectFMiddle.X ,rectFMiddle.Y + rectFMiddle.Height);
				g->DrawLine(&penDown,rectFMiddle.X,rectFMiddle.Y + rectFMiddle.Height,rectFMiddle.X + rectFMiddle.Width,rectFMiddle.Y + rectFMiddle.Height);
				g->DrawLine(&penDown,rectFMiddle.X + rectFMiddle.Width,rectFMiddle.Y ,rectFMiddle.X + rectFMiddle.Width ,rectFMiddle.Y + rectFMiddle.Height);
			} 
			else
			{
				g->DrawArc(&penDown,rWork,270.0f,90.0f);
				g->DrawArc(&penUp,rWork,0.0f,90.0f);
			}
			
		}
		else
		{
			if (m_bIsRectangle)
			{
				g->DrawLine(&penUp,rectFMiddle.X,rectFMiddle.Y,rectFMiddle.X + rectFMiddle.Width,rectFMiddle.Y);
				g->DrawLine(&penUp,rectFMiddle.X,rectFMiddle.Y ,rectFMiddle.X ,rectFMiddle.Y + rectFMiddle.Height);
				g->DrawLine(&penDown,rectFMiddle.X,rectFMiddle.Y + rectFMiddle.Height,rectFMiddle.X + rectFMiddle.Width,rectFMiddle.Y + rectFMiddle.Height);
				g->DrawLine(&penDown,rectFMiddle.X + rectFMiddle.Width,rectFMiddle.Y ,rectFMiddle.X + rectFMiddle.Width ,rectFMiddle.Y + rectFMiddle.Height);
			} 
			else
			{
				g->DrawArc(&penUp,rWork,270.0f,90.0f);
				g->DrawArc(&penDown,rWork,0.0f,90.0f);
			}
			
		}
		if(m_bIsSplitBtn && m_bIsPressed)
		{
			if (m_bIsRectangle)
			{
				g->DrawLine(&penUp,rectFMiddle.X,rectFMiddle.Y,rectFMiddle.X + rectFMiddle.Width,rectFMiddle.Y);
				g->DrawLine(&penUp,rectFMiddle.X,rectFMiddle.Y ,rectFMiddle.X ,rectFMiddle.Y + rectFMiddle.Height);
				g->DrawLine(&penDown,rectFMiddle.X,rectFMiddle.Y + rectFMiddle.Height,rectFMiddle.X + rectFMiddle.Width,rectFMiddle.Y + rectFMiddle.Height);
				g->DrawLine(&penDown,rectFMiddle.X + rectFMiddle.Width,rectFMiddle.Y ,rectFMiddle.X + rectFMiddle.Width ,rectFMiddle.Y + rectFMiddle.Height);
			} 
			else
			{
				g->DrawLine(&penUp,rectFMiddle.X + (radius/2),rectFMiddle.Y,rWork.X + (radius/2),rWork.Y);
				g->DrawLine(&penDown,rectFMiddle.X + (radius/2),rectFMiddle.Y+ radius,rWork.X + (radius/2),rWork.Y + radius);
				g->DrawLine(&penDown,rectFMiddle.X + rectFMiddle.Width - rectFMiddle.Height + 1,rectFMiddle.Y,rWork.X + (radius/2),rWork.Y);
				g->DrawLine(&penUp,rectFMiddle.X + rectFMiddle.Width - rectFMiddle.Height + 1,rectFMiddle.Y+ radius,rWork.X +(radius/2),rWork.Y + radius);
			}
			

		}
		else if(m_bIsSplitBtn && m_bIsSplitPressed)
		{
			if (m_bIsRectangle)
			{
				g->DrawLine(&penUp,rectFMiddle.X,rectFMiddle.Y,rectFMiddle.X + rectFMiddle.Width,rectFMiddle.Y);
				g->DrawLine(&penUp,rectFMiddle.X,rectFMiddle.Y ,rectFMiddle.X ,rectFMiddle.Y + rectFMiddle.Height);
				g->DrawLine(&penDown,rectFMiddle.X,rectFMiddle.Y + rectFMiddle.Height,rectFMiddle.X + rectFMiddle.Width,rectFMiddle.Y + rectFMiddle.Height);
				g->DrawLine(&penDown,rectFMiddle.X + rectFMiddle.Width,rectFMiddle.Y ,rectFMiddle.X + rectFMiddle.Width ,rectFMiddle.Y + rectFMiddle.Height);
			} 
			else
			{
				g->DrawLine(&penDown,rectFMiddle.X + (radius/2),rectFMiddle.Y,rWork.X + (radius/2),rWork.Y);
				g->DrawLine(&penUp,rectFMiddle.X + (radius/2),rectFMiddle.Y+ radius,rWork.X + (radius/2),rWork.Y + radius);
				g->DrawLine(&penUp,rectFMiddle.X + rectFMiddle.Width - rectFMiddle.Height + 1,rectFMiddle.Y,rWork.X + (radius/2),rWork.Y);
				g->DrawLine(&penDown,rectFMiddle.X + rectFMiddle.Width - rectFMiddle.Height + 1,rectFMiddle.Y+ radius,rWork.X +(radius/2),rWork.Y + radius);
			}
		
		}
		else
		{
			if (m_bIsRectangle)
			{
				g->DrawLine(&penUp,rectFMiddle.X,rectFMiddle.Y,rectFMiddle.X + rectFMiddle.Width,rectFMiddle.Y);
				g->DrawLine(&penUp,rectFMiddle.X,rectFMiddle.Y ,rectFMiddle.X ,rectFMiddle.Y + rectFMiddle.Height);
				g->DrawLine(&penDown,rectFMiddle.X,rectFMiddle.Y + rectFMiddle.Height,rectFMiddle.X + rectFMiddle.Width,rectFMiddle.Y + rectFMiddle.Height);
				g->DrawLine(&penDown,rectFMiddle.X + rectFMiddle.Width,rectFMiddle.Y ,rectFMiddle.X + rectFMiddle.Width ,rectFMiddle.Y + rectFMiddle.Height);


			} 
			else
			{
				g->DrawLine(&penUp,rectFMiddle.X + (radius/2),rectFMiddle.Y,rWork.X + (radius/2),rWork.Y);
				g->DrawLine(&penDown,rectFMiddle.X + (radius/2),rectFMiddle.Y+ radius,rWork.X +(radius/2),rWork.Y + radius);
			}
			
		}

	}
	if(m_bIsSplitBtn)
	{
		SmoothingMode oldSmooth = g->GetSmoothingMode();
		PixelOffsetMode oldPoxel = g->GetPixelOffsetMode();
		g->SetSmoothingMode(SmoothingModeNone);
		g->SetPixelOffsetMode(PixelOffsetModeInvalid);
		g->DrawLine(&pen,rectMiddle.right - rectMiddle.Height(),rectMiddle.top - 1,
			rectMiddle.right - rectMiddle.Height(),rectMiddle.bottom + 1);
		Pen penUp(colorUpLine, 2.0f);
		if(m_bIsPressed ) penUp.SetColor(colorDownLine);
		g->DrawLine(&penUp,rectMiddle.right - rectMiddle.Height() + 2,rectMiddle.top,
			rectMiddle.right - rectMiddle.Height() + 2,rectMiddle.bottom);
		g->SetSmoothingMode(SmoothingModeHighQuality);
		GraphicsPath gpT;
		INT nW = 14;
		INT nH = 13;
		INT nXOffSet = 0;
		INT nYOffSet = 0;
		if(m_bOverSplit)
		{
			nXOffSet = -1;
			nYOffSet = -1;
		}
		if(m_bIsSplitPressed)
		{
			nXOffSet = 1;
			nYOffSet = 1;
		}
		Point data[] = {
			Point(rectMiddle.right - rectMiddle.Height() + (rectMiddle.Height() - nW)/2 + nXOffSet,rectMiddle.top + (rectMiddle.Height() - nH) / 2 + nYOffSet),
			Point(rectMiddle.right - (rectMiddle.Height() - nW) / 2 + nXOffSet,rectMiddle.top + (rectMiddle.Height() - nH) / 2 + nYOffSet),
			Point(rectMiddle.right - rectMiddle.Height() / 2 + nXOffSet,rectMiddle.top + (rectMiddle.Height() - nH) / 2 + nH + nYOffSet)
		};
		gpT.AddPolygon(data,3);
		SolidBrush sb(CLR2ARGB(RGB(255,255,255)));
		g->FillPath(&sb,&gpT);
		g->DrawPath(&pen,&gpT);
		g->SetPixelOffsetMode(oldPoxel);
		g->SetSmoothingMode(oldSmooth);
	}

}

void CGlassButton::SetButtonAutoSize(BOOL bIsAutoSize /* = TRUE */)
{
	m_bIsInitSize = !bIsAutoSize;
}

void CGlassButton::SetSplitBtn( BOOL bIsSplit,UINT unMsg)
{
	m_bIsSplitBtn = bIsSplit;
	m_unMsgSplit = unMsg;
}

void CGlassButton::SetButtonShape( BOOL IsRectangle )
{
     m_bIsRectangle = IsRectangle;
}
