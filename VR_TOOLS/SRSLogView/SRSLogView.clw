; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "srslogview.h"
LastPage=0

ClassCount=10
Class1=CEventsListDlg
Class2=CEventsList
Class3=CEventsWindow
Class4=CChildFrame
Class5=CEventsFilterDlg
Class6=CMainFrame
Class7=CSRSLogViewApp
Class8=CAboutDlg
Class9=CSRSLogViewDoc
Class10=CSRSLogViewView

ResourceCount=6
Resource1=IDD_SRSLOGVIEW_FORM (English (U.S.))
Resource2=IDR_EVENTS_FILTER (English (U.S.))
Resource3=IDD_EVENTS_FILTER_EX
Resource4=IDR_SRSLOGTYPE (English (U.S.))
Resource5="IDD_XABOUTDLG" (Neutral (Default))
Resource6=IDR_MAINFRAME (English (U.S.))

[CLS:CEventsListDlg]
Type=0
HeaderFile=\VR\VR_CLASS\EVENTLOG\CONTROLS\EventsListDlg.h
ImplementationFile=\VR\VR_CLASS\EVENTLOG\CONTROLS\EventsListDlg.cpp
Filter=D
BaseClass=CEmptyAnyDialog<CResizableDialog>/*CParent*/
VirtualFilter=dWC

[CLS:CEventsList]
Type=0
BaseClass=CListCtrl
HeaderFile=\VR\VR_CLASS\EVENTLOG\CONTROLS\EventsListDlg.h
ImplementationFile=\VR\VR_CLASS\EVENTLOG\CONTROLS\EventsListDlg.cpp
Filter=N
VirtualFilter=FWC

[CLS:CEventsWindow]
Type=0
BaseClass=CWnd
HeaderFile=\VR\VR_CLASS\EVENTLOG\EventWin.h
ImplementationFile=\VR\VR_CLASS\EVENTLOG\EventWin.cpp

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CEventsFilterDlg]
Type=0
BaseClass=CDialogBar
HeaderFile=EventsFilterDlg.h
ImplementationFile=EventsFilterDlg.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CSRSLogViewApp]
Type=0
HeaderFile=SRSLogView.h
ImplementationFile=SRSLogView.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=SRSLogView.cpp
ImplementationFile=SRSLogView.cpp
LastObject=CAboutDlg

[CLS:CSRSLogViewDoc]
Type=0
BaseClass=CDocument
HeaderFile=SRSLogViewDoc.h
ImplementationFile=SRSLogViewDoc.cpp

[CLS:CSRSLogViewView]
Type=0
BaseClass=CParent
HeaderFile=SRSLogViewView.h
ImplementationFile=SRSLogViewView.cpp

[DLG:IDR_EVENTS_FILTER]
Type=1
Class=CEventsFilterDlg

[DLG:IDD_SRSLOGVIEW_FORM (English (U.S.))]
Type=1
Class=?
ControlCount=9
Control1=IDC_STATIC_BOX,static,1350696960
Control2=IDC_BUTTON_OPENLOG,button,1208025088
Control3=IDC_BUTTON1,button,1208025088
Control4=IDC_BUTTON_OPENLOG_CURSES,button,1208025088
Control5=IDC_BUTTON2,button,1208025088
Control6=IDC_BUTTON3,button,1208025088
Control7=IDC_BUTTON4,button,1342242816
Control8=IDC_BUTTON_SHOW_DETAILS,button,1342242816
Control9=IDC_BUTTON_SHOW_STATUS,button,1342242816

[DLG:"IDD_XABOUTDLG" (Neutral (Default))]
Type=1
Class=?
ControlCount=9
Control1=IDOK,button,1342373889
Control2=IDC_STATIC_SRS_EMBLEM,static,1342179342
Control3=IDC_APPNAME,static,1342308480
Control4=IDC_VERSION,static,1342308352
Control5=IDC_COPYRIGHT,static,1342308480
Control6=IDC_BUILD,static,1342308352
Control7=IDC_APP_ICON,static,1342177283
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC_INFO,static,1342308352

[DLG:IDD_EVENTS_FILTER_EX]
Type=1
Class=?
ControlCount=19
Control1=IDC_TIMEPICKER_START,SysDateTimePick32,1342242873
Control2=IDC_TIMEPICKER_STOP,SysDateTimePick32,1342242873
Control3=IDC_EDIT_INFO,edit,1350639744
Control4=IDC_SPIN_INFO,msctls_updown32,1342177463
Control5=IDC_EDIT_WARNING,edit,1350639744
Control6=IDC_SPIN_WARNING,msctls_updown32,1342177463
Control7=IDC_EDIT_ERROR,edit,1350639744
Control8=IDC_SPIN_ERROR,msctls_updown32,1342177463
Control9=IDC_STATIC_CHANNELS,static,1342308352
Control10=IDC_LIST_CHANNELS,SysListView32,1350680593
Control11=IDC_CHECK_ALL_CHANNELS,button,1342242819
Control12=IDC_CHECK_INFO,button,1342242819
Control13=IDC_CHECK_WARNING,button,1342242819
Control14=IDC_CHECK_ERROR,button,1342242819
Control15=IDC_COMBO_DATA_SPAN,combobox,1344340226
Control16=IDC_MONTHCALENDAR,SysMonthCal32,1342242832
Control17=IDC_STATIC_DATE_START,static,1342308353
Control18=IDC_STATIC_DATE_STOP,static,1342308353
Control19=IDC_STATIC,button,1342177287

[DLG:IDR_EVENTS_FILTER (English (U.S.))]
Type=1
Class=?
ControlCount=24
Control1=IDC_CHECK_START_USE,button,1342242819
Control2=IDC_STATIC_START,button,1342177287
Control3=IDC_DATEPICKER_START,SysDateTimePick32,1342242864
Control4=IDC_TIMEPICKER_START,SysDateTimePick32,1342242873
Control5=IDC_CHECK_STOP_USE,button,1342242819
Control6=IDC_STATIC_STOP,button,1342177287
Control7=IDC_DATEPICKER_STOP,SysDateTimePick32,1342242864
Control8=IDC_TIMEPICKER_STOP,SysDateTimePick32,1342242873
Control9=IDC_EDIT_INFO,edit,1350639744
Control10=IDC_SPIN_INFO,msctls_updown32,1342177463
Control11=IDC_EDIT_WARNING,edit,1350639744
Control12=IDC_SPIN_WARNING,msctls_updown32,1342177463
Control13=IDC_EDIT_ERROR,edit,1350639744
Control14=IDC_SPIN_ERROR,msctls_updown32,1342177463
Control15=IDC_STATIC_CHANNELS,static,1342308352
Control16=IDC_LIST_CHANNELS,SysListView32,1350680593
Control17=IDC_CHECK_ALL_CHANNELS,button,1342242819
Control18=IDC_CHECK_INFO,button,1342242819
Control19=IDC_CHECK_WARNING,button,1342242819
Control20=IDC_CHECK_ERROR,button,1342242819
Control21=IDC_COMBO_VIEW_RANGE,combobox,1344340226
Control22=IDC_CHECK_USE_FILTER,button,1342242819
Control23=IDC_CHECK_APPLY,button,1342246914
Control24=IDC_CHECK_CHANNELS_USE,button,1342242819

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_FILE_PRINT
Command7=ID_APP_ABOUT
CommandCount=7

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_PRINT_SETUP
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_LOG_RESIZE
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_SRSLOGTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_CLOSE
Command3=ID_FILE_PRINT
Command4=ID_FILE_PRINT_PREVIEW
Command5=ID_FILE_PRINT_SETUP
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_STATUS_BAR
Command10=ID_WINDOW_NEW
Command11=ID_WINDOW_CASCADE
Command12=ID_WINDOW_TILE_HORZ
Command13=ID_WINDOW_ARRANGE
Command14=ID_APP_ABOUT
CommandCount=14

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_NEXT_PANE
Command8=ID_PREV_PANE
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_CUT
Command12=ID_EDIT_UNDO
CommandCount=12

