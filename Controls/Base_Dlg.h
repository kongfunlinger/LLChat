#pragma once
#include "../commonclass/BufferMemDC.h"
#include "../Controls/SkinDialog.h"
// CBase_Dlg dialog

class CBase_Dlg : public CDialogEx
{
public:
	CBase_Dlg(UINT nIDTemplate,CWnd* pParent = NULL);   // standard constructor
	virtual ~CBase_Dlg();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	static void DrawTitleRect(CRect rc,CBufferMemDC& memDC,BOOL bIsTop = TRUE);
	// Dialog Data
protected:
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void LoadMainFrameSkin(SKIN_RESOURCE &skinRes, CFontInfo &fontInfo);
};
