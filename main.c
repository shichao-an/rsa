#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "keys.h"
#include "certificate.h"
#include "trace.h"


int main()
{
    srand(time(NULL));
    Keypair *t = generate_keypair();  // Trent
    Keypair *kp1 = generate_keypair(); // Alice

    /* Alice's certificate */
    Certificate *c = generate_certificate("Alice", kp1->public_key,
                                          t->private_key);

    /* Bob's u */
    rsa_int u = generate_random_u(c);

    /* Alice computes h(u) and v */
    rsa_int hu = rsa_int_hash(u);
    rsa_int v = crypt(hu, kp1->private_key, 0);

    /* Alice sends v to Bob
     * Bob encrypts v with Alice's public key,
     * and checks whether it is h(u)
     * */
    rsa_int r = crypt(v, kp1->public_key, 1); // E(e, v)
    assert(r == hu);

    /* Trace begins */
    trace("204-206:u: %d", u);
    trace("Sequence of bits for u");
    trace_int_bits(u, "u");
    trace("204-206:h(u): %d", hu);
    trace("Sequence of bits for h(u)");
    trace_int_bits(hu, "h(u)");
    trace("204-206:v: %d", v);
    trace("Sequence of bits for v");
    trace_int_bits(v, "v");
    trace("204-206:E(e, v): %d", r);
    trace("Sequence of bits for E(e, v)");
    trace_int_bits(r, "E(e, v)");
    /* Trace ends */

    destroy_certificate(c);
    destroy_keypair(kp1);
    destroy_keypair(t);
    return 0;
}
