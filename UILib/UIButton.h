#ifndef __UIBUTTON_H__
#define __UIBUTTON_H__


#pragma once
#include "UILib.h"

class UILIB_API CButtonUI :public CLabelUI
{
public:
	CButtonUI(void);
	~CButtonUI(void);

public:
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	UINT GetControlFlags() const;

	bool Activate();
	void SetEnabled(bool bEnable = true);

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void Event(TEventUI& event);

	void SetHotBkColor(DWORD dwColor);
	DWORD GetHotBkColor() const;
	void SetHotTextColor(DWORD dwColor);
	DWORD GetHotTextColor() const;
	void SetPushedTextColor(DWORD dwColor);
	DWORD GetPushedTextColor() const;
	void SetFocusedTextColor(DWORD dwColor);
	DWORD GetFocusedTextColor() const;

	LPCTSTR GetNormalImage();
	void SetNormalImage(LPCTSTR pStrImage);
	LPCTSTR GetHotImage();
	void SetHotImage(LPCTSTR pStrImage);
	LPCTSTR GetPushedImage();
	void SetPushedImage(LPCTSTR pStrImage);
	LPCTSTR GetFocusedImage();
	void SetFocusedImage(LPCTSTR pStrImage);
	LPCTSTR GetDisabledImage();
	void SetDisabledImage(LPCTSTR pStrImage);
	LPCTSTR GetForeImage();
	void SetForeImage(LPCTSTR pStrImage);
	LPCTSTR GetHotForeImage();
	void SetHotForeImage(LPCTSTR pStrImage);

	SIZE EstimateSize(SIZE szAvailable);

	void PaintText(HDC hDC);
	void PaintStatusImage(HDC hDC);

protected:
	UINT m_uButtonState;

	DWORD m_dwHotBkColor;
	DWORD m_dwHotTextColor;
	DWORD m_dwPushedTextColor;
	DWORD m_dwFocusedTextColor;

	CStdString m_sNormalImage;
	CStdString m_sForeImage;
	CStdString m_sHotImage;
	CStdString m_sHotForeImage;
	CStdString m_sPushedImage;
	CStdString m_sPushedForeImage;
	CStdString m_sFocusedImage;
	CStdString m_sDisabledImage;
};




/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API COptionUI : public CControlUI
{
public:
	COptionUI();

	LPCTSTR GetClass() const;
	UINT GetControlFlags() const;

	bool Activate();

	bool IsChecked() const;
	void SetCheck(bool bSelected);
	void SetWidth(int cxWidth);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	void Event(TEventUI& event);

	SIZE EstimateSize(SIZE szAvailable);
	void DoPaint(HDC hDC, const RECT& rcPaint);
protected:
	bool m_bSelected;
	UINT m_uStyle;
	UINT m_uButtonState;
	int m_cxWidth;
};

#endif // __UIBUTTON_H__