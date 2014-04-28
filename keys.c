#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
        trace("Random Number %d: %d\n", i + 1, r);
        lsb = r & 1;
        trace("Extracted Bit: %d\n", lsb);
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
        printf("c: %d\n", c);
        if (!primality_test(c, n)) return 0;
        i++;
    }
    return 1;
}


rsa_int generate_prime()
{
    rsa_int prime = generate_candidate();

    return prime;
}
