#pragma once
class CGUI_Utils
{
public:
	CBrush		m_brushDialogPageBackground;		// Dialog page background
	CBrush		m_brushViewPageBackground;			//the view page background
	CFont*		GetPageLabelFont();			// PageLabel font
	CFont*		GetPageDescriptionFont();
	static CGUI_Utils * GetInstance();
protected:
	CFont*		m_pFontPageLabel;			// PageLabel font
	CFont*		m_pFontPageDescription;		// description font
	CGUI_Utils(void);
	~CGUI_Utils(void);
};
