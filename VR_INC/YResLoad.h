#ifndef __YRESLOAD_H
#define __YRESLOAD_H

/////////////////////////////////////////////////////////////////////////////
// YLoadableResource

#define RT_CAPTION              MAKEINTRESOURCE((DWORD)RT_CURSOR + 0x7F) //AY 11.06.2012 extension
#define RT_CONTROL              MAKEINTRESOURCE((DWORD)RT_CURSOR + 0x80) //AY 11.06.2012 extension

typedef struct {
  LPCSTR                        szDesc;
  LPCTSTR                       szType;  //RT_ICON,RT_BITMAP,RT_STRING; //KSN 2006.06.21 (const char* -> LPCTSTR)
  unsigned                      nID;     
  void*                         handle;  //HICON,HBITMAP,LPCTSTR, now new handles always provided
  unsigned                      nCtrlID; //AY 11.06.2012   control IDC or dialog IDD
  LPCSTR                        azText;  //AY 24.09.2012 - default string value (or default tooltip?)
} YLoadableResource; 

/*ATTENTION! struct must be same as unnamed struct in _resource.c. _resource.h, _messages.h, _messages.c:
struct { const char* szDesc; const char* szType; unsigned nID; void* handle; unsigned nReserved; const char* azReserved; } g_resources_namespace[];
  see also J:\VR\VR_INC\YRESOURC\YResourc.cpp(221)
*/

/////////////////////////////////////////////////////////////////////////////
// YResourceLoader
class YResourceLoader
{
public:
                                YResourceLoader(HINSTANCE hInstance=NULL, YLoadableResource* pPattern=NULL);//in constructor called SetResources(s_resources);
                                ~YResourceLoader();
  
  void                          SetResources(YLoadableResource* pResources, HINSTANCE hInstance=NULL);
  YLoadableResource*            GetResources() const
                                  { return m_resources; }
  
  static void                   SetDefaultResources(YLoadableResource* pResources)//last element contain all zeros in all fields
                                  { s_resources = pResources; }
  static YLoadableResource*     GetDefaultResources()
                                  { return s_resources; }

  void                          AttachResources(YLoadableResource* pResources)
                                  { m_resources = pResources; }
  void                          DetachResources(YLoadableResource* pResources)
                                  { m_resources = NULL; }

  HINSTANCE                     GetInstance() const
                                  { return m_hInstance?m_hInstance:AfxGetApp()->m_hInstance; }

  static void                   SetResourcesNamespace(YLoadableResource* pNamespace, int nth=0)//last element contain all zeros in all fields
                                  { nth==0 ? s_namespace = pNamespace :  s_nsmessage = pNamespace ; }
  static YLoadableResource*     GetResourcesNamespace(int nth=0)
                                  { return nth==0 ? s_namespace : s_nsmessage; }

public:
  BOOL                          CheckResources(const YLoadableResource* pPattern) const;
  void                          LoadResources();   //from OnInitDialog
  void                          ReleaseResources(BOOL bPurgeOnly=FALSE);//in Destructor or Earlier.

  LPCTSTR                       GetString(LPCSTR szDesc, LPCSTR azDefault=NULL) const;//AY 25.09.2012 - strings only

  HBITMAP                       GetBitmapHandle(LPCSTR szDesc) const;
  HICON                         GetIconHandle(LPCSTR szDesc) const;
  LPCTSTR                       GetStringHandle(LPCSTR szDesc, LPCSTR azDefault=NULL) const;
  LPCTSTR                       GetMessageHandle(LPCSTR szDesc, LPCSTR azDefault=NULL) const;

  LPVOID                        GetResourceHandle(LPCSTR szDesc, LPCTSTR nType) const;
  UINT                          GetResourceID(LPCSTR szDesc, LPCTSTR nType) const;
  LPCSTR                        GetResourceText(LPCSTR szDesc, LPCTSTR nType=NULL) const;//AY 25.09.2012 - any control

  void                          UpdateControls(CWnd* pDlg, BOOL bReload=FALSE);
protected:
  static int                    GetResourcesCount(const YLoadableResource* pResources);
  static int                    ResolvePattern(YLoadableResource* pPattern);
  int                           FindResource(LPCSTR szDesc, LPCTSTR nType) const;
  static int                    FindResource(const YLoadableResource* pResources, const YLoadableResource* pItem);
  static const YLoadableResource* FindResource(const YLoadableResource* pResources, LPCSTR szDesc, LPCTSTR szType=NULL);
  void                          DumpResources() const;

  static YLoadableResource*     s_resources;
  YLoadableResource*            m_resources;
  YLoadableResource*            m_pattern;
  static YLoadableResource*     s_namespace;
  static YLoadableResource*     s_nsmessage;

  HINSTANCE                     m_hInstance;
public:
  static void                   DumpNamespaceResources();
  static int                    DumpNamespaceStrings(LPCTSTR szFileName, WORD wLangID);
};

/////////////////////////////////////////////////////////////////////////////
// resource namespace support (see _resource.c generated by YResourc.exe)
#ifdef  RESOURCES_NAMESPACE_DEFINED

struct  YResourceNamespaceInitializator{ YResourceNamespaceInitializator() { YResourceLoader::SetResourcesNamespace((YLoadableResource*)g_resources_namespace,0);}};
static  YResourceNamespaceInitializator s_resources_namespace_initializator;/*may be used __declspec(selectany)?*/

#endif//RESOURCES_NAMESPACE_DEFINED

/////////////////////////////////////////////////////////////////////////////
// messages namespace support (see _messages.c generated by YResourc.exe)
#ifdef  MESSAGES_NAMESPACE_DEFINED

struct  YResourceNSMessagesInitializator{ YResourceNSMessagesInitializator() { YResourceLoader::SetResourcesNamespace((YLoadableResource*)g_messages_namespace,1);}};
static  YResourceNSMessagesInitializator s_messages_namespace_initializator;/*may be used __declspec(selectany)?*/

#endif//MESSAGES_NAMESPACE_DEFINED
#endif//__YRESLOAD_H
