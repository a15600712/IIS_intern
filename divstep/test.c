#include <arm_neon.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    poly64x2_t one = {0x0000000000000001, 0x0000000000000000};

    poly64x2_t f = {0x0000000000000001, 0x0000000000000001};
    poly64x2_t g = {0xC000000000000001, 0x0000000000000001};

    poly64x2_t u = {0x8000000000000001, 0x0000000000000000};
    poly64x2_t v = {0x0000000000000000, 0x0000000000000000};
    poly64x2_t q = {0x0000000000000000, 0x0000000000000000};
    poly64x2_t r = {0x0000000000000001, 0x0000000000000000};

    poly64x2_t swap = {0x0000000000000000, 0x0000000000000000};
    int64_t delta   = 1;
    swap            = vdupq_n_p64(-1);
    poly64x2_t tmp  = g & one;
    printf("%llx %llx\n", u[1], u[0]);
    int64_t msb_chk = u[0] & 0x8000000000000000;
    u               = u << 1;
    if (msb_chk)
    {
        u[1] = u[1] ^ 0x0000000000000001;
    }
    printf("%llx %llx\n", u[1], u[0]);
}