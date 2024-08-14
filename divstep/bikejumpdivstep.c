#include <arm_neon.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void printarr(poly64_t *s, int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        printf("%llx ", s[i]);
    }
    printf("\n");
}

void printx(poly64_t *s)
{
    poly64_t one = 0x0000000000000001;
    for (int i = 0; i < 193; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if ((s[i] >> j) & one)
                printf("x^%d + ", (12323 - (64 * i + j)));
        }
    }
    printf("\n");
}

void GetnLSB(poly64_t *s, int size, int n)
{
    poly64_t tmp[193];
    for (int i = 0; i < 193; i++)
    {
        tmp[i] = 0xFFFFFFFFFFFFFFFF;
    }
    rightshift(tmp, 12352 - n);
    for (int i = 0; i < 193; i++)
    {
        s[i] = s[i] & tmp[i];
    }
    for (int i = 192; i >= 0; i++)
    {
        printf("%llx ", s[i]);
    }
    printf("\n");
}

void rightshift(poly64_t *s, int n)
{
    for (int j = 0; j < n; j++)
    {
        poly64_t one     = 0x0000000000000001;
        int lsb_chk[193] = {0};
        for (int i = 1; i < 193; i++)
        {
            lsb_chk[i] = s[i] & one;
        }

        for (int i = 0; i < 193; i++)
        {
            s[i] = s[i] >> 1;
        }

        for (int i = 0; i < 192; i++)
        {
            if (lsb_chk[i + 1])
            {
                s[i] = s[i] ^ 0x8000000000000000;
            }
        }
    }
}

void leftshift(poly64_t *s, int n)
{
    for (int j = 0; j < n; j++)
    {
        poly64_t msb         = 0x8000000000000000;
        int64_t msb_chk[193] = {0};
        for (int i = 0; i < 192; i++)
        {
            msb_chk[i] = (s[i] & msb) ? 0x0000000000000001 : 0x0000000000000000;
        }

        for (int i = 0; i < 193; i++)
        {
            s[i] = s[i] << 1;
        }

        for (int i = 1; i < 193; i++)
        {
            if (msb_chk[i - 1])
            {
                s[i] = s[i] ^ 0x0000000000000001;
            }
        }
    }
}

void swapchk(poly64_t *swap, int64_t delta, poly64_t g)
{
    poly64_t one = 0x0000000000000001;
    // printf("in swap:%llx\n", g);
    poly64_t tmp = g & one;
    // printf("in swap:%llx\n", tmp);
    *swap        = (delta > 0 && (tmp)) ? -1 : 0;
    // printf("in swap:%llx\n", *swap);
}

void setmaskandswap(poly64_t *mask, poly64_t *f, poly64_t *g, poly64_t swap)
{
    for (int i = 0; i < 193; i++)
    {
        mask[i] = (f[i] ^ g[i]) & swap;
    }
    // printarr(mask, 193);
    for (int i = 0; i < 193; i++)
    {
        f[i] = f[i] ^ mask[i];
        g[i] = g[i] ^ mask[i];
    }
}

int main()
{
    poly64_t zero = 0x0000000000000000;
    poly64_t one  = 0x0000000000000001;
    poly64_t msb  = 0x8000000000000000;

    poly64_t f[193] = {0x0000000000000001};
    f[192]          = 0x0000000800000000;

    poly64_t g[193] = {0x000000000000000F};
    g[192]          = 0x0000000700000000;
    poly64_t u[193] = {one};
    poly64_t v[193] = {zero};
    poly64_t q[193] = {zero};
    poly64_t r[193] = {one};

    poly64_t swap      = zero;
    int64_t delta      = 1;
    poly64_t mask[193] = {zero};
    printf("Before:\n");
    printarr(f, 193);
    printarr(g, 193);

    for (int i = 0; i < 12323; i++)
    {
        swapchk(&swap, delta, g[0]);

        delta = delta ^ ((delta ^ (-delta)) & swap);

        setmaskandswap(mask, f, g, swap);

        setmaskandswap(mask, q, u, swap);
        setmaskandswap(mask, v, r, swap);
        delta += 1;
        poly64_t f0 = (f[0] & 0x0000000000000001) ? -1 : 0;
        poly64_t g0 = (g[0] & 0x0000000000000001) ? -1 : 0;
        for (int i = 0; i < 193; i++)
        {
            g[i] = (f0 & g[i]) ^ (g0 & f[i]);
        }
        rightshift(g, 1);
        for (int i = 0; i < 193; i++)
        {
            q[i] = (f0 & q[i]) ^ (g0 & u[i]);
        }
        for (int i = 0; i < 193; i++)
        {
            r[i] = (f0 & r[i]) ^ (g0 & v[i]);
        }
        leftshift(u, 1);
        leftshift(v, 1);
    }
    printf("After:\n");
    printarr(f, 193);
    printarr(g, 193);
}