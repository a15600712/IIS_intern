#include <arm_neon.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define x127_1       0x80000000000000000000000000000001
#define x62x61x60x_1 0x6000000000000007
#define inv_ans      0x4A5294A5294A5294

int degree(const poly128_t a)
{
    return 127 - __builtin_clzll(a);
}

int caldelta(const poly128_t f, const poly128_t g)
{
    return degree(f) - degree(g);
}

void printbinary(const poly128_t s, const char ch)
{
    printf("%c:", ch);
    poly128_t tmp = 0x80000000000000000000000000000000;
    for (int i = 127; i >= 0; i--)
    {
        // printf("%d", (tmp & s) >> i);
        if ((tmp & s) >> i)
            printf("x^%d+ ", i);
        tmp = tmp >> 1;
    }
    printf("\n");
}

void printoriginalorder(const poly128_t s, const char ch)
{
    printf("%c:", ch);
    poly128_t tmp = 0x80000000000000000000000000000000;
    for (int i = 127; i >= 0; i--)
    {
        // printf("%d", (tmp & s) >> i);
        if ((tmp & s) >> i)
            printf("x^%d+ ", 127 - i);
        tmp = tmp >> 1;
    }
    printf("\n");
}

int main()
{
    poly128_t f, g, u, v, q, r;
    f = x127_1;        // reverse order
    g = x62x61x60x_1;  // reverse order
    u = 0x00000000000000000000000000000001;
    v = 0x00000000000000000000000000000000;
    q = 0x00000000000000000000000000000000;
    r = 0x00000000000000000000000000000001;

    poly128_t swap = 0x00000000000000000000000000000000;
    int64_t delta  = caldelta(f, g);
    int i          = 0;
    for (i = 1; i <= (2 * 127) - 1; i++)
    {
        swap           = (delta > 0 && (g & 0x00000000000000000000000000000001)) ? -1 : 0;
        delta          = delta ^ ((delta ^ (-delta)) & swap);
        poly128_t mask = (f ^ g) & swap;
        f              = f ^ mask;
        g              = g ^ mask;
        mask           = (q ^ u) & swap;
        q              = q ^ mask;
        u              = u ^ mask;
        mask           = (r ^ v) & swap;
        v              = v ^ mask;
        r              = r ^ mask;

        delta += 1;
        poly128_t f0 = (f & 0x00000000000000000000000000000001) ? -1 : 0;
        poly128_t g0 = (g & 0x00000000000000000000000000000001) ? -1 : 0;
        g            = (f0 & g) ^ (g0 & f);
        g            = g >> 1;
        q            = (f0 & q) ^ (g0 & u);
        r            = (f0 & r) ^ (g0 & v);
        u            = u << 1;
        v            = v << 1;
    }
    printoriginalorder(v, 'v');
    printf("v(reverse in hex):%llx=%llx?\n%d\n", v, inv_ans, v == inv_ans);
}
