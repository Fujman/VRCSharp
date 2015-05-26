#ifndef __XCKEYBRD_H
#define __XCKEYBRD_H

class CKeyboard
{
  public:
    static void SetNumLock( BOOL bState );
    static void PressNumKey( BYTE byVK );
};

#endif//__XCKEYBRD_H
#pragma once