#ifndef __XCRECT_H
#define __XCRECT_H

inline CRect CRect__CenterByWidth(CRect& rc, const CRect& rcFrame)
{
  int xPos = (rcFrame.Width()-rc.Width())/2;
  rc += CPoint(xPos + rcFrame.left - rc.left, 0);
  return rc;
}

inline CRect CRect__CenterByHeight(CRect& rc, const CRect& rcFrame)
{
  int yPos = (rcFrame.Height()-rc.Height())/2;
  rc += CPoint(0, yPos + rcFrame.top - rc.top);
  return rc;
}

inline CRect CRect__Center(CRect& rc, const CRect& rcFrame)
{
  CRect__CenterByWidth(rc, rcFrame);
  CRect__CenterByHeight(rc, rcFrame);  
  return rc;
}

#endif//__XCRECT_H
#pragma once
