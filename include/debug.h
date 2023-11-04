#pragma once
#ifdef DBG
#include <stdio.h>
#define STR(X) # X
#define XSTR(X) STR(X)
#define DEBUG(X) fprintf(stdout, "DEBUG\t" XSTR(X) ": %#0*x\n", sizeof(X)*2, X)
#else
#define DEBUG(X) (void)X
#endif