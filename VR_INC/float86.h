#ifndef __FLOAT86_H
#define __FLOAT86_H

#define FLOAT86_NEG_INFINITE (YFloat86(0x0ff800000).m_f) // -1.#INF0E+000f

union YFloat86
{
  YFloat86(int i)
    { m_i = i; }
  float   m_f;
  __int32 m_i;
};

#endif//__FLOAT86_H
#pragma once
