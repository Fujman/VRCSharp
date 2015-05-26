#ifndef __XCLIST_H
#define __XCLIST_H
#include <afxcmn.h>
#include "c_array.h"
////////////////////////////////////////////////////////////////////////////////
// global expansions

void CListCtrl__SaveSettings(CListCtrl* pList, LPCTSTR szIniSection, LPCTSTR szListName=NULL);
void CListCtrl__LoadSettings(CListCtrl* pList, LPCTSTR szIniSection, LPCTSTR szListName=NULL);

////////////////////////////////////////////////////////////////////////////////
// extended styles

#ifndef LVS_EX_LABELTIP
const int LVS_EX_LABELTIP = 0x00004000;
#endif

#define ListView_AddExtendedListViewStyle(hwnd,style) \
  ListView_SetExtendedListViewStyle((hwnd),(style)|ListView_GetExtendedListViewStyle(hwnd))

#define ListView_RemExtendedListViewStyle(hwnd,style) \
  ListView_SetExtendedListViewStyle((hwnd),(~(style))&ListView_GetExtendedListViewStyle(hwnd))

////////////////////////////////////////////////////////////////////////////////
// CListCtrl__
// return items count
inline int CListCtrl__GetMultipleSelectBounds(CListCtrl& list, int* pnFirstItem=NULL, int* pnLastItem=NULL)
{
  POSITION pos = list.GetFirstSelectedItemPosition();
  int nFirstItem = -1;
  int nLastItem  = -1;
  int nItems = 0;
  while(pos){
    int nItem = list.GetNextSelectedItem(pos);
    if(nFirstItem<0)
      nFirstItem = nItem;
    nLastItem = nItem;
    nItems++;
  }
  if(pnFirstItem!=NULL) *pnFirstItem = nFirstItem;
  if(pnLastItem!=NULL)  *pnLastItem = nLastItem;
  return nItems;
}


inline int CListCtrl__GetSubselection(CListCtrl& list, int iSelection, int* pnFirstItem=NULL, int* pnLastItem=NULL)
{
    POSITION pos = list.GetFirstSelectedItemPosition();
    int nFirstItem = -1;
    int nLastItem  = -1;
    int nItems = 0;
    while(pos){
        int nItem = list.GetNextSelectedItem(pos);
        if(nFirstItem<0)
        {    nFirstItem = nItem; }
        else
            if(nItem!=nLastItem+1)
            {
                if(iSelection == 0)
                    break;
                iSelection--;
                nFirstItem = nItem;
                nItems = 0;
            }

        nLastItem = nItem;
        nItems++;
    }
    if(iSelection>0){
        nItems = 0;
        if(pnFirstItem!=NULL) *pnFirstItem = -1;
        if(pnLastItem!=NULL)  *pnLastItem = -1;

    }
    else{
      if(pnFirstItem!=NULL) *pnFirstItem = nFirstItem;
      if(pnLastItem!=NULL)  *pnLastItem = nLastItem;
    }
    return nItems;
}



////////////////////////////////////////////////////////////////////////////////
// XCListCtrl

template <class CLISTCTRL=CListCtrl>
class XCListCtrl :      public CLISTCTRL
{
public:
  int                   AddItemAndData(LPCTSTR  sz, int nColumn, DWORD dwData);//10.05.2012
  int                   AddItem(LPCTSTR  sz, int nColumn=0);
  int                   RemoveItem(int iItem=-1);
  int                   SetItemImage(int nImage, int iItem, int nColumn=0);
  int                   SetItem(LPCTSTR  sz, int iItem, int nColumn=0);
  int                   GetItem(CString& sz, int iItem, int nColumn=0) const;

  CString               GetItem(int iItem, int nColumn=0) const;
  int                   GetSize() const;
  int                   FindByData(DWORD dwData);

  int                   SetCurrentItem(LPCTSTR  sz, int nColumn=0);
  int                   GetCurrentItem(CString& sz, int nColumn=0) const;

  int                   SetCurrentItem(int iItem);//AY 05.02.2010
  int                   GetCurrentItem() const;   //AY 05.02.2010
  int                   IsItemNonSelected(int iItem) const;

  int                   SetActive(int iItem=-1);
  int                   ClearSelection();//AY 23.04.2003

  int                   GetColumnsCount();
//int                   GetItemsCount();

  void                  SaveSettings(LPCTSTR szIniSection, LPCTSTR szListName=NULL);
  void                  LoadSettings(LPCTSTR szIniSection, LPCTSTR szListName=NULL);

  int                   FindItemString(int nStart, LPCTSTR lpszItem, int nColumn=0) const; //AY 15.02.2010  Note: Not As CListBox nStartAfter!

  int                   SetSel(int nIndex, BOOL bSelect=TRUE, int nColumn=0); //like as CListBox //AY 05.01.2012
};


template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::GetSize()const
{
  return GetItemCount();
}

template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::AddItemAndData(LPCTSTR  sz, int nColumn, DWORD dwData)//10.05.2012
{
  int iItem = AddItem(LPCTSTR sz, int nColumn);
  SetItemData(iItem,dwData);
  return iItem;
}

template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::AddItem(LPCTSTR  sz, int nColumn)
{
  LVITEM lvitem = {0};
  lvitem.mask = LVIF_TEXT;
  lvitem.iItem = GetSize();
  lvitem.iSubItem = nColumn;
  lvitem.pszText = (LPTSTR) sz;
//lvitem.cchTextMax = sizeof(sz);
//lvitem.lParam = 0;
  int iRet = CListCtrl::InsertItem(&lvitem);
  ASSERT(iRet>=0);
  return iRet;
}

template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::GetItem(CString& _sz, int iItem, int nColumn) const {
  TCHAR sz[1024];
  int i = iItem;
  if(i==-1){
    _sz = _T("");
  }else{
    LVITEM lvitem;
    lvitem.mask = LVIF_TEXT;
    lvitem.iItem = i;
    lvitem.iSubItem = nColumn;
    lvitem.pszText = sz;
    lvitem.cchTextMax = countof(sz);
    lvitem.lParam = 0;
    BOOL bRet = CListCtrl::GetItem(&lvitem);
    if(bRet) {
      _sz = sz;
    }else {
      _sz = _T("");
      i = -1;//AY 05.02.2010
    }
  }
  return i;
}

template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::SetItem(LPCTSTR _sz, int iItem, int nColumn){
//char sz[1024];  //KSN 10.09.02
  TCHAR sz[1024]; //KSN 10.09.02 //AY 18.02.2009 256->1024
  ASSERT(_tcslen(_sz)+1<countof(sz));
  _tcsnccpy(sz,_sz,countof(sz));
  sz[countof(sz)-1] = '\0';//AY 18.02.2009
  int i = iItem;
  {
    LVITEM lvitem;
    lvitem.mask = LVIF_TEXT;
    lvitem.iItem = i;
    lvitem.iSubItem = nColumn;
    lvitem.pszText = sz;
    lvitem.cchTextMax = countof(sz);
    lvitem.lParam = 0;
    BOOL bRet = CListCtrl::SetItem(&lvitem);
  }
  return i;
}

template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::SetItemImage(int nImage, int iItem, int nColumn/*0*/)
{
  int i = iItem;
  {
    LVITEM lvitem = {0};
    lvitem.mask = LVIF_IMAGE;
    lvitem.iItem = i;
    lvitem.iSubItem = nColumn;
    lvitem.iImage = nImage;
    lvitem.lParam = 0;
    BOOL bRet = CListCtrl::SetItem(&lvitem);
    if(!bRet)//AY 10.09.2004
      return -1;
  }
  return i;
}

template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::GetCurrentItem() const
{
  return GetNextItem(-1,LVNI_SELECTED);
}

template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::GetCurrentItem(CString& _sz, int nColumn) const {
  TCHAR sz[1024];
  int i = GetNextItem(-1,LVNI_SELECTED);
  if(i==-1){
    _sz = _T("");
  }else{
    LVITEM lvitem;
    lvitem.mask = LVIF_TEXT;
    lvitem.iItem = i;
    lvitem.iSubItem = nColumn;
    lvitem.pszText = sz;
    lvitem.cchTextMax = countof(sz);
    lvitem.lParam = 0;
    BOOL bRet = CListCtrl::GetItem(&lvitem);
    if(bRet)
      _sz = sz;
    else
      _sz = _T("");
  }
  return i;
}

template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::IsItemNonSelected(int iItem) const { //AY 05.02.2010
  if(iItem<0){
    return -1;
  }else{
    LVITEM lvitem = {0};
    lvitem.mask = LVIF_STATE;
    lvitem.iItem = iItem;
    BOOL bRet = CListCtrl::GetItem(&lvitem);
    if(!bRet)
      return -1;
    if(lvitem.mask&LVNI_SELECTED)
      return 0;
  }
  return 1;
}

template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::SetCurrentItem(LPCTSTR _sz, int nColumn){
  TCHAR sz[1024]; ASSERT(_tcslen(_sz)+1<countof(sz));
  _tcsncpy(sz,_sz,countof(sz)); sz[countof(sz)-1] = '\0';
  int i = GetNextItem(-1,LVNI_SELECTED);
  {
    LVITEM lvitem;
    lvitem.mask = LVIF_TEXT;
    lvitem.iItem = i;
    lvitem.iSubItem = nColumn;
    lvitem.pszText = sz;
    lvitem.cchTextMax = countof(sz);
    lvitem.lParam = 0;
    BOOL bRet = CListCtrl::SetItem(&lvitem);
  }
  return i;
}


template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::SetActive(int iItem/*-1*/)
{
  if(iItem==-1) {
    iItem = GetNextItem(-1,LVNI_SELECTED);
    if(iItem==-1)
      return -1;
  }else{
    int i;
    while((i=GetNextItem(-1,LVNI_SELECTED))!=-1) {
      LVITEM lvitem;
      lvitem.mask = LVIF_STATE;
      lvitem.iItem = i;
      lvitem.iSubItem = 0;
      lvitem.state = 0;//LVIS_FOCUSED|LVIS_SELECTED
      lvitem.stateMask = LVIS_FOCUSED|LVIS_SELECTED;
      BOOL bRet = CListCtrl::SetItem(&lvitem);
    }
  }
  LVITEM lvitem;
  lvitem.mask = LVIF_STATE;
  lvitem.iItem = iItem;
  lvitem.iSubItem = 0;
  lvitem.state = LVIS_FOCUSED|LVIS_SELECTED;
  lvitem.stateMask = LVIS_FOCUSED|LVIS_SELECTED;
  BOOL bRet = CListCtrl::SetItem(&lvitem);
  EnsureVisible(iItem,TRUE);
  return 0;
}

template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::SetCurrentItem(int iItem/*-1*/)
{
  if(iItem==-1) {
    iItem = GetNextItem(-1,LVNI_SELECTED);
    if(iItem==-1)
      return -1;
  }else{
    int i;
    while((i=GetNextItem(-1,LVNI_SELECTED))!=-1) {
      LVITEM lvitem;
      lvitem.mask = LVIF_STATE;
      lvitem.iItem = i;
      lvitem.iSubItem = 0;
      lvitem.state = 0;//LVIS_SELECTED
      lvitem.stateMask = LVIS_SELECTED;
      BOOL bRet = CListCtrl::SetItem(&lvitem);
    }
  }
  LVITEM lvitem;
  lvitem.mask = LVIF_STATE;
  lvitem.iItem = iItem;
  lvitem.iSubItem = 0;
  lvitem.state = LVIS_SELECTED;
  lvitem.stateMask = LVIS_SELECTED;
  BOOL bRet = CListCtrl::SetItem(&lvitem);
//EnsureVisible(iItem,TRUE);
  return 0;
}



template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::ClearSelection()
{
  LVITEM lvitem;
  for(POSITION pos = GetFirstSelectedItemPosition();pos!=NULL;) {
    lvitem.iItem = GetNextSelectedItem(pos);
    lvitem.iSubItem = 0;
    lvitem.mask = LVIF_STATE;
    lvitem.state = 0;//LVIS_SELECTED;//|LVIS_FOCUSED
    lvitem.stateMask = LVIS_SELECTED;//|LVIS_FOCUSED
    CListCtrl::SetItem(&lvitem);
  }
  return 0;
}

template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::SetSel(int nIndex, BOOL bSelect, int nColumn)
{
  LVITEM lvitem = {0};
  lvitem.iItem    = nIndex;
  lvitem.iSubItem = 0;
  lvitem.mask     = LVIF_STATE;
  CListCtrl::GetItem(&lvitem);
  if( ( bSelect && (lvitem.state&LVIS_SELECTED)==0) ||
      (!bSelect && (lvitem.state&LVIS_SELECTED)!=0) ){
    lvitem.state     = bSelect?LVIS_SELECTED:0;
    lvitem.stateMask = LVIS_SELECTED;
    CListCtrl::SetItem(&lvitem);
  }
  return 0;
}



template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::RemoveItem(int iItem/*-1*/)
{
  if(iItem==-1) {
    while((iItem = GetNextItem(-1,LVNI_SELECTED))!=-1)
      DeleteItem(iItem);
  }else{
    DeleteItem(iItem);
  }
  return 0;
}

template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::FindByData(DWORD dwData)
{
  for(int i=0; i<GetItemCount(); ++i){
    if(GetItemData(i)==dwData)
      return i;
  }
  return -1;
}

template <class CLISTCTRL> inline CString
XCListCtrl<CLISTCTRL>::GetItem(int iItem, int nColumn/*0*/) const
{
  CString sz; GetItem(sz,iItem,nColumn); return sz;
}

template <class CLISTCTRL> inline void
XCListCtrl<CLISTCTRL>::SaveSettings(LPCTSTR szIniSection, LPCTSTR szListName)
  { CListCtrl__SaveSettings(this,szIniSection,szListName); }

template <class CLISTCTRL> inline void
XCListCtrl<CLISTCTRL>::LoadSettings(LPCTSTR szIniSection, LPCTSTR szListName)
  { CListCtrl__LoadSettings(this,szIniSection,szListName); }

template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::GetColumnsCount()
{
  int nCount = 0;
  CHeaderCtrl* pCtrl = GetHeaderCtrl();
  ASSERT(pCtrl != NULL);
  if (pCtrl != NULL)
    nCount = pCtrl->GetItemCount();
  return nCount;
}

template <class CLISTCTRL> inline int
XCListCtrl<CLISTCTRL>::FindItemString(int nStart, LPCTSTR lpszItem, int nColumn) const //AY 15.02.2010
{
  ASSERT(nStart>=0);
  for(int i=nStart; i<GetSize(); ++i) {
    if(GetItem(i,nColumn)==lpszItem)
      return i;
  }
  return -1;
}

////////////////////////////////////////////////////////////////////////////////
// XListCtrlAsBox

template <class TLISTCTRL=XCListCtrl<CListCtrl> > class XListCtrlAsBox : public TLISTCTRL
{
public:
  typedef TLISTCTRL     CLISTCTRL;

  int                   GetCurSel( ) const
                          { int iItem = CLISTCTRL::GetCurrentItem(); return iItem<0?LB_ERR:iItem; }

  int                   SetCurSel( int nSelect )
                          { int iItem = CLISTCTRL::SetCurrentItem(nSelect); return iItem<0?LB_ERR:iItem; }//TO DO error processing

  int                   GetText( int nIndex, CString& szString ) const
                          { int iItem = CLISTCTRL::GetItem(szString,nIndex); return iItem<0?LB_ERR:iItem; }

  int                   GetSel( int nIndex ) const
                          { int iItem = CLISTCTRL::IsItemNonSelected(nIndex); return iItem<0?LB_ERR:nIndex; }

  int                   GetCount() const
                          { return CLISTCTRL::GetSize(); }

  int                   AddString(LPCTSTR lpszItem)
                          { int iItem = CLISTCTRL::AddItem(lpszItem); return iItem<0?LB_ERR:iItem; }

  void                  ResetContent()
                          { CLISTCTRL::DeleteAllItems(); }
};



#endif __XCLIST_H
#pragma once
