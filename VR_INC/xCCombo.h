//UNICODE
#ifndef __XCCOMBO_H
#define __XCCOMBO_H
#include "xCWnd.h"

inline void CComboBox__AdjustSizeByContent(CComboBox* pCombo, int nMaxLines=10, LPCTSTR szMinWidth=_T("HHHHHHHH"))
{
    // Find the longest string in the combo box.
    CString str;
    CSize   siz;
    int     dx=0;
    int     dy=0;
    CDC*    pDC = pCombo->GetDC();
    if(szMinWidth!=NULL)
      dx = (pDC->GetTextExtent(szMinWidth,_tcslen(szMinWidth))).cx;
    for(int i=0; i<pCombo->GetCount(); i++) {
       pCombo->GetLBText( i, str );
       siz = pDC->GetTextExtent(str);
       if(siz.cx > dx)
         dx = siz.cx;
       if(i<nMaxLines)
         dy += siz.cy;
    }
    pCombo->ReleaseDC(pDC);
    // Adjust the width for the vertical scroll bar and the left and right border.
    dx += ::GetSystemMetrics(SM_CXVSCROLL) + 2*::GetSystemMetrics(SM_CXEDGE);
    dy += ::GetSystemMetrics(SM_CYVSCROLL) + 2*::GetSystemMetrics(SM_CYEDGE);
    // Set the width of the list box so that every item is completely visible.
    CRect rc = CWnd__GetRect(pCombo);
    rc.bottom += dy;
    CWnd__SetRect(pCombo, rc);
    if(szMinWidth!=NULL)
      pCombo->SetDroppedWidth(dx);
}

#endif//__XCCOMBO_H