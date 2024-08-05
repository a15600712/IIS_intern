#include <arm_neon.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define inv_ans 0xDA

int degree(const poly8_t a)
{
    return 7 - __builtin_clzll(a);
}

int caldelta(const poly8_t f, const poly8_t g)
{
    return degree(f) - degree(g);
}
void printbinary(const poly8_t s, const char ch)
{
    printf("%c:", ch);
    poly8_t tmp = 0x80;
    for (int i = 7; i >= 0; i--)
    {
        // printf("%d", (tmp & s) >> i);
        if ((tmp & s) >> i)
            printf("x^%d+ ", i);
        tmp = tmp >> 1;
    }
    printf("\n");
}
void printoriginalorder(const poly8_t s, const char ch)
{
    printf("%c:", ch);
    poly8_t tmp = 0x80;
    for (int i = 7; i >= 0; i--)
    {
        // printf("%d", (tmp & s) >> i);
        if ((tmp & s) >> i)
            printf("x^%d+ ", 7 - i);
        tmp = tmp >> 1;
    }
    printf("\n");
}
int main()
{
    poly8_t f, g, u, v, q, r;
    f            = 0x81;  // reverse order of x^7 + 1
    g            = 0x61;  // reverse order of x^6+x+1
    // printf("%x\n", f);
    // printf("%x\n", g);
    u            = 0x01;
    v            = 0x00;
    q            = 0x00;
    r            = 0x01;
    // poly8_t delta = caldelta(f, g); use this will error
    int8_t delta = caldelta(f, g);
    // printbinary(f, 'f');
    // printbinary(g, 'g');
    // printbinary(u, 'u');
    // printbinary(v, 'v');
    // printbinary(q, 'q');
    // printbinary(r, 'r');
    poly8_t swap = 0x00;
    int i        = 0;
    for (i = 1; i <= (2 * 7) - 1; i++)
    {
        swap         = (delta > 0 && (g & 0x01)) ? -1 : 0;
        delta        = delta ^ ((delta ^ (-delta)) & swap);
        poly8_t mask = (f ^ g) & swap;
        f            = f ^ mask;
        g            = g ^ mask;
        mask         = (q ^ u) & swap;
        q            = q ^ mask;
        u            = u ^ mask;
        mask         = (r ^ v) & swap;
        v            = v ^ mask;
        r            = r ^ mask;

        delta += 1;
        poly8_t f0 = (f & 0x01) ? -1 : 0;
        poly8_t g0 = (g & 0x01) ? -1 : 0;
        g          = (f0 & g) ^ (g0 & f);
        g          = g >> 1;
        q          = (f0 & q) ^ (g0 & u);
        r          = (f0 & r) ^ (g0 & v);
        u          = u << 1;
        v          = v << 1;
    }
    printoriginalorder(v, 'v');
    printf("v(reverse in hex):%x=%x?\n", v, inv_ans);
}
