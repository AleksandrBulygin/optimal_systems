// Эталонная программа алгоритма Герцля (ядро с62)
#include "goertzel_type.h"
void c62_goertzel_power_no_opt(s16 cos_Q15, const s16 *in, int n, s32 *power) {
  int sprev = 0;
  int sprev1 = 0;
  int s;
  int i;
  for (i = 0; i < n; i++) {
    int x = (in[i]) << 8;
    // Q0.15 << 8 => Q0.23
    s = 2 * (((sprev) >> 15) * cos_Q15) - sprev1 + x;
    // Q8.23 >> 15 => Q8.8
    // Q8.8 * Q0.15 = Q8.23
    sprev1 = sprev;
    sprev = s;
  }
  sprev = (sprev) >> 16;
  sprev1 = (sprev1) >> 16;
  // Q8.23 >> 16 => Q8.7
  *power = ((sprev1 * sprev1)) + ((sprev * sprev)) -
           (((sprev * cos_Q15) >> 14) * sprev1);
  // Q8.7 * Q8.7 => Q16.14
  // Q8.7 * Q0.15 >> 15 *2 = Q8.7 * Q0.15 >> 14 => Q8.7 * 2
}
