#ifndef __YTIMETZ_H
#define __YTIMETZ_H
#include "YTime.h"
#include "YTimeZone.h"

/////////////////////////////////////////////////////////////////
// Class YTimeTZ

class YTimeTZ : public YTime
{
protected:
//YTIME                         m_data; //UTC
  YTIME                         m_bias; //UTC = local time + bias
public:
  static YTimeTZ                mktime(YTime t, const YTimeZone* ptz=NULL);
  YTimeTZ(YTIME t, YTIME bias);
  YTimeTZ(const YTimeTZ& ytz);
  YTimeTZ();
  YTimeTZ(const SYSTEMTIME& st, const YTimeZone* ptz=NULL);
private: //unused now - TO DO:
  YTimeTZ(YTime t);
  YTimeTZ(CTime t);

public:
  YTIME                         GetBias() const
                                  { return m_bias; }
public:
  static YTimeSpan              GetCurrentBias();
  static YTimeTZ                GetCurrentTime();

public:
  static YTimeSpan              CalcBias(YTime t, const YTimeZone* ptz=NULL);
};

inline YTimeTZ YTimeTZ::mktime(YTime t, const YTimeZone* ptz)
  { return YTimeTZ(t,CalcBias(t,ptz)); }



#endif//__YTIMETZ_H
#pragma once
