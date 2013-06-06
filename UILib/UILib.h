// DirectUI.h


#ifdef UILIB_EXPORTS
#define UILIB_API __declspec(dllexport)
#else
#define UILIB_API __declspec(dllimport)
#endif

#define _CRT_SECURE_NO_DEPRECATE // Don't bother us about depricated functions


// Include
#pragma once
#include <windows.h>
#include <WindowsX.h>
#include <commctrl.h>
#include <tchar.h>
#include <afxcom_.h>
#include <atlstr.h>

//#include <GdiPlus.h>
//#pragma comment( lib, "GdiPlus.lib" )
//using namespace Gdiplus;


#include "UIBase.h"
#include "UIManager.h"
#include "UIControl.h"
#include "UILabel.h"
#include "UIButton.h"
#include "UIContainer.h"
#include "UIBlue.h"
#include "UIEdit.h"
#include "UILayout.h"
#include "UIDialog.h"


