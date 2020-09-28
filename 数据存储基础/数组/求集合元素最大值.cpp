//求集合元素的最大值，集合元素存放在数组A中，数组大小为N
/*就是通过循环控制变量i从数组的第二个元素，下标为1，开始逐个查找，每次
都与当前已知的最大值进行比较，当发现更大值时更新Curmax*/

//elementtype could be int, double, etc.
ElementType Max(ElementType S[], int N)
{
    int i;
    ElementType Curmax = 0; //将第一个元素记为最大值，即基准值
    for ( i = 1; i < N; i++)
    {
        if (S[i] > Curmax)
        {
            Curmax = S[i];
        }
        
    }
    return Curmax; //此时返回的是最大值，如果要返回最大值的位置，则return i。
    
}
