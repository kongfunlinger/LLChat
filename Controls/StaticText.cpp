// StaticText.cpp : implementation file
//

#include "stdafx.h"
#include "StaticText.h"
#include "../commonclass/BufferMemDC.h"

// CStaticText

IMPLEMENT_DYNAMIC(CStaticText, CStatic)

CStaticText::CStaticText()
{
	m_pImage = NULL;
	m_colorOfFont = Color(0, 0, 0);
	m_sizeOfFont = 10;
	m_fontType = _T("Arial");
	m_fontStyle = FontStyleRegular;
	m_hCur = LoadCursor(NULL, IDC_HAND);
	m_bIsHandCur = FALSE;
	m_bIsFill = FALSE;
	m_bIsBranch = FALSE;
	m_nSaH = StringAlignmentNear;
	m_nSaV = StringAlignmentCenter;
	m_strString = _T("");
	m_corBK = RGB(255, 255, 255);
	m_bIsDrawShadow = FALSE;
	m_corShadow = RGB(127, 127, 127);
}

CStaticText::~CStaticText()
{
	SAFE_DELETE(m_pImage);
}


void CStaticText::SetStaticImage(CString StrImageName)
{
	if (m_pImage)
	{
		delete m_pImage;
		m_pImage = NULL;
	}
	m_pImage = LoadImageInAppPath(StrImageName);
}

void CStaticText::SetFontSize(REAL size)
{
	m_sizeOfFont = size;
}

void CStaticText::SetFontColor(Color clr)
{
	m_colorOfFont = clr;
}

void CStaticText::SetIsHandCur(BOOL bIsHandCur)
{
	m_bIsHandCur = bIsHandCur;
}

void CStaticText::SetIsBranchShow(BOOL bIsBranch)
{
	m_bIsBranch = bIsBranch;
}

void CStaticText::SetStringAlig(StringAlignment saH, StringAlignment saV)
{
	m_nSaH = saH;
	m_nSaV = saV;
}

void CStaticText::SetBKCor(COLORREF cor)
{
	m_corBK = cor;
}

void CStaticText::SetDrawShadow(BOOL bIsDraw, COLORREF corShadow)
{
	m_bIsDrawShadow = bIsDraw;
	m_corShadow = corShadow;
}

void CStaticText::OnPaint()
{
	CPaintDC dcPaint(this); // device context for painting
	CRect rectClient;
	GetClientRect(rectClient);

	CBufferMemDC memDC(&dcPaint, &rectClient, m_corBK, m_bIsFill);
	Graphics graphics(memDC);
	SmoothingMode smOriginal = graphics.GetSmoothingMode();
	TextRenderingHint trOriginal = graphics.GetTextRenderingHint();
	graphics.SetSmoothingMode(SmoothingModeHighQuality);
	graphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);

	RectF rectClientF((REAL)rectClient.left, (REAL)rectClient.top, (REAL)rectClient.Width(), (REAL)rectClient.Height());
	SolidBrush brush(NULL_BRUSH);
	graphics.FillRectangle(&brush, rectClientF);

	CRect	rectText = rectClient;
	CRect	rectImage = rectClient;
	//draw the static image
	if (m_pImage)
	{
		rectImage.right = rectImage.left + 60;
		rectText.left = rectImage.right;
		graphics.DrawImage(m_pImage,
			(REAL)(rectImage.CenterPoint().x - m_pImage->GetWidth() / 2),
			(REAL)(rectImage.CenterPoint().y - m_pImage->GetHeight() / 2),
			(REAL)m_pImage->GetWidth(), (REAL)m_pImage->GetHeight());
	}

	//draw button text
	CString szText = m_strString;
	//	GetWindowText(szText);
	COLORREF fontColor = m_colorOfFont.ToCOLORREF();
	if (m_bIsBranch)
	{
		INT nPos = szText.Find('\n');
		if (nPos >= 0)
		{
			CString strTop = szText.Left(nPos);
			CString strBottom = szText.Right(szText.GetLength() - nPos - 1);
			CRect crtTop(rectText);
			crtTop.bottom = crtTop.top + (rectText.Height() / 2);
			DrawText(&graphics, crtTop, strTop, m_fontType, m_sizeOfFont, m_fontStyle, fontColor, StringAlignmentNear, StringAlignmentCenter, 1, 0);
			CRect crtBottom(rectText);
			crtBottom.top = crtBottom.bottom - (rectText.Height() / 2);
			DrawText(&graphics, crtBottom, strBottom, m_fontType, 10, FontStyleRegular, fontColor, StringAlignmentNear, StringAlignmentCenter, 1, 0);
		}
	}
	else
	{
		if (m_bIsDrawShadow)
		{
			rectText.OffsetRect(0, 1);
			DrawText(&graphics, rectText, szText, m_fontType, m_sizeOfFont, m_fontStyle, m_corShadow, m_nSaH, m_nSaV, 1, 0);
			rectText.OffsetRect(0, -1);
		}
		DrawText(&graphics, rectText, szText, m_fontType, m_sizeOfFont, m_fontStyle, fontColor, m_nSaH, m_nSaV, 1, 0);
	}
	graphics.SetSmoothingMode(smOriginal);
	graphics.SetTextRenderingHint(trOriginal);
}

void CStaticText::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rectClient;
	GetClientRect(rectClient);

	if (m_bIsHandCur&& m_hCur && PtInRect(rectClient, point))
	{
		::SetCursor(m_hCur);
	}

	CStatic::OnMouseMove(nFlags, point);
}

void CStaticText::SetWindowText(LPCTSTR lpszString)
{
	m_strString = lpszString;
	Invalidate();
}

void CStaticText::SetWindowText(UINT unResID)
{
	m_strString.LoadString(unResID);
	Invalidate();
}

void CStaticText::PreSubclassWindow()
{
	GetWindowText(m_strString);
	CStatic::PreSubclassWindow();
}

BEGIN_MESSAGE_MAP(CStaticText, CStatic)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CStaticText message handlers


