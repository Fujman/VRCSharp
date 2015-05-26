#ifndef __YTIMEOLE_H
#define __YTIMEOLE_H
#include "YTime.h"

class CComDateTime: protected COleDateTime
{
public:
  static BOOL OleDateFromTm(WORD wYear, WORD wMonth, WORD wDay,
	  WORD wHour, WORD wMinute, WORD wSecond, DATE& dtDest)
  {
    static const int MonthDays[13] =
	    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

	  // Validate year and month (ignore day of week and milliseconds)
	  if (wYear > 9999 || wMonth < 1 || wMonth > 12)
		  return FALSE;

	  //  Check for leap year and set the number of days in the month
	  BOOL bLeapYear = ((wYear & 3) == 0) &&
		  ((wYear % 100) != 0 || (wYear % 400) == 0);

	  int nDaysInMonth =
		  MonthDays[wMonth] - MonthDays[wMonth-1] +
		  ((bLeapYear && wDay == 29 && wMonth == 2) ? 1 : 0);

	  // Finish validating the date
	  if (wDay < 1 || wDay > nDaysInMonth ||
		  wHour > 23 || wMinute > 59 ||
		  wSecond > 59)
	  {
		  return FALSE;
	  }

	  // Cache the date in days and time in fractional days
	  long nDate;
	  double dblTime;

	  //It is a valid date; make Jan 1, 1AD be 1
	  nDate = wYear*365L + wYear/4 - wYear/100 + wYear/400 +
		  MonthDays[wMonth-1] + wDay;

	  //  If leap year and it's before March, subtract 1:
	  if (wMonth <= 2 && bLeapYear)
		  --nDate;

	  //  Offset so that 12/30/1899 is 0
	  nDate -= 693959L;

	  dblTime = (((long)wHour * 3600L) +  // hrs in seconds
		  ((long)wMinute * 60L) +  // mins in seconds
		  ((long)wSecond)) / 86400.;

	  dtDest = (double) nDate + ((nDate >= 0) ? dblTime : -dblTime);

	  return TRUE;
  }

  CComDateTime(DATE t)
    :COleDateTime(t) 
  {
  }

  CComDateTime(YTIME t)
  {
	  // Assume UTC FILETIME, so convert to LOCALTIME
	  FILETIME filetimeLocal; YTime(t).GetAsFileTime(filetimeLocal);
	  if(YTime(t).IsBad())
	  {
  #ifdef _DEBUG
		  DWORD dwError = GetLastError();
		  TRACE1("\nFileTimeToLocalFileTime failed. Error = %lu.\n\t", dwError);
  #endif // _DEBUG
		  m_status = invalid;
	  }
	  else
	  {
		  // Take advantage of SYSTEMTIME -> FILETIME conversion
		  SYSTEMTIME systime;
		  m_status = FileTimeToSystemTime(&filetimeLocal, &systime) ?
			  valid : invalid;

		  // At this point systime should always be valid, but...
		  if (GetStatus() == valid)
		  {
			  m_status = OleDateFromTm(systime.wYear, systime.wMonth,
				  systime.wDay, systime.wHour, systime.wMinute,
				  systime.wSecond, m_dt) ? valid : invalid;
		  }
	  }

	  //return *this;
  }


  operator YTime() const
  {
    int nMsec = 0; ASSERT(nMsec>=0 && nMsec<1000);
    if(GetStatus()!=COleDateTime::DateTimeStatus::valid)
      return YTime();//invalid
    SYSTEMTIME st; FILETIME ft;
    BOOL bRet = GetAsSystemTime(st);
    st.wMilliseconds += nMsec;
    if(bRet)
      bRet = ::SystemTimeToFileTime(&st,&ft);
    if(!bRet)
      return YTime();//invalid
    else
      return ft;
  }

  operator DATE() const
  {
    return COleDateTime::operator DATE();
  }

};


#endif//__YTIMEOLE_H
#pragma once