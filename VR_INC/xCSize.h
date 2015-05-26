#ifndef __XCSIZE_H
#define __XCSIZE_H

inline BOOL operator == (const SIZE& s1, const SIZE& s2)
{
  return s1.cx==s2.cx && s1.cy==s2.cy;
}

inline BOOL operator != (const SIZE& s1, const SIZE& s2)
{
  return s1.cx!=s2.cx || s1.cy!=s2.cy;
}


#endif//__XCSIZE_H
#pragma once
