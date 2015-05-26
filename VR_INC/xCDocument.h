#ifndef __XCDOCUMENT_H
#define __XCDOCUMENT_H

#include "xCDocTemplate.h"

inline CDocument* CDocument__GetApplicationDocument(CWinApp* pApp=NULL, BOOL bUseView=TRUE)
{
  CDocTemplate* pDocTemplate = CDocTemplate__GetApplicationDocTemplate(pApp,TRUE,bUseView);
  if(pDocTemplate==NULL)
    return NULL;
  for(POSITION posDoc=pDocTemplate->GetFirstDocPosition(); posDoc!=NULL; ) {
    CDocument* pDoc = pDocTemplate->GetNextDoc(posDoc);
    if(!bUseView)
      return pDoc;
    for(POSITION posView=pDoc->GetFirstViewPosition(); posView!=NULL; )
      return pDoc;
  }
  return NULL;
}

inline CView* CDocument__GetApplicationActiveView()
{
  CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
  CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
  CView *pView = pChild->GetActiveView();
  return pView;
}

inline CView* CDocument__GetView(CDocument* pDoc)
{
  if(pDoc==NULL)
    pDoc = CDocument__GetApplicationDocument(NULL,TRUE);
  if(pDoc==NULL)
    return NULL;
  for(POSITION posView=pDoc->GetFirstViewPosition(); posView!=NULL; )
    return pDoc->GetNextView(posView);
  return NULL;
}

#ifdef _DEBUG
inline void CDocument__DumpDocument(CDocument* pDocument, CDumpContext& dc)
{
  if(pDocument==NULL)
    pDocument = CDocument__GetApplicationDocument();
  if(pDocument==NULL)
    return;
  CDocument* pDoc = pDocument;
  dc << "=== Document =====================================\n";
  pDoc->Dump(dc);
  for(POSITION posView=pDoc->GetFirstViewPosition(); posView!=NULL; ){
    dc << "--- View -----------------------------------------\n";
    CView* pView = pDoc->GetNextView(posView);
    pView->Dump(dc);
  }
  dc << "\n";
}

inline void CDocument__DumpDocTemplate(CDocument* pDocument, CDumpContext& dc)
{
  if(pDocument==NULL)
    pDocument = CDocument__GetApplicationDocument();
  if(pDocument==NULL)
    return;
  CDocTemplate* pDocTemplate = pDocument->GetDocTemplate();
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

#endif//__XCDOCUMENT_H
#pragma once
