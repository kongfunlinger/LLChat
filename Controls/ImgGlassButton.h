#pragma once
#include "afxwin.h"

enum BUTTON_TYPE
{
	BUTTON_TYPE_CUSTOM = 0,
	BUTTON_TYPE_ACTION,
	BUTTON_TYPE_NON_DISTRACTION,
	BUTTON_TYPE_NEW_NON_DISTRACTION
};

class CImgGlassButton :
	public CButton
{
public:
	CImgGlassButton(void);
	~CImgGlassButton(void);


	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void DrawImgGlassButton(Graphics* g);
	void SetImageName(UINT unResID);
	void SetGradient(COLORREF clrTop,COLORREF clrBottom);
	void DrawGradientBackground(GraphicsPath *pGP,CRect &rc, Color clrGradientTop, Color clrGradientBottom, Graphics* g, REAL radius, DWORD fCorners );
	void SetOutLineColor(COLORREF clrOutLine);
	void SetFontColor(COLORREF clrFontColor);
	void SetLeftSpace(INT nLeftSpaceIcon,INT nLeftSpaceText);
	void SetButtonType(BUTTON_TYPE nType);
	void SetFontSize(REAL size);
	void SetFocusToParent( BOOL bSetFocus );
	void SetFontStyle( FontStyle nFontStyle );
	
private:
	BUTTON_TYPE m_nBtnType;
	BOOL m_bOverControl;
	BOOL m_bIsPressed;
	COLORREF m_clrButton;
	COLORREF m_clrBKGrnd;
	COLORREF m_clrFont;
	COLORREF m_clrOutLine;
	COLORREF m_clrFill;
	COLORREF m_clrGradientTop;
	COLORREF m_clrGradientBottom;
	INT m_nLeftSpaceIcon;
	INT m_nBottomSpaceText;
	REAL m_fFontSize;
	BOOL m_bSetFocusToParent;

	Image* m_pImage;

	UINT	m_uiButtonType;
	BOOL		m_bIsTrackingMouse;
	HRGN m_hRgn;
	FontStyle m_nFontStyle;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
