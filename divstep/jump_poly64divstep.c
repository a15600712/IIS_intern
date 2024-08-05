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
    u     = 0x0000000000000001;
    v     = 0x0000000000000000;
    q     = 0x0000000000000000;
    r     = 0x0000000000000001;

    poly64_t swap = 0x0000000000000000;
    int64_t delta = caldelta(f, g);
    int j, k;
    j = (2 * 63 - 1) / 2;
    k = (2 * 63 - 1) - j;
    for (int i = 0; i < j; i++)
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
    poly64_t new_f, new_g;
    ori_f = ori_f >> j;
    ori_g = ori_g >> j;
    struct Matrix M1;
    M1.u = u;
    M1.q = q;
    M1.r = r;
    M1.v = v;

    // printbinary(u, 'u');
    // printbinary(f, 'f');
    poly64_t tmp1 = (uint64_t)u * (uint64_t)f;
    // printbinary(tmp1, '1');
    poly64_t tmp2 = (uint64_t)v * (uint64_t)g;

    new_f = tmp1 + tmp2 + f;
    // tmp1  = vmull_p64(q, f);
    // tmp2  = vmull_p64(r, g);
    tmp1  = (uint64_t)q * (uint64_t)f;
    tmp2  = (uint64_t)r * (uint64_t)g;
    new_g = tmp1 + tmp2 + g;

    printbinary(new_f, 'f');
    printbinary(new_g, 'g');
    u = 0x0000000000000001;
    v = 0x0000000000000000;
    q = 0x0000000000000000;
    r = 0x0000000000000001;
    for (int i = 0; i < k; i++)
    {
        swap          = (delta > 0 && (g & 0x0000000000000001)) ? -1 : 0;
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
}
