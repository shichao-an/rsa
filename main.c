#include <assert.h>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <time.h>
#include "keys.h"
#include "certificate.h"


int main()
{
    srand(time(NULL));
    Keypair *t = generate_keypair();  // Trent
    Keypair *kp1 = generate_keypair(); // Alice

    /* Alice's certificate */
    Certificate *c = generate_certificate("Alice", kp1->public_key, t->private_key);

    /* Bob's u */
    rsa_int u = generate_random_u(c);

    /* Alice computes h(u) and v */
    rsa_int hu = rsa_int_hash(u);
    rsa_int v = crypt(hu, kp1->private_key);

    /* Alice sends v to Bob 
     * Bob encrypts v with Alice's public key,
     * and checks whether it is h(u)
     * */
    rsa_int r = crypt(v, kp1->public_key);
    assert(r == hu);

    destroy_certificate(c);
    destroy_keypair(kp1);
    destroy_keypair(t);
    print_char_bits(255, "a");
    return 0;
}
