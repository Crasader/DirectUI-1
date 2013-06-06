#ifndef __UIBLUE_H__20121117_7C69_4AB8_ACD8_F7FA3FBDC076__INCLUDED_
#define __UIBLUE_H__20121117_7C69_4AB8_ACD8_F7FA3FBDC076__INCLUDED_

#pragma once
#include "UILib.h"

//////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CRenderClip
{
public:
	~CRenderClip();
	RECT rcItem;
	HDC hDC;
	HRGN hRgn;
	HRGN hOldRgn;

	static void GenerateClip(HDC hDC, RECT rc, CRenderClip& clip);
	static void GenerateRoundClip(HDC hDC, RECT rc, RECT rcItem, int width, int height, CRenderClip& clip);
	static void UseOldClipBegin(HDC hDC, CRenderClip& clip);
	static void UseOldClipEnd(HDC hDC, CRenderClip& clip);
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CRenderEngine
{
public:
	static DWORD AdjustColor(DWORD dwColor, short H, short S, short L);
	static TImageInfo* LoadImage(STRINGorID bitmap, LPCTSTR type = NULL, DWORD mask = 0);
	//static void FreeImage(const TImageInfo* bitmap);
	static void DrawImage(HDC hDC, HBITMAP hBitmap, const RECT& rc, const RECT& rcPaint, \
		const RECT& rcBmpPart, const RECT& rcCorners, bool alphaChannel, BYTE uFade = 255, 
		bool hole = false, bool xtiled = false, bool ytiled = false);
	static bool DrawImageString(HDC hDC, CPaintManagerUI* pManager, const RECT& rcItem, const RECT& rcPaint, 
		LPCTSTR pStrImage, LPCTSTR pStrModify = NULL);
	static void DrawColor(HDC hDC, const RECT& rc, DWORD color);
	static void DrawGradient(HDC hDC, const RECT& rc, DWORD dwFirst, DWORD dwSecond, bool bVertical, int nSteps);

	// 以下函数中的颜色参数alpha值无效
	static void DrawLine(HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor,int nStyle = PS_SOLID);
	static void DrawRect(HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor);
	static void DrawRoundRect(HDC hDC, const RECT& rc, int width, int height, int nSize, DWORD dwPenColor);
	static void DrawText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, \
		DWORD dwTextColor, int iFont, UINT uStyle);
	static void DrawHtmlText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, 
		DWORD dwTextColor, RECT* pLinks, CStdString* sLinks, int& nLinkRects, UINT uStyle);
	static HBITMAP GenerateBitmap(CPaintManagerUI* pManager, CControlUI* pControl, RECT rc);
};


/////////////////////////////////////////////////////////////////////////////////////
//

//class UILIB_API CBlueRenderEngineUI
//{
//public:
//	/*static void DoFillRect(HDC hDC, CPaintManagerUI* pManager, RECT rc, UITYPE_COLOR Color);
//	static void DoFillRect(HDC hDC, CPaintManagerUI* pManager, RECT rc, COLORREF clrFill);
//	static void DoPaintFrame(HDC hDC, CPaintManagerUI* pManager, RECT rc, UITYPE_COLOR Light, UITYPE_COLOR Dark, UITYPE_COLOR Background = UICOLOR__INVALID, UINT uStyle = 0);
//	static void DoPaintBitmap(HDC hDC, CPaintManagerUI* pManager, HBITMAP hBmp, RECT rcBitmap);
//	static void DoPaintButton(HDC hDC, CPaintManagerUI* pManager, RECT rc, LPCTSTR pstrText, RECT rcPadding, UINT uState, UINT uDrawStyle);
//	static void DoPaintEditBox(HDC hDC, CPaintManagerUI* pManager, RECT rcItem, LPCTSTR pstrText, UINT uState, UINT uDrawStyle, bool bPaintFrameOnly);
//	static void DoPaintOptionBox(HDC hDC, CPaintManagerUI* pManager, RECT rcItem, LPCTSTR pstrText, UINT uState, UINT uStyle);
//	static void DoPaintQuickText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, UITYPE_COLOR iTextColor, UITYPE_FONT iFont, UINT uStyle);
//	static void DoPaintPrettyText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, UITYPE_COLOR iTextColor, UITYPE_COLOR iBackColor, RECT* pLinks, int& nLinkRects, UINT uStyle);
//	static void DoPaintGradient(HDC hDC, CPaintManagerUI* pManager, RECT rc, COLORREF clrFirst, COLORREF clrSecond, bool bVertical, int nSteps);
//	static void GenerateClip(HDC hDC, RECT rcItem, CRenderClip& clip);*/
//};

class UILIB_API CDefaultRenderEngineUI
{
public:
	static void FillRect(HDC hDC, RECT rc, DWORD clrFill);
	// The Rectangle function draws a rectangle. The rectangle is outlined by using the current pen and filled by using the current brush. 
	static void Rectangle(HDC hDC, RECT rc, DWORD dwFillColor, DWORD dwBorderColor, int nSize = 1, int nStyle = PS_SOLID);
	static void DrawRoundRect(HDC hDC, const RECT& rc, int nSize, int nWidth, int nHeight, DWORD dwPenColor);
	static void DrawLine(HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor,int nStyle = PS_SOLID);
	static void DrawText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, DWORD dwTextColor, int iFont, UINT uStyle);
	static void DrawHtmlText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, DWORD dwTextColor, RECT* prcLinks, int& nLinkRects, UINT uStyle);
	static void DoPaintFrame(HDC hDC, CPaintManagerUI* pManager, RECT rc, DWORD dwLight, DWORD dwDark, DWORD dwBackground = 0x00000000, UINT uStyle = 0);
};



#endif // __UIBLUE_H__20121117_7C69_4AB8_ACD8_F7FA3FBDC076__INCLUDED_