#ifndef __XCDOCTEMPLATE_H
#define __XCDOCTEMPLATE_H

inline CDocTemplate* CDocTemplate__GetApplicationDocTemplate(CWinApp* pApp=NULL, BOOL bUseDoc=TRUE, BOOL bUseView=TRUE)
{
  bUseDoc = bUseDoc || bUseView;
  if(pApp==NULL)
    pApp = ::AfxGetApp();
  for(POSITION pos=pApp->GetFirstDocTemplatePosition(); pos!=NULL; ) {
    CDocTemplate* pDocTemplate = pApp->GetNextDocTemplate(pos);
    if(!bUseDoc)
      return pDocTemplate;
    for(POSITION posDoc=pDocTemplate->GetFirstDocPosition(); posDoc!=NULL; ) {
      CDocument* pDoc = pDocTemplate->GetNextDoc(posDoc);
      if(!bUseView)
        return pDocTemplate;
      for(POSITION posView=pDoc->GetFirstViewPosition(); posView!=NULL; )
        return pDocTemplate;
    }
  }
  return NULL;
}

inline CDocument* CDocTemplate__GetDocument(CDocTemplate* pDocTemplate=NULL)
{
  if(pDocTemplate==NULL)
    pDocTemplate = CDocTemplate__GetApplicationDocTemplate(NULL,TRUE,FALSE);
  if(pDocTemplate==NULL)
    return NULL;
  for(POSITION pos=pDocTemplate->GetFirstDocPosition(); pos!=NULL; )
    return pDocTemplate->GetNextDoc(pos);
  return NULL;
}

inline CView* CDocTemplate__GetView(CDocTemplate* pDocTemplate=NULL)
{
  if(pDocTemplate==NULL)
    pDocTemplate = CDocTemplate__GetApplicationDocTemplate(NULL,TRUE,TRUE);
  if(pDocTemplate==NULL)
    return NULL;
  for(POSITION pos=pDocTemplate->GetFirstDocPosition(); pos!=NULL; ) {
    CDocument* pDoc = pDocTemplate->GetNextDoc(pos);
    for(pos=pDoc->GetFirstViewPosition(); pos!=NULL; )
      return pDoc->GetNextView(pos);
  }
  return NULL;
}

#ifdef _DEBUG
inline void CDocTemplate__DumpDocTemplate(CDocTemplate* pDocTemplate/*NULL*/, CDumpContext& dc)
{
  if(pDocTemplate==NULL)
    pDocTemplate = CDocTemplate__GetApplicationDocTemplate();
  if(pDocTemplate==NULL)
    return;
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

#endif//__XCDOCTEMPLATE_H
