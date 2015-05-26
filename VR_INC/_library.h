#if !defined(_DEBUG) && !(defined(UNICODE) || defined(_UNICODE)) //Release
  #define LIB_SUFFIX ""
#endif//Release
#if  defined(_DEBUG) && !(defined(UNICODE) || defined(_UNICODE)) //Debug
  #define LIB_SUFFIX "D"
  #pragma comment(linker, "/nodefaultlib:libcmtd")
#endif//Debug
#if !defined(_DEBUG) &&  (defined(UNICODE) || defined(_UNICODE)) //Unicode Release
  #define LIB_SUFFIX "U"
#endif//Unicode Release
#if  defined(_DEBUG) &&  (defined(UNICODE) || defined(_UNICODE)) //Unicode Debug
  #define LIB_SUFFIX "UD"
  #pragma comment(linker, "/nodefaultlib:libcmtd")
#endif//Unicode Debug

#ifdef VS2010_VERSION
  #define LIB_IS64  "64"
  #define LIB_IS64_ "_64"
#else// VS 6.0
  #define LIB_IS64  ""
  #define LIB_IS64_ ""
#endif

#pragma comment(lib,         "fs" LIB_IS64 LIB_SUFFIX ".lib")
#pragma comment(lib,         "dx" LIB_IS64 LIB_SUFFIX ".lib")
#pragma comment(lib,    "streams" LIB_IS64 LIB_SUFFIX ".lib")
#pragma comment(lib,    "devices" LIB_IS64 LIB_SUFFIX ".lib")
#pragma comment(lib,    "records" LIB_IS64 LIB_SUFFIX ".lib")
#pragma comment(lib,    "clients" LIB_IS64 LIB_SUFFIX ".lib")
#pragma comment(lib,    "SRSBase" LIB_IS64 LIB_SUFFIX ".lib")
#pragma comment(lib,   "eventlog" LIB_IS64 LIB_SUFFIX ".lib")
#pragma comment(lib,   "textedit" LIB_IS64 LIB_SUFFIX ".lib")
#pragma comment(lib,   "controls" LIB_IS64 LIB_SUFFIX ".lib")
#pragma comment(lib,   "wavealgo" LIB_IS64 LIB_SUFFIX ".lib")
#pragma comment(lib,   "settings" LIB_IS64 LIB_SUFFIX ".lib")
//ragma comment(lib,       "xvid" LIB_IS64 LIB_SUFFIX ".lib")
#pragma comment(lib,       "zlib" LIB_IS64 LIB_SUFFIX ".lib")
#pragma comment(lib,       "fftw" LIB_IS64 LIB_SUFFIX ".lib")
#pragma comment(lib,       "jpeg" LIB_IS64 LIB_SUFFIX ".lib")
#pragma comment(lib,      "ydsp" LIB_IS64_ LIB_SUFFIX ".lib")

#pragma comment(lib,  "vclibrary" LIB_IS64 LIB_SUFFIX ".lib")

//system libs
#pragma comment(lib, "winmm.lib"   )
#pragma comment(lib, "msacm32.lib" )
#pragma comment(lib, "dsound.lib"  )
#pragma comment(lib, "version.lib" )
#pragma comment(lib, "shell32"     )
#pragma comment(lib, "strmiids.lib")

#undef LIB_IS64_
#undef LIB_IS64
#undef LIB_SUFFIX
