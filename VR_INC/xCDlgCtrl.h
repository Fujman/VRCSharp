#ifndef __XCDLGCTRL_H
#define __XCDLGCTRL_H

UINT  CDialog__RandomIDC(CDialog* pThis);
int   CDialog__ExpandAfter(CDialog* pThis, CWnd* pAfter, CSize siz, BOOL bResizeWnd=FALSE);
CWnd* CDialog__GetLeft(CWnd* pThis, CWnd* pCtrl);

#endif//__XCDLGCTRL_H
#pragma once
