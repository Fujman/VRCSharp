#define C_STRUCT_CLEAR(STRUCT) \
  memset(&(STRUCT),0,sizeof(STRUCT))

#define C_CLASS_CLEAR(THIS,PARENT) \
  memset(((BYTE*)(THIS))+sizeof(PARENT),0,sizeof(*(THIS))-sizeof(PARENT))

#define C_STRUCT_EQ(S1,S2) \
  (0==memcmp(&(S1),&(S2),sizeof(S1)))

#define C_STRUCT_NE(S1,S2) \
  (0!=memcmp(&(S1),&(S2),sizeof(S1)))


