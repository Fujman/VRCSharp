#ifndef __EVNTAPP_INL
#define __EVNTAPP_INL
#define time_t YEventBaseData::time_t //AY 01.02.2011
/////////////////////////////////////////////////////////////////////////////
// Class YEventChannel inline implementation
inline UINT YEventApplication::GetMessage() const
  { return GetData16(); }

inline UINT YEventApplication::SetMessage(UINT nMessage)
  { return (SetData16(nMessage)); }


inline YEventApplication::YEventApplication()
  : YEvent64(EVN_APPLICATION_TYPE,0,0)
{ }

inline YEventApplication::YEventApplication(const void *p, int n/*0*/)
  : YEvent64(p,n)
{ ASSERT(m_nType==EVN_APPLICATION_TYPE); }

inline YEventApplication::YEventApplication(UINT nMessage, const char* psz, time_t tTime, WORD nMsec/*0*/)
  : YEvent64(EVN_APPLICATION_TYPE)
{
  SetMessage(nMessage);
  if(tTime!=-1)
    SetTime(tTime,nMsec);
  SetString(psz);
}
inline YEventApplication::YEventApplication(UINT nMessage, int n1, int n2, time_t tTime, WORD nMsec/*0*/)
  : YEvent64(EVN_APPLICATION_TYPE,n1,n2)
{
  SetMessage(nMessage);
  if(tTime!=-1)
    SetTime(tTime,nMsec);
}
inline YEventApplication::YEventApplication(UINT nMessage, const char* psz)
  : YEvent64(EVN_APPLICATION_TYPE)
{
  SetMessage(nMessage);
  SetTime();
  SetString(psz);
}
inline YEventApplication::YEventApplication(UINT nMessage, int n1, int n2)
  : YEvent64(EVN_APPLICATION_TYPE,n1,n2)
{
  SetMessage(nMessage);
  SetTime();
}


inline YEventApplication::~YEventApplication()
  { }

#undef time_t
#endif//__EVNTAPP_INL
