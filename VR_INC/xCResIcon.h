#ifndef __XCRESICON_H
#define __XCRESICON_H
#include "YResLoad.h"

//
// _xstrings_.h :
//
//#ifndef __MESSAGE_STRINGS_SUPPORT      //use #define ... 0 in stdafx.h to disable
//#define __MESSAGE_STRINGS_SUPPORT    1
//#endif
// #define  RS(id,ds) CString__MultilanguageResourceString(IDSX_##id,ds) -
//

//
//YResLoad.h:
//#ifdef  RESOURCES_NAMESPACE_DEFINED
//struct  YResourceNamespaceInitializator{ YResourceNamespaceInitializator() { YResourceLoader::SetResourcesNamespace((YLoadableResource*)g_resources_namespace);}};
//static  YResourceNamespaceInitializator s_resources_namespace_initializator;/*may be used __declspec(selectany)?*/
//#endif//RESOURCES_NAMESPACE_DEFINED
//

//
// xCResLoad.h:
//
// LoadMultilanguageResource(...)
// CString__MultilanguageResourceString(...)
// CString__MultilanguageResourceIcon(...)    //?
//


#ifndef __RESOURCE_ICONS_SUPPORT  //use #define ... 0 in stdafx.h to disable
#define __RESOURCE_ICONS_SUPPORT  1
#endif

//#define  RS(id,ds) CString__MultilanguageResourceString(IDSX_##id,ds)
//#define  RS_COMMAND_ID(id) ((IDSX_##id)&0xFFFF)


#endif//__XCRESICON_H
#pragma once
