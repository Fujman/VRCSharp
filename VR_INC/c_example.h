//C and C++ inheritance example:

typedef struct tagYUserInfo //ui
{
  DWORD         dwMember0;
  DWORD         dwMember1;
}
YUserInfo;

//common inheritance

#ifndef __cplusplus //C inheritance
typedef union   tagYLineInfo {/*public YUserInfo*/ struct{
  DWORD         dwMember0;
  DWORD         dwMember1;
                             };struct{ YUserInfo UI;
#else   //C++ inheritance
typedef struct  tagYLineInfo  : public YUserInfo { struct{
#endif  //body
  DWORD         dwMember2;
  DWORD         dwMember3;
};} 
YLineInfo;

//fixed struct size inheritance


#ifndef __cplusplus //C inheritance
typedef union   tagYLineInfo {/*public YUserInfo*/ struct{
  DWORD         dwMember0;
  DWORD         dwMember1;
                             };struct{ YUserInfo UI;
#else   //C++ inheritance
typedef struct  tagYLineInfo  : public YUserInfo { struct{
#endif  //body
  union { BYTE  abLineInfo[128-sizeof(YUserInfo)]; struct{
  DWORD         dwMember2;
  DWORD         dwMember3;
};};};}
YLineInfo;
