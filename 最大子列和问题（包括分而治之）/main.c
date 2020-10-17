//最直接的方法，穷举所有子列和，从中找到最大值
//这个就是三重for循环
int MaxSubseqSum1(int List[], int N)
{
    int i, j, k;
    int thissum, maxsum = 0;
    for ( i = 0; i < N; i++)
    {
        for ( j = i; j < N; j++)
        {
            thissum = 0;
            for ( k = i; k <= j; k++)
            {
                thissum += List[k];
            }
            if (thissum > maxsum)
            {
                maxsum = thissum;
            }
        }
        
    }
    return maxsum;
} 

//因为第三层K循环里面，对于固定的i，当j增加到1，K循环就要重新从i加到j，事实上不需要，这个j-1步的结果完全可以存起来，加上一个list[j]即可。
//从穷举的N的3次方变成了N的二次方
int MaxSubseqSum2(int List[], int N)
{
    int i,j;
    int thissum, maxsum = 0;
    for ( i = 0; i < N; i++)
    {
        thissum = 0;
        for ( j = i; j < N; j++)
        {
            thissum += List[j];
            if (thissum > maxsum)
            {
                maxsum = thissum;
            }
            
        }
        
    }
    return maxsum;
}

//用分而治之：将原问题拆分成若干小型问题，分别解决后再将结果合而治之，用递归实现非常方便
/*
step1: 将序列从中分为左右两个子序列
step2：递归求得两子列的最大和S左和S右
step3：从中分点分头向左向右两边扫描，找出跨过分界线的最大子列和S中
step4：Smax =  max(S左，S右，S中)
*/
//这里面调用了几个函数
int Max3 (int A, int B, int C)
{
    return A>B? A>C? A:C:B>C?B:C; //一种写法

    int max; //另一种写法
    if (A>B && A > C)
    {
        max = A;
    }else if(B > C){
        max = B;
    }else{
        max = C;
    }
    return max;
}

//分而治之
int DivideAndConquer(int List[], int left, int right)
{
    //分治法求List[left]到list[right]的最大子列和
    int maxleftsum, maxrightsum;
    int maxleftbordersum, maxrightbordersum; //存放跨分界线的结果

    int leftbordersum, rightbordersum;
    int center, i;

    if (left == right)
    {
        if (List[left] > 0)
        {
            return List[left];
        }else
        {
            return 0;
        }
    }
    
    //下面是分的过程
    center = (left+right)/2;  //找到中分点
    /*递归求的两边子列的最大和*/
    maxleftsum = DivideAndConquer(List, left, center);
    maxrightsum = DivideAndConquer(List,center+1, right);

    /*下面求跨分界线的最大子列和*/
    maxleftbordersum = 0;
    leftbordersum = 0;
    for ( i = center; i >= left; i--)
    {
        leftbordersum += List[i];
        if (leftbordersum > maxleftbordersum)
        {
            maxleftbordersum = leftbordersum;
        }
    }//左边扫描结束

    maxrightbordersum = 0;
    rightbordersum = 0;
    for ( i = center +1 ; i < right; i++)
    {
        rightbordersum += List[i];
        if (rightbordersum > maxrightbordersum)
        {
            maxrightbordersum = rightbordersum;
        }
    }
    
    //下面返回治的结果
    return Max3( maxleftsum,maxrightsum,maxleftbordersum + maxrightbordersum);
}

int MaxSubseqSum3(int List[], int N)  //保持与前面两种求最大子列和的方法函数头相同
{
    return DivideAndConquer(List,0,N-1);  //直接return一个函数，然后把值带进去，在输入的时候，要把return的函数里面输入的东西都满足了。
}


//使用在线处理法
//核心思想，如果整数序列a1,a2,...,an的最大子列和是ai,ai+1,...,aj，那么必定有从i到l ak>=0，对任意l属于i到j成立，因此，一旦发现当前子列和为负，则重新开始考察一个新的子列

int MaxSubseqSum4(int List[]. int N)
{
    int i;
    int thissum, maxsum;

    thissum = maxsum = 0;
    for ( i = 0; i < N; i++)
    {
        thissum += List[i]; //向右累加
        if (thissum > maxsum)
        {
            maxsum = thissum;
        }else if(thissum <0)
        {
            thissum = 0; //因为如果当前子列和为负，则不可能使后面的部分和增大，则抛弃这部分子列。
        }
    }
    return maxsum;
}