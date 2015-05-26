#ifndef _DCLIST_
#define _DCLIST_

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/************* „“‚€€‚‹…›‰ –ˆŠ‹ˆ—…‘Šˆ‰ ‘ˆ‘ŽŠ **************************/

typedef struct tagDCNODE {
        struct tagDCNODE FAR *nxt;
        struct tagDCNODE FAR *prv;
} DCNODE;
typedef DCNODE FAR *LPDCNODE;

typedef struct {
        LPDCNODE first;
        WORD   cnt;
} DCLIST;
typedef DCLIST FAR *LPDCLIST;

typedef struct tagDCBRANCH {
  DCNODE          lev;
  struct tagDCBRANCH FAR *Parent;
  DCLIST          Sons;
} DCBRANCH;
typedef DCBRANCH FAR * LPDCBRANCH;

DWORD FAR PASCAL DC_AllocList(LPDCLIST lst,DWORD cnt,DWORD size);
VOID  FAR PASCAL DC_FreeList(LPDCLIST lst);

LPDCNODE FAR PASCAL DC_InitNode(LPDCNODE node);
LPDCNODE FAR PASCAL DC_GetLastNode(LPDCLIST lst);

void FAR PASCAL DC_AddHead(LPDCLIST lst,LPDCNODE n);
void FAR PASCAL DC_AddTail(LPDCLIST lst,LPDCNODE n);
void FAR PASCAL DC_AddListBefore(LPDCLIST lst,LPDCNODE node,LPDCNODE n);
void FAR PASCAL DC_AddListAfter(LPDCLIST lst,LPDCNODE node,LPDCNODE n);
void FAR PASCAL DC_Remove(LPDCLIST lst,LPDCNODE node);

#define DC_NEXT(n)                   ((LPVOID)(((LPDCNODE)(n))->nxt))
#define DC_PREV(n)                   ((LPVOID)(((LPDCNODE)(n))->prv))
#define DC_GETFIRST(lst)             ((LPVOID)( ((LPDCLIST)(lst))->first ))
#define DC_GETLAST(lst)              ( ((lst)->first) ? (lst)->first->prv : NULL )
#define DC_GETCNT(lst)               ( (lst)->cnt )
#define DC_INIT(node)                ((LPVOID)DC_InitNode((LPDCNODE)(node)))
#define DC_LISTINIT(lst)             {(lst)->first=NULL;(lst)->cnt=0;}
#define DC_ADDTAIL(lst,node)         DC_AddTail((LPDCLIST)(lst),(LPDCNODE)(node))
#define DC_ADDHEAD(lst,node)         DC_AddHead((LPDCLIST)(lst),(LPDCNODE)(node))
#define DC_REMOVE(lst,node)          DC_Remove((LPDCLIST)(lst) ,(LPDCNODE)(node))
#define DC_INSERTBEFORE(lst,node,n)  DC_AddListBefore((LPDCLIST)(lst),(LPDCNODE)(node),(LPDCNODE)(n))
#define DC_INSERTAFTER(lst,node,n)   DC_AddListAfter((LPDCLIST)(lst),(LPDCNODE)(node),(LPDCNODE)(n))

#ifdef __cplusplus
}
#endif

#endif

