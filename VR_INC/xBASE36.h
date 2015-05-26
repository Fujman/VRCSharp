#include "xGUID.h"

inline CString md5_to_base36(const GUID& guid)
{
  return md52serial(guid);
}

inline GUID base36_to_md5(LPCTSTR szSerial)
{
  return serial2md5(szSerial);
}
