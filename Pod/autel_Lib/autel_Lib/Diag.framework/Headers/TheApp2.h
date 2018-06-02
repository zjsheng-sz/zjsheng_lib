#ifndef __THEAPP2_H__
#define __THEAPP2_H__
#include "Shell.h"

extern "C" UINT __attribute__ ((visibility("default"))) StartDemo2( );

#ifdef SHELL2ND
extern "C" int AutelStartShell();
void AutelSysCall(){
	AutelStartShell();
}

#else

extern "C" void __attribute__ ((visibility("default"))) _init(void){};

#endif

#endif

