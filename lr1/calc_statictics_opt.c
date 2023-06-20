// Оптимизированная программа статистических параметров
struct int_statistics {
  short min;
  short max;
  int average;
  int variance;
};

long long summ2sa(short *, int);

#if defined(_TMS320C6400)
void calc_statistics_opt(short *data, int n, struct int_statistics *result) {
  int i;
  short min = 32767;
  short max = -32768;
  int summ = 0;
  short max1 = -32768;
  short min1 = 32767;
  long summ2 = 0;
  short x, y;
#pragma MUST_ITERATE(4, , 4)
  for (i = 0; i < n; i += 2) {
    x = data[i];
    y = data[i + 1];
    min = x < min ? x : min;
    max = x > max ? x : max;
    min1 = y < min1 ? y : min1;
    max1 = y > max1 ? y : max1;
    summ += x + y;
    summ2 += x * x + y * y;
  }
  min = min < min1 ? min : min1;
  max = max > max1 ? max : max1;
  result->variance = (summ2 - (long long)summ * (long long)summ / n) / (n);
  result->average = summ / n;
  result->min = min;
  result->max = max;
}
void calc_statistics_opt_2(short *data, int n, struct int_statistics *result) {
  int i;
  int summ = 0;
  int minp = 0x7fff7fff;
  int maxp = 0x80008000;
  long summ2 = 0;
  int dotp;
  int one = 0x00010001;
  short min, min1, max, max1;
#pragma MUST_ITERATE(4, , 4)
  for (i = 0; i < n; i += 2) {
    dotp = _pack2(data[i], data[i + 1]);
    minp = _min2(minp, dotp);
    maxp = _max2(maxp, dotp);
    summ += _dotp2(dotp, one);
    summ2 += _dotp2(dotp, dotp);
  }
  min = minp;
  min1 = minp >> 16;
  min = min < min1 ? min : min1;
  max = maxp;
  max1 = maxp >> 16;
  max = max > max1 ? max : max1;
  result->variance = (summ2 - (long long)summ * (long long)summ / n) / (n);
  result->average = summ / n;
  result->min = min;
  result->max = max;
  ;
}
#endif
#if defined(_TMS320C6200)
void calc_statistics_opt(short *data, int n, struct int_statistics *result) {
  int i;
  short min = 32767;
  short max = -32768;
  int summ = 0;
  long summ2 = 0;
  short x;
#pragma MUST_ITERATE(4, , 4)
  for (i = 0; i < n; i++) {
    x = data[i];
    if (x < min)
      min = x;
    if (x > max)
      max = x;
    summ += x;
    summ2 += x * x;
  }
  result->variance = (summ2 - (long long)summ * (long long)summ / n) / (n);
  result->average = summ / n;
  result->min = min;
  result->max = max;
}
void calc_statistics_opt_2(short *data, int n, struct int_statistics *result) {
  int i;
  short min = 32767;
  short max = -32768;
  int summ = 0;
  long summ2 = 0;
  short x;
#pragma MUST_ITERATE(4, , 4)
  for (i = 0; i < n; i++) {
    x = data[i];
    min = x < min ? x : min;
    max = x > max ? x : max;
    summ += x;
    summ2 += x * x;
  }
  result->variance = (summ2 - (long long)summ * (long long)summ / n) / (n);
  result->average = summ / n;
  result->min = min;
  result->max = max;
}
void calc_statistics_opt_3(const short *data, int n,
                           struct int_statistics *result) {
  int i;
  short min = 32767;
  short max = -32768;
  int summ = 0;
  short max1 = -32768;
  short min1 = 32767;
  long summ2 = 0;
  short x;
  short y;
#pragma MUST_ITERATE(2, , 2)
  for (i = 0; i < n; i += 2) {
    x = data[i];
    y = data[i + 1];
    min = x < min ? x : min;
    max = x > max ? x : max;
    min1 = y < min1 ? y : min1;
    max1 = y > max1 ? y : max1;
    summ += x + y;
    summ2 += x * x + y * y;
  }
  min = min < min1 ? min : min1;
  max = max > max1 ? max : max1;
  result->variance = (summ2 - (long long)summ * (long long)summ / n) / (n);
  result->average = summ / n;
  result->min = min;
  result->max = max;
}
void calc_statistics_opt_4(short *data, int n, struct int_statistics *result) {
  int i;
  short min = 32767;
  short max = -32768;
  int summ = 0;
  short max1 = 32767;
  short min1 = -32768;
  long summ2 = 0;
  int x;
  int y;
#pragma MUST_ITERATE(4, , 4)
  for (i = 0; i < n; i += 2) {
    x = data[i];
    y = data[i + 1];
    min = x < min ? x : min;
    max = x > max ? x : max;
    min1 = y < min1 ? y : min1;
    max1 = y > max1 ? y : max1;
    summ += x + y;
  }
  summ2 = summ2sa(data, n);
  min = min < min1 ? min : min1;
  max = max > max1 ? max : max1;
  result->variance = (summ2 - (long long)summ * (long long)summ / n) / (n);
  result->average = summ / n;
  result->min = min;
  result->max = max;
}
#endif
