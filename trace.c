#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trace.h"

void print_int_bits(rsa_int a, char *desc)
{
    char s[33], b;
    int i;
    memset(s, '0', 33);
    s[32] = '\0';
    for (i = 0; a >> i && i <= 31; i++) {
        b = (a & (1 << i)) != 0 ? '1' : '0';
        s[31 - i] = b;
    }
    printf("  %s: %s\n", desc, s);
}

void print_char_bits(char a, char *desc)
{
    char s[9], b;
    int i;
    memset(s, '0', 9);
    s[8] = '\0';
    for (i = 0; a >> i && i <= 7; i++) {
        b = (a & (1 << i)) != 0 ? '1' : '0';
        s[7 - i] = b;
    }
    printf("  %s: %s\n", desc, s);
}

void print_pair_bits(Pair *r, char *desc)
{
    size_t nc = NUM_NAME_CHARS;
    size_t ns = nc + 65; // 6 + 65 = 71
    char s[ns], b;
    int i;
    memset(s, '0', nc + 65);
    s[ns - 1] = '\0';  // ns - 1 = 70
    // name: bytes 1 - 6 (Bit index 0 - 5)
    strncpy(s, r->name, nc);
    // n: bytes 7 - 10 (Bit index 6 - 37)
    for (i = 0; r->n >> i && i <= 31; i++) {
        b = (r->n & (1 << i)) != 0 ? '1' : '0';
        s[nc + 31 - i] = b;
    }
    // e: bytes 11 - 14 (Bit index 38 - 69, 70 is '\0')
    for (i = 0; r->e >> i && i <= 31; i++) {
        b = (r->e & (1 << i)) != 0 ? '1' : '0';
        s[nc + 63 - i] = b;
    }
    printf("  %s: %s\n", desc, s);
}
