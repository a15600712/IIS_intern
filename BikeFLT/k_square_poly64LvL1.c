#include "arm_neon.h"
#include "math.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

#define r 12323

int64_t map[r] = {0};

// calculate a^(2^k)
void k_square(poly64_t *result, poly64_t *a, int k)
{
    for (int i = 0; i < r; i++)
    {
        map[i] = (i * (int64_t)(pow(2, k))) % r;
    }
    for (int i = 0; i < 193; i++)
    {
        poly64_t b = a[i];
        for (int j = 0; j < 64; j++)
        {
            uint64_t bit = (b >> j) & 1;
            uint64_t pos = map[i * 64 + j];
            result[pos / 64] |= (bit << (pos % 64));
        }
    }
}

void printbin(poly64_t *f)
{
    poly64_t msb = 0x8000000000000000;

    for (int i = 192; i >= 0; i--)
    {
        for (int j = 0; j < 64; j++)
        {
            if ((msb >> j) & f[i])
            {
                printf("1");
            }
            else
            {
                printf("0");
            }
        }
    }
}

void printx(poly64_t *f)
{
    poly64_t msb = 0x0000000000000001;

    for (int i = 192; i >= 0; i--)
    {
        for (int j = 63; j >= 0; j--)
        {
            if ((msb << j) & f[i])
            {
                printf("x^%d +", ((i * 64) + j));
            }
        }
    }
}

int main()
{
    poly64_t f[193]      = {0x0000000000000000};
    poly64_t result[193] = {0};

    f[0]   = 0x00000000000000F9;
    f[192] = 0x00000007C8000000;
    k_square(result, f, 10);
    // printx(f);
    // printbin(result);
    // printf("\n");
    printx(result);
    printf("\n");
}