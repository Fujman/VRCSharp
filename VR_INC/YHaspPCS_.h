#include "YHaspPCS.h"
#include "xpragma.h"

#if defined(YHASP_USE_HASP_PCS) && defined(YHASP_PCS_MANUAL)
static HASP_PCS hasp_pcs = { {HASP_PCS_SIGNATURE} };
#pragma message(__FILE__LINE__ " : notify : HASP PCS invoked manually")
#endif
