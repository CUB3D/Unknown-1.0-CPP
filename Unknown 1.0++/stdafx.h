// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//


#ifdef _WIN32
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

//#include <cstdio>

// TODO: reference additional headers your program requires here

//Fix for projects created in VS15
//FILE _iob[] = { *stdin, *stdout, *stderr };

//extern "C" FILE * __cdecl __iob_func(void)
//{
//	return _iob;
//}
#endif