#pragma once
#include "App.h"


int WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd)
{
	EnableMemLeakCheck();

	CPaintManagerUI::SetResourceInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	//CPaintManagerUI::SetResourceZip(_T("skin.zip"));

	HRESULT hRes = ::CoInitialize(NULL);
	if (FAILED(hRes))
		return 0;

	CTestUIDlg *Dlg = new CTestUIDlg;
	Dlg->Create(NULL, _T("TestUI"),
		//WS_VISIBLE | WS_OVERLAPPEDWINDOW,// |WS_POPUP | WS_SYSMENU,			//创建无标题栏窗口所要用的样式			WS_VISIBLE | WS_OVERLAPPEDWINDOW
		WS_VISIBLE | WS_POPUP | WS_SYSMENU,
		//WS_EX_STATICEDGE | WS_EX_APPWINDOW,
		0,
		300, 300, 600, 400, NULL);
	Dlg->CenterWindow();

	UINT_PTR nResponse = CPaintManagerUI::MessageLoop();


	 ::CoUninitialize();
	return nResponse;

	//CWnd::OnCreate()
}
