#ifndef RSA_KEYS_H
#define RSA_KEYS_H

#define NUM_BITS 7  /* Number of bits to store primes */
#define NUM_TESTS 20  /* Number of values to pass primality test */


typedef int rsa_int; 
typedef struct Key {
    rsa_int n;
    rsa_int k;
} Key;


typedef struct Keypair {
    Key *private_key;
    Key *public_key;
} Keypair;


rsa_int generate_candidate();
rsa_int primality_test(rsa_int a, rsa_int n);
rsa_int is_prime(rsa_int n);
rsa_int generate_prime();

#endif
