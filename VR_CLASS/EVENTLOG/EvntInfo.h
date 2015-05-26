inline LPCTSTR YEventStripInfo(CString& sz)
{
  if(!sz.IsEmpty() && sz[0]=='|') 
  {
    int iLast = sz.Find('|',1);
    if(iLast>0)
     sz.Delete(0,iLast+1);
  }
  return sz;
}

// format: "|0abcd|Event text"
inline int YEventGetInfo(const CString& sz, int* pnLevel=NULL, LPTSTR szClass=NULL)
{
  int nLevel; 
  if(pnLevel==NULL)
    pnLevel = &nLevel;
  *pnLevel = -1;

  if(!sz.IsEmpty() && sz[0]=='|') 
  {
    int iLast = sz.Find('|',1);
    if(iLast==-1)
      return -1;
    if(sz[1]>='0' || sz[1]<='9')
      *pnLevel = sz[1]-'0';
    if(szClass!=NULL) {
      LPTSTR psz = szClass;
      for(int i=(*pnLevel==-1?1:2); i<=iLast; ++i)
        *psz++ = sz[i];
      *psz = '\0';
    }
  }
  return *pnLevel;
}
