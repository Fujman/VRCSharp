// EventsFilter.h: interface for the CEventsFilter class.
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_EVENTSFILTER_H__4F51B5C4_A23F_42A7_B113_F18ABE5F98B4__INCLUDED_)
#define AFX_EVENTSFILTER_H__4F51B5C4_A23F_42A7_B113_F18ABE5F98B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Channels/chan_id.h"
#include "yTime.h"

#pragma pack(push,1)
//-----------
class CEventsPageArray;
//-----------
class CEventsFilter {
  friend class      CEventsPageArray;
public:
  enum {_MAXCHANNELS=128};

	                  CEventsFilter();
	virtual           ~CEventsFilter();
public:
//	static void       _SetEventType(DWORD& dwTarget, DWORD dwErrFlags, DWORD dwWarnFlags, DWORD dwInfoFlags);
  void              SetUseFilter(BOOL bUse);
  void              SetShowChannelsEvents(BOOL bShow) {m_bShowChsEvs = bShow;}
  void              SetStartTime(YTime tTime);
  void              SetStopTime (YTime tTime);
  void              SetLevelWarningFlags(DWORD dwLevelsBits);//1bit-0 lev,2bit - 1 lev, 3bit- 4 lev .. 8bit - 7 lev
  void              SetLevelInfoFlags(DWORD dwLevelsBits);//1bit-0 lev,2bit - 1 lev, 3bit- 4 lev .. 8bit - 7 lev
  void              SetLevelErrorFlags(DWORD dwLevelsBits);//1bit-0 lev,2bit - 1 lev, 3bit- 4 lev .. 8bit - 7 lev
  BOOL              SetChannelsList(const YSRSChannelsList*  paChannels);

  BOOL              IsUseFilter() const {return m_bUseFilter;}
  BOOL              IsShowChannelsEvents() const {return m_bShowChsEvs;}
  YTime             GetStartTime() const {return m_tStart;}
  YTime             GetStopTime() const {return m_tStop;}
  DWORD             GetLevelWarningFlags() const {return m_dwLevWarn;}
  DWORD             GetLevelInfoFlags() const {return m_dwLevInfo;}
  DWORD             GetLevelErrorFlags() const {return m_dwLevErr;}
  BOOL              GetChannelsList(YSRSChannelsList* paChannels) const;
 
//  DWORD     GetEventType() const {return m_dwEventType;}
                                   // 3          2          1          0
private:                           //10987654 32109876 54321098 76543210
  DWORD             m_dwEventType; //00000000 IIIIIIII WWWWWWWW EEEEEEEE W-warning,I-info,E-error
protected:
  BOOL              m_bUseFilter;                                   
  BOOL              m_bShowChsEvs;                                  
  DWORD             m_dwLevWarn; //depth flags - //0..7             
  DWORD             m_dwLevInfo; //depth flags - //0..7             
  DWORD             m_dwLevErr;  //depth flags - //0..7             
  YTime             m_tStart;                                       
  YTime             m_tStop;                                        
  int               m_anChannels[_MAXCHANNELS];
  YSRSChannelsList  m_aChannels;
};

#pragma pack(pop)

#endif // !defined(AFX_EVENTSFILTER_H__4F51B5C4_A23F_42A7_B113_F18ABE5F98B4__INCLUDED_)
