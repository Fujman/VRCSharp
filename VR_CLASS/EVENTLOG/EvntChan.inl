#ifndef __EVNTCHAN_INL
#define __EVNTCHAN_INL
#define time_t YEventBaseData::time_t //AY 01.02.2011
/////////////////////////////////////////////////////////////////////////////
// Class YEventChannel inline implementation
inline UINT YEventChannel::GetMessage() const
  { return GetData16(); }

inline int YEventChannel::GetChannel() const
  { return GetData16(1); }
//inline int YEventChannel::GetChannel() const
//  { return GetData32(0); }

inline int YEventChannel::GetData(short* pData16/*NULL*/) const
{ 
  if(pData16!=NULL)
    *pData16 = GetData16(2);
  return GetData32(1); 
}

inline UINT YEventChannel::SetMessage(UINT nMessage)
  { return (SetData16(nMessage)); }

inline int YEventChannel::SetChannel(int nChannel)
  { return SetData16(nChannel,1); }
//inline int YEventChannel::SetChannel(int nChannel)
//  { return (SetData32(nChannel,0)); }

inline int YEventChannel::SetData(int nData, short pData16)
  { return (SetData16(pData16,2),SetData32(nData,1)); }



inline YEventChannel::YEventChannel()
  : YEvent64(EVN_CHANNELS_TYPE,0,0)
{ }

inline YEventChannel::YEventChannel(const void *p, int n/*0*/)
  : YEvent64(p,n)
{ ASSERT(m_nType==EVN_CHANNELS_TYPE); }

inline YEventChannel::YEventChannel(int nChannel, UINT nMessage, int nData, short nData16, time_t tTime, WORD nMsec)
  : YEvent64(EVN_CHANNELS_TYPE)
{
  SetMessage(nMessage);
  SetChannel(nChannel);
  SetData(nData,nData16);
  if(tTime!=-1)
    SetTime(tTime,nMsec);
}
inline YEventChannel::YEventChannel(int nChannel, UINT nMessage, int nData/*0*/, short nData16/*0*/)
  : YEvent64(EVN_CHANNELS_TYPE)
{
  SetMessage(nMessage);
  SetChannel(nChannel);
  SetData(nData, nData16);
  SetTime();
}

inline YEventChannel::YEventChannel(int nChannel, UINT nMessage, const char* sz, time_t tTime, WORD nMsec/*0*/)
  : YEvent64(EVN_CHANNELS_TYPE)
{
  SetMessage(nMessage);
  SetChannel(nChannel);
  SetString(sz);
  if(tTime!=-1)
    SetTime(tTime,nMsec);
}
inline YEventChannel::YEventChannel(int nChannel, UINT nMessage, const char* sz)
  : YEvent64(EVN_CHANNELS_TYPE)
{
  SetMessage(nMessage);
  SetChannel(nChannel);
  SetString(sz);
  SetTime();
}
inline YEventChannel::~YEventChannel()
{ }

#undef time_t
#endif//__EVNTCHAN_INL
