//////////////////////////////////////////////////////////////////////////////
// yResBase.h
#ifndef __YRESBASE_H
#define __YRESBASE_H

#ifdef  __cplusplus
extern "C" {
#endif

#if defined(UNICODE) || defined(_UNICODE)
  #define LoadStringEx  LoadStringExW
  #define LoadFontEx    LoadFontExW
#else
  #define LoadStringEx  LoadStringExA
  #define LoadFontEx    LoadFontExA
#endif

int     LoadStringExA(
          HMODULE hModule,  // handle to module containing string resource
          UINT uID,         // resource identifier
          char* lpBuffer,   // pointer to buffer for resource
          int nBufferMax,   // size of buffer
          WORD wLanguageID
        );
int     LoadStringExW(
          HMODULE hModule,  // handle to module containing string resource
          UINT uID,         // resource identifier
          LPWSTR lpBuffer,  // pointer to buffer for resource
          int nBufferMax,   // size of buffer
          WORD wLanguageID
        );

int     LoadFontExA(
          HMODULE hModule,  // handle to module containing string resource
          const char* szFont,// name of font (must be in "FONTNAME" IDR_*==szFont and same IDR_?* with font)
          void* lpBuffer,   // pointer to buffer for resource
          int nBufferMax,   // size of buffer
          WORD wLanguageID
        );
int     LoadFontExW(
          HMODULE hModule,  // handle to module containing string resource
          const wchar_t* szFont,// name of font (must be in "FONTNAME" IDR_*==szFont and same IDR_?* with font)
          void* lpBuffer,   // pointer to buffer for resource
          int nBufferMax,   // size of buffer
          WORD wLanguageID
        );

HBITMAP LoadBitmapEx(
          HINSTANCE hInstance,  // handle to application instance
          LPCTSTR lpBitmapName  // address of bitmap resource name
        );

#ifdef  __cplusplus
}
#endif

#endif//__YRESBASE_H
#pragma once