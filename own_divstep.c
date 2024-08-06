#include <arm_neon.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define x63_1 0x8000000000000001
#define x62x61x60x_1 0x6000000000000007
#define inv_ans 0x4A5294A5294A5294

int degree(const poly64_t a) { return 63 - __builtin_clzll(a); }

int caldelta(const poly64_t f, const poly64_t g) {
  return degree(f) - degree(g);
}

void printbinary(const poly64_t s, const char ch) {
  printf("%c:", ch);
  poly64_t tmp = 0x8000000000000000;
  for (int i = 63; i >= 0; i--) {
    // printf("%d", (tmp & s) >> i);
    if ((tmp & s) >> i)
      printf("x^%d+ ", i);
    tmp = tmp >> 1;
  }
  printf("\n");
}

void printoriginalorder(const poly64_t s, const char ch) {
  printf("%c:", ch);
  poly64_t tmp = 0x8000000000000000;
  for (int i = 63; i >= 0; i--) {
    // printf("%d", (tmp & s) >> i);
    if ((tmp & s) >> i)
      printf("x^%d+ ", 63 - i);
    tmp = tmp >> 1;
  }
  printf("\n");
}

int main() {
  poly64_t f, g, u, v, q, r;
  f = x63_1;        // reverse order
  g = x62x61x60x_1; // reverse order
  u = 0x0000000000000001;
  v = 0x0000000000000000;
  q = 0x0000000000000000;
  r = 0x0000000000000001;

  poly64_t swap = 0x0000000000000000;
  int64_t delta = caldelta(f, g);
  int i = 0;
  for (i = 1; i <= /* (2 * 63) - 1*/ 62; i++) {
    swap = (delta > 0 && (g & 0x0000000000000001)) ? -1 : 0;
    delta = delta ^ ((delta ^ (-delta)) & swap);
    poly64_t mask = (f ^ g) & swap;
    f = f ^ mask;
    g = g ^ mask;
    mask = (q ^ u) & swap;
    q = q ^ mask;
    u = u ^ mask;
    mask = (r ^ v) & swap;
    v = v ^ mask;
    r = r ^ mask;

    delta += 1;
    poly64_t f0 = (f & 0x0000000000000001) ? -1 : 0;
    poly64_t g0 = (g & 0x0000000000000001) ? -1 : 0;
    g = (f0 & g) ^ (g0 & f);
    g = g >> 1;
    q = (f0 & q) ^ (g0 & u);
    r = (f0 & r) ^ (g0 & v);
    u = u << 1;
    v = v << 1;
  }

  printbinary(u, 'u');
  printbinary(v, 'v');
  printbinary(q, 'q');
  printbinary(r, 'r');
  printbinary(f, 'f');
  printbinary(g, 'g');
  // printoriginalorder(v, 'v');
  // printf("v(reverse in hex):%llx=%llx?\n%d\n", v, inv_ans, v == inv_ans);
}
