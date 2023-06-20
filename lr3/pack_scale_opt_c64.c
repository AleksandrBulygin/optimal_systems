// Оптимизированная программа для уплотнения РЛС сигнала (ядро С64)
#include "pack_type.h"
int c64_pack_scale_x4_opt_1(const u8 *in, int n, int m, u8 *restrict result) {
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
      // структура для уменьшения завязки по данным
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
int c64_pack_scale_x4_opt_2(const u8 *in, int n, int m, u8 *restrict result) {
  int k;
  u32 max = 0;
  u32 max1 = 0;
  u32 max2 = 0;
  u32 max3 = 0;
  int count = 0;
  int countb = 0;
  int m1 = m >> 2;
  u32 *din = (u32 *)in;
  u32 *dres = (u32 *)result;
  int m12 = _mpy(m1, 2);
  int m13 = _mpy(m1, 3);
#pragma MUST_ITERATE(1)
  for (k = 0; k < n; k += 16) {
    u32 v = *(din + m13);
    u32 z = *(din + m12);
    u32 y = *(din + m1);
    u32 x = *din++;
    max = _maxu4(max, v);
    max1 = _maxu4(max1, z);
    max2 = _maxu4(max2, y);
    max3 = _maxu4(max3, x);
    count += 4;
    if (count == m) {
      u32 l = _packl4(max, max1);
      u32 h = _packh4(max, max1);
      u32 maxlh = _maxu4(l, h);
      u32 l1 = _packl4(max2, max3);
      u32 h1 = _packh4(max2, max3);
      u32 maxlh1 = _maxu4(l1, h1);
      u32 pack16l = _packl4(maxlh, maxlh1);
      u32 pack16h = _packh4(maxlh, maxlh1);
      *dres++ = _maxu4(pack16l, pack16h);
      max = 0;
      max1 = 0;
      max2 = 0;
      max3 = 0;
      count = 0;
      countb += 4;
      din += m13;
    }
  }
  return countb;
}
int c64_pack_scale_x8_opt_3(const u8 *in, int n, int m, u8 *restrict result) {
  int k;
  u32 max = 0;
  u32 maxs32 = 0;
  int count = 0;
  int countb = 0;
  u64 *din = (u64 *)in;
#pragma UNROLL(2)
#pragma MUST_ITERATE(1)
  for (k = 0; k < n; k += 8) {
    u64 x = *din++;
    maxs32 = _maxu4(maxs32, x >> 32);
    max = _maxu4(max, x);
    count += 8;
    if (count == m) {
      max = _maxu4(max, maxs32);
      max = _maxu4(max, max >> 16);
      *result++ = _maxu4(max, max >> 8);
      max = 0;
      maxs32 = 0;
      count = 0;
      countb++;
    }
  }
  return countb;
}
int c64_pack_scale_x2_opt_4(const u8 *in, int n, int m, u8 *restrict result) {
  int k;
  u32 max = 0;
  u32 max1 = 0;
  int count = 0;
  int countb = 0;
  int m1 = m >> 1;
  u16 *din = (u16 *)in;
#pragma UNROLL(2)
#pragma MUST_ITERATE(2, , 2)
  for (k = 0; k < n; k += 4) {
    u32 y = *(din + m1);
    u32 x = *din++;
    max = _maxu4(max, y);
    max1 = _maxu4(max1, x);
    count += 2;
    if (count == m) {
      *result++ = _maxu4(max1, max1 >> 8);
      *result++ = _maxu4(max, max >> 8);
      count = 0;
      countb += 2;
      din += m1;
      max = 0;
      max1 = 0;
    }
  }
  return countb;
}
int c64_pack_scale_1_opt_5(const u8 *in, int n, u8 *restrict result) {
  _nassert(((int)(in)&0x7) == 0);
  int i;
  u64 *din = (u64 *)in;
  u64 *dres = (u64 *)result;
#pragma MUST_ITERATE(1)
  for (i = 0; i < n; i += 16) {
    *dres++ = *din++;
    *dres++ = *din++;
  }
  return n;
}
int c64_pack_scale_2_opt_6(const u8 *in, int n, u8 *restrict result) {
  int i;
  int count = 0;
  u64 *din = (u64 *)in;
  u32 *dres = (u32 *)result;
#pragma UNROLL(2)
#pragma MUST_ITERATE(1)
  for (i = 0; i < n; i += 8) {
    u64 x = *din++;
    u32 l = _packl4(x >> 32, x);
    u32 h = _packh4(x >> 32, x);
    u32 max = _maxu4(h, l);
    *dres++ = max;
    count += 4;
  }
  return count;
}
int c64_pack_scale_3_opt_7(const u8 *in, int n, u8 *restrict result) {
  int i;
  int count = 0;
  u32 m8 = 256;
  u32 *din = (u32 *)in;
  u32 *dres = (u32 *)result;
#pragma MUST_ITERATE(1)
  for (i = 0; i < n; i += 12) {
    u32 x = *din++;
    u32 y = *din++;
    u32 z = *din++;
    u8 x0 = x;
    u8 x1 = x >> 8;
    u8 x2 = x >> 16;
    u8 y2 = y >> 16;
    u8 y3 = y >> 24;
    u8 z0 = z;
    u32 a = _mpy(x >> 24, m8) + x0;
    u32 b = _mpy(y, m8) + x1;
    u32 c = _mpy(y >> 8, m8) + x2;
    u32 d = _mpy(z >> 8, m8) + y2;
    u32 e = _mpy(z >> 16, m8) + y3;
    u32 f = _mpy(z >> 24, m8) + z0;
    a = _pack2(d, a);
    b = _pack2(e, b);
    c = _pack2(f, c);
    u32 max = _maxu4(a, b);
    max = _maxu4(max, c);
    *dres++ = max;
    count += 4;
  }
  return count;
}
int c64_pack_scale_4_opt_8(const u8 *in, int n, u8 *restrict result) {
  int i;
  u32 max;
  int count = 0;
  u64 *din = (u64 *)in;
  u16 *dres = (u16 *)result;
#pragma UNROLL(2)
#pragma MUST_ITERATE(1)
  for (i = 0; i < n; i += 8) {
    u64 x = *din++;
    u32 l = _packl4(x >> 32, x);
    u32 h = _packh4(x >> 32, x);
    max = _maxu4(l, h);
    max = _maxu4(max >> 8, max);
    *dres++ = _packl4(max, max);
    count += 2;
  }
  return count;
}
int c64_pack_scale_x1_opt_9(const u8 *in, int n, int m, u8 *restrict result) {
  int k;
  u32 max = 0;
  u32 max1 = 0;
  int count = 0;
  int countb = 0;
#pragma MUST_ITERATE(1)
  for (k = 0; k < n; k += 2) {
    u32 y = *(in + m);
    u32 x = *in++;
    max = _maxu4(max, x);
    max1 = _maxu4(max1, y);
    count++;
    if (count == m) {
      *result++ = max;
      *result++ = max1;
      max = 0;
      max1 = 0;
      count = 0;
      countb += 2;
      in += m;
    }
  }
  return countb;
}