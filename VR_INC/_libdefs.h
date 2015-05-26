#if !defined(_DEBUG) && !(defined(UNICODE) || defined(_UNICODE)) //Release
  #define LIB_SUFFIX ""
#endif//Release
#if  defined(_DEBUG) && !(defined(UNICODE) || defined(_UNICODE)) //Debug
  #define LIB_SUFFIX "D"
  #define LIB_SUFFIX "_D"
  #pragma comment(linker, "/nodefaultlib:libcmtd")
#endif//Debug
#if !defined(_DEBUG) &&  (defined(UNICODE) || defined(_UNICODE)) //Unicode Release
  #define LIB_SUFFIX "U"
#endif//Unicode Release
#if  defined(_DEBUG) &&  (defined(UNICODE) || defined(_UNICODE)) //Unicode Debug
  #define LIB_SUFFIX "UD"
  #define LIB_SUFFIX_ "_D"
  #pragma comment(linker, "/nodefaultlib:libcmtd")
#endif//Unicode Debug

#ifdef VS2010_VERSION
  #define LIB_IS64  "64"
  #define LIB_IS64_ "_64"
#else// VS 6.0
  #define LIB_IS64  ""
  #define LIB_IS64_ ""
#endif

/*
Example:
#include "_libdefs.h"
#pragma comment(lib, "library" LIB_IS64 LIB_SUFFIX ".lib")
#undef LIB_IS64_
#undef LIB_IS64
#undef LIB_SUFFIX
#undef LIB_SUFFIX_
*/
