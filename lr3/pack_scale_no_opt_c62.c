// Эталонная программа для уплотнения РЛС сигнала (ядро С62)
#include "pack_type.h"
int c62_pack_scale_no_opt(const u8 *in, int n, int m, u8 *result) {
  int k;
  u8 max;
  int count = 0;
  while (n >= m) {
    max = 0;
    for (k = 0; k < m; k++) {
      u8 x = *in++;
      max = (x > max) ? x : max;
    }
    *result++ = max;
    n -= m;
    count++;
  }
  return count;
}