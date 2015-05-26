// YRealTimer.h: interface for the YRealTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YREALTIMER_H__F54731A9_1507_4E22_933B_43B78662A7C1__INCLUDED_)
#define AFX_YREALTIMER_H__F54731A9_1507_4E22_933B_43B78662A7C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "YTime.h"
#include "YPos.h"

class YRealTimer  
{
protected: //members
  int           m_nMode;
  YTimeSpan     m_tsBase;
  BOOL          m_bResetNeeded;

  YTime         m_tStart;
  YPos          m_qPrevPos;
protected: //cached
  YTimeSpan     m_tsDeltaTime;
  YPos          m_qDeltaPos;

public:   //construction/destruction
  enum        { modeBaseLong=0, modeBaseEveryTime=1, modeTimeSpan=2 };
  enum        { modeSpanInfinite=0, modeSpanMomentary=1, modeSpan=2 };
                YRealTimer();
                ~YRealTimer();
  int           Init(int nMode=0,YTimeSpan tsBase=0);//nMode = 0 - BaseLong,1- BaseEveryTime, 2-Base TimeSpan
  void          Reset();
  int           Update(YTime tTime, YPos qPos);
public:   //attributes
  YPos          GetDeltaPos() const;
  YTimeSpan     GetDeltaTime() const;
  YTime         GetStartTime() const;
};

#endif // !defined(AFX_YREALTIMER_H__F54731A9_1507_4E22_933B_43B78662A7C1__INCLUDED_)
