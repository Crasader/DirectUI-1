
#include "StdAfx.h"
#include "UIContainer.h"


/////////////////////////////////////////////////////////////////////////////////////
//
//

CContainerUI::CContainerUI() : 
m_iPadding(0),
m_bAutoDestroy(true),
m_pVerticalScrollBar(NULL),
m_pHorizontalScrollBar(NULL),
m_bAllowScrollbars(false)
{
	//m_cxyFixed.cx = m_cxyFixed.cy = 0;
	::ZeroMemory(&m_rcInset, sizeof(m_rcInset));
}

CContainerUI::~CContainerUI()
{
	RemoveAll();
}

LPCTSTR CContainerUI::GetClass() const
{
	return _T("ContainerUI");
}

LPVOID CContainerUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcscmp(pstrName, _T("Container")) == 0)
		return static_cast<IContainerUI*>(this);
	
	return CControlUI::GetInterface(pstrName);
}

CControlUI* CContainerUI::GetItem(int iIndex) const
{
	if (iIndex < 0 || iIndex >= m_items.GetSize())
		return NULL;
	
	return static_cast<CControlUI*>(m_items[iIndex]);
}

int CContainerUI::GetItemIndex(CControlUI* pControl) const
{
	for (int it = 0; it < m_items.GetSize(); it++)
	{
		if (static_cast<CControlUI*>(m_items[it]) == pControl)
		{
			return it;
		}
	}

	return -1;
}

bool CContainerUI::SetItemIndex(CControlUI* pControl, int iIndex)
{
	for (int it = 0; it < m_items.GetSize(); it++)
	{
		if (static_cast<CControlUI*>(m_items[it]) == pControl)
		{
			UpdateLayout();            
			m_items.Remove(it);
			return m_items.InsertAt(iIndex, pControl);
		}
	}

	return false;
}

int CContainerUI::GetCount() const
{
	return m_items.GetSize();
}

bool CContainerUI::Add(CControlUI* pControl)
{
	if (pControl == NULL)
		return false;

	if (m_pManager != NULL)
		m_pManager->InitControls(pControl, this);

	if (IsVisible())
		UpdateLayout();
	else
		pControl->SetInternVisible(false);

	return m_items.Add(pControl);
}


bool CContainerUI::AddAt(CControlUI* pControl, int iIndex)
{
	if (pControl == NULL)
		return false;

	if (m_pManager != NULL)
		m_pManager->InitControls(pControl, this);
	
	if (IsVisible())
		UpdateLayout();
	else
		pControl->SetInternVisible(false);
	
	return m_items.InsertAt(iIndex, pControl);
}

bool CContainerUI::Remove(CControlUI* pControl)
{
	for (int it = 0; m_bAutoDestroy && it < m_items.GetSize(); it++)
	{
		if (static_cast<CControlUI*>(m_items[it]) == pControl)
		{
			if (m_pManager != NULL)
				m_pManager->UpdateLayout();
			delete pControl;
			return m_items.Remove(it);
		}
	}

	return false;
}

bool CContainerUI::RemoveAt(int iIndex)
{
	CControlUI* pControl = GetItem(iIndex);
	if (pControl != NULL)
	{
		return CContainerUI::Remove(pControl);
	}

	return false;
}

void CContainerUI::RemoveAll()
{
	for (int it = 0; m_bAutoDestroy && it < m_items.GetSize(); it++)
		delete static_cast<CControlUI*>(m_items[it]);

	m_items.Empty();

	if (m_pManager != NULL)
		m_pManager->UpdateLayout();
}

void CContainerUI::Event(TEventUI& event)
{
	/*if (m_hwndScroll != NULL) 
	{
		if (event.Type == UIEVENT_VSCROLL) 
		{
			switch( LOWORD(event.wParam) )
			{
			case SB_THUMBPOSITION:
			case SB_THUMBTRACK:
			 {
				 SCROLLINFO si = { 0 };
				 si.cbSize = sizeof(SCROLLINFO);
				 si.fMask = SIF_TRACKPOS;
				 ::GetScrollInfo(m_hwndScroll, SB_CTL, &si);
				 SetScrollPos(si.nTrackPos);
			 }
			 break;

			case SB_LINEUP:
				SetScrollPos(GetScrollPos() - 5);
				break;

			case SB_LINEDOWN:
				SetScrollPos(GetScrollPos() + 5);
				break;

			case SB_PAGEUP:
				SetScrollPos(GetScrollPos() - GetScrollPage());
				break;

			case SB_PAGEDOWN:
				SetScrollPos(GetScrollPos() + GetScrollPage());
				break;
			}
		}

		if (event.Type == UIEVENT_KEYDOWN) 
		{
			switch( event.chKey )
			{
			case VK_DOWN:
				SetScrollPos(GetScrollPos() + 5);
				return;

			case VK_UP:
				SetScrollPos(GetScrollPos() - 5);
				return;

			case VK_NEXT:
				SetScrollPos(GetScrollPos() + GetScrollPage());
				return;

			case VK_PRIOR:
				SetScrollPos(GetScrollPos() - GetScrollPage());
				return;

			case VK_HOME:
				SetScrollPos(0);
				return;

			case VK_END:
				SetScrollPos(9999);
				return;
			}
		}
	}*/

	CControlUI::Event(event);
}

void CContainerUI::SetVisible(bool bVisible)
{
	if (m_bVisible == bVisible)
		return;
	
	CControlUI::SetVisible(bVisible);
	// Hide children as well
	for (int it = 0; it < m_items.GetSize(); it++)
	{
		static_cast<CControlUI*>(m_items[it])->SetInternVisible(IsVisible());
	}
}

// 逻辑上，对于Container控件不公开此方法
// 调用此方法的结果是，内部子控件隐藏，控件本身依然显示，背景等效果存在
void CContainerUI::SetInternVisible(bool bVisible)
{
	CControlUI::SetInternVisible(bVisible);
	if (m_items.IsEmpty())
		return;
	for (int it = 0; it < m_items.GetSize(); it++)
	{
		// 控制子控件显示状态
		// InternVisible状态应由子控件自己控制
		static_cast<CControlUI*>(m_items[it])->SetInternVisible(IsVisible());
	}
}

void CContainerUI::SetInset(RECT rcInset)
{
	m_rcInset = rcInset;
	UpdateLayout();
}

void CContainerUI::SetPadding(int iPadding)
{
	m_iPadding = iPadding;
}

// void CContainerUI::SetWidth(int cx)
// {
// 	m_cxyFixed.cx = cx;
// }
// 
// void CContainerUI::SetHeight(int cy)
// {
// 	m_cxyFixed.cy = cy;
// }

void CContainerUI::SetAutoDestroy(bool bAuto)
{
	m_bAutoDestroy = bAuto;
}

int CContainerUI::FindSelectable(int iIndex, bool bForward /*= true*/) const
{
	// NOTE: This is actually a helper-function for the list/combo/ect controls
	//       that allow them to find the next enabled/available selectable item
	
	if (GetCount() == 0)
		return -1;

	iIndex = CLAMP(iIndex, 0, GetCount() - 1);
	
	if (bForward)
	{
		for (int i = iIndex; i < GetCount(); i++)
		{
			if (GetItem(i)->GetInterface(_T("ListItem")) != NULL 
				&& GetItem(i)->IsVisible()
				&& GetItem(i)->IsEnabled())
				return i;
		}
		return -1;
	}
	else
	{
		for (int i = iIndex; i >= 0; --i)
		{
			if (GetItem(i)->GetInterface(_T("ListItem")) != NULL 
				&& GetItem(i)->IsVisible()
				&& GetItem(i)->IsEnabled())
				return i;
		}
		return FindSelectable(0, true);
	}
}

void CContainerUI::SetPos(RECT rc)
{
	CControlUI::SetPos(rc);

	//if (m_items.IsEmpty())
	//	return;

	//rc.left += m_rcInset.left;
	//rc.top += m_rcInset.top;
	//rc.right -= m_rcInset.right;
	//rc.bottom -= m_rcInset.bottom;

	//for( int it = 0; it < m_items.GetSize(); it++ )
	//{
	//	CControlUI* pControl = static_cast<CControlUI*>(m_items[it]);
	//	if (!pControl->IsVisible())
	//		continue;
	//	if (pControl->IsFloat())
	//	{
	//		//SetFloatPos(it);
	//	}
	//	else
	//	{
	//		pControl->SetPos(rc); // 所有非float子控件放大到整个客户区
	//	}
	//}
}

void CContainerUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
	RECT rcTemp = { 0 };
	if (!::IntersectRect(&rcTemp, &rcPaint, &m_rcItem))
		return;

	CRenderClip clip;
	CRenderClip::GenerateClip(hDC, m_rcItem, clip);
	CControlUI::DoPaint(hDC, rcPaint);

	for (int it = 0; it < m_items.GetSize(); it++)
	{
		CControlUI* pControl = static_cast<CControlUI*>(m_items[it]);
		if (!pControl->IsVisible())
			continue;
		if (!::IntersectRect(&rcTemp, &rcPaint, &pControl->GetPos())) 
			continue;
		if (!::IntersectRect(&rcTemp, &m_rcItem, &pControl->GetPos())) 
			continue;
		pControl->DoPaint(hDC, rcPaint);
	}
}

void CContainerUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcscmp(pstrName, _T("inset")) == 0)
	{
		RECT rcInset = { 0 };
		LPTSTR pstr = NULL;
		rcInset.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
		rcInset.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
		rcInset.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);    
		rcInset.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);    
		SetInset(rcInset);
	}
	else if (_tcscmp(pstrName, _T("padding")) == 0)
		SetPadding(_ttoi(pstrValue));
	//else if (_tcscmp(pstrName, _T("width")) == 0)
	//	SetWidth(_ttoi(pstrValue));
	//else if (_tcscmp(pstrName, _T("height")) == 0)
	//	SetHeight(_ttoi(pstrValue));
	else if (_tcscmp(pstrName, _T("scrollbar")) == 0)
		EnableScrollBar(_tcscmp(pstrValue, _T("true")) == 0);
	else 
		CControlUI::SetAttribute(pstrName, pstrValue);
}

void CContainerUI::SetManager(CPaintManagerUI* pManager, CControlUI* pParent)
{
	for (int it = 0; it < m_items.GetSize(); it++)
	{
		static_cast<CControlUI*>(m_items[it])->SetManager(pManager, this);
	}
	CControlUI::SetManager(pManager, pParent);
}

CControlUI* CContainerUI::FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags)
{
	// Check if this guy is valid
	if ((uFlags & UIFIND_VISIBLE) != 0 && !IsVisible())
		return NULL;

	if ((uFlags & UIFIND_ENABLED) != 0 && !IsEnabled())
		return NULL;

	if ((uFlags & UIFIND_HITTEST) != 0 && !::PtInRect(&m_rcItem, *(static_cast<LPPOINT>(pData))))
		return NULL;
	
	if ((uFlags & UIFIND_ME_FIRST) != 0 )
	{
		CControlUI* pControl = CControlUI::FindControl(Proc, pData, uFlags);
		if (pControl != NULL)
			return pControl;
	}

	for (int it = 0; it != m_items.GetSize(); it++)
	{
		CControlUI* pControl = static_cast<CControlUI*>(m_items[it])->FindControl(Proc, pData, uFlags);
		if( pControl != NULL )
			return pControl;
	}

	return CControlUI::FindControl(Proc, pData, uFlags);
}

SIZE CContainerUI::GetScrollPos() const
{
	SIZE sz = {0, 0};
	/*if (m_pVerticalScrollBar != NULL && m_pVerticalScrollBar->IsVisible())
		sz.cy = m_pVerticalScrollBar->GetScrollPos();
	if (m_pHorizontalScrollBar != NULL && m_pHorizontalScrollBar->IsVisible())
		sz.cx = m_pHorizontalScrollBar->GetScrollPos();*/
	return sz;
}

void CContainerUI::SetScrollPos(SIZE szPos)
{
	int cx = 0;
	//int cy = 0;
	//if (m_pVerticalScrollBar != NULL && m_pVerticalScrollBar->IsVisible())
	//{
	//	int iLastScrollPos = m_pVerticalScrollBar->GetScrollPos();
	//	m_pVerticalScrollBar->SetScrollPos(szPos.cy);
	//	cy = m_pVerticalScrollBar->GetScrollPos() - iLastScrollPos;
	//}

	//if (m_pHorizontalScrollBar != NULL && m_pHorizontalScrollBar->IsVisible())
	//{
	//	int iLastScrollPos = m_pHorizontalScrollBar->GetScrollPos();
	//	m_pHorizontalScrollBar->SetScrollPos(szPos.cx);
	//	cx = m_pHorizontalScrollBar->GetScrollPos() - iLastScrollPos;
	//}

	//if (cx == 0 && cy == 0)
	//	return;

	//// Reposition children to the new viewport.
	//RECT rcPos;
	//for (int it2 = 0; it2 < m_items.GetSize(); it2++)
	//{
	//	CControlUI* pControl = static_cast<CControlUI*>(m_items[it2]);
	//	if (!pControl->IsVisible())
	//		continue;
	//	if (pControl->IsFloat())
	//		continue;

	//	rcPos = pControl->GetPos();
	//	rcPos.left -= cx;
	//	rcPos.right -= cx;
	//	rcPos.top -= cy;
	//	rcPos.bottom -= cy;
	//	pControl->SetPos(rcPos);
	//}

	Invalidate();
}

SIZE CContainerUI::GetScrollRange() const
{
	SIZE sz = {0, 0};
	/*if (m_pVerticalScrollBar != NULL && m_pVerticalScrollBar->IsVisible())
		sz.cy = m_pVerticalScrollBar->GetScrollRange();
	if (m_pHorizontalScrollBar != NULL  && m_pHorizontalScrollBar->IsVisible())
		sz.cx = m_pHorizontalScrollBar->GetScrollRange();*/
	return sz;
}

void CContainerUI::LineUp()
{
	int cyLine = 8;
	if (m_pManager != NULL)
		cyLine = m_pManager->GetDefaultFontInfo()->tm.tmHeight + 8;

	SIZE sz = GetScrollPos();
	sz.cy -= cyLine;
	SetScrollPos(sz);
}

void CContainerUI::LineDown()
{
	int cyLine = 8;
	if (m_pManager != NULL)
		cyLine = m_pManager->GetDefaultFontInfo()->tm.tmHeight + 8;

	SIZE sz = GetScrollPos();
	sz.cy += cyLine;
	SetScrollPos(sz);
}

void CContainerUI::PageUp()
{
	/*SIZE sz = GetScrollPos();
	int iOffset = m_rcItem.bottom - m_rcItem.top - m_rcInset.top - m_rcInset.bottom;
	if (m_pHorizontalScrollBar != NULL && m_pHorizontalScrollBar->IsVisible())
		iOffset -= m_pHorizontalScrollBar->GetFixedHeight();
	sz.cy -= iOffset;
	SetScrollPos(sz);*/
}

void CContainerUI::PageDown()
{
	/*SIZE sz = GetScrollPos();
	int iOffset = m_rcItem.bottom - m_rcItem.top - m_rcInset.top - m_rcInset.bottom;
	if (m_pHorizontalScrollBar != NULL && m_pHorizontalScrollBar->IsVisible())
		iOffset -= m_pHorizontalScrollBar->GetFixedHeight();
	sz.cy += iOffset;
	SetScrollPos(sz);*/
}

void CContainerUI::HomeUp()
{
	SIZE sz = GetScrollPos();
	sz.cy = 0;
	SetScrollPos(sz);
}

void CContainerUI::EndDown()
{
	SIZE sz = GetScrollPos();
	sz.cy = GetScrollRange().cy;
	SetScrollPos(sz);
}

void CContainerUI::LineLeft()
{
	SIZE sz = GetScrollPos();
	sz.cx -= 8;
	SetScrollPos(sz);
}

void CContainerUI::LineRight()
{
	SIZE sz = GetScrollPos();
	sz.cx += 8;
	SetScrollPos(sz);
}

void CContainerUI::PageLeft()
{
	/*SIZE sz = GetScrollPos();
	int iOffset = m_rcItem.right - m_rcItem.left - m_rcInset.left - m_rcInset.right;
	if (m_pVerticalScrollBar != NULL && m_pVerticalScrollBar->IsVisible())
		iOffset -= m_pVerticalScrollBar->GetFixedWidth();
	sz.cx -= iOffset;
	SetScrollPos(sz);*/
}

void CContainerUI::PageRight()
{
	/*SIZE sz = GetScrollPos();
	int iOffset = m_rcItem.right - m_rcItem.left - m_rcInset.left - m_rcInset.right;
	if (m_pVerticalScrollBar != NULL && m_pVerticalScrollBar->IsVisible())
		iOffset -= m_pVerticalScrollBar->GetFixedWidth();
	sz.cx += iOffset;
	SetScrollPos(sz);*/
}

void CContainerUI::HomeLeft()
{
	SIZE sz = GetScrollPos();
	sz.cx = 0;
	SetScrollPos(sz);
}

void CContainerUI::EndRight()
{
	SIZE sz = GetScrollPos();
	sz.cx = GetScrollRange().cx;
	SetScrollPos(sz);
}

void CContainerUI::EnableScrollBar(bool bEnableVertical, bool bEnableHorizontal)
{
	/*if (bEnableVertical && m_pVerticalScrollBar == NULL)
	{
		m_pVerticalScrollBar = new CScrollBarUI;
		m_pVerticalScrollBar->SetOwner(this);
		m_pVerticalScrollBar->SetManager(m_pManager, NULL, false);
		if (m_pManager != NULL)
		{
			LPCTSTR pDefaultAttributes = m_pManager->GetDefaultAttributeList(_T("VScrollBar"));
			if (pDefaultAttributes != NULL)
			{
				m_pVerticalScrollBar->ApplyAttributeList(pDefaultAttributes);
			}
		}
	}
	else if (!bEnableVertical && m_pVerticalScrollBar != NULL)
	{
		delete m_pVerticalScrollBar;
		m_pVerticalScrollBar = NULL;
	}

	if (bEnableHorizontal && m_pHorizontalScrollBar == NULL)
	{
		m_pHorizontalScrollBar = new CScrollBarUI;
		m_pHorizontalScrollBar->SetHorizontal(true);
		m_pHorizontalScrollBar->SetOwner(this);
		m_pHorizontalScrollBar->SetManager(m_pManager, NULL, false);
		if (m_pManager != NULL)
		{
			LPCTSTR pDefaultAttributes = m_pManager->GetDefaultAttributeList(_T("HScrollBar"));
			if (pDefaultAttributes != NULL)
			{
				m_pHorizontalScrollBar->ApplyAttributeList(pDefaultAttributes);
			}
		}
	}
	else if (!bEnableHorizontal && m_pHorizontalScrollBar != NULL)
	{
		delete m_pHorizontalScrollBar;
		m_pHorizontalScrollBar = NULL;
	}*/

	UpdateLayout();
}

CScrollBarUI* CContainerUI::GetVerticalScrollBar() const
{
	return m_pVerticalScrollBar;
}

CScrollBarUI* CContainerUI::GetHorizontalScrollBar() const
{
	return m_pHorizontalScrollBar;
}

void CContainerUI::ProcessScrollbar(RECT rc, int cyRequired)
{
	//// Need the scrollbar control, but it's been created already?
	//if (cyRequired > rc.bottom - rc.top && m_hwndScroll == NULL && m_bAllowScrollbars )
	//{
	//	m_hwndScroll = ::CreateWindowEx(0, WC_SCROLLBAR, NULL, WS_CHILD | SBS_VERT, 0, 0, 0, 0, m_pManager->GetPaintWindow(), NULL, m_pManager->GetResourceInstance(), NULL);
	//	ASSERT(::IsWindow(m_hwndScroll));
	//	::SetProp(m_hwndScroll, _T("WndX"), static_cast<HANDLE>(this));
	//	::SetScrollPos(m_hwndScroll, SB_CTL, 0, TRUE);
	//	::ShowWindow(m_hwndScroll, SW_SHOWNOACTIVATE);
	//	SetPos(m_rcItem);
	//	return;
	//}

	//// No scrollbar required
	//if (m_hwndScroll == NULL )
	//	return;
	//
	//// Move it into place
	////int cxScroll = m_pManager->GetSystemMetrics().cxvscroll;
	////::MoveWindow(m_hwndScroll, rc.right, rc.top, cxScroll, rc.bottom - rc.top, TRUE);
	//
	//// Scroll not needed anymore?
	//int cyScroll = cyRequired - (rc.bottom - rc.top);
	//if (cyScroll < 0)
	//{
	//	if (m_iScrollPos != 0) 
	//		SetScrollPos(0);
	//	cyScroll = 0;
	//}

	//// Scroll range changed?
	//int cyOld1, cyOld2;
	//::GetScrollRange(m_hwndScroll, SB_CTL, &cyOld1, &cyOld2);
	//if (cyOld2 != cyScroll)
	//{
	//	::SetScrollRange(m_hwndScroll, SB_CTL, 0, cyScroll, FALSE);
	//	::EnableScrollBar(m_hwndScroll, SB_CTL, cyScroll == 0 ? ESB_DISABLE_BOTH : ESB_ENABLE_BOTH);
	//}
}





/////////////////////////////////////////////////////////////////////////////////////
//
//
//
//CCanvasUI::CCanvasUI() : m_hBitmap(NULL), m_iOrientation(HTBOTTOMRIGHT)
//{
//}
//
//CCanvasUI::~CCanvasUI()
//{
//	if (m_hBitmap != NULL)
//		::DeleteObject(m_hBitmap);
//}
//
//LPCTSTR CCanvasUI::GetClass() const
//{
//	return _T("CanvasUI");
//}
//
//bool CCanvasUI::SetWatermark(UINT iBitmapRes, int iOrientation)
//{
//	return SetWatermark(MAKEINTRESOURCE(iBitmapRes), iOrientation);
//}
//
//bool CCanvasUI::SetWatermark(LPCTSTR pstrBitmap, int iOrientation)
//{
//	if (m_hBitmap != NULL)
//		::DeleteObject(m_hBitmap);
//	m_hBitmap = (HBITMAP)::LoadImage(m_pManager->GetResourceInstance(), pstrBitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
//	ASSERT(m_hBitmap!=NULL);
//	if (m_hBitmap == NULL)
//		return false;
//	::GetObject(m_hBitmap, sizeof(BITMAP), &m_BitmapInfo);
//	m_iOrientation = iOrientation;
//	Invalidate();
//	return true;
//}
//
//void CCanvasUI::DoPaint(HDC hDC, const RECT& rcPaint)
//{
//	CControlUI::DoPaint(hDC, rcPaint);
//
//	return;
//	// Fill background
//	RECT rcFill = { 0 };
//	if (::IntersectRect(&rcFill, &rcPaint, &m_rcItem))
//	{
////		CBlueRenderEngineUI::DoFillRect(hDC, m_pManager, rcFill, m_clrBack);
//	}
//
//	// Paint watermark bitmap
//	if (m_hBitmap != NULL)
//	{
//		RECT rcBitmap = { 0 };
//		switch( m_iOrientation )
//		{
//		case HTTOPRIGHT:
//			::SetRect(&rcBitmap, m_rcItem.right - m_BitmapInfo.bmWidth, m_rcItem.top, m_rcItem.right, m_rcItem.top + m_BitmapInfo.bmHeight);
//			break;
//		case HTBOTTOMRIGHT:
//			::SetRect(&rcBitmap, m_rcItem.right - m_BitmapInfo.bmWidth, m_rcItem.bottom - m_BitmapInfo.bmHeight, m_rcItem.right, m_rcItem.bottom);
//			break;
//		default:
//			::SetRect(&rcBitmap, m_rcItem.right - m_BitmapInfo.bmWidth, m_rcItem.bottom - m_BitmapInfo.bmHeight, m_rcItem.right, m_rcItem.bottom);
//			break;
//		}
//
//		RECT rcTemp = { 0 };
//		if (::IntersectRect(&rcTemp, &rcPaint, &rcBitmap))
//		{
//			CRenderClip clip;
//			//CBlueRenderEngineUI::GenerateClip(hDC, m_rcItem, clip);
//			//CBlueRenderEngineUI::DoPaintBitmap(hDC, m_pManager, m_hBitmap, rcBitmap);
//		}
//	}
//
//	CContainerUI::DoPaint(hDC, rcPaint);
//}
//
//void CCanvasUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
//{
//	if (_tcscmp(pstrName, _T("watermark")) == 0)
//		SetWatermark(pstrValue);
//	else 
//		CContainerUI::SetAttribute(pstrName, pstrValue);
//}




/////////////////////////////////////////////////////////////////////////////////////
//
//

// CWindowCanvasUI::CWindowCanvasUI()
// {
// 	//SetInset(CSize(10, 10));
// //	m_clrBack = m_pManager->GetThemeColor(UICOLOR_WINDOW_BACKGROUND);
// }
// 
// LPCTSTR CWindowCanvasUI::GetClass() const
// {
// 	return _T("WindowCanvasUI");
// }


/////////////////////////////////////////////////////////////////////////////////////
//
//

//CControlCanvasUI::CControlCanvasUI()
//{
//	SetInset(CSize(0, 0));
/////	m_clrBack = m_pManager->GetThemeColor(UICOLOR_CONTROL_BACKGROUND_NORMAL);
//}
//
//LPCTSTR CControlCanvasUI::GetClass() const
//{
//	return _T("ControlCanvasUI");
//}


/////////////////////////////////////////////////////////////////////////////////////
//
//

//CWhiteCanvasUI::CWhiteCanvasUI()
//{
//	SetInset(CSize(0, 0));
////	m_clrBack = m_pManager->GetThemeColor(UICOLOR_STANDARD_WHITE);
//}

//LPCTSTR CWhiteCanvasUI::GetClass() const
//{
//	return _T("WhiteCanvasUI");
//}


/////////////////////////////////////////////////////////////////////////////////////
//
//
// 
// CDialogCanvasUI::CDialogCanvasUI()
// {
// 	//SetInset(CSize(10, 10));
// ///	m_clrBack = m_pManager->GetThemeColor(UICOLOR_DIALOG_BACKGROUND);
// }
// 
// LPCTSTR CDialogCanvasUI::GetClass() const
// {
// 	return _T("DialogCanvasUI");
// }


/////////////////////////////////////////////////////////////////////////////////////
//
//

// CTabFolderCanvasUI::CTabFolderCanvasUI()
// {
// 	SetInset(CSize(0, 0));
// 	COLORREF clrColor1;
// //	m_pManager->GetThemeColorPair(UICOLOR_TAB_FOLDER_NORMAL, clrColor1, m_clrBack);
// }
// 
// LPCTSTR CTabFolderCanvasUI::GetClass() const
// {
// 	return _T("TabFolderCanvasUI");
// }




/////////////////////////////////////////////////////////////////////////////////////
//
//

CDialogLayoutUI::CDialogLayoutUI() : m_bFirstResize(true), m_aModes(sizeof(STRETCHMODE))
{
	::ZeroMemory(&m_rcDialog, sizeof(m_rcDialog));
}

LPCTSTR CDialogLayoutUI::GetClass() const
{
	return _T("DialogLayoutUI");
}

LPVOID CDialogLayoutUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcscmp(pstrName, _T("DialogLayout")) == 0)
		return this;
	
	return CContainerUI::GetInterface(pstrName);
}

void CDialogLayoutUI::SetStretchMode(CControlUI* pControl, UINT uMode)
{
	STRETCHMODE mode;
	mode.pControl = pControl;
	mode.uMode = uMode;
	mode.rcItem = pControl->GetPos();
	m_aModes.Add(&mode);
}

SIZE CDialogLayoutUI::EstimateSize(SIZE szAvailable)
{
	RecalcArea();
	return CSize(m_rcDialog.right - m_rcDialog.left, m_rcDialog.bottom - m_rcDialog.top);
}

void CDialogLayoutUI::SetPos(RECT rc)
{
	m_rcItem = rc;
	RecalcArea();
	
	// Do Scrollbar
	ProcessScrollbar(rc, m_rcDialog.bottom - m_rcDialog.top);
	//if (m_hwndScroll != NULL)
	//	rc.right -= m_pManager->GetSystemMetrics().cxvscroll;
	
	// Determine how "scaled" the dialog is compared to the original size
	int cxDiff = (rc.right - rc.left) - (m_rcDialog.right - m_rcDialog.left);
	int cyDiff = (rc.bottom - rc.top) - (m_rcDialog.bottom - m_rcDialog.top);
	if (cxDiff < 0)
		cxDiff = 0;
	if (cyDiff < 0)
		cyDiff = 0;
	
	// Stretch each control
	// Controls are coupled in "groups", which determine a scaling factor.
	// A "line" indicator is used to apply the same scaling to a new group of controls.
	int nCount, cxStretch, cyStretch, cxMove, cyMove;
	for (int i = 0; i < m_aModes.GetSize(); i++)
	{
		STRETCHMODE* pItem = static_cast<STRETCHMODE*>(m_aModes[i]);
		if (i == 0 || (pItem->uMode & UISTRETCH_NEWGROUP) != 0)
		{
			nCount = 0;
			for (int j = i + 1; j < m_aModes.GetSize(); j++)
			{
				STRETCHMODE* pNext = static_cast<STRETCHMODE*>(m_aModes[j]);
				if ((pNext->uMode & (UISTRETCH_NEWGROUP | UISTRETCH_NEWLINE)) != 0)
					break;
				if ((pNext->uMode & (UISTRETCH_SIZE_X | UISTRETCH_SIZE_Y)) != 0)
					nCount++;
			}

			if (nCount == 0)
				nCount = 1;
			cxStretch = cxDiff / nCount;
			cyStretch = cyDiff / nCount;
			cxMove = 0;
			cyMove = 0;
		}

		if ((pItem->uMode & UISTRETCH_NEWLINE) != 0)
		{
			cxMove = 0;
			cyMove = 0;
		}

		RECT rcPos = pItem->rcItem;
		::OffsetRect(&rcPos, rc.left, rc.top - 0);
		if ((pItem->uMode & UISTRETCH_MOVE_X) != 0)
			::OffsetRect(&rcPos, cxMove, 0);
		if ((pItem->uMode & UISTRETCH_MOVE_Y) != 0)
			::OffsetRect(&rcPos, 0, cyMove);
		if ((pItem->uMode & UISTRETCH_SIZE_X) != 0)
			rcPos.right += cxStretch;
		if ((pItem->uMode & UISTRETCH_SIZE_Y) != 0)
			rcPos.bottom += cyStretch;
		if ((pItem->uMode & (UISTRETCH_SIZE_X | UISTRETCH_SIZE_Y)) != 0 )
		{
			cxMove += cxStretch;
			cyMove += cyStretch;
		}      
		pItem->pControl->SetPos(rcPos);
	}
}

void CDialogLayoutUI::RecalcArea()
{
	if (!m_bFirstResize)
		return;
	
	// Add the remaining control to the list
	// Controls that have specific stretching needs will define them in the XML resource
	// and by calling SetStretchMode(). Other controls needs to be added as well now...
	for (int it = 0; it < m_items.GetSize(); it++)
	{         
		CControlUI* pControl = static_cast<CControlUI*>(m_items[it]);
		bool bFound = false;
		for (int i = 0; !bFound && i < m_aModes.GetSize(); i++)
		{
			if (static_cast<STRETCHMODE*>(m_aModes[i])->pControl == pControl)
				bFound = true;
		}

		if (!bFound)
		{
			STRETCHMODE mode;
			mode.pControl = pControl;
			mode.uMode = UISTRETCH_NEWGROUP;
			mode.rcItem = pControl->GetPos();
			m_aModes.Add(&mode);
		}
	}

	// Figure out the actual size of the dialog so we can add proper scrollbars later
	CRect rcDialog(9999, 9999, 0, 0);
	for (int i = 0; i < m_items.GetSize(); i++)
	{
		const RECT& rcPos = static_cast<CControlUI*>(m_items[i])->GetPos();
		rcDialog.Join(rcPos);
	}

	for (int j = 0; j < m_aModes.GetSize(); j++)
	{
		RECT& rcPos = static_cast<STRETCHMODE*>(m_aModes[j])->rcItem;
		::OffsetRect(&rcPos, -rcDialog.left, -rcDialog.top);
	}
	m_rcDialog = rcDialog;
	// We're done with initialization
	m_bFirstResize = false;
}








