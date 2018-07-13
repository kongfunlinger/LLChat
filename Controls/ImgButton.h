#pragma once


// CImgButton

class CImgButton : public CButton
{
	DECLARE_DYNAMIC(CImgButton)

public:
	CImgButton();
	virtual ~CImgButton();

	void	SetImage(CString strImageName);
	void	SetImage(UINT unResID);
	void	SetFillBK(BOOL bIsFill);

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
private:
	BOOL		m_bIsFillBK;
	Image *		m_pImage;
	COLORREF	m_clrBKGrnd;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


