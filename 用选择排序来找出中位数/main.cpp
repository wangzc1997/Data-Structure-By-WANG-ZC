/*选择排序的基本思路：从待排序列中找出值最大的元素，然后将该最大值元素跟待排序列的第一个元素交换，一直重复，使待排序列越来越短，
当待排序列只剩一个元素的时候，排序就完成了。

可以使用两重循环来实现上述算法
外层循环:i 从i到n-1表示 数组中待排序列的下标区间
内层循环：目标是在数组i到n-1区间里找出一个最大值
*/

ElementType Median(ElementType A[], int N)
{
    int i,j,Maxposition;
    ElementType TmpA;

    for ( i = 0; i < N-1; i++)
    {
        Maxposition = i;
        for ( j = i+1; j < N; j++)
        {
            if (A[j] > A[Maxposition])
            {
                Maxposition = j;
            }

        }

        /*下面将最大值与待排序列的第一个元素A[i]交换*/
        //外循环循环一次 i才加1.
        TmpA = A[i];
        A[i] = A[Maxposition];
        A[Maxposition] = TmpA;
        
    }
    return A[(N-1)/2];
    
}