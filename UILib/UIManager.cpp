#pragma once
#include "UILib.h"
#include "StdAfx.h"

DECLARE_HANDLE(HZIP);	// An HZIP identifies a zip file that has been opened
typedef DWORD ZRESULT;
#define OpenZip OpenZipU
#define CloseZip(hz) CloseZipU(hz)
extern HZIP OpenZipU(void *z,unsigned int len,DWORD flags);
extern ZRESULT CloseZipU(HZIP hz);


/////////////////////////////////////////////////////////////////////////////////////
//
//

static UINT GetNameHash(LPCTSTR pstrName)
{
	UINT i = 0;
	SIZE_T len = _tcslen(pstrName);
	while (len-- > 0)
		i = (i << 5) + i + pstrName[len];
	return i;
}

static UINT MapKeyState()
{
	UINT uState = 0;
	if (::GetKeyState(VK_CONTROL) < 0)
		uState |= MK_CONTROL;
	if (::GetKeyState(VK_RBUTTON) < 0)
		uState |= MK_LBUTTON;
	if (::GetKeyState(VK_LBUTTON) < 0)
		uState |= MK_RBUTTON;
	if (::GetKeyState(VK_SHIFT) < 0)
		uState |= MK_SHIFT;
	if (::GetKeyState(VK_MENU) < 0)
		uState |= MK_ALT;
	return uState;
}


/////////////////////////////////////////////////////////////////////////////////////
//

//#define IDB_ICONS16 200
//#define IDB_ICONS24 201
//#define IDB_ICONS32 202
//#define IDB_ICONS50 203

typedef struct tagFINDTABINFO
{
	CControlUI* pFocus;
	CControlUI* pLast;
	bool bForward;
	bool bNextIsIt;
} FINDTABINFO;

typedef struct tagFINDSHORTCUT
{
	TCHAR ch;
	bool bPickNext;
} FINDSHORTCUT;

typedef struct tagTIMERINFO
{
	CControlUI* pSender;
	UINT nLocalID;
	HWND hWnd;
	UINT uWinTimer;
} TIMERINFO;


/////////////////////////////////////////////////////////////////////////////////////
//

//CAnimationSpooler m_anim;
//HPEN g_hPens[UICOLOR__LAST] = { 0 };
//HFONT g_hFonts[UIFONT__LAST] = { 0 };
//HBRUSH g_hBrushes[UICOLOR__LAST] = { 0 };
//LOGFONT g_aLogFonts[UIFONT__LAST] = { 0 };
//COLORREF g_clrColors[UICOLOR__LAST][2] = { 0 };
//TEXTMETRIC g_aTextMetrics[UIFONT__LAST] = { 0 };
//HIMAGELIST g_himgIcons16 = NULL;
//HIMAGELIST g_himgIcons24 = NULL;
//HIMAGELIST g_himgIcons32 = NULL;
//HIMAGELIST g_himgIcons50 = NULL;



/////////////////////////////////////////////////////////////////////////////////////////////////
//

HINSTANCE CPaintManagerUI::m_hInstance = NULL;
HINSTANCE CPaintManagerUI::m_hLangInst = NULL;
HINSTANCE CPaintManagerUI::m_hResourceInstance = NULL;
CStdPtrArray CPaintManagerUI::m_aPreMessages;
CStdString CPaintManagerUI::m_pStrResourcePath;
CStdString CPaintManagerUI::m_pStrResourceZip;
bool CPaintManagerUI::m_bCachedResourceZip = false;
HANDLE CPaintManagerUI::m_hResourceZip = NULL;
//short CPaintManagerUI::m_H = 180;
//short CPaintManagerUI::m_S = 100;
//short CPaintManagerUI::m_L = 100;

CPaintManagerUI::CPaintManagerUI(void):
	m_hWndPaint(NULL),
	m_hDcPaint(NULL),
	m_hDcOffscreen(NULL),
	m_hbmpOffscreen(NULL),
	m_uTimerID(0x1000),
	m_pRoot(NULL),
	m_pFocus(NULL),
	m_pEventHover(NULL),
	m_pEventClick(NULL),
	m_pEventKey(NULL),
	m_hWndTooltip(NULL),
	m_nAlpha(255),
	m_bFirstLayout(true),
	m_bFocusNeeded(false),
	m_bResizeNeeded(false),
	m_bMouseTracking(false),
	m_bOffscreenPaint(true),
	m_pParentResourcePM(NULL)
{
	m_dwDefaultDisabledColor = 0xFFA7A6AA;
	m_dwDefaultFontColor = 0xFF000000;
	m_dwDefaultLinkFontColor = 0xFF0000FF;
	m_dwDefaultLinkHoverFontColor = 0xFFD3215F;
	m_dwDefaultSelectedBkColor = 0xFFBAE4FF;
	LOGFONT lf = { 0 };
	::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	lf.lfCharSet = DEFAULT_CHARSET;
	//if (CPaintManagerUI::m_pStrDefaultFontName.GetLength()>0)
	//{
	//	_tcscpy_s(lf.lfFaceName, LF_FACESIZE, CPaintManagerUI::m_pStrDefaultFontName.GetData());
	//}
	HFONT hDefaultFont = ::CreateFontIndirect(&lf);
	m_DefaultFontInfo.hFont = hDefaultFont;
	m_DefaultFontInfo.sFontName = lf.lfFaceName;
	m_DefaultFontInfo.iSize = -lf.lfHeight;
	m_DefaultFontInfo.bBold = (lf.lfWeight >= FW_BOLD);
	m_DefaultFontInfo.bUnderline = (lf.lfUnderline == TRUE);
	m_DefaultFontInfo.bItalic = (lf.lfItalic == TRUE);
	::ZeroMemory(&m_DefaultFontInfo.tm, sizeof(m_DefaultFontInfo.tm));

	//if (g_hFonts[1] == NULL) 
	//{
	//	// Fill in default font information
	//	LOGFONT lf = { 0 };
	//	::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	//	_tcscpy(lf.lfFaceName, _T("Tahoma"));
	//	// TODO: Handle "large fonts" or other font sizes when
	//	//       screen resolution changes!!!
	//	lf.lfHeight = -12;
	//	g_aLogFonts[UIFONT_NORMAL] = lf;
	//	g_aLogFonts[UIFONT_CAPTION] = lf;
	//	LOGFONT lfBold = lf;
	//	lfBold.lfWeight += FW_BOLD;
	//	g_aLogFonts[UIFONT_BOLD] = lfBold;
	//	lfBold.lfHeight -= 2;
	//	g_aLogFonts[UIFONT_TITLE] = lfBold;
	//	lfBold.lfHeight -= 4;
	//	g_aLogFonts[UIFONT_HEADLINE] = lfBold;
	//	LOGFONT lfSubscript = lf;
	//	lfSubscript.lfHeight -= 4;
	//	g_aLogFonts[UIFONT_SUBSCRIPT] = lfSubscript;
	//	LOGFONT lfLink = lf;
	//	lfLink.lfUnderline = TRUE;
	//	g_aLogFonts[UIFONT_LINK] = lfLink;

	//	// Fill the color table
	//	g_clrColors[UICOLOR_WINDOW_BACKGROUND][0]            = RGB(239,239,235);
	//	g_clrColors[UICOLOR_DIALOG_BACKGROUND][0]            = RGB(238,238,238);
	//	g_clrColors[UICOLOR_DIALOG_TEXT_NORMAL][0]           = RGB(0,0,0);
	//	g_clrColors[UICOLOR_DIALOG_TEXT_DARK][0]             = RGB(96,96,80);
	//	g_clrColors[UICOLOR_TITLE_BACKGROUND][0]             = RGB(114,136,172);
	//	g_clrColors[UICOLOR_TITLE_TEXT][0]                   = RGB(255,255,255);
	//	g_clrColors[UICOLOR_TITLE_BORDER_LIGHT][0]           = RGB(171,192,231);
	//	g_clrColors[UICOLOR_TITLE_BORDER_DARK][0]            = RGB(0,55,122);
	//	g_clrColors[UICOLOR_BUTTON_BACKGROUND_NORMAL][0]     = RGB(250,250,252);
	//	g_clrColors[UICOLOR_BUTTON_BACKGROUND_NORMAL][1]     = RGB(215,215,227);
	//	g_clrColors[UICOLOR_BUTTON_BACKGROUND_DISABLED][0]   = RGB(248,248,248);
	//	g_clrColors[UICOLOR_BUTTON_BACKGROUND_DISABLED][1]	 = RGB(214,214,214);
	//	g_clrColors[UICOLOR_BUTTON_BACKGROUND_PUSHED][0]     = RGB(215,215,227);
	//	g_clrColors[UICOLOR_BUTTON_BACKGROUND_PUSHED][1]     = RGB(250,250,252);
	//	g_clrColors[UICOLOR_BUTTON_TEXT_NORMAL][0]           = RGB(0,0,0);
	//	g_clrColors[UICOLOR_BUTTON_TEXT_PUSHED][0]           = RGB(0,0,20);
	//	g_clrColors[UICOLOR_BUTTON_TEXT_DISABLED][0]         = RGB(204,204,204);
	//	g_clrColors[UICOLOR_BUTTON_BORDER_LIGHT][0]          = RGB(123,158,189);
	//	g_clrColors[UICOLOR_BUTTON_BORDER_DARK][0]           = RGB(123,158,189);
	//	g_clrColors[UICOLOR_BUTTON_BORDER_DISABLED][0]       = RGB(204,204,204);
	//	g_clrColors[UICOLOR_BUTTON_BORDER_FOCUS][0]          = RGB(140,140,140);
	//	g_clrColors[UICOLOR_TOOL_BACKGROUND_NORMAL][0]       = RGB(114,136,172);
	//	g_clrColors[UICOLOR_TOOL_BACKGROUND_DISABLED][0]     = RGB(100,121,156);
	//	g_clrColors[UICOLOR_TOOL_BACKGROUND_HOVER][0]        = RGB(100,121,156);
	//	g_clrColors[UICOLOR_TOOL_BACKGROUND_PUSHED][0]       = RGB(80,101,136);
	//	g_clrColors[UICOLOR_TOOL_BORDER_NORMAL][0]           = RGB(0,55,122);
	//	g_clrColors[UICOLOR_TOOL_BORDER_DISABLED][0]         = RGB(0,55,122);
	//	g_clrColors[UICOLOR_TOOL_BORDER_HOVER][0]            = RGB(0,55,122);
	//	g_clrColors[UICOLOR_TOOL_BORDER_PUSHED][0]           = RGB(0,55,122);
	//	g_clrColors[UICOLOR_EDIT_BACKGROUND_DISABLED][0]     = RGB(255,251,255);
	//	g_clrColors[UICOLOR_EDIT_BACKGROUND_READONLY][0]     = RGB(255,251,255);
	//	g_clrColors[UICOLOR_EDIT_BACKGROUND_NORMAL][0]       = RGB(255,255,255);
	//	g_clrColors[UICOLOR_EDIT_BACKGROUND_HOVER][0]        = RGB(255,251,255);
	//	g_clrColors[UICOLOR_EDIT_TEXT_NORMAL][0]             = RGB(0,0,0);
	//	g_clrColors[UICOLOR_EDIT_TEXT_DISABLED][0]           = RGB(167,166,170);
	//	g_clrColors[UICOLOR_EDIT_TEXT_READONLY][0]           = RGB(167,166,170);      
	//	g_clrColors[UICOLOR_NAVIGATOR_BACKGROUND][0]         = RGB(229,217,213);
	//	g_clrColors[UICOLOR_NAVIGATOR_BACKGROUND][1]         = RGB(201,199,187);
	//	g_clrColors[UICOLOR_NAVIGATOR_TEXT_NORMAL][0]        = RGB(102,102,102);
	//	g_clrColors[UICOLOR_NAVIGATOR_TEXT_SELECTED][0]      = RGB(0,0,0);
	//	g_clrColors[UICOLOR_NAVIGATOR_TEXT_PUSHED][0]        = RGB(0,0,0);       
	//	g_clrColors[UICOLOR_NAVIGATOR_BORDER_NORMAL][0]      = RGB(131,133,116);
	//	g_clrColors[UICOLOR_NAVIGATOR_BORDER_SELECTED][0]    = RGB(159,160,144);
	//	g_clrColors[UICOLOR_NAVIGATOR_BUTTON_HOVER][0]       = RGB(200,200,200);
	//	g_clrColors[UICOLOR_NAVIGATOR_BUTTON_PUSHED][0]      = RGB(184,184,183);
	//	g_clrColors[UICOLOR_NAVIGATOR_BUTTON_SELECTED][0]    = RGB(238,238,238);
	//	g_clrColors[UICOLOR_TAB_BACKGROUND_NORMAL][0]        = RGB(255,251,255);
	//	g_clrColors[UICOLOR_TAB_FOLDER_NORMAL][0]            = RGB(255,251,255);
	//	g_clrColors[UICOLOR_TAB_FOLDER_NORMAL][1]            = RGB(233,231,215);
	//	g_clrColors[UICOLOR_TAB_FOLDER_SELECTED][0]          = RGB(255,251,255);
	//	g_clrColors[UICOLOR_TAB_BORDER][0]                   = RGB(148,166,181);
	//	g_clrColors[UICOLOR_TAB_TEXT_NORMAL][0]              = RGB(0,0,0);
	//	g_clrColors[UICOLOR_TAB_TEXT_SELECTED][0]            = RGB(0,0,0);
	//	g_clrColors[UICOLOR_TAB_TEXT_DISABLED][0]            = RGB(0,0,0);      
	//	g_clrColors[UICOLOR_HEADER_BACKGROUND][0]            = RGB(233,231,215);
	//	g_clrColors[UICOLOR_HEADER_BACKGROUND][1]            = RGB(150,150,147);
	//	g_clrColors[UICOLOR_HEADER_BORDER][0]                = RGB(218,219,201);
	//	g_clrColors[UICOLOR_HEADER_SEPARATOR][0]             = RGB(197,193,177);
	//	g_clrColors[UICOLOR_HEADER_TEXT][0]                  = RGB(0,0,0);
	//	g_clrColors[UICOLOR_TASK_BACKGROUND][0]              = RGB(230,243,255);
	//	g_clrColors[UICOLOR_TASK_BACKGROUND][1]              = RGB(255,255,255);
	//	g_clrColors[UICOLOR_TASK_BORDER][0]                  = RGB(140,158,198);
	//	g_clrColors[UICOLOR_TASK_CAPTION][0]                 = RGB(140,158,198);
	//	g_clrColors[UICOLOR_TASK_TEXT][0]                    = RGB(65,65,110);
	//	g_clrColors[UICOLOR_LINK_TEXT_NORMAL][0]             = RGB(0,0,255);
	//	g_clrColors[UICOLOR_LINK_TEXT_HOVER][0]              = RGB(0,0,100);
	//	g_clrColors[UICOLOR_CONTROL_BACKGROUND_NORMAL][0]    = RGB(255,255,255);
	//	g_clrColors[UICOLOR_CONTROL_BACKGROUND_SELECTED][0]  = RGB(173,195,231);
	//	g_clrColors[UICOLOR_CONTROL_BACKGROUND_READONLY][0]  = RGB(255,255,255);
	//	g_clrColors[UICOLOR_CONTROL_BACKGROUND_DISABLED][0]  = RGB(255,255,255);
	//	g_clrColors[UICOLOR_CONTROL_BACKGROUND_HOVER][0]     = RGB(233,245,255);
	//	g_clrColors[UICOLOR_CONTROL_BACKGROUND_SORTED][0]    = RGB(242,242,246);
	//	g_clrColors[UICOLOR_CONTROL_BACKGROUND_EXPANDED][0]  = RGB(255,255,255);
	//	g_clrColors[UICOLOR_CONTROL_BACKGROUND_EXPANDED][1]  = RGB(236,242,255);
	//	g_clrColors[UICOLOR_CONTROL_BORDER_NORMAL][0]        = RGB(123,158,189);
	//	g_clrColors[UICOLOR_CONTROL_BORDER_SELECTED][0]      = RGB(123,158,189);
	//	g_clrColors[UICOLOR_CONTROL_BORDER_DISABLED][0]      = RGB(204,204,204);
	//	g_clrColors[UICOLOR_CONTROL_TEXT_NORMAL][0]          = RGB(0,0,0);
	//	g_clrColors[UICOLOR_CONTROL_TEXT_SELECTED][0]        = RGB(0,0,0);
	//	g_clrColors[UICOLOR_CONTROL_TEXT_DISABLED][0]        = RGB(204,204,204);
	//	g_clrColors[UICOLOR_STANDARD_BLACK][0]               = RGB(0,0,0);
	//	g_clrColors[UICOLOR_STANDARD_YELLOW][0]              = RGB(255,255,204);
	//	g_clrColors[UICOLOR_STANDARD_RED][0]                 = RGB(255,204,204);
	//	g_clrColors[UICOLOR_STANDARD_GREY][0]                = RGB(145,146,119);
	//	g_clrColors[UICOLOR_STANDARD_LIGHTGREY][0]           = RGB(195,196,179);
	//	g_clrColors[UICOLOR_STANDARD_WHITE][0]               = RGB(255,255,255);

	//	// Boot Windows Common Controls (for the ToolTip control)
	//	::InitCommonControls();

	//	// We need the image library for effects. It is however optional in Windows so
	//	// we'll also need to provide a gracefull fallback.
	//	::LoadLibrary(_T("msimg32.dll"));
	//}
	m_szMinWindow.cx = 140;
	m_szMinWindow.cy = 200;
	m_ptLastMousePos.x = m_ptLastMousePos.y = -1;
	m_szRoundCorner.cx = m_szRoundCorner.cy = 0;
	::ZeroMemory(&m_rcSizeBox, sizeof(m_rcSizeBox));
	::ZeroMemory(&m_rcCaption, sizeof(m_rcCaption));
}

CPaintManagerUI::~CPaintManagerUI(void)
{
	// Delete the control-tree structures
	int i;
	for (i = 0; i < m_aDelayedCleanup.GetSize(); i++)
		delete static_cast<CControlUI*>(m_aDelayedCleanup[i]);
	
	delete m_pRoot;
	m_pRoot = NULL;

	::DeleteObject(m_DefaultFontInfo.hFont);
	RemoveAllFonts();
	
	// Release other collections
	for (i = 0; i < m_aTimers.GetSize(); i++)
		delete static_cast<TIMERINFO*>(m_aTimers[i]);
	
	// Reset other parts...
	if (m_hWndTooltip != NULL )
		::DestroyWindow(m_hWndTooltip);
	if (m_hDcOffscreen != NULL)
		::DeleteDC(m_hDcOffscreen);
	if (m_hbmpOffscreen != NULL)
		::DeleteObject(m_hbmpOffscreen);
	if (m_hDcPaint != NULL)
		::ReleaseDC(m_hWndPaint, m_hDcPaint);
	m_aPreMessages.Remove(m_aPreMessages.Find(this));
}

void CPaintManagerUI::Init(HWND hWnd)
{
	ASSERT(::IsWindow(hWnd));

	// Remember the window context we came from
	m_hWndPaint = hWnd;
	m_hDcPaint = ::GetDC(hWnd);

	// We'll want to filter messages globally too
	m_aPreMessages.Add(this);
}

void CPaintManagerUI::UpdateLayout()
{
	ASSERT(::IsWindow(m_hWndPaint));

	m_bResizeNeeded = true;
	::InvalidateRect(m_hWndPaint, NULL, FALSE);
}

void CPaintManagerUI::Invalidate(RECT& rcItem)
{
	ASSERT(::IsWindow(m_hWndPaint));

	::InvalidateRect(m_hWndPaint, &rcItem, FALSE);
}

HWND CPaintManagerUI::GetPaintWindow() const
{
	return m_hWndPaint;
}

HDC CPaintManagerUI::GetPaintDC() const
{
	return m_hDcPaint;
}

HWND CPaintManagerUI::GetTooltipWindow() const
{
	return m_hWndTooltip;
}


POINT CPaintManagerUI::GetMousePos() const
{
	return m_ptLastMousePos;
}

SIZE CPaintManagerUI::GetClientSize() const
{
	ASSERT(::IsWindow(m_hWndPaint));

	RECT rcClient = { 0 };
	::GetClientRect(m_hWndPaint, &rcClient);
	return CSize(rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
}

SIZE CPaintManagerUI::GetRoundCorner() const
{
	return m_szRoundCorner;
}

void CPaintManagerUI::SetRoundCorner(int cx, int cy)
{
	m_szRoundCorner.cx = cx;
	m_szRoundCorner.cy = cy;
}

RECT& CPaintManagerUI::GetCaptionRect()
{
	return m_rcCaption;
}

void CPaintManagerUI::SetCaptionRect(RECT& rcCaption)
{
	m_rcCaption = rcCaption;
}

RECT& CPaintManagerUI::GetSizeBox()
{
	return m_rcSizeBox;
}

void CPaintManagerUI::SetSizeBox(RECT& rcSizeBox)
{
	m_rcSizeBox = rcSizeBox;
}

int CPaintManagerUI::GetTransparent() const
{
	return m_nAlpha;
}
void CPaintManagerUI::SetTransparent(int nAlpha)
{
	if (nAlpha < 0)
		m_nAlpha = 0;
	else if (nAlpha > 255)
		m_nAlpha = 255;
	else
		m_nAlpha = nAlpha;

	if (m_hWndPaint != NULL)
	{
		// SetLayeredWindowAttributes 该函数只支持WS_POPUP风格窗体，不支持WS_CHILD风格窗体
		DWORD dwStyle = ::GetWindowLong(m_hWndPaint, GWL_EXSTYLE);
		DWORD dwNewStyle = dwStyle;
		if (nAlpha >= 0 && nAlpha < 256)
			dwNewStyle |= WS_EX_LAYERED;
		else
			dwNewStyle &= ~WS_EX_LAYERED;
		if (dwStyle != dwNewStyle)
			::SetWindowLong(m_hWndPaint, GWL_EXSTYLE, dwNewStyle);
		::SetLayeredWindowAttributes(m_hWndPaint, 0, nAlpha, LWA_ALPHA);
	}
}

void CPaintManagerUI::SetMinMaxInfo(int cx, int cy)
{
	ASSERT(cx>=0 && cy>=0);
	m_szMinWindow.cx = cx;
	m_szMinWindow.cy = cy;
}

HINSTANCE CPaintManagerUI::GetResourceInstance()
{
	return m_hInstance;
}

HINSTANCE CPaintManagerUI::GetLanguageInstance()
{
	return m_hLangInst;
}

void CPaintManagerUI::SetResourceInstance(HINSTANCE hInst)
{
	m_hInstance = hInst;
	if(m_hLangInst == NULL)
		m_hLangInst = hInst;
}

void CPaintManagerUI::SetLanguageInstance(HINSTANCE hInst)
{
	m_hLangInst = hInst;
}

HINSTANCE CPaintManagerUI::GetResourceDll()
{
	if (m_hResourceInstance == NULL)
		return m_hInstance;

	return m_hResourceInstance;
}

void CPaintManagerUI::SetResourceDll(HINSTANCE hInst)
{
	m_hResourceInstance = hInst;
}

CStdString CPaintManagerUI::GetInstancePath()
{
	if (m_hInstance == NULL )
		return _T('\0');

	TCHAR tszModule[MAX_PATH + 1] = { 0 };
	::GetModuleFileName(m_hInstance, tszModule, MAX_PATH);
	CStdString sInstancePath = tszModule;
	int pos = sInstancePath.ReverseFind(_T('\\'));
	if (pos >= 0)
		sInstancePath = sInstancePath.Left(pos + 1);
	return sInstancePath;
}

const CStdString& CPaintManagerUI::GetResourcePath()
{
	return m_pStrResourcePath;
}

void CPaintManagerUI::SetResourcePath(LPCTSTR pStrPath)
{
	m_pStrResourcePath = pStrPath;
	if (m_pStrResourcePath.IsEmpty())
		return;
	TCHAR cEnd = m_pStrResourcePath.GetAt(m_pStrResourcePath.GetLength() - 1);
	if (cEnd != _T('\\') && cEnd != _T('/'))
		m_pStrResourcePath += _T('\\');
}

const CStdString& CPaintManagerUI::GetResourceZip()
{
	return m_pStrResourceZip;
}

void CPaintManagerUI::SetResourceZip(LPCTSTR pStrPath, bool bCachedResourceZip)
{
	if (m_pStrResourceZip == pStrPath && m_bCachedResourceZip == bCachedResourceZip)
		return;
	if (m_bCachedResourceZip && m_hResourceZip != NULL)
	{
		CloseZip((HZIP)m_hResourceZip);
		m_hResourceZip = NULL;
	}
	m_pStrResourceZip = pStrPath;
	m_bCachedResourceZip = bCachedResourceZip;
	if (m_bCachedResourceZip)
	{
		CStdString sFile = CPaintManagerUI::GetResourcePath();
		sFile += CPaintManagerUI::GetResourceZip();
		m_hResourceZip = (HANDLE)OpenZip((void*)sFile.GetData(), 0, 2);
	}
}

bool CPaintManagerUI::IsCachedResourceZip()
{
	return m_bCachedResourceZip;
}

HANDLE CPaintManagerUI::GetResourceZipHandle()
{
	return m_hResourceZip;
}

/*void CPaintManagerUI::GetHSL(short* H, short* S, short* L)
{
	*H = m_H;
	*S = m_S;
	*L = m_L;
}*/

//HPEN CPaintManagerUI::GetThemePen(UITYPE_COLOR Index) const
//{
//	if (Index <= UICOLOR__FIRST || Index >= UICOLOR__LAST)
//		return NULL;
//
//	if (g_hPens[Index] == NULL)
//		g_hPens[Index] = ::CreatePen(PS_SOLID, 1, g_clrColors[Index][0]);
//	return g_hPens[Index];
//}
//
//HFONT CPaintManagerUI::GetThemeFont(UITYPE_FONT Index) const
//{
//	if (Index <= UIFONT__FIRST || Index >= UIFONT__LAST) 
//		return NULL;
//
//	if (g_hFonts[Index] == NULL) 
//		g_hFonts[Index] = ::CreateFontIndirect(&g_aLogFonts[Index]);
//	return g_hFonts[Index];
//}
//
//HBRUSH CPaintManagerUI::GetThemeBrush(UITYPE_COLOR Index) const
//{
//	if (Index <= UICOLOR__FIRST || Index >= UICOLOR__LAST) 
//		return NULL;
//
//	if (g_hBrushes[Index] == NULL)
//		g_hBrushes[Index] = ::CreateSolidBrush(g_clrColors[Index][0]);
//
//	return g_hBrushes[Index];
//}
//
//COLORREF CPaintManagerUI::GetThemeColor(UITYPE_COLOR Index) const
//{
//	if (Index <= UICOLOR__FIRST || Index >= UICOLOR__LAST)
//		return RGB(0,0,0);
//
//	return g_clrColors[Index][0];
//}
//
//bool CPaintManagerUI::GetThemeColorPair(UITYPE_COLOR Index, COLORREF& clr1, COLORREF& clr2) const
//{
//	if (Index <= UICOLOR__FIRST || Index >= UICOLOR__LAST)
//		return false;
//
//	clr1 = g_clrColors[Index][0];
//	clr2 = g_clrColors[Index][1];
//	return true;
//}
//
//HICON CPaintManagerUI::GetThemeIcon(int iIndex, int cxySize) const
//{
//	if(g_himgIcons16 == NULL)
//	{
//		g_himgIcons16 = ImageList_LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_ICONS16), 16, 0, RGB(255,0,255), IMAGE_BITMAP, LR_CREATEDIBSECTION);
//		g_himgIcons24 = ImageList_LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_ICONS16), 16, 0, RGB(255,0,255), IMAGE_BITMAP, LR_CREATEDIBSECTION);
//		g_himgIcons32 = ImageList_LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_ICONS16), 16, 0, RGB(255,0,255), IMAGE_BITMAP, LR_CREATEDIBSECTION);
//		g_himgIcons50 = ImageList_LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_ICONS50), 50, 0, RGB(255,0,255), IMAGE_BITMAP, LR_CREATEDIBSECTION);
//	}
//
//	if (cxySize == 16)
//		return ImageList_GetIcon(g_himgIcons16, iIndex, ILD_NORMAL);
//	else if (cxySize == 24) 
//		return ImageList_GetIcon(g_himgIcons24, iIndex, ILD_NORMAL);
//	else if (cxySize == 32)
//		return ImageList_GetIcon(g_himgIcons32, iIndex, ILD_NORMAL);
//	else if (cxySize == 50)
//		return ImageList_GetIcon(g_himgIcons50, iIndex, ILD_NORMAL);
//
//	return NULL;
//}
//
//const TEXTMETRIC& CPaintManagerUI::GetThemeFontInfo(UITYPE_FONT Index) const
//{
//	if (Index <= UIFONT__FIRST || Index >= UIFONT__LAST) 
//		return g_aTextMetrics[0];
//
//	if (g_aTextMetrics[Index].tmHeight == 0)
//	{
//		HFONT hOldFont = (HFONT)::SelectObject(m_hDcPaint, GetThemeFont(Index));
//		::GetTextMetrics(m_hDcPaint, &g_aTextMetrics[Index]);
//		::SelectObject(m_hDcPaint, hOldFont);
//	}
//
//	return g_aTextMetrics[Index];
//}

DWORD CPaintManagerUI::GetDefaultFontColor() const
{
	if (m_pParentResourcePM != NULL)
		return m_pParentResourcePM->GetDefaultFontColor();

	return m_dwDefaultFontColor;
}

void CPaintManagerUI::SetDefaultFontColor(DWORD dwColor)
{
	m_dwDefaultFontColor = dwColor;
}

DWORD CPaintManagerUI::GetDefaultLinkFontColor() const
{
	if (m_pParentResourcePM != NULL)
		return m_pParentResourcePM->GetDefaultLinkFontColor();

	return m_dwDefaultLinkFontColor;
}

void CPaintManagerUI::SetDefaultLinkFontColor(DWORD dwColor)
{
	m_dwDefaultLinkFontColor = dwColor;
}

DWORD CPaintManagerUI::GetDefaultLinkHoverFontColor() const
{
	if (m_pParentResourcePM != NULL)
		return m_pParentResourcePM->GetDefaultLinkHoverFontColor();

	return m_dwDefaultLinkHoverFontColor;
}

void CPaintManagerUI::SetDefaultLinkHoverFontColor(DWORD dwColor)
{
	m_dwDefaultLinkHoverFontColor = dwColor;
}

DWORD CPaintManagerUI::GetDefaultDisabledColor() const
{
	if (m_pParentResourcePM != NULL)
		return m_pParentResourcePM->GetDefaultDisabledColor();

	return m_dwDefaultDisabledColor;
}

void CPaintManagerUI::SetDefaultDisabledColor(DWORD dwColor)
{
	m_dwDefaultDisabledColor = dwColor;
}

TFontInfo* CPaintManagerUI::GetDefaultFontInfo()
{
	if (m_pParentResourcePM != NULL)
		return m_pParentResourcePM->GetDefaultFontInfo();

	if (m_DefaultFontInfo.tm.tmHeight == 0)
	{
		HFONT hOldFont = (HFONT) ::SelectObject(m_hDcPaint, m_DefaultFontInfo.hFont);
		::GetTextMetrics(m_hDcPaint, &m_DefaultFontInfo.tm);
		::SelectObject(m_hDcPaint, hOldFont);
	}
	return &m_DefaultFontInfo;
}

void CPaintManagerUI::SetDefaultFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic)
{
	LOGFONT lf = { 0 };
	::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	_tcscpy(lf.lfFaceName, pStrFontName);
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfHeight = -nSize;
	if( bBold ) lf.lfWeight += FW_BOLD;
	if( bUnderline ) lf.lfUnderline = TRUE;
	if( bItalic ) lf.lfItalic = TRUE;
	HFONT hFont = ::CreateFontIndirect(&lf);
	if( hFont == NULL ) return;

	::DeleteObject(m_DefaultFontInfo.hFont);
	m_DefaultFontInfo.hFont = hFont;
	m_DefaultFontInfo.sFontName = pStrFontName;
	m_DefaultFontInfo.iSize = nSize;
	m_DefaultFontInfo.bBold = bBold;
	m_DefaultFontInfo.bUnderline = bUnderline;
	m_DefaultFontInfo.bItalic = bItalic;
	::ZeroMemory(&m_DefaultFontInfo.tm, sizeof(m_DefaultFontInfo.tm));
	if (m_hDcPaint)
	{
		HFONT hOldFont = (HFONT) ::SelectObject(m_hDcPaint, hFont);
		::GetTextMetrics(m_hDcPaint, &m_DefaultFontInfo.tm);
		::SelectObject(m_hDcPaint, hOldFont);
	}
}

HFONT CPaintManagerUI::AddFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic)
{
	LOGFONT lf = { 0 };
	::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	_tcscpy(lf.lfFaceName, pStrFontName);
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfHeight = -nSize;
	if (bBold)
		lf.lfWeight += FW_BOLD;
	if (bUnderline)
		lf.lfUnderline = TRUE;
	if (bItalic)
		lf.lfItalic = TRUE;
	HFONT hFont = ::CreateFontIndirect(&lf);
	if (hFont == NULL)
		return NULL;

	TFontInfo* pFontInfo = new TFontInfo;
	if (!pFontInfo)
		return false;
	::ZeroMemory(pFontInfo, sizeof(TFontInfo));
	pFontInfo->hFont = hFont;
	pFontInfo->sFontName = pStrFontName;
	pFontInfo->iSize = nSize;
	pFontInfo->bBold = bBold;
	pFontInfo->bUnderline = bUnderline;
	pFontInfo->bItalic = bItalic;
	if (m_hDcPaint)
	{
		HFONT hOldFont = (HFONT) ::SelectObject(m_hDcPaint, hFont);
		::GetTextMetrics(m_hDcPaint, &pFontInfo->tm);
		::SelectObject(m_hDcPaint, hOldFont);
	}
	if (!m_aCustomFonts.Add(pFontInfo))
	{
		::DeleteObject(hFont);
		delete pFontInfo;
		return NULL;
	}

	return hFont;
}

HFONT CPaintManagerUI::AddFontAt(int index, LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic)
{
	LOGFONT lf = { 0 };
	::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	_tcscpy(lf.lfFaceName, pStrFontName);
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfHeight = -nSize;
	if (bBold)
		lf.lfWeight += FW_BOLD;
	if (bUnderline)
		lf.lfUnderline = TRUE;
	if (bItalic) 
		lf.lfItalic = TRUE;
	HFONT hFont = ::CreateFontIndirect(&lf);
	if (hFont == NULL)
		return NULL;

	TFontInfo* pFontInfo = new TFontInfo;
	if( !pFontInfo ) return false;
	::ZeroMemory(pFontInfo, sizeof(TFontInfo));
	pFontInfo->hFont = hFont;
	pFontInfo->sFontName = pStrFontName;
	pFontInfo->iSize = nSize;
	pFontInfo->bBold = bBold;
	pFontInfo->bUnderline = bUnderline;
	pFontInfo->bItalic = bItalic;
	if (m_hDcPaint)
	{
		HFONT hOldFont = (HFONT) ::SelectObject(m_hDcPaint, hFont);
		::GetTextMetrics(m_hDcPaint, &pFontInfo->tm);
		::SelectObject(m_hDcPaint, hOldFont);
	}
	if (!m_aCustomFonts.InsertAt(index, pFontInfo))
	{
		::DeleteObject(hFont);
		delete pFontInfo;
		return NULL;
	}

	return hFont;
}

HFONT CPaintManagerUI::GetFont(int index)
{
	if (index < 0 || index >= m_aCustomFonts.GetSize())
		return GetDefaultFontInfo()->hFont;
	TFontInfo* pFontInfo = static_cast<TFontInfo*>(m_aCustomFonts[index]);
	
	return pFontInfo->hFont;
}

HFONT CPaintManagerUI::GetFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic)
{
	TFontInfo* pFontInfo = NULL;
	for (int it = 0; it < m_aCustomFonts.GetSize(); it++)
	{
		pFontInfo = static_cast<TFontInfo*>(m_aCustomFonts[it]);
		if (pFontInfo->sFontName == pStrFontName && pFontInfo->iSize == nSize && 
			pFontInfo->bBold == bBold && pFontInfo->bUnderline == bUnderline && pFontInfo->bItalic == bItalic) 
			return pFontInfo->hFont;
	}

	if (m_pParentResourcePM)
		return m_pParentResourcePM->GetFont(pStrFontName, nSize, bBold, bUnderline, bItalic);

	return NULL;
}

void CPaintManagerUI::RemoveAllFonts()
{
	TFontInfo* pFontInfo;
	for (int it = 0; it < m_aCustomFonts.GetSize(); it++)
	{
		pFontInfo = static_cast<TFontInfo*>(m_aCustomFonts[it]);
		::DeleteObject(pFontInfo->hFont);
		delete pFontInfo;
	}
	m_aCustomFonts.Empty();
}


TFontInfo* CPaintManagerUI::GetFontInfo(int index)
{
	if (index < 0 || index >= m_aCustomFonts.GetSize())
		return GetDefaultFontInfo();

	TFontInfo* pFontInfo = static_cast<TFontInfo*>(m_aCustomFonts[index]);
	if (pFontInfo->tm.tmHeight == 0)
	{
		HFONT hOldFont = (HFONT) ::SelectObject(m_hDcPaint, pFontInfo->hFont);
		::GetTextMetrics(m_hDcPaint, &pFontInfo->tm);
		::SelectObject(m_hDcPaint, hOldFont);
	}
	return pFontInfo;
}

TFontInfo* CPaintManagerUI::GetFontInfo(HFONT hFont)
{
	TFontInfo* pFontInfo = NULL;
	for (int it = 0; it < m_aCustomFonts.GetSize(); it++)
	{
		pFontInfo = static_cast<TFontInfo*>(m_aCustomFonts[it]);
		if (pFontInfo->hFont == hFont)
		{
			if (pFontInfo->tm.tmHeight == 0)
			{
				HFONT hOldFont = (HFONT) ::SelectObject(m_hDcPaint, pFontInfo->hFont);
				::GetTextMetrics(m_hDcPaint, &pFontInfo->tm);
				::SelectObject(m_hDcPaint, hOldFont);
			}
			return pFontInfo;
		}
	}

	if (m_pParentResourcePM != NULL)
		return m_pParentResourcePM->GetFontInfo(hFont);
	
	return GetDefaultFontInfo();
}

const TImageInfo* CPaintManagerUI::GetImageEx(LPCTSTR bitmap, LPCTSTR type, DWORD mask)
{
	TImageInfo* data = static_cast<TImageInfo*>(m_mImageHash.Find(bitmap));
	if (!data)
	{
		if (AddImage(bitmap, type, mask))
		{
			data = static_cast<TImageInfo*>(m_mImageHash.Find(bitmap));
		}
	}

	return data;
}

const TImageInfo* CPaintManagerUI::AddImage(LPCTSTR bitmap, LPCTSTR type, DWORD mask)
{
	TImageInfo* data = NULL;
	if (type != NULL)
	{
		if (isdigit(*bitmap))
		{
			LPTSTR pstr = NULL;
			int iIndex = _tcstol(bitmap, &pstr, 10);
			data = CRenderEngine::LoadImage(iIndex, type, mask);
		}
	}
	else
	{
		data = CRenderEngine::LoadImage(bitmap, NULL, mask);
	}

	if (!data)
		return NULL;
	if (type != NULL)
		data->sResType = type;
	data->dwMask = mask;
	if (!m_mImageHash.Insert(bitmap, data))
	{
		::DeleteObject(data->hBitmap);
		delete data;
	}

	return data;
}

void CPaintManagerUI::AddDefaultAttributeList(LPCTSTR pStrControlName, LPCTSTR pStrControlAttrList)
{
	CStdString* pDefaultAttr = new CStdString(pStrControlAttrList);
	if (pDefaultAttr != NULL)
	{
		if (m_DefaultAttrHash.Find(pStrControlName) == NULL)
			m_DefaultAttrHash.Set(pStrControlName, (LPVOID)pDefaultAttr);
		else
			delete pDefaultAttr;
	}
}

LPCTSTR CPaintManagerUI::GetDefaultAttributeList(LPCTSTR pStrControlName) const
{
	CStdString* pDefaultAttr = static_cast<CStdString*>(m_DefaultAttrHash.Find(pStrControlName));
	if (!pDefaultAttr && m_pParentResourcePM)
		return m_pParentResourcePM->GetDefaultAttributeList(pStrControlName);

	if (pDefaultAttr)
		return pDefaultAttr->GetData();
	else return NULL;
}

bool CPaintManagerUI::RemoveDefaultAttributeList(LPCTSTR pStrControlName)
{
	CStdString* pDefaultAttr = static_cast<CStdString*>(m_DefaultAttrHash.Find(pStrControlName));
	if (!pDefaultAttr)
		return false;

	delete pDefaultAttr;
	return m_DefaultAttrHash.Remove(pStrControlName);
}

const CStdStringPtrMap& CPaintManagerUI::GetDefaultAttribultes() const
{
	return m_DefaultAttrHash;
}

void CPaintManagerUI::RemoveAllDefaultAttributeList()
{
	CStdString* pDefaultAttr;
	for (int i = 0; i< m_DefaultAttrHash.GetSize(); i++)
	{
		if (LPCTSTR key = m_DefaultAttrHash.GetAt(i))
		{
			pDefaultAttr = static_cast<CStdString*>(m_DefaultAttrHash.Find(key));
			delete pDefaultAttr;
		}
	}
	m_DefaultAttrHash.RemoveAll();
}

bool CPaintManagerUI::AttachDialog(CControlUI* pControl)
{
	ASSERT(::IsWindow(m_hWndPaint));

	// Reset any previous attachment
	SetFocus(NULL);
	m_pEventKey = NULL;
	m_pEventHover = NULL;
	m_pEventClick = NULL;
	m_aNameHash.Empty();

	// Remove the existing control-tree. We might have gotten inside this function as
	// a result of an event fired or similar, so we cannot just delete the objects and
	// pull the internal memory of the calling code. We'll delay the cleanup.
	if (m_pRoot != NULL)
	{
		m_aDelayedCleanup.Add(m_pRoot);
		::PostMessage(m_hWndPaint, WM_APP + 1, 0, 0L);
	}

	// Set the dialog root element
	m_pRoot = pControl;
	// Go ahead...
	m_bResizeNeeded = true;
	m_bFirstLayout = true;
	m_bFocusNeeded = true;
	// Initiate all control

	return InitControls(pControl);
}

bool CPaintManagerUI::InitControls(CControlUI* pControl, CControlUI* pParent /*= NULL*/)
{
	ASSERT(pControl != NULL);

	if (pControl == NULL)
		return false;
	pControl->SetManager(this, pParent != NULL ? pParent : pControl->GetParent());

	// We're usually initializing the control after adding some more of them to the tree,
	// and thus this would be a good time to request the name-map rebuilt.
	m_aNameHash.Empty();
	return true;
}

void CPaintManagerUI::ReapObjects(CControlUI* pControl)
{
	if (pControl == m_pEventKey)
		m_pEventKey = NULL;
	if (pControl == m_pEventHover)
		m_pEventHover = NULL;
	if (pControl == m_pEventClick)
		m_pEventClick = NULL;

	// TODO: Do something with name-hash-map
	//m_aNameHash.Empty();
}

CControlUI* CPaintManagerUI::GetFocus() const
{
	return m_pFocus;
}

void CPaintManagerUI::SetFocus(CControlUI* pControl)
{
	// Paint manager window has focus?
	if (::GetFocus() != m_hWndPaint) 
		::SetFocus(m_hWndPaint);

	// Already has focus?
	if (pControl == m_pFocus)
		return;

	// Remove focus from old control
	if (m_pFocus != NULL) 
	{
		TEventUI event = { 0 };
		event.Type = UIEVENT_KILLFOCUS;
		event.pSender = pControl;
		event.dwTimestamp = ::GetTickCount();
		m_pFocus->Event(event);
		SendNotify(m_pFocus, _T("killfocus"));
		m_pFocus = NULL;
	}

	// Set focus to new control
	if (pControl != NULL 
		&& pControl->GetManager() == this 
		&& pControl->IsVisible() 
		&& pControl->IsEnabled()) 
	{
		m_pFocus = pControl;
		TEventUI event = { 0 };
		event.Type = UIEVENT_SETFOCUS;
		event.pSender = pControl;
		event.dwTimestamp = ::GetTickCount();
		m_pFocus->Event(event);
		SendNotify(m_pFocus, _T("setfocus"));
	}
}

bool CPaintManagerUI::SetNextTabControl(bool bForward)
{
	// If we're in the process of restructuring the layout we can delay the
	// focus calulation until the next repaint.
	if (m_bResizeNeeded && bForward)
	{
		m_bFocusNeeded = true;
		::InvalidateRect(m_hWndPaint, NULL, FALSE);
		return true;
	}

	// Find next/previous tabbable control
	FINDTABINFO info1 = { 0 };
	info1.pFocus = m_pFocus;
	info1.bForward = bForward;
	CControlUI* pControl = m_pRoot->FindControl(__FindControlFromTab, &info1, UIFIND_VISIBLE | UIFIND_ENABLED | UIFIND_ME_FIRST);
	if (pControl == NULL)
	{  
		if (bForward)
		{
			// Wrap around
			FINDTABINFO info2 = { 0 };
			info2.pFocus = bForward ? NULL : info1.pLast;
			info2.bForward = bForward;
			pControl = m_pRoot->FindControl(__FindControlFromTab, &info2, UIFIND_VISIBLE | UIFIND_ENABLED | UIFIND_ME_FIRST);
		}
		else
		{
			pControl = info1.pLast;
		}
	}
	if (pControl != NULL)
		SetFocus(pControl);
	m_bFocusNeeded = false;
	return true;
}

bool CPaintManagerUI::SetTimer(CControlUI* pControl, UINT nTimerID, UINT uElapse)
{
	ASSERT(pControl != NULL);
	ASSERT(uElapse > 0);

	m_uTimerID = (++m_uTimerID) % 0xFF;
	if (!::SetTimer(m_hWndPaint, m_uTimerID, uElapse, NULL))
		return FALSE;
	TIMERINFO* pTimer = new TIMERINFO;
	if (pTimer == NULL )
		return FALSE;
	pTimer->hWnd = m_hWndPaint;
	pTimer->pSender = pControl;
	pTimer->nLocalID = nTimerID;
	pTimer->uWinTimer = m_uTimerID;

	return m_aTimers.Add(pTimer);
}

bool CPaintManagerUI::KillTimer(CControlUI* pControl, UINT nTimerID)
{
	ASSERT(pControl != NULL);

	for (int i = 0; i< m_aTimers.GetSize(); i++ )
	{
		TIMERINFO* pTimer = static_cast<TIMERINFO*>(m_aTimers[i]);
		if (pTimer->pSender == pControl
			&& pTimer->hWnd == m_hWndPaint
			&& pTimer->nLocalID == nTimerID)
		{
			::KillTimer(pTimer->hWnd, pTimer->uWinTimer);
			delete pTimer;
			return m_aTimers.Remove(i);
		}
	}
	return false;
}

bool CPaintManagerUI::AddNotifier(INotifyUI* pNotifier)
{
	ASSERT(m_aNotifiers.Find(pNotifier) < 0);

	return m_aNotifiers.Add(pNotifier);
}

bool CPaintManagerUI::RemoveNotifier(INotifyUI* pNotifier)
{
	for (int i = 0; i < m_aNotifiers.GetSize(); i++)
	{
		if (static_cast<INotifyUI*>(m_aNotifiers[i]) == pNotifier)
		{
			return m_aNotifiers.Remove(i);
		}
	}
	return false;
}

void CPaintManagerUI::SendNotify(TNotifyUI& Msg)
{
	// Pre-fill some standard members
	Msg.ptMouse = m_ptLastMousePos;
	Msg.dwTimestamp = ::GetTickCount();
	// Allow sender control to react
	Msg.pSender->Notify(Msg);

	// Send to all listeners
	for (int i = 0; i < m_aNotifiers.GetSize(); i++)
	{
		static_cast<INotifyUI*>(m_aNotifiers[i])->Notify(Msg);
	}
}

void CPaintManagerUI::SendNotify(CControlUI* pControl, LPCTSTR pstrMessage, WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/)
{
	TNotifyUI Msg;
	Msg.pSender = pControl;
	Msg.sType = pstrMessage;
	Msg.wParam = 0;
	Msg.lParam = 0;
	SendNotify(Msg);
}

CControlUI* CPaintManagerUI::FindControl(POINT pt) const
{
	ASSERT(m_pRoot);
	return m_pRoot->FindControl(__FindControlFromPoint, &pt, UIFIND_VISIBLE | UIFIND_HITTEST);
}

CControlUI* CPaintManagerUI::FindControl(LPCTSTR pstrName)
{
	ASSERT(m_pRoot);
	// First time here? Build hash array...
	if (m_aNameHash.GetSize() == 0)
	{
		int nCount = 0;
		m_pRoot->FindControl(__FindControlFromCount, &nCount, UIFIND_ALL);
		m_aNameHash.Resize(nCount + (nCount / 10));
		m_pRoot->FindControl(__FindControlFromNameHash, this, UIFIND_ALL);
	}
	// Find name in the hash array
	int nCount = 0;
	int nSize = m_aNameHash.GetSize();
	int iNameHash = (int) (GetNameHash(pstrName) % nSize);
	while (m_aNameHash[iNameHash] != NULL)
	{
		if (static_cast<CControlUI*>(m_aNameHash[iNameHash])->GetName() == pstrName)
			return static_cast<CControlUI*>(m_aNameHash[iNameHash]);
		iNameHash = (iNameHash + 1) % nSize;
		if (++nCount >= nSize)
			break;
	}
	return NULL;
}

int CPaintManagerUI::MessageLoop(void)
{
	MSG msg = { 0 };
	while(::GetMessage(&msg, NULL, 0, 0))
	{
		if (!CPaintManagerUI::TranslateMessage(&msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

bool CPaintManagerUI::TranslateMessage(const LPMSG pMsg)
{
	// Pretranslate Message takes care of system-wide messages, such as
	// tabbing and shortcut key-combos. We'll look for all messages for
	// each window and any child control attached.
	HWND hWndParent = ::GetParent(pMsg->hwnd);
	UINT uStyle = GetWindowStyle(pMsg->hwnd);

	LRESULT lRes = 0;
	for (int i = 0; i < m_aPreMessages.GetSize(); i++ )
	{
		CPaintManagerUI* pT = static_cast<CPaintManagerUI*>(m_aPreMessages[i]);
		if (pMsg->hwnd == pT->GetPaintWindow() || (hWndParent == pT->GetPaintWindow() && ((uStyle & WS_CHILD) != 0)))
		{
			if (pT->PreMessageHandler(pMsg->message, pMsg->wParam, pMsg->lParam, lRes)) 
				return true;
		}
	}
	return false;
}

bool CPaintManagerUI::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes)
{
//	#ifdef _DEBUG
//	switch( uMsg ) {
//   case WM_NCPAINT:
//   case WM_NCHITTEST:
//   case WM_SETCURSOR:
//	   break;
//   default:
//	   TRACE(_T("MSG: %-20s (%08ld)"), TRACEMSG(uMsg), ::GetTickCount());
//	}
//#endif


	// Not ready yet?
	if (m_hWndPaint == NULL)
		return false;

	// Cycle through listeners
	for (int i = 0; i < m_aMessageFilters.GetSize(); i++) 
	{
		bool bHandled = false;
		LRESULT lResult = static_cast<IMessageFilterUI*>(m_aMessageFilters[i])->MessageHandler(uMsg, wParam, lParam, bHandled);
		if (bHandled)
		{
			lRes = lResult;
			return true;
		}
	}

	// Custom handling of events
	switch (uMsg)
	{
	case WM_APP + 1:
		{
			// Delayed control-tree cleanup. See AttachDialog() for details.
			for (int i = 0; i < m_aDelayedCleanup.GetSize(); i++)
				delete static_cast<CControlUI*>(m_aDelayedCleanup[i]);
			m_aDelayedCleanup.Empty();
		}
		break;

	case WM_CLOSE:
		{
			// Make sure all matching "closing" events are sent
			TEventUI event = { 0 };
			event.ptMouse = m_ptLastMousePos;
			event.dwTimestamp = ::GetTickCount();
			if (m_pEventHover != NULL)
			{
				event.Type = UIEVENT_MOUSELEAVE;
				event.pSender = m_pEventHover;
				m_pEventHover->Event(event);
			}
			if (m_pEventClick != NULL)
			{
				event.Type = UIEVENT_BUTTONUP;
				event.pSender = m_pEventClick;
				m_pEventClick->Event(event);
			}
			SetFocus(NULL);

			// Hmmph, the usual Windows tricks to avoid
			// focus loss...
			HWND hwndParent = GetWindowOwner(m_hWndPaint);
			if (hwndParent != NULL)
				::SetFocus(hwndParent);
		}
		break;

	case WM_ERASEBKGND:
	   {
		   // We'll do the painting here...
		   lRes = 1;
		   return true;
	   }
	   break;

	case WM_PAINT:
		{
			// Should we paint?
		   RECT rcPaint = { 0 };
		   if (!::GetUpdateRect(m_hWndPaint, &rcPaint, FALSE))
			   return true;

		   // Do we need to resize anything?
		   // This is the time where we layout the controls on the form.
		   // We delay this even from the WM_SIZE messages since resizing can be
		   // a very expensize operation.
		   if (m_bResizeNeeded)
		   {
			   RECT rcClient = { 0 };
			   ::GetClientRect(m_hWndPaint, &rcClient);

			   if (!::IsRectEmpty(&rcClient))
			   {
				   HDC hDC = ::CreateCompatibleDC(m_hDcPaint);
				   m_pRoot->SetPos(rcClient);
				   ::DeleteDC(hDC);
				   m_bResizeNeeded = false;

				   // We'll want to notify the window when it is first initialized
				   // with the correct layout. The window form would take the time
				   // to submit swipes/animations.
				   if (m_bFirstLayout)
				   {
					   m_bFirstLayout = false;
					   SendNotify(m_pRoot, _T("windowinit"));
				   }
			   }

			   // Reset offscreen device
			   if (m_hDcOffscreen != NULL)
				   ::DeleteDC(m_hDcOffscreen);
			   if (m_hbmpOffscreen != NULL)
				   ::DeleteObject(m_hbmpOffscreen);
			   m_hDcOffscreen = NULL;
			   m_hbmpOffscreen = NULL;
		   }

		   // Set focus to first control?
		   /*if( m_bFocusNeeded ) {
			   SetNextTabControl();
		   }*/

		   //
		   // Render screen
		   //
// 		   if( m_anim.IsAnimating() )
// 		   {
// 			   // 3D animation in progress
// 			   m_anim.Render();
// 			   // Do a minimum paint loop
// 			   // Keep the client area invalid so we generate lots of
// 			   // WM_PAINT messages. Cross fingers that Windows doesn't
// 			   // batch these somehow in the future.
// 			   PAINTSTRUCT ps = { 0 };
// 			   ::BeginPaint(m_hWndPaint, &ps);
// 			   ::EndPaint(m_hWndPaint, &ps);
// 			   ::InvalidateRect(m_hWndPaint, NULL, FALSE);
// 		   }
//		   else if( m_anim.IsJobScheduled() ) {
//			   // Animation system needs to be initialized
//			   m_anim.Init(m_hWndPaint);
//			   // A 3D animation was scheduled; allow the render engine to
//			   // capture the window content and repaint some other time
//			   if( !m_anim.PrepareAnimation(m_hWndPaint) ) m_anim.CancelJobs();
//			   ::InvalidateRect(m_hWndPaint, NULL, TRUE);
//		   }
//		   else
//		   {
			   // Standard painting of control-tree - no 3D animation now.
			   // Prepare offscreen bitmap?
			   if (m_bOffscreenPaint && m_hbmpOffscreen == NULL)
			   {
				   RECT rcClient = { 0 };
				   ::GetClientRect(m_hWndPaint, &rcClient);
				   m_hDcOffscreen = ::CreateCompatibleDC(m_hDcPaint);
				   m_hbmpOffscreen = ::CreateCompatibleBitmap(m_hDcPaint, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top); 
				   ASSERT(m_hDcOffscreen);
				   ASSERT(m_hbmpOffscreen);
			   }

			   // Begin Windows paint
			   PAINTSTRUCT ps = { 0 };
			   ::BeginPaint(m_hWndPaint, &ps);
			   if (m_bOffscreenPaint)
			   {
				   // We have an offscreen device to paint on for flickerfree display.
				   HBITMAP hOldBitmap = (HBITMAP) ::SelectObject(m_hDcOffscreen, m_hbmpOffscreen);
				   // Paint the image on the offscreen bitmap
				   int iSaveDC = ::SaveDC(m_hDcOffscreen);
				   m_pRoot->DoPaint(m_hDcOffscreen, ps.rcPaint);
				   ::RestoreDC(m_hDcOffscreen, iSaveDC);
				   // Draw alpha bitmaps on top?
 				   /*for (int i = 0; i < m_aPostPaint.GetSize(); i++)
				   {
 					   TPostPaintUI* pBlit = static_cast<TPostPaintUI*>(m_aPostPaint[i]);
 					   CBlueRenderEngineUI::DoPaintAlphaBitmap(m_hDcOffscreen, this, pBlit->hBitmap, pBlit->rc, pBlit->iAlpha);
 				   }
				   m_aPostPaint.Empty();*/
				   // Blit offscreen bitmap back to display
				   ::BitBlt(ps.hdc, 
					   ps.rcPaint.left, 
					   ps.rcPaint.top, 
					   ps.rcPaint.right - ps.rcPaint.left,
					   ps.rcPaint.bottom - ps.rcPaint.top,
					   m_hDcOffscreen,
					   ps.rcPaint.left,
					   ps.rcPaint.top,
					   SRCCOPY);
				   ::SelectObject(m_hDcOffscreen, hOldBitmap);
			   }
			   else
			   {
				   // A standard paint job
				   int iSaveDC = ::SaveDC(ps.hdc);
				   m_pRoot->DoPaint(ps.hdc, ps.rcPaint);
				   ::RestoreDC(ps.hdc, iSaveDC);
			   }
			   // All Done!
			   ::EndPaint(m_hWndPaint, &ps);
//		   }
	   }
	   // If any of the painting requested a resize again, we'll need
	   // to invalidate the entire window once more.
	   if (m_bResizeNeeded)
		   ::InvalidateRect(m_hWndPaint, NULL, FALSE);
	   return true;

   case WM_PRINTCLIENT:
	   {
		   RECT rcClient;
		   ::GetClientRect(m_hWndPaint, &rcClient);
		   HDC hDC = (HDC) wParam;
		   int save = ::SaveDC(hDC);
		   m_pRoot->DoPaint(hDC, rcClient);

		   // Check for traversing children. The crux is that WM_PRINT will assume
		   // that the DC is positioned at frame coordinates and will paint the child
		   // control at the wrong position. We'll simulate the entire thing instead.
		   if ((lParam & PRF_CHILDREN) != 0)
		   {
			   HWND hWndChild = ::GetWindow(m_hWndPaint, GW_CHILD);
			   while (hWndChild != NULL)
			   {
				   RECT rcPos = { 0 };
				   ::GetWindowRect(hWndChild, &rcPos);
				   ::MapWindowPoints(HWND_DESKTOP, m_hWndPaint, reinterpret_cast<LPPOINT>(&rcPos), 2);
				   ::SetWindowOrgEx(hDC, -rcPos.left, -rcPos.top, NULL);
				   
				   // NOTE: We use WM_PRINT here rather than the expected WM_PRINTCLIENT
				   //       since the latter will not print the nonclient correctly for
				   //       EDIT controls.
				   ::SendMessage(hWndChild, WM_PRINT, wParam, lParam | PRF_NONCLIENT);
				   hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT);
			   }
		   }
		   ::RestoreDC(hDC, save);
	   }
	   break;

   case WM_GETMINMAXINFO:
	   {
		   LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
		   lpMMI->ptMinTrackSize.x = m_szMinWindow.cx;
		   lpMMI->ptMinTrackSize.y = m_szMinWindow.cy;
	   }
	   break;

   case WM_SIZE:
	   {
		   if (m_pFocus != NULL)
		   {
			   TEventUI event = { 0 };
			   event.Type = UIEVENT_WINDOWSIZE;
			   event.dwTimestamp = ::GetTickCount();
			   m_pFocus->Event(event);
		   }
		   //		   if( m_anim.IsAnimating() ) m_anim.CancelJobs();
		   m_bResizeNeeded = true;

		   return true;
	   }
	   break;

   case WM_TIMER:
	   {
		   for (int i = 0; i < m_aTimers.GetSize(); i++)
		   {
			   const TIMERINFO* pTimer = static_cast<TIMERINFO*>(m_aTimers[i]);
			   if (pTimer->hWnd == m_hWndPaint && pTimer->uWinTimer == LOWORD(wParam))
			   {
				   TEventUI event = { 0 };
				   event.Type = UIEVENT_TIMER;
				   event.wParam = pTimer->nLocalID;
				   event.dwTimestamp = ::GetTickCount();
				   pTimer->pSender->Event(event);
				   break;
			   }
		   }
	   }
	   break;

   case WM_MOUSEHOVER:
	   {
		   m_bMouseTracking = false;
		   POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		   CControlUI* pHover = FindControl(pt);
		   if (pHover == NULL)
			   break;
		   // Generate mouse hover event
		   if (m_pEventHover != NULL)
		   {
			   TEventUI event = { 0 };
			   event.ptMouse = pt;
			   event.Type = UIEVENT_MOUSEHOVER;
			   event.pSender = pHover;
			   event.dwTimestamp = ::GetTickCount();
			   m_pEventHover->Event(event);
		   }
		   // Create tooltip information
		   CStdString sToolTip = pHover->GetToolTip();
		   if (sToolTip.IsEmpty())
			   return true;
		   sToolTip.ProcessResourceTokens();
		   ::ZeroMemory(&m_ToolTip, sizeof(TOOLINFO));
		   if (_WIN32_WINNT > 501)
			    m_ToolTip.cbSize = sizeof(TOOLINFO) - sizeof(void*);
		   else
			   m_ToolTip.cbSize = sizeof(TOOLINFO);
		   m_ToolTip.uFlags = TTF_IDISHWND;
		   m_ToolTip.hwnd = m_hWndPaint;
		   m_ToolTip.uId = (UINT) m_hWndPaint;
		   m_ToolTip.hinst = m_hInstance;
		   m_ToolTip.lpszText = const_cast<LPTSTR>((LPCTSTR)sToolTip);
		   m_ToolTip.rect = pHover->GetPos();
		   if (m_hWndTooltip == NULL)
		   {
			   m_hWndTooltip = ::CreateWindowEx(0, TOOLTIPS_CLASS, NULL, WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, m_hWndPaint, NULL, m_hInstance, NULL);
			   ::SendMessage(m_hWndTooltip, TTM_ADDTOOL, 0, (LPARAM) &m_ToolTip);
		   }
		   ::SendMessage(m_hWndTooltip, TTM_SETTOOLINFO, 0, (LPARAM) &m_ToolTip);
		   ::SendMessage(m_hWndTooltip, TTM_TRACKACTIVATE, TRUE, (LPARAM) &m_ToolTip);
	   }
	   return true;

   case WM_MOUSELEAVE:
	   {
		   if (m_hWndTooltip != NULL)
			   ::SendMessage(m_hWndTooltip, TTM_TRACKACTIVATE, FALSE, (LPARAM) &m_ToolTip);
		   if (m_bMouseTracking)
			   ::SendMessage(m_hWndPaint, WM_MOUSEMOVE, 0, (LPARAM) -1);
		   m_bMouseTracking = false;
	   }
	   break;

   case WM_MOUSEMOVE:
	   {
		   // Start tracking this entire window again...
		   if (!m_bMouseTracking)
		   {
			   TRACKMOUSEEVENT tme = { 0 };
			   tme.cbSize = sizeof(TRACKMOUSEEVENT);
			   tme.dwFlags = TME_HOVER | TME_LEAVE;
			   tme.hwndTrack = m_hWndPaint;
			   tme.dwHoverTime = m_hWndTooltip == NULL ? 1000UL : (DWORD)::SendMessage(m_hWndTooltip, TTM_GETDELAYTIME, TTDT_INITIAL, 0L);
			   _TrackMouseEvent(&tme);
			   m_bMouseTracking = true;
		   }
		   // Generate the appropriate mouse messages
		   POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		   m_ptLastMousePos = pt;
		   CControlUI* pNewHover = FindControl(pt);
		   if (pNewHover != NULL && pNewHover->GetManager() != this)
			   break;
		   TEventUI event = { 0 };
		   event.ptMouse = pt;
		   event.dwTimestamp = ::GetTickCount();
		   if (pNewHover != m_pEventHover && m_pEventHover != NULL)
		   {
			   event.Type = UIEVENT_MOUSELEAVE;
			   event.pSender = pNewHover;
			   m_pEventHover->Event(event);
			   m_pEventHover = NULL;
			   if (m_hWndTooltip != NULL)
				   ::SendMessage(m_hWndTooltip, TTM_TRACKACTIVATE, FALSE, (LPARAM) &m_ToolTip);
		   }
		   if (pNewHover != m_pEventHover && pNewHover != NULL)
		   {
			   event.Type = UIEVENT_MOUSEENTER;
			   event.pSender = m_pEventHover;
			   pNewHover->Event(event);
			   m_pEventHover = pNewHover;
		   }
		   if (m_pEventClick != NULL)
		   {
			   event.Type = UIEVENT_MOUSEMOVE;
			   event.pSender = NULL;
			   m_pEventClick->Event(event);
		   }
		   else if (pNewHover != NULL)
		   {
			   event.Type = UIEVENT_MOUSEMOVE;
			   event.pSender = NULL;
			   pNewHover->Event(event);
		   }
	   }
	   break;

   case WM_LBUTTONDOWN:
	   {
		   // We alway set focus back to our app (this helps
		   // when Win32 child windows are placed on the dialog
		   // and we need to remove them on focus change).
		   ::SetFocus(m_hWndPaint);
		   POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		   m_ptLastMousePos = pt;
		   CControlUI* pControl = FindControl(pt);
		   if (pControl == NULL)
			   break;
		   if (pControl->GetManager() != this)
			   break;
		   m_pEventClick = pControl;
		   pControl->SetFocus();

		   TEventUI event = { 0 };
		   event.Type = UIEVENT_BUTTONDOWN;
		   event.wParam = wParam;
		   event.lParam = lParam;
		   event.ptMouse = pt;
		   event.wKeyState = wParam;
		   event.dwTimestamp = ::GetTickCount();
		   pControl->Event(event);
		   // No need to burden user with 3D animations
		   // m_anim.CancelJobs();
		   // We always capture the mouse
		   ::SetCapture(m_hWndPaint);
	   }
	   break;

   case WM_LBUTTONUP:
	   {
		   POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		   m_ptLastMousePos = pt;
		   if (m_pEventClick == NULL)
			   break;
		   ::ReleaseCapture();
		   
		   TEventUI event = { 0 };
		   event.Type = UIEVENT_BUTTONUP;
		   event.wParam = wParam;
		   event.lParam = lParam;
		   event.ptMouse = pt;
		   event.wKeyState = wParam;
		   event.dwTimestamp = ::GetTickCount();
		   m_pEventClick->Event(event);
		   m_pEventClick = NULL;
	   }
	   break;

   case WM_LBUTTONDBLCLK:
	   {
		   POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		   m_ptLastMousePos = pt;
		   CControlUI* pControl = FindControl(pt);
		   if (pControl == NULL)
			   break;
		   if (pControl->GetManager() != this)
			   break;
		   TEventUI event = { 0 };
		   event.Type = UIEVENT_DBLCLICK;
		   event.ptMouse = pt;
		   event.wKeyState = wParam;
		   event.dwTimestamp = ::GetTickCount();
		   pControl->Event(event);
		   m_pEventClick = pControl;
		   // We always capture the mouse
		   ::SetCapture(m_hWndPaint);
	   }
	   break;

   case WM_CHAR:
	   {
		   if (m_pFocus == NULL)
			   break;
		   TEventUI event = { 0 };
		   event.Type = UIEVENT_CHAR;
		   event.chKey = wParam;
		   event.ptMouse = m_ptLastMousePos;
		   event.wKeyState = MapKeyState();
		   event.dwTimestamp = ::GetTickCount();
		   m_pFocus->Event(event);
	   }
	   break;

   case WM_KEYDOWN:
	   {
		   if (m_pFocus == NULL)
			   break;
		   TEventUI event = { 0 };
		   event.Type = UIEVENT_KEYDOWN;
		   event.chKey = wParam;
		   event.ptMouse = m_ptLastMousePos;
		   event.wKeyState = MapKeyState();
		   event.dwTimestamp = ::GetTickCount();
		   m_pFocus->Event(event);
		   m_pEventKey = m_pFocus;
	   }
	   break;

   case WM_KEYUP:
	   {
		   if (m_pEventKey == NULL)
			   break;
		   TEventUI event = { 0 };
		   event.Type = UIEVENT_KEYUP;
		   event.chKey = wParam;
		   event.ptMouse = m_ptLastMousePos;
		   event.wKeyState = MapKeyState();
		   event.dwTimestamp = ::GetTickCount();
		   m_pEventKey->Event(event);
		   m_pEventKey = NULL;
	   }
	   break;

   case WM_SETCURSOR:
	   {
		   POINT pt = { 0 };
		   ::GetCursorPos(&pt);
		   ::ScreenToClient(m_hWndPaint, &pt);
		   CControlUI* pControl = FindControl(pt);
		   if (pControl == NULL) break;
		   if ((pControl->GetControlFlags() & UIFLAG_SETCURSOR) == 0)
			   break;
		   TEventUI event = { 0 };
		   event.Type = UIEVENT_SETCURSOR;
		   event.wParam = wParam;
		   event.lParam = lParam;
		   event.ptMouse = pt;
		   event.wKeyState = MapKeyState();
		   event.dwTimestamp = ::GetTickCount();
		   pControl->Event(event);
	   }
	   return true;

//   case WM_CTLCOLOREDIT:
//	   {
//		   ::DefWindowProc(m_hWndPaint, uMsg, wParam, lParam);
//		   HDC hDC = (HDC) wParam;
//		   ::SetTextColor(hDC, GetThemeColor(UICOLOR_EDIT_TEXT_NORMAL));
//		   ::SetBkColor(hDC, GetThemeColor(UICOLOR_EDIT_BACKGROUND_NORMAL));
//		   lRes = (LRESULT) GetThemeBrush(UICOLOR_EDIT_BACKGROUND_NORMAL);
//	   }
//	   return true;
//   case WM_MEASUREITEM:
//	   {
//		   if( wParam == 0 ) break;
//		   HWND hWndChild = ::GetDlgItem(m_hWndPaint, ((LPMEASUREITEMSTRUCT) lParam)->CtlID);
//		   lRes = ::SendMessage(hWndChild, OCM__BASE + uMsg, wParam, lParam);
//		   return true;
//	   }
//	   break;
//   case WM_DRAWITEM:
//	   {
//		   if( wParam == 0 ) break;
//		   HWND hWndChild = ((LPDRAWITEMSTRUCT) lParam)->hwndItem;
//		   lRes = ::SendMessage(hWndChild, OCM__BASE + uMsg, wParam, lParam);
//		   return true;
//	   }
//	   break;
//   case WM_VSCROLL:
//	   {
//		   if( lParam == NULL ) break;
//		   CContainerUI* pContainer = static_cast<CContainerUI*>(::GetProp((HWND) lParam, "WndX"));
//		   if( pContainer == NULL ) break;
//		   TEventUI event = { 0 };
//		   event.Type = UIEVENT_VSCROLL;
//		   event.wParam = wParam;
//		   event.lParam = lParam;
//		   event.dwTimestamp = ::GetTickCount();
//		   pContainer->Event(event);
//	   }
//	   break;

   case WM_NOTIFY:
	   {
		   LPNMHDR lpNMHDR = (LPNMHDR) lParam;
		   if (lpNMHDR != NULL)
			   lRes = ::SendMessage(lpNMHDR->hwndFrom, OCM__BASE + uMsg, wParam, lParam);
		   return true;
	   }
	   break;

   case WM_COMMAND:
	   {
		   if (lParam == 0)
			   break;
		   HWND hWndChild = (HWND) lParam;
		   lRes = ::SendMessage(hWndChild, OCM__BASE + uMsg, wParam, lParam);
		   return true;
	   }
	   break;

   default:
	   // Handle WM_MOUSEWHEEL
	   //if ((uMsg == m_uMsgMouseWheel || uMsg == 0x020A) && m_pFocus != NULL )
	   //{
		  // int zDelta = (int) (short) HIWORD(wParam);
		  // TEventUI event = { 0 };
		  // event.Type = UIEVENT_SCROLLWHEEL;
		  // event.wParam = MAKELPARAM(zDelta < 0 ? SB_LINEDOWN : SB_LINEUP, 0);
		  // event.lParam = lParam;
		  // event.dwTimestamp = ::GetTickCount();
		  // m_pFocus->Event(event);
		  // // Simulate regular scrolling by sending scroll events
		  // event.Type = UIEVENT_VSCROLL;
		  // for( int i = 0; i < abs(zDelta); i += 40 ) m_pFocus->Event(event);
		  // // Let's make sure that the scroll item below the cursor is the same as before...
		  // ::SendMessage(m_hWndPaint, WM_MOUSEMOVE, 0, (LPARAM) MAKELPARAM(m_ptLastMousePos.x, m_ptLastMousePos.y));
	   //}
	   break;
	}

	return false;
}

bool CPaintManagerUI::PreMessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& /*lRes*/)
{
	switch (uMsg) 
	{
	case WM_KEYDOWN:
		{
			// Tabbing between controls
			if (wParam == VK_TAB)
			{
				SetNextTabControl(::GetKeyState(VK_SHIFT) >= 0);
				::InvalidateRect(m_hWndPaint, NULL, FALSE);
				return true;
			}
			// Handle default dialog controls OK and CANCEL.
			// If there are controls named "ok" or "cancel" they
			// will be activated on keypress.
			if (wParam == VK_RETURN)
			{
				CControlUI* pControl = FindControl(_T("ok"));
				if (pControl != NULL && m_pFocus != pControl)
				{
					if (m_pFocus == NULL || (m_pFocus->GetControlFlags() & UIFLAG_WANTRETURN) == 0)
					{
						pControl->Activate();
						return true;
					}
				}
			}
			if (wParam == VK_ESCAPE)
			{
				CControlUI* pControl = FindControl(_T("cancel"));
				if (pControl != NULL)
				{
					pControl->Activate();
					return true;
				}
			}
		}
		break;
	case WM_SYSCHAR:
		{
			// Handle ALT-shortcut key-combinations
			FINDSHORTCUT fs = { 0 };
			fs.ch = toupper(wParam);
			CControlUI* pControl = m_pRoot->FindControl(__FindControlFromShortcut, &fs, UIFIND_VISIBLE | UIFIND_ENABLED | UIFIND_ME_FIRST);
			if (pControl != NULL)
			{
				pControl->SetFocus();
				pControl->Activate();
				return true;
			}
		}
		break;
	case WM_SYSKEYDOWN:
		{
			if (m_pFocus != NULL)
			{
				TEventUI event = { 0 };
				event.Type = UIEVENT_SYSKEY;
				event.chKey = wParam;
				event.ptMouse = m_ptLastMousePos;
				event.wKeyState = MapKeyState();
				event.dwTimestamp = ::GetTickCount();
				m_pFocus->Event(event);
			}
		}
		break;
	}
	return false;
}

CControlUI* CALLBACK CPaintManagerUI::__FindControlFromNameHash(CControlUI* pThis, LPVOID pData)
{
	CPaintManagerUI* pManager = static_cast<CPaintManagerUI*>(pData);
	// No name?
	const CStdString& sName = pThis->GetName();
	if (sName.IsEmpty())
		return NULL;
	// Add this control to the hash list
	int nCount = 0;
	int nSize = pManager->m_aNameHash.GetSize();
	int iNameHash = (int) (GetNameHash(sName) % nSize);
	while (pManager->m_aNameHash[iNameHash] != NULL)
	{
		iNameHash = (iNameHash + 1) % nSize;
		if (++nCount == nSize)
			return NULL;
	}
	pManager->m_aNameHash.SetAt(iNameHash, pThis);
	return NULL; // Attempt to add all controls
}

CControlUI* CALLBACK CPaintManagerUI::__FindControlFromCount(CControlUI* /*pThis*/, LPVOID pData)
{
	int* pnCount = static_cast<int*>(pData);
	(*pnCount)++;
	return NULL;  // Count all controls
}


CControlUI* CALLBACK CPaintManagerUI::__FindControlFromPoint(CControlUI* pThis, LPVOID pData)
{
	LPPOINT pPoint = static_cast<LPPOINT>(pData);
	return ::PtInRect(&pThis->GetPos(), *pPoint) ? pThis : NULL;
}

CControlUI* CALLBACK CPaintManagerUI::__FindControlFromTab(CControlUI* pThis, LPVOID pData)
{
	FINDTABINFO* pInfo = static_cast<FINDTABINFO*>(pData);
	if (pInfo->pFocus == pThis)
	{
		if (pInfo->bForward)
			pInfo->bNextIsIt = true;
		return pInfo->bForward ? NULL : pInfo->pLast;
	}
	if ((pThis->GetControlFlags() & UIFLAG_TABSTOP) == 0)
		return NULL;
	pInfo->pLast = pThis;
	if (pInfo->bNextIsIt)
		return pThis;
	if (pInfo->pFocus == NULL )
		return pThis;
	return NULL;  // Examine all controls
}

CControlUI* CALLBACK CPaintManagerUI::__FindControlFromShortcut(CControlUI* pThis, LPVOID pData)
{
	FINDSHORTCUT* pFS = static_cast<FINDSHORTCUT*>(pData);
	if (pFS->ch == toupper(pThis->GetShortcut()))
		pFS->bPickNext = true;

	// Labels never get focus!
	if (_tcsstr(pThis->GetClass(), _T("Label")) != NULL)	
		return NULL;

	return pFS->bPickNext ? pThis : NULL;
}