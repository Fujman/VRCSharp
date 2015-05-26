#if !defined(AFX_EVENTSLISTDLG_H__E948B834_2864_4B91_86A6_7B32F8E07B1F__INCLUDED_)
#define AFX_EVENTSLISTDLG_H__E948B834_2864_4B91_86A6_7B32F8E07B1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EventsListDlg.h : header file
//

#include <afxcmn.h>
#include <afxmt.h>
#include <afxtempl.h>
#include "xCDialog.h"
#include "CONTROLS/AUTOSIZE/ResizableDialog.h"
#include "HeaderCtrl.h"
#include "CONTROLS/MemDC.h"
#include "EVENTLOG/event.h"

#include "EventsFilter.h"
//#define  K_DEBUG

class   YEventsProtocol;
class   CEventsPage;
class   CEventsPageArray;
class   CEventsList;
class   YEvent;

#define STACK_LEN     ((MAX_PATH+1)*sizeof(wchar_t)+sizeof(YEvent64)) //542

//class   CFindInfo;

class CFindInfo {
public:
  enum { //flags
    fndText   = 1,
    fndID     = 2,
    fndTime   = 4
  };
  enum {
    dirNONE   = 0,
    dirUP     = 1,
    dirDOWN   = 2,
    dirUPDOWN = 3,
    dirDOWNUP = 4
  };
  enum {
    fndPartial  = 256
  };
public:
  CFindInfo() {m_szText.Empty(); m_nID=0; m_tTime=YTime::INVALID(); m_nDirection = 0; m_dwFlags=0;m_dwOtherFlags=0;}
  CFindInfo(const CFindInfo* pFindInfo)
  {
    m_szText  = pFindInfo->m_szText; 
    m_nID     = pFindInfo->m_nID; 
    m_tTime   = pFindInfo->m_tTime; 
    m_nDirection   = pFindInfo->m_nDirection; 
    m_dwFlags = pFindInfo->m_dwFlags;
    m_dwOtherFlags = pFindInfo->m_dwOtherFlags;
  }
  
public:
  CString     m_szText;
  UINT        m_nID;
  YTime       m_tTime;
  UINT        m_nDirection;   //dirUP,dirDOWN...
  DWORD       m_dwFlags;      //fndText,fndID...
  DWORD       m_dwOtherFlags; //fndPartial
};

//class   CMessagesArbiter;
class CMessagesArbiter : public CObject  
{
public:
  class CMessage {
    public:
      enum{
        dataNone    =0,
        dataFindInfo=1
      };
    public:
    HWND          m_hMesWnd;
    UINT          m_nMessage;
    BOOL          m_bPostMode;
    WPARAM        m_WParam;
    LPARAM        m_LParam;
    UINT          m_nDataType;
    private:
    void*         m_pData;
    public:
    CMessage() {InitElements();}
    CMessage(const CMessage& message) {InitElements();operator=(message);}
    ~CMessage();// {if(m_pData) delete (CFindInfo*)m_pData;}

    void SetData(void* pData, UINT nDataType) {
      if(m_nDataType==dataFindInfo) {
        delete (CFindInfo*)m_pData;
        m_nDataType = dataNone;
        m_pData = NULL;
      }
      ASSERT(nDataType==dataNone || nDataType==dataFindInfo);
      switch(nDataType)
      {
        case dataFindInfo:
          {
            m_pData = new CFindInfo((CFindInfo*)pData);
            m_nDataType = dataFindInfo;
          }
          break;
        case dataNone:
        default:
          break;
      }
      m_WParam  = (WPARAM)m_pData;
    }

    CMessage& operator=(const CMessage& message) {
      if(this==&message) {
        ASSERT(0);
        return *this;
      }
      m_hMesWnd=message.m_hMesWnd;
      m_nMessage=message.m_nMessage;
      m_bPostMode=message.m_bPostMode;
      m_WParam=message.m_WParam;
      m_LParam=message.m_LParam;
      SetData(message.m_pData,message.m_nDataType);
      return *this;
    }
    private:
      inline void InitElements() {m_hMesWnd=NULL,m_nMessage=0,m_bPostMode=TRUE,m_WParam=NULL,m_LParam=NULL;m_nDataType=dataNone,m_pData=NULL;}
  };
private:
  CArray<CMessage,CMessage>  m_messages;
  CCriticalSection           m_cs;
  CCriticalSection           m_csQueue;
  CSingleLock                m_SingleLock;
public:             
                  CMessagesArbiter();

  void            DoPushMessage(CMessage* pMessage); //do this to post message (and no wait for begin processing) (For start processing)
  void            DoEndProcessing();                                    //do this when when message processed                        (For end   processing)
protected:
  void            TryPopMessage();

  void            _PopMessage();
  void            _DoStartProcessing();
  void            _DoEndProcessing();

private:
public:
  
};
/////////////////////////////////////////////////////////////////////////////
// CEventsListDlg dialog
class CEventsListDlg : public CEmptyAnyDialog<CResizableDialog>
{
  typedef  QWORD    HEVENT;

  class CMessageDlg : public CEmptyAnyDialog<CDialog>
  {
    typedef CEmptyAnyDialog<CDialog>  CParentDlg;
  public:
    CMessageDlg(/*CWnd* pParent = NULL*/) { m_bCreated=FALSE; m_pText=NULL;}   // standard constructor
    virtual       ~CMessageDlg(){delete m_pText; m_pText = NULL;}
    int           ReCreate(CRect rectDlg, LPCTSTR lpszText, CWnd* pParent);

    void          Show(BOOL bShow);
  protected:
    BOOL ShowWindow(int nCmdShow) {return CParentDlg::ShowWindow(nCmdShow);}; 
  private:
    BOOL          m_bCreated;
    CFont         m_TextFont;
    CStatic*      m_pText;
  protected:
    virtual void DoDataExchange(CDataExchange* pDX);
  protected:
    virtual BOOL OnInitDialog();
  };
  //---------------------------------------
  typedef CEmptyAnyDialog<CResizableDialog>  CParent;
  enum {
    IMAGE_INFO = 0
  };
public:
  enum {
    DETAIL_HIDE = 1,
    DETAIL_SHOW = 2 //show message levels
  };

  CCriticalSection  m_cs;
protected:
//   int                m_nSortColumn;
//   CHeaderCtrlEx      m_HeaderCtrl;
//   CFont              m_NewHeaderFont;


  BOOL               m_bNeedStopFind;
  BOOL               m_bNeedKillLoader;
  BOOL               m_bNeedReset;
  BOOL               m_bPausePreloader;
  BOOL               m_bLoadLeft;//direction of preloading
  HANDLE             m_hNeedLoadEvent;
  HANDLE             m_hNeedFindEvent;

  HANDLE             m_hLoaderThread;
  HANDLE             m_hFindThread;
  HANDLE             m_hMessagesThread;

  BOOL               m_bEnableFilterDialog;
  BOOL               m_bShowLogStatus;

  UINT               m_nLogStatusHeight;
protected:
  CWinThread*        m_pLoaderThread;
  CWinThread*        m_pFindThread;
  CWinThread*        m_pMessagesThread;

  YEventsProtocol*   m_pevp;
  BYTE*              m_pbyPageBuf;

  int                m_nOpenMode;
  ULONG              m_nFirstPageInd;
  ULONG              m_nFirstOffset;
  ULONG              m_nFirstPageOffset;
  ULONG              m_nLogSize;
  ULONG              m_nPageDataSize;

  ULONG              m__nCachedPageNum;
  ULONG              m__nCachedPageInd;

  BOOL               m_bIsAttachedLog;
//  BOOL               m_bIsReplacedFirstPage;

  UINT*              m_paPreCacheOffs;
  CEventsPageArray*  m_paPages;    //log
  CEventsPageArray*  m_paPreCache; //preload cache
  CEventsPageArray*  m_pPagePreCache;
  CEventsFilter      m_EventsFilter;
  
  ULONG              m_nLastPageOffset;
  ULONG              m_nLastPageIndex;
  //cached event
  BYTE               m_Buf[STACK_LEN];
  YEvent*            m_pcachedEv;
  ULONG              m_ncachedEv;
  //found event
  BYTE               m_BufFEv[STACK_LEN];
  YEvent*            m_pcachedFEv;
  ULONG              m_ncachedFEv;

  int                m_nHeaderLines;

  #ifdef DEBUG_EL
  CString            m_szEvNumText;
  #endif
  CString            m_szLogStatusText;
  CFindInfo*         m_pTextFindInfo;
  UINT               m_nSerachStart;

  CStatic*           m_pLogStatus;
  CEventsList*       m_pList;
  CImageList         m_ImageList;
/*  int                m_nViewMode; //AY*/
  BOOL               m_bDetailImages;

  BOOL               m_bHideOnClose;

private:
#if USE_DLGWAIT
  CMessageDlg      m_dlgWait;
#endif
public:
  CMessagesArbiter  m_MesArb;
  // Construction
public://AY 13.01.2013

  struct CREATE_STRUCT
  {
    WINDOWPLACEMENT wndpl;
    LPCTSTR         szText; //pointer!
    DWORD           dwStyle;
    DWORD           dwStyleEx;
    CWnd*           pParent;
    int             nID;
    HICON           hIcon;
    DWORD           dwHelp;
  };
  int               Create(CREATE_STRUCT* pcs);
  int               ReCreate(CWnd *pWnd);

public:
                CEventsListDlg(/*CWnd* pParent = NULL*/);   // standard constructor
  virtual       ~CEventsListDlg() {TRACE(_T(""));};
  int           __ReCreate(CWnd* pWnd);
  int           AdjustColumnSize();//AY
//  int           SetViewMode(int nMode);// 0-full,1-short //AY
//  int           GetViewMode() const;// 0-full,1-short //AY
  void          SetFilter(const CEventsFilter& filter);
  BOOL          GetFilter(CEventsFilter* pfilter);
  BOOL          SetHeaderLinesCount(int nTextLines);
  void          EnableFilterDialog(BOOL bEnable) {m_bEnableFilterDialog = bEnable;}
  void          ShowLogStatus(BOOL bShow);
  BOOL          IsShowLogStatus() const {return m_bShowLogStatus;}
  void          SetDetailImages(BOOL bShow);
  BOOL          IsDetailImages() const {return m_bDetailImages;}
  BOOL          GetDetailImages() const;

  void          SetHideOnClose(BOOL bHideOnClose=TRUE);

public:
  int           DetachLog();

protected:
  void          SetStatusText(CString szText) {if(m_pLogStatus) m_pLogStatus->SetWindowText(szText);}
private:
  /*static */HICON  CreateImage(/*HDC hParentDC, */HICON hIconSource, int sx, int sy, int nTextMask, BOOL bDetailsShow);
  /*static */void   DestroyImage(HICON);
private:
  static UINT   _BackgroundFinding(LPVOID lpVoid);
  UINT          BackgroundFind();

  static UINT   _BackgroundPreLoading(LPVOID lpVoid);
  UINT          BackgroundPreload();
  UINT          CheckAndPreloadPages(CEventsPageArray& aPages, UINT* panDestIndex);
  BOOL          IsNeedPreLoadPages() const;
  inline BOOL   IsAttachedLog()const {return m_bIsAttachedLog;}   
  
  int           AttachLog(YEventsProtocol* pevp, int nMode);

  void          ReInit();
  void          InitForPreloader();
  inline BOOL   IsReplacedFirstPage()const;
protected:
  int           LoadPage(CEventsPage& page, UINT nDestIndex); //fast realization,fast filling (using filtered pages)
#if 0
  int           LoadPage(const BYTE* pData, WORD nEvFirst, ULONG nDestIndex, CEventsPageArray*  paPageCache);//Slow realization, slow filling (filtering pages). The old version. Not used now.
#endif//0
  inline void   SetFirstOffset(ULONG nOffset);
  inline ULONG  GetFirstOffset() const;
  inline ULONG  GetFirstPageOffset() const;

  int             _FindEvent(CFindInfo* pFindInfo, int nStart);
  inline BOOL     _FindAndLoadEvent(ULONG nIndex);
  inline BOOL     _FindAndLoadEventF(ULONG nIndex); //for list finding
  BOOL            GetEventImage(ULONG nIndex, int nBufSize, LPTSTR lpszText, int* pnIcon);
  inline BOOL     GetEventText(ULONG nIndex, int nBufSize, LPTSTR lpszText, int& nTextSize);
  inline BOOL     GetEventTextF(ULONG nIndex, int nBufSize, LPTSTR lpszText, int& nTextSize); //for list finding
  inline BOOL     GetEventID(ULONG nIndex, UINT& nID);
  inline BOOL     GetEventIDF(ULONG nIndex, UINT& nID);
//  BOOL            GetEventHandle(ULONG nIndex, HEVENT hEvent);
         int      __FindEventByTime(YTime tFindTime, BOOL bFindUp, ULONG nStart);
  inline BOOL     GetEventTime(ULONG nIndex, YTime& tTime);
  inline BOOL     GetEventTimeF(ULONG nIndex, YTime& tTime);
  inline BOOL     GetEventChannel(ULONG nIndex, int nBufSize, LPTSTR lpszText, int& nTextSize);

  inline ULONG    GetPageSize() const;
  inline ULONG    GetLogSize() const;
public:
  int             GetOpenMode() const
                    { return m_nOpenMode; }

//overrides
protected:
  virtual void OnOK() {};
  virtual void OnCancel() {};
// Dialog Data
  //{{AFX_DATA(CEventsListDlg)
  //enum { IDD = IDD_EVENTSLIST_DIALOG };
  enum { IDD = 0 };
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CEventsListDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CEventsListDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnDestroy();
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
  afx_msg void    OnClose( );
  afx_msg void    OnMenuCommandRange(UINT nID);
  afx_msg void    OnGetdispinfoEventslist(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg void    OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
//  afx_msg void    OnOdfinditemEventslist(NMHDR* pNMHDR, LRESULT* pResult);
//  afx_msg LRESULT OnFindItem(WPARAM, LPARAM);
  afx_msg LRESULT OnLogEvent    (WPARAM, LPARAM);
  afx_msg LRESULT OnAttach      (WPARAM, LPARAM);
  afx_msg LRESULT OnLoadedBufferBetweenThread(WPARAM, LPARAM);
  afx_msg LRESULT OnLoadedBuffer(WPARAM, LPARAM);
  afx_msg LRESULT OnELFindItem  (WPARAM, LPARAM);
  afx_msg LRESULT OnELBeginFindItem(WPARAM, LPARAM);
  afx_msg LRESULT OnELFinishFindItem(WPARAM, LPARAM);
  afx_msg LRESULT OnSetFilter   (WPARAM, LPARAM);
  afx_msg LRESULT OnListChangedSize(WPARAM, LPARAM);
  DECLARE_MESSAGE_MAP()
  //---------------------------------------
//   class CMessageDlg : public CEmptyAnyDialog<CDialog>
//   {
//     typedef CEmptyAnyDialog<CDialog>  CParentDlg;
//   public:
//     CMessageDlg(/*CWnd* pParent = NULL*/) { m_bCreated=FALSE; m_pText=NULL;}   // standard constructor
//     virtual       ~CMessageDlg(){delete m_pText; m_pText = NULL;}
//     int           ReCreate(CRect rectDlg, LPCTSTR lpszText, CWnd* pParent);
//   private:
//     BOOL          m_bCreated;
//     CFont         m_TextFont;
//     CStatic*      m_pText;
//   protected:
//     virtual void DoDataExchange(CDataExchange* pDX);
//   protected:
//     virtual BOOL OnInitDialog();
//   };
//   //---------------------------------------
};

#include <afxdtctl.h>
#include "xCDialog.h"
#include "xCString.h"
#include "YTime.h"

class CTimeDialog : public CEmptyDialog
{
public:
  typedef CEmptyDialog  CParent;
public:
  CTimeDialog(YTime tDateTime, CWnd* pParent, LPCTSTR szOkCancel);
  ~CTimeDialog();   
  
  BOOL                  InitModal(DWORD style=WS_POPUPWINDOW, DWORD dwExtendedStyle=0, LPCRECT lpRect=NULL, CWnd* pParentWnd=NULL);
  
  YTime                 GetDateTime() const {return m_tDateTime;};
  
protected:// Implementation
  YTime                 m_tDateTime;
  CDateTimeCtrl*        m_pDate;
  CDateTimeCtrl*        m_pTime;
  CWnd*                 m_pParentWnd;
  HLOCAL                m_hLocal;
  CFont*                m_pFont;
  
  CButton*              m_pOK;
  CButton*              m_pCancel;
  
  BYTE*                 m_pBuffer;//03.01.03VEN 
  CStringArray          m_aszButtonNames;
  // Generated message map functions
  //{{AFX_MSG(CThreeChooseDialog)
  //}}AFX_MSG
  afx_msg int           OnCreate(LPCREATESTRUCT lpCreateStruct);
  virtual BOOL          OnInitDialog();
  afx_msg void          OnOk();
public:
  DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CEventsList window

class CEventsList : public CListCtrl {
// Construction
public:
                  CEventsList();
  virtual         ~CEventsList();
  BOOL            Create(DWORD dwStyle, DWORD dwExStyle, RECT& rect, CWnd* pParent, UINT nID);
  int             ReCreate(CWnd* pWnd);

public:
  int             GetLastVisibleItem() const;
  int             GetClientRectWithoutScrolBar(CRect& Rect);
  BOOL            SetHeaderLinesCount(int nTextLines);
// Attributes
protected:
  COLORREF        m_rgbWindow;
  CRect           m_rectList; //size without header and scrollbar
//  CRect           m_rectListWithoutScroolAndHeader; //size without header and scrollbar
  CRect           m_rectListHead;
  CRect           m_rectClientArea;

//  CMemDC*            m_pmemDC;
//  int             m_nRedraws;
protected: 
  CBitmap*        m_pbmpView; 

  int             m_nSortColumn;
protected:
  CHeaderCtrlEx   m_HeaderCtrl;
  CFont           m_NewHeaderFont;

// Operations
public:

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CEventsList)
  //}}AFX_VIRTUAL

// Implementation
public:

  // Generated message map functions
protected:
  //{{AFX_MSG(CEventsList)
  afx_msg void OnPaint();
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	//}}AFX_MSG
  afx_msg void    OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void    OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  DECLARE_MESSAGE_MAP()
};

#include "EventsListDlg.inl"
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVENTSLISTDLG_H__E948B834_2864_4B91_86A6_7B32F8E07B1F__INCLUDED_)
