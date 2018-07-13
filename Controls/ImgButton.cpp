// ImgBtton.cpp : implementation file
//

#include "stdafx.h"
#include "ImgButton.h"
#include "../commonclass/BufferMemDC.h"

// CImgBtton

IMPLEMENT_DYNAMIC(CImgButton, CButton)

CImgButton::CImgButton()
{
	m_bIsFillBK = TRUE;
	m_clrBKGrnd = RGB(255, 255, 255);
	m_pImage = NULL;
}

CImgButton::~CImgButton()
{
	SAFE_DELETE(m_pImage);
}


void CImgButton::SetImage(CString strImageName)
{
	SAFE_DELETE(m_pImage);
	m_pImage = LoadImageInAppPath(strImageName);
}

void CImgButton::SetImage(UINT unResID)
{
	SAFE_DELETE(m_pImage);
	m_pImage = LoadImageInResource(unResID);
}

void CImgButton::SetFillBK(BOOL bIsFill)
{
	m_bIsFillBK = bIsFill;
}

void CImgButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CRect rectClient;
	GetClientRect(rectClient);
	CBufferMemDC memDC(CDC::FromHandle(lpDrawItemStruct->hDC), &rectClient, m_clrBKGrnd, m_bIsFillBK);
	
	Graphics g(memDC);
	
	if (m_pImage)
	{
		INT nImageW = g_dpi.ScaleX(m_pImage->GetWidth());
		INT nImageH = g_dpi.ScaleY(m_pImage->GetHeight());
		
			g.DrawImage(m_pImage,
			(REAL)(rectClient.left),
			(REAL)(rectClient.top),
			(REAL)nImageW, (REAL)nImageH);
	}
}

BOOL CImgButton::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;//CButton::OnEraseBkgnd(pDC);
}

BEGIN_MESSAGE_MAP(CImgButton, CButton)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CImgBtton message handlers


