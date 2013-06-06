

#pragma once
#include "UILib.h"
#include "stdafx.h"


////////////////////////////////////////////////////////////////////////////////
//

CDialogUI::CDialogUI(void)
{
}

CDialogUI::~CDialogUI(void)
{
}

void CDialogUI::Notify(TNotifyUI& msg)
{
}

LPCTSTR CDialogUI::GetWindowClassName() const
{ 
	return _T("UIDialog");
};

LRESULT CDialogUI::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
// 	case WM_DESTROY:
// 		::PostQuitMessage(0L);
// 		break;

	case WM_CREATE:
		{
			// ³õÊ¼»¯¿Ø¼þ
			OnInitDialog();
			return 0;
		}
		break;

	default:
		break;
	}


//  	if( uMsg == WM_CREATE ) {
//  		SetIcon(IDR_MAINFRAME);
//  		_CreatePage("page_start");
//  	}
//  	if( uMsg == WM_DESTROY ) {
//  		::PostQuitMessage(0L);
//  	}
  	//if( uMsg == WM_SETFOCUS ) {
  	//	::SetFocus(m_hWnd);
  	//}
 	/*if( uMsg == WM_SIZE ) {
 		RECT rcClient;
 		::GetClientRect(m_hWnd, &rcClient);
 		::MoveWindow(m_hWndClient, rcClient.left, rcClient.top, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, TRUE);
 		return 0;
 	}*/
//  	if( uMsg == WM_ERASEBKGND ) {
//  		return 1;
//  	}
 	//if( uMsg == WM_PAINT ) {
 	//	PAINTSTRUCT ps = { 0 };
 	//	::BeginPaint(m_hWnd, &ps);
 	//	::EndPaint(m_hWnd, &ps);
 	//	return 0;
 	//}

	LRESULT lRes = 0;
	if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes))
		return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

int CDialogUI::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//LRESULT lRes = CWndUI::OnCreate(lpCreateStruct);

	OnInitDialog();
	//return lRes;

	return 0;
}

BOOL CDialogUI::OnInitDialog(void)
{
	return TRUE;
}
