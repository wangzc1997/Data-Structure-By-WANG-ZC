/*
归并排序是建立在归并操作基础上的一种排序方法，归并操作，是指将两个已排序的子序列合并成一个有序序列的过程。

基本原理：将大小为N的序列看成N个长度为1的子序列，接下来将相邻子序列两两进行归并操作，形成N/2个长度为2的有序子序列；然后在进行相邻子序列两两归并操作，如此一直循环，
直到形成一个长度为N的序列。

归并排序的核心操作在于归并操作的实现，归并操作的过程如下：
1.首先申请额外的空间用于放置两个子序列归并后的结果
2.设置两个指针分别指向两个已排序子序列的第一个位置，然后比较两个指针指向的元素，将较小的元素放置到已申请的额外空间内，并将当前位置向后移动一格，重复以上过程，
直到某一子序列的指针指向该序列的结尾，这时候将另一个指针所指向序列的剩余元素全部放置到额外空间内，归并操作结束。

这个其实也是分而治之思想的逆理解，就是将原序列划分成两个等长子序列，再递归的排序这两个子序列，最后再调用归并操作合并成一个完整的有序序列。

下面的Merge是对两个有序序列的归并操作，MSort是核心的归并排序递归函数，而MergeSort是使用了统一用户接口的排序函数。
*/

//L=左边起始位置， R = 右边起始位置， RightEnd = 右边终点位置
void Merge(elementtype A[], elementtype TmpA[], int L, int R, int RightEnd)
{
    //将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列
    int LeftEnd, NumElements, Tmp;
    int i;

    LeftEnd = R - 1; //左边终点位置
    Tmp = L;  //有序序列的起始位置
    NumElements = RightEnd - L + 1; //总共有这些个数据元素

    while (L <= LeftEnd && R <= RightEnd)
    {
        if (A[L] < A[R])
        {
            TmpA[Tmp++] = A[L++];  //将左边元素复制到TmpA
        }else
        {
            TmpA[Tmp++] = A[R++]; //将右边元素复制到TmpA
        }
    }
    while (L <= LeftEnd)  //意思就是右边的子序列已经全部进入TmpA数组里面了，只剩下左边的子序列还没有放进去
    {
        TmpA[Tmp++] = A[L++];  //直接复制左边剩下的
    }
    while (R <= RightEnd)
    {
        TmpA[Tmp++] = A[R++]; //直接复制右边剩下的
    }
    
    for (i = 0; i < NumElements; i++,RightEnd--)  //这个是从右往左逐个复制回原数组的，这个i只是起到了一个计数器的作用
    {
        A[RightEnd] = TmpA[RightEnd]; //将有序的TmpA[]复制回A[]   
    }
}

void  Msort(elementtype A[], elementtype TmpA[], int L, int RightEnd)
{
    int Center;

    if (L < RightEnd)
    {
        Center = (L + RightEnd)/2;
        Msort(A, TmpA, L, Center);
        Msort(A, TmpA, Center + 1, RightEnd);
        Merge(A, TmpA, L, Center+1, RightEnd);
    }
    
}

void MergeSort(elementtype A[], int N)
{
    elementtype *TmpA;
    TmpA = (elementtype *)malloc(N * sizeof(elementtype));

    if (TmpA != NULL)
    {
        Msort(A, TmpA, 0, N-1);
        free(TmpA);
    }else
    {
        printf("空间不足");
    }
    
    
}

/*
由非递归的算法描述可以看到，每一趟归并操作，需要进行O(N)次比较，而一共将进行O(log2 N)趟归并操作，因此整个归并排序的时间复杂度为O(N log2 N),哪怕在最坏情况下的
时间复杂度也一样。

空间复杂度上，由于归并操作过程中需要额外的空间用于保存已排序的子序列，因此，如果实现方法正确的话，整个归并排序的空间复杂度为O(N).

若使用递归方法进行实现，并在Merge函数内部申请空间，如果不及时释放，则可以证明将耗费O(Nlog2N)的额外空间；若每次都执行申请和释放，则除了耗费O(N)的额外空间外，
还增加O(N)次malloc和free操作。这儿也就是为什么在Merge之外(MergeSort中)申请了额外空间，并且一直将这个数组的地址通过指针方式传递给递归函数的原因。

此外，相对于快速排序和堆排序，归并排序虽然耗费更多的额外空间，但整体的排序过程是稳定的，关键字值相同的两个元素在排序过程中并不会发生相对位置上的变化。


虽然归并排序看上去稳定而且时间复杂度不高，但是在实际应用中，开辟大块的额外空间并且将两个数组的元素来回复制是很耗时的，所以归并排序一般不用于内部排序。
但是他是进行外部排序的非常有用的工具。


*/