#ifndef __YTIMESPAN_H
#define __YTIMESPAN_H
//
// == ////////////////////////////////////////////////////////////////////////////////////////////////////
//
inline BOOL operator  == (YTimeSpan        ts1, signed           ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (signed           ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }

inline BOOL operator  == (YTimeSpan        ts1, signed long      ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (signed  long     ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }

inline BOOL operator  == (YTimeSpan        ts1, signed short     ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (signed  short    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }

inline BOOL operator  == (YTimeSpan        ts1, signed char      ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (signed  char     ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }


inline BOOL operator  == (YTimeSpan        ts1, unsigned         ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (unsigned         ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }

inline BOOL operator  == (YTimeSpan        ts1, unsigned long    ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (unsigned long    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }

inline BOOL operator  == (YTimeSpan        ts1, unsigned short   ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (unsigned short   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }

inline BOOL operator  == (YTimeSpan        ts1, unsigned char    ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (unsigned char    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }


inline BOOL operator  == (YTimeSpan        ts1, signed __int64   ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (signed __int64   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }

inline BOOL operator  == (YTimeSpan        ts1, signed __int32   ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (signed __int32   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }

inline BOOL operator  == (YTimeSpan        ts1, signed __int16   ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (signed __int16   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }

inline BOOL operator  == (YTimeSpan        ts1, signed __int8    ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (signed __int8    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }


inline BOOL operator  == (YTimeSpan        ts1, unsigned __int64 ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (unsigned __int64 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }

inline BOOL operator  == (YTimeSpan        ts1, unsigned __int32 ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (unsigned __int32 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }

inline BOOL operator  == (YTimeSpan        ts1, unsigned __int16 ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (unsigned __int16 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }

inline BOOL operator  == (YTimeSpan        ts1, unsigned __int8  ts2)  { return (YTIME)ts1 == (YTIME)ts2; }
inline BOOL operator  == (unsigned __int8  ts1, YTimeSpan        ts2)  { return (YTIME)ts1 == (YTIME)ts2; }

//
// != ////////////////////////////////////////////////////////////////////////////////////////////////////
//
inline BOOL operator  != (YTimeSpan        ts1, signed           ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (signed           ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }

inline BOOL operator  != (YTimeSpan        ts1, signed long      ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (signed  long     ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }

inline BOOL operator  != (YTimeSpan        ts1, signed short     ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (signed  short    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }

inline BOOL operator  != (YTimeSpan        ts1, signed char      ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (signed  char     ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }


inline BOOL operator  != (YTimeSpan        ts1, unsigned         ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (unsigned         ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }

inline BOOL operator  != (YTimeSpan        ts1, unsigned long    ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (unsigned long    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }

inline BOOL operator  != (YTimeSpan        ts1, unsigned short   ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (unsigned short   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }

inline BOOL operator  != (YTimeSpan        ts1, unsigned char    ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (unsigned char    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }


inline BOOL operator  != (YTimeSpan        ts1, signed __int64   ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (signed __int64   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }

inline BOOL operator  != (YTimeSpan        ts1, signed __int32   ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (signed __int32   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }

inline BOOL operator  != (YTimeSpan        ts1, signed __int16   ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (signed __int16   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }

inline BOOL operator  != (YTimeSpan        ts1, signed __int8    ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (signed __int8    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }


inline BOOL operator  != (YTimeSpan        ts1, unsigned __int64 ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (unsigned __int64 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }

inline BOOL operator  != (YTimeSpan        ts1, unsigned __int32 ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (unsigned __int32 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }

inline BOOL operator  != (YTimeSpan        ts1, unsigned __int16 ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (unsigned __int16 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }

inline BOOL operator  != (YTimeSpan        ts1, unsigned __int8  ts2)  { return (YTIME)ts1 != (YTIME)ts2; }
inline BOOL operator  != (unsigned __int8  ts1, YTimeSpan        ts2)  { return (YTIME)ts1 != (YTIME)ts2; }

//
// >= ////////////////////////////////////////////////////////////////////////////////////////////////////
//
inline BOOL operator  >= (YTimeSpan        ts1, signed           ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (signed           ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }

inline BOOL operator  >= (YTimeSpan        ts1, signed long      ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (signed  long     ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }

inline BOOL operator  >= (YTimeSpan        ts1, signed short     ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (signed  short    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }

inline BOOL operator  >= (YTimeSpan        ts1, signed char      ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (signed  char     ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }


inline BOOL operator  >= (YTimeSpan        ts1, unsigned         ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (unsigned         ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }

inline BOOL operator  >= (YTimeSpan        ts1, unsigned long    ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (unsigned long    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }

inline BOOL operator  >= (YTimeSpan        ts1, unsigned short   ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (unsigned short   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }

inline BOOL operator  >= (YTimeSpan        ts1, unsigned char    ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (unsigned char    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }


inline BOOL operator  >= (YTimeSpan        ts1, signed __int64   ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (signed __int64   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }

inline BOOL operator  >= (YTimeSpan        ts1, signed __int32   ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (signed __int32   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }

inline BOOL operator  >= (YTimeSpan        ts1, signed __int16   ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (signed __int16   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }

inline BOOL operator  >= (YTimeSpan        ts1, signed __int8    ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (signed __int8    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }


inline BOOL operator  >= (YTimeSpan        ts1, unsigned __int64 ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (unsigned __int64 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }

inline BOOL operator  >= (YTimeSpan        ts1, unsigned __int32 ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (unsigned __int32 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }

inline BOOL operator  >= (YTimeSpan        ts1, unsigned __int16 ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (unsigned __int16 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }

inline BOOL operator  >= (YTimeSpan        ts1, unsigned __int8  ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }
inline BOOL operator  >= (unsigned __int8  ts1, YTimeSpan        ts2)  { return (YTIME)ts1 >= (YTIME)ts2; }

//
// <= ////////////////////////////////////////////////////////////////////////////////////////////////////
//
inline BOOL operator  <= (YTimeSpan        ts1, signed           ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (signed           ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }

inline BOOL operator  <= (YTimeSpan        ts1, signed long      ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (signed  long     ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }

inline BOOL operator  <= (YTimeSpan        ts1, signed short     ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (signed  short    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }

inline BOOL operator  <= (YTimeSpan        ts1, signed char      ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (signed  char     ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }


inline BOOL operator  <= (YTimeSpan        ts1, unsigned         ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (unsigned         ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }

inline BOOL operator  <= (YTimeSpan        ts1, unsigned long    ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (unsigned long    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }

inline BOOL operator  <= (YTimeSpan        ts1, unsigned short   ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (unsigned short   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }

inline BOOL operator  <= (YTimeSpan        ts1, unsigned char    ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (unsigned char    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }


inline BOOL operator  <= (YTimeSpan        ts1, signed __int64   ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (signed __int64   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }

inline BOOL operator  <= (YTimeSpan        ts1, signed __int32   ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (signed __int32   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }

inline BOOL operator  <= (YTimeSpan        ts1, signed __int16   ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (signed __int16   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }

inline BOOL operator  <= (YTimeSpan        ts1, signed __int8    ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (signed __int8    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }


inline BOOL operator  <= (YTimeSpan        ts1, unsigned __int64 ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (unsigned __int64 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }

inline BOOL operator  <= (YTimeSpan        ts1, unsigned __int32 ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (unsigned __int32 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }

inline BOOL operator  <= (YTimeSpan        ts1, unsigned __int16 ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (unsigned __int16 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }

inline BOOL operator  <= (YTimeSpan        ts1, unsigned __int8  ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }
inline BOOL operator  <= (unsigned __int8  ts1, YTimeSpan        ts2)  { return (YTIME)ts1 <= (YTIME)ts2; }

//
// > ////////////////////////////////////////////////////////////////////////////////////////////////////
//
inline BOOL operator  > (YTimeSpan        ts1, signed           ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (signed           ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }

inline BOOL operator  > (YTimeSpan        ts1, signed long      ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (signed  long     ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }

inline BOOL operator  > (YTimeSpan        ts1, signed short     ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (signed  short    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }

inline BOOL operator  > (YTimeSpan        ts1, signed char      ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (signed  char     ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }


inline BOOL operator  > (YTimeSpan        ts1, unsigned         ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (unsigned         ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }

inline BOOL operator  > (YTimeSpan        ts1, unsigned long    ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (unsigned long    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }

inline BOOL operator  > (YTimeSpan        ts1, unsigned short   ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (unsigned short   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }

inline BOOL operator  > (YTimeSpan        ts1, unsigned char    ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (unsigned char    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }


inline BOOL operator  > (YTimeSpan        ts1, signed __int64   ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (signed __int64   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }

inline BOOL operator  > (YTimeSpan        ts1, signed __int32   ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (signed __int32   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }

inline BOOL operator  > (YTimeSpan        ts1, signed __int16   ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (signed __int16   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }

inline BOOL operator  > (YTimeSpan        ts1, signed __int8    ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (signed __int8    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }


inline BOOL operator  > (YTimeSpan        ts1, unsigned __int64 ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (unsigned __int64 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }

inline BOOL operator  > (YTimeSpan        ts1, unsigned __int32 ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (unsigned __int32 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }

inline BOOL operator  > (YTimeSpan        ts1, unsigned __int16 ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (unsigned __int16 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }

inline BOOL operator  > (YTimeSpan        ts1, unsigned __int8  ts2)  { return (YTIME)ts1 > (YTIME)ts2; }
inline BOOL operator  > (unsigned __int8  ts1, YTimeSpan        ts2)  { return (YTIME)ts1 > (YTIME)ts2; }

//
// < ////////////////////////////////////////////////////////////////////////////////////////////////////
//
inline BOOL operator  < (YTimeSpan        ts1, signed           ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (signed           ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }

inline BOOL operator  < (YTimeSpan        ts1, signed long      ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (signed  long     ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }

inline BOOL operator  < (YTimeSpan        ts1, signed short     ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (signed  short    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }

inline BOOL operator  < (YTimeSpan        ts1, signed char      ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (signed  char     ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }


inline BOOL operator  < (YTimeSpan        ts1, unsigned         ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (unsigned         ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }

inline BOOL operator  < (YTimeSpan        ts1, unsigned long    ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (unsigned long    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }

inline BOOL operator  < (YTimeSpan        ts1, unsigned short   ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (unsigned short   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }

inline BOOL operator  < (YTimeSpan        ts1, unsigned char    ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (unsigned char    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }


inline BOOL operator  < (YTimeSpan        ts1, signed __int64   ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (signed __int64   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }

inline BOOL operator  < (YTimeSpan        ts1, signed __int32   ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (signed __int32   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }

inline BOOL operator  < (YTimeSpan        ts1, signed __int16   ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (signed __int16   ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }

inline BOOL operator  < (YTimeSpan        ts1, signed __int8    ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (signed __int8    ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }


inline BOOL operator  < (YTimeSpan        ts1, unsigned __int64 ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (unsigned __int64 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }

inline BOOL operator  < (YTimeSpan        ts1, unsigned __int32 ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (unsigned __int32 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }

inline BOOL operator  < (YTimeSpan        ts1, unsigned __int16 ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (unsigned __int16 ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }

inline BOOL operator  < (YTimeSpan        ts1, unsigned __int8  ts2)  { return (YTIME)ts1 < (YTIME)ts2; }
inline BOOL operator  < (unsigned __int8  ts1, YTimeSpan        ts2)  { return (YTIME)ts1 < (YTIME)ts2; }

//
// test /////////////////////////////////////////////////////////////////////////////////////////////////
//
#if 1
inline void YTimeSpan__compare_operators_compilation_test()
{
  YTimeSpan ts(0);
  {
    BOOL b = ts< 0 || 0< ts || ts> 0 || 0> ts
          || ts<=0 || 0<=ts || ts>=0 || 0>=ts
          || ts==0 || 0==ts || ts!=0 || 0!=ts;
  }
  {
    YTIME O = 0;
    BOOL b = ts< O || O< ts || ts> O || O> ts
          || ts<=O || O<=ts || ts>=O || O>=ts
          || ts==O || O==ts || ts!=O || O!=ts;
  }
  {
    YTimeSpan O(0);
    BOOL b = ts< O || O< ts || ts> O || O> ts
          || ts<=O || O<=ts || ts>=O || O>=ts
          || ts==O || O==ts || ts!=O || O!=ts;
  }
}
#endif

#endif// __YTIMESPAN_H
#pragma once
