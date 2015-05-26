#ifndef __YHASPLIC_H
#define __YHASPLIC_H
#include "xCStringTable.h"
#include "LICENSE/VideoLicense.h"
#include "LICENSE/AudioLicense.h"
#include "LICENSE/ClientLicense.h"
#include "YArray.h"

typedef YStaticByteArray 
        YHaspLicense__LicData;

struct  YHaspLicense__License
{
  int              nHASP;
  TCHAR            serial[30];//5*5+(5-1)+1
  TCHAR            date[16];
  LICENSE__VIDEO   video;
  LICENSE__AUDIO   audio;
  LICENSE__CLIENT  client;
  TCHAR            label[128];
  GUID             blob;
  GUID             hasp;//serial as MD5
};

extern  YHaspLicense__LicData g_licdata;
extern  YHaspLicense__License g_license;

BOOL    YHaspLicence__Calc(LPCTSTR fzCSV, LPCTSTR fzMD5);
int     YHaspLicence__Make(LPCTSTR fzCSV, LPCTSTR fzLIC, BOOL bBlobs=FALSE, BOOL bNoClean=FALSE);
int     YHaspLicence__Save(LPCTSTR fzLIC, LPCTSTR fzCSV=NULL);

int     YHaspLicence__Data(YHaspLicense__LicData& data, LPCTSTR szFile=NULL, LPCTSTR szResource=NULL);//to g_license_data?
int     YHaspLicence__Load(CStringTable& table, void* p, int n, LPCTSTR szFile=NULL);
CString YHaspLicence__Find(YHaspLicense__License* pLic, CStringTable& table, CString* pszBLOB=NULL);

CString YHaspLicence__Hasp(YHaspLicense__License* plic, CStringTable& table);// rewrite

GUID    hasp2md5(int nHaspSerial, LPCTSTR szLabel, int nLength=-1);
CString hasp2serial(int nHaspSerial, LPCTSTR szLabel, int nLength=-1);

#endif//__YHASPLIC_H
#pragma once 