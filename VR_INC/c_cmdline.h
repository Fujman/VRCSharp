#ifndef __C_CMDLINE_H
#include <string.h>

inline char* c_GetArg(int nth, int argc, char *argv[], char* szDef=NULL)// nth=0,1,...
{
  for(int i=1, arg=0; i<argc; ++i)
    if( argv[i][0]!='/' )
      if(nth==arg++)
        return argv[i];
  return szDef;
}

inline char* c_GetKey(const char* szKey, int argc, char *argv[], char* szDef=NULL)
{
  for(int i=1; i<argc; ++i)
    if( stricmp(argv[i],szKey)==0 )
      return argv[i]+strlen(szKey);
  return szDef;
}

inline int   c_HasKey(const char* szKey, int argc, char *argv[])
{
  for(int i=1; i<argc; ++i)
    if( stricmp(argv[i],szKey)==0 )
      return 1;
  return 0;
}


#endif//__C_CMDLINE_H