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

	// �ı����
	virtual CStdString GetText() const;
	virtual void SetText(LPCTSTR pstrText);

	// ͼ�����
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

	// �߿����
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

	// λ�����
	virtual RECT GetPos() const;
	virtual void SetPos(RECT rc);
	virtual RECT GetPadding() const;
	virtual void SetPadding(RECT rcPadding); // ������߾࣬���ϲ㴰�ڻ���
// 	virtual SIZE GetFixedXY() const;         // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
// 	virtual void SetFixedXY(SIZE szXY);      // ��floatΪtrueʱ��Ч
// 	virtual int GetFixedWidth() const;       // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
// 	virtual void SetFixedWidth(int cx);      // Ԥ��Ĳο�ֵ
// 	virtual int GetFixedHeight() const;      // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
// 	virtual void SetFixedHeight(int cy);     // Ԥ��Ĳο�ֵ
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

	// �����ʾ
	virtual CStdString GetToolTip() const;
	virtual void SetToolTip(LPCTSTR pstrText);

	// ��ݼ�
	virtual TCHAR GetShortcut() const;
	virtual void SetShortcut(TCHAR ch);

	// // һЩ��Ҫ������
	virtual bool IsVisible() const;
	virtual bool IsEnabled() const;
	virtual bool IsMouseEnabled() const;
	virtual bool IsFocused() const;
	virtual void SetVisible(bool bVisible = true);
	virtual void SetInternVisible(bool bVisible = true); // �����ڲ����ã���ЩUIӵ�д��ھ������Ҫ��д�˺���
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
	CPaintManagerUI* m_pManager;	// ������Ϣ���ͼ��������
	CControlUI* m_pParent;			// �߼��ϵĸ�����(�ؼ�)����ָ�롣
	TCHAR m_chShortcut;				// ��ݼ�
	CStdString m_sName;				// �ؼ���ʶ����ͬһ�����ھ���Ψһ�ԡ�
	CStdString m_sText;				// �ؼ���ʾ�������ʾ�ű��ַ�����
	CStdString m_sToolTip;			// �ؼ���Tip��Ϣ��
	RECT m_rcItem;
	RECT m_rcPaint;
	RECT m_rcPadding;				// �ؼ�������ʾλ����������?��߾�?
	//SIZE m_cXY;						// Ԥ���λ�ã�
	//SIZE m_cxyFixed;				// Ԥ��Ĵ�С��
	//SIZE m_cxyMin;					// ��Сֵ
	//SIZE m_cxyMax;					// ���ֵ
	bool m_bVisible;
	bool m_bInternVisible;
	bool m_bEnabled;
	bool m_bMouseEnabled;			// �Ƿ���Ӧ�����Ϣ�����Ϊfalse��������������ֵܻ��׽�㴦��
	bool m_bFocused;
	//bool m_bFloat;					// �����ؼ��������ָ���������򱳾�ͼƬ�����쵽�������������ֻ�ˮƽ����ֱ������ʾ
	//TRelativePosUI m_tRelativePos;	// �ӿؼ�(����)����ڸ��ؼ�(����)�Ŀͻ�������

	DWORD m_dwBackColor;			// ��һ�ֱ�����ɫ�����ָ���ڶ��ֱ�����ɫ�򱳾�Ϊ��ֱ����Ľ���ɫ
	DWORD m_dwBackColor2;			// �ڶ��ֱ�����ɫ
	DWORD m_dwBackColor3;			// һ�㲻���õ�
	//bool m_bColorHSL;				// HSL���Ǵ���ɫ�������Ͷȣ���������ͨ������ɫ?
	CStdString m_sBkImage;			// ����ͼƬ
	DWORD m_dwBorderColor;			// �߿�����ɫ
	DWORD m_dwFocusBorderColor;		// �߽罹����ɫ
	//int m_nBorderStyle;			// �߿���ʽ
	int m_nBorderSize;				// �߿��߳ߴ�
	//RECT m_rcBorderSize;			// �߿��߳ߴ�
	SIZE m_cxyBorderRound;			// ��Բ�ǿ��С��
};

#endif // __UICONTROL_H__20121015_5C7E_4F99_9C59_CCC21A03C209__INCLUDED_