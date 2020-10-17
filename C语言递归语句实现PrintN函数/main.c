//
//  main.c
//  C语言递归语句实现PrintN函数
//
//  Created by PhD Wang's Macbook  on 2020/9/26.
//


//用C语言循环语句实现printN函数
void PrintN(int N)
{
    int i;
    for (i = 1; i <= N; i++) {
        printf("%d\n",i);
    }
    return 0;
}

//用C语言递归语句实现的PrintN函数
void PrintN()
{
    if(N> 0){
        PrintN( N - 1 );
        printf("%d\n",N);
    }
}

//但是递归在空间中占用较大，因为需要把所有的要运行的程序都要同时放进内存中。
