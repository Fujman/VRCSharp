#ifndef __YRTFTEXT_H
#define __YRTFTEXT_H

#include <afxwin.h>
#include <richedit.h>
#include <afxcoll.h>
#include <afxrich.h>
#include <atlconv.h> 
#include "YText.h"

/////////////////////////////////////////////////////////////////////////////
// CRTFText
class CRTFText  : public CSimpleTextA
{
  typedef CSimpleTextA CParent;
public:
                CRTFText();
  int           Save(LPCTSTR szFileName) const;
  int           Save2(LPCTSTR szFileName) const; //patch rtf font table + save file
  int           Load(LPCTSTR szFileName);

  int           SetRTFText(const void* pText, UINT  nSize, int nBufType=0);

  int           GetRichEditCtrl(CRichEditCtrl* pRichEdit);
  int           SetRichEditCtrl(CRichEditCtrl* pRichEdit);
  
  static BOOL   PatchFontTable(const BYTE* pDataSrc, int nDataSize, BYTE** pDataTrg, int& nDataSizeTrg);
protected:
  static void   _PatchFontTable(const BYTE* pDataSrc, int nMaxDataLen, int nStartPosOrg, YStringA& szPatchedTable,int& nEndPosOrg);
  static int    FindAndPatchFontString(const BYTE* pDataSrc, int naxDataLen, int nStartPos,YStringA& szPatched,int& nEndPos);

  static  DWORD CALLBACK EditStreamCallback(DWORD dwCookie, // application-defined value
                                            LPBYTE pbBuff,  // pointer to a buffer
                                            LONG cb,        // number of bytes to read or write
                                            LONG *pcb       // pointer to number of bytes transferred
                                            );
  DWORD         GetCallback(LPBYTE pbBuff, LONG cb, LONG *pcb);
  DWORD         SetCallback(LPBYTE pbBuff, LONG cb, LONG *pcb);
  int           m_isRead;
  ULONG         m_nOffset;
};

#endif//__YRTFTEXT_H
#pragma once
