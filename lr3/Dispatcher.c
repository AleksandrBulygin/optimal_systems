#include "pack_type.h"
int c62_pack_scale_no_opt(const u8 *in, int n, int m, u8 *restrict result);
int c62_pack_scale_x1_opt_1(const u8 *in, int n, int m, u8 *restrict result);
int c62_pack_scale_x2_opt_2(const u8 *in, int n, int m, u8 *restrict result);
int c62_pack_scale_x4_opt_3(const u8 *in, int n, int m, u8 *restrict result);
int c62_pack_scale_1_opt_4(const u8 *in, int n, u8 *restrict result);
int c62_pack_scale_2_opt_5(const u8 *in, int n, u8 *restrict result);
int c62_pack_scale_3_opt_6(const u8 *in, int n, u8 *restrict result);
int c62_pack_scale_4_opt_7(const u8 *in, int n, u8 *restrict result);
int c64_pack_scale_no_opt(const u8 *in, int n, int m, u8 *restrict result);
int c64_pack_scale_x4_opt_1(const u8 *in, int n, int m, u8 *restrict result);
int c64_pack_scale_x4_opt_2(const u8 *in, int n, int m, u8 *restrict result);
int c64_pack_scale_x8_opt_3(const u8 *in, int n, int m, u8 *restrict result);
int c64_pack_scale_x2_opt_4(const u8 *in, int n, int m, u8 *restrict result);
int c64_pack_scale_1_opt_5(const u8 *in, int n, u8 *restrict result);
int c64_pack_scale_2_opt_6(const u8 *in, int n, u8 *restrict result);
int c64_pack_scale_3_opt_7(const u8 *in, int n, u8 *restrict result);
int c64_pack_scale_4_opt_8(const u8 *in, int n, u8 *restrict result);
int c64_pack_scale_x1_opt_9(const u8 *in, int n, int m, u8 *restrict result);
int c62_pack_scale(const u8 *in, int n, int m, u8 *result) {
  switch (m) {
  case 1:
    return c62_pack_scale_1_opt_4(in, n, result);
  case 2:
    return c62_pack_scale_2_opt_5(in, n, result);
  case 3:
    return c62_pack_scale_3_opt_6(in, n, result);
  case 4:
    return c62_pack_scale_4_opt_7(in, n, result);
  default:
    if ((m % 4) == 0)
      return c62_pack_scale_x4_opt_3(in, n, m, result);
    else if ((m % 2) == 0)
      return c62_pack_scale_x2_opt_2(in, n, m, result);
    else
      return c62_pack_scale_x1_opt_1(in, n, m, result);
  }
}
int c64_pack_scale(u8 *in, int n, int m, u8 *result) {
  switch (m) {
  case 1:
    return c64_pack_scale_1_opt_5(in, n, result);
  case 2:
    return c64_pack_scale_2_opt_6(in, n, result);
  case 3:
    return c64_pack_scale_3_opt_7(in, n, result);
  case 4:
    return c64_pack_scale_4_opt_8(in, n, result);
  default:
    if ((m % 8) == 0)
      return c64_pack_scale_x8_opt_3(in, n, m, result);
    else if ((m % 4) == 0)
      return c64_pack_scale_x4_opt_2(in, n, m, result);
    else if ((m % 2) == 0)
      return c64_pack_scale_x2_opt_4(in, n, m, result);
    else
      return c64_pack_scale_x1_opt_9(in, n, m, result);
  }
}