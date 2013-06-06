#include "TestUIDlg.h"

CTestUIDlg::CTestUIDlg(void)
{
}

CTestUIDlg::~CTestUIDlg(void)
{
}

LPCTSTR CTestUIDlg::GetDialogResource() const
{
	return NULL;
}

UINT CTestUIDlg::OnNcHitTest(POINT point)
{
	return 0;
	//return CDialogUI::OnNcHitTest(point);
}

void CTestUIDlg::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("click") || msg.sType == _T("link"))
	{
		if (wcscmp(msg.pSender->GetName(), _T("cancel")) == 0)
		{
			OnButtonCancleClick();
		}
		if (wcscmp(msg.pSender->GetName(), _T("text")) == 0)
		{
			OnButtonTextClick();
		}
		if (wcscmp(msg.pSender->GetName(), _T("ok")) == 0)
		{
			//MessageBox(m_hWnd, _T("OK"), _T("ok"), MB_OK);
		}

	}
	if (msg.sType == _T("changed"))
	{
		if (wcscmp(msg.pSender->GetName(), _T("Option1")) == 0 && ((COptionUI*)msg.pSender)->IsChecked() == true)
		{
			//msg.pSender->SetAttribute(_T("selected"), _T("false"));
			//MessageBox(m_hWnd, _T("OK"), _T("ok"), MB_OK);
			COptionUI *p = (COptionUI*)m_pm.FindControl(_T("Option2"));
			if (p != NULL)
			{
				p->SetCheck(false);
			}
		}
		if (wcscmp(msg.pSender->GetName(), _T("Option2")) == 0 && ((COptionUI*)msg.pSender)->IsChecked() == true)
		{
			//MessageBox(m_hWnd, _T("OK"), _T("ok"), MB_OK);
			COptionUI *p = (COptionUI*)m_pm.FindControl(_T("Option1"));
			if (p != NULL)
			{
				p->SetCheck(false);
			}
		}
	}
}

void CTestUIDlg::OnFinalMessage(HWND /*hWnd*/)
{ 
	delete this; 
};

LRESULT CTestUIDlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
	{     
		::PostQuitMessage(0L);
	}
	if (uMsg == WM_SIZE)
	{
		SIZE szRoundCorner = m_pm.GetRoundCorner();
		if( !::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0) ) {
			CRect rcWnd;
			::GetWindowRect(*this, &rcWnd);
			rcWnd.Offset(-rcWnd.left, -rcWnd.top);
			rcWnd.right++; rcWnd.bottom++;
			HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
			::SetWindowRgn(*this, hRgn, TRUE);
			::DeleteObject(hRgn);
		}
	}
	if (uMsg == WM_NCCALCSIZE)
	{
		return 0;
	}
	if (uMsg == WM_NCHITTEST)
	{
		POINT pt; 
		pt.x = GET_X_LPARAM(lParam); 
		pt.y = GET_Y_LPARAM(lParam);
		::ScreenToClient(*this, &pt);

		RECT rcClient;
		::GetClientRect(*this, &rcClient);

		if( !::IsZoomed(*this) )
		{
			RECT rcSizeBox = m_pm.GetSizeBox();
			if( pt.y < rcClient.top + rcSizeBox.top ) 
			{
				if ( pt.x < rcClient.left + rcSizeBox.left )
					return HTTOPLEFT;
				if( pt.x > rcClient.right - rcSizeBox.right ) 
					return HTTOPRIGHT;
				return HTTOP;
			}
			else if( pt.y > rcClient.bottom - rcSizeBox.bottom ) 
			{
				if( pt.x < rcClient.left + rcSizeBox.left )
					return HTBOTTOMLEFT;
				if( pt.x > rcClient.right - rcSizeBox.right )
					return HTBOTTOMRIGHT;
				return HTBOTTOM;
			}
			if( pt.x < rcClient.left + rcSizeBox.left ) 
				return HTLEFT;
			if( pt.x > rcClient.right - rcSizeBox.right )
				return HTRIGHT;
		}

		RECT rcCaption = m_pm.GetCaptionRect();
		if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
			&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) {
				CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
				if( pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 && 
					_tcscmp(pControl->GetClass(), _T("OptionUI")) != 0 &&
					_tcscmp(pControl->GetClass(), _T("TextUI")) != 0 )
					return HTCAPTION;
		}

		return HTCLIENT;
	}
	if (uMsg == WM_GETMINMAXINFO)
	{
		MONITORINFO oMonitor = {};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
		CRect rcWork = oMonitor.rcWork;
		rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

		LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
		lpMMI->ptMaxPosition.x	= rcWork.left;
		lpMMI->ptMaxPosition.y	= rcWork.top;
		lpMMI->ptMaxSize.x		= rcWork.right;
		lpMMI->ptMaxSize.y		= rcWork.bottom;

		//return 0;
	}


	return CDialogUI::HandleMessage(uMsg, wParam, lParam);
}

BOOL CTestUIDlg::OnInitDialog(void)
{
	CDialogUI::OnInitDialog();

	// 设置图标
	SetIcon(IDR_MAINFRAME);

	/*LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);*/
	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE)
		| WS_MAXIMIZEBOX | WS_MINIMIZEBOX
		| WS_SYSMENU | WS_SIZEBOX;
	dwStyle &= ~WS_CAPTION;
	::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);

	//CRichEditCtrl::SetBackgroundColor()
	//::SendMessage(m_hWnd, WM_SETBKGNDCOLOR, FALSE, BLACK_BRUSH);
	m_pm.Init(m_hWnd);
	/*CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(GetDialogResource());
	ASSERT(pRoot && "Failed to parse XML");*/
	CDialogLayoutUI* pRoot = NULL;
	pRoot = new CDialogLayoutUI();
	pRoot->SetBkColor(0xFFD1E8F5);
	pRoot->SetBkColor2(0xFFC6E0F1);
	//pRoot->SetBkColor3(0xFF768D25);
	pRoot->SetBkImage(_T("file='icon.png' source='0,0,16,16' dest='5,4,21,20'"));
	pRoot->SetBorderColor(0xFF768D9B);
	pRoot->SetBorderSize(1);
	pRoot->SetBorderRound(CSize(5, 5));
	//RECT rcInset = { 1,0,1,0 };
	//pRoot->SetInset(rcInset);


	ASSERT(pRoot && "Failed to parse XML");
	RECT rcPos = {0, 0, 600, 800};
	//pRoot->SetPos(rcPos);


	CControlUI* pButton = NULL;
	pButton = new CButtonUI;
	RECT rcButtonPos = {50, 100, 90, 128};
	pButton->SetPos(rcButtonPos);
	pButton->SetText(_T("&New"));
	pButton->SetName(_T("text"));
	pButton->SetToolTip(_T("弹出一个对话框"));
	pRoot->Add(pButton);
	//pRoot->SetStretchMode(pButton, UISTRETCH_NEWGROUP);

	CControlUI* pButton1 = NULL;
	pButton1 = new CButtonUI;
	RECT rcButtonPos1 = {150, 100, 200, 128};
	pButton1->SetPos(rcButtonPos1);
	pButton1->SetText(_T("确定"));
	pButton1->SetName(_T("OK"));
	//pButton1->SetBkColor(0xFFFF0000);
	pButton1->SetBorderSize(1);
	pButton1->SetToolTip(_T("确定"));
	//pButton1->SetFocusBorderColor(0xFFFF0000);
	pRoot->Add(pButton1);
	//pRoot->SetStretchMode(pButton1, UISTRETCH_SIZE_X);



	CControlUI* pButton2 = NULL;
	pButton2 = new CButtonUI;
	RECT rcButtonPos2 = {260, 100, 310, 128};
	pButton2->SetPos(rcButtonPos2);
	pButton2->SetText(_T("取消"));
	pButton2->SetName(_T("cancel"));
	pRoot->Add(pButton2);
	//pRoot->SetStretchMode(pButton2, UISTRETCH_NEWGROUP|UISTRETCH_MOVE_X);
	//pRoot->SetStretchMode(pButton2, UISTRETCH_MOVE_X |UISTRETCH_SIZE_X);

	CButtonUI* pButton3 = NULL;
	pButton3 = new CButtonUI;
	RECT rcButtonPos3 = {330, 100, 500, 128};
	pButton3->SetPos(rcButtonPos3);
	pButton3->SetText(_T("<a www.baidu.com>www.baidu.com</a>"));
	pButton3->SetName(_T("can"));
	pRoot->Add(pButton3);
	pButton3->SetShowHtml();


	CLabelUI* pLabel = NULL;
	pLabel = new CLabelUI;
	RECT rcLabel = {40, 30, 500, 100};
	pLabel->SetPos(rcLabel);
	//pLabel->SetText(_T("<b>CLabelUI</b> <c #FF0000>静态</c>文本控件 <a>www.baidu.com</a> "));
	pLabel->SetText(_T("<b><x 10>CLabelUI</b> <c #00FF0000>静<i>态</i></c><u>文<x 10>本</u>控<s>选中测试</s>件 <a www.baidu.com>www.ba<h>idu.com</a> "));
	//pLabel->SetBkColor(0xFFFF0000);
	//pLabel->SetEnabled(false);
	pLabel->SetShowHtml();
	pRoot->Add(pLabel);
//	pLabel->SetManager(&m_pm, NULL, false);

// 	CControlUI* pLabel2 = NULL;
// 	pLabel2 = new CLabelUI;
// 	RECT rcLabel2 = {0, 0, 0, 0};
// 	pLabel2->SetPos(rcLabel2);
// 	pLabel2->SetText(_T("CLabelUI 静态文本控件"));
// 	pRoot->Add(pLabel2);
// 	pLabel2->SetManager(&m_pm, NULL, false);

	/*CControlUI* pSingleLineEdit = NULL;
	pSingleLineEdit = new CSingleLineEditUI;
	RECT rcSingleLineEdit = {10, 50, 200, 70};
	pSingleLineEdit->SetPos(rcSingleLineEdit);
	pSingleLineEdit->SetText(_T("CSingleLineEditUI 单行编辑控件"));
	pRoot->Add(pSingleLineEdit);

	CControlUI* pMultiLineEdit = NULL;
	pMultiLineEdit = new CMultiLineEditUI;
	RECT rcMultiLineEdit = {10, 80, 200, 140};
	pMultiLineEdit->SetPos(rcMultiLineEdit);
	pMultiLineEdit->SetText(_T("CMultiLineEditUI\r\n多行编辑控件 "));
	pRoot->Add(pMultiLineEdit);*/

	//CControlUI* pOption1 = NULL;
	//pOption1 = new COptionUI;
	//RECT rcOption1 = {10, 150, 200, 165};
	//pOption1->SetPos(rcOption1);
	//pOption1->SetAttribute(_T("selected"), _T("true"));
	//pOption1->SetText(_T("COptionUI 单选按钮1"));
	//pOption1->SetName(_T("Option1"));
	//pRoot->Add(pOption1);

	//CControlUI* pOption2 = NULL;
	//pOption2 = new COptionUI;
	//RECT rcOption2 = {220, 150, 370, 165};
	//pOption2->SetPos(rcOption2);
	//pOption2->SetName(_T("Option2"));
	//pOption2->SetText(_T("COptionUI 单选按钮2"));
	////pOption2->SetAttribute(_T("selected"), _T("true"));
	//pRoot->Add(pOption2);



	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);

	m_pm.SetRoundCorner(5, 5);
	RECT rcCaption = { 0, 0, 0, 90 };
	m_pm.SetCaptionRect(rcCaption);
	RECT rcSizeBox = { 5, 5, 5, 5 };
	m_pm.SetSizeBox(rcSizeBox);

	return TRUE;
}

void CTestUIDlg::OnButtonCancleClick()
{
	// 关闭
	ASSERT(::IsWindow(m_hWnd));
	if( !::IsWindow(m_hWnd) ) return;
	PostMessage(WM_CLOSE);
	/*::PostQuitMessage(0L);*/
}

void CTestUIDlg::OnButtonTextClick()
{
	CTest2UIDlg *Dlg = new CTest2UIDlg;
	Dlg->Create(m_hWnd, _T("Test2UI"),
		WS_VISIBLE | WS_OVERLAPPEDWINDOW,//WS_POPUP | WS_SYSMENU,			//创建无标题栏窗口所要用的样式			WS_VISIBLE | WS_OVERLAPPEDWINDOW
		0,
		300, 300, 600, 400, NULL);

	Dlg->ShowModal();
}








/////////////////////////////////
CTest2UIDlg::CTest2UIDlg(void)
{
}

CTest2UIDlg::~CTest2UIDlg(void)
{
}

void CTest2UIDlg::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("click") || msg.sType == _T("link"))
	{
		if (wcscmp(msg.pSender->GetName(), _T("cancel")) == 0)
		{
			OnButtonCancleClick();
		}
		if (wcscmp(msg.pSender->GetName(), _T("text")) == 0)
		{
			OnButtonTextClick();
		}
	}
}

LPCTSTR CTest2UIDlg::GetDialogResource() const
{
	return NULL;
}


void CTest2UIDlg::OnFinalMessage(HWND /*hWnd*/)
{ 
	delete this; 
};

BOOL CTest2UIDlg::OnInitDialog(void)
{
	CDialogUI::OnInitDialog();

	// 设置图标
	SetIcon(IDR_MAINFRAME);

	//CRichEditCtrl::SetBackgroundColor()
	//::SendMessage(m_hWnd, WM_SETBKGNDCOLOR, FALSE, BLACK_BRUSH);


	return TRUE;
}

void CTest2UIDlg::OnButtonCancleClick()
{
	// 关闭
	//::PostQuitMessage(0L);
	return;
	//SendMessage(WM_CLOSE);
	ASSERT(::IsWindow(m_hWnd));
	if( !::IsWindow(m_hWnd) ) return;
	PostMessage(WM_CLOSE);
}

void CTest2UIDlg::OnButtonTextClick()
{
	CTest3UIDlg *Dlg = new CTest3UIDlg;
	Dlg->Create(m_hWnd, _T("Test3UI"),
		WS_VISIBLE | WS_OVERLAPPEDWINDOW,//WS_POPUP | WS_SYSMENU,			//创建无标题栏窗口所要用的样式			WS_VISIBLE | WS_OVERLAPPEDWINDOW
		0,
		300, 300, 600, 400, NULL);

	Dlg->ShowModal();
}

LRESULT CTest2UIDlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CDialogUI::HandleMessage(uMsg, wParam, lParam);
}



////////////////////////////////
CTest3UIDlg::CTest3UIDlg(void)
{
}

CTest3UIDlg::~CTest3UIDlg(void)
{
}

void CTest3UIDlg::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("click") || msg.sType == _T("link"))
	{
		if (wcscmp(msg.pSender->GetName(), _T("cancel")) == 0)
		{
			OnButtonCancleClick();
		}
		if (wcscmp(msg.pSender->GetName(), _T("text")) == 0)
		{
			OnButtonTextClick();
		}
	}
}

LPCTSTR CTest3UIDlg::GetDialogResource() const
{
	return NULL;
}


void CTest3UIDlg::OnFinalMessage(HWND /*hWnd*/)
{ 
	delete this; 
};

BOOL CTest3UIDlg::OnInitDialog(void)
{
	CDialogUI::OnInitDialog();

	// 设置图标
	SetIcon(IDR_MAINFRAME);

	//CRichEditCtrl::SetBackgroundColor()
	//::SendMessage(m_hWnd, WM_SETBKGNDCOLOR, FALSE, BLACK_BRUSH);

	return TRUE;
}

void CTest3UIDlg::OnButtonCancleClick()
{
	// 关闭
	::PostQuitMessage(0L);
	return;
	//SendMessage(WM_CLOSE);
	ASSERT(::IsWindow(m_hWnd));
	if( !::IsWindow(m_hWnd) ) return;
	PostMessage(WM_CLOSE);
}

void CTest3UIDlg::OnButtonTextClick()
{
	CTest3UIDlg *Dlg = new CTest3UIDlg;
	Dlg->Create(m_hWnd, _T("Test4UI"),
		WS_VISIBLE | WS_OVERLAPPEDWINDOW,//WS_POPUP | WS_SYSMENU,			//创建无标题栏窗口所要用的样式			WS_VISIBLE | WS_OVERLAPPEDWINDOW
		0,
		300, 300, 600, 400, NULL);
	Dlg->ShowModal();
}

LRESULT CTest3UIDlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CDialogUI::HandleMessage(uMsg, wParam, lParam);
}