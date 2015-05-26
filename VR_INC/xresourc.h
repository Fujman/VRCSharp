//
// g_resources_namespace - .skp support
// g_messages_namespace  - .skp support
//
#if defined(RESOURCES_NAMESPACE_DEFINED) || defined(MESSAGES_NAMESPACE_DEFINED)
#define RESOURCE_MAP_NAMESPACE 1
#endif

#if !defined(RESOURCE_MAP_NAMESPACE) && !defined(__YRESLOAD_CPP)
#include "resource.h"
#endif

/////////////////////////////////////////////////////////////////////////////////////
// obsolete macroses

//#define DECLARE_BITMAP(IDI_BMP)         YResourceLoader::GetBitmapHandle(#IDI_BMP) //obsolete
//#define DECLARE_ICON(IDI_ICO)           YResourceLoader::GetIconHandle(#IDI_ICO)   //obsolete
#define LOAD_STRING(IDS_STR,sz)           YResourceLoader::GetStringHandle(#IDS_STR,(sz))
#define LOAD_BITMAP(IDB_BMP)              YResourceLoader::GetBitmapHandle(#IDB_BMP)
#define LOAD_ICON(IDI_ICON)               YResourceLoader::GetIconHandle(#IDI_ICON)
#define STRING_ID(IDS_STR)                YResourceLoader::GetResourceID(#IDS_STR,RT_STRING)
#define BITMAP_ID(IDB_BMP)                YResourceLoader::GetResourceID(#IDB_BMP,RT_BITMAP)
#define ICON_ID(IDI_ICO)                  YResourceLoader::GetResourceID(#IDI_ICO,RT_ICON)
#define CONTEXT_MENU_ID(IDR_MENU)         YResourceLoader::GetResourceID(#IDR_MENU,RT_MENU)
#define MENU_COMMAND_ID(IDM_STR)          YResourceLoader::GetResourceID(#IDM_STR,RT_STRING)

#define DECLARE_ICON(IDI_ICO)            (YResourceLoader::) //syntax error generation - prevent with xCIcon interference

//////////////////////////////////////////////////////////////////////////////////////
// Resource map support

#define RESOURCE_MAP(CLASS)               s_resources_##CLASS
#define RESOURCE_IDD(IDD)                 _T(#IDD)       //UNICODE or ANSI
#define RESOURCE_IDS(IDS)                 #IDS           //ANSI always

#define BEGIN_RESOURCE_MAP(CLASS)         static YLoadableResource s_resources_##CLASS[] = {
#define END_RESOURCE_MAP()                {0}};

#if RESOURCE_MAP_NAMESPACE //ID's don't defined - character names only
  #define RESOURCE_MAP_MESSAGE(IDS,s)     { #IDS, RT_MESSAGETABLE,  0, NULL,   0, (s) },
  #define RESOURCE_MAP_STRING(IDS,s)      { #IDS, RT_STRING,        0, NULL,   0, (s) },
  #define RESOURCE_MAP_ICON(IDI,s)        { #IDI, RT_ICON,          0, NULL,   0, (s) },
  #define RESOURCE_MAP_BITMAP(IDB,s)      { #IDB, RT_BITMAP,        0, NULL,   0, (s) },
  #define RESOURCE_MAP_CAPTION(IDD,s)     { #IDD, RT_CAPTION,       0, NULL, IDD, (s) },
  #define RESOURCE_MAP_CONTROL(IDC,s)     { #IDC, RT_CONTROL,       0, NULL, IDC, (s) },

  #define RESOURCE_MAP_CAPT_EX(IDD,s,IDS) { #IDD, RT_CAPTION,     IDS, NULL, IDD, (s) },//specified IDS
  #define RESOURCE_MAP_CTRL_EX(IDC,s,IDS) { #IDC, RT_CONTROL,     IDS, NULL, IDC, (s) },//specified IDS
#else                      //all ID's must be defined in resource.h
  #define RESOURCE_MAP_MESSAGE(IDS,s)     { #IDS, RT_MESSAGETABLE,IDS, NULL,   0, (s) },
  #define RESOURCE_MAP_STRING(IDS,s)      { #IDS, RT_STRING,      IDS, NULL,   0, (s) },
  #define RESOURCE_MAP_ICON(IDI,s)        { #IDI, RT_ICON,        IDS, NULL,   0, (s) },
  #define RESOURCE_MAP_BITMAP(IDB,s)      { #IDB, RT_BITMAP,      IDS, NULL,   0, (s) },
  #define RESOURCE_MAP_CAPTION(IDD,s)     { #IDD, RT_CAPTION,     IDS, NULL, IDD, (s) },
  #define RESOURCE_MAP_CONTROL(IDC,s)     { #IDC, RT_CONTROL,     IDS, NULL, IDC, (s) },

  #define RESOURCE_MAP_CAPT_EX(IDD,s,IDS) { #IDD, RT_CAPTION,     IDS, NULL, IDD, (s) },//specified IDS
  #define RESOURCE_MAP_CTRL_EX(IDC,s,IDS) { #IDC, RT_CONTROL,     IDS, NULL, IDC, (s) },//specified IDS
#endif

//////////////////////////////////////////////////////////////////////////////////////
// Resource map messages support  //AY 12.06.2012
#define FACILITY_DIALOG                   0x75
#define STATUS_SEVERITY_DESCRIPTION        0x1

#define DEFAULT_DIALOG_ID(IDD)            ( 0                        +\
                                           (unsigned((IDD)-99  )<<8) +\
                                           (FACILITY_DIALOG<<16)     +\
                                           (STATUS_SEVERITY_DESCRIPTION<<30))

#define DEFAULT_CONTROL_ID(IDD,IDC)       ( unsigned((IDC)-999 )     +\
                                           (unsigned((IDD)-99  )<<8) +\
                                           (FACILITY_DIALOG<<16)     +\
                                           (STATUS_SEVERITY_DESCRIPTION<<30))

#define CONTROL_ID_FROM_IDS(IDS)          ( unsigned( (IDS)    &0xFF) + 999 ) //AY 25.09.2012 0-for default IDS only!
#define DIALOG_ID_FROM_IDS(IDS)           ( unsigned(((IDS)>>8)&0xFF) +  99 ) //AY 25.09.2012 0-for default IDS only!

//////////////////////////////////////////////////////////////////////////////////////
//
// Example of designing the dialog with loadable multilanguage resources and messages
/*
//  Variant A. The multilanguage messages namespace is not enabled.
//             IDS_EXAMPLE must be defined in resource.h,
//             resource.h will be included inside the xresourc.h from CExampleDlg.cpp
//             Class must included in project directly
    StdAfx.h:
      #include "YResLoad.h"

//  Variant B. The multilanguage messages namespace is enabled.
//             IDS_EXAMPLE does not need to be defined,
//             resource.h will is not used in CExampleDlg.cpp.
//             Class may be included in library.
    StdAfx.h:
      #include "_xstrings_.h"
      #include "_resource.h"
      #include "_messages.h"
      #include "YResLoad.h"
    res\project.rc2
      #include "Message/Messages.rc"  // Note: In project settings of resource compiler
                                      // must be defined additional include path \VR\VR_RES

//  Common part vor Variants A and B.
//
    CExampleDlg.h:
      class CExampleDlg: public YResourceLoader, ... { ... };

    CExampleDlg.cpp:
      #include "xresourc.h" //used instead "resource.h"

      BEGIN_RESOURCE_MAP(CExampleDlg)
        RESOURCE_MAP_STRING(IDS_EXAMPLE,"Example")
      END_RESOURCE_MAP()

      CExampleDlg::CExampleDlg()
        :YResourceLoader(NULL,RESOURCE_MAP(CPasswordsDialog)), ... { ... }

      CExampleDlg::OnInitDialog()
        { CString szExample = GetString(RESOURCE_IDS(IDS_EXAMPLE)); ... }
*/


/* obsolete: OLD REALIZATION
#define RESOURCE_MAP_MESSAGE(IDS)       { #IDS, RT_MESSAGETABLE,0,NULL,   0 },
#define RESOURCE_MAP_STRING(IDS)        { #IDS, RT_STRING,     0, NULL,   0 },
#define RESOURCE_ICON(IDI)              { #IDI, RT_ICON,       0, NULL,   0 },
#define RESOURCE_BITMAP(IDB)            { #IDB, RT_BITMAP,     0, NULL,   0 },
#define RESOURCE_CAPTION(IDD)           { #IDD, RT_CAPTION,    0, NULL, IDD },
#define RESOURCE_CONTROL(IDC)           { #IDC, RT_CONTROL,    0, NULL, IDC },

#define RESOURCE_CAPTION_EX(IDD,IDS)    { #IDD, RT_CAPTION,  IDS, NULL, IDD }, //unused now?
#define RESOURCE_CONTROL_EX(IDC,IDS)    { #IDC, RT_CONTROL,  IDS, NULL, IDC }, //unused now?
*/
