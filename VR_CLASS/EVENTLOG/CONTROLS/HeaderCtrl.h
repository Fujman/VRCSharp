#ifndef __HEADERCTRL_H
#define __HEADERCTRL_H
class CHeaderCtrlEx : public CHeaderCtrl {
// Construction
public:
  CHeaderCtrlEx();

// Attributes
public:

// Operations
public:

protected:
  int   m_iSortColumn;
  BOOL  m_bSortAscending;

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CHeaderCtrlEx)
  //}}AFX_VIRTUAL

// Implementation
public:
  void    SetSortArrow( const int iColumn, const BOOL bAscending );
  virtual ~CHeaderCtrlEx();

  // Generated message map functions
protected:
  //{{AFX_MSG(CHeaderCtrlEx)
    // NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};
#endif //__HEADERCTRL_H
