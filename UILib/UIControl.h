#ifndef __UICONTROL_H__20121015_5C7E_4F99_9C59_CCC21A03C209__INCLUDED_
#define __UICONTROL_H__20121015_5C7E_4F99_9C59_CCC21A03C209__INCLUDED_

#pragma once
#include "UILib.h"

/////////////////////////////////////////////////////////////////////////////////////
//

typedef CControlUI* (CALLBACK* FINDCONTROLPROC)(CControlUI*, LPVOID);

class UILIB_API CControlUI : public INotifyUI
{
public:
	CControlUI(void);
	virtual ~CControlUI(void);

public:
	virtual CStdString GetName() const;
	virtual void SetName(LPCTSTR pstrName);
	virtual LPCTSTR GetClass() const;
	virtual LPVOID GetInterface(LPCTSTR pstrName);
	virtual UINT GetControlFlags() const;

	virtual bool Activate();

	virtual CPaintManagerUI* GetManager() const;
	virtual void SetManager(CPaintManagerUI* pManager, CControlUI* pParent);
	virtual CControlUI* GetParent() const;

	// 文本相关
	virtual CStdString GetText() const;
	virtual void SetText(LPCTSTR pstrText);

	// 图形相关
	DWORD GetBkColor() const;
	void SetBkColor(DWORD dwBackColor);
	DWORD GetBkColor2() const;
	void SetBkColor2(DWORD dwBackColor);
	DWORD GetBkColor3() const;
	void SetBkColor3(DWORD dwBackColor);
	LPCTSTR GetBkImage();
	void SetBkImage(LPCTSTR pStrImage);
	DWORD GetBorderColor() const;
	void SetBorderColor(DWORD dwBorderColor);
	DWORD GetFocusBorderColor() const;
	void SetFocusBorderColor(DWORD dwBorderColor);
// 	bool IsColorHSL() const;
// 	void SetColorHSL(bool bColorHSL);
	SIZE GetBorderRound() const;
	void SetBorderRound(SIZE cxyRound);
	bool DrawImage(HDC hDC, LPCTSTR pStrImage, LPCTSTR pStrModify = NULL);

	// 边框相关
	int GetBorderSize() const;
	void SetBorderSize(int nSize);
	/*void SetBorderSize(RECT rc);
	int GetLeftBorderSize() const;
	void SetLeftBorderSize(int nSize);
	int GetTopBorderSize() const;
	void SetTopBorderSize(int nSize);
	int GetRightBorderSize() const;
	void SetRightBorderSize(int nSize);
	int GetBottomBorderSize() const;
	void SetBottomBorderSize(int nSize);
	int GetBorderStyle() const;
	void SetBorderStyle(int nStyle);*/

	// 位置相关
	virtual RECT GetPos() const;
	virtual void SetPos(RECT rc);
	virtual RECT GetPadding() const;
	virtual void SetPadding(RECT rcPadding); // 设置外边距，由上层窗口绘制
// 	virtual SIZE GetFixedXY() const;         // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
// 	virtual void SetFixedXY(SIZE szXY);      // 仅float为true时有效
// 	virtual int GetFixedWidth() const;       // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
// 	virtual void SetFixedWidth(int cx);      // 预设的参考值
// 	virtual int GetFixedHeight() const;      // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
// 	virtual void SetFixedHeight(int cy);     // 预设的参考值
// 	virtual int GetMinWidth() const;
// 	virtual void SetMinWidth(int cx);
// 	virtual int GetMaxWidth() const;
// 	virtual void SetMaxWidth(int cx);
// 	virtual int GetMinHeight() const;
// 	virtual void SetMinHeight(int cy);
// 	virtual int GetMaxHeight() const;
// 	virtual void SetMaxHeight(int cy);
// 	virtual void SetRelativePos(SIZE szMove,SIZE szZoom);
// 	virtual void SetRelativeParentSize(SIZE sz);
	//virtual TRelativePosUI GetRelativePos() const;
	//virtual bool IsRelativePos() const;

	// 鼠标提示
	virtual CStdString GetToolTip() const;
	virtual void SetToolTip(LPCTSTR pstrText);

	// 快捷键
	virtual TCHAR GetShortcut() const;
	virtual void SetShortcut(TCHAR ch);

	// // 一些重要的属性
	virtual bool IsVisible() const;
	virtual bool IsEnabled() const;
	virtual bool IsMouseEnabled() const;
	virtual bool IsFocused() const;
	virtual void SetVisible(bool bVisible = true);
	virtual void SetInternVisible(bool bVisible = true); // 仅供内部调用，有些UI拥有窗口句柄，需要重写此函数
	virtual void SetEnabled(bool bEnable = true);
	virtual void SetFocus();
// 	virtual bool IsFloat() const;
// 	virtual void SetFloat(bool bFloat = true);

	virtual CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);

	void Invalidate();
	void UpdateLayout();
	void ParentUpdateLayout();
	//DWORD GetAdjustColor(DWORD dwColor);

	virtual void Init();
	virtual void Event(TEventUI& event);
	virtual void Notify(TNotifyUI& msg);

	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	CControlUI* ApplyAttributeList(LPCTSTR pstrList);

	virtual SIZE EstimateSize(SIZE szAvailable) = 0;

	virtual void DoPaint(HDC hDC, const RECT& rcPaint);
	virtual void PaintBkColor(HDC hDC);
	virtual void PaintBkImage(HDC hDC);
	virtual void PaintStatusImage(HDC hDC);
	virtual void PaintText(HDC hDC);
	virtual void PaintBorder(HDC hDC);

protected:
	CPaintManagerUI* m_pManager;	// 窗口消息或绘图管理器。
	CControlUI* m_pParent;			// 逻辑上的父窗口(控件)对象指针。
	TCHAR m_chShortcut;				// 快捷键
	CStdString m_sName;				// 控件标识，在同一窗口内具有唯一性。
	CStdString m_sText;				// 控件显示标题或显示脚本字符串。
	CStdString m_sToolTip;			// 控件的Tip信息。
	RECT m_rcItem;
	RECT m_rcPaint;
	RECT m_rcPadding;				// 控件文字显示位置缩进距离?外边距?
	//SIZE m_cXY;						// 预设的位置？
	//SIZE m_cxyFixed;				// 预设的大小？
	//SIZE m_cxyMin;					// 最小值
	//SIZE m_cxyMax;					// 最大值
	bool m_bVisible;
	bool m_bInternVisible;
	bool m_bEnabled;
	bool m_bMouseEnabled;			// 是否响应鼠标消息，如果为false则由其最近的左兄弟或父亲结点处理
	bool m_bFocused;
	//bool m_bFloat;					// 浮动控件？如果不指定此属性则背景图片会拉伸到整个容器，文字会水平居左垂直居中显示
	//TRelativePosUI m_tRelativePos;	// 子控件(容器)相对于父控件(容器)的客户区坐标

	DWORD m_dwBackColor;			// 第一种背景颜色，如果指定第二种背景颜色则背景为垂直方向的渐变色
	DWORD m_dwBackColor2;			// 第二种背景颜色
	DWORD m_dwBackColor3;			// 一般不会用到
	//bool m_bColorHSL;				// HSL即是代表色调，饱和度，亮度三个通道的颜色?
	CStdString m_sBkImage;			// 背景图片
	DWORD m_dwBorderColor;			// 边框线颜色
	DWORD m_dwFocusBorderColor;		// 边界焦点颜色
	//int m_nBorderStyle;			// 边框样式
	int m_nBorderSize;				// 边框线尺寸
	//RECT m_rcBorderSize;			// 边框线尺寸
	SIZE m_cxyBorderRound;			// 边圆角框大小？
};

#endif // __UICONTROL_H__20121015_5C7E_4F99_9C59_CCC21A03C209__INCLUDED_