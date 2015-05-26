#ifndef __XCWNDMAP_H
#define __XCWNDMAP_H

#if VS2010_VERSION

#define BEGIN_TEMPLATED_MESSAGE_MAP(theClass, baseClass)\
  BEGIN_TEMPLATE_MESSAGE_MAP(theClass, T, baseClass)

#else //VS 6.0

// BEGIN_TEMPLATED_MESSAGE_MAP(theClass, baseClass)           //AY
// BEGIN_TEMPLATE_MESSAGE_MAP(theClass, tmplClass, baseClass) //AA

#ifdef _AFXDLL
#define BEGIN_TEMPLATED_MESSAGE_MAP(theClass, baseClass) \
template <class T> \
    const AFX_MSGMAP* PASCAL theClass<T>::_GetBaseMessageMap() \
    { return &baseClass::messageMap; } \
template <class T> \
    AFX_COMDAT AFX_DATADEF const AFX_MSGMAP theClass<T>::messageMap = \
    { &theClass::_GetBaseMessageMap, &theClass::_messageEntries[0] }; \
template <class T> \
    const AFX_MSGMAP* theClass<T>::GetMessageMap() const \
    { return &theClass::messageMap; } \
template <class T> \
    AFX_COMDAT const AFX_MSGMAP_ENTRY theClass<T>::_messageEntries[] = {
#else
#define BEGIN_TEMPLATED_MESSAGE_MAP(theClass, baseClass) \
template <class T> \
    AFX_COMDAT AFX_DATADEF const AFX_MSGMAP theClass<T>::messageMap = \
    { &baseClass::messageMap, &theClass::_messageEntries[0] }; \
template <class T> \
    const AFX_MSGMAP* theClass<T>::GetMessageMap() const \
    { return &theClass::messageMap; } \
template <class T> \
    AFX_COMDAT const AFX_MSGMAP_ENTRY theClass<T>::_messageEntries[] = {
#endif

#ifdef _AFXDLL
#define BEGIN_TEMPLATE_MESSAGE_MAP(theClass, tmplClass, baseClass) \
	template<class tmplClass>\
	const AFX_MSGMAP* PASCAL theClass<tmplClass>::_GetBaseMessageMap() \
		{ return &baseClass::messageMap; } \
	template<class tmplClass>\
		const AFX_MSGMAP* theClass<tmplClass>::GetMessageMap() const \
		  { return &theClass<tmplClass>::messageMap; } \
	template<class tmplClass>\
 	  AFX_COMDAT AFX_DATADEF const AFX_MSGMAP theClass<tmplClass>::messageMap = \
	    { &theClass<tmplClass>::_GetBaseMessageMap, &theClass<tmplClass>::_messageEntries[0] }; \
	template<class tmplClass>\
	  AFX_COMDAT const AFX_MSGMAP_ENTRY theClass<tmplClass>::_messageEntries[] = \
	{
	
#else
#define BEGIN_TEMPLATE_MESSAGE_MAP(theClass, tmplClass, baseClass) \
	template<class tmplClass>\
	const AFX_MSGMAP* theClass<tmplClass>::GetMessageMap() const \
		{ return &theClass<tmplClass>::messageMap; } \
	template<class tmplClass>\
		AFX_COMDAT AFX_DATADEF const AFX_MSGMAP theClass<tmplClass>::messageMap = \
	    { &baseClass::messageMap, &theClass<tmplClass>::_messageEntries[0] }; \
	template<class tmplClass>\
	AFX_COMDAT const AFX_MSGMAP_ENTRY theClass<tmplClass>::_messageEntries[] = \
	{
	
#endif


#endif //VS 6.0

#endif//__XCWNDMAP_H
#pragma once
