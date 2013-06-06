#include "UILabel.h"
#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////////////
//

CLabelUI::CLabelUI() :
m_uTextStyle(DT_VCENTER),
m_dwTextColor(0),
m_dwDisabledTextColor(0),
m_iFont(-1),
m_bShowHtml(false),
m_nLinks(0),
m_hAlign(DT_LEFT),
m_vAlign(DT_CENTER)
{
	::ZeroMemory(m_rcLinks, sizeof(m_rcLinks));
	::ZeroMemory(&m_rcTextPadding, sizeof(m_rcTextPadding));
}

CLabelUI::~CLabelUI()
{
}

LPCTSTR CLabelUI::GetClass() const
{
	return _T("LabelUI");
}

LPVOID CLabelUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcscmp(pstrName, _T("Label")) == 0)
		return static_cast<CLabelUI*>(this);
	
	return CControlUI::GetInterface(pstrName);
}

void CLabelUI::SetTextStyle(UINT uStyle)
{
	m_uTextStyle = uStyle;
	Invalidate();
}

UINT CLabelUI::GetTextStyle() const
{
	return m_uTextStyle;
}

void CLabelUI::SetTextColor(DWORD dwTextColor)
{
	m_dwTextColor = dwTextColor;
	Invalidate();
}

DWORD CLabelUI::GetTextColor() const
{
	return m_dwTextColor;
}

void CLabelUI::SetDisabledTextColor(DWORD dwTextColor)
{
	m_dwDisabledTextColor = dwTextColor;
	Invalidate();
}

DWORD CLabelUI::GetDisabledTextColor() const
{
	return m_dwDisabledTextColor;
}

void CLabelUI::SetFont(int index)
{
	m_iFont = index;
	Invalidate();
}

int CLabelUI::GetFont() const
{
	return m_iFont;
}

RECT CLabelUI::GetTextPadding() const
{
	return m_rcTextPadding;
}

void CLabelUI::SetTextPadding(RECT rc)
{
	m_rcTextPadding = rc;
	Invalidate();
}

bool CLabelUI::IsShowHtml()
{
	return m_bShowHtml;
}

void CLabelUI::SetShowHtml(bool bShowHtml)
{
	if (m_bShowHtml == bShowHtml)
		return;

	m_bShowHtml = bShowHtml;
	Invalidate();
}

SIZE CLabelUI::EstimateSize(SIZE szAvailable)
{
	//if (m_cxyFixed.cy == 0 ) return CSize(m_cxyFixed.cx, m_pManager->GetFontInfo(GetFont())->tm.tmHeight + 4);
	//return CControlUI::EstimateSize(szAvailable);
	//return CSize(0, 0);
	return CSize(0, m_pManager->GetFontInfo(GetFont())->tm.tmHeight + 4);
}

void CLabelUI::Event(TEventUI& event)
{
	if( event.Type == UIEVENT_SETFOCUS ) 
	{
		m_bFocused = true;
		return;
	}
	if( event.Type == UIEVENT_KILLFOCUS ) 
	{
		m_bFocused = false;
		return;
	}
	if( event.Type == UIEVENT_MOUSEENTER )
	{
		// return;
	}
	if( event.Type == UIEVENT_MOUSELEAVE )
	{
		// return;
	}
	CControlUI::Event(event);
}

void CLabelUI::PaintText(HDC hDC)
{
	ASSERT(m_pManager != NULL);

	if (m_dwTextColor == 0)
		m_dwTextColor = m_pManager->GetDefaultFontColor();
	if (m_dwDisabledTextColor == 0)
		m_dwDisabledTextColor = m_pManager->GetDefaultDisabledColor();

	RECT rc = m_rcItem;
	rc.left += m_rcTextPadding.left;
	rc.right -= m_rcTextPadding.right;
	rc.top += m_rcTextPadding.top;
	rc.bottom -= m_rcTextPadding.bottom;

	if (m_sText.IsEmpty())
		return;
	int m_nLinks = 0;
	if (IsEnabled())
	{
		if (m_bShowHtml)
			CDefaultRenderEngineUI::DrawHtmlText(hDC, m_pManager, rc, m_sText, m_dwTextColor, NULL, m_nLinks, DT_SINGLELINE | m_uTextStyle);
		else
			CDefaultRenderEngineUI::DrawText(hDC, m_pManager, rc, m_sText, m_dwTextColor, m_iFont, DT_SINGLELINE | m_uTextStyle);
	}
	else
	{
		if (m_bShowHtml)
			CDefaultRenderEngineUI::DrawHtmlText(hDC, m_pManager, rc, m_sText, m_dwDisabledTextColor, NULL, m_nLinks, DT_SINGLELINE | m_uTextStyle);
		else
			CDefaultRenderEngineUI::DrawText(hDC, m_pManager, rc, m_sText, m_dwDisabledTextColor, m_iFont, DT_SINGLELINE | m_uTextStyle);
	}
}