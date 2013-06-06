#ifndef __UIEDIT_H__20121015_B209_44A1_88A0_1D790CEBBDF7__INCLUDED_
#define __UIEDIT_H__20121015_B209_44A1_88A0_1D790CEBBDF7__INCLUDED_

#pragma once
#include "UILib.h"



/////////////////////////////////////////////////////////////////////////////////////
//

class CSingleLineEditWnd;

class UILIB_API CSingleLineEditUI : public CControlUI
{
	friend CSingleLineEditWnd;
public:
	CSingleLineEditUI(void);
	~CSingleLineEditUI(void);

public:
	LPCTSTR GetClass() const;
	UINT GetControlFlags() const;

	void SetText(LPCTSTR pstrText);

	void SetEditStyle(UINT uStyle);
	void SetReadOnly(bool bReadOnly);
	bool IsReadOnly() const;

	void Event(TEventUI& event);

	SIZE EstimateSize(SIZE szAvailable);
	void DoPaint(HDC hDC, const RECT& rcPaint);

protected:
	CSingleLineEditWnd* m_pWindow;
	bool m_bReadOnly;
	UINT m_uEditStyle;
};





/////////////////////////////////////////////////////////////////////////////////////
//

class CMultiLineEditWnd;

class UILIB_API CMultiLineEditUI : public CControlUI
{
	friend CMultiLineEditWnd;
public:
	CMultiLineEditUI();
	~CMultiLineEditUI();

	LPCTSTR GetClass() const;
	UINT GetControlFlags() const;

	void Init();

	CStdString GetText() const;
	void SetText(LPCTSTR pstrText);

	void SetEnabled(bool bEnabled);
	void SetVisible(bool bVisible);
	void SetReadOnly(bool bReadOnly);
	//void SetFocus(bool bReadOnly);
	bool IsReadOnly() const;

	void Event(TEventUI& event);

	SIZE EstimateSize(SIZE szAvailable);
	void SetPos(RECT rc);
	void SetPos(int left, int top, int right, int bottom);
	void DoPaint(HDC hDC, const RECT& rcPaint);

protected:
	CMultiLineEditWnd* m_pWindow;
};





#endif // __UIEDIT_H__20121015_B209_44A1_88A0_1D790CEBBDF7__INCLUDED_