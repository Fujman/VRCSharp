#include "stdafx.h"
#include "HeaderCtrl.h"

static COLORREF  m_crCOLOR_BTNFACE       = ::GetSysColor(COLOR_BTNFACE);
static COLORREF  m_crCOLOR_HIGHLIGHTTEXT = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
static COLORREF  m_crCOLOR_HIGHLIGHT     = ::GetSysColor(COLOR_HIGHLIGHT);
static COLORREF  m_crCOLOR_BTNTEXT       = ::GetSysColor(COLOR_BTNTEXT);
static COLORREF  m_crCOLOR_WINDOW        = RGB(255,255,255);//::GetSysColor(COLOR_WINDOW);
static COLORREF  m_crCOLOR_3DFACE        = ::GetSysColor(COLOR_3DFACE);
static COLORREF  m_crCOLOR_3DHILIGHT     = ::GetSysColor(COLOR_3DHILIGHT);
static COLORREF  m_crCOLOR_3DSHADOW      = ::GetSysColor(COLOR_3DSHADOW);

#define FL_HEADER_SORTARROW   3

CHeaderCtrlEx::CHeaderCtrlEx() : m_iSortColumn( -1 ), m_bSortAscending( TRUE )
{}

CHeaderCtrlEx::~CHeaderCtrlEx()
{}

BEGIN_MESSAGE_MAP(CHeaderCtrlEx, CHeaderCtrl)
  //{{AFX_MSG_MAP(CHeaderCtrlEx)
    // NOTE - the ClassWizard will add and remove mapping macros here.
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CHeaderCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
  // attath to the device context.
  CDC dc;
  VERIFY( dc.Attach( lpDrawItemStruct->hDC ) );
  dc.SelectObject(GetStockObject(DEFAULT_GUI_FONT));
  // save the device context.
  const int iSavedDC = dc.SaveDC();

  // get the column rect.
  CRect rc( lpDrawItemStruct->rcItem );

  // set the clipping region to limit drawing within the column.
  CRgn rgn;
  VERIFY( rgn.CreateRectRgnIndirect( &rc ) );
  (void)dc.SelectObject( &rgn );
  VERIFY( rgn.DeleteObject() );

  // draw the background,
  CBrush brush( m_crCOLOR_3DFACE );
  //dc.FillRect( rc, &brush );
  ::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_ADJUSTRECT);

  // get the column text and format.
  TCHAR szText[ 64 ];
  HD_ITEM hditem;

  hditem.mask = HDI_TEXT|HDI_FORMAT;
  hditem.pszText = szText;
  hditem.cchTextMax = 63;

  VERIFY( GetItem( lpDrawItemStruct->itemID, &hditem ) );

  // determine the format for drawing the column label.
  UINT uFormat = DT_WORDBREAK | DT_WORD_ELLIPSIS;//DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER | DT_END_ELLIPSIS ;
  //DT_CENTER | 

  if( hditem.fmt & HDF_CENTER)
    uFormat |= DT_CENTER;
  else if( hditem.fmt & HDF_RIGHT)
    uFormat |= DT_RIGHT;
  else
    uFormat |= DT_LEFT;

  // adjust the rect if the mouse button is pressed on it.
  if( lpDrawItemStruct->itemState == ODS_SELECTED )
  {
    ++(rc.left);
    rc.top += 2;
    ++(rc.right);
  }

  CRect rcIcon( lpDrawItemStruct->rcItem );
  
  const int iOffset = FL_HEADER_SORTARROW;
  //int iOffset = dc.GetTextExtent(_T(" "), 1).cx*2;
  // adjust the rect further if the sort arrow is to be displayed.
  if( lpDrawItemStruct->itemID == (UINT)m_iSortColumn )
    rc.right -= (int)(4.5 * iOffset);

  rc.left += iOffset+2;
  rc.right -= iOffset+2;

  // draw the column label.
  if( rc.left < rc.right )  
    //(void)dc.DrawText( szText, -1, rc, uFormat );
    ::DrawText(lpDrawItemStruct->hDC, szText, _tcslen(szText), &rc, uFormat);  


  // draw the sort arrow.
  if( lpDrawItemStruct->itemID == (UINT)m_iSortColumn )
  {
    // set up the pens to use for drawing the arrow.
    CPen penLight( PS_SOLID, 1, m_crCOLOR_3DHILIGHT );
    CPen penShadow( PS_SOLID, 1, m_crCOLOR_3DSHADOW );
    CPen* pOldPen = dc.SelectObject( &penLight );

    if( m_bSortAscending )
    {
      // Draw triangle pointing upwards

      dc.MoveTo( rcIcon.right - 2 * iOffset, rcIcon.bottom-iOffset-8);
      dc.LineTo( rcIcon.right - iOffset, rcIcon.bottom - iOffset - 1 );
      dc.LineTo( rcIcon.right - 3 * iOffset - 2, rcIcon.bottom - iOffset - 1 );
      (void)dc.SelectObject( &penShadow );
      dc.MoveTo( rcIcon.right - 3 * iOffset - 1, rcIcon.bottom - iOffset - 1 );
      dc.LineTo( rcIcon.right - 2 * iOffset, rcIcon.bottom-iOffset-8-1);    
    }
    else
    {
      // Draw triangle pointing downwords
      dc.MoveTo( rcIcon.right - iOffset , rcIcon.bottom-iOffset-8);
      dc.LineTo( rcIcon.right - 2 * iOffset-1 , rcIcon.bottom - iOffset );
      (void)dc.SelectObject( &penShadow );
      dc.MoveTo( rcIcon.right - 2 * iOffset - 2, rcIcon.bottom - iOffset-1 );
      dc.LineTo( rcIcon.right - 3 * iOffset - 2, rcIcon.bottom-iOffset-8);
      dc.LineTo( rcIcon.right - iOffset , rcIcon.bottom-iOffset-8);   
    
    }
    // restore the pen.
    (void)dc.SelectObject( pOldPen );
  }

  // restore the previous device context.
  VERIFY( dc.RestoreDC( iSavedDC ) );

  // detach the device context before returning.
  (void)dc.Detach();
}


void CHeaderCtrlEx::SetSortArrow( const int iSortColumn, const BOOL bSortAscending )
{
  m_iSortColumn = iSortColumn;
  m_bSortAscending = bSortAscending;

  // change the item to owner drawn.
  HD_ITEM hditem;

  hditem.mask = HDI_FORMAT;
  VERIFY( GetItem( iSortColumn, &hditem ) );
  hditem.fmt |= HDF_OWNERDRAW;
  VERIFY( SetItem( iSortColumn, &hditem ) );

  // invalidate the header control so it gets redrawn
  Invalidate();
}