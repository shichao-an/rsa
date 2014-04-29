#include <stdlib.h> 
#include <stdio.h>
#include <time.h>
#include "keys.h"


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
    return 0;
}
