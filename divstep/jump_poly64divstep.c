#include <arm_neon.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define x63_1        0x8000000000000001
#define x62x61x60x_1 0x6000000000000007
#define inv_ans      0x4A5294A5294A5294

struct Matrix
{
    poly64_t u, v, q, r;
};

int degree(const poly64_t a)
{
    return 63 - __builtin_clzll(a);
}

int caldelta(const poly64_t f, const poly64_t g)
{
    return degree(f) - degree(g);
}

void printbinary(const poly64_t s, const char ch)
{
    printf("%c:", ch);
    poly64_t tmp = 0x8000000000000000;
    for (int i = 63; i >= 0; i--)
    {
        // printf("%d", (tmp & s) >> i);
        if ((tmp & s) >> i)
            printf("x^%d+ ", i);
        tmp = tmp >> 1;
    }
    printf("\n");
}

void printoriginalorder(const poly64_t s, const char ch)
{
    printf("%c:", ch);
    poly64_t tmp = 0x8000000000000000;
    for (int i = 63; i >= 0; i--)
    {
        // printf("%d", (tmp & s) >> i);
        if ((tmp & s) >> i)
            printf("x^%d+ ", 63 - i);
        tmp = tmp >> 1;
    }
    printf("\n");
}

int main()
{
    poly64_t f, g, u, v, q, r, ori_f, ori_g;

    f     = x63_1;  // reverse order
    ori_f = f;
    g     = x62x61x60x_1;  // reverse order
    ori_g = g;

    f = f & 0x7FFFFFFFFFFFFFFF;
    g = g & 0x7FFFFFFFFFFFFFFF;

    u = 0x0000000000000001;
    v = 0x0000000000000000;
    q = 0x0000000000000000;
    r = 0x0000000000000001;

    int n = 2 * 63 - 1;
    int j = (n / 2) + 1;
    // printf("j:%d\n", j);
    int k = n - j;
    // printf("k:%d\n", k);

    poly64_t swap = 0x0000000000000000;
    int64_t delta = 1;
    int i         = 0;
    for (i = 1; i <= j; i++)
    {
        swap          = (delta > 0 && (g & 0x0000000000000001)) ? -1 : 0;
        delta         = delta ^ ((delta ^ (-delta)) & swap);
        poly64_t mask = (f ^ g) & swap;
        f             = f ^ mask;
        g             = g ^ mask;
        mask          = (q ^ u) & swap;
        q             = q ^ mask;
        u             = u ^ mask;
        mask          = (r ^ v) & swap;
        v             = v ^ mask;
        r             = r ^ mask;

        delta += 1;
        poly64_t f0 = (f & 0x0000000000000001) ? -1 : 0;
        poly64_t g0 = (g & 0x0000000000000001) ? -1 : 0;
        g           = (f0 & g) ^ (g0 & f);
        g           = g >> 1;
        q           = (f0 & q) ^ (g0 & u);
        r           = (f0 & r) ^ (g0 & v);
        u           = u << 1;
        v           = v << 1;
    }

    struct Matrix m1;

    m1.u = u;
    m1.v = v;
    m1.q = q;
    m1.r = r;

    poly64_t ori_fh = ori_f >> j;
    poly64_t ori_gh = ori_g >> j;

    poly64_t new_f = (poly64_t)(vmull_p64(u, ori_fh)) ^ (poly64_t)(vmull_p64(v, ori_gh));
    poly64_t new_g = (poly64_t)(vmull_p64(q, ori_fh)) ^ (poly64_t)(vmull_p64(r, ori_gh));
    new_f          = new_f ^ f;
    new_g          = new_g ^ g;

    u    = 0x0000000000000001;
    v    = 0x0000000000000000;
    q    = 0x0000000000000000;
    r    = 0x0000000000000001;
    swap = 0x0000000000000000;
    for (i = 1; i <= k; i++)
    {
        swap          = (delta > 0 && (new_g & 0x0000000000000001)) ? -1 : 0;
        delta         = delta ^ ((delta ^ (-delta)) & swap);
        poly64_t mask = (new_f ^ new_g) & swap;
        new_f         = new_f ^ mask;
        new_g         = new_g ^ mask;
        mask          = (q ^ u) & swap;
        q             = q ^ mask;
        u             = u ^ mask;
        mask          = (r ^ v) & swap;
        v             = v ^ mask;
        r             = r ^ mask;

        delta += 1;
        poly64_t new_f0 = (new_f & 0x0000000000000001) ? -1 : 0;
        poly64_t new_g0 = (new_g & 0x0000000000000001) ? -1 : 0;
        new_g           = (new_f0 & new_g) ^ (new_g0 & new_f);
        new_g           = new_g >> 1;
        q               = (new_f0 & q) ^ (new_g0 & u);
        r               = (new_f0 & r) ^ (new_g0 & v);
        u               = u << 1;
        v               = v << 1;
    }
    printbinary(v, 'v');
    printbinary(u, 'u');
    printbinary(q, 'q');
    printbinary(r, 'r');
    poly128_t tmp1  = vmull_p64(u, m1.v);
    poly128_t tmp2  = vmull_p64(m1.r, v);
    poly64_t result = (poly64_t)tmp1 ^ (poly64_t)tmp2;
    // printf("%llx\n", result);
    printf("%llx\n", result);
}
