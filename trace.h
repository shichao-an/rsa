#ifndef RSA_TRACE_H
#define RSA_TRACE_H

#include <stdio.h>
#include "keys.h"
#include "certificate.h"

#ifdef NTRACE
#define trace(M, ...)
#define trace_int_bits(M, ...)
#define trace_char_bits(M, ...)
#define trace_pair_bits(M, ...)
#else
#define trace(M, ...) fprintf(stdout, "TRACE %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define trace_int_bits(M, ...) print_int_bits(M, ##__VA_ARGS__)
#define trace_char_bits(M, ...) print_char_bits(M, ##__VA_ARGS__)
#define trace_pair_bits(M, ...) print_pair_bits(M, ##__VA_ARGS__)
#endif

void print_int_bits(rsa_int a, char *desc);
void print_char_bits(char a, char *desc);
void print_pair_bits(Pair *r, char *desc);
#endif
