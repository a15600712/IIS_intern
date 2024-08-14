#include "arm_neon.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

void leftshift(poly64_t *s, int n)
{
    for (int j = 0; j < n; j++)
    {
        poly64_t msb       = 0x8000000000000000;
        int64_t msb_chk[2] = {0};
        for (int i = 0; i < 2; i++)
        {
            msb_chk[i] = (s[i] & msb) ? 0x0000000000000001 : 0x0000000000000000;
        }

        for (int i = 0; i < 2; i++)
        {
            s[i] = s[i] << 1;
        }

        for (int i = 1; i < 2; i++)
        {
            if (msb_chk[i - 1])
            {
                s[i] = s[i] ^ 0x0000000000000001;
            }
        }
    }
}

void poly_mul(poly64_t result[], const poly64_t p1, const poly64_t p2)
{
    poly64_t one = 0x0000000000000001;

    for (int i = 0; i < 64; i++)
    {
        poly64_t tmp[2];
        tmp[0] = p2;

        if (one << i & p1)
        {
            leftshift(tmp, i);
            for (int i = 0; i < 2; i++)
            {
                result[i] = result[i] ^ tmp[i];
            }
        }
    }
}

int main()
{
    poly64_t p1 = 0x100000000200004b, p2 = 0x80000000100086;
    poly64_t result[2] = {0};
    poly_mul(result, p1, p2);
    for (int i = 1; i >= 0; i--)
    {
        printf("%llx ", result[i]);
    }
    printf("\n");
}
