#ifndef __YTIMEZONE
#define __YTIMEZONE

#ifndef __YTIME_DEFINED
#define __YTIME_DEFINED
typedef __int64 YTIME;
#endif//__YTIME_DEFINED

class YTimeZone: public TIME_ZONE_INFORMATION //AY 01.11.2010
/* inherited
  LONG       Bias;             //UTC = local time + bias 
  WCHAR      StandardName[32];
  SYSTEMTIME StandardDate;
  LONG       StandardBias;
  WCHAR      DaylightName[32];
  SYSTEMTIME DaylightDate;
  LONG       DaylightBias;
*/
{
public: //helpers
  static int PASCAL tzdate(const SYSTEMTIME* pstTZ /*local*/, SYSTEMTIME* pstLOCAL/*in-out, local*/);
  static int PASCAL tztime(YTIME* ptUTC, const SYSTEMTIME* pstLOCAL, const YTimeZone* ptz=NULL);
  static int PASCAL tzbias(YTIME* ptsBias, const SYSTEMTIME* pstLOCAL, const YTimeZone* ptz=NULL);
  static const YTimeZone* safe_get_tz();
protected:
  static YTimeZone* s_ptz;
  static YTimeZone  s_tz;
};

inline const YTimeZone* YTimeZone::safe_get_tz()
{
  if(s_ptz!=NULL)
    return s_ptz;
  DWORD dwRet = ::GetTimeZoneInformation(&s_tz);
  if(dwRet==TIME_ZONE_ID_INVALID)
    return NULL;
  ASSERT(dwRet!=TIME_ZONE_ID_UNKNOWN                                  || dwRet==0/*daylight saving time is not used */);
  ASSERT(dwRet==TIME_ZONE_ID_STANDARD || dwRet==TIME_ZONE_ID_DAYLIGHT || dwRet==0/*daylight saving time is not used */);
  s_ptz = &s_tz;
  return  &s_tz;
}

#endif//__YTIMEZONE
#pragma once