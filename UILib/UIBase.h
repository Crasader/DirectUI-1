#ifndef __UIBASE_H__20121015_9CD9_47F7_A794_2050208FA2E6__INCLUDED_
#define __UIBASE_H__20121015_9CD9_47F7_A794_2050208FA2E6__INCLUDED_

#pragma once
#include "UILib.h"




/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CRect : public tagRECT
{
public:
	CRect();
	CRect(const RECT& src);
	CRect(int iLeft, int iTop, int iRight, int iBottom);

	int GetWidth() const;
	int GetHeight() const;
	void Empty();
	void Join(const RECT& rc);
	void ResetOffset();
	void Normalize();
	void Offset(int cx, int cy);
	void Inflate(int cx, int cy);
	void Deflate(int cx, int cy);
	void Union(CRect& rc);
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CSize : public tagSIZE
{
public:
	CSize();
	CSize(const SIZE& src);
	CSize(const RECT rc);
	CSize(int cx, int cy);
};


/////////////////////////////////////////////////////////////////////////////////////
//

class STRINGorID
{
public:
	STRINGorID(LPCTSTR lpString) : m_lpstr(lpString)
	{ }
	STRINGorID(UINT nID) : m_lpstr(MAKEINTRESOURCE(nID))
	{ }
	LPCTSTR m_lpstr;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CPoint : public tagPOINT
{
public:
	CPoint();
	CPoint(const POINT& src);
	CPoint(int x, int y);
	CPoint(LPARAM lParam);
};

////////////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CWindowWnd
{
public:
	CWindowWnd(void);
	~CWindowWnd(void);

public:
	HWND GetHWND() const;
	operator HWND() const;
	HWND GetSafeHwnd(void);

	BOOL RegisterWindowClass();
	bool RegisterSuperclass();

	HWND Create(HWND hWndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);
	HWND Create(HWND hWndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);

	HWND Subclass(HWND hWnd);
	void Unsubclass();

	UINT GetClassStyle(void);
	void ShowWindow(bool bShow = true, bool bTakeFocus = true);
	int ShowModal();
	void Close();
	void CenterWindow();
	LONG GetStyle(void);
	LONG GetExStyle(void);

	void SetIcon(UINT nRes);

	LRESULT SendMessage(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0L);
	BOOL PostMessage(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0L);
	
protected:
	virtual LPCTSTR GetWindowClassName() const = 0;
	virtual LPCTSTR GetSuperClassName() const;

	void ResizeClient(int cx = -1, int cy = -1);

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnFinalMessage(HWND hWnd);

	static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	HWND m_hWnd;
	WNDPROC m_lpOldWndProc;
	bool m_bSubclassed;
};




/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CStdPtrArray
{
public:
	CStdPtrArray(int iPreallocSize = 0);
	virtual ~CStdPtrArray();

	void Empty();
	void Resize(int iSize);
	bool IsEmpty() const;
	int Find(LPVOID iIndex) const;
	bool Add(LPVOID pData);
	bool SetAt(int iIndex, LPVOID pData);
	bool InsertAt(int iIndex, LPVOID pData);
	bool Remove(int iIndex);
	int GetSize() const;
	LPVOID* GetData();

	LPVOID GetAt(int iIndex) const;
	LPVOID operator[] (int nIndex) const;

protected:
	LPVOID* m_ppVoid;
	int m_nCount;
	int m_nAllocated;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CStdValArray
{
public:
	CStdValArray(int iElementSize, int iPreallocSize = 0);
	virtual ~CStdValArray();

	void Empty();
	bool IsEmpty() const;
	bool Add(LPCVOID pData);
	bool Remove(int iIndex);
	int GetSize() const;
	LPVOID GetData();

	LPVOID GetAt(int iIndex) const;
	LPVOID operator[] (int nIndex) const;

protected:
	LPBYTE m_pVoid;
	int m_iElementSize;
	int m_nCount;
	int m_nAllocated;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CStdString
{
public:
	enum { MAX_LOCAL_STRING_LEN = 63 };

	CStdString();
	CStdString(const TCHAR ch);
	CStdString(const CStdString& src);
	CStdString(LPCTSTR lpsz, int nLen = -1);
	virtual ~CStdString();

	static CStdString RES(UINT nRes);

	void Empty();
	int GetLength() const;
	bool IsEmpty() const;
	TCHAR GetAt(int nIndex) const;
	void Append(LPCTSTR pstr);
	void Assign(LPCTSTR pstr, int nLength = -1);
	LPCTSTR GetData();

	void SetAt(int nIndex, TCHAR ch);
	operator LPCTSTR() const;

	TCHAR operator[] (int nIndex) const;
	const CStdString& operator=(const CStdString& src);
	const CStdString& operator=(const TCHAR ch);
	const CStdString& operator=(LPCTSTR pstr);
#ifndef _UNICODE
	const CStdString& CStdString::operator=(LPCWSTR lpwStr);
#endif
	CStdString operator+(const CStdString& src);
	CStdString operator+(LPCTSTR pstr);
	const CStdString& operator+=(const CStdString& src);
	const CStdString& operator+=(LPCTSTR pstr);
	const CStdString& operator+=(const TCHAR ch);

	bool operator == (LPCTSTR str) const;
	bool operator != (LPCTSTR str) const;
	bool operator <= (LPCTSTR str) const;
	bool operator <  (LPCTSTR str) const;
	bool operator >= (LPCTSTR str) const;
	bool operator >  (LPCTSTR str) const;

	int Compare(LPCTSTR pstr) const;
	int CompareNoCase(LPCTSTR pstr) const;

	void MakeUpper();
	void MakeLower();

	CStdString Left(int nLength) const;
	CStdString Mid(int iPos, int nLength = -1) const;
	CStdString Right(int nLength) const;

	int Find(TCHAR ch, int iPos = 0) const;
	int Find(LPCTSTR pstr, int iPos = 0) const;
	int ReverseFind(TCHAR ch) const;
	int Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo);

	void ProcessResourceTokens();
	int __cdecl Format(LPCTSTR pstrFormat, ...);
	int __cdecl SmallFormat(LPCTSTR pstrFormat, ...);

protected:
	LPTSTR m_pstr;
	TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN + 1];
};

/////////////////////////////////////////////////////////////////////////////////////
//

struct TITEM
{
	CStdString Key;
	LPVOID Data;
	struct TITEM* pPrev;
	struct TITEM* pNext;
};

class UILIB_API CStdStringPtrMap
{
public:
	CStdStringPtrMap(int nSize = 83);
	~CStdStringPtrMap();

	void Resize(int nSize = 83);
	LPVOID Find(LPCTSTR key, bool optimize = true) const;
	bool Insert(LPCTSTR key, LPVOID pData);
	LPVOID Set(LPCTSTR key, LPVOID pData);
	bool Remove(LPCTSTR key);
	void RemoveAll();
	int GetSize() const;
	LPCTSTR GetAt(int iIndex) const;
	LPCTSTR operator[] (int nIndex) const;

protected:
	TITEM** m_aT;
	int m_nBuckets;
	int m_nCount;
};


#endif // __UIBASE_H__20121015_9CD9_47F7_A794_2050208FA2E6__INCLUDED_
