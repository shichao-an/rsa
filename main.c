#include <stdlib.h> 
#include <stdio.h>
#include <time.h>
#include "keys.h"


int main()
{
    srand(time(NULL));
    printf("%d\n", generate_candidate());
    printf("%d\n", is_prime(113));
    return 0;
}
