#include <math.h>
#define eqvl(x,y) (fabs((x)-(y))<=(fabs(x)+fabs(y))*2e-15)
#define squb(x)   pow((x)<0.0?-(x):(x),1.0/3.0)*((x)<0.0?-1.0:1.0);
#define squa(x)   pow((x)<0.0?-(x):(x),1.0/4.0)*((x)<0.0?-1.0:1.0);
#define sq(x)     ((x)*(x))

#define XMATH__PI  3.14159265358979323846        // число п
#define XMATH__E   2.71828182845904523536        // число e
#define XMATH__M   0.434294481903251827651       // lg(e)
#define XMATH__C   0.577216                      // постоянная Эйлера

inline  int xrand(int nMin, int nMax)
{
  int nRnd = rand();
  // 0..RAND_MAX -> nMin..nMax;
  int nValues  = nMax-nMin+1;
  int nRandoms = RAND_MAX+1;
  int nCur = int(__int64(nRnd-0)*nValues/nRandoms) + nMin;
//int nCur = muldiv32(nRnd-0,nValues,nRandoms) + nMin;//error?
  return nCur;
}

void xmath__rand_shuffle_array(int* aArray, int nLen, BOOL bInit=FALSE, BOOL bInitRand=FALSE);