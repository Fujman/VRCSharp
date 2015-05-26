#ifndef __XGUID_H
#define __XGUID_H
#include <stdio.h>

#ifndef  GUID_DEFINED
#include <basetyps.h>
#endif

/* for compare GUID's
#include <objbase.h>
*/

/////////////////////////////////////////////////////////////////
//
// macro STATIC_GUID_S
//

#define STATIC_IS_GUID_S(s) ((int)((s[8])=='-' && s[13]=='-' && s[18]=='-' && s[23]=='-')) //TO DO: check all symbols?

#define STATIC_IS_ABCDEF(s) ( (((BYTE)(*(s)))&0x40)>>6 )
#define STATIC_HEX_SHIFT(s) ( (STATIC_IS_ABCDEF(s)<<2)| \
                              (STATIC_IS_ABCDEF(s)<<1)| \
                              (STATIC_IS_ABCDEF(s)   ) ) //0 or 7
#define STATIC_DEC_SHIFT(s) (  ((BYTE)(*(s)))-0x30 )

#define STATIC_HEXTOXCIF(s) ((DWORD)(STATIC_DEC_SHIFT(s)-STATIC_HEX_SHIFT(s)) )
#define STATIC_HEXTOBYTE(s) ( (BYTE)(STATIC_HEXTOXCIF((s)+1)|(STATIC_HEXTOXCIF(s)<< 4)) )
#define STATIC_HEXTOWORD(s) ( (WORD)(STATIC_HEXTOBYTE((s)+2)|(STATIC_HEXTOBYTE(s)<< 8)) )
#define STATIC_HEXTODWORD(s)((DWORD)(STATIC_HEXTOWORD((s)+4)|(STATIC_HEXTOWORD(s)<<16)) )

//                      0---------1---------2---------3-----
// example:           s:012345678901234567890123456789012345
//  STATIC_GUID_S(name,"f5078f32-c551-11d3-89b9-0000f81fe221")
//

#define STATIC_GUID_S(name, s) static const GUID name = {\
       (1/STATIC_IS_GUID_S(s))*    \
          STATIC_HEXTODWORD(s)    ,\
          STATIC_HEXTOWORD(s+ 8+1),\
          STATIC_HEXTOWORD(s+12+2),\
        { STATIC_HEXTOBYTE(s+16+3),\
          STATIC_HEXTOBYTE(s+18+3),\
          STATIC_HEXTOBYTE(s+20+4),\
          STATIC_HEXTOBYTE(s+22+4),\
          STATIC_HEXTOBYTE(s+24+4),\
          STATIC_HEXTOBYTE(s+26+4),\
          STATIC_HEXTOBYTE(s+28+4),\
          STATIC_HEXTOBYTE(s+30+4) }                    }

///////////////////////////////////////////////////////////////////////////

#define STATIC_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        static const GUID name \
                = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

#define GLOBAL_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        const GUID name \
                = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

///////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

//Parse GUID: "a9b87672-24fd-41e5-b17f-c510eb1edf48"
//             012345678901234567890123456789012345
GUID    str2guid(LPCTSTR szGUID); //ERROR: don't worked! AY 06.09.2011
GUID    str2guidA(LPCSTR szGUID);
GUID    str2guidW(LPCWSTR szGUID);

CString guid2str(const GUID& guid, BOOL bToUpper=FALSE); //use lowercase by default
CString guid2hex(const GUID& guid, BOOL bToUpper=FALSE); //use lowercase by default
GUID    hex2guid(LPCTSTR szHex);

#ifdef __YSTRINGA_H

inline YStringA guid2strA(const GUID& guid, BOOL bToUpper=FALSE) //use lowercase by default
{
  ASSERT(sizeof(WORD)==sizeof(unsigned short));
  ASSERT(sizeof(DWORD)==sizeof(unsigned int));

  LPCSTR szFormat = bToUpper ?
    "%8.8X-%4.4hX-%4.4hX-%4.4hX-%4.4hX%8.8X":
    "%8.8x-%4.4hx-%4.4hx-%4.4hx-%4.4hx%8.8x";
  // Data1 Data2  Data3  aw[0]  aw[1] adw[1]

  union{ DWORD adw[2]; WORD aw[4]; BYTE abyData4[8]; };
  abyData4[1] = guid.Data4[0];//aw[0]
  abyData4[0] = guid.Data4[1];
  abyData4[3] = guid.Data4[2];//aw[1]
  abyData4[2] = guid.Data4[3];
  abyData4[7] = guid.Data4[4];//adw[1]
  abyData4[6] = guid.Data4[5];
  abyData4[5] = guid.Data4[6];
  abyData4[4] = guid.Data4[7];

  YStringA sz; sz.Format(szFormat,
    guid.Data1,
    guid.Data2,
    guid.Data3,
    aw[0],      //pGUID->Data4[0],pGUID->Data4[1],
    aw[1],adw[1]//pGUID->Data4[2],pGUID->Data4[3],pGUID->Data4[4],pGUID->Data4[5],pGUID->Data4[6],pGUID->Data4[7]
  );
  return sz;
}

#endif//__YSTRINGA_H


/////////////////////////////////////////////////////////////////////
//
// Obsolete DWORD <-> serial support  (MREC used)
//

inline GUID dword2guid(DWORD dw, DWORD dwPrefix=2930683552)
{
  GUID guid;
  guid.Data1 = (dw ^ dwPrefix);
  guid.Data2 = 0x0000;//GUID_Data2;
  guid.Data3 = 0x0010;//GUID_Data3;
  ((DWORD *)guid.Data4)[0] = 0xaa000080;//GUID_Data4_1;
  ((DWORD *)guid.Data4)[1] = 0x719b3800;//GUID_Data4_2;
  return guid;
}

inline DWORD guid2dword(const GUID& guid, DWORD dwPrefix=2930683552)
{
  BOOL bOK = TRUE;
  bOK = bOK && (guid.Data2 == 0x0000);
  bOK = bOK && (guid.Data3 == 0x0010);
  bOK = bOK && (((DWORD *)guid.Data4)[0] == 0xaa000080);
  bOK = bOK && (((DWORD *)guid.Data4)[1] == 0x719b3800);
  if(!bOK)
    return 0;
  DWORD dw = guid.Data1;
  return (dw ^ dwPrefix);
}

/////////////////////////////////////////////////////////////////////
//
// Obsolete GUID  <-> serial support //AY 07.11.2011 moved to .cpp
//

CString guid2serial(const GUID& guid, BOOL bToUpper=FALSE, DWORD dwPrefix=2930683552); //use lowercase by default
GUID    serial2guid(LPCTSTR szGUID, DWORD dwPrefix=2930683552);

/////////////////////////////////////////////////////////////////////
//
// MD5 <-> serial support (Base36 based) //AY 07.11.2011
//

CString md52serial(const GUID& guid); //AY 07.11.2011
GUID    serial2md5(LPCTSTR szSerial); //AY 07.11.2011

#endif//__cplusplus

#endif//__XGUID_H
#pragma once
