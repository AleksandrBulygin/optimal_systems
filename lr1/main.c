#include <stdio.h>

short A[512];
struct int_statistics {
  short min;
  short max;
  int average;
  int variance;
};

void calc_statistics_no_opt(short *data, int n, struct int_statistics *result);

void calc_statistics_opt_2(short *data, int n, struct int_statistics *result);

void calc_statistics_opt_3(short *data, int n, struct int_statistics *result);

void calc_statistics_opt_4(short *data, int n, struct int_statistics *result);

void calc_statistics_opt(short *data, int n, struct int_statistics *result);

void print_statictics(struct int_statistics disp, char *prefix) {
  printf("%s: \n minimum: %d \n maximum: %d \n ", prefix, disp.min, disp.max);
  printf("average: %d \n variance: %d \n", disp.average, disp.variance);
}

int main(void) {
  struct int_statistics p;
  int n = sizeof(A) / sizeof(A[0]);
  int i;
  for (i = 0; i < n; i++) {
    A[i] = i + 32000;
  }
  for (i = 0; i < 100; i++) {
    calc_statistics_no_opt(A, n, &p);
  }
  print_statictics(p, "No opt");
  for (i = 0; i < 100; i++) {
    calc_statistics_opt(A, n, &p);
  }
  print_statictics(p, "Opt");
  for (i = 0; i < 100; i++) {
    calc_statistics_opt_2(A, n, &p);
  }
  print_statictics(p, "Opt 2");

#if defined(_TMS320C6200)
  for (i = 0; i < 100; i++) {
    calc_statistics_opt_3(A, n, &p);
  }
  print_statictics(p, "Opt 3");
  for (i = 0; i < 100; i++) {
    calc_statistics_opt_4(A, n, &p);
  }
  print_statictics(p, "Opt 4");
#endif
  return 0;
}
