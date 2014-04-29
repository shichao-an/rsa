#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "keys.h"
#include "certificate.h"

/* One-way hash function
 */
rsa_int rsa_hash(Pair *r)
{
    int i;
    char res;
    char *n_bytes, *e_bytes;
    res = (char) 0;
    for (i = 0; i < NUM_NAME_CHARS; i++) {
        res ^= r->name[i];
    }
    n_bytes = int_to_chars(r->n);
    e_bytes = int_to_chars(r->e);
    for (i = 0; i < 4; i ++) {
        res ^= n_bytes[i];
        res ^= e_bytes[i];
    }
    free(n_bytes);
    free(e_bytes);
    return (rsa_int) res;
}

/* Sign a hashed value
 */
rsa_int rsa_sign(rsa_int h, Key *private_key)
{
    rsa_int sig;
    rsa_int m = (rsa_int) h;
    sig = crypt(m, private_key);
    return sig;
}

Certificate *generate_certificate(char name[], Key *public_key, Key *private_key)
{
    Pair *r;
    Certificate *cert;
    rsa_int sig, h;
    int padding, l;  // l is length (number of chars) of `name`
    char *p;
    r = (Pair *) malloc(sizeof(Pair));
    cert = (Certificate *) malloc(sizeof(Certificate));

    /* Pad `r->name` with leading blanks */
    memset(r->name, ' ', NUM_NAME_CHARS);  // Initialize with blanks
    p = r->name;
    if (strlen(name) > NUM_NAME_CHARS)
        l = NUM_NAME_CHARS;
    else
        l = strlen(name);
    padding = NUM_NAME_CHARS - l;
    p += padding;
    strncpy(p, name, l);

    /* Add n and e to Pair r */
    r->n = public_key->n;
    r->e = public_key->k;
    
    /* Hash r to h and sign h */
    h = rsa_hash(r);
    sig = rsa_sign(h, private_key);

    /* Add pair and signed hash to certificate */
    cert->pair = r;
    cert->s = sig;
    return cert;
}

/* Convert a 32-bit integer to an four-sized array of chars
 */
char *int_to_chars(int n)
{
    char *bytes;
    bytes = (char *) malloc(4 * sizeof(char));
    bytes[0] = (n >> 24) & 0xFF;
    bytes[1] = (n >> 16) & 0xFF;
    bytes[2] = (n >> 8) & 0xFF;
    bytes[3] = n & 0xFF;
    return bytes;
}
