#include "math.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

#define LENGTH 64

void leftshift(bool *source, int shift)
{
    int tmp[LENGTH] = {0};
    for (int i = 0; i < LENGTH; i++)
    {
        if (i + shift <= LENGTH - 1)
        {
            source[i] = source[i + shift];
        }
        else
        {
            source[i] = 0;
        }
    }
}

void rightshift(bool *source, int shift)
{
    int tmp[LENGTH] = {0};
    for (int i = LENGTH - 1; i >= 0; i--)
    {
        if (i - shift >= 0)
        {
            source[i] = source[i - shift];
        }
        else
        {
            source[i] = 0;
        }
    }
}

int caldelta(bool f[], bool g[])
{
    int f_degree = 0;
    for (int i = LENGTH - 1; i >= 0; i--)
    {
        if (f[i] == 1)
        {
            f_degree = i;
            break;
        }
    }
    for (int i = LENGTH - 1; i >= 0; i--)
    {
        if (g[i] == 1)
        {
            return f_degree - i;
        }
    }
}
/*
step(f, g, f0, g0);
leftshift(g, 1);
step(u, q, f0, g0);
step(v, r, f0, g0);
*/
void step(bool f[], bool g[], bool f0, bool g0)
{
    bool tmp[LENGTH] = {0};
    for (int i = 0; i < LENGTH; i++)
    {
        tmp[i] = (f0 & g[i]) ^ (g0 & f[i]);
    }

    for (int i = 0; i < LENGTH - 1; i++)
    {
        g[i] = tmp[i];
    }
}

void swap(bool f[], bool g[], bool s)
{
    bool msk[LENGTH] = {0};
    for (int i = 0; i < LENGTH; i++)
    {
        msk[i] = (f[i] ^ g[i]) & s;
    }
    for (int i = 0; i < LENGTH; i++)
    {
        f[i] = (f[i] ^ msk[i]);
    }
    for (int i = 0; i < LENGTH; i++)
    {
        g[i] = (g[i] ^ msk[i]);
    }
}

void printarr(bool arr[])
{
    for (int i = 0; i < LENGTH; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n------------------------\n");
}

int main()
{
    bool g[LENGTH] = {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1};

    bool f[LENGTH] = {0};
    bool u[LENGTH] = {0};
    bool v[LENGTH] = {0};
    bool q[LENGTH] = {0};
    bool r[LENGTH] = {0};
    f[0]           = 1;
    f[LENGTH - 1]  = 1;
    u[0]           = 1;
    r[0]           = 1;
    int delta      = caldelta(f, g);
    bool s         = false;
    for (int i = 1; i <= 2 * (LENGTH - 1) - 1; i++)
    {
        s = (delta > 0 && g[0] != 0);

        swap(f, g, s);

        swap(q, u, s);

        swap(v, r, s);

        int intswap = (int)s;
        delta       = delta ^ ((delta ^ (-delta)) & -intswap);
        delta += 1;
        bool f0 = f[0];
        bool g0 = g[0];
        step(f, g, f0, g0);
        leftshift(g, 1);
        step(u, q, f0, g0);
        step(v, r, f0, g0);
        rightshift(u, 1);
        rightshift(v, 1);

        // printf("%d:\n%d\n", i, delta);
        // printf("u:");
        // printarr(u);
        // printf("v:");
        // printarr(v);
        // printf("q:");
        // printarr(q);
        // printf("r:");
        // printarr(r);
    }
    // printf("delta:%d\n", delta);
    // printf("f:");
    // printarr(f);
    // printf("g:");
    // // printarr(g);
    // printf("u:");
    // printarr(u);
    // printf("v:");
    // printarr(v);
    // printf("q:");
    // printarr(q);
    // printf("r:");
    // printarr(r);
    for (int i = 0; i < LENGTH; i++)
    {
        if (v[i] == 1)
        {
            printf("x^%d + ", LENGTH - i - 1);
        }
    }
    printf("\n");
}
