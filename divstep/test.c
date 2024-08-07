#include <arm_neon.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void leftshift(poly64_t *s, int n)
{
    for (int j = 0; j < n; j++)
    {
        poly64_t msb        = 0x8000000000000000;
        int64_t msb_chk[30] = {0};
        for (int i = 0; i < 29; i++)
        {
            msb_chk[i] = (s[i] & msb) ? 0x0000000000000001 : 0x0000000000000000;
        }

        for (int i = 0; i < 30; i++)
        {
            s[i] = s[i] << 1;
        }

        for (int i = 1; i < 30; i++)
        {
            if (msb_chk[i - 1])
            {
                s[i] = s[i] ^ 0x0000000000000001;
            }
        }
    }
}

int main()
{
    poly64_t t[30] = {0x8ffffffffffffff1, 0x0000000000000000, 0x8ffffffffffffff1};
    for (int i = 29; i >= 0; i--)
    {
        printf("%llx ", t[i]);
    }
    printf("\n");
    leftshift(t, 128);
    for (int i = 29; i >= 0; i--)
    {
        printf("%llx ", t[i]);
    }
    printf("\n");
}