/*
简单插入排序的核心思想是：将待排序的一组序列分为已排好序和未排序的两个部分；初始状态下，已排序序列仅包含第一个元素，未排序序列中的元素为除去第一个以外的N-1个元素，此后，
将未排序序列中的元素逐一插入到已排序的序列中。如此往复，经过N-1次插入后，未排序序列中元素个数为0，此时排序完成。


具体到第k-1次插入，对应待插入元素应为第k个元素，也就是未排序序列中第一个元素，插入过程是：将第k个元素，和第k-1个元素(就是已排序序列中最后一个元素)进行比较，若大于第k-1个
元素，则该次循环结束(是从小到大的顺序)；否则，将两个元素交换，在比较该数与第k-2个元素之间的大小，依次往复，知道该数比它当前位置的前一个元素大；或该数已经交换到第1个位置，
则第k-1次循环结束。

*/
void InsertionSort(elementtype A[], int N)
{
    int P, i;
    elementtype tmp;

    for (P = 1; P < N; P++)
    {
        tmp = A[P]; //取出未排序序列中第一个元素
        for (i = P; i>0 && A[i-1]>tmp; i--) //从p开始往前推，P之前的都是已排序序列
        {
            A[i] = A[i-1];  //依次与已排序序列中元素比较并右移
        }
        A[i] = tmp; //放进合适位置
        
    }
    

}
/*
由该算法代码可以看出，空间复杂度上，简单插入排序仅需要常数个额外空间；时间复杂度上，函数有两个嵌套的循环，每个循环进行O(N)次比较和交换，因此整个简单插入排序的
平均时间复杂度为O(N^2)。在最坏的情况下，对应每一个P，要进行P-1次比较和交换，即每次都要从未排序序列第一个挪到已排序序列第一个。 总共花费O(N^2)次操作；
在最好的情况下，也就是对排好序的序列进行排序，第二个循环在第一个(A[i-1]>tmp)比较时就跳出，因此总共花费O(N)次操作。

简单插入排序是稳定的排序！！！数值相同的两个记录不会发生相对位置上的改变。

*/