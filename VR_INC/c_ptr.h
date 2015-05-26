#define C_PTR_ALIGN(t,p,a)  ((t) ((((DWORD)(p))+((int)(a)-1))/(int)(a)*(int)(a)))

#define C_PTR_CAST(t,p,p2)   t p = (t)(p2)
