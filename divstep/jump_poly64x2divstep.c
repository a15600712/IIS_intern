#include <arm_neon.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct matrix
{
    int64_t delta;
    poly64_t f, g;
    poly64_t u, v, q, r;
};

struct matrix divstep(int64_t n, int64_t delta, poly64_t f, poly64_t g)
{
    uint64_t delta;
    struct matrix m;

    m.u           = 0x0000000000000001;
    m.v           = 0x0000000000000000;
    m.q           = 0x0000000000000000;
    m.r           = 0x0000000000000001;
    poly64_t swap = 0x0000000000000000;
    int64_t delta = 1;

    for (int i = 0; i < n; i++)
    {
        swap          = (delta > 0 && (g & 0x0000000000000001)) ? -1 : 0;
        delta         = delta ^ ((delta ^ (-delta)) & swap);
        poly64_t mask = (f ^ g) & swap;
        f             = f ^ mask;
        g             = g ^ mask;
        mask          = (m.q ^ m.u) & swap;
        m.q           = m.q ^ mask;
        m.u           = m.u ^ mask;
        mask          = (m.r ^ m.v) & swap;
        m.v           = m.v ^ mask;
        m.r           = m.r ^ mask;

        delta += 1;
        poly64_t f0 = (f & 0x0000000000000001) ? -1 : 0;
        poly64_t g0 = (g & 0x0000000000000001) ? -1 : 0;
        g           = (f0 & g) ^ (g0 & f);
        g           = g >> 1;
        m.q         = (f0 & m.q) ^ (g0 & m.u);
        m.r         = (f0 & m.r) ^ (g0 & m.v);
        m.u         = m.u << 1;
        m.v         = m.v << 1;
    }
    return m;
}

struct matrix jumpdivstep()
{
}

int main()
{
    poly64x2_t f = {0x0000000000000001, 0x8000000000000000};
    poly64x2_t g = {0x000000000000000F, 0x7C00000000000000};

    struct matrix *m1, *m2;

    int64_t n = (2 * 127) - 1;
    int64_t j, k;
    __int128_t delta;
    delta = -1;
    j     = n / 2;
    k     = n - j;
    divstep(j, delta, f, g);
}