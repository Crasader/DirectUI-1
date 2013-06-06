#ifndef __UIMANAGER_H__20121015_5FA9_40A2_84A5_0C635F56C6F4__INCLUDED_
#define __UIMANAGER_H__20121015_5FA9_40A2_84A5_0C635F56C6F4__INCLUDED_

#pragma once
#include "UILib.h"


/////////////////////////////////////////////////////////////////////////////////////
//

class CControlUI;




/////////////////////////////////////////////////////////////////////////////////////
//

typedef enum EVENTTYPE_UI
{
	UIEVENT__KEYBEGIN,
	UIEVENT_KEYDOWN,
	UIEVENT_KEYUP,
	UIEVENT_CHAR,
	UIEVENT_SYSKEY,
	UIEVENT__KEYEND,
	UIEVENT__MOUSEBEGIN,
	UIEVENT_MOUSEMOVE,
	UIEVENT_MOUSELEAVE,
	UIEVENT_MOUSEENTER,
	UIEVENT_MOUSEHOVER,
	UIEVENT_BUTTONDOWN,
	UIEVENT_BUTTONUP,
	UIEVENT_RBUTTONDOWN,
	UIEVENT_DBLCLICK,
	UIEVENT_CONTEXTMENU,
	UIEVENT_SCROLLWHEEL,
	UIEVENT__MOUSEEND,
	UIEVENT_KILLFOCUS,
	UIEVENT_SETFOCUS,
	UIEVENT_WINDOWSIZE,
	UIEVENT_SETCURSOR,
	UIEVENT_TIMER,
	UIEVENT_NOTIFY,
	UIEVENT_COMMAND,
	UIEVENT__LAST,
};

//typedef enum
//{
//	UIFONT__FIRST = 0,
//	UIFONT_NORMAL,
//	UIFONT_BOLD,
//	UIFONT_CAPTION,
//	UIFONT_MENU,
//	UIFONT_LINK,
//	UIFONT_TITLE,
//	UIFONT_HEADLINE,
//	UIFONT_SUBSCRIPT,
//	UIFONT__LAST,
//} UITYPE_FONT;

//typedef enum
//{
//	UICOLOR__FIRST = 0,
//	UICOLOR_WINDOW_BACKGROUND,
//	UICOLOR_WINDOW_TEXT,
//	UICOLOR_DIALOG_BACKGROUND,
//	UICOLOR_DIALOG_TEXT_NORMAL,
//	UICOLOR_DIALOG_TEXT_DARK,
//	UICOLOR_MENU_BACKGROUND,
//	UICOLOR_MENU_TEXT_NORMAL,
//	UICOLOR_MENU_TEXT_HOVER,
//	UICOLOR_MENU_TEXT_SELECTED,
//	UICOLOR_TEXTCOLOR_NORMAL,
//	UICOLOR_TEXTCOLOR_HOVER,
//	UICOLOR_TAB_BACKGROUND_NORMAL,
//	UICOLOR_TAB_BACKGROUND_SELECTED,
//	UICOLOR_TAB_FOLDER_NORMAL,
//	UICOLOR_TAB_FOLDER_SELECTED,
//	UICOLOR_TAB_BORDER,
//	UICOLOR_TAB_TEXT_NORMAL,
//	UICOLOR_TAB_TEXT_SELECTED,
//	UICOLOR_TAB_TEXT_DISABLED,
//	UICOLOR_NAVIGATOR_BACKGROUND,
//	UICOLOR_NAVIGATOR_BUTTON_HOVER,
//	UICOLOR_NAVIGATOR_BUTTON_PUSHED,
//	UICOLOR_NAVIGATOR_BUTTON_SELECTED,
//	UICOLOR_NAVIGATOR_BORDER_NORMAL,
//	UICOLOR_NAVIGATOR_BORDER_SELECTED,
//	UICOLOR_NAVIGATOR_TEXT_NORMAL,
//	UICOLOR_NAVIGATOR_TEXT_SELECTED,
//	UICOLOR_NAVIGATOR_TEXT_PUSHED,
//	UICOLOR_BUTTON_BACKGROUND_NORMAL,
//	UICOLOR_BUTTON_BACKGROUND_DISABLED,
//	UICOLOR_BUTTON_BACKGROUND_PUSHED,
//	UICOLOR_BUTTON_TEXT_NORMAL,
//	UICOLOR_BUTTON_TEXT_PUSHED,
//	UICOLOR_BUTTON_TEXT_DISABLED,
//	UICOLOR_BUTTON_BORDER_LIGHT,
//	UICOLOR_BUTTON_BORDER_DARK,
//	UICOLOR_BUTTON_BORDER_DISABLED,
//	UICOLOR_BUTTON_BORDER_FOCUS,
//	UICOLOR_CONTROL_BACKGROUND_NORMAL,
//	UICOLOR_CONTROL_BACKGROUND_SELECTED,
//	UICOLOR_CONTROL_BACKGROUND_DISABLED,
//	UICOLOR_CONTROL_BACKGROUND_READONLY,
//	UICOLOR_CONTROL_BACKGROUND_HOVER,
//	UICOLOR_CONTROL_BACKGROUND_SORTED,
//	UICOLOR_CONTROL_BACKGROUND_EXPANDED,
//	UICOLOR_CONTROL_BORDER_NORMAL,
//	UICOLOR_CONTROL_BORDER_SELECTED,
//	UICOLOR_CONTROL_BORDER_DISABLED,
//	UICOLOR_CONTROL_TEXT_NORMAL,
//	UICOLOR_CONTROL_TEXT_SELECTED,
//	UICOLOR_CONTROL_TEXT_DISABLED,
//	UICOLOR_CONTROL_TEXT_READONLY,
//	UICOLOR_TOOL_BACKGROUND_NORMAL,
//	UICOLOR_TOOL_BACKGROUND_DISABLED,
//	UICOLOR_TOOL_BACKGROUND_HOVER,
//	UICOLOR_TOOL_BACKGROUND_PUSHED,
//	UICOLOR_TOOL_BORDER_NORMAL,
//	UICOLOR_TOOL_BORDER_DISABLED,
//	UICOLOR_TOOL_BORDER_HOVER,
//	UICOLOR_TOOL_BORDER_PUSHED,
//	UICOLOR_EDIT_BACKGROUND_NORMAL,
//	UICOLOR_EDIT_BACKGROUND_HOVER,
//	UICOLOR_EDIT_BACKGROUND_DISABLED,
//	UICOLOR_EDIT_BACKGROUND_READONLY,
//	UICOLOR_EDIT_TEXT_NORMAL,
//	UICOLOR_EDIT_TEXT_DISABLED,
//	UICOLOR_EDIT_TEXT_READONLY,
//	UICOLOR_TITLE_BACKGROUND,
//	UICOLOR_TITLE_TEXT,
//	UICOLOR_TITLE_BORDER_LIGHT,
//	UICOLOR_TITLE_BORDER_DARK,
//	UICOLOR_HEADER_BACKGROUND,
//	UICOLOR_HEADER_BORDER,
//	UICOLOR_HEADER_SEPARATOR,
//	UICOLOR_HEADER_TEXT,
//	UICOLOR_TASK_BACKGROUND,
//	UICOLOR_TASK_CAPTION,
//	UICOLOR_TASK_BORDER,
//	UICOLOR_TASK_TEXT,
//	UICOLOR_LINK_TEXT_HOVER,
//	UICOLOR_LINK_TEXT_NORMAL,
//	UICOLOR_STANDARD_BLACK,
//	UICOLOR_STANDARD_YELLOW,
//	UICOLOR_STANDARD_RED,
//	UICOLOR_STANDARD_GREY,
//	UICOLOR_STANDARD_LIGHTGREY,
//	UICOLOR_STANDARD_WHITE,
//	UICOLOR__LAST,
//	UICOLOR__INVALID,
//} UITYPE_COLOR;



/////////////////////////////////////////////////////////////////////////////////////
//
//
//Styles for the DoPaintFrame() helper
#define UIFRAME_ROUND        0x00000001
#define UIFRAME_FOCUS        0x00000002

// Flags for CControlUI::GetControlFlags()
#define UIFLAG_TABSTOP       0x00000001
#define UIFLAG_SETCURSOR     0x00000002
#define UIFLAG_WANTRETURN    0x00000004

// Flags for FindControl()
#define UIFIND_ALL           0x00000000
#define UIFIND_VISIBLE       0x00000001
#define UIFIND_ENABLED       0x00000002
#define UIFIND_HITTEST       0x00000004
#define UIFIND_ME_FIRST      0x80000000

// Flags for the CDialogLayout stretching
#define UISTRETCH_NEWGROUP   0x00000001
#define UISTRETCH_NEWLINE    0x00000002
#define UISTRETCH_MOVE_X     0x00000004
#define UISTRETCH_MOVE_Y     0x00000008
#define UISTRETCH_SIZE_X     0x00000010
#define UISTRETCH_SIZE_Y     0x00000020

// Flags used for controlling the paint
#define UISTATE_FOCUSED      0x00000001
#define UISTATE_SELECTED     0x00000002
#define UISTATE_DISABLED     0x00000004
#define UISTATE_HOT          0x00000008
#define UISTATE_PUSHED       0x00000010
#define UISTATE_CHECKED      0x00000020
#define UISTATE_READONLY     0x00000040
#define UISTATE_CAPTURED     0x00000080



/////////////////////////////////////////////////////////////////////////////////////
//

// Structure for notifications from the system
// to the control implementation.
typedef struct tagTEventUI
{
	int Type;
	CControlUI* pSender;
	DWORD dwTimestamp;
	POINT ptMouse;
	TCHAR chKey;
	WORD wKeyState;
	WPARAM wParam;
	LPARAM lParam;
} TEventUI;

// Structure for notifications to the outside world
typedef struct tagTNotifyUI 
{
	CStdString sType;
	CControlUI* pSender;
	DWORD dwTimestamp;
	POINT ptMouse;
	WPARAM wParam;
	LPARAM lParam;
} TNotifyUI;

// Listener interface
class INotifyUI
{
public:
	virtual void Notify(TNotifyUI& msg) = 0;
};

// MessageFilter interface
class IMessageFilterUI
{
public:
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) = 0;
};

typedef struct tagTFontInfo
{
	HFONT hFont;
	CStdString sFontName;
	int iSize;
	bool bBold;
	bool bUnderline;
	bool bItalic;
	TEXTMETRIC tm;
} TFontInfo;

typedef struct tagTImageInfo
{
	HBITMAP hBitmap;
	int nX;
	int nY;
	bool alphaChannel;
	CStdString sResType;
	DWORD dwMask;
} TImageInfo;

//// Structure for relative position to the parent
//typedef struct tagTRelativePosUI
//{
//	bool bRelative;
//	SIZE szParent;
//	int nMoveXPercent;
//	int nMoveYPercent;
//	int nZoomXPercent;
//	int nZoomYPercent;
//}TRelativePosUI;

//class ITranslateAccelerator
//{
//public:
//	virtual LRESULT TranslateAccelerator(MSG *pMsg) = 0;
//};



////////////////////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CPaintManagerUI
{
public:
	CPaintManagerUI(void);
	~CPaintManagerUI(void);

public:
	void Init(HWND hWnd);
	void UpdateLayout();				// NeedUpdate()
	void Invalidate(RECT& rcItem);

	HWND GetPaintWindow() const;
	HDC GetPaintDC() const;
	HWND GetTooltipWindow() const;

	POINT GetMousePos() const;
	SIZE GetClientSize() const;
	SIZE GetRoundCorner() const;
	void SetRoundCorner(int cx, int cy);
	RECT& GetCaptionRect();
	void SetCaptionRect(RECT& rcCaption);
	RECT& GetSizeBox();
	void SetSizeBox(RECT& rcSizeBox);

	int GetTransparent() const;
	void SetTransparent(int nAlpha);

	void SetMinMaxInfo(int cx, int cy);

	static HINSTANCE GetResourceInstance();
	static HINSTANCE GetLanguageInstance();
	static void SetResourceInstance(HINSTANCE hInst);
	static void SetLanguageInstance(HINSTANCE hInst);
	static HINSTANCE GetResourceDll();
	static void SetResourceDll(HINSTANCE hInst);
	static CStdString GetInstancePath();
	static const CStdString& GetResourcePath();
	static void SetResourcePath(LPCTSTR pStrPath);
	static const CStdString& GetResourceZip();
	//static void SetResourceZip(LPVOID pVoid, unsigned int len);
	static void SetResourceZip(LPCTSTR pstrZip, bool bCachedResourceZip = false);
	static bool IsCachedResourceZip();
	static HANDLE GetResourceZipHandle();

	//static void GetHSL(short* H, short* S, short* L);

	/*HPEN GetThemePen(UITYPE_COLOR Index) const;
	HFONT GetThemeFont(UITYPE_FONT Index) const;
	HBRUSH GetThemeBrush(UITYPE_COLOR Index) const;
	COLORREF GetThemeColor(UITYPE_COLOR Index) const;
	bool GetThemeColorPair(UITYPE_COLOR Index, COLORREF& clr1, COLORREF& clr2) const;
	HICON GetThemeIcon(int Index, int cxySize) const;
	const TEXTMETRIC& GetThemeFontInfo(UITYPE_FONT Index) const;*/
	DWORD GetDefaultFontColor() const;
	void SetDefaultFontColor(DWORD dwColor);
	DWORD GetDefaultLinkFontColor() const;
	void SetDefaultLinkFontColor(DWORD dwColor);
	DWORD GetDefaultLinkHoverFontColor() const;
	void SetDefaultLinkHoverFontColor(DWORD dwColor);
	DWORD GetDefaultDisabledColor() const;
	void SetDefaultDisabledColor(DWORD dwColor);
	TFontInfo* GetDefaultFontInfo();
	void SetDefaultFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
	HFONT AddFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
	HFONT AddFontAt(int index, LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
	HFONT GetFont(int index);
	HFONT GetFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
	void RemoveAllFonts();
	TFontInfo* GetFontInfo(int index);
	TFontInfo* GetFontInfo(HFONT hFont);

	const TImageInfo* GetImageEx(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0);
	const TImageInfo* AddImage(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0);

	void AddDefaultAttributeList(LPCTSTR pStrControlName, LPCTSTR pStrControlAttrList);
	LPCTSTR GetDefaultAttributeList(LPCTSTR pStrControlName) const;
	bool RemoveDefaultAttributeList(LPCTSTR pStrControlName);
	const CStdStringPtrMap& GetDefaultAttribultes() const;
	void RemoveAllDefaultAttributeList();

	bool AttachDialog(CControlUI* pControl);
	bool InitControls(CControlUI* pControl, CControlUI* pParent = NULL);
	void ReapObjects(CControlUI* pControl);

	CControlUI* GetFocus() const;
	void SetFocus(CControlUI* pControl);

	bool SetNextTabControl(bool bForward = true);

	bool SetTimer(CControlUI* pControl, UINT nTimerID, UINT uElapse);
	bool KillTimer(CControlUI* pControl, UINT nTimerID);

	bool AddNotifier(INotifyUI* pControl);
	bool RemoveNotifier(INotifyUI* pControl);  
	void SendNotify(TNotifyUI& Msg);
	void SendNotify(CControlUI* pControl, LPCTSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0);

	CControlUI* FindControl(POINT pt) const;
	CControlUI* FindControl(LPCTSTR pstrName);

	static int MessageLoop(void);
	static bool TranslateMessage(const LPMSG pMsg);

	bool MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);
	bool PreMessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);

private:
	static CControlUI* CALLBACK __FindControlFromNameHash(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromCount(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromPoint(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromTab(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromShortcut(CControlUI* pThis, LPVOID pData);

private:
	HWND m_hWndPaint;					// 控件布局窗口句柄。
	HDC m_hDcPaint;						// 控件布局窗口设备DC。
	HDC m_hDcOffscreen;					// 离屏内存DC。
	HBITMAP m_hbmpOffscreen;			// 离屏内存DC相关联HBITMAP。
	HWND m_hWndTooltip;
	TOOLINFO m_ToolTip;
	int m_nAlpha;						// 透明度
	//
	CControlUI* m_pRoot;				// 如果控件是叠加存放的则存放最下层的控件对象,否则存放第一个创建的控件对象。
	CControlUI* m_pFocus;				// 存放活的焦点的控件对象指针。
	CControlUI* m_pEventHover;			// 存放当前有鼠标移进移出事件的控件对象指针。
	CControlUI* m_pEventClick;			// 存放当前有点击事件的控件对象指针。
	CControlUI* m_pEventKey;			// 存放当前有按键事件的控件对象指针。
	//
	POINT m_ptLastMousePos;
	SIZE m_szMinWindow;
	UINT m_uTimerID;
	bool m_bFirstLayout;
	bool m_bResizeNeeded;
	bool m_bOffscreenPaint;
	bool m_bFocusNeeded;
	bool m_bMouseTracking;
	SIZE m_szRoundCorner;				// 圆角
	RECT m_rcCaption;					// 标题栏区域
	RECT m_rcSizeBox;					// sizebox
	//
	CStdPtrArray m_aNotifiers;			// 记录所有需要事件通知的窗口,根据窗口名称调用相应的消息处理函数。
	CStdPtrArray m_aNameHash;			// 保存控件对象指针hash表(用控件名称生成hash值)。
	CStdPtrArray m_aTimers;
	CStdPtrArray m_aMessageFilters;		// 保存需要进行消息过滤的控件或功能(如动画类)。
	CStdPtrArray m_aDelayedCleanup;
	//
	CPaintManagerUI* m_pParentResourcePM;	// 用于ComBox，Menu
	DWORD m_dwDefaultFontColor;
	DWORD m_dwDefaultDisabledColor;
	DWORD m_dwDefaultLinkFontColor;
	DWORD m_dwDefaultLinkHoverFontColor;
	DWORD m_dwDefaultSelectedBkColor;
	TFontInfo m_DefaultFontInfo;		// 默认字体
	CStdPtrArray m_aCustomFonts;
	//
	CStdStringPtrMap m_mImageHash;
	CStdStringPtrMap m_DefaultAttrHash;
	//
	static HINSTANCE m_hInstance;
	static HINSTANCE m_hLangInst;
	static HINSTANCE m_hResourceInstance;
	static CStdString m_pStrResourcePath;
	static CStdString m_pStrResourceZip;
	static bool m_bCachedResourceZip;
	static HANDLE m_hResourceZip;
	static CStdPtrArray m_aPreMessages;	// 预处理消息。

	/*static short m_H;
	static short m_S;
	static short m_L;*/
};

#endif // __UIMANAGER_H__20121015_5FA9_40A2_84A5_0C635F56C6F4__INCLUDED_