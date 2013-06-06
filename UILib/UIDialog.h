#ifndef __UIDIALOG_H__20121015_A8EF_4576_8C40_C9BA12F69895__INCLUDED_
#define __UIDIALOG_H__20121015_A8EF_4576_8C40_C9BA12F69895__INCLUDED_

#pragma once
#include "UILib.h"

class UILIB_API CDialogUI : public CWindowWnd, public INotifyUI
{
public:
	CDialogUI(void);
	~CDialogUI(void);

public:
	virtual void Notify(TNotifyUI& msg);

	virtual LPCTSTR GetWindowClassName() const;

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog(void);

	virtual LPCTSTR GetDialogResource() const = 0;

protected:
	CPaintManagerUI m_pm;
};


#endif // __UIDIALOG_H__20121015_A8EF_4576_8C40_C9BA12F69895__INCLUDED_