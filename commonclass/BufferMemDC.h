#pragma once

// essentially provides GDI double buffering
class CBufferMemDC : public CDC 
{
private:       
    CBitmap    m_bitmap;        // Offscreen bitmap
    CBitmap*   m_oldBitmap;     // bitmap originally found in CMemDC
    CDC*       m_pDC;           // Saves CDC passed in constructor
    CRect      m_rect;          // Rectangle of drawing area.
public:

	CBufferMemDC (CDC* pDC, const CRect* pRect, COLORREF clrBk, BOOL bFill = TRUE) : CDC()
	{
		// Some initialization
		m_pDC = pDC;
		m_oldBitmap = NULL;

		// Get the rectangle to draw
		m_rect = *pRect;

		// Create a Memory DC
		CreateCompatibleDC(pDC);
		pDC->LPtoDP(&m_rect);

		ASSERT(pDC->m_hDC != NULL);
		m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
		m_oldBitmap = SelectObject(&m_bitmap);

		SetMapMode(pDC->GetMapMode());

		SetWindowExt(pDC->GetWindowExt());
		SetViewportExt(pDC->GetViewportExt());

		pDC->DPtoLP(&m_rect);
		SetWindowOrg(m_rect.left, m_rect.top);

		if ( bFill )
		{
			// Fill background 
			FillSolidRect(m_rect, clrBk);
		}
		else
		{
			BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), pDC, m_rect.left, m_rect.top, SRCCOPY);
		}
	}

	CBufferMemDC (CDC* pDC, const CRect* pRect, CBitmap* pBMP) : CDC()
	{
		// Some initialization
		m_pDC = pDC;
		m_oldBitmap = NULL;

		// Get the rectangle to draw
		m_rect = *pRect;

		// Create a Memory DC
		CreateCompatibleDC(pDC);
		pDC->LPtoDP(&m_rect);

		//m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
		m_oldBitmap = SelectObject(pBMP);

		SetMapMode(pDC->GetMapMode());

		SetWindowExt(pDC->GetWindowExt());
		SetViewportExt(pDC->GetViewportExt());

		pDC->DPtoLP(&m_rect);
		SetWindowOrg(m_rect.left, m_rect.top);

	}

	~CBufferMemDC ()      
	{          
		// Copy the offscreen bitmap onto the screen.
		m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(),  m_rect.Height(), this, m_rect.left, m_rect.top, SRCCOPY);            

		//Swap back the original bitmap.
		SelectObject(m_oldBitmap);    
		DeleteObject(&m_bitmap);
	}
};