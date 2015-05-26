#ifndef __XCICON_H
#define __XCICON_H

#define DECLARE_ICON_S(ID) static HICON hicon##ID=NULL; (hicon##ID==NULL?hicon##ID=::AfxGetApp()->LoadIcon(_T(#ID)):NULL)

#define DECLARE_ICON(ID)   static HICON hicon##ID=NULL; (hicon##ID==NULL?hicon##ID=::AfxGetApp()->LoadIcon(ID):NULL)

#define SET_BUTTON_ICON(CtrlID,ID) \
  static HICON hicon##ID=NULL; (hicon##ID==NULL?hicon##ID=::AfxGetApp()->LoadIcon(ID):NULL);\
  ((CButton*)GetDlgItem(CtrlID))->SetIcon(hicon##ID);

/* Usage:
   CWnd::Create() {
     DECLARE_ICON(IDI_ICON1);
     DECLARE_ICON(IDI_ICON2);
     HICON ahIcons = {hiconIDI_ICON1, hiconIDI_ICON2};
     ...
   }
*/

#endif//__XCICON_H
#pragma once
