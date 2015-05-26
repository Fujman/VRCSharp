#ifndef _YHIERARHYITEMEXT_
#define _YHIERARHYITEMEXT_

#include "YList.h"

template <class T> 
class YHierarhyItemExt : public YHierarhyItem<T>
{
public:
     YHierarhyItemExt(T* pThis, CArrayGuard* pcsGuard):
     YHierarhyItem<T>(pThis,pcsGuard){}// build owner of list, if NULL - unprotected
     YHierarhyItemExt(T* pThis=NULL, YHierarhyItem<T>* pParent=NULL, YHierarhyItem<T>* pBuddy=NULL, YHierarhyItem<T>* pChild=NULL)
		 :YHierarhyItem<T>(pThis, pParent, pBuddy, pChild)
	 {}
	 


	 YHierarhyItemExt<T>*    _GetHierarhyRootBuddy(){return (YHierarhyItemExt<T>*) YHierarhyItem<T>::_GetHierarhyRootBuddy();}
     
     int   InsertChild(YHierarhyItemExt<T>* pChild,
         YHierarhyItemExt<T>* pBuddyAfter,BOOL bAddWithAllBuddies=FALSE, DWORD dwTimeout=INFINITE)
     {
		 YHierarhyItemExt<T>* pOldChild = (YHierarhyItemExt<T>*)pChild->m_pChild; pChild->m_pChild=NULL; // save old child
		 {if(!LockArray(dwTimeout)) return -1;//lock
         ASSERT(pChild->m_pParent==NULL && (bAddWithAllBuddies||(pChild->m_pChild==NULL && pChild->m_pBuddy==NULL && pChild->m_pPrevBuddy==NULL)));
         ASSERT(pChild->m_pcsGuard==NULL || pChild->m_pcsGuard==m_pcsGuard);

         
		 if(bAddWithAllBuddies)
		 {
			 for(YHierarhyItemExt<T>* pBuddy=pChild; pBuddy!=NULL; pBuddy=(YHierarhyItemExt<T>*)pBuddy->m_pBuddy)
			 { //correct childs list
				 pBuddy->m_pParent = this;
             }
		 }
		 
		 if(m_pChild==NULL)  // add new childs list root
         {
             m_pChild = pChild;
			 pChild->m_pChild = pOldChild;
         }else{ // add to end of childs list
             YHierarhyItemExt<T>* pTwin = ((YHierarhyItemExt<T>*)m_pChild)->_GetHierarhyRootBuddy();
             
             if(pBuddyAfter==NULL)
             {
                 YHierarhyItemExt<T>* pOldChild = (YHierarhyItemExt<T>*)m_pChild;
                 m_pChild = pChild;//m_pChild->_GetHierarhyLastBuddy()->_AddBuddy(pChild);
                 pOldChild->m_pPrevBuddy = m_pChild;
                 ((YHierarhyItemExt<T>*)m_pChild)->m_pBuddy     = pOldChild;
                 ((YHierarhyItemExt<T>*)m_pChild)->m_pPrevBuddy = NULL; 
			 }
             else
             {
				//Check for consistency
                for(; pTwin->m_pBuddy!=NULL; pTwin=(YHierarhyItemExt<T>*)pTwin->m_pBuddy)
                {
                    ASSERT(((YHierarhyItemExt<T>*)pTwin->m_pBuddy)->m_pParent==this || pTwin==pBuddyAfter);
                    if(pTwin->m_pParent==this)
                          if(pTwin==pBuddyAfter)
                              break;
                }//pTwin is last twin by parent or end of buddies list
             
                pTwin->_AddBuddy(pChild);//m_pChild->_GetHierarhyLastBuddy()->_AddBuddy(pChild);
             }
			 pChild->m_pChild = pOldChild;
         }
         pChild->m_pcsGuard = m_pcsGuard;
         UnlockArray();}//unlock
         ASSERT(pBuddyAfter==NULL || pChild->m_pChild==pOldChild);
		 ASSERT(pChild->m_pParent == this);
		 return 0;
     }
	 
	 int DetachChild(YHierarhyItemExt<T>* pChild, BOOL bDetachWithAllBuddies=FALSE, DWORD dwTimeout=INFINITE)
	 {
		 {if(!pChild->LockArray(dwTimeout)) return -1;//lock childs hierarhy
		 //ASSERT(!bDetachWithAllBuddies);//TO DO
		 
		 {if(!LockArray(dwTimeout)) { pChild->UnlockArray(); return -1; }//lock
		 ASSERT(pChild->m_pParent==this);
		 ASSERT(m_pChild!=NULL);
		 //ASSERT(pChild->m_pcsGuard!=NULL && m_pcsGuard!=NULL && pChild->m_pcsGuard!=m_pcsGuard);
		 
		 //detach child from this
		 pChild->m_pParent = NULL;//TO DO: check all buddies list of this
		 
		 //detach this from child
		 BOOL bLinkChild=this->m_pChild==pChild;
		 if(bDetachWithAllBuddies)
		 {
			ASSERT(bLinkChild==TRUE);
			m_pChild=NULL; //correct buddies list
			for(YHierarhyItemExt<T>* pBuddy=pChild; pBuddy!=NULL; pBuddy=(YHierarhyItemExt<T>*)pBuddy->m_pBuddy)
				pBuddy->m_pParent = NULL;
            return 0;
		 }else
		 if(bLinkChild)
		 {     // we delete link to parent;
			 
			 if      (pChild->m_pPrevBuddy!=NULL){
				 //ASSERT(pChild->m_pPrevBuddy->m_pcsGuard!=pChild->m_pcsGuard);//TO DO: check all buddies list of pChild
				 ASSERT(pChild->m_pPrevBuddy->m_pParent==this);//TO DO
				 this->m_pChild = pChild->m_pPrevBuddy;//shift childs list left
				 pChild->m_pPrevBuddy->m_pBuddy = pChild->m_pBuddy;//Zero or not don`t care
			 }else
			 if(pChild->m_pBuddy!=NULL) {
				 //ASSERT(pChild->m_pBuddy->m_pcsGuard!=pChild->m_pcsGuard);//TO DO: check all buddies list of pChild
				 ASSERT(pChild->m_pBuddy->m_pParent==this);//TO DO
				 this->m_pChild = pChild->m_pBuddy;//shift childs list right
				 pChild->m_pBuddy->m_pPrevBuddy=NULL;
			 }else{
		 		 this->m_pChild = NULL;// last child deleted
			 }
		 }else //detach child from buddies
		 {
			 if(pChild->m_pPrevBuddy)
				pChild->m_pPrevBuddy->m_pBuddy=pChild->m_pBuddy;// renew right direction link
			 if(pChild->m_pBuddy)
				 pChild->m_pBuddy->m_pPrevBuddy = pChild->m_pPrevBuddy;// renew left direction link
		 }

		 pChild->m_pBuddy  = NULL;
		 pChild->m_pPrevBuddy = NULL;
		 
		 UnlockArray();}//unlock
		 
		 pChild->UnlockArray();}//unlock child hierarhy
		 return 0;
	 }

	 
	 
	 
	 
	 
	 friend class  YHierarhyIterator<T>;
};


#endif