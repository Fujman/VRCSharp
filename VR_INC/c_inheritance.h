#ifndef __C_INHERITANCE_H
#define __C_INHERITANCE_H

#ifdef __cplusplus
  #define INHERIT(c)            :public c
  #define PUBLIC(c)             :public c
  #define PUBLIC2(c1,c2)        :public c1,c2
  #define INHERITED(op)
  #define I(op)
  #define Cxx(op)               op
  #define Cx1(op)               op
  #define Cx2(op,op2)           op,op2

  #define USE_AS(type,member)\
    operator const type&() const\
      { return *reinterpret_cast<const type*>(&(member)); }\
    operator type&()\
      { return *reinterpret_cast<type*>(&(member)); }

  #define ASS_AS(type,member)\
    type& operator =(const type& e) { ((type&)member) = e; return (type&)member; }

  #define USE_AS_OPERATOR(type,body) \
    operator type() body
  #define ASS_AS_OPERATOR(type,body) \
    type& operator =(const type& e) body
  #define DECLAREOPERATOR(type,body) \
    operator type() body

  #define DECLARE_ASSIGN(type)  ASS_AS(type, *this)
  #define DECLARE_PARENT(type)  USE_AS(type, *this); ASS_AS(type, *this)
  #define PARENT(type, member)  type member; USE_AS(type,member); ASS_AS(type,member);
#else//C
  #define INHERIT(s)
  #define PUBLIC(c)
  #define PUBLIC2(c1,c2)
  #define INHERITED(op)         op
  #define I(op)                 op
  #define Cxx(op)
  #define Cx1(op)
  #define Cx2(op,op2)
  #define USE_AS(type,member)
  #define ASS_AS(type,member)
  #define USE_AS_OPERATOR(type,body)
  #define ASS_AS_OPERATOR(type,body)
  #define DECLAREOPERATOR(type,body)
  #define DECLARE_ASSIGN(type)
  #define DECLARE_PARENT(type)
  #define PARENT(type, member)  struct type member;
#endif

#endif/ __C_INHERITANCE_H