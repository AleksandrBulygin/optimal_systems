#include "pack_type.h"
#define N 480
#pragma DATA_ALIGN(A, 1)
u8 A[N], p1[N], p2[N], p3[N], p4[N], p5[N], p6[N], p7[N], p8[N], p9[N], p10[N],
    p11[N], p12[N], p13[N], p14[N], p15[N], p16[N], p17[N], p18[N], p19[N];
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
int c62_pack_scale(const u8 *in, int n, int m, u8 *result);
int c64_pack_scale(u8 *in, int n, int m, u8 *result);
void print_scale(const u8 *array, int n, char *prefix, u8 *in, int m) {
  printf("---------------------------------------------------\n");
  printf("%s\nquantity of bytes: %d\n", prefix, n);
  printf("begin of packed array: %d, %d, %d, %d;\n", array[0], array[1],
         array[2], array[3]);
  c62_pack_scale_no_opt(in, N, m, p1);
  if (memcmp(array, p1, n) == 0)
    printf("array equal to array of reference function.\n\n");
  else
    printf("array don't equal to array of reference function.\n\n");
}
int main(void) {
  int i, m, nd, c1, c2, c3, c4, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15,
      c16, c17, c18;
  char k;
  nd = N / 2;
  for (i = 0; i < N; i++) {
    if (i < nd)
      k = i;
    else
      k = N - i;
    A[i] = k;
  }
  m = 8;
  for (i = 0; i < 100; i++) {
    c62_pack_scale_no_opt(A, N, m, p1);
    c2 = c62_pack_scale_x1_opt_1(A, N, m, p2);
    c3 = c62_pack_scale_x2_opt_2(A, N, m, p3);
    c4 = c62_pack_scale_x4_opt_3(A, N, m, p4);
    c64_pack_scale_no_opt(A, N, m, p5);
    c6 = c64_pack_scale_x4_opt_1(A, N, m, p6);
    c7 = c64_pack_scale_x4_opt_2(A, N, m, p7);
    c8 = c64_pack_scale_x8_opt_3(A, N, m, p9);
    c9 = c64_pack_scale_x2_opt_4(A, N, m, p8);
    c10 = c64_pack_scale_1_opt_5(A, N, p10);
    c11 = c64_pack_scale_2_opt_6(A, N, p11);
    c12 = c62_pack_scale_1_opt_4(A, N, p12);
    c13 = c64_pack_scale_3_opt_7(A, N, p13);
    c14 = c62_pack_scale_2_opt_5(A, N, p14);
    c15 = c62_pack_scale_3_opt_6(A, N, p15);
    c16 = c62_pack_scale_4_opt_7(A, N, p16);
    c17 = c64_pack_scale_4_opt_8(A, N, p17);
    c18 = c64_pack_scale_x1_opt_9(A, N, m, p18);
  }
  printf("n: %d, m: %d\n", N, m);
  print_scale(p2, c2, "c62_pack_scale_x1_opt_1:", A, m);
  print_scale(p3, c3, "c62_pack_scale_x2_opt_2:", A, m);
  print_scale(p4, c4, "c62_pack_scale_x4_opt_3:", A, m);
  print_scale(p12, c12, "c62_pack_scale_1_opt_4:", A, 1);
  print_scale(p14, c14, "c62_pack_scale_2_opt_5:", A, 2);
  print_scale(p15, c15, "c62_pack_scale_3_opt_6:", A, 3);
  print_scale(p16, c16, "c62_pack_scale_4_opt_7:", A, 4);
  print_scale(p6, c6, "c64_pack_scale_x4_opt_1:", A, m);
  print_scale(p7, c7, "c64_pack_scale_x4_opt_2:", A, m);
  print_scale(p9, c8, "c64_pack_scale_x8_opt_3:", A, m);
  print_scale(p8, c9, "c64_pack_scale_x2_opt_4:", A, m);
  print_scale(p10, c10, "c64_pack_scale_1_opt_5:", A, 1);
  print_scale(p11, c11, "c62_pack_scale_2_opt_6:", A, 2);
  print_scale(p13, c13, "c62_pack_scale_3_opt_7:", A, 3);
  print_scale(p17, c17, "c62_pack_scale_4_opt_8:", A, 4);
  print_scale(p18, c18, "c62_pack_scale_x1_opt_9:", A, m);
  c1 = c62_pack_scale(A, N, m, p1);
  print_scale(p1, c1, "C62_dispatcher:", A, m);
  c1 = c64_pack_scale(A, N, m, p1);
  print_scale(p1, c1, "C64_dispatcher:", A, m);
  return 0;
}