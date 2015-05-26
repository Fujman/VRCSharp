#include "stdafx.h"
#include "EventClass.h"
#include "Event.h"
#include "mm/MM4CC.h"
#include "xCString.h"

inline BOOL operator==(const YEventClassInfo& info, const YEventBaseData& data)
{
  BOOL b = info.m_nClass == data.GetClass();
  b = b && (info.m_nType == data.GetType() || info.m_nType==(WORD)-1);
  if(info.m_nMessageID!=0)
    b = b && (info.m_nMessageID == data.GetMessageID());
  if(info.m_nSignature!=0)
    b = b && (info.m_nSignature == data.GetSignature());
  return b;
}
inline BOOL operator!=(const YEventClassInfo& info, const YEventBaseData& data)
{
  return ! operator==(info, data);
}

BOOL YEventClassInfo::operator==(const YEventBaseData& data) const
{
  return ::operator==(*this,data);
}
BOOL YEventClassInfo::operator!=(const YEventBaseData& data) const
{
  return ::operator!=(*this,data);
}

YEventClassInfo* YEVENT__CreateClass(YEventClassInfo* p, YEventClassInfo*& s_pClassesList)
{
  BOOL bNoType2 = p->m_nType != (WORD)-1;
  WORD wOne = (WORD)-1;
  BOOL bNoTyped  = p->m_nType != wOne;
 
  //check substitutes
  for(YEventClassInfo *pPrev=NULL, *pItem=s_pClassesList; pItem!=NULL; pPrev=pItem, pItem=pItem->m_pNext){
    BOOL bSame  = pItem->m_nClass==p->m_nClass;
    bSame=bSame&& pItem->m_nType==p->m_nType;
    if(pItem->m_nClass==EVN_xxBIT_CLASS){
      bSame=bSame&& pItem->m_nMessageID!=p->m_nMessageID;
      bSame=bSame&& pItem->m_nSignature!=p->m_nSignature;
    }
    if(!bSame)
      continue;

    if(pPrev!=NULL)//skip this element
      pPrev->m_pNext = pItem->m_pNext;
    if(pPrev==NULL)//replace root
      s_pClassesList = pItem->m_pNext;
    pItem->m_pHead = pItem;//mark used
    pItem->m_pNext = NULL;//set single
    YEVENT__ClassReplaceDump(pItem);
    break;
  }
  //find tile
  for(YEventClassInfo* pTile=s_pClassesList; pTile!=NULL && pTile->m_pNext!=NULL; pTile=pTile->m_pNext)
    ;

  //add item
  if(p->m_pHead==NULL && s_pClassesList==NULL){ //add single
    p->m_pNext = NULL;
    p->m_pHead = p;
    s_pClassesList = p;
  }else if(p->m_pHead==NULL && p->m_nType!=(WORD)-1){//add to head
    p->m_pNext = s_pClassesList;
    p->m_pHead = p;
    s_pClassesList = p;
  }else if(p->m_pHead==NULL && p->m_nType==(WORD)-1){//add to tile
    p->m_pHead = s_pClassesList;
    p->m_pNext = pTile->m_pNext;
    pTile->m_pNext = p;
  }

  //adjust root
  for(pItem=s_pClassesList; pItem!=NULL; pItem=pItem->m_pNext)
    pItem->m_pHead = s_pClassesList;

  return (YEventClassInfo*)p;
}


int YEVENT__ClassReplaceDump(const YEventClassInfo* pNext)
{
#ifdef _DEBUG
  afxDump << "\n**" << "YEvent" << " metaclass object replaced **:" << "\r\n";
    afxDump << "  event:" << pNext->m_szDescript;
    afxDump << "  class:" << pNext->m_nClass;
    afxDump << "  type:"  << pNext->m_nType;
    if(pNext->m_nSignature)
      afxDump << "  4cc:"   << MM4CC(pNext->m_nSignature).GetAsString();
    if(pNext->m_nMessageID)
      afxDump << "  message:" << pNext->m_nMessageID;
    afxDump << "\r\n";
#endif
  return 0;
}

int YEVENT__ClassesDump()
{
  const YEventClassInfo* pNext = YClass<YEvent16,YEvent>::s_ClassInfo.m_pHead;
#ifdef _DEBUG
  afxDump << "\n**" << "YEvent" << " metaclass dump **:" << "\r\n";
  for(int nClass=0; pNext!=0; pNext=pNext->m_pNext, ++nClass){
    afxDump << "  event:" << pNext->m_szDescript;
    afxDump << "  class:" << pNext->m_nClass;
    afxDump << "  type:"  << pNext->m_nType;
    if(pNext->m_nMessageID)
      afxDump << "  message:" << pNext->m_nMessageID;
    if(pNext->m_nSignature) {
      afxDump << "  4cc:"   << MM4CC(pNext->m_nSignature).GetAsString();
      afxDump << FormatString(_T(" 0x%08.8X (%u)"),pNext->m_nSignature,pNext->m_nSignature);
    }
    afxDump << "\r\n";
  }
  afxDump << "Tolal " << nClass << " derived classes in metaclass " << "YEvent" << "\r\n";
#else
  for(int nClass=0; pNext!=0; pNext=pNext->m_pNext, ++nClass)
    ;
#endif
  return nClass;
}

