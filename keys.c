#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "keys.h"
#include "trace.h"

static rsa_int test_values[NUM_TESTS];

/* `generate_candidate` generates a random rsa_int number */
rsa_int generate_candidate()
{
    rsa_int n = 1;
    rsa_int r;
    int i, lsb;
    n <<= (NUM_BITS - 1);
    n |= 1;
    r = rand();
    for (i = 0; i < NUM_BITS - 2; i ++) {
        r = rand();
        trace("97-100:Random Number %d: %d", i + 1, r);
        lsb = r & 1;
        trace("97-100:Extracted Bit: %d", lsb);
        lsb <<= i + 1;
        n |= lsb;
    }
    return n;

}

/* Miller-Rabin primality test
 *
 */
int primality_test(rsa_int a, rsa_int n)
{
    rsa_int x = n - 1;
    rsa_int y = 1, z;
    int i, cb;
    for (i = NUM_BITS - 1; i >= 0; i--) {
        z = y;
        y = y * y % n;
        if (y == 1 && z != 1 && z != n - 1)
            return 0;
        // Get bit of `x` at `i`
        cb = ((x & (1 << i)) != 0);
        if (cb == 1)
            y = y * a % n;
    }
    return (y == 1);
}

/* `is_prime` determines whether a candidate is probably prime
 * by performing Miller–Rabin primality test
 *
 * By using array static `test_values`, `is_prime` makes sure it
 * does not perform primality test on the already-passed values
 * and at most test `NUM_TESTS` times
 */
int is_prime(rsa_int n)
{
    int i = 0, j, tested;
    rsa_int c;
    while (i < NUM_TESTS) {
        tested = 0;
        c = (rsa_int) rand() % (int) n;
        if (c == 0) continue;
        test_values[i] = c;
        for (j = 0; j < i; j++) {
            if (test_values[j] == c) {
                tested = 1;
                i++;
                break;
            }
        }
        if (tested) continue;
        //printf("c: %d\n", c);
        if (!primality_test(c, n)) return 0;
        i++;
    }
    return 1;
}

/* `generate_prime` generates a prime number after performing primality
 * test
 * For completeness, this function makes sure that `generate_candidate`
 * generates a non-prime number to trace
 */
rsa_int generate_prime()
{
    rsa_int prime = generate_candidate();
    while (is_prime(prime))
        prime = generate_candidate();
    trace("112-117:Not Prime: %d", prime);
    while (!is_prime(prime))
        prime = generate_candidate();
    trace("112-117:Perhaps Prime: %d", prime);
    return prime;
}

/* `get_inverse` calculates the multiplicative inverse of `a` modulo `n`
 * using the Extended Euclidean algorithm
 */
rsa_int get_inverse(rsa_int a, rsa_int n)
{
    rsa_int s = 0, old_s = 1, t = 1, old_t = 0;
    rsa_int r = a, old_r = n;
    rsa_int tr, ts, tt, q;  // Temporary variables
    while (r != 0) {
        tr = r;
        ts = s;
        tt = t;
        q = old_r / r; 
        r = old_r - q * tr;
        s = old_s - q * ts;
        t = old_t - q * tt;
        old_r = tr;
        old_s = ts;
        old_t = tt;
    }
    if (old_r > 1) {
        trace("133-142:Invalid e: %d", a);
        return -1;  // gcd(a,n) != 1, thus a is not invertible modulo n,
                    // i.e. a and n are not relatively prime
    }
    if (old_t < 0)
        old_t += n;
    return old_t;
}

/* `generate_key` generates a RSA key
 *
 */
Key *generate_key(rsa_int k, rsa_int n)
{
    Key *key = (Key *)malloc(sizeof(Key));
    key->n = n;
    key->k = k;
    return key;
}

/* `generate_keypair` generates an RSA keypair (public_key, private_key)
 *
 */
Keypair *generate_keypair()
{
    rsa_int p, q, n, phi;
    rsa_int e = 3, d;
    Keypair *keypair;
    p = generate_prime();
    do {
        q = generate_prime();
    } while (q == p);
    n = p * q;
    phi = (p - 1) * (q - 1);
    while (get_inverse(e, phi) == -1) {
        e++;
    }
    d = get_inverse(e, phi);
    trace("143-144:d: %d", d);
    trace("147-148:p,q,n,e,d: %d,%d,%d,%d,%d", p, q, n, e, d);
    keypair = (Keypair *)malloc(sizeof(Keypair));
    keypair->public_key = generate_key(e, n);
    keypair->private_key = generate_key(d, n);
    return keypair;
}

/* Free the keypair and wrapped keys
 */
void destroy_keypair(Keypair *keypair)
{
    free(keypair->public_key);
    free(keypair->private_key);
    free(keypair);
}

/* Fast exponentiation a^x mod n
 */
rsa_int fast_exp(rsa_int a, rsa_int x, rsa_int n)
{
    rsa_int y = 1;
    int i, cb;
    int xx = x, k = -1;
    while (xx != 0) {
        xx >>= 1;
        k++;    
    }
    /* x_k, x_k-1, ..., x_0 */
    for (i = k; i >= 0; i--) {
        y = y * y % n;
        // Get bit of `x` at `i`
        cb = ((x & (1 << i)) != 0);
        if (cb == 1)
            y = y * a % n;
    }
    return y;
}

/* Encrypt or decrypt using fast exponentiation
 */
rsa_int crypt(rsa_int m, Key *key)
{
    rsa_int n, k;
    n = key->n;
    k = key->k;
    return fast_exp(m, k, n);
}
