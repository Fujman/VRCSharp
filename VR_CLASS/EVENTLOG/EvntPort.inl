#ifndef __EVNTPORT_INL
#define __EVNTPORT_INL
#define time_t YEventBaseData::time_t //AY 01.02.2011
/////////////////////////////////////////////////////////////////////////////
// Class YEventPort inline implementation
inline YEventPort::YEventPort(const void *p, int n/*0*/) : YEvent20(p,n)
  { }
inline YEventPort::YEventPort() : YEvent20((DWORD)0)
  { }
inline YEventPort::~YEventPort()
  { }


inline BYTE  YEventPort::GetByte() const
  { return (BYTE)(GetData20()&0xFF); }

inline WORD  YEventPort::GetPort() const
  { return (WORD)((GetData20()>>8)&0x7FF); }

inline int   YEventPort::isIn() const
  { return ((GetData20()>>8)&0x800)!=0; }

inline int   YEventPort::isOut() const
  { return ((GetData20()>>8)&0x800)==0; }


inline BYTE  YEventPort::SetByte(BYTE bData) {
  SetData20((GetData20()&0xFFFFFF00UL)+bData);
  return bData;
}
inline WORD  YEventPort::SetPort(WORD nPort) {
  ASSERT(nPort<=0x7FF); // 2047
  SetData20((GetData20()&0xFFF800FFUL)+(((DWORD)nPort)<<8));
  return nPort;
}
inline void  YEventPort::in(WORD nPort,BYTE bData){
  ASSERT(nPort<=0x7FF); // 2047
  DWORD  dw = (((((DWORD)nPort)<<8) + bData) | 0x80000UL);
  SetData20(dw);
  SetTime();
}
inline void  YEventPort::out(WORD nPort,BYTE bData){
  ASSERT(nPort<=0x7FF); // 2047
  DWORD  dw = (((((DWORD)nPort)<<8) + bData) & 0x7FFFFUL);
  SetData20(dw);
  SetTime();
}
inline void  YEventPort::in(WORD nPort,BYTE bData,time_t tTime,WORD nMsec/*0*/){
  in(nPort, bData);
  if(tTime!=-1)
    SetTime(tTime,nMsec);
}
inline void  YEventPort::out(WORD nPort,BYTE bData,time_t tTime,WORD nMsec/*0*/){
  out(nPort, bData);
  if(tTime!=-1)
    SetTime(tTime,nMsec);
}

#undef time_t
#endif//__EVNTPORT_INL
