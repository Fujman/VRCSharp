#ifndef __CVALUES_SRS_H
#define __CVALUES_SRS_H

#include "c_string.h"
#include "xCString.h"

#include "yRegKeyEx.h"


struct VALUE_DESCRIPTION
{
  int nType;
  int idDesc;
  LPCTSTR szDesc;
  int nCtrl;
  CRuntimeClass* pClass;
};

//=================================template=class CValues<VALUES>====================
//=================================== class members:=================================
//
//  void SetValues(VALUES& value)       values - array to copy from;
//  void SetValues(VALUES* value)       
//  void CopyValuesTo(VALUES& ValueToCopy)      copies VALUES data to ValueToCopy
//  void CopyValuesTo(VALUES* ValueToCopy)      copies VALUES data to ValueToCopy
//  CString GetDesc(int desc, int iValue)   desc: DESCNAME=long name, DESCSHORT=short name, 
//                              DESCUNITS= units of a member
//                        iValue: value number
//  CString GetName(int iValue)         returns value long name
//  int GetValueType(int iValue) const      returns value type 
//                        (VT_INT=int,VT_R4=float, VT_R8=double, VT_PTR=LPVOID)
//  const void* GetValue(int iValue) const    returns const pointer to VALUES
//  void* ValueAt(int iValue)         returns pointer to VALUES
//  static SizeOfValue(int nType)       returns size to VALUES of nType
//  LPCTSTR       GetRegistryKey() const    returns Registry Key
//  LPCTSTR       GetRegistryValue() const      returns Registry Value
//  BOOL          IsAutoSaveEnabled() const     returns Autosave state
//  static void SetAutoSaveMode(int mode)       Sets Autosave mode: 0: disabled;  1:enabled
//  int SaveToRegistry()                        Saves VALUES structure to registry
//  int LoadFromRegistry()                      Loads VALUES structure from registry
//  int SaveToRegistryFlat()                    Saves VALUES structure to registry as flat memory
//  int LoadFromRegistryFlat()                  Loads VALUES structure from registry saved as flat memory

//  int SaveToMemory(LPBYTE* lplpBuff)          Saves VALUES to memory
//  void LoadFromMemory(LPBYTE pBuff)           Loads VALUES to memory

//  DWORD GetFullDataSize()                     returns Full Size of VALUES data members

//  const VALUES* GetValues(){return this;}     returns Pointer to VALUES structure

//==================================================================================

template <class VALUES>
class CValues : public VALUES
{
public:
   enum { MAX_VALUES = sizeof(s_desc)/sizeof(*s_desc) };

public:
   CValues()
   { 
    memset(this,0,sizeof(*this));
    if(s_iAutoSaveMode)
      LoadFromRegistry();
   }
   ~CValues()
   { 
     if(s_iAutoSaveMode)
       SaveToRegistry();
     FreeValues();
   }

   enum { DESCNAME=2, DESCSHORT=1, DESCUNITS=0 };

   CString GetDesc(int desc, int iValue) const
   {
     ASSERT(iValue<MAX_VALUES);
     CString szDesc=""; 
     LPCTSTR sz = s_desc[iValue].szDesc;
     int id = s_desc[iValue].idDesc;
     if(id<=65535) {
       ASSERT(sz!=NULL);
       #if defined(UNICODE) || defined(_UNICODE)
         int dst_length = ::WideCharToMultiByte(CP_ACP, 0, sz, -1, NULL, 0, NULL, NULL);
         if(dst_length>0) {
           char* psz = new char[dst_length];
           ::WideCharToMultiByte(CP_ACP, 0, sz, dst_length, psz, dst_length, 0, 0 );
           szDesc = ResourceString(id,psz);
           delete [] psz;
         }
         else szDesc = "";
       #else
         szDesc = ResourceString(id,sz);
       #endif
     }
     else
       szDesc = FormatErrorString(id,NULL);
//   ASSERT(!szDesc.IsEmpty());
     if(szDesc.IsEmpty())
       szDesc=sz;
     TCHAR cDelim = szDesc[0];
     szDesc.Delete(0);
     string_parser sp;
     int i = 0;
     CString szRet; 
     LPTSTR szD = szDesc.LockBuffer(); //KSN LPSTR -> LPTSTR
     for(LPCTSTR szName=parse_first(&sp, szD, cDelim); szD!=NULL; ){
       if(i++==desc)
         { szRet = szName; break; }
       szName = parse_next(&sp);
     }
     szDesc.UnlockBuffer();
     return szRet;
   }

   CString GetName(int iValue) const
   {
     return GetDesc(DESCNAME, iValue);
   }

   
   int GetValueType(int iValue) const
   {
     ASSERT(iValue<MAX_VALUES);
     return s_desc[iValue].nType;
   }
   
   const void* GetValue(int iValue) const
   {
     ASSERT(iValue<MAX_VALUES);
     const void* p = this;
     for(int i=0; i<iValue; ++i){
       unsigned nSizeOf = SizeOfValue(s_desc[i].nType);
       p = ((const BYTE*)p) + nSizeOf;
     } 
     return p;
   }

   void* ValueAt(int iValue)
   {
     ASSERT(iValue<MAX_VALUES);
     void* p = this;
     for(int i=0; i<iValue; ++i){
       unsigned nSizeOf = SizeOfValue(s_desc[i].nType);
       p = ((BYTE*)p) + nSizeOf;
     } 
     return p;
   }

public:
   static SizeOfValue(int nType)
   {
     if(nType==VT_INT)    return sizeof(int);
     if(nType==VT_R4)     return sizeof(float);
     if(nType==VT_R8)     return sizeof(double);
     if(nType==VT_PTR)    return sizeof(LPVOID);
     ASSERT(!"must be never reached");
     return 0;
   }

protected:
    static CString        s_szRegistryKey;
    static CString        s_szRegistryValue;
    static int            s_iAutoSaveMode;

public:
  LPCTSTR       GetRegistryKey() const
  {
    return s_szRegistryKey;
  }

  LPCTSTR       GetRegistryValue() const
  {
    return s_szRegistryValue;
  }

  static                SetRegistryKeyAndValue(LPCTSTR szRegKey, LPCTSTR szRegValue)
  {
    s_szRegistryKey = szRegKey;
    s_szRegistryValue = szRegValue;
    
  }
  BOOL          IsAutoSaveEnabled() const
  {
    if(s_iAutoSaveMode==FALSE)
           return FALSE;
      if(s_iAutoSaveMode==TRUE)
          return TRUE;
      return FALSE;
  }

  //Mode: 0=Disabled;1=Enabled
  static void SetAutoSaveMode(int mode) 
  {
    s_iAutoSaveMode = mode;
  }


  

  int SaveToRegistry()
  {
        
    
    for(int i=0;i<MAX_VALUES;++i)
    {
    try{
      int vt=GetValueType(i);
      CString regpath;
      regpath.Format(_T("%s%s\\%s\\"),GetRegistryKey(),GetRegistryValue(),
                GetDesc(DESCSHORT,i));
      switch(vt)
      {
        case VT_INT:
          YRegKey::SetInt(*(int*)ValueAt(i),HKEY_CURRENT_USER, regpath,_T("INTVALUE"));
          break;
        case VT_R4:
          YRegKey::SetBinary((LPBYTE)ValueAt(i),SizeOfValue(vt),HKEY_CURRENT_USER,regpath,_T("R4VALUE"));
          break;
        case VT_R8:
          YRegKey::SetBinary((LPBYTE)ValueAt(i),SizeOfValue(vt),HKEY_CURRENT_USER,regpath,_T("R8VALUE"));
          break;
        case VT_PTR:
          LPVOID pVal   = *(LPVOID*)ValueAt(i);
          if(pVal)
          {
             YRegKey::SetBinary( *(LPBYTE*)ValueAt(i),*((DWORD*)pVal),HKEY_CURRENT_USER,regpath,_T("BINVALUE"));
          }else
            YRegKey::DeleteValue(HKEY_CURRENT_USER,regpath,_T("BINVALUE"));
          break;
        ASSERT(0);
      }
      YRegKey::SetString(GetDesc(DESCNAME,i),HKEY_CURRENT_USER, regpath, _T("DESC"));
      }
        catch(CException* e)
        {
            TCHAR msg[201];
            e->GetErrorMessage(msg,200);
            TRACE(msg);
            e->Delete();
        }
    }
            
        return 0;
    }

  int LoadFromRegistry()
  {


    for(int i=0;i<MAX_VALUES;++i)
    {
      int vt=GetValueType(i);
    try{
      CString regpath;
      regpath.Format(_T("%s%s\\%s\\"),GetRegistryKey(),GetRegistryValue(),
                GetDesc(DESCSHORT,i));
      CByteArray ba;
      switch(vt)
      {
        case VT_INT:

          YRegKey::GetInt(*(DWORD*)ValueAt(i),HKEY_CURRENT_USER, regpath,_T("INTVALUE"));
          break;
        case VT_R4:
          ba.RemoveAll();
          YRegKey::GetBinary(ba,HKEY_CURRENT_USER,regpath,_T("R4VALUE"));
          memcpy(ValueAt(i),ba.GetData(),SizeOfValue(vt));
          break;
        case VT_R8:
          ba.RemoveAll();
          YRegKey::GetBinary(ba,HKEY_CURRENT_USER,regpath,_T("R8VALUE"));
          memcpy(ValueAt(i),ba.GetData(),SizeOfValue(vt));
          
          break;
        case VT_PTR:
          LPVOID* p    = (LPVOID*)ValueAt(i);
          LPVOID pVal   = *p;
          if(pVal)
          {
            delete pVal;
            *p=NULL;
          }
          if(YRegKey::isValueExists(REG_BINARY,HKEY_CURRENT_USER,regpath,_T("BINVALUE")))
          {
            ba.RemoveAll();
            YRegKey::GetBinary( ba,HKEY_CURRENT_USER,regpath,_T("BINVALUE"));
            *p    =  malloc(ba.GetSize());
            memcpy(*p,ba.GetData(),ba.GetSize());
          }
          break;
        ASSERT(0);
      }
      YRegKey::SetString(GetDesc(DESCNAME,i),HKEY_CURRENT_USER, regpath, _T("DESC"));
      }
        catch(CException* e)
        {
            TCHAR msg[201];
            e->GetErrorMessage(msg,200);
            TRACE(msg);
            e->Delete();
        }
    }
            
        return 0;
  }
  
  
  
  int SaveToRegistryFlat()
  {
        try{
            LPBYTE mem=NULL;
            int nSize=CopyToMemory(&mem);
            YRegKey::SetBinary(mem,nSize,HKEY_CURRENT_USER,GetRegistryKey(),GetRegistryValue());
            delete mem;
            }
        catch(CException* e)
        {
            char msg[201];
            e->GetErrorMessage(msg,200);
            TRACE(msg);
            e->Delete();
        }
        return 0;
    }
    
    int LoadFromRegistryFlat()
  {

        UINT size=0;
  
        try{
    
        CByteArray ba;
    
        YRegKey::GetBinary(ba,HKEY_CURRENT_USER,GetRegistryKey(),GetRegistryValue());
        if(ba.GetSize()>0)
            LoadFromMemory(ba.GetData());
        ba.RemoveAll();

    }
        catch(CException* e)
    {
            char msg[201];
            e->GetErrorMessage(msg,200);
            TRACE(msg);
            e->Delete();
    }

  return 0;
  }
  
public:
  // allocates memory to *lplpBuff
  // returns mem size
  int SaveToMemory(LPBYTE* lplpBuff)
  {
    int nSize=GetFullDataSize();
    *lplpBuff = (LPBYTE)malloc(nSize);
    LPBYTE pBuff=*lplpBuff;
    for(int i=0;i<MAX_VALUES;++i)
    {
      int vt=GetValueType(i);
      switch(vt)
      {
        case VT_INT:
          *(int*)pBuff    = *(int*)ValueAt(i);
          break;
        case VT_R4:
          *(float*)pBuff  = *(float*)ValueAt(i);
          break;
        case VT_R8:
          *(double*)pBuff = *(double*)ValueAt(i);
          break;
        case VT_PTR:
          LPVOID pVal   = *(LPVOID*)ValueAt(i);
          if(pVal)
          {
            DWORD  dwSize = *(DWORD*)pVal;
            memcpy(pBuff,(void*)pVal,dwSize);
          }else
            *(LPVOID*)pBuff = NULL;
          break;
        ASSERT(0);
      }
      if(GetValueType(i)==VT_PTR && (*(LPVOID*)ValueAt(i)))
        pBuff+=*(DWORD*)(*(LPVOID*)ValueAt(i));
      else
        pBuff+=SizeOfValue(GetValueType(i));
    }
    return nSize;
  }

  void LoadFromMemory(LPBYTE pBuff)
  {
    for(int i=0;i<MAX_VALUES;++i)
    {
      int vt=GetValueType(i);
      switch(vt)
      {
        case VT_INT:
          *(int*)ValueAt(i) = *(int*)pBuff;
          break;
        case VT_R4:
          *(float*)ValueAt(i) = *(float*)pBuff;
          break;
        case VT_R8:
          *(double*)ValueAt(i) = *(double*)pBuff;
          break;
        case VT_PTR:
          LPVOID pVal   = pBuff;
          
          DWORD  dwSize = *(DWORD*)pVal;
          LPVOID* p    = (LPVOID*)ValueAt(i);
          if(*p)
            delete *p;
          *p = NULL;
          if(dwSize)
          {
            *p    =  malloc(dwSize);
            memcpy(*p,(void*)pVal,dwSize);
          }
          else
            *p     = NULL;
          break;
        ASSERT(0);
      }
      if(GetValueType(i)==VT_PTR && (*(LPVOID*)ValueAt(i)))
        pBuff+=*(DWORD*)(*(LPVOID*)ValueAt(i));
      else
        pBuff+=SizeOfValue(vt);
    }
  }

  DWORD GetFullDataSize()
  {
    DWORD nSize=0;
    for(int i=0;i<MAX_VALUES;++i)
    {
      if(GetValueType(i)==VT_PTR && (*(LPVOID*)ValueAt(i)))
        nSize+=*(DWORD*)(*(LPVOID*)ValueAt(i));
      else
        nSize+=SizeOfValue(GetValueType(i));
    }
    return nSize;
  }

public:
  void SetValues(VALUES& value){SetValues(&value);}
  void SetValues(VALUES* value)
  {
    CValues<VALUES>* cval= (CValues<VALUES>*)value;
    for(int i=0; i<MAX_VALUES; ++i)
    {
      switch(GetValueType(i))
      {
        
        case VT_INT:
          *(int*)ValueAt(i)    = *(int*)cval->ValueAt(i);
          break;
        case VT_R4:
          *(float*)ValueAt(i)  = *(float*)cval->ValueAt(i);
          break;
        case VT_R8:
          *(double*)ValueAt(i) = *(double*)cval->ValueAt(i);
          break;
        case VT_PTR:
          LPVOID* ppl   = (LPVOID*)cval->ValueAt(i);
          LPVOID pVal   = *((LPVOID*)ppl);
          
          LPVOID* p    = (LPVOID*)ValueAt(i);
          if(*p)
            delete *p;
            *p= NULL;
          if(pVal)
          {
            DWORD  dwSize = *(DWORD*)pVal;
            
            *p    =  malloc(dwSize);
            memcpy(*p,(void*)pVal,dwSize);
          }else
            *p = NULL;
          break;
        ASSERT(0);
      }
    } 
  
  }

  const VALUES* GetValues(){return this;}
  void CopyValuesTo(VALUES& ValueToCopy){CopyValuesTo(&ValueToCopy);}
  void CopyValuesTo(VALUES* ValueToCopy)
  {
    ((CValues<VALUES>*)ValueToCopy)->SetValues(this);
  }


protected:
  void FreeValues()
  {
    for(int i=0; i<MAX_VALUES; ++i)
    {
      switch(GetValueType(i))
      {
        
        case VT_INT:
          break;
        case VT_R4:
          break;
        case VT_R8:
          break;
        case VT_PTR:
          
          LPVOID* p    = (LPVOID*)ValueAt(i);
          if(*p)
            delete *p;
          *p=NULL;
          break;
        ASSERT(0);
      }
    } 
  
  }
  
  

};



template <class VALUES>
BOOL    CValues<VALUES>::s_iAutoSaveMode = 0;
template <class VALUES>
CString CValues<VALUES>::s_szRegistryKey;
template <class VALUES>
CString CValues<VALUES>::s_szRegistryValue;



//========================
//EXAMPLE OF USAGE

/*

struct VALUE //non-virtual!!!!
{
   int     p1;
   double  p2;
#ifdef __cplusplus
   static  VALUE_DESCRIPTION s_desc[2];
   static  VALUE s_min, s_max, s_step;
#endif
};

//.cpp


VALUE_DESCRIPTION VALUE::s_desc[] = {
  { VT_INT,  VALUE_VOLUME, "|dB|Volume|Speaker volume long description" , 0, RUNTIME_CLASS(CSliderCtrl) },
  { VT_RT8,  VALUE_VOLUME, "|dB|Volume|Speaker volume long description" , 0, RUNTIME_CLASS(CSliderCtrl) }
};
VALUE VALUE::s_min  = {   0,   0 };
VALUE VALUE::s_max  = { 100, 100 };
VALUE VALUE::s_step = {   1,   1 };

CValues<VALUE>;

*/

#endif