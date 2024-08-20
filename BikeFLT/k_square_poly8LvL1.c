#include "arm_neon.h"
#include "math.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

#define r 12323

int16_t map[r] = {0};

// calculate a^(2^k)
void k_square(poly8_t *result, poly8_t *a, int k)
{
    for (int i = 0; i < r; i++)
    {
        map[i] = (i * (int)(pow(2, k))) % r;
    }
    for (int i = 0; i < 1541; i++)
    {
        poly8_t b = a[i];
        for (int j = 0; j < 8; j++)
        {
            int bit = (b >> j) & 1;
            int pos = map[i * 8 + j];
            result[pos / 8] |= (bit << (pos % 8));
        }
    }
}

void printbin(poly8_t *f)
{
    poly8_t msb = 0x80;

    for (int i = 1540; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
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

int main()
{
    poly8_t f[1541]      = {0xF9};
    f[1540]              = 0x07;
    f[1539]              = 0xC8;
    poly8_t result[1541] = {0};
    k_square(result, f, 10);
    // for (int i = 1540; i >= 0; i--)
    // {
    //     printf("%02x", result[i]);
    // }
    printbin(result);
    printf("\n");
}