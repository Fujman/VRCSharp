#ifndef __XCMOUSE_H
#define __XCMOUSE_H
#include <afxtempl.h>
#include "xpragma.h"
#include "ycookie.h"

#if(_WIN32_WINNT < 0x0500)
#pragma message(__FILE__LINE__ ": warning : force defininig Windows 5.0 only macroses")
#endif

#ifndef MK_XBUTTON1
#define MK_XBUTTON1         0x0020
#endif

#ifndef MK_XBUTTON2
#define MK_XBUTTON2         0x0040
#endif

////////////////////////////////////////////////////////////////////////////////////////
// CWinApp__MouseWheel
//
/* Usage example: 
  HANDLE hMouseWheelCallback = NULL;

  CWinApp::PreTranslateMessage(MSG* pMsg)
  {
    LRESULT lRet = CWinApp__MouseWheel::PreTranslateMouseWheelMessage(pMsg);
    if(lRet)
      return lRet;
    ...
    return 0;
  }

  CWinApp::InitInstance()
  {
    hMouseWheelCallback = CWinApp__MouseWheel::RegisterMouseWheelCallback(proc,(CWnd*)pWnd);
    //...
  }  
  CWinApp::ExitInstance()
  {
    hMouseWheelCallback = CWinApp__MouseWheel::UnegisterMouseWheelCallback(hMouseWheelCallback);
    //...
  }  
*/
class CWinApp__MouseWheel
{
public:
  typedef LRESULT (CALLBACK *ON_WM_MOUSEWHEEL_PROC)(void* pThis, UINT message, WPARAM wParam, LPARAM lParam);

  static  HANDLE  RegisterMouseWheelCallback(ON_WM_MOUSEWHEEL_PROC proc, void* pThis, HWND hwnd=NULL, UINT nFlags=0);
  static  HANDLE  UnregisterMouseWheelCallback(HANDLE handle);
  static  LRESULT PreTranslateMouseWheelMessage(MSG* pMsg);
protected:
  typedef struct { ON_WM_MOUSEWHEEL_PROC proc; void* pThis; HWND hwnd; UINT nFlags; HANDLE handle; }
                  CALLBACK_DESCRIPTION;
  static  CMap< HANDLE,HANDLE,CALLBACK_DESCRIPTION,CALLBACK_DESCRIPTION& > 
                  m_map;
  static  YCookie m_cookie;
};

#endif//__XCMOUSE_H
#pragma once