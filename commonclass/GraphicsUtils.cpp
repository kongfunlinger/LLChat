#include "StdAfx.h"
#include "GraphicsUtils.h"

CString g_AppImagePath = _T("");
void InitPathStrings()
{
	CString strAppPath, sParams;
	::GetModuleFileName(NULL, strAppPath.GetBuffer(MAX_PATH), MAX_PATH);
	strAppPath.ReleaseBuffer();
	int iPos = -1;

	if ((iPos = strAppPath.ReverseFind(_T('\\'))) != -1)
	{
		strAppPath = strAppPath.Left(iPos + 1);
	}

	if (strAppPath.GetLength() > 0)
	{
		g_AppImagePath = strAppPath + _T("Images\\");
	}
}

Image* LoadImageInAppPath(CString strFileName)
{
	// append the image path 
	if (_T("") == g_AppImagePath){
		InitPathStrings();
	}
	strFileName = g_AppImagePath + strFileName;
	Image* pImage = Image::FromFile(strFileName.AllocSysString());
	if (pImage->GetLastStatus() != Ok)
	{
		delete pImage;
		pImage = NULL;
		//CString strInfo = L"";
		//strInfo.Format(L"The picture \"%s\" has not found,please re-install %s!",strFileName,TU::PRODUCT_NAME);
		//::MessageBox(NULL,strInfo,g_strCaption,MB_OK|MB_ICONWARNING);
		//		::ExitProcess(0);
	}
	return pImage;
}
Image* LoadImageInResource(UINT unResID)
{
	Image *pRetImg = NULL;
	HGLOBAL        hGlobal = NULL;
	HRSRC        hSource = NULL;
	LPVOID        lpVoid = NULL;
	int            nSize = 0;
	hSource = FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(unResID), _T("PNG"));
	if (hSource == NULL)
		return pRetImg;
	hGlobal = LoadResource(AfxGetResourceHandle(), hSource);
	if (hGlobal == NULL)
	{
		FreeResource(hGlobal);
		return pRetImg;
	}
	lpVoid = LockResource(hGlobal);
	if (lpVoid == NULL)
		goto Exit;

	nSize = (UINT)SizeofResource(AfxGetResourceHandle(), hSource);

	HGLOBAL hGlobal2 = GlobalAlloc(GMEM_MOVEABLE, nSize);
	if (hGlobal2 == NULL)
	{
		goto Exit;
	}

	void* pData = GlobalLock(hGlobal2);
	memcpy(pData, (void *)hGlobal, nSize);
	GlobalUnlock(hGlobal2);

	IStream* pStream = NULL;

	if (CreateStreamOnHGlobal(hGlobal2, TRUE, &pStream) == S_OK)
	{
		pRetImg = Image::FromStream(pStream, FALSE);
		pStream->Release();
	}
	FreeResource(hGlobal2);
Exit:
	UnlockResource(hGlobal);
	FreeResource(hGlobal);
	return pRetImg;
}
Font* CreateDefaultFont(int iFontSize, BOOL bBold, BOOL bItalic, BOOL bUnderline)
{
	LOGFONT lf;
	NONCLIENTMETRICS nmc;
	nmc.cbSize = sizeof(nmc);
	// get LOGFONT structure for the icon font
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &nmc, 0);

	lf = nmc.lfMessageFont;

	HDC hDC = GetDC(NULL);

	if (iFontSize != -1)
	{
		lf.lfHeight = -MulDiv(iFontSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	}

	lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	lf.lfItalic = bItalic ? TRUE : FALSE;
	lf.lfUnderline = bUnderline ? TRUE : FALSE;
	Font* pFont = new Font(hDC, &lf);

	::ReleaseDC(NULL, hDC);
	return pFont;
}

void DrawText(Graphics* g, CRect rect, LPCTSTR lpszText, LPCTSTR lpszFontName, REAL fFontSize, int iFontStyle, COLORREF cr, StringAlignment saH, StringAlignment saV, BOOL bDontChangeAlias, BOOL bIsDrawOutline, StringTrimming stringTrim)
{
	if (fFontSize > 11.0)
	{//解决大小字体上下对不齐问题
		rect.OffsetRect(-2, 0);
	}
	Font* pActualFont = NULL;
	if (lpszFontName)
	{
		//UnicodeString usFontFamily( lpszFontName );
		CString usFontFamily(lpszFontName);
		FontFamily fontFamily(usFontFamily.AllocSysString());
		pActualFont = new Font(&fontFamily, fFontSize, iFontStyle, UnitPoint);
		if (pActualFont->GetLastStatus() != Ok)
		{
			delete pActualFont;
			pActualFont = CreateDefaultFont((int)fFontSize, ((iFontStyle & FontStyleBold) == FontStyleBold),
				((iFontStyle & FontStyleItalic) == FontStyleItalic), ((iFontStyle & FontStyleUnderline) == FontStyleUnderline));
		}
	}
	else
	{
		pActualFont = CreateDefaultFont((int)fFontSize, ((iFontStyle & FontStyleBold) == FontStyleBold),
			((iFontStyle & FontStyleItalic) == FontStyleItalic), ((iFontStyle & FontStyleUnderline) == FontStyleUnderline));
	}

	RectF rectF((REAL)rect.left, (REAL)rect.top, (REAL)rect.Width(), (REAL)rect.Height());

	StringFormat stringFormat;
	stringFormat.SetAlignment(saH);
	stringFormat.SetLineAlignment(saV);
	stringFormat.SetTrimming(stringTrim);
	stringFormat.SetFormatFlags(StringFormatFlagsLineLimit);
	SolidBrush brush(Color(CLR2ARGB(cr)));

	if (!bDontChangeAlias)
	{
		if (fFontSize > 10 || iFontStyle == FontStyleBoldItalic || iFontStyle == FontStyleBold)
		{
			g->SetTextRenderingHint(TextRenderingHintAntiAlias);
		}
		else
		{
			g->SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
		}
	}

	//UnicodeString usText( lpszText );
	CString usText(lpszText);
	// Draw text shadow
	if (bIsDrawOutline)
	{
		SolidBrush brushShadow(Color(CLR2ARGB(COLOR_DLG_BUTTON_TEXT_OUTLINE)));
		RectF rectFShadow = rectF;
		rectFShadow.X = rectFShadow.X + 1;
		rectFShadow.Y = rectFShadow.Y + 1;
		g->DrawString(usText.AllocSysString(), -1, pActualFont, rectFShadow, &stringFormat, &brushShadow);
	}

	// draw real text
	g->DrawString(usText.AllocSysString(), -1, pActualFont, rectF, &stringFormat, &brush);

	/*
	// Draw text path
	if (bIsDrawOutline)
	{
	GraphicsPath pathText;
	FontFamily	fontFamily;
	pActualFont->GetFamily(&fontFamily);
	pathText.AddString(usText, -1, &fontFamily, pActualFont->GetStyle(), pActualFont->GetSize(), rectF, &stringFormat);
	Pen txtPen(Color( CLR2ARGB(COLOR_DLG_BUTTON_TEXT_OUTLINE) ) , 1.0);
	g->DrawPath(&txtPen, &pathText);
	}
	*/

	delete pActualFont;
}

void DrawText(Graphics* g, CRect rect, UINT uTextId, LPCTSTR lpszFontName, REAL fFontSize, int iFontStyle, COLORREF cr, StringAlignment saH, StringAlignment saV, BOOL bDontChangeAlias, BOOL bIsDrawOutline, StringTrimming stringTrim)
{
	CString sText;
	sText.LoadString(uTextId);
	DrawText(g, rect, sText, lpszFontName, fFontSize, iFontStyle, cr, saH, saV, bDontChangeAlias, bIsDrawOutline, stringTrim);
}

void DrawText(Graphics* g, CRect rect, LPCTSTR lpszText, CFontInfo fontInfo, StringTrimming stringTrim)
{
	DrawText(g, rect, lpszText, fontInfo.strFontName, fontInfo.fFontSize, fontInfo.nFontStyle, fontInfo.nFontCor, fontInfo.saH, fontInfo.saV, fontInfo.bDontChangeAlias, FALSE, stringTrim);
}

void DrawText(Graphics* g, CRect rect, UINT uTextId, CFontInfo fontInfo, StringTrimming stringTrim)
{
	DrawText(g, rect, uTextId, fontInfo.strFontName, fontInfo.fFontSize, fontInfo.nFontStyle, fontInfo.nFontCor, fontInfo.saH, fontInfo.saV, fontInfo.bDontChangeAlias, FALSE, stringTrim);

}



void DrawImageAlpha(Graphics* g, Image* pImg, CRect rect, float fAlpha)
{
	ImageAttributes ImgAttr;

	if (fAlpha != 1.0)
	{
		ColorMatrix ClrMatrix = {
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, fAlpha, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		ImgAttr.SetColorMatrix(&ClrMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	}
	// centerlize the painting rect so that image is painted in its original size
	int	imageHeight = pImg->GetHeight();
	int	imageWidth = pImg->GetWidth();
	if (rect.Width() > imageWidth && rect.Height() > imageHeight)
	{
		rect.left = rect.left + (rect.Width() - imageWidth) / 2;
		rect.top = rect.top + (rect.Height() - imageHeight) / 2;
		rect.right = rect.left + imageWidth;
		rect.bottom = rect.top + imageHeight;
	}
	RectF rectF((REAL)rect.left, (REAL)rect.top, (REAL)rect.Width(), (REAL)rect.Height());
	g->DrawImage(pImg, rectF, 0, 0, (REAL)pImg->GetWidth(), (REAL)pImg->GetHeight(), UnitPixel, &ImgAttr);
}

void FillSolidRect(Graphics* g, CRect rect, REAL radius, COLORREF cr, DWORD fCorners)
{
	SolidBrush brush(Color(CLR2ARGB(cr)));

	if (radius == 0 || fCorners == NULL)
	{
		// simple case with no rounded corners
		RectF rectF((REAL)rect.left, (REAL)rect.top, (REAL)rect.Width(), (REAL)rect.Height());
		g->FillRectangle(&brush, rectF);
	}
	else
	{
		GraphicsPath gp;
		_CreateRectPath(&gp, rect, radius, fCorners);
		g->FillPath(&brush, &gp);
	}
}
void FillSolidRect(Graphics* g, CRect rect, REAL radius, Color cr, DWORD fCorners)
{
	SolidBrush brush(cr);

	if (radius == 0 || fCorners == NULL)
	{
		// simple case with no rounded corners
		RectF rectF((REAL)rect.left, (REAL)rect.top, (REAL)rect.Width(), (REAL)rect.Height());
		g->FillRectangle(&brush, rectF);
	}
	else
	{
		GraphicsPath gp;
		_CreateRectPath(&gp, rect, radius, fCorners);
		g->FillPath(&brush, &gp);
	}
}

void FillSolidRect(Graphics* g, CRect rect, REAL radius, const Brush* pBrush, DWORD fCorners)
{
	if (radius == 0 || fCorners == NULL)
	{
		// simple case with no rounded corners
		RectF rectF((REAL)rect.left, (REAL)rect.top, (REAL)rect.Width(), (REAL)rect.Height());
		g->FillRectangle(pBrush, rectF);
	}
	else
	{
		GraphicsPath gp;
		_CreateRectPath(&gp, rect, radius, fCorners);
		g->FillPath(pBrush, &gp);
	}
}

void FillSolidRect(Graphics* g, RectF* rectF, REAL radius, const Brush* pBrush, DWORD fCorners)
{
	if (radius == 0 || fCorners == NULL)
	{
		// simple case with no rounded corners
		g->FillRectangle(pBrush, *rectF);
	}
	else
	{
		CRect rect;
		rect.left = (int)rectF->X;
		rect.right = (int)rectF->X + (int)rectF->Width;
		rect.top = (int)rectF->Y;
		rect.bottom = (int)rectF->Y + (int)rectF->Height;
		GraphicsPath gp;
		_CreateRectPath(&gp, rect, radius, fCorners);
		g->FillPath(pBrush, &gp);
	}
}

void _CreateRectPath(GraphicsPath *gp, CRect rect, REAL radius, DWORD dwCorners)
{
	ATLASSERT(gp);

	RectF rectF((REAL)rect.left, (REAL)rect.top, (REAL)rect.Width(), (REAL)rect.Height());
	RectF rWork;

	// these are used for the arc corners
	rWork.Width = radius;
	rWork.Height = radius;

	if ((dwCorners & CORNER_TOP_LEFT) == CORNER_TOP_LEFT)
	{
		// do round corner
		rWork.X = rectF.X;
		rWork.Y = rectF.Y;
		gp->AddArc(rWork, 180.0f, 90.0f);
	}
	else
	{
		// do square corner
		gp->AddLine(rectF.X, rectF.Y, rectF.X + (REAL)1.0, rectF.Y);
	}

	if ((dwCorners & CORNER_TOP_RIGHT) == CORNER_TOP_RIGHT)
	{
		// do round corner
		rWork.X = rectF.X + rectF.Width - radius;
		rWork.Y = rectF.Y;
		gp->AddArc(rWork, 270.0f, 90.0f);
	}
	else
	{
		// do square corner
		rWork.X = rectF.X + rectF.Width;
		gp->AddLine(rWork.X, rectF.Y, rWork.X, rectF.Y + (REAL)1.0);
	}

	if ((dwCorners & CORNER_BOTTOM_RIGHT) == CORNER_BOTTOM_RIGHT)
	{
		// do round corner
		rWork.X = rectF.X + rectF.Width - radius;
		rWork.Y = rectF.Y + rectF.Height - radius;
		gp->AddArc(rWork, 0.0f, 90.0f);
	}
	else
	{
		// do square corner
		rWork.X = rectF.X + rectF.Width;
		rWork.Y = rectF.Y + rectF.Height;
		gp->AddLine(rWork.X, rWork.Y, rWork.X - (REAL)1.0, rWork.Y);
	}

	if ((dwCorners & CORNER_BOTTOM_LEFT) == CORNER_BOTTOM_LEFT)
	{
		// do round corner
		rWork.X = rectF.X;
		rWork.Y = rectF.Y + rectF.Height - radius;
		gp->AddArc(rWork, 90.0f, 90.0f);
	}
	else
	{
		// do square corner
		rWork.X = rectF.X;
		rWork.Y = rectF.Y + rectF.Height;
		gp->AddLine(rWork.X, rWork.Y, rWork.X, rWork.Y - (REAL)1.0);
	}

	gp->CloseFigure();
}