#include "/vr/vr_res/message/messages_.h"

//
//  g_messages_namespace
//

#define LOAD_MESSAGE(IDS_STR,sz)  YResourceLoader::GetMessageHandle(#IDS_STR,(sz))
#define MESSAGE_ID(IDS_STR)       YResourceLoader::GetResourceID(#IDS_STR,RT_MESSAGETABLE)
