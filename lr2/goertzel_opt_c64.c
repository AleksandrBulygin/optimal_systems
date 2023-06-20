// Оптимизированная программа алгоритма Герцля (Ядро с64)
#include "goertzel_type.h"
void c64_goertzel_power_opt_1(const s16 *cos_Q15, const s16 *in, int n,
                              s32 *power) {
  int s[6], i, k, sprev[6], sprev1[6];
  short cosx[6];
  for (k = 0; k < 6; k++) {
    cosx[k] = cos_Q15[k];
    sprev[k] = 0;
    sprev1[k] = 0;
  }
#pragma MUST_ITERATE(2, ,2)
  for (i = 0; i < n; i++) {
    int x = _sshl(in[i], 8);
    for (k = 0; k < 6; k++) {
      s[k] = _sadd(_ssub(x, sprev1[k]), _smpy((sprev[k]) >> 15, cosx[k]));
      sprev1[k] = sprev[k];
      sprev[k] = s[k];
    }
  }for (k = 0; k < 6; k++) {
    sprev[k] = (sprev[k]) >> 16;
    sprev1[k] = (sprev1[k]) >> 16;
    power[k] = (_mpy(sprev1[k], sprev1[k])
                + _mpy(sprev[k], sprev[k])
                - _mpy((_smpy(sprev[k], cosx[k]) >> 15), sprev1[k]));
  }
}
void c64_goertzel_power_opt_2(const s16 *cos_Q15, const s16 *in, int n,
                              s32 *power) {
  int s[8], i, k, sprev[8], sprev1[8];
  short cosx[8];
  for (k = 0; k < 8; k++) {
    cosx[k] = cos_Q15[k];
    sprev[k] = 0;
    sprev1[k] = 0;
  }
#pragma MUST_ITERATE(2, ,2)
  for (i = 0; i < n; i++) {
    int x = _sshl(in[i], 8);
    for (k = 0; k < 8; k++) {
      s[k] = _sadd(_ssub(x, sprev1[k]), _smpy((sprev[k]) >> 15, cosx[k]));
      sprev1[k] = sprev[k];
      sprev[k] = s[k];
    }
  }
  for (k = 0; k < 8; k++) {
    sprev[k] = (sprev[k]) >> 16;
    sprev1[k] = (sprev1[k]) >> 16;
    power[k] = (_mpy(sprev1[k], sprev1[k])
                + _mpy(sprev[k], sprev[k])
                - _mpy((_smpy(sprev[k], cosx[k]) >> 15), sprev1[k]));
  }
}