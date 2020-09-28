//使用直接法 通过循环累计求和来计算多项式函数值
double f(int n, double a[], double x)
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

//使用秦九韶法
double f(int n, int a[], double x)
{
    int i;
    double p = a[n];
    for ( i = n; i > 0; i--)
    {
        p = a[i-1] + x * p;
    }
    return p;
    
}
