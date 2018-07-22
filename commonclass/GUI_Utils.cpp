#include "StdAfx.h"
#include "GUI_Utils.h"
#include "GraphicsUtils.h"

static CFont* CreatePageLabelFont()
{
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
	lf.lfHeight = -MulDiv((int)PAGE_LABEL_FONT_SIZE, GetDeviceCaps(::AfxGetApp()->m_pMainWnd->GetDC()->m_hDC, LOGPIXELSY), 72);   // request a 18-pixel-height font
	lf.lfWeight = FW_BOLD;
	_tcscpy_s(lf.lfFaceName, PAGE_LABEL_FONT_NAME);        // request a face name "Arial"
	CFont* pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	return pFont;
}

static CFont* CreatePageDescriptionFont()
{
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
	lf.lfHeight = -MulDiv((int)PAGE_DESCRIPTION_FONT_SIZE, GetDeviceCaps(::AfxGetApp()->m_pMainWnd->GetDC()->m_hDC, LOGPIXELSY), 72);   // request a 18-pixel-height font
	lf.lfWeight = FW_NORMAL;
	_tcscpy_s(lf.lfFaceName, PAGE_DESCRIPTION_FONT_NAME);        // request a face name "Arial"
	CFont* pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	return pFont;
}

CGUI_Utils::CGUI_Utils(void)
{
	// Create all drawing components
	m_pFontPageLabel = NULL;
	m_pFontPageDescription = NULL;
	m_brushDialogPageBackground.CreateSolidBrush(COLOR_CENTER_BOX);	// initialize Dialog background brush
	m_brushViewPageBackground.CreateSolidBrush(COLOR_SCANPROCESS_BACKGROUND);  //init View background brush

}
CFont* CGUI_Utils::GetPageLabelFont(){
	if( NULL ==	m_pFontPageLabel ){
		m_pFontPageLabel = CreatePageLabelFont();
	}
	return m_pFontPageLabel;

}
CFont* CGUI_Utils::GetPageDescriptionFont(){
	if( NULL ==	m_pFontPageDescription ){
		m_pFontPageDescription = CreatePageDescriptionFont();
	}
	return m_pFontPageDescription;

}

CGUI_Utils::~CGUI_Utils(void)
{
	if (m_pFontPageLabel)
	{
		delete m_pFontPageLabel;
	}
	if (m_pFontPageDescription)
	{
		delete m_pFontPageDescription;
	}
}

CGUI_Utils* CGUI_Utils::GetInstance()
{
	static CGUI_Utils instance;
	return &instance;
}
