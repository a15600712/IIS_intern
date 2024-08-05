#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// For N = 5, (1 + x + x^4)^(−1) = 1 + x2 + x3 in R2
#define degree 65

void shift_right(bool *src, int n)
{
	for (int i = degree - 1; i >= n; i--)
	{
		src[i] = src[i - n];
	}
	for (int i = 0; i < n; i++)
	{
		src[i] = 0;
	}
}

void shift_left(bool *src, int n)
{
	for (int i = 0; i < degree - n; i++)
	{
		src[i] = src[i + n];
	}
	for (int i = degree - n; i < degree; i++)
	{
		src[i] = 0;
	}
}

void xor
        (bool *src1, bool *src2) {
	        for (int i = 0; i < degree; i++)
	        {
		        src1[i] = src1[i] ^ src2[i];
	        }
        }

        void and
    (bool *src1, bool *src2)
{
	for (int i = 0; i < degree; i++)
	{
		src1[i] = src1[i] & src2[i];
	}
}

void xor_int(bool *src1, bool k)
{
	for (int i = 0; i < degree; i++)
	{
		src1[i] = src1[i] ^ k;
	}
}

void swap(bool *src1, bool *src2, bool whether)
{
	bool mask[degree];
	bool temp2[degree];
	create(src1, mask);
	create(src2, temp2);
	xor(mask, temp2);
	mul_int(mask, whether);
	xor(src1, mask);
	xor(src2, mask);
}

void mul_int(bool *src1, bool k)
{
	for (int i = 0; i < degree; i++)
	{
		src1[i] = src1[i] & k;
	}
}

void create(bool *src1, bool *dest)
{
	for (int i = 0; i < degree; i++)
	{
		dest[i] = src1[i];
	}
}

void axe(bool *src1, bool f0, bool *src2, int n)
{
	bool temp1[degree];
	bool temp2[degree];
	create(src1, temp1);
	create(src2, temp2);
	mul_int(temp1, f0);
	mul_int(temp2, n);
	xor(temp1, temp2);
	create(temp1, src1);
}

void reverse(bool *src1)
{
	for (int i = 0; i < degree / 2; i++)
	{
		bool temp            = src1[i];
		src1[i]              = src1[degree - i - 1];
		src1[degree - i - 1] = temp;
	}
}

int main()
{
	bool g[degree] = {
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0
	}; // inverse order
	bool divisor[degree] = { 0 };
	divisor[0]           = 1;
	divisor[degree - 1]  = 1;
	bool u[degree]       = { 0 };
	u[0]                 = 1;
	bool v[degree]       = { 0 };
	bool q[degree]       = { 0 };
	bool r[degree]       = { 0 };
	r[0]                 = 1;

	int delta = 1;
	for (int times = 0; times < 2 * (degree - 1) - 1; times++)
	{
		bool whether_swap = (delta > 0 && g[0] != 0);

		swap(g, divisor, whether_swap);
		swap(u, q, whether_swap);
		swap(v, r, whether_swap);
		int intswap = (int)whether_swap;
		delta       = delta ^ ((delta ^ (-delta)) & (-intswap));

		delta += 1;
		int f0 = divisor[0];
		int g0 = g[0];
		axe(g, f0, divisor, g0); // print temp
		// print temp
		shift_left(g, 1);

		axe(q, f0, u, g0);
		axe(r, f0, v, g0);
		shift_right(u, 1);
		shift_right(v, 1);
	}

	printf("v: using for stop\n");
	for (int i = degree - 1; i > 0; i--)
	{
		if (v[i] != 0)
		{
			printf("x^(%d) ", degree - 1 - i);
			printf("+ ");
		}
	}
	printf("\n");

	return 0;
}