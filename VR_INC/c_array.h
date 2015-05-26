#define C_ARRAY_STATIC_COPY(s,t)  memcpy((s),(t),sizeof((s)))

#define C_ARRAY_COPY(s,t,n)  memcpy((s),(t),(n)*sizeof(*(s)))

#define C_ARRAY_CLEAR(s) memset(s,0,sizeof(s))
#define C_ARRAY_SIZE(s)  (sizeof(s)/sizeof(*s))

#ifndef countof //MFC ANALOG
#define countof(array) (sizeof(array)/sizeof(array[0]))
#endif

