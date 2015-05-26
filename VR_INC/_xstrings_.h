#ifndef ___XSTRINGS__H
#define ___XSTRINGS__H

// #include "/vr/vr_res/message/messages_.h"

/*
  Use in stdafx.h:

  #define  MULTILANGSTRINGS - strings only
  #define  MULTILANG        - strings and dialogs

  if enabled, enable dependence of FS library project
*/


#ifndef __MESSAGE_STRINGS_SUPPORT      //use #define ... 0 in stdafx.h to disable
#define __MESSAGE_STRINGS_SUPPORT    1
#endif

/*
  if enabled,  modify project.rc2:
  #include "/vr/vr_res/message/messages.rc"

  and enable dependence of SRSMessages project

  xCString.cpp must be included in the project directly
*/

#include "xCString.h"

#define  RS(id,ds) CString__MultilanguageResourceString(IDSX_##id,ds)
#define  RS_COMMAND_ID(id) ((IDSX_##id)&0xFFFF)
#define  RS_XSTRING_ID(id) ((IDSX_##id))

#endif//___XSTRINGS__H
