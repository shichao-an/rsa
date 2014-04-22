#ifndef RSA_TRACE_H
#define RSA_TRACE_H

#include <stdio.h>

#ifdef NTRACE
#define trace(M, ...)
#else
#define trace(M, ...) fprintf(stderr, "TRACE %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#endif
