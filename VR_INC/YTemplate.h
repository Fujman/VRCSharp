#ifndef __YTEMPLATE_H
#define __YTEMPLATE_H

#define STATIC_IF(COND,Ta,Tb) YIfThenElse<Ta,Tb>::YResult<COND>::TYPE

template <typename Ta, typename Tb> struct YIfThenElse
{
  template <bool COND> struct YResult;
  template<> struct YResult<true>
  {
    public: typedef Ta TYPE;
  };
  template<> struct YResult<false>
  {
    public: typedef Tb TYPE;
  };
};

#if 0

#define STATIC_IF(COND,Ta,Tb) YIfThenElse<COND,Ta,Tb>::YResult

template <bool IF, typename Ta, typename Tb> class YIfThenElse;

template <typename Ta, typename Tb> class YIfThenElse<true,Ta,Tb> 
{
  public: typedef Ta YResult;
};

template <typename Ta, typename Tb> class YIfThenElse<false,Ta,Tb> 
{
  public: typedef Tb YResult;
};
#endif


#endif//__YTEMPLATE_H