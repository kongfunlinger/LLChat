#pragma once


class CNcControl_Base
{
protected:
	CWnd *m_pParentWnd;
	CRect	m_crtWnd;
	UINT		m_unResID;
	BOOL  m_bIsShowWindow;
	CString m_strWindowText;
	CFontInfo m_fontInfo;
	BOOL m_bIsHover;
	COLORREF m_corBK;
	BOOL m_bIsFillBK;
	BOOL m_bIsAsBackground;
public:
	CNcControl_Base();
	~CNcControl_Base();
	enum BTN_STATE
	{
		BTN_STATE_NORMAL = 0,
		BTN_STATE_HOVER,
		BTN_STATE_PRESS
	};
	virtual BOOL Create(UINT unResID,CRect crtWnd,CWnd *pParent);
	virtual void OnNcPaint(Graphics *g)=0;
	virtual void OnNcPaint();
	virtual BOOL OnNcLButtonDown(WPARAM /*wParam*/,LPARAM /*lParam*/){return FALSE;};
	virtual void OnNcMouseMove(WPARAM /*wParam*/,LPARAM /*lParam*/){};
	virtual void OnNcLButtonUp(UINT /*nHitTest*/, CPoint /*point*/){};
	virtual BOOL OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/){return FALSE;};
	virtual BOOL IsInControl(CPoint point);
	virtual BOOL IsWindowShow();
	virtual BOOL IsHover();
	virtual void MoveWindow(CRect crt,BOOL bIsRefresh = FALSE);
	virtual void MoveWindow(INT nl, INT nT, INT nR, INT nB, BOOL bIsRefresh = FALSE);
	virtual void ShowWindow(BOOL bIsShow);
	virtual void SetWindowText(CString strText);
	virtual void SetWindowText(UINT unResID);
	virtual void SetFontInfo(CFontInfo fontInfo);
	virtual CFontInfo GetFontInfo();
	virtual void SetBKCor(COLORREF cor);
	virtual void SetFillBK(BOOL bIsFill);
	virtual UINT GetCtrlID();
	virtual void SetAsBackground(BOOL bIsAsBackground);
	virtual BOOL GetAsBackground();
};
class CNcControl_LinkButton : public CNcControl_Base
{
private:
	BOOL m_bIsPressed;
	HCURSOR m_hCursor;
public:
	CNcControl_LinkButton();
	~CNcControl_LinkButton();
	virtual void OnNcPaint(Graphics *g);
	virtual BOOL OnNcLButtonDown(WPARAM wParam,LPARAM lParam);
	virtual void OnNcLButtonUp(UINT nHitTest, CPoint point);
	virtual BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};
class CNcControl_Static : public CNcControl_Base
{
public:
	CNcControl_Static();
	~CNcControl_Static();
	virtual void OnNcPaint(Graphics *g);
	virtual BOOL OnNcLButtonDown(WPARAM wParam,LPARAM lParam);
};
class CNcControl_Picture : public CNcControl_Base
{
public:
	CNcControl_Picture();
	~CNcControl_Picture();
	virtual void OnNcPaint(Graphics *g);
	void SetImageID(UINT unImage);
private:
	Image *m_pImage;
};
class CNcControl_ToolBtn : public CNcControl_Base
{
private:
	Image		*m_pImage;
	Image		*m_pImageNor;
	Image		*m_pImageSelected;
	Image		*m_pImageHover;
	BOOL		m_bIsSelected;
	BOOL		m_bIsPressed;
public:

	CNcControl_ToolBtn();
	~CNcControl_ToolBtn();
	virtual void OnNcPaint(Graphics *g);
	virtual BOOL OnNcLButtonDown(WPARAM wParam,LPARAM lParam);
	virtual void OnNcLButtonUp(UINT nHitTest, CPoint point);
	virtual void OnNcMouseMove(WPARAM wParam,LPARAM lParam);
	void SetImage(Image *pImage);
	void SetSelected(BOOL bIsSelected);
	BOOL IsSelected();
	void DrawToolBtn( Graphics *g,BTN_STATE nState );
	void DrawToolBtn( CDC *pDC,BTN_STATE nState );
	void SetNorImage(Image *pImage);
	void SetSelectedImage(Image *pImage);
	void SetHoverImage(Image *pImage);
};

class CNcControl_ImageBtn : public CNcControl_Base
{
private:
	Image *m_pImage;
	BOOL m_bIsPressed;
	HCURSOR m_hCursor;
public:
	CNcControl_ImageBtn();
	~CNcControl_ImageBtn();
	virtual void OnNcPaint(Graphics *g);
	void SetImageID(UINT unImage);
	virtual BOOL OnNcLButtonDown(WPARAM wParam,LPARAM lParam);
	virtual void OnNcLButtonUp(UINT nHitTest, CPoint point);
	virtual BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};