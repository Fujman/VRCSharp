#ifndef __YHASPPCS_H
#define __YHASPPCS_H
#include "xpragma.h"

#ifdef  YHASP_PCS_MANUAL
#ifndef YHASP_USE_HASP_PCS
#define YHASP_USE_HASP_PCS
#endif
#endif

#pragma pack(push,1)
struct HASP_PCS {
  char          Signature[10+1]       ;// 10 characters   $HASP$PCS$
//char          LastStatus            ;//  1 byte          NetHASP LastStatus
  char          ProgramNumber         ;//  1 byte          NetHASP Program Number
  int           Service               ;//  integer         hasp() service
  int           SeedCode              ;//  integer         Seed Code
  int           Input1                ;//  integer         1st parameter to hasp()
  int           Input2                ;//  integer         2nd parameter to hasp()
  int           Input3                ;//  integer         3rd parameter to hasp()
  int           Input4                ;//  integer         4th parameter to hasp()
  int           Return1               ;//  integer         1st return parameter
  int           Return2               ;//  integer         2nd return parameter
  int           Return3               ;//  integer         3rd return parameter
  int           Return4               ;//  integer         4th return parameter
};
#pragma pack(pop)

#define HASP_PCS_SIGNATURE "$HASP$PCS$"

class YHaspPCS //Pattern Code System
{
  public: static BOOL CheckInstalled(BOOL bException=FALSE);
};

#if defined(YHASP_USE_HASP_PCS) && !defined(YHASP_PCS_MANUAL)
static HASP_PCS hasp_pcs = { {HASP_PCS_SIGNATURE} };
#pragma message(__FILE__LINE__ " : notify : HASP PCS invoked")
#endif

#endif//__YHASPPCS_H