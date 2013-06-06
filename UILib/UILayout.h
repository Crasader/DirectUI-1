#ifndef __UILAYOUT_H__
#define __UILAYOUT_H__


#pragma once
#include "UILib.h"

class UILIB_API CVerticalLayoutUI : public CContainerUI
{
public:
	CVerticalLayoutUI(void);

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	UINT GetControlFlags() const;
};


#endif // __UILAYOUT_H__