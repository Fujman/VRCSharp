/*---------------------------------------------------------------------------\
|  FNAMES.H                                    Last Change : 16.06.00 13:07  |
\---------------------------------------------------------------------------*/

#ifndef __FNAMES_H
#define __FNAMES_H

  #define DOUBLE_BACKSLASH "\\\\"
  #define BACKSLASH        '\\'

#ifdef __cplusplus
extern "C" {
#endif
  char *fnamecpy(char *string, char *file, int length);
  int fnamecmp(char *file, char *pattern);
  char *fnamecpyfname(char *file, char *pattern);
  char *fnamecpyext(char *file, char *pattern);
  char *fnameexpand(char *file, char *fname, char *ext);
  char *fnamedelpath(char *file);
  char *fnamedelext(char *file);
  char *fnamedrive(char *file);
  char *fnamename(char *file);
  char *fnameext(char *file);
  char *fnameaddslash(char *file);
  int fnameisspecial(char *file);
#ifdef __cplusplus
}
#endif
#endif/*__FNAMES_H*/
