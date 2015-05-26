#include "YTime.h"

#ifndef __YAREA_DEFINED
#define __YAREA_DEFINED

typedef __int64 YAREA__LONGTITUDE;
typedef __int64 YAREA__LATITUDE;
typedef __int64 YAREA__ALTITUDE;

#pragma pack(push,1)
struct YAREA
{
  YAREA__LONGTITUDE m_longtitude;
  YAREA__LATITUDE   m_latitude;
  YAREA__ALTITUDE   m_altitude;
};
#pragma pack(pop)

#endif//__YAREA_DEFINED

class YArea : public YAREA
{
};