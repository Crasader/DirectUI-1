#ifndef __UICONTAINER_H__20121117_A630_4A4F_A33E_FADD3CA9D475__INCLUDED_
#define __UICONTAINER_H__20121117_A630_4A4F_A33E_FADD3CA9D475__INCLUDED_

#pragma once
#include "UILib.h"


/////////////////////////////////////////////////////////////////////////////////////
//

class IContainerUI
{
public:
	virtual CControlUI* GetItem(int iIndex) const = 0;
	virtual int GetItemIndex(CControlUI* pControl) const  = 0;
	virtual bool SetItemIndex(CControlUI* pControl, int iIndex)  = 0;
	virtual int GetCount() const = 0;
	virtual bool Add(CControlUI* pControl) = 0;
	virtual bool AddAt(CControlUI* pControl, int iIndex)  = 0;
	virtual bool Remove(CControlUI* pControl) = 0;
	virtual bool RemoveAt(int iIndex)  = 0;
	virtual void RemoveAll() = 0;
};



/////////////////////////////////////////////////////////////////////////////////////
//
class CScrollBarUI;

class UILIB_API CContainerUI : public CControlUI, public IContainerUI
{
public:
	CContainerUI();
	virtual ~CContainerUI();

public:
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	CControlUI* GetItem(int iIndex) const;
	int GetItemIndex(CControlUI* pControl) const;
	bool SetItemIndex(CControlUI* pControl, int iIndex);
	int GetCount() const;
	bool Add(CControlUI* pControl);
	bool AddAt(CControlUI* pControl, int iIndex);
	bool Remove(CControlUI* pControl);
	bool RemoveAt(int iIndex);
	void RemoveAll();

	void Event(TEventUI& event);
	void SetVisible(bool bVisible);
	void SetInternVisible(bool bVisible = true);

	virtual void SetInset(RECT rcInset);			// 设置内边距，相当于设置客户区
	virtual void SetPadding(int iPadding);
	//virtual void SetWidth(int cx);
	//virtual void SetHeight(int cy);
	virtual void SetAutoDestroy(bool bAuto);

	virtual int FindSelectable(int iIndex, bool bForward = true) const;

	void SetPos(RECT rc);
	void DoPaint(HDC hDC, const RECT& rcPaint);

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	void SetManager(CPaintManagerUI* pManager, CControlUI* pParent);
	CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);

	// ScrollBar
	virtual SIZE GetScrollPos() const;
	virtual void SetScrollPos(SIZE szPos);
	virtual SIZE GetScrollRange() const;
	virtual void LineUp();
	virtual void LineDown();
	virtual void PageUp();
	virtual void PageDown();
	virtual void HomeUp();
	virtual void EndDown();
	virtual void LineLeft();
	virtual void LineRight();
	virtual void PageLeft();
	virtual void PageRight();
	virtual void HomeLeft();
	virtual void EndRight();
	virtual void EnableScrollBar(bool bEnableVertical = true, bool bEnableHorizontal = false);
	virtual CScrollBarUI* GetVerticalScrollBar() const;
	virtual CScrollBarUI* GetHorizontalScrollBar() const;

protected:
	virtual void ProcessScrollbar(RECT rc, int cyRequired);

protected:
	CStdPtrArray m_items;		// 同一层的控件对象或控件对象的子对象,例如canvas上放置的按钮、combox由edit和list两个子对象组成,其它还有tab等。
	RECT m_rcInset;
	int m_iPadding;
	bool m_bAutoDestroy;		// 是否自动销毁?
	bool m_bAllowScrollbars;	// 是否允许滚动条?
	CScrollBarUI* m_pVerticalScrollBar;
	CScrollBarUI* m_pHorizontalScrollBar;
};



/////////////////////////////////////////////////////////////////////////////////////
//
//
//class UILIB_API CCanvasUI : public CContainerUI
//{
//public:
//	CCanvasUI();
//	virtual ~CCanvasUI();
//
//	LPCTSTR GetClass() const;
//
//	bool SetWatermark(UINT iBitmapRes, int iOrientation = HTBOTTOMRIGHT);
//	bool SetWatermark(LPCTSTR pstrBitmap, int iOrientation = HTBOTTOMRIGHT);
//
//	void DoPaint(HDC hDC, const RECT& rcPaint);
//
//	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
//
//protected:
//	COLORREF m_clrBack;
//	HBITMAP m_hBitmap;
//	BITMAP m_BitmapInfo;
//	int m_iOrientation;
//};
//
//
///////////////////////////////////////////////////////////////////////////////////////
////
//
//class UILIB_API CWindowCanvasUI : public CCanvasUI
//{
//public:
//	CWindowCanvasUI();
//	LPCTSTR GetClass() const;
//};
//
//
///////////////////////////////////////////////////////////////////////////////////////
////
//
//class UILIB_API CControlCanvasUI : public CCanvasUI
//{
//public:
//	CControlCanvasUI();
//	LPCTSTR GetClass() const;
//};
//
//
///////////////////////////////////////////////////////////////////////////////////////
////
//
//class UILIB_API CWhiteCanvasUI : public CCanvasUI
//{
//public:
//	CWhiteCanvasUI();
//	LPCTSTR GetClass() const;
//};
//
//
///////////////////////////////////////////////////////////////////////////////////////
////
//
//class UILIB_API CDialogCanvasUI : public CCanvasUI
//{
//public:
//	CDialogCanvasUI();
//	LPCTSTR GetClass() const;
//};
//
//
///////////////////////////////////////////////////////////////////////////////////////
////
//
//class UILIB_API CTabFolderCanvasUI : public CCanvasUI
//{
//public:
//	CTabFolderCanvasUI();
//	LPCTSTR GetClass() const;
//};
//




/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CDialogLayoutUI : public CContainerUI
{
public:
	CDialogLayoutUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	void SetStretchMode(CControlUI* pControl, UINT uMode);

	void SetPos(RECT rc);
	SIZE EstimateSize(SIZE szAvailable);

protected:
	void RecalcArea();

protected:  
	typedef struct 
	{
		CControlUI* pControl;
		UINT uMode;
		RECT rcItem;
	} STRETCHMODE;

	RECT m_rcDialog;
	RECT m_rcOriginal;
	bool m_bFirstResize;
	CStdValArray m_aModes;		// 用于存放在Layout上绝对坐标转成相对坐标(CDialogLayoutUI::RecalcArea)的控件对象(指针、大小、模式),目的是否为了让布局上的控件随布局变化而变化,能够正确绘图？？？
};



#endif // __UICONTAINER_H__20121117_A630_4A4F_A33E_FADD3CA9D475__INCLUDED_