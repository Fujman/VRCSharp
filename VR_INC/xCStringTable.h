#ifndef __XCSTRINGTABLE_H
#define __XCSTRINGTABLE_H
#include "c_array.h"
#include "xunicod.h"
#include "xCStringArray.h"

/////////////////////////////////////////////////////////////////////
//
// CStringTable (CSV support)
//

class CStringTable : public CStringArray
{
public:
  enum          { MAX_COLUMNS = 64 };
  typedef LPCTSTR_COMPLEMENT LPCxSTR;
public:
  struct CCellPtr 
  {
    CCellPtr()  { m_pTable=NULL; m_iRow=m_iCol=-1; }
    CStringTable* m_pTable;  int m_iRow,m_iCol;
  };

public:// Cell(iRow,iCol) = CString() and table(iRow,iCol) implementation
  struct CCell: public CCellPtr 
  { CCell(CStringTable* pTable, int iRow, int iCol)     { m_pTable=pTable; m_iRow=iRow; m_iCol=iCol; }
  /*CString*/     operator CString() const              { return m_pTable->GetCell(m_iRow,m_iCol); }
    CCell&        operator=(const CString& s)           { m_pTable->SetCell(m_iRow,m_iCol,s); return *this; }
    CCell&        operator=(const CCell& cell)          { m_pTable->SetCell(m_iRow,m_iCol,CString(cell)); return *this; }
  };
    CCell         operator()(int iRow, int iCol)        { return Cell(iRow,iCol); }
    CCell         operator()(LPCTSTR szCol, int iRow)   { return Cell(iRow,Column(szCol)); }
    CCell         operator()(LPCxSTR szCol, int iRow)   { return Cell(iRow,Column(szCol)); }

public:// operator[iRow][iCol] implementation
  struct CRow: public CCellPtr 
  {               CRow(CStringTable* pTable, int iRow)  { m_pTable=pTable; m_iRow=iRow; }
    CCell         operator[](int iCol)                  { return m_pTable->Cell(m_iRow,iCol); }
  };
    CRow          operator[](int iRow)                  { return CRow(this,iRow); }

public:// operator["Column"][iRow] implementation
  struct CCol: public CCellPtr 
  {               CCol(CStringTable* pTable, int iCol)  { m_pTable=pTable; m_iCol=iCol; }
    CCell         operator[](int iRow)                  { return m_pTable->Cell(iRow,m_iCol); }
  };
    CCol          operator[](LPCTSTR sCol)              { return CCol(this,Column(sCol)); }
    CCol          operator[](LPCxSTR sCol)              { return CCol(this,Column(sCol)); }

public:
   enum         { modeNOSPACES = 1 };

                CStringTable(const CStringArray& asText, int mode=0)
                  { construct(); Create(asText,mode); }
                CStringTable()
                  { construct(); }

  int           Create(const CStringArray& sText, int mode=0);
  int           Parse(int mode=0);
  int           Scan();

  CCell         Cell(int iRow, int iCol);

public:
  int           GetCols() const { return m_nColumns; }
  int           GetRows() const { return GetSize(); }

  CString       GetCell(int iRow, int iCol) const;
  void          SetCell(int iRow, int iCol, const CString& szValue);

  int           Column(LPCTSTR szHeader) const;
  int           Column(LPCxSTR szHeader) const;
  CString       Header(int iCol) const;

  CString       String(int iRow) const;
  CString&      String(int iRow);

public://debug helpers
  void          Dump(int nLines=0);
protected:
  TCHAR         m_cDelimiter;
  int           m_nColumns;
  int           m_anWidths[MAX_COLUMNS];
private:
  void          construct()
                  { m_cDelimiter=';'; m_nColumns=0; C_ARRAY_CLEAR(m_anWidths); }
};


#if 0
// creating /////////////////////////////////////////////

inline int CStringTable::Create(const CStringArray& asText, int mode)
{
  CStringArray::Copy(asText);
  int iMod = 0;
  for(int i=GetSize()-1; i>=0; --i){
    CString& sz = String(i);
    int nLen1 = sz.GetLength();
    sz.TrimRight(_T("\r\n\f\x1A"));//CR,LF,FF,EOF
    int nLen2 = sz.GetLength();
    if(nLen2==0)
      { RemoveAt(i); iMod++; }
    else if(nLen2!=nLen1)
      {/*SetAt(i,sz);*/ iMod++; }
  }
  Parse(mode);
  return 0;
}

inline int CStringTable::Parse(int mode)
{
  TCHAR szDelimiters[2] = { m_cDelimiter };
  BOOL  bNoSpaces = (mode&modeNOSPACES)!=0;
  int   nColumns = 0;
  int   iRow = 0;
  int   iCol = 0;
  CString szClean;
  for(iRow=0; iRow<GetSize(); ++iRow) {
    CString& sz = String(iRow);
    int nStart = bNoSpaces?0:nColumns;//skip defined
    for(iCol=nStart; 1; ++iCol) {
      size_t nAns  = 0;
      LPTSTR szAns = xstrnsub(iCol,(LPCTSTR)sz,sz.GetLength(),&nAns,szDelimiters);
      if(szAns==NULL || *szAns=='\0')
        break;
      if(nColumns<iCol)
        nColumns = iCol;
      if(bNoSpaces && nAns>0) {
        szClean = CString(szAns,nAns-1);
        int nLen1 = szClean.GetLength();
        szClean.TrimLeft(_T(" \t"));
        szClean.TrimRight(_T(" \t"));
        int nLen2 = szClean.GetLength();
        if(nLen1!=nLen2){
          int iPos = szAns - sz;
          ASSERT(iPos>=0);
          sz.Delete(iPos, nAns-1);
          sz.Insert(iPos, szClean);
        }
      }
    }
  }
  m_nColumns = 0;
  if(GetSize()==0)
    return -1;

  nColumns = nColumns + 1;//AY 11.11.2011?
  ASSERT(nColumns<=MAX_COLUMNS);
  m_nColumns = nColumns<=MAX_COLUMNS?nColumns:MAX_COLUMNS;

  Scan();
  return 0;
}

inline int CStringTable::Scan()
{
  int  nWidths = m_nColumns; 
  int* aWidths = m_anWidths;
  ASSERT(nWidths>0 && aWidths!=NULL);
  memset(aWidths,0,nWidths);
  int iRow = 0;
  int iCol = 0;
  for(iRow=0; iRow<GetRows(); ++iRow) {
    for(iCol=0; iCol<GetCols(); ++iCol) {
      CString sz = (*this)[iRow][iCol];
      if(iCol<nWidths){
        if(aWidths[iCol]<sz.GetLength())
          aWidths[iCol] = sz.GetLength();
      }
    }
  }
  return 0;
}

inline trace_long_string(LPCTSTR a_sz)
{
  CString sz = a_sz;
  LPTSTR  s  = sz.GetBuffer(sz.GetLength()+1);
  for(int i=0; i<sz.GetLength(); i+=256){
    if(i+256<sz.GetLength()){
      TCHAR c = s[i+256];
      s[i+256] = '\0';
      TRACE(_T("%s"),s+i);
      s[i+256] = c;
    }else{
      TRACE(_T("%s"),s+i);
    }
  }
  sz.ReleaseBuffer(0);
}

inline void CStringTable::Dump(int nLines)
{
  int  nWidths = m_nColumns; 
  int* aWidths = m_anWidths;
  int iRow = 0;
  int iCol = 0;

  int nRows = GetRows();
  int nCols = GetCols();
  if(nLines!=0)
    nRows = min(nLines,nRows);

  if(nRows==0) {
    TRACE(_T("\n"));
    for(iCol=0; iCol<GetCols(); ++iCol) {
      CString szCol = Header(iCol);
      CString sz = (*this)[szCol][iRow];
      int nWidth = 0;
      if(iCol<nWidths && aWidths!=NULL)
        nWidth = aWidths[iCol];
      TRACE(_T("%16s: %d\n"), szCol, nWidth);
    }
  }
  TRACE(_T("\n"));
  for(iRow=0; iRow<nRows; ++iRow) {
    for(iCol=0; iCol<nCols; ++iCol) {
      CString sz = (*this)[iRow][iCol];
      LPCTSTR s = sz;//debug
      int nWidth = 16;
      if(iCol<nWidths && aWidths!=NULL)
        nWidth = aWidths[iCol] + 1;
      //TRACE(_T("%s"),sz); 
      trace_long_string(sz);
      if(nWidth>sz.GetLength() && iCol+1<nCols)
        //TRACE(_T("%s"),CString(' ',nWidth-sz.GetLength()));
        trace_long_string(CString(' ',nWidth-sz.GetLength()));
    }
    TRACE(_T("\n"));
  }
  TRACE(_T("\n"));
}

// operations /////////////////////////////////////////////

inline void CStringTable::SetCell(int iRow, int iCol, const CString& s)
{
  ASSERT(iRow>=0 && iCol>=0); ASSERT(iCol<m_nColumns);
  if(iRow<0 || iCol<0)
    return;
  TCHAR szDelimiters[2] = { m_cDelimiter };
  CString& sz = String(iRow);
  size_t nAns  = 0;
  LPTSTR szAns = xstrnsub(iCol,(LPCTSTR)sz,sz.GetLength(),&nAns,szDelimiters);
  if(szAns==NULL || nAns==0)
    return;
  if(szAns[nAns-1]==m_cDelimiter)
    nAns = nAns-1;
  int iPos = szAns - sz;
  ASSERT(iPos>=0);
  sz.Delete(iPos, nAns);
  sz.Insert(iPos, s);
}


inline CString CStringTable::GetCell(int iRow, int iCol) const
{
  ASSERT(iRow>=0 && iCol>=0); ASSERT(iCol<m_nColumns);
  if(iRow<0 || iCol<0)
    return CString();
  TCHAR szDelimiters[2] = { m_cDelimiter };
  const CString sz = String(iRow);
  size_t nAns  = 0;
  LPTSTR szAns = xstrnsub(iCol,(LPCTSTR)sz,sz.GetLength(),&nAns,szDelimiters);
  if(szAns==NULL || nAns<=0)
    return CString();
  if(szAns[nAns-1]==m_cDelimiter)
    nAns = nAns-1;
  CString szRet(szAns,nAns);
  szRet.TrimRight(szDelimiters);
  return szRet;
}

inline CString CStringTable::Header(int iCol) const
{
  CString szHeader = GetCell(0,iCol);
  szHeader.TrimLeft(_T(" "));
  szHeader.TrimRight(_T(" "));
  return szHeader;
}

inline int CStringTable::Column(LPCTSTR szColumn) const
{
  for(int iCol=0; iCol<m_nColumns; ++iCol){
    if(Header(iCol).CompareNoCase(szColumn)==0)
      return iCol;
  }
  return -1;
}
inline int CStringTable::Column(LPCxSTR xzColumn) const
{
  CString szColumn(xzColumn);
  for(int iCol=0; iCol<m_nColumns; ++iCol){
    if(Header(iCol).CompareNoCase(szColumn)==0)
      return iCol;
  }
  return -1;
}
#endif

inline CString  CStringTable::String(int iRow) const
{
  return GetAt(iRow);
}
inline CString& CStringTable::String(int iRow)
{
  return ElementAt(iRow);
}

inline CStringTable::CCell CStringTable::Cell(int iRow, int iCol)
{
  return CCell(this, iRow, iCol);
}

#endif//__XCSTRINGTABLE_H
#pragma once
