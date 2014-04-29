#ifndef RSA_CERTIFICATE_H
#define RSA_CERTIFICATE_H
#include "keys.h"
#include "trace.h"

#define NUM_NAME_CHARS 6

typedef int rsa_hash_t;
typedef struct Pair {
    char name[NUM_NAME_CHARS];
    rsa_int n;
    rsa_int e;
} Pair;

typedef struct Certificate {
    Pair *pair;
    rsa_int s;  // Signature
} Certificate;

rsa_int rsa_hash(Pair *r);
rsa_int rsa_int_hash(rsa_int u);
rsa_int rsa_sign(rsa_int h, Key *private_key);
Certificate *generate_certificate(char name[], Key *public_key, Key *private_key);
void destroy_certificate(Certificate *cert);
char *int_to_chars(int n);
rsa_int generate_random_u(Certificate *cert);
#endif
