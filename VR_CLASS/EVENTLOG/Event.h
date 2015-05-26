#ifndef __EVENT_H
#define __EVENT_H
#include "EventBase.h"
#include "EventObj.h"
#include "EventClass.h"
#ifdef  __cplusplus
#pragma pack(push,1)
/////////////////////////////////////////////////////////////////////////////

class   YEventsProtocol;

class   YEventObject;   //+
class   YEventBaseData; //+
struct  YEventClassInfo;//=
class       YEvent;

/////////////////////////////////////////////////////////////////////////////
// YEvent; pure virtual;
class YEvent : public YEventObject, public YMetaClass<YEventBaseData,YEventClassInfo> {
public://constants
  enum          { classERROR=0, classWARNING=1, classINFO=2 };

public://application initialization
  static         YEventsProtocol* GetLog();
  static int     SetLog(YEventsProtocol* );

public://construction/destructon
  static YEvent* Create(const void *pEBD, int nSize=0, void *pMem=NULL, int nMemSize=0, LPCSTR szFileName=0, int nLine=0);
  static YEvent* Delete(YEvent* pEvent, void *pMem=0);
                 YEvent() {}
  virtual        ~YEvent() {}
public://attributes
  virtual LPTSTR GetInfo(LPTSTR szEvent, int nLength, int* pnLevel=NULL, int* pnClass=NULL, DWORD* pdwCategory=NULL) const;
  virtual LPTSTR GetText(LPTSTR szEvent, int nLength) const =0;
  virtual LPTSTR GetDump(LPTSTR szEvent, int nLength) const;
  virtual int    GetDataSize() const; //with base data
  virtual void*  GetData(void *pData, int nMaxSize=0) const;
  virtual int    GetRawSize() const; // without base data
  virtual void*  GetRawData(void *pData, int nMaxSize=0, size_t nOffset=0) const;
  virtual void*  SetRawData(const void *pData, int nRawSize=0, size_t nOffset=0);
  virtual int    Validate() const;
  virtual int    IsEmpty() const;
  virtual size_t SizeOf() const; //size of object

public://helpers
//static  size_t SizeOf(size_t nNewNeedSize, const YEventBaseData* pData, size_t nDataSize=0);//inherited form YEventObject
  virtual void   Encode(void *pData, size_t nSize, size_t nOffset) const;
  virtual void   Decode(void *pData, size_t nSize, size_t nOffset) const;

  static  int    GetMessageInfo(UINT nMessageID, CString& szText, int* pnLevel=NULL, int* pnClass=NULL, DWORD* pdwCategory=NULL);

protected://members
  static         YEventsProtocol* s_pLog;
};

/////////////////////////////////////////////////////////////////////////////
// Class YEvent16; // sizeof() = 64 bits = 8 bytes, data = 16 bits
class YEvent16 : public YEVENT_CLASS(YEvent16,YEvent) {
//WORD           m_nClass:2; = EVN_16BIT_CLASS (1)
//WORD           m_nType:4;    0..15
//WORD           m_nMsec:10;
//WORD           m_nData;      data (16 bits)
//time_t         m_tTime;
public: enum    {eventCLASS=EVN_16BIT_CLASS, eventTYPE=-1};
public:
  static YEvent* Allocate(const void *pEBD, size_t nSize=0, void *pMem=NULL, size_t nMemSize=0, LPCSTR szFileName=0, int nLine=0);
                 YEvent16(const void* pEBD, int nSize=0);
public:
                 YEvent16();
                 YEvent16(WORD nType, WORD nData=0);

  WORD           GetData16()const;          // 16 bit data: Class=0
  WORD           SetData16(WORD nData);

  LPTSTR         GetText(LPTSTR szEvent, int nLength) const;

private://exclude non-used functions
  WORD           SetClass(WORD nClass){ASSERT(0);return 0;};
public:
  enum           {SIZE_OF_BASE_DATA=sizeof(tagYEventBaseData)};
};
/////////////////////////////////////////////////////////////////////////////
// Class YEvent20; // sizeof = 64 bits = 8 bytes,  data = 20 bits
class YEvent20 : public YEVENT_CLASS(YEvent20,YEvent){
//WORD           m_nClass:2; = EVN_20BIT_CLASS (2)
//WORD           m_nType:4;    data bits 16..19
//WORD           m_nMsec:10;
//WORD           m_nData;      data bits  0..15
//time_t         m_tTime;

public: enum    {eventCLASS=EVN_20BIT_CLASS, eventTYPE=-1};
public:
  static YEvent* Allocate(const void *pEBD, size_t nSize=0, void *pMem=NULL, size_t nMemSize=0, LPCSTR szFileName=0, int nLine=0);
                 YEvent20(const void* pEBD, int nSize=0);
public:
                 YEvent20();
                 YEvent20(DWORD dwData);

  DWORD          GetData20()const;          // 20 bit data: Class=2
  DWORD          SetData20(DWORD dwData);

  LPTSTR          GetText(LPTSTR szEvent, int nLength) const;

private://exclude non-used functions
  WORD           SetClass(WORD nClass){ASSERT(0);return 0;};
public:
  enum           {SIZE_OF_BASE_DATA=sizeof(tagYEventBaseData)};
};
/////////////////////////////////////////////////////////////////////////////
// Class YEvent64                   // sizeof() = 128 bits = 16 bytes
// WORD  0000 1111 2222 3333 4444   // sizeof data = 64+16 bits = 8+2 bytes
// DWORD      0000-0000 1111-1111   // Class=0 , Type=0..15
// int64      0000-0000-0000-0000
class YEvent64 : public YEVENT_CLASS(YEvent64,YEvent){
protected:
//WORD           m_nClass:2; = EVN_64BIT_CLASS (2)
//WORD           m_nType:4;    
//WORD           m_nMsec:10; /////////// GetData16  GetData32 GetData64 GetData8
//WORD           m_nData;      data bits 0..15      -         -         0..15
//time_t         m_tTime;
  DWORD          m_dwData[2];//data bits 16..79     0..63     0..63     16..79

public: enum    {eventCLASS=EVN_64BIT_CLASS, eventTYPE=-1};
public:
  static YEvent* Allocate(const void *pEBD, size_t nSize=0, void *pMem=NULL, size_t nMemSize=0, LPCSTR szFileName=0, int nLine=0);
                 YEvent64(const void* pEBD, int nSize=0);
public:
                 YEvent64(WORD nType=0, DWORD dwData=0, DWORD dwData2=0); // 64 bit

  BYTE           GetData8(int n=0)const;           // n=0..9
  BYTE           SetData8(BYTE nData, int n=0);    // n=0..9
  WORD           GetData16(int n=0)const;          // n=0..4
  WORD           SetData16(WORD nData, int n=0);   // n=0..4
  DWORD          GetData32(int n=0) const;         // n=0..1
  DWORD          SetData32(DWORD dwData, int n=0); // n=0..1
  DWORD          GetData64(DWORD* pdwData2) const;
  DWORD          SetData64(DWORD* pdwData2);
  const char*    SetString(const char* sz);
  char*          GetString(char* sz) const;

  LPTSTR         GetText(LPTSTR szEvent, int nLength) const;
  int            IsEmpty() const;

private://exclude non-used functions
  WORD           SetClass(WORD nClass){ASSERT(0);return 0;};
public:
  enum           {SIZE_OF_BASE_DATA=sizeof(tagYEventBaseData64)};
};

/////////////////////////////////////////////////////////////////////////////
// classes registration
#include "EventClass.inl"
YEVENT_CLASS_DECLARE(YEvent16,YEvent);
YEVENT_CLASS_DECLARE(YEvent20,YEvent);
YEVENT_CLASS_DECLARE(YEvent64,YEvent);

/////////////////////////////////////////////////////////////////////////////
// Inline implementation

#include "Event.inl"

/////////////////////////////////////////////////////////////////////////////
#pragma pack(pop)
#endif//__cplusplus
#endif//__EVENT_H
#pragma once
