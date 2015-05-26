#ifndef __MESSAGE_H
#define __MESSAGE_H

/*
#ifdef  WIN32 //Extract in the 32-bit framework:
  UINT nID = LOWORD(msg->wParam);           //Command ID
  HWND hWndCtrl = (HWND)(msg->lParam);	    //Control handle
  int nCode = HIWORD(msg->wParam);	        //Notification code
#else         //Extract in the 16-bit framework:
  UINT nID = msg->wParam;                   //Command ID
  HWND hWndCtrl = (HWND)LOWORD(msg->lParam);//Control handle
  int nCode = HIWORD(msg->lParam);	        //Notification code
#endif
*/

inline HWND GetCommandCtrlHWND(const MSG *msg) 
{
#ifdef  WIN32 //Extract in the 32-bit framework:
  return (HWND)(msg->lParam);	      //Control handle
#else         //Extract in the 16-bit framework:
  return (HWND)LOWORD(msg->lParam); //Control handle
#endif
}


inline int GetCommandNotificationCode(const MSG *msg) 
{
#ifdef  WIN32 //Extract in the 32-bit framework:
  return HIWORD(msg->wParam);	        //Notification code
#else         //Extract in the 16-bit framework:
  return HIWORD(msg->lParam);	        //Notification code
#endif
}

inline void MakeCommandMessageParams(
  int nID, int nCode, HWND hWnd, 
  WPARAM& wParam, LPARAM& lParam) 
{
#ifdef  WIN32 //Extract in the 32-bit framework:
  wParam = (WORD)nID;                       //Command ID
  lParam = (DWORD)hWnd;                     //Control handle
  wParam += (((DWORD) ((UINT)(nCode)))<<16);//Notification code
#else        //Extract in the 16-bit framework:
  wParam = (WORD)nID;                       //Command ID
  lParam = (WORD)hWnd;                      //Control handle
  lParam += (((DWORD) ((UINT)(nCode)))<<16);//Notification code
#endif
}

inline BOOL PostCommandMessage(CWnd *wnd, UINT nID, UINT nCode, HWND hWnd) 
{
  WPARAM wParam; LPARAM lParam;
  MakeCommandMessageParams(nID,nCode,hWnd,wParam,lParam);
  return wnd->PostMessage(WM_COMMAND,wParam,lParam);
}

inline LRESULT SendCommandMessage(CWnd *wnd, UINT nID, UINT nCode, HWND hWnd) 
{
  WPARAM wParam; LPARAM lParam;
  MakeCommandMessageParams(nID,nCode,hWnd,wParam,lParam);
  return wnd->SendMessage(WM_COMMAND,wParam,lParam);
}

inline BOOL IsCommandMessageFromKeyboard(const MSG *msg)
{
  return 
    msg->message == WM_COMMAND &&
    GetCommandCtrlHWND(msg) == NULL && 
    GetCommandNotificationCode(msg) != 0;
}

inline BOOL IsCommandMessageFromMenu(const MSG *msg)
{
  return 
    msg->message == WM_COMMAND &&
    GetCommandCtrlHWND(msg) == NULL && 
    GetCommandNotificationCode(msg) == 0;
}

inline BOOL IsCommandMessageFromControl(const MSG *msg)
{
  return 
    msg->message == WM_COMMAND &&
    GetCommandCtrlHWND(msg)!=NULL;
}

#endif//__MESSAGE_H
#pragma once