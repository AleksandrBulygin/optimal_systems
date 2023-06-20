#include "goertzel_type.h"
#define N 128
short A[N];
void c62_goertzel_power_no_opt(s16 cos_Q15, const s16 *in, int n, s32 *power);
void c64_goertzel_power_no_opt(s16 cos_Q15, const s16 *in, int n, s32 *power);
void c62_goertzel_power_opt_1(s16 cos_Q15, const s16 *in, int n, s32 *power);
void c62_goertzel_power_opt_2(s16 cos_Q15, const s16 *in, int n, s32 *power);
void c62_goertzel_power_opt_3(const s16 *cos_Q15, const s16 *in, int n,
                              s32 *power);
void c64_goertzel_power_opt_1(const s16 *cos_Q15, const s16 *in, int n,
                              s32 *power);
void c64_goertzel_power_opt_2(const s16 *cos_Q15, const s16 *in, int n,
                              s32 *power);
void print_goertzel(long check, s32 power, char *prefix) {
  float checkf = (float)check / 8388608; // 8388608 = 2^23
  float powerf = (float)power / 16384;   // 16384 = 2^14
  float delta = checkf - powerf;
  float epsilon = 200 * delta / (checkf + powerf);
  float gp = powerf / checkf * 100;
  printf("goertzel_power%s: %.4f(%.3f%%), ", prefix, powerf, gp);
  printf("difference: %.3f%%", epsilon);
  if (epsilon <= 1)
    printf("(OK!).\n");
  else
    printf("(ERROR!).\n");
}
void print_multi_goertzel(long check, int *power, int *origin, char *prefix,
                          char *prefix1, int n, s16 *cos) {
  int i;
  float checkf = (float)check / 8388608;
  float powerf = (float)power[0] / 16384;
  float delta = checkf - powerf;
  float epsilon = 200 * delta / (checkf + powerf);
  printf("-------------------------------------------------\n");
  for (i = 0; i < n; i++) {
    float powerfi = (float)power[i] / 16384;
    float originfi = (float)origin[i] / 16384;
    float gp = powerfi / originfi * 100;
    float cosf = (float)cos[i] / 32768;
    float deltai = originfi - powerfi;
    float epsiloni = 200 * deltai / (powerfi + originfi);
    printf("cos[%d] = %f:\n", i, cosf);
    printf("goertzel_power%s: %.4f(%.1f%%);\n", prefix, powerfi, gp);
    printf("goertzel_power_no_opt%s: %.4f(100%%);\n", prefix1, originfi);
    printf("difference: %.2f%%.\n\n", epsiloni);
  }
  float coscheck = (float)cos[0] / 32768;
  float gpc = powerf / checkf * 100;
  printf("CHECK:\n");
  printf("cos[0] = %f:\n", coscheck);
  printf("total_power: %.4f(100%%);\n", checkf);
  printf("goertzel_power%s: %.4f(%.3f%%);\n", prefix, powerf, gpc);
  printf("difference: %.3f%%", epsilon);
  if (epsilon <= 1)
    printf("(OK!).\n\n");
  else
    printf("(ERROR!).\n\n");
}
long total_power(short *in, int n) {
  int i;
  long total = 0;
  for (i = 0; i < n; i++) {
    short x = in[i];
    total += x * x;
    // Q0.15 * Q0.15 => Q0.30
  }
  return (total * n / 2) >> 7;
  // Q0.30 >> 7 => 8.23
}
int main(void) {
  int i, numberg4, numberg5, k, g162[6], g164[8], g2, g3, g4[6], g5[6], g6[8];
  long check;
  float checkf;
  numberg4 = sizeof(g4) / sizeof(g4[0]);
  numberg5 = sizeof(g6) / sizeof(g6[0]);
  short cosx[] = {16000, 14000, 12000, 10000, 8000, 6000, 4000, 2000};
  float cosf = (float)cosx[0] / 32768; // 32768 = 2^15
  A[0] = 0;
  A[1] = 5000;
  for (i = 2; i < N; i++) {
    A[i] = 2 * ((A[i - 1] * cosx[0]) >> 15) - A[i - 2];
  }
  check = total_power(A, N);
  for (i = 0; i < 100; i++) {
    for (k = 0; k < 6; k++) {
      c62_goertzel_power_no_opt(cosx[k], A, N, &g162[k]);
    }
    for (k = 0; k < 8; k++) {
      c64_goertzel_power_no_opt(cosx[k], A, N, &g164[k]);
    }
    c62_goertzel_power_opt_1(cosx[0], A, N, &g2);
    c62_goertzel_power_opt_2(cosx[0], A, N, &g3);
    c62_goertzel_power_opt_3(cosx, A, N, g4);
    c64_goertzel_power_opt_1(cosx, A, N, g5);
    c64_goertzel_power_opt_2(cosx, A, N, g6);
  }
  int amp = -32768;
  for (i = 1; i < N; i++) {
    if (amp < A[i])
      amp = A[i];
  }
  float ampf = (float)amp / 32768;
  checkf = (float)check / 8388608;
  printf("amplitude: %.5f, quantity of elements: %d:\n\n", ampf, N);
  printf("cos=%.3f:\n", cosf);
  printf("total_power: %.4f (100%%)\n", checkf);
  print_goertzel(check, g162[0], "_no_opt_c62");
  print_goertzel(check, g2, "_opt_1_c62");
  print_goertzel(check, g3, "_opt_2_c62");
  print_multi_goertzel(check, g4, g162, "_opt_3_c62", "_c62", numberg4, cosx);
  printf("-------------------------------------------------\n");
  printf("cos=%.3f:\n", cosf);
  printf("total_power: %.4f (100%%)\n", checkf);
  print_goertzel(check, g164[0], "_no_opt_c64");
  print_multi_goertzel(check, g5, g164, "_opt_1_c64", "_c64", numberg4, cosx);
  print_multi_goertzel(check, g6, g164, "_opt_2_c64", "_c64", numberg5, cosx);
  return 0;
}