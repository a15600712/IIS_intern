#include <arm_neon.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    poly64_t test[2]   = {0xF0000000000000FF, 0xF00000000000000F};
    poly64_t result[4] = {0};
    poly64_t carry     = 0x0000000000000000;
    for (int i = 0; i < 2; i++)
    {
        poly128_t temp    = vmull_p64(test[i], test[i]);
        result[2 * i]     = temp;
        result[2 * i + 1] = temp >> 64;
    }
    for (int i = 3; i >= 0; i--)
    {
        printf("%llx ", result[i]);
    }
    printf("\n");
}