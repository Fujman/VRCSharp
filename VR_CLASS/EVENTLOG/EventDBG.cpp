#include "stdafx.h"
#include "eventlog.h"
#include "eventwin.h"
#include "string.h"
#include "xCString.h"

int  YEventsProtocol::SendEventDebug(const YEvent& ev, ULONG nOffset, ULONG nSize) {
  if(m_wndLog!=NULL) { //TO DO
    TCHAR sz[255];
    ev.GetText(sz,255);
    _tcscat(sz,FormatString(_T("     Page:%d Offset:%ld  Size:%ld"),
      ThisPageOffset(nOffset)/m_nPageSize,nOffset,nSize));
    m_wndLog->AddLine(sz);
    return SUCCESS;
  }
  return FAILURE;
}
