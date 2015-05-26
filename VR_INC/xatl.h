#ifndef __XATL_H
#define __XATL_H

inline LPCTSTR XATL__FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
    while (p1 != NULL && *p1 != NULL)
    {
        LPCTSTR p = p2;
        while (p != NULL && *p != NULL)
        {
            if (*p1 == *p)
                return CharNext(p1);
            p = CharNext(p);
        }
        p1 = CharNext(p1);
    }
    return NULL;
}

inline HRESULT XATL__IsRegisteredAsService(LPCTSTR app_id)
{
  // Are we Service or Local Server
  CRegKey keyAppID;
  LONG lRes = keyAppID.Open(HKEY_CLASSES_ROOT, _T("AppID"), KEY_READ);
  if (lRes != ERROR_SUCCESS)
    return HRESULT_FROM_WIN32(lRes);//0x80070000|lRes

  CRegKey key;
  lRes = key.Open(keyAppID, app_id, KEY_READ);
  if (lRes != ERROR_SUCCESS)
    return HRESULT_FROM_WIN32(lRes);

  TCHAR szValue[_MAX_PATH];
  DWORD dwLen = _MAX_PATH;
  lRes = key.QueryValue(szValue, _T("LocalService"), &dwLen);

  if (lRes == ERROR_SUCCESS)
    return S_OK;//ok

  return S_FALSE;
}


#endif//__XATL_H

#if 0 //ATL server support examples:
//MFC .EXE/.SYS ///////////////////////////////////////////////////////////////
//stdafx.h 
  class CServiceModule : public CComModule//, public CServiceApp
  {
  public:
	  HRESULT RegisterServer(BOOL bRegTypeLib, BOOL bService);
	  HRESULT UnregisterServer();
	  void Init(_ATL_OBJMAP_ENTRY* p, HINSTANCE h, UINT nServiceNameID, const GUID* plibid = NULL);
    void Start();
	  void ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
    void Handler(DWORD dwOpcode);
    void Run();
    BOOL IsInstalled();
    BOOL Install();
    BOOL Uninstall();
	  LONG Unlock();
	  void LogEvent(LPCTSTR pszFormat, ...);
    void SetServiceStatus(DWORD dwState);
    void SetupAsLocalServer();
  //Implementation
  private:
	  static void WINAPI _ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
    static void WINAPI _Handler(DWORD dwOpcode);
  // data members
  public:
    TCHAR m_szServiceName[256];
    SERVICE_STATUS_HANDLE m_hServiceStatus;
    SERVICE_STATUS m_status;
	  DWORD dwThreadID;
	  BOOL m_bService;
  };
  extern CServiceModule _Module;
//Exe.h (generated) see below...
//Exe.cpp
  CServiceModule _Module;
  //...ObjectMap...
  HRESULT CServiceModule::RegisterServer(BOOL bRegTypeLib, BOOL bService);
  HRESULT CServiceModule::UnregisterServer();
  LONG    CServiceModule::Unlock();
  BOOL    CServiceModule::IsInstalled();
  BOOL    CServiceModule::Install();
  BOOL    CServiceModule::Uninstall();
  void         CServiceModule::SetServiceStatus(DWORD dwState);
  void WINAPI  CServiceModule::_Handler(DWORD dwOpcode) { _Module.Handler(dwOpcode); }
  void WINAPI  CServiceModule::_ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv) { _Module.ServiceMain(dwArgc, lpszArgv); }
  inline void  CServiceModule::Handler(DWORD dwOpcode);//SERVICE_CONTROL_STOP processed only now - Post WM_QUIT

  void         CServiceModule::Init(_ATL_OBJMAP_ENTRY* p, HINSTANCE h, UINT nServiceNameID, const GUID* plibid);

  void         CServiceModule::Run()
  {
    _Module.dwThreadID = GetCurrentThreadId();
    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    //...
    CoInitializeSecurity(sd, -1, NULL, NULL,RPC_C_AUTHN_LEVEL_PKT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
    //...
    _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER, REGCLS_MULTIPLEUSE);
    //...
    if(m_bService)
      SetServiceStatus(SERVICE_RUNNING);
    MSG msg;
    while (GetMessage(&msg, 0, 0, 0))
      DispatchMessage(&msg);
    _Module.RevokeClassObjects();
    CoUninitialize();
  }

  void  CServiceModule::ServiceMain(DWORD /* dwArgc */, LPTSTR* /* lpszArgv */)
  {
    m_status.dwCurrentState = SERVICE_START_PENDING;
    m_hServiceStatus = RegisterServiceCtrlHandler(m_szServiceName, _Handler);
    //...on error.. return;
    SetServiceStatus(SERVICE_START_PENDING);
    m_status.dwWin32ExitCode = S_OK;
    m_status.dwCheckPoint = 0;
    m_status.dwWaitHint = 0;
    // When the Run function returns, the service has stopped.
    Run();

    SetServiceStatus(SERVICE_STOPPED);
  }

  extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
  {
    _Module.Init(ObjectMap, hInstance, IDS_SERVICENAME, &LIBID_EXELib);
    _Module.m_bService = TRUE;
    lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
    if("UnregServer")
      return _Module.UnregisterServer();
    if("RegServer")
      return _Module.RegisterServer(TRUE, FALSE);
    if("Service")
      return _Module.RegisterServer(TRUE, TRUE);

    if(XATL__IsRegisteredAsService(APP_ID))
      _Module.m_bService = TRUE;

    _Module.Start(); //AS LOCAL SERVER OR SERVICE

    // When we get here, the service has been stopped
    return _Module.m_status.dwWin32ExitCode;
  }

  void CServiceModule::Start()
  {
    SERVICE_TABLE_ENTRY st[] = { { m_szServiceName, _ServiceMain },{ NULL, NULL } };
    if(m_bService && !::StartServiceCtrlDispatcher(st))
      m_bService = FALSE;
    if(m_bService == FALSE)
      Run(); //AS LOCAL SERVER
  }


//MFC .EXE ////////////////////////////////////////////////////////////////////
//stdafx.h 
    class CExeModule : public CComModule
    {
	    LONG    Unlock();
	    LONG    Lock();
	    DWORD   dwThreadID;
    };
    extern CExeModule _Module;
//Exe.h
    class CExeApp : public CWinApp
    { ...
	    BOOL m_bATLInited;
	    BOOL InitATL();
    };
//Exe.cpp
    CExeApp theApp;
    CExeModule _Module;
    //...ObjectMap...

    LONG CExeModule::Unlock()  { AfxOleUnlockApp(); return 0; }
    LONG CExeModule::Lock()    { AfxOleLockApp(); return 1; }

    BOOL CSRSClientApp::InitInstance()
    {
	    if (!InitATL())
		    return FALSE;
      ...
    }  
    int CExeApp::ExitInstance(){
	    if (m_bATLInited) {
		    _Module.RevokeClassObjects();
		    _Module.Term();
		    CoUninitialize();
	    }
	    return CWinApp::ExitInstance();
    }

    BOOL CSRSClientApp::InitATL()
    {
	    m_bATLInited = TRUE;
	    HRESULT hRes = CoInitialize(NULL);
      //...on error... m_bATLInited = FALSE;

	    _Module.Init(ObjectMap, AfxGetInstanceHandle());
	    _Module.dwThreadID = GetCurrentThreadId();

	    LPTSTR lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
      if("UnregServer"){
			  _Module.UpdateRegistryFromResource(IDR_EXE, FALSE);
			  _Module.UnregisterServer(TRUE); //TRUE means typelib is unreg'd
        return FALSE; //m_bATLInited=FALSE; _Module.Term(); CoUninitialize();
      }
      if("RegServer"){
	      _Module.UpdateRegistryFromResource(IDR_EXE, TRUE);
  	    _Module.RegisterServer(TRUE);
        return FALSE; //m_bATLInited=FALSE; _Module.Term(); CoUninitialize();
      }
      //...on error... return FALSE; //m_bATLInited=FALSE; _Module.Term(); CoUninitialize();
	    hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE);
      //...on error... return FALSE; //m_bATLInited=FALSE; _Module.Term(); CoUninitialize();
	    return TRUE;
    }

//Exe_i.c (generated)
    const IID   IID_ICls;
    const IID   LIBID_EXELib;
    const IID   DIID__IClsEvents;//connection points support
    const CLSID CLSID_Cls;
//Exe_i.h (generated)
    interface ICls;
    interface _IClsEvents;       //connection points support
    class Cls;
//resources
    "REGISTRY" IDR_EXE -> Exe.rgs
    "REGISTRY" IDR_CLS -> Cls.rgs


//MFC .DLL ////////////////////////////////////////////////////////////////////
//stdafx.h 
    extern CComModule _Module;
//Exe.h (generated) see below...
//Exe.cpp
    CComModule _Module;
    //...ObjectMap...
    class CExeApp : public CWinApp
    {
    };
    CExeApp theApp;

    BOOL CExe::InitInstance() { _Module.Init(ObjectMap, m_hInstance, &LIBID_APPLib); return CWinExe::InitInstance(); }
    int  CExe::ExitInstance() { _Module.Term(); return CWinExe::ExitInstance(); }
    //exported
      STDAPI DllCanUnloadNow(void) { AFX_MANAGE_STATE(AfxGetStaticModuleState());  return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE; }
      STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) { return _Module.GetClassObject(rclsid, riid, ppv); }
      STDAPI DllRegisterServer(void)   { return _Module.RegisterServer(TRUE); }
      STDAPI DllUnregisterServer(void) { return _Module.UnregisterServer(TRUE); }
//Exe.h (generated)
    interface ICls;
    interface _IClsEvents;       //connection points support
    class Cls;
//Exe_i.c (generated)
    const IID   IID_ICls;
    const IID   LIBID_EXELib;
    const IID   DIID__IClsEvents;//connection points support
    const CLSID CLSID_Cls;
//resources
    "REGISTRY" IDR_CLS -> Cls.rgs



//MFC .EXE ////////////////////////////////////////////////////////////////////
//Exe.rgs
  HKCR
  {
	  NoRemove AppID
	  {
		  {APPID_Exe} = s 'Exe'
		  'Exe.EXE'
		  {
			  val AppID = s {APPID_Exe}
		  }
	  }
  }
//Cls.rgs
  HKCR
  {
	  Exe.Cls.1 = s 'Cls Class'
	  {
		  CLSID = s '{CLSID_Cls}'
	  }
	  Exe.Cls = s 'Cls Class'
	  {
		  CLSID = s '{CLSID_Cls}'
		  CurVer = s 'Exe.Cls.1'
	  }
	  NoRemove CLSID
	  {
		  ForceRemove {CLSID_Cls} = s 'Cls Class'
		  {
			  ProgID = s 'Exe.Cls.1'
			  VersionIndependentProgID = s 'Exe.Cls'
			  ForceRemove 'Programmable'
			  LocalServer = s '%MODULE%'
			  val AppID = s '{APPID_Exe}'
			  'TypeLib' = s '{LIBID_EXELib}'
		  }
	  }
  }


//MFC .DLL ////////////////////////////////////////////////////////////////////
//Cls.rgs
  HKCR
  {
	  Exe.Cls.1 = s 'Cls Class'
	  {
		  CLSID = s '{CLSID_Cls}'
	  }
	  Exe.Cls = s 'Cls Class'
	  {
		  CLSID = s '{CLSID_Cls}'
		  CurVer = s 'Exe.Cls.1'
	  }
	  NoRemove CLSID
	  {
		  ForceRemove {CLSID_Cls} = s 'Cls Class'
		  {
			  ProgID = s 'Exe.Cls.1'
			  VersionIndependentProgID = s 'Exe.Cls'
			  ForceRemove 'Programmable'
			  InprocServer32 = s '%MODULE%'
			  {
				  val ThreadingModel = s 'Free'
			  }
			  'TypeLib' = s '{LIBID_EXELib}'
		  }
	  }
  }

#endif