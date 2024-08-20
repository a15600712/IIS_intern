#include "arm_neon.h"
#include "stdio.h"
#include "stdlib.h"

void squaring_mod(poly64_t *result)
{
    // printf("%llx\n", *result);
    poly128_t temp = vmull_p64(*result, *result);
    *result        = (poly64_t)temp;
    *result        = (poly64_t)(*result ^ (poly64_t)(temp >> 64));
}

void repeated_sqr(poly64_t *result, poly64_t f, int num_sqrs)
{
    poly64_t a = f;
    for (int i = 0; i < num_sqrs; i++)
    {
        squaring_mod(&a);
    }
    *result = a;
}

int main()
{
    poly64_t test   = 0x00000000000000BF;
    poly64_t result = 0x0000000000000000;
    repeated_sqr(&result, test, 5);
    printf("%llx\n", result);
}