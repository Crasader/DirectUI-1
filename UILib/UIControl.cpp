

#pragma once
#include "UILib.h"
#include "stdafx.h"

CControlUI::CControlUI(void) : 
	m_pManager(NULL), 
	m_pParent(NULL),
	m_chShortcut('\0'),
	m_sName(_T("")),
	m_sText(_T("")),
	m_bVisible(true), 
	m_bInternVisible(true),
	m_bEnabled(true),
	//m_bFloat(false),
	m_bMouseEnabled(true),
	m_bFocused(false),
	m_dwBackColor(0),
	m_dwBackColor2(0),
	m_dwBackColor3(0),
	m_dwBorderColor(0),
	m_dwFocusBorderColor(0),
	m_nBorderSize(0)
	//m_bColorHSL(false)
{
	m_cxyBorderRound.cx = m_cxyBorderRound.cy = 0;
	//m_cxyFixed.cx = m_cxyFixed.cy = 0;

	::ZeroMemory(&m_rcItem, sizeof(RECT));
	::ZeroMemory(&m_rcPaint, sizeof(RECT));
}

CControlUI::~CControlUI(void)
{
	if (m_pManager != NULL)
		m_pManager->ReapObjects(this);
}

CStdString CControlUI::GetName() const
{
	return m_sName;
}

void CControlUI::SetName(LPCTSTR pstrName)
{
	m_sName = pstrName;
}

LPCTSTR CControlUI::GetClass() const
{
	return _T("ControlUI");
}

LPVOID CControlUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcscmp(pstrName, _T("Control")) == 0)
		return this;

	return NULL;
}

UINT CControlUI::GetControlFlags() const
{
	return 0;
}

bool CControlUI::Activate()
{
	if (!IsVisible())
		return false;
	if (!IsEnabled())
		return false;

	return true;
}

CPaintManagerUI* CControlUI::GetManager() const
{
	return m_pManager;
}

void CControlUI::SetManager(CPaintManagerUI* pManager, CControlUI* pParent)
{
	bool bInit = m_pManager == NULL;

	m_pManager = pManager;
	m_pParent = pParent;

	if (bInit && m_pParent != NULL)
		Init();
}

CControlUI* CControlUI::GetParent() const
{
	return m_pParent;
}

CStdString CControlUI::GetText() const
{
	return m_sText;
}

void CControlUI::SetText(LPCTSTR pstrText)
{
	if (m_sText == pstrText)
		return;

	m_sText = pstrText;
	Invalidate();
}

DWORD CControlUI::GetBkColor() const
{
	return m_dwBackColor;
}

void CControlUI::SetBkColor(DWORD dwBackColor)
{
	if (m_dwBackColor == dwBackColor)
		return;

	m_dwBackColor = dwBackColor;
	Invalidate();
}

DWORD CControlUI::GetBkColor2() const
{
	return m_dwBackColor2;
}

void CControlUI::SetBkColor2(DWORD dwBackColor)
{
	if (m_dwBackColor2 == dwBackColor)
		return;

	m_dwBackColor2 = dwBackColor;
	Invalidate();
}

DWORD CControlUI::GetBkColor3() const
{
	return m_dwBackColor3;
}

void CControlUI::SetBkColor3(DWORD dwBackColor)
{
	if (m_dwBackColor3 == dwBackColor)
		return;

	m_dwBackColor3 = dwBackColor;
	Invalidate();
}

LPCTSTR CControlUI::GetBkImage()
{
	return m_sBkImage;
}

void CControlUI::SetBkImage(LPCTSTR pStrImage)
{
	if (m_sBkImage == pStrImage)
		return;

	m_sBkImage = pStrImage;
	Invalidate();
}

DWORD CControlUI::GetBorderColor() const
{
	return m_dwBorderColor;
}

void CControlUI::SetBorderColor(DWORD dwBorderColor)
{
	if (m_dwBorderColor == dwBorderColor)
		return;

	m_dwBorderColor = dwBorderColor;
	Invalidate();
}

DWORD CControlUI::GetFocusBorderColor() const
{
	return m_dwFocusBorderColor;
}

void CControlUI::SetFocusBorderColor(DWORD dwBorderColor)
{
	if (m_dwFocusBorderColor == dwBorderColor)
		return;

	m_dwFocusBorderColor = dwBorderColor;
	Invalidate();
}

//bool CControlUI::IsColorHSL() const
//{
//	return m_bColorHSL;
//}
//
//void CControlUI::SetColorHSL(bool bColorHSL)
//{
//	if (m_bColorHSL == bColorHSL)
//		return;
//
//	m_bColorHSL = bColorHSL;
//	Invalidate();
//}

SIZE CControlUI::GetBorderRound() const
{
	return m_cxyBorderRound;
}

void CControlUI::SetBorderRound(SIZE cxyRound)
{
	m_cxyBorderRound = cxyRound;
	Invalidate();
}

bool CControlUI::DrawImage(HDC hDC, LPCTSTR pStrImage, LPCTSTR pStrModify)
{
	return CRenderEngine::DrawImageString(hDC, m_pManager, m_rcItem, m_rcPaint, pStrImage, pStrModify);
}

int CControlUI::GetBorderSize() const
{
	return m_nBorderSize;
}

void CControlUI::SetBorderSize(int nSize)
{
	if (m_nBorderSize == nSize)
		return;

	m_nBorderSize = nSize;
	Invalidate();
}
//
//void CControlUI::SetBorderSize( RECT rc )
//{
//	m_rcBorderSize = rc;
//	Invalidate();
//}
//
//int CControlUI::GetLeftBorderSize() const
//{
//	return m_rcBorderSize.left;
//}
//
//void CControlUI::SetLeftBorderSize( int nSize )
//{
//	m_rcBorderSize.left = nSize;
//	Invalidate();
//}
//
//int CControlUI::GetTopBorderSize() const
//{
//	return m_rcBorderSize.top;
//}
//
//void CControlUI::SetTopBorderSize( int nSize )
//{
//	m_rcBorderSize.top = nSize;
//	Invalidate();
//}
//
//int CControlUI::GetRightBorderSize() const
//{
//	return m_rcBorderSize.right;
//}
//
//void CControlUI::SetRightBorderSize( int nSize )
//{
//	m_rcBorderSize.right = nSize;
//	Invalidate();
//}
//
//int CControlUI::GetBottomBorderSize() const
//{
//	return m_rcBorderSize.bottom;
//}
//
//void CControlUI::SetBottomBorderSize( int nSize )
//{
//	m_rcBorderSize.bottom = nSize;
//	Invalidate();
//}
//
//int CControlUI::GetBorderStyle() const
//{
//	return m_nBorderStyle;
//}
//void CControlUI::SetBorderStyle( int nStyle )
//{
//	m_nBorderStyle = nStyle;
//	Invalidate();
//}

RECT CControlUI::GetPos() const
{
	return m_rcItem;
}

void CControlUI::SetPos(RECT rc)
{
	m_rcItem = rc;
	// NOTE: SetPos() is usually called during the WM_PAINT cycle where all controls are
	//       being laid out. Calling UpdateLayout() again would be wrong. Refreshing the
	//       window won't hurt (if we're already inside WM_PAINT we'll just validate it out).
	Invalidate();
}

RECT CControlUI::GetPadding() const
{
	return m_rcPadding;
}

void CControlUI::SetPadding(RECT rcPadding)
{
	m_rcPadding = rcPadding;
	ParentUpdateLayout();
}

//SIZE CControlUI::GetFixedXY() const
//{
//	return m_cXY;
//}
//
//void CControlUI::SetFixedXY(SIZE szXY)
//{
//	m_cXY.cx = szXY.cx;
//	m_cXY.cy = szXY.cy;
//
//	if (!m_bFloat)
//		ParentUpdateLayout();
//	else
//		UpdateLayout();
//}
//
//int CControlUI::GetFixedWidth() const
//{
//	return m_cxyFixed.cx;
//}
//
//void CControlUI::SetFixedWidth(int cx)
//{
//	if (cx < 0)
//		return; 
//	m_cxyFixed.cx = cx;
//	if (!m_bFloat)
//		ParentUpdateLayout();
//	else
//		UpdateLayout();
//}
//
//int CControlUI::GetFixedHeight() const
//{
//	return m_cxyFixed.cy;
//}
//
//void CControlUI::SetFixedHeight(int cy)
//{
//	if (cy < 0)
//		return; 
//	m_cxyFixed.cy = cy;
//	if (!m_bFloat)
//		ParentUpdateLayout();
//	else
//		UpdateLayout();
//}
//
//int CControlUI::GetMinWidth() const
//{
//	return m_cxyMin.cx;
//}
//
//void CControlUI::SetMinWidth(int cx)
//{
//	if (m_cxyMin.cx == cx)
//		return;
//
//	if (cx < 0)
//		return; 
//	
//	m_cxyMin.cx = cx;
//	if (!m_bFloat)
//		ParentUpdateLayout();
//	else
//		UpdateLayout();
//}
//
//int CControlUI::GetMaxWidth() const
//{
//	return m_cxyMax.cx;
//}
//
//void CControlUI::SetMaxWidth(int cx)
//{
//	if (m_cxyMax.cx == cx)
//		return;
//
//	if (cx < 0)
//		return; 
//	
//	m_cxyMax.cx = cx;
//	if (!m_bFloat)
//		ParentUpdateLayout();
//	else
//		UpdateLayout();
//}
//
//int CControlUI::GetMinHeight() const
//{
//	return m_cxyMin.cy;
//}
//
//void CControlUI::SetMinHeight(int cy)
//{
//	if (m_cxyMin.cy == cy)
//		return;
//
//	if (cy < 0)
//		return; 
//	
//	m_cxyMin.cy = cy;
//	if (!m_bFloat) 
//		ParentUpdateLayout();
//	else 
//		UpdateLayout();
//}
//
//int CControlUI::GetMaxHeight() const
//{
//	return m_cxyMax.cy;
//}
//
//void CControlUI::SetMaxHeight(int cy)
//{
//	if (m_cxyMax.cy == cy)
//		return;
//
//	if (cy < 0)
//		return; 
//
//	m_cxyMax.cy = cy;
//	if (!m_bFloat)
//		ParentUpdateLayout();
//	else
//		UpdateLayout();
//}
//
//void CControlUI::SetRelativePos(SIZE szMove,SIZE szZoom)
//{
//	m_tRelativePos.bRelative = TRUE;
//	m_tRelativePos.nMoveXPercent = szMove.cx;
//	m_tRelativePos.nMoveYPercent = szMove.cy;
//	m_tRelativePos.nZoomXPercent = szZoom.cx;
//	m_tRelativePos.nZoomYPercent = szZoom.cy;
//}
//
//void CControlUI::SetRelativeParentSize(SIZE sz)
//{
//	m_tRelativePos.szParent = sz;
//}
//
//TRelativePosUI CControlUI::GetRelativePos() const
//{
//	return m_tRelativePos;
//}
//
//bool CControlUI::IsRelativePos() const
//{
//	return m_tRelativePos.bRelative;
//}

CStdString CControlUI::GetToolTip() const
{
	return m_sToolTip;
}

void CControlUI::SetToolTip(LPCTSTR pstrText)
{
	m_sToolTip = pstrText;
}

TCHAR CControlUI::GetShortcut() const
{
	return m_chShortcut;
}

void CControlUI::SetShortcut(TCHAR ch)
{
	m_chShortcut = ch;
}

bool CControlUI::IsVisible() const
{
	return m_bVisible;
}

bool CControlUI::IsEnabled() const
{
	return m_bEnabled;
}

bool CControlUI::IsMouseEnabled() const
{
	return m_bMouseEnabled;
}

bool CControlUI::IsFocused() const
{
	return m_bFocused;
}

void CControlUI::SetVisible(bool bVisible)
{
	if (m_bVisible == bVisible)
		return;

	m_bVisible = bVisible;
	if (m_pManager != NULL)
		m_pManager->UpdateLayout();
}

void CControlUI::SetInternVisible(bool bVisible)
{
	m_bInternVisible = bVisible;
	if (!bVisible && m_pManager != NULL && m_pManager->GetFocus() == this)
	{
		m_pManager->SetFocus(NULL) ;
	}
}

void CControlUI::SetEnabled(bool bEnabled)
{
	m_bEnabled = bEnabled;
	Invalidate();
}

void CControlUI::SetFocus()
{
	if (m_pManager != NULL)
		m_pManager->SetFocus(this);
}

//bool CControlUI::IsFloat() const
//{
//	return m_bFloat;
//}
//
//void CControlUI::SetFloat(bool bFloat)
//{
//	if (m_bFloat == bFloat)
//		return;
//
//	m_bFloat = bFloat;
//	ParentUpdateLayout();
//}

CControlUI* CControlUI::FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags)
{
	if ((uFlags & UIFIND_VISIBLE) != 0 && !IsVisible())
		return NULL;
	if ((uFlags & UIFIND_ENABLED) != 0 && !IsEnabled() )
		return NULL;
	if ((uFlags & UIFIND_HITTEST) != 0 && !::PtInRect(&m_rcItem, * static_cast<LPPOINT>(pData)))
		return NULL;

	return Proc(this, pData);
}

void CControlUI::Invalidate()
{
	if (m_pManager != NULL)
		m_pManager->Invalidate(m_rcItem);
}

void CControlUI::UpdateLayout()
{
	if (m_pManager != NULL)
		m_pManager->UpdateLayout();
}

void CControlUI::ParentUpdateLayout()
{
	if (GetParent() != NULL)
	{
		GetParent()->UpdateLayout();
		GetParent()->Invalidate();
	}
	else
	{
		UpdateLayout();
	}

	if (m_pManager != NULL)
		m_pManager->UpdateLayout();
}

//DWORD CControlUI::GetAdjustColor(DWORD dwColor)
//{
//	if (!m_bColorHSL)
//		return dwColor;
//	short H, S, L;
//	CPaintManagerUI::GetHSL(&H, &S, &L);
//	return CRenderEngine::AdjustColor(dwColor, H, S, L);
//}

void CControlUI::Init()
{
}

void CControlUI::Event(TEventUI& event)
{
	if (event.Type == UIEVENT_SETCURSOR)
	{
		::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
		return;
	}
	if (event.Type == UIEVENT_SETFOCUS) 
	{
		m_bFocused = true;
		Invalidate();
		return;
	}
	if (event.Type == UIEVENT_KILLFOCUS)
	{
		m_bFocused = false;
		Invalidate();
		return;
	}
	if (event.Type == UIEVENT_TIMER)
	{
		m_pManager->SendNotify(this, _T("timer"), event.wParam, event.lParam);
		return;
	}
	if (m_pParent != NULL)
		m_pParent->Event(event);
}

void CControlUI::Notify(TNotifyUI& /*msg*/)
{
}

void CControlUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcscmp(pstrName, _T("pos")) == 0)
	{
		RECT rcPos = { 0 };
		LPTSTR pstr = NULL;
		rcPos.left = _tcstol(pstrValue, &pstr, 10);
		ASSERT(pstr);
		rcPos.top = _tcstol(pstr + 1, &pstr, 10);
		ASSERT(pstr);
		rcPos.right = _tcstol(pstr + 1, &pstr, 10);
		ASSERT(pstr);
		rcPos.bottom = _tcstol(pstr + 1, &pstr, 10);
		ASSERT(pstr);
		SetPos(rcPos);
	}
	else if (_tcscmp(pstrName, _T("name")) == 0)
		SetName(pstrValue);
	else if (_tcscmp(pstrName, _T("text")) == 0)
		SetText(pstrValue);
	else if (_tcscmp(pstrName, _T("tooltip")) == 0)
		SetToolTip(pstrValue);
	else if (_tcscmp(pstrName, _T("enabled")) == 0)
		SetEnabled(_tcscmp(pstrValue, _T("true")) == 0);
	else if (_tcscmp(pstrName, _T("visible")) == 0)
		SetVisible(_tcscmp(pstrValue, _T("true")) == 0);
	else if (_tcscmp(pstrName, _T("shortcut")) == 0)
		SetShortcut(pstrValue[0]);
}

CControlUI* CControlUI::ApplyAttributeList(LPCTSTR pstrList)
{
	CStdString sItem;
	CStdString sValue;
	while (*pstrList != '\0')
	{
		sItem.Empty();
		sValue.Empty();
		while (*pstrList != '\0' && *pstrList != '=')
			sItem += *pstrList++;
		ASSERT(*pstrList=='=');
		if (*pstrList++ != '=')
			return this;
		ASSERT(*pstrList=='\"');
		if (*pstrList++ != '\"')
			return this;
		while (*pstrList != '\0' && *pstrList != '\"')
			sValue += *pstrList++;
		ASSERT(*pstrList=='\"');
		if (*pstrList++ != '\"')
			return this;
		SetAttribute(sItem, sValue);
		if (*pstrList++ != ',')
			return this;
	}
	return this;
}

//SIZE CControlUI::EstimateSize(SIZE szAvailable)
//{
//	return 0;//m_cxyFixed;
//}

void CControlUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
	if (!::IntersectRect(&m_rcPaint, &rcPaint, &m_rcItem))
		return;

	// »æÖÆÑ­Ðò£º±³¾°ÑÕÉ«->±³¾°Í¼->×´Ì¬Í¼->ÎÄ±¾->±ß¿ò
	/*if (m_cxyBorderRound.cx > 0 || m_cxyBorderRound.cy > 0)
	{
		CRenderClip roundClip;
		CRenderClip::GenerateRoundClip(hDC, m_rcPaint,  m_rcItem, m_cxyBorderRound.cx, m_cxyBorderRound.cy, roundClip);
		PaintBkColor(hDC);
 		PaintBkImage(hDC);
 		PaintStatusImage(hDC);
 		PaintText(hDC);
 		PaintBorder(hDC);
	}
	else */
	{
		PaintBkColor(hDC);
 		PaintBkImage(hDC);
 		PaintStatusImage(hDC);
 		PaintText(hDC);
 		PaintBorder(hDC);
	}
}

void CControlUI::PaintBkColor(HDC hDC)
{
	if (m_dwBackColor != 0) 
	{
		if (m_dwBackColor2 != 0)
		{
			if (m_dwBackColor3 != 0)
			{
				RECT rc = m_rcItem;
				rc.bottom = (rc.bottom + rc.top) / 2;
				CRenderEngine::DrawGradient(hDC, rc, m_dwBackColor, m_dwBackColor2, true, 8);
				rc.top = rc.bottom;
				rc.bottom = m_rcItem.bottom;
				CRenderEngine::DrawGradient(hDC, rc, m_dwBackColor2, m_dwBackColor3, true, 8);
			}
			else 
				CRenderEngine::DrawGradient(hDC, m_rcItem, m_dwBackColor, m_dwBackColor2, true, 16);
		}
		else if (m_dwBackColor >= 0xFF000000)
			CRenderEngine::DrawColor(hDC, m_rcPaint, m_dwBackColor);
		else
			CRenderEngine::DrawColor(hDC, m_rcItem, m_dwBackColor);
	}
}

void CControlUI::PaintBkImage(HDC hDC)
{
	if (m_sBkImage.IsEmpty())
		return;
	if (!DrawImage(hDC, (LPCTSTR)m_sBkImage))
		m_sBkImage.Empty();
}

void CControlUI::PaintStatusImage(HDC hDC)
{
	return;
}

void CControlUI::PaintText(HDC hDC)
{
	return;
}

void CControlUI::PaintBorder(HDC hDC)
{
	if (m_dwBorderColor != 0 || m_dwFocusBorderColor != 0)
	{
		if ( m_nBorderSize > 0 && ( m_cxyBorderRound.cx > 0 || m_cxyBorderRound.cy > 0) )//»­Ô²½Ç±ß¿ò
		{
			if (IsFocused() && m_dwFocusBorderColor != 0)
				CRenderEngine::DrawRoundRect(hDC, m_rcItem, m_nBorderSize, m_cxyBorderRound.cx, m_cxyBorderRound.cy, m_dwFocusBorderColor);
			else
				CRenderEngine::DrawRoundRect(hDC, m_rcItem, m_nBorderSize, m_cxyBorderRound.cx, m_cxyBorderRound.cy, m_dwBorderColor);
		}
		else
		{
			if (IsFocused() && m_dwFocusBorderColor != 0 && m_nBorderSize > 0)
				CRenderEngine::DrawRect(hDC, m_rcItem, m_nBorderSize, m_dwFocusBorderColor);
			else if(m_nBorderSize > 0)
				CRenderEngine::DrawRect(hDC, m_rcItem, m_nBorderSize, m_dwBorderColor);
		}
	}
}

