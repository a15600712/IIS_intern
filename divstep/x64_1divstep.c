#include <arm_neon.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    poly64x2_t msb = {0x0000000000000000, 0x0000000000000001};
    poly64_t one   = 0x0000000000000001;
    poly64_t zero  = 0x0000000000000000;
    poly64x2_t f   = {one, one};
    poly64x2_t g   = {0xC000000000000001, zero};

    poly64x2_t u = {one, zero};
    poly64x2_t v = {zero, zero};
    poly64x2_t q = {zero, zero};
    poly64x2_t r = {one, zero};

    poly64x2_t swap = {zero, zero};

    int64_t delta = 1;

    for (int i = 0; i < 2 * 64 - 1; i++)
    {
        poly64_t tmp    = g[0] & one;
        swap            = (delta > 0 && (tmp)) ? vdupq_n_p64(-1) : vdupq_n_p64(0);
        delta           = delta ^ ((delta ^ (-delta)) & swap[0]);
        poly64x2_t mask = (f ^ g) & swap;
        f               = f ^ mask;
        g               = g ^ mask;
        mask            = (q ^ u) & swap;
        q               = q ^ mask;
        u               = u ^ mask;
        mask            = (r ^ v) & swap;
        v               = v ^ mask;
        r               = r ^ mask;

        delta += 1;
        poly64x2_t f0 = (f[0] & 0x0000000000000001) ? vdupq_n_p64(-1) : vdupq_n_p64(0);
        poly64x2_t g0 = (g[0] & 0x0000000000000001) ? vdupq_n_p64(-1) : vdupq_n_p64(0);
        g             = (f0 & g) ^ (g0 & f);

        int64_t chk_lsb = g[1] & 0x0000000000000001;
        g               = g >> 1;
        if (chk_lsb)
        {
            g[0] = g[0] ^ 0x8000000000000000;
        }
        q               = (f0 & q) ^ (g0 & u);
        r               = (f0 & r) ^ (g0 & v);
        int64_t msb_chk = u[0] & 0x8000000000000000;
        u               = u << 1;
        if (msb_chk == 0x8000000000000000)
        {
            u[1] = u[1] ^ 0x0000000000000001;
        }
        msb_chk = v[0] & 0x8000000000000000;
        v       = v << 1;
        if (msb_chk == 0x8000000000000000)
        {
            v[1] = v[1] ^ 0x0000000000000001;
        }
    }
    if (v[1] & one)
    {
        printf("1 + ");
    }
    poly64_t t = 0x8000000000000000;
    for (int i = 1; i <= 64; i++)
    {
        if (t & v[0])
            printf("x^%d + ", i);
        t = t >> 1;
    }

    // printf("%llx %llx\n", v[1], v[0]);
}
