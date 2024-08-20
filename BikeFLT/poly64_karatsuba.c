#include "arm_neon.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

int main()
{
    poly64x2_t a = {0x7001020900000464};
    poly64x2_t b = {0xAF00EBC012641004};

    poly128_t tmp = vmull_p64(a, b);
    poly64x2_t result
}