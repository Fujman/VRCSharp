#ifndef __CFIXED_H
#define __CFIXED_H

#include <math.h>
//Custom float point value, stored in integer 
//Format:                S-SIGN
//   1111110000000000    s-EXP SIGN
//   5432109876543210    E-EXP     
//   SsEEEEMMMMMMMMMM    M-MANTISSE
//
//
template<class TYPE, int DIGITS, int BASE>
class CFixed {
public://construction
                        CFixed() {/* non-initialized*/};
                        CFixed(const CFixed&);
                        CFixed(__int64);
  CFixed&               operator =(const CFixed&);
  CFixed&               operator =(__int64);
                        operator __int64() const;
  CFixed                operator -() const;
public://methods
  TYPE                  GetRawData() const;
  void                  SetRawData(TYPE);
  BOOL                  IsNegative() const;
protected:
  static TYPE           CalcMantisse(__int64 arg); 
  static TYPE           CalcExp(__int64 arg);
  TYPE                  m_value;
public://constants
  static int            MANT_BITS;// = (log10(pow(BASE,DIGITS))/log10(2) + (((int)(log(BASE)/log(2)))==log(BASE)/log(2)?0:1));
  static int            EXP_BITS ;// = (sizeof(TYPE)-2-MANT_BITS);
  static TYPE           SIGN_MASK;// = ((TYPE)1)<<(sizeof(TYPE)*8-1);
  static TYPE           ESGN_MASK;// = ((TYPE)1)<<(sizeof(TYPE)*8-2);
  static TYPE           EXP_MASK ;// = (~((~(TYPE)0)<<EXP_BITS));
  static TYPE           MANT_MASK;// = (~((~(TYPE)0)<<MANT_BITS));
  static TYPE           MANT_MAX ;// = (TYPE)pow(2,MANT_BITS);
  static TYPE           BASESHIFT;// = (TYPE)(log10((double)MANT_MAX)/log10((double)BASE));
  static TYPE           BASE_MULT;// = (TYPE)pow((double)BASE,(double)BASESHIFT);
protected:
  static BOOL           m_bInited;
  static BOOL           InitConsts();
};

#define CFIXED          CFixed<TYPE,DIGITS,BASE>
                        template<class TYPE, int DIGITS, int BASE>
int  CFIXED::MANT_BITS;// =(int)(log10(pow(BASE,DIGITS))/log10(2) + (((int)(log(BASE)/log(2)))==log(BASE)/log(2)?0:1));
                        template<class TYPE, int DIGITS, int BASE>
int  CFIXED::EXP_BITS ;// =(sizeof(TYPE)*8-2-CFIXED::MANT_BITS);
                        template<class TYPE, int DIGITS, int BASE>
TYPE CFIXED::SIGN_MASK;// =((TYPE)1)<<(sizeof(TYPE)*8-1);
                        template<class TYPE, int DIGITS, int BASE>
TYPE CFIXED::ESGN_MASK;// =((TYPE)1)<<(sizeof(TYPE)*8-2);
                        template<class TYPE, int DIGITS, int BASE>
TYPE CFIXED::EXP_MASK ;// =(~((~(TYPE)0)<<CFIXED::EXP_BITS));
                        template<class TYPE, int DIGITS, int BASE>
TYPE CFIXED::MANT_MASK;// =(~((~(TYPE)0)<<CFIXED::MANT_BITS));
                        template<class TYPE, int DIGITS, int BASE>
TYPE CFIXED::MANT_MAX ;// =(TYPE)pow(2,CFIXED::MANT_BITS);
                        template<class TYPE, int DIGITS, int BASE>
TYPE CFIXED::BASESHIFT;// =(TYPE)(log10((double)CFIXED::MANT_MAX)/log10((double)BASE));
                        template<class TYPE, int DIGITS, int BASE>
TYPE CFIXED::BASE_MULT;// =(TYPE)pow((double)BASE,(double)CFIXED::BASESHIFT);
                        template<class TYPE, int DIGITS, int BASE>
BOOL CFIXED::m_bInited = CFIXED::InitConsts();

template<class TYPE, int DIGITS, int BASE>
BOOL CFIXED::InitConsts()
{
  CFIXED::MANT_BITS =(int)(log10(pow(double(BASE),DIGITS))/log10(2.0) + 
    (((int)(log(double(BASE))/log(2.0)))==log(double(BASE))/log(2.0)?0:1));//AY 11.01.2010 OLD: pow(BASE,DIGITS)
  CFIXED::EXP_BITS  =(sizeof(TYPE)*8-2-CFIXED::MANT_BITS);
  CFIXED::SIGN_MASK =((TYPE)1)<<(sizeof(TYPE)*8-1);
  CFIXED::ESGN_MASK =((TYPE)1)<<(sizeof(TYPE)*8-2);
  CFIXED::EXP_MASK  =(~((~(TYPE)0)<<CFIXED::EXP_BITS));
  CFIXED::MANT_MASK =(~((~(TYPE)0)<<CFIXED::MANT_BITS));
  CFIXED::MANT_MAX  =(TYPE)pow(2.0,CFIXED::MANT_BITS);
  CFIXED::BASESHIFT =(TYPE)(log10((double)CFIXED::MANT_MAX)/log10((double)BASE)-1);
  CFIXED::BASE_MULT =(TYPE)(pow((double)BASE,(double)CFIXED::BASESHIFT));
  return TRUE;
}

template<class TYPE, int DIGITS, int BASE> inline
TYPE CFIXED::CalcMantisse(__int64 arg)
{
  double dDenom = pow((double)BASE,(double)CalcExp(arg));
  //TRACE("MANTISSE=%lf   ",((double)arg)/pow((double)BASE,(double)CalcExp(arg)));
  //TRACE("EXP=%lf  ",log10((double)arg));
  return (TYPE)((((double)arg)*BASE_MULT)/dDenom);
}

template<class TYPE, int DIGITS, int BASE> inline
TYPE CFIXED::CalcExp(__int64 arg) {
  double dPow = log10((double)arg);
  if(BASE!=10)
    dPow /= log10((double)BASE);
  return (TYPE)dPow;
}

template<class TYPE, int DIGITS, int BASE> inline
TYPE CFIXED::GetRawData() const
{
  return m_value;
}
template<class TYPE, int DIGITS, int BASE> inline
void CFIXED::SetRawData(TYPE f)
{
  m_value = f;
}

template<class TYPE, int DIGITS, int BASE> inline
BOOL CFIXED::IsNegative() const
{
  return (m_value & SIGN_MASK)!=0;
}

template<class TYPE, int DIGITS, int BASE> inline
CFIXED CFIXED::operator -() const
{
  CFixed value; value.m_value = m_value;
  if(value.m_value & SIGN_MASK)
    value.m_value &= ~SIGN_MASK;
  else
    value.m_value |= SIGN_MASK;
  return value;
}

template<class TYPE, int DIGITS, int BASE> inline
CFIXED::CFixed(const CFixed& f)
{
  if(m_bInited)
    operator =(f);
}

template<class TYPE, int DIGITS, int BASE> inline
CFIXED::CFixed(__int64 i64)
{
  if(m_bInited)
    operator =(i64);
}

template<class TYPE, int DIGITS, int BASE> inline
CFIXED& CFIXED::operator =(const CFixed& f)
{
  m_value = f.m_value;
  return *this;
}

template<class TYPE, int DIGITS, int BASE>
CFIXED& CFIXED::operator =(__int64 arg)
{
  if(arg==0)
    { m_value = 0; return *this; }
  if(arg<0) 
    { *this = -CFixed(-arg); return *this; }

  TYPE   mantisse = CalcMantisse(arg);
  TYPE   exp      = CalcExp(arg);
  //TRACE("IMANTISSE=%d   ",(int)mantisse);
  //TRACE("IEXP=%d  ",(int)exp);

  m_value = mantisse;
  if(exp>=0) {
    m_value |= exp<<MANT_BITS;
  }else{
    m_value |= (-exp)<<MANT_BITS;
    m_value |= ESGN_MASK;
  }
  return *this;
}

template<class TYPE, int DIGITS, int BASE> 
CFIXED::operator __int64() const
{
  if(m_value==0)
    { return 0; }
  if(IsNegative()) 
    { return -((__int64) -CFixed(*this)); }

  TYPE   mantisse = m_value & MANT_MASK;
  TYPE   exp      = (m_value>>MANT_BITS) & EXP_MASK;

  return (__int64)((((double)mantisse)/BASE_MULT)*pow(double(BASE),exp));//AY 11.01.2011 OLD: ...pow(double(BASE),exp)
}

#undef CFIXED

#endif//__CFIXED_H
#pragma once
