/*---------------------------------------------------------------------------\
|  xCFile.H                                    Last Change : 06.06.01 11:31  |
\---------------------------------------------------------------------------*/
#ifndef __XCFILE_H
#define __XCFILE_H

#ifdef  __XCFILE_CARCHIVE_OPERATORS
#define  __XCFILE_CARCHIVE_OPERATOR_STRING_DEFINED
inline
CArchive& operator<<(CArchive& ar, LPCTSTR sz)
{
  ar.WriteString(sz);
  return ar;
}
#endif

#endif//__XCFILE_H
#pragma once
