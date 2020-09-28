#include <stdio.h>
#include <time.h>
#include <math.h>

clock_t start, stop;
double duration;
#define MAXN 10  //多项式最大项数，即多项式阶数+1
#define MAXK 1e7 //被测函数的最大重复调用次数

double f1(int n, double a[], double x)
{
    /*计算阶数为n，系数为a[0],a[1],..,a[n]的多项式在x的值*/
    int i;
    double p = a[0];
    for ( i = 1; i <= n ; i++)
    {
        p += a[i] * pow(x,i);
    }
    return p;
}

double f2(int n, double a[], double x)
{
    int i;
    double p = a[n];
    for ( i = n; i > 0; i--)
    {
        p = a[i-1] + x * p;
    }
    return p;
    
}

void run(double(*f)(int,double *, double),double a[], int case_n)
{
    //这个run函数是输入一个函数、数据、case_n 等于1则代表是f1函数，等于2则代表是f2函数
    int i;
    start = clock();
    for ( i = 0; i < MAXK; i++)
    {
        (*f)(MAXN - 1, a, 1.1); //1.1是x的值
    }
    stop = clock();

    duration = ((double)(stop - start))/ CLK_TCK/ MAXK;
    printf("ticks%d = %f\n", case_n, (double)(stop - start));
    printf("duration%d = %6.2e\n", case_n, duration);
}

int main()
{
    int i;
    double a[MAXN]; //存储多项式系数

    for ( i = 0; i < MAXN; i++)
    {
        a[i] = (double)i; //本题设置的是a[i] = i；
    }

    run(f1, a, 1);
    run(f2, a, 2);

    return 0;
}