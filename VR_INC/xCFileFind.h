#ifndef __XCFILEFIND_H
#define __XCFILEFIND_H
#include <afxinet.h>

class CFileFindEx : public CFileFind
{
  public: operator const WIN32_FIND_DATA*() const
    { return (WIN32_FIND_DATA*)m_pNextInfo; }
};

class CFtpFileFindEx : public CFtpFileFind
{
  public: operator const WIN32_FIND_DATA*() const
    { return (WIN32_FIND_DATA*)m_pNextInfo; }
};

/////////////////////////////////////////////
// Using:
// CFileFind ff;           CFtpFileFind ftpff;
// ff.FindFile("*.*");     ftpff.FindFile("*.*");
// const WIN32_FIND_DATA* pfd = *((CFileFindEx*)(&ff));
// const WIN32_FIND_DATA* pftpfd = *((CFtpFileFindEx*)&ftpff);


#endif