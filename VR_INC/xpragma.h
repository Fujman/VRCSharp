#ifndef __XPRAGMA_H
#define __XPRAGMA_H

//Example: #pragma message(__FILE__LINE__ ": warning : text text text" )

//#pragma message() support macroces:
#define xpragma__line__(line)    #line
#define xpragma__line(line)      xpragma__line__(line)

#define __FILE__LINE__ __FILE__ "(" xpragma__line(__LINE__) ")"

#endif//__XPRAGMA_H
#pragma once
