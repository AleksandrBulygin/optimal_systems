// Эталонная программа вычистения статистических параметров
struct int_statistics {
    short min;
    short max;
    int average;
    int variance;
};
void calc_statistics_no_opt(short *data, int n, struct int_statistics *result)
{
    int i;
    short min=32767;
    short max=-32768;
    int summ=0;
    long summ2=0;
    int x;
    for (i=0; i<n; i++)
    {
        x=data[i];
        if(x<min) min=x;
        if(x>max) max=x;
        summ+=x;
        summ2+=x*x;
    }
// дисперисия расчитывается как разность суммы квадратов и квадрата суммы
// всех элементов массива, деленное на количество элементов.
// полученная разность делится на количество элементов массива
    result->variance=(summ2-(long long)summ*(long long)summ/n)/(n);
    result->average=summ/n;
    result->min=min;
    result->max=max;
}

