/////////////////////////////////////////////////////////////////////////////
// YEventClassInfo
#include "os/OsLock.h"

template <> inline YEventClassInfo* YMetaClass<YEventBaseData,YEventClassInfo>::
CreateClass(YEventClassInfo* p)
{
  YEventClassInfo* YEVENT__CreateClass(YEventClassInfo* p, YEventClassInfo*& s_pClassesList);

  OS_LOCK(&s_nClassesLock);

  p = YEVENT__CreateClass(p,s_pClassesList);

  OS_UNLOCK(&s_nClassesLock);
  return (YEventClassInfo*)p;
}

#include "YClass.inl"