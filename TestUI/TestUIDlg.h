#pragma once
#include "App.h"

class CTestUIDlg : public CDialogUI
{
public:
	CTestUIDlg(void);
	~CTestUIDlg(void);

public:
	virtual LPCTSTR GetDialogResource() const;
	UINT OnNcHitTest(POINT point);
	virtual void Notify(TNotifyUI& msg);
	void OnFinalMessage(HWND /*hWnd*/);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	BOOL OnInitDialog(void);
	void OnButtonCancleClick();
	void OnButtonTextClick();
};



////////////////////////////////////
class CTest2UIDlg : public CDialogUI
{
public:
	CTest2UIDlg(void);
	~CTest2UIDlg(void);

public:
	virtual LPCTSTR GetDialogResource() const;
	virtual void Notify(TNotifyUI& msg);
	void OnFinalMessage(HWND /*hWnd*/);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	BOOL OnInitDialog(void);
	void OnButtonCancleClick();
	void OnButtonTextClick();
};


////////////////////////////////////
class CTest3UIDlg : public CDialogUI
{
public:
	CTest3UIDlg(void);
	~CTest3UIDlg(void);

public:
	virtual LPCTSTR GetDialogResource() const;
	virtual void Notify(TNotifyUI& msg);
	void OnFinalMessage(HWND /*hWnd*/);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	BOOL OnInitDialog(void);
	void OnButtonCancleClick();
	void OnButtonTextClick();
};
