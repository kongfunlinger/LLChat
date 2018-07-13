#pragma once


// CStaticText

class CStaticText : public CStatic
{
	DECLARE_DYNAMIC(CStaticText)

public:
	CStaticText();
	virtual ~CStaticText();
	void SetStaticImage(CString StrImageName);
	void SetFontSize(REAL size);
	void SetFontColor(Color clr);
	void SetFontStyle(UINT nStyle){ m_fontStyle = nStyle; };
	void SetFontType(CString strType){ m_fontType = strType; };
	void SetIsHandCur(BOOL bIsHandCur);
	void SetFillBK(BOOL bIsFill){ m_bIsFill = bIsFill; };
	void SetIsBranchShow(BOOL bIsBranch);//是否分行显示
	void SetStringAlig(StringAlignment saH, StringAlignment saV);
	void SetBKCor(COLORREF cor);
	void SetDrawShadow(BOOL bIsDraw, COLORREF corShadow);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

private:
	BOOL m_bIsFill;
	CString m_fontType;
	UINT m_fontStyle;
	Image *m_pImage;
	REAL m_sizeOfFont;
	Color m_colorOfFont;
	HCURSOR m_hCur;
	BOOL m_bIsHandCur;
	BOOL m_bIsBranch;
	StringAlignment m_nSaH;
	StringAlignment m_nSaV;
	CString m_strString;
	COLORREF m_corBK;
	BOOL m_bIsDrawShadow;
	COLORREF m_corShadow;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void SetWindowText(LPCTSTR lpszString);
	void SetWindowText(UINT unResID);
protected:
	virtual void PreSubclassWindow();
};


