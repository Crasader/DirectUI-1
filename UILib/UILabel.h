#ifndef __UILABLE_H__
#define __UILABLE_H__

#pragma once
#include "UILib.h"


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CLabelUI : public CControlUI
{
public:
	CLabelUI(void);
	~CLabelUI(void);

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	void SetTextStyle(UINT uStyle);
	UINT GetTextStyle() const;
	void SetTextColor(DWORD dwTextColor);
	DWORD GetTextColor() const;
	void SetDisabledTextColor(DWORD dwTextColor);
	DWORD GetDisabledTextColor() const;
	void SetFont(int index);
	int GetFont() const;
	RECT GetTextPadding() const;
	void SetTextPadding(RECT rc);
	bool IsShowHtml();
	void SetShowHtml(bool bShowHtml = true);

	SIZE EstimateSize(SIZE szAvailable);
	void Event(TEventUI& event);

	void PaintText(HDC hDC);

protected:
	UINT	m_uTextStyle;
	DWORD	m_dwTextColor;
	DWORD	m_dwDisabledTextColor;
	int		m_iFont;
	RECT	m_rcTextPadding;
	bool	m_bShowHtml;
	int		m_nLinks;
	RECT	m_rcLinks[8];

	int		m_hAlign;
	int		m_vAlign;
};



#endif // __UILABLE_H__