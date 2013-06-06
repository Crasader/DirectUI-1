#include "stdafx.h"
#include "UILayout.h"

CVerticalLayoutUI::CVerticalLayoutUI(void)
{
}

LPCTSTR CVerticalLayoutUI::GetClass() const
{
	return _T("VerticalLayoutUI");
}

LPVOID CVerticalLayoutUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcscmp(pstrName, _T("VerticalLayout")) == 0)
		return static_cast<CVerticalLayoutUI*>(this);

	return CContainerUI::GetInterface(pstrName);
}

UINT CVerticalLayoutUI::GetControlFlags() const
{
	if (IsEnabled())
		return UIFLAG_SETCURSOR;
	else
		return 0;
}