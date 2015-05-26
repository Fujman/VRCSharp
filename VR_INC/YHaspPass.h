#undef HASP_COMPILE_MESSAGE
#undef HASP_PASS1
#undef HASP_PASS2
#include "xpragma.h"

#ifdef  YHASP_FORCE_DEMO
#pragma message(__FILE__LINE__ " : notify : HASP DEMO forced")
#include "haspdemo.h"
#else
#include "hasppass.h" // see j:\vr\key\hasppass.h: add from menu Options include directory j:\vr\key
#endif

#if !defined(HASP_PASS1) || !defined(HASP_PASS2)
#pragma message(__FILE__LINE__ " : notify : HASP DEMO by default")
#define HASP_COMPILE_MESSAGE "DEMO HASP"
#define HASP_PASS1 15417 //demo hasp
#define HASP_PASS2  9632 //demo hasp
#define HASP_VENDOR_CODE "AzIceaqfA1hX5wS+M8cGnYh5ceevUnOZIzJBbXFD6dgf3tBkb9cvUF/Tkd/iKu2fsg9wAysYKw7RMAsVvIp4KcXle/v1RaXrLVnNBJ2H2DmrbUMOZbQUFXe698qmJsqNpLXRA367xpZ54i8kC5DTXwDhfxWTOZrBrh5sRKHcoVLumztIQjgWh37AzmSd1bLOfUGI0xjAL9zJWO3fRaeB0NS2KlmoKaVT5Y04zZEc06waU2r6AU2Dc4uipJqJmObqKM+tfNKAS0rZr5IudRiC7pUwnmtaHRe5fgSI8M7yvypvm+13Wm4Gwd4VnYiZvSxf8ImN3ZOG9wEzfyMIlH2+rKPUVHI+igsqla0Wd9m7ZUR9vFotj1uYV0OzG7hX0+huN2E/IdgLDjbiapj1e2fKHrMmGFaIvI6xzzJIQJF9GiRZ7+0jNFLKSyzX/K3JAyFrIPObfwM+y+zAgE1sWcZ1YnuBhICyRHBhaJDKIZL8MywrEfB2yF+R3k9wFG1oN48gSLyfrfEKuB/qgNp+BeTruWUk0AwRE9XVMUuRbjpxa4YA67SKunFEgFGgUfHBeHJTivvUl0u4Dki1UKAT973P+nXy2O0u239If/kRpNUVhMg8kpk7s8i6Arp7l/705/bLCx4kN5hHHSXIqkiG9tHdeNV8VYo5+72hgaCx3/uVoVLmtvxbOIvo120uTJbuLVTvT8KtsOlb3DxwUrwLzaEMoAQAFk6Q9bNipHxfkRQER4kR7IYTMzSoW5mxh3H9O8Ge5BqVeYMEW36q9wnOYfxOLNw6yQMf8f9sJN4KhZty02xm707S7VEfJJ1KNq7b5pP/3RjE0IKtB2gE6vAPRvRLzEohu0m7q1aUp8wAvSiqjZy7FLaTtLEApXYvLvz6PEJdj4TegCZugj7c8bIOEqLXmloZ6EgVnjQ7/ttys7VFITB3mazzFiyQuKf4J6+b/a/Y"
#endif

#if defined(YHASP_FORCE_NO_DEMO) && HASP_PASS1==15417 && HASP_PASS2==9632
#pragma message(__FILE__LINE__ " : notify : HASP DEMO disabled")
#define HASP_PASS1 0
#define HASP_PASS2 0
#define HASP_VENDOR_CODE ""
#endif

#ifndef HASP_COMPILE_MESSAGE_SHOWED
#define HASP_COMPILE_MESSAGE_SHOWED

#pragma message(__FILE__LINE__ " : notify : " HASP_COMPILE_MESSAGE " implemented")

#endif//HASP_COMPILE_MESSAGE_SHOWED
