#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <time.h>
#include "keys.h"
#include "certificate.h"


int main()
{
    srand(time(NULL));
    //printf("%d\n", generate_candidate());
    //printf("%d\n", is_prime(113));
    printf("%d\n", generate_prime());
    printf("%d\n", get_inverse(28, 75));
    Keypair *kp = generate_keypair();
    printf("N: %d\n", kp->public_key->n);
    printf("Pub: %d\n", kp->public_key->k);
    printf("Pri: %d\n", kp->private_key->k);
    destroy_keypair(kp);
    char *bytes = int_to_chars(128);
    printf("%d\n", bytes[2]);
    printf("%d\n", bytes[3]);
    Pair *r = (Pair *) malloc(sizeof(Pair));
    memset(r->name, ' ', 6);
    r->n = 10;
    r->e = 5;
    rsa_hash_t res = rsa_hash(r);
    printf("hash:%d\n", res);
    char a = 1;
    char b = 2;
    printf("a^z:%d\n", a^b);
    return 0;
}
