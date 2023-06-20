// Оптимизированная программа для уплотнения РЛС сигнала (ядро С62)
#include "pack_type.h"
int c62_pack_scale_x1_opt_1(const u8 *in, int n, int m, u8 *restrict result) {
  int k;
  int count = 0;
  int countb = 0;
  u8 max = 0;
#pragma MUST_ITERATE(1)
  for (k = 0; k < n; k++) {
    u8 x = *in++;
    max = (x > max) ? x : max;
    count++;
    if (count == m) {
      *result++ = max;
      max = 0;
      count = 0;
      countb++;
    }
  }
  return countb;
}
int c62_pack_scale_x2_opt_2(const u8 *in, int n, int m, u8 *restrict result) {
  int k;
  int count = 0;
  int countb = 0;
  u8 max = 0;
  u8 max1 = 0;
#pragma MUST_ITERATE(1)
  for (k = 0; k < n; k += 2) {
    u8 x = *in++;
    u8 y = *in++;
    max = (x > max) ? x : max;
    max1 = (y > max1) ? y : max1;
    count += 2;
    if (count == m) {
      // конструкция для уменьшения завязки по данным
      if (max > max1)
        *result++ = max;
      if (max1 > max)
        *result++ = max1;
      max = 0;
      max1 = 0;
      count = 0;
      countb++;
    }
  }
  return countb;
}
int c62_pack_scale_x4_opt_3(const u8 *in, int n, int m, u8 *restrict result) {
  int k;
  int count = 0;
  int countb = 0;
  u8 max = 0;
  u8 max1 = 0;
#pragma MUST_ITERATE(1)
  for (k = 0; k < n; k += 4) {
    u8 x = *in++;
    u8 y = *in++;
    u8 z = *in++;
    u8 a = *in++;
    x = (x > z) ? x : z;
    y = (y > a) ? y : a;
    max = (x > max) ? x : max;
    max1 = (y > max1) ? y : max1;
    count += 4;
    if (count == m) {
      // конструкция для уменьшения завязки по данным
      if (max > max1)
        *result++ = max;
      if (max1 > max)
        *result++ = max1;
      max = 0;
      max1 = 0;
      count = 0;
      countb++;
    }
  }
  return countb;
}
int c62_pack_scale_1_opt_4(const u8 *in, int n, u8 *restrict result) {
  int i;
  _nassert(((int)(in)&0x3) == 0);
  u32 *din = (u32 *)in;
  u32 *restrict dres = (u32 *)result;
#pragma MUST_ITERATE(1)
  for (i = 0; i < n; i += 4) {
    u32 x = *din++;
    *dres++ = x;
  }
  return n;
}
int c62_pack_scale_2_opt_5(const u8 *in, int n, u8 *restrict result) {
  int i;
  int count = 0;
#pragma MUST_ITERATE(1)
  for (i = 0; i < n; i += 4) {
    u8 x = *in++;
    u8 y = *in++;
    *result++ = (x > y) ? x : y;
    u8 a = *in++;
    u8 b = *in++;
    *result++ = (a > b) ? a : b;
    count += 2;
  }
  return count;
}
int c62_pack_scale_3_opt_6(const u8 *in, int n, u8 *restrict result) {
  int i;
  int count = 0;
  u8 max;
#pragma UNROLL(2)
#pragma MUST_ITERATE(1)
  for (i = 0; i < n; i += 3) {
    u8 x = *in++;
    u8 y = *in++;
    u8 z = *in++;
    max = (z > y) ? z : y;
    *result++ = (x > max) ? x : max;
    count++;
  }
  return count;
}
int c62_pack_scale_4_opt_7(const u8 *in, int n, u8 *restrict result) {
  int i;
  int count = 0;
  u8 max, max1;
#pragma UNROLL(2)
#pragma MUST_ITERATE(1)
  for (i = 0; i < n; i += 4) {
    u8 x = *in++;
    u8 y = *in++;
    u8 z = *in++;
    u8 a = *in++;
    max = (z > a) ? z : a;
    max1 = (x > y) ? x : y;
    *result++ = (max > max1) ? max : max1;
    count++;
  }
  return count;
}