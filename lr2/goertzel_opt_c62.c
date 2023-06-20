// Оптимизированная программа алгоритма Герцля (ядро с62)
#include "goertzel_type.h"
void c62_goertzel_power_opt_1(s16 cos_Q15, const s16 *in, int n, s32 *power) {
  int sprev = 0;
  int sprev1 = 0;
  int s;
  int i;
#pragma UNROLL(2)
  for (i = 0; i < n; i++) {
    int x = (in[i]) << 8;
    s = 2 * (((sprev) >> 15) * cos_Q15) - sprev1 + x;
    sprev1 = sprev;
    sprev = s;
  }
  sprev = (sprev) >> 16;
  sprev1 = (sprev1) >> 16;
  *power =
      (sprev1 * sprev1 + sprev * sprev - ((sprev * cos_Q15) >> 14) * sprev1);
}
void c62_goertzel_power_opt_2(s16 cos_Q15, const s16 *in, int n, s32 *power) {
  int sprev = 0;
  int sprev1 = 0;
  int i, s;
#pragma UNROLL(2)
  for (i = 0; i < n; i++) {
    int x = _sshl(in[i], 8);
    s = _sadd(_ssub(x, sprev1), _smpy((sprev) >> 15, cos_Q15));
    sprev1 = sprev;
    sprev = s;
  }
  sprev = (sprev) >> 16;
  sprev1 = (sprev1) >> 16;
  *power = (sprev1 * sprev1 + sprev * sprev -
            (_smpy(sprev, cos_Q15) >> 15) * sprev1);
}
void c62_goertzel_power_opt_3(const s16 *cos_Q15, const s16 *in, int n,
                              s32 *power) {
  int s[6], i, k, sprev[6], sprev1[6];
  int cosx[6];
  for (k = 0; k < 6; k++) {
    cosx[k] = cos_Q15[k];
    sprev[k] = 0;
    sprev1[k] = 0;
  }
#pragma MUST_ITERATE(2, , 2)
  for (i = 0; i < n; i++) {
    int x = _sshl(in[i], 8);
    for (k = 0; k < 6; k++) {
      s[k] = _sadd(_ssub(x, sprev1[k]), _smpy((sprev[k]) >> 15, cosx[k]));
      sprev1[k] = sprev[k];
      sprev[k] = s[k];
    }
  }
  for (k = 0; k < 6; k++) {
    sprev[k] = (sprev[k]) >> 16;
    sprev1[k] = (sprev1[k]) >> 16;
    power[k] = (_mpy(sprev1[k], sprev1[k]) + _mpy(sprev[k], sprev[k]) -
                _mpy((_smpy(sprev[k], cosx[k]) >> 15), sprev1[k]));
  }
}