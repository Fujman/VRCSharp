#ifndef __XCVIEW_H
#define __XCVIEW_H

#include "xCDocument.h"

inline CView* CView__GetApplicationView(CWinApp* pApp=NULL)
{
  CDocument* pDoc = CDocument__GetApplicationDocument(pApp);
  if(pDoc==NULL)
    return NULL;
  for(POSITION pos=pDoc->GetFirstViewPosition(); pos!=NULL; )
    return pDoc->GetNextView(pos);
  return NULL;
}

#ifdef _DEBUG
inline void CView__DumpView(CView* pView, CDumpContext& dc)
{
  if(pView==NULL)
    pView = CView__GetApplicationView();
  if(pView==NULL)
    return;
  dc << "--- View -----------------------------------------\n";
  pView->Dump(dc);
  dc << "\n";
}

inline void CView__DumpDocument(CView* pView, CDumpContext& dc)
{
  if(pView==NULL)
    pView = CView__GetApplicationView();
  if(pView==NULL)
    return;
  CDocument* pDoc = pView->GetDocument();
  dc << "=== Document =====================================\n";
  pDoc->Dump(dc);
  for(POSITION posView=pDoc->GetFirstViewPosition(); posView!=NULL; ){
    dc << "--- View -----------------------------------------\n";
    CView* pView = pDoc->GetNextView(posView);
    pView->Dump(dc);
  }
  dc << "\n";
}

inline void CView__DumpDocTemplate(CView* pView, CDumpContext& dc)
{
  if(pView==NULL)
    pView = CView__GetApplicationView();
  if(pView==NULL)
    return;
  CDocTemplate* pDocTemplate = pView->GetDocument()->GetDocTemplate();
  dc << "EEE Template EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n";
  pDocTemplate->Dump(dc);
  for(POSITION pos=pDocTemplate->GetFirstDocPosition(); pos!=NULL; ){
    CDocument* pDoc = pDocTemplate->GetNextDoc(pos);
    dc << "=== Document =====================================\n";
    pDoc->Dump(dc);
    for(POSITION posView=pDoc->GetFirstViewPosition(); posView!=NULL; ){
      dc << "--- View -----------------------------------------\n";
      CView* pView = pDoc->GetNextView(posView);
      pView->Dump(dc);
    }
  }
  dc << "\n";
}
#endif//_DEBUG

#endif//__XCVIEW_H
#pragma once
