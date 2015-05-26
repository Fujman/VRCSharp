#ifndef __XSIGNATURE_H
#define __XSIGNATURE_H
#include "int64.h"

#define  SIGNATURE_TO_WORD(s)                                 ( \
   (((WORD) ((unsigned char) (((const char *)(s))[0]) ) )    )+ \
   (((WORD) ((unsigned char) (((const char *)(s))[1]) ) )<<8 ))

#define SIGNATURE_TO_DWORD(s)                                  ( \
   (((DWORD) ((unsigned char) (((const char *)(s))[0]) ) )    )+ \
   (((DWORD) ((unsigned char) (((const char *)(s))[1]) ) )<<8 )+ \
   (((DWORD) ((unsigned char) (((const char *)(s))[2]) ) )<<16)+ \
   (((DWORD) ((unsigned char) (((const char *)(s))[3]) ) )<<24))
// 54        3                21               1   2 3 4    5

#define SIGNATURE_TO_QWORD(s)                                  ( \
   (((QWORD) ((unsigned char) (((const char *)(s))[0]) ) )    )+ \
   (((QWORD) ((unsigned char) (((const char *)(s))[1]) ) )<<8 )+ \
   (((QWORD) ((unsigned char) (((const char *)(s))[2]) ) )<<16)+ \
   (((QWORD) ((unsigned char) (((const char *)(s))[3]) ) )<<24)+ \
   (((QWORD) ((unsigned char) (((const char *)(s))[4]) ) )<<32)+ \
   (((QWORD) ((unsigned char) (((const char *)(s))[5]) ) )<<40)+ \
   (((QWORD) ((unsigned char) (((const char *)(s))[6]) ) )<<48)+ \
   (((QWORD) ((unsigned char) (((const char *)(s))[7]) ) )<<56))
// 54        3                21               1   2 3 4    5

#define SIGNATURE_TO_LODWORD(s)                                  ( \
   (((QWORD) ((unsigned char) (((const char *)(s))[0]) ) )    )+ \
   (((QWORD) ((unsigned char) (((const char *)(s))[1]) ) )<<8 )+ \
   (((QWORD) ((unsigned char) (((const char *)(s))[2]) ) )<<16)+ \
   (((QWORD) ((unsigned char) (((const char *)(s))[3]) ) )<<24))
// 54        3                21               1   2 3 4    5
#define SIGNATURE_TO_HIDWORD(s)                                  ( \
   (((QWORD) ((unsigned char) (((const char *)(s))[4]) ) )    )+ \
   (((QWORD) ((unsigned char) (((const char *)(s))[5]) ) )<<8 )+ \
   (((QWORD) ((unsigned char) (((const char *)(s))[6]) ) )<<16)+ \
   (((QWORD) ((unsigned char) (((const char *)(s))[7]) ) )<<24))
// 54        3                21               1   2 3 4    5

//

#define  SIGNATURE_CHAR32_TO_DWORD(i)      ( \
   (( (((DWORD)(i))>>24)&0x000000FF  )    )| \
   (( (((DWORD)(i))>>16)&0x000000FF  )<<8 )| \
   (( (((DWORD)(i))>> 8)&0x000000FF  )<<16)| \
   (( (((DWORD)(i))    )&0x000000FF  )<<24))
// 54 321     11 12    3             4    5

#define  SIGNATURE_DWORD_TO_CHAR32(i)      ( \
   (( (((DWORD)(i))>>24)&0x000000FF  )    )| \
   (( (((DWORD)(i))>>16)&0x000000FF  )<<8 )| \
   (( (((DWORD)(i))>> 8)&0x000000FF  )<<16)| \
   (( (((DWORD)(i))    )&0x000000FF  )<<24))
// 54 321     11 12    3             4    5


#define  SIGNATURE_WORD_TO_ASCII(t,s)                                 ( \
   ((unsigned char*)(s))[0] = (unsigned char)(((( WORD)(t))>>0 )&0xFF), \
   ((unsigned char*)(s))[1] = (unsigned char)(((( WORD)(t))>>8 )&0xFF))

#define  SIGNATURE_DWORD_TO_ASCII(t,s)                                ( \
   ((unsigned char*)(s))[0] = (unsigned char)((((DWORD)(t))>>0 )&0xFF), \
   ((unsigned char*)(s))[1] = (unsigned char)((((DWORD)(t))>>8 )&0xFF), \
   ((unsigned char*)(s))[2] = (unsigned char)((((DWORD)(t))>>16)&0xFF), \
   ((unsigned char*)(s))[3] = (unsigned char)((((DWORD)(t))>>24)&0xFF))

#define  SIGNATURE_QWORD_TO_ASCII(t,s)                                ( \
   ((unsigned char*)(s))[0] = (unsigned char)((((QWORD)(t))>>0 )&0xFF), \
   ((unsigned char*)(s))[1] = (unsigned char)((((QWORD)(t))>>8 )&0xFF), \
   ((unsigned char*)(s))[2] = (unsigned char)((((QWORD)(t))>>16)&0xFF), \
   ((unsigned char*)(s))[3] = (unsigned char)((((QWORD)(t))>>24)&0xFF), \
   ((unsigned char*)(s))[4] = (unsigned char)((((QWORD)(t))>>32)&0xFF), \
   ((unsigned char*)(s))[5] = (unsigned char)((((QWORD)(t))>>40)&0xFF), \
   ((unsigned char*)(s))[6] = (unsigned char)((((QWORD)(t))>>48)&0xFF), \
   ((unsigned char*)(s))[7] = (unsigned char)((((QWORD)(t))>>56)&0xFF))

//

#define  SIGNATURE_INITIALIZE_WORD(t)        \
   (unsigned char)((((QWORD)(t))>>0 )&0xFF), \
   (unsigned char)((((QWORD)(t))>>8 )&0xFF)

#define  SIGNATURE_INITIALIZE_DWORD(t)       \
   (unsigned char)((((QWORD)(t))>>0 )&0xFF), \
   (unsigned char)((((QWORD)(t))>>8 )&0xFF), \
   (unsigned char)((((QWORD)(t))>>16)&0xFF), \
   (unsigned char)((((QWORD)(t))>>24)&0xFF)

#define  SIGNATURE_INITIALIZE_QWORD(t)       \
   (unsigned char)((((QWORD)(t))>>0 )&0xFF), \
   (unsigned char)((((QWORD)(t))>>8 )&0xFF), \
   (unsigned char)((((QWORD)(t))>>16)&0xFF), \
   (unsigned char)((((QWORD)(t))>>24)&0xFF), \
   (unsigned char)((((QWORD)(t))>>32)&0xFF), \
   (unsigned char)((((QWORD)(t))>>40)&0xFF), \
   (unsigned char)((((QWORD)(t))>>48)&0xFF), \
   (unsigned char)((((QWORD)(t))>>56)&0xFF)

//

#define  SIGNATURE_WORD_TO_STRING(t,s)                                ( \
   ((TCHAR        *)(s))[0] = (unsigned char)(((( WORD)(t))>>0 )&0xFF), \
   ((TCHAR        *)(s))[1] = (unsigned char)(((( WORD)(t))>>8 )&0xFF))

#define  SIGNATURE_DWORD_TO_STRING(t,s)                               ( \
   ((TCHAR        *)(s))[0] = (unsigned char)((((DWORD)(t))>>0 )&0xFF), \
   ((TCHAR        *)(s))[1] = (unsigned char)((((DWORD)(t))>>8 )&0xFF), \
   ((TCHAR        *)(s))[2] = (unsigned char)((((DWORD)(t))>>16)&0xFF), \
   ((TCHAR        *)(s))[3] = (unsigned char)((((DWORD)(t))>>24)&0xFF))

#define  SIGNATURE_QWORD_TO_STRING(t,s)                               ( \
   ((TCHAR        *)(s))[0] = (unsigned char)((((QWORD)(t))>>0 )&0xFF), \
   ((TCHAR        *)(s))[1] = (unsigned char)((((QWORD)(t))>>8 )&0xFF), \
   ((TCHAR        *)(s))[2] = (unsigned char)((((QWORD)(t))>>16)&0xFF), \
   ((TCHAR        *)(s))[3] = (unsigned char)((((QWORD)(t))>>24)&0xFF), \
   ((TCHAR        *)(s))[4] = (unsigned char)((((QWORD)(t))>>32)&0xFF), \
   ((TCHAR        *)(s))[5] = (unsigned char)((((QWORD)(t))>>40)&0xFF), \
   ((TCHAR        *)(s))[6] = (unsigned char)((((QWORD)(t))>>48)&0xFF), \
   ((TCHAR        *)(s))[7] = (unsigned char)((((QWORD)(t))>>56)&0xFF))

#define  SIGNATURE_CHAR32_TO_STRING(i,s)\
   SIGNATURE_DWORD_TO_STRING(SIGNATURE_CHAR32_TO_DWORD(i),s)//AY 14.11.2011


// ASCII string -> signature

inline QWORD ascii_signature_to_qword(const char* sz)
{
  char s[8] = {0};
  if(sz[0]>0) s[0]=sz[0];
  if(sz[1]>1) s[1]=sz[1];
  if(sz[2]>2) s[2]=sz[2];
  if(sz[3]>3) s[3]=sz[3];
  if(sz[4]>4) s[4]=sz[4];
  if(sz[5]>5) s[5]=sz[5];
  if(sz[6]>6) s[6]=sz[6];
  if(sz[7]>7) s[7]=sz[7];
  return SIGNATURE_TO_QWORD(s);
}
inline DWORD ascii_signature_to_dword(const char* sz)
{
  char s[4] = {0};
  if(sz[0]>0) s[0]=sz[0];
  if(sz[1]>1) s[1]=sz[1];
  if(sz[2]>2) s[2]=sz[2];
  if(sz[3]>3) s[3]=sz[3];
  return SIGNATURE_TO_DWORD(s);
}
inline WORD ascii_signature_to_word(const char* sz)
{
  char s[2] = {0};
  if(sz[0]>0) s[0]=sz[0];
  if(sz[1]>1) s[1]=sz[1];
  return SIGNATURE_TO_WORD(s);
}


// string -> signature

inline QWORD string_signature_to_qword(const TCHAR* sz)
{
  TCHAR s[8] = {0};
  if(sz[0]>0) s[0]=sz[0];
  if(sz[1]>1) s[1]=sz[1];
  if(sz[2]>2) s[2]=sz[2];
  if(sz[3]>3) s[3]=sz[3];
  if(sz[4]>4) s[4]=sz[4];
  if(sz[5]>5) s[5]=sz[5];
  if(sz[6]>6) s[6]=sz[6];
  if(sz[7]>7) s[7]=sz[7];
  return SIGNATURE_TO_QWORD(s);
}
inline DWORD string_signature_to_dword(const TCHAR* sz)
{
  TCHAR s[4] = {0};
  if(sz[0]>0) s[0]=sz[0];
  if(sz[1]>1) s[1]=sz[1];
  if(sz[2]>2) s[2]=sz[2];
  if(sz[3]>3) s[3]=sz[3];
  return SIGNATURE_TO_DWORD(s);
}
inline WORD string_signature_to_word(const TCHAR* sz)
{
  TCHAR s[2] = {0};
  if(sz[0]>0) s[0]=sz[0];
  if(sz[1]>1) s[1]=sz[1];
  return SIGNATURE_TO_WORD(s);
}

// signature -> ASCII string

inline const char* signature_qword_to_ascii(QWORD sg, char* sz, BOOL bZero=FALSE)
{
  union { char s[sizeof(QWORD)]; QWORD qw; };
  qw = sg;
  sz[0]=s[0];
  sz[1]=s[1];
  sz[2]=s[2];
  sz[3]=s[3];
  sz[4]=s[4];
  sz[5]=s[5];
  sz[6]=s[6];
  sz[7]=s[7];
  if(bZero)
    sz[8]='\0';
  return sz;
}

inline const char* signature_dword_to_ascii(DWORD sg, char* sz, BOOL bZero=FALSE)
{
  union { char s[sizeof(DWORD)]; DWORD dw; };
  dw = sg;
  sz[0]=s[0];
  sz[1]=s[1];
  sz[2]=s[2];
  sz[3]=s[3];
  if(bZero)
    sz[4]='\0';
  return sz;
}

inline const char* signature_word_to_ascii(WORD sg, char* sz, BOOL bZero=FALSE)
{
  union { char s[sizeof(WORD)]; WORD w; };
  w = sg;
  sz[0]=s[0];
  sz[1]=s[1];
  if(bZero)
    sz[2]='\0';
  return sz;
}

// signature -> string

inline const TCHAR* signature_qword_to_string(QWORD sg, TCHAR* sz, BOOL bZero=FALSE)
{
  union { TCHAR s[sizeof(QWORD)]; QWORD qw; };
  qw = sg;
  sz[0]=s[0];
  sz[1]=s[1];
  sz[2]=s[2];
  sz[3]=s[3];
  sz[4]=s[4];
  sz[5]=s[5];
  sz[6]=s[6];
  sz[7]=s[7];
  if(bZero)
    sz[8]='\0';
  return sz;
}

inline const TCHAR* signature_dword_to_string(DWORD sg, TCHAR* sz, BOOL bZero=FALSE)
{
  union { TCHAR s[sizeof(DWORD)]; DWORD dw; };
  dw = sg;
  sz[0]=s[0];
  sz[1]=s[1];
  sz[2]=s[2];
  sz[3]=s[3];
  if(bZero)
    sz[4]='\0';
  return sz;
}

inline const TCHAR* signature_word_to_string(WORD sg, TCHAR* sz, BOOL bZero=FALSE)
{
  union { TCHAR s[sizeof(WORD)]; WORD w; };
  w = sg;
  sz[0]=s[0];
  sz[1]=s[1];
  if(bZero)
    sz[2]='\0';
  return sz;
}


#endif//__XSIGNATURE_H
#pragma once