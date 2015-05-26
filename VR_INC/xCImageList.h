#ifndef __XCIMAGELIST_H
#define __XCIMAGELIST_H
#include <afxcoll.h>
#include "xCIcon.h"

////////////////////////////////////////////////////////////
// macroses based on CImageListEx

#define DECLARE_IMAGE_ICON_S(image,ID)  DECLARE_ICON_S(ID); image.Add(hicon##ID,_T(#ID));
#define DECLARE_IMAGE_ICON(image,ID)    DECLARE_ICON(ID);   image.Add(hicon##ID,_T(#ID));

#define ADD_IMAGE_ICON_S(image,ID)      image.Load(_T(#ID));
#define ADD_IMAGE_ICON(image,ID)        image.Load(ID,_T(#ID));

#define GET_IMAGE_ICON_ID(image,ID)     (image.GetID(_T(#ID)))

////////////////////////////////////////////////////////////
// CImageListEx

class CImageListEx : public CImageList
{
public:
  int     Add(HICON hicon, LPCTSTR szicon);

  int     GetID(LPCTSTR szicon) const;
  int     GetID(UINT uicon) const;

  int     Load(LPCTSTR szicon);
  int     Load(UINT uicon, LPCTSTR szicon=NULL);

protected:
  CMapStringToPtr m_map;
};

inline int  CImageListEx::Add(HICON hicon, LPCTSTR szicon)
{
  int iIdx = CImageList::Add(hicon); ASSERT(iIdx>=0);
  m_map[szicon] = (void*)iIdx;
  return iIdx;
}

inline int  CImageListEx::GetID(LPCTSTR szicon) const
{
  void* iIdx = (void*)-1;
  VERIFY( m_map.Lookup(szicon,iIdx) );
  return (int)iIdx;
}

inline int  CImageListEx::Load(LPCTSTR szicon)
{
  HICON hicon = ::AfxGetApp()->LoadIcon(szicon);
  return Add(hicon,szicon);
}

inline int  CImageListEx::Load(UINT  uicon, LPCTSTR szicon)
{
  HICON hicon = ::AfxGetApp()->LoadIcon(uicon);
  CString szIcon;
  if(szicon==NULL) { 
    szIcon.Format(_T("#08.8X"),uicon); 
    szicon = szIcon; 
  }
  return Add(hicon,szicon);
}

inline int  CImageListEx::GetID(UINT uicon) const
{
  CString szIcon; 
    szIcon.Format(_T("#08.8X"),uicon);
  return GetID((LPCTSTR)szIcon);
}




#endif//__XCIMAGELIST_H
#pragma once