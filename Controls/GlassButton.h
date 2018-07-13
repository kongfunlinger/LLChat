#pragma once


// CGlassButton

class CGlassButton : public CButton
{
	DECLARE_DYNAMIC(CGlassButton)

public:
	CGlassButton();
	virtual ~CGlassButton();
	void SetButtonColor(Color clrDark,Color clrUpline,Color clrDownline) { m_clrButton = clrDark;m_clrUpline=clrUpline;m_clrDownline = clrDownline;};
	void SetImageName(CString strName);
	void SetBKColor(COLORREF clr){ m_clrBKGrnd = clr; };

	typedef enum {
		BUTTON_TYPE_NORMAL = 0,			// normal button, used for non-critical actions: Blue
		BUTTON_TYPE_ACTION,				// action button, used for prompting users to take actions: Green
		BUTTON_TYPE_ACTION_EX,				// action button, used for prompting users to take actions: Green
		BUTTON_TYPE_NON_DISTRACTION,		// non-distraction button, which we don't want user to click usually: Grey
		 BUTTON_TYPE_DEFINE_COLOR_SELF// use this type after call SetButtonColor()
	} GlassButtonType;

protected:
	DECLARE_MESSAGE_MAP()
	void DrawEmbossedGlassButton( Graphics* g, CRect rect, REAL radius, COLORREF crBg, DWORD fCorners, BOOL bPressed, BOOL bFocused , BOOL bHover);

	void DrawGlassButton(Graphics* g);
	// owner of the button should call these functions to initialize button
public:
	void SetButtonType (UINT btnType = BUTTON_TYPE_NORMAL);	// set the type of button
	//void InitializeButton ();	// make initialization of the button settings, especially its size
	void SetButtonAutoSize(BOOL bIsAutoSize = TRUE);
	void SetTextSize(REAL reSize){m_reTextSize = reSize;};
	void SetSplitBtn(BOOL bIsSplit,UINT unMsg);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

private:
	BOOL m_bOverControl;
	BOOL m_bOverSplit;
	BOOL m_bIsPressed;
	BOOL m_bIsSplitPressed;
	BOOL m_bIsDisabled;
	BOOL m_bIsInitSize;		// if the button window size has been calculated and initialized
	Color m_clrButton;
	Color m_clrUpline;
	Color m_clrDownline;
	COLORREF m_clrBKGrnd;

	BOOL m_bUseImage;
	Image* m_pImage;
	Font* m_pFont;

	UINT	m_uiButtonType;
	BOOL		m_bIsTrackingMouse;
	HRGN m_hRgn;
	REAL m_reTextSize;
	BOOL m_bIsSplitBtn;
	UINT m_unMsgSplit;
};


