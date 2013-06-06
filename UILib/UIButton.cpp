
#pragma once
#include "UILib.h"
#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////////////
//
CButtonUI::CButtonUI() : m_uButtonState(0), 
m_dwHotTextColor(0),
m_dwPushedTextColor(0),
m_dwFocusedTextColor(0),
m_dwHotBkColor(0)
{
	m_uTextStyle = DT_SINGLELINE | DT_VCENTER | DT_CENTER;
	//m_dwBorderColor = RGB(140,140,140);
	m_dwFocusBorderColor = 0xFF8C8C8C;
}

CButtonUI::~CButtonUI(void)
{
}

LPCTSTR CButtonUI::GetClass() const
{
	return _T("ButtonUI");
}

LPVOID CButtonUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcscmp(pstrName, _T("ButtonUI")) == 0) 
		return static_cast<CButtonUI*>(this);

	return CLabelUI::GetInterface(pstrName);
}

UINT CButtonUI::GetControlFlags() const
{
	return UIFLAG_TABSTOP | (IsEnabled() ? UIFLAG_SETCURSOR : 0);
}

bool CButtonUI::Activate()
{
	if (!CControlUI::Activate())
		return false;

	if (m_pManager != NULL)
		m_pManager->SendNotify(this, _T("click"));
	return true;
}

void CButtonUI::SetEnabled(bool bEnable)
{
	CControlUI::SetEnabled(bEnable);

	if (!IsEnabled())
	{
		m_uButtonState = 0;
	}
}

void CButtonUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	CLabelUI::SetAttribute(pstrName, pstrValue);
}

void CButtonUI::Event(TEventUI& event)
{
	if (!IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND)
	{
		if (m_pParent != NULL)
			m_pParent->Event(event);
		else 
			CLabelUI::Event(event);
		return;
	}
	if (event.Type == UIEVENT_KEYDOWN)
	{
		if (event.chKey == VK_SPACE || event.chKey == VK_RETURN)
		{
			Activate();
			return;
		}
	}
	if (event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK)
	{
		if (::PtInRect(&m_rcItem, event.ptMouse) && IsEnabled())
		{
			m_uButtonState |= UISTATE_PUSHED | UISTATE_CAPTURED;
			Invalidate();
		}
	}
	if (event.Type == UIEVENT_MOUSEMOVE)
	{
		if ((m_uButtonState & UISTATE_CAPTURED) != 0)
		{
			if (::PtInRect(&m_rcItem, event.ptMouse))
				m_uButtonState |= UISTATE_PUSHED;
			else
				m_uButtonState &= ~UISTATE_PUSHED;
			Invalidate();
		}
	}
	if (event.Type == UIEVENT_BUTTONUP)
	{
		if ((m_uButtonState & UISTATE_CAPTURED) != 0)
		{
			if (::PtInRect(&m_rcItem, event.ptMouse))
				Activate();
			m_uButtonState &= ~(UISTATE_PUSHED | UISTATE_CAPTURED);
			Invalidate();
		}
	}
	if (event.Type == UIEVENT_MOUSEENTER)
	{
		if (::PtInRect(&m_rcItem, event.ptMouse) && IsEnabled())
		{
			m_uButtonState |= UISTATE_HOT;
			Invalidate();
		}
	}
	if (event.Type == UIEVENT_MOUSELEAVE)
	{
		m_uButtonState &= ~UISTATE_HOT;
		Invalidate();
	}

	CLabelUI::Event(event);
}

void CButtonUI::SetHotBkColor(DWORD dwColor)
{
	m_dwHotBkColor = dwColor;
	Invalidate();
}

DWORD CButtonUI::GetHotBkColor() const
{
	return m_dwHotBkColor;
}

void CButtonUI::SetHotTextColor(DWORD dwColor)
{
	m_dwHotTextColor = dwColor;
	Invalidate();
}

DWORD CButtonUI::GetHotTextColor() const
{
	return m_dwHotTextColor;
}

void CButtonUI::SetPushedTextColor(DWORD dwColor)
{
	m_dwPushedTextColor = dwColor;
	Invalidate();
}

DWORD CButtonUI::GetPushedTextColor() const
{
	return m_dwPushedTextColor;
}

void CButtonUI::SetFocusedTextColor(DWORD dwColor)
{
	m_dwFocusedTextColor = dwColor;
	Invalidate();
}

DWORD CButtonUI::GetFocusedTextColor() const
{
	return m_dwFocusedTextColor;
}

LPCTSTR CButtonUI::GetNormalImage()
{
	return m_sNormalImage;
}

void CButtonUI::SetNormalImage(LPCTSTR pStrImage)
{
	m_sNormalImage = pStrImage;
	Invalidate();
}

LPCTSTR CButtonUI::GetHotImage()
{
	return m_sHotImage;
}

void CButtonUI::SetHotImage(LPCTSTR pStrImage)
{
	m_sHotImage = pStrImage;
	Invalidate();
}

LPCTSTR CButtonUI::GetPushedImage()
{
	return m_sPushedImage;
}

void CButtonUI::SetPushedImage(LPCTSTR pStrImage)
{
	m_sPushedImage = pStrImage;
	Invalidate();
}

LPCTSTR CButtonUI::GetFocusedImage()
{
	return m_sFocusedImage;
}

void CButtonUI::SetFocusedImage(LPCTSTR pStrImage)
{
	m_sFocusedImage = pStrImage;
	Invalidate();
}

LPCTSTR CButtonUI::GetDisabledImage()
{
	return m_sDisabledImage;
}

void CButtonUI::SetDisabledImage(LPCTSTR pStrImage)
{
	m_sDisabledImage = pStrImage;
	Invalidate();
}

LPCTSTR CButtonUI::GetForeImage()
{
	return m_sForeImage;
}


void CButtonUI::SetForeImage( LPCTSTR pStrImage )
{
	m_sForeImage = pStrImage;
	Invalidate();
}

LPCTSTR CButtonUI::GetHotForeImage()
{
	return m_sHotForeImage;
}

void CButtonUI::SetHotForeImage( LPCTSTR pStrImage )
{
	m_sHotForeImage = pStrImage;
	Invalidate();
}

SIZE CButtonUI::EstimateSize(SIZE /*szAvailable*/)
{
	//return CSize(0, m_pManager->GetFontInfo(GetFont())->tm.tmHeight + 8);

	//return CSize(0, 0);
	SIZE sz = { 0, 12 + m_pManager->GetFontInfo(GetFont())->tm.tmHeight + 8 };

	if (m_pManager != NULL)
	{
		RECT rcText = { 0, 0, 9999, 20 };
		int nLinks = 0;
		CDefaultRenderEngineUI::DrawHtmlText(m_pManager->GetPaintDC(), m_pManager, rcText, m_sText, m_dwTextColor, NULL, nLinks, DT_SINGLELINE | DT_CALCRECT);
		sz.cx = rcText.right - rcText.left;
	}
	sz.cx += (m_rcTextPadding.right - m_rcTextPadding.left) * 2;
	sz.cy += (m_rcTextPadding.bottom - m_rcTextPadding.top) * 2;
	return sz;
}

void CButtonUI::PaintText(HDC hDC)
{
	// ½¹µã
	if (IsFocused())
		m_uButtonState |= UISTATE_FOCUSED;
	else 
		m_uButtonState &= ~UISTATE_FOCUSED;

	// ½ûÓÃ
	if (!IsEnabled())
		m_uButtonState |= UISTATE_DISABLED;
	else
		m_uButtonState &= ~UISTATE_DISABLED;

	if (m_dwTextColor == 0)
		m_dwTextColor = m_pManager->GetDefaultFontColor();
	if (m_dwDisabledTextColor == 0)
		m_dwDisabledTextColor = m_pManager->GetDefaultDisabledColor();

	if (m_sText.IsEmpty())
		return;
	
	int nLinks = lengthof(m_rcLinks);
	
	RECT rc = m_rcItem;
	rc.left += m_rcTextPadding.left;
	rc.right -= m_rcTextPadding.right;
	rc.top += m_rcTextPadding.top;
	rc.bottom -= m_rcTextPadding.bottom;

	DWORD clrColor = IsEnabled() ? m_dwTextColor : m_dwDisabledTextColor;

	if ((m_uButtonState & UISTATE_PUSHED) != 0)
	{
		rc.top += 1;
		rc.left += 1;
		rc.right += 1;
		rc.bottom += 1;
		if (GetPushedTextColor() != 0 )
		{
			clrColor = GetPushedTextColor();
		}
	}
	else if ( (m_uButtonState & UISTATE_HOT) != 0 && GetHotTextColor() != 0 )
		clrColor = GetHotTextColor();
	else if ( (m_uButtonState & UISTATE_FOCUSED) != 0 && GetFocusedTextColor() != 0 )
		clrColor = GetFocusedTextColor();

	if (m_bShowHtml)
		CDefaultRenderEngineUI::DrawHtmlText(hDC, m_pManager, rc, m_sText, clrColor, m_rcLinks, nLinks, m_uTextStyle);
	else
		CDefaultRenderEngineUI::DrawText(hDC, m_pManager, rc, m_sText, clrColor, m_iFont, m_uTextStyle);
}

void CButtonUI::PaintStatusImage(HDC hDC)
{
	if (IsFocused())
		m_uButtonState |= UISTATE_FOCUSED;
	else
		m_uButtonState &= ~UISTATE_FOCUSED;

	if (!IsEnabled())
		m_uButtonState |= UISTATE_DISABLED;
	else
		m_uButtonState &= ~UISTATE_DISABLED;

	if ((m_uButtonState & UISTATE_DISABLED) != 0)
	{
		if (!m_sDisabledImage.IsEmpty())
		{
			if (!DrawImage(hDC, (LPCTSTR)m_sDisabledImage))
				m_sDisabledImage.Empty();
			else
				goto Label_ForeImage;
		}
	}
	else if ((m_uButtonState & UISTATE_PUSHED) != 0)
	{
		if (!m_sPushedImage.IsEmpty()) 
		{
			if (!DrawImage(hDC, (LPCTSTR)m_sPushedImage))
			{
				m_sPushedImage.Empty();
			}
			if (!m_sPushedForeImage.IsEmpty())
			{
				if (!DrawImage(hDC, (LPCTSTR)m_sPushedForeImage))
					m_sPushedForeImage.Empty();
				return;
			}
			else 
				goto Label_ForeImage;
		}
	}
	else if ((m_uButtonState & UISTATE_HOT) != 0)
	{
		if (!m_sHotImage.IsEmpty())
		{
			if (!DrawImage(hDC, (LPCTSTR)m_sHotImage))
			{
				m_sHotImage.Empty();
			}
			if (!m_sHotForeImage.IsEmpty()) 
			{
				if (!DrawImage(hDC, (LPCTSTR)m_sHotForeImage))
					m_sHotForeImage.Empty();
				return;
			}
			else 
				goto Label_ForeImage;
		}
		else if (m_dwHotBkColor != 0) 
		{
			CRenderEngine::DrawColor(hDC, m_rcPaint, m_dwHotBkColor);
			return;
		}
	}
	else if ((m_uButtonState & UISTATE_FOCUSED) != 0) 
	{
		if (!m_sFocusedImage.IsEmpty()) 
		{
			if (!DrawImage(hDC, (LPCTSTR)m_sFocusedImage))
				m_sFocusedImage.Empty();
			else 
				goto Label_ForeImage;
		}
		else
		{
			//CDefaultRenderEngineUI::DoPaintFrame(hDC, m_pManager, m_rcItem, m_dwFocusBorderColor, m_dwFocusBorderColor, 0, UIFRAME_ROUND);
			//::InflateRect(&m_rcItem, -1, -1);
		}
	}

	if (!m_sNormalImage.IsEmpty()) 
	{
		if (!DrawImage(hDC, (LPCTSTR)m_sNormalImage))
			m_sNormalImage.Empty();
		else 
			goto Label_ForeImage;
	}

	if (!m_sForeImage.IsEmpty())
		goto Label_ForeImage;

	return;

Label_ForeImage:
	if (!m_sForeImage.IsEmpty())
	{
		if (!DrawImage(hDC, (LPCTSTR)m_sForeImage))
			m_sForeImage.Empty();
	}
}



/////////////////////////////////////////////////////////////////////////////////////
//
//

COptionUI::COptionUI() : m_cxWidth(0), m_uButtonState(0), m_uStyle(DT_LEFT), m_bSelected(false)
{
}

LPCTSTR COptionUI::GetClass() const
{
	return _T("OptionUI");
}

UINT COptionUI::GetControlFlags() const
{
	return UIFLAG_TABSTOP;
}

bool COptionUI::Activate()
{
	if (!CControlUI::Activate())
		return false;
	SetCheck(true);
	return true;
}


bool COptionUI::IsChecked() const
{
	return m_bSelected;
}

void COptionUI::SetCheck(bool bSelected)
{
	if (m_bSelected == bSelected)
		return;
	m_bSelected = bSelected;
	if (m_pManager != NULL)
		m_pManager->SendNotify(this, _T("changed"));
	Invalidate();
}

void COptionUI::SetWidth(int cxWidth)
{
	m_cxWidth = cxWidth;
	UpdateLayout();
}

void COptionUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcscmp(pstrName, _T("width")) == 0)
		SetWidth(_ttoi(pstrValue));
	else if (_tcscmp(pstrName, _T("selected")) == 0)
		SetCheck(_tcscmp(pstrValue, _T("true")) == 0);
	else if (_tcscmp(pstrName, _T("align")) == 0)
	{
		if (_tcsstr(pstrValue, _T("right")) != NULL)
			m_uStyle |= DT_RIGHT;
	}
	else
		CControlUI::SetAttribute(pstrName, pstrValue);
}

void COptionUI::Event(TEventUI& event)
{
	if (event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK)
	{
		if (::PtInRect(&m_rcItem, event.ptMouse) && IsEnabled())
		{
			m_uButtonState |= UISTATE_PUSHED | UISTATE_CAPTURED;
			Invalidate();
		}
	}
	if (event.Type == UIEVENT_MOUSEMOVE)
	{
		if ((m_uButtonState & UISTATE_CAPTURED) != 0)
		{
			if (::PtInRect(&m_rcItem, event.ptMouse))
				m_uButtonState |= UISTATE_PUSHED;
			else
				m_uButtonState &= ~UISTATE_PUSHED;
			Invalidate();
		}
	}
	if (event.Type == UIEVENT_BUTTONUP)
	{
		if ((m_uButtonState & UISTATE_CAPTURED) != 0)
		{
			if (::PtInRect(&m_rcItem, event.ptMouse))
				Activate();
			m_uButtonState &= ~(UISTATE_PUSHED | UISTATE_CAPTURED);
			Invalidate();
		}
	}
	CControlUI::Event(event);
}

SIZE COptionUI::EstimateSize(SIZE /*szAvailable*/)
{
	return CSize(0 ,0);
//	return CSize(m_cxWidth, 18 + m_pManager->GetThemeFontInfo(UIFONT_NORMAL).tmHeight);
}

void COptionUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
	// Draw button
	UINT uState = 0;
	if (m_bSelected)
		uState |= UISTATE_CHECKED;
	if (IsFocused())
		uState |= UISTATE_FOCUSED;
	if (!IsEnabled())
		uState |= UISTATE_DISABLED;
//	CBlueRenderEngineUI::DoPaintOptionBox(hDC, m_pManager, m_rcItem, m_sText, m_uButtonState | uState, m_uStyle);
}
