/*
堆排序的核心思想：利用最大堆(或者最小堆)输出堆顶元素，即最大值(最小值)，将剩下的元素重新生成最大堆(最小堆)，继续输出堆顶元素，重复此过程，直到全部元素都已输出，
得到的输出元素序列即为有序序列。

实现堆排序方法一种简单地做法就是额外开辟一个数组空间，将堆顶元素逐一放入这个数组中，最后再把数组的内容复制回原来的数组。这种方法的额外空间复杂度是O(N). 但是如果我们
不把堆顶元素放到一个数组中，而是把堆顶元素放入原来的堆里面，因为我这个堆每次要输出栈顶元素，那么肯定整个堆就变成了N-1个元素，之前有N个堆空间，所以我只要输出后，
把剩余元素给重新生成堆(此时的堆中元素个数应该减一)，然后把输出的栈顶元素放在第N个空的结点处即可。如此循环下去，直到堆中只剩一个元素，即可停止，得到一个从小到大排列的
有序序列。

堆排序方法的复杂度与简单选择排序一样，都是O(NlogN),但是不需要额外的辅助数组，所以额外空间复杂度是O(1)。

在堆排序中，和之前最大堆的代码不相同的，因为之前最大堆的代码是从i=1开始的，然后左孩子是2i，右孩子是2i+1.但是在堆排序中，数据是从第0个单元开始存放的，左孩子是2i+1，
右孩子是2i+2，所以代码需要做相应的改动。但是无论是最大堆还是堆排序，无论是建立堆还是删除堆顶元素，最核心的还是下滤，所以我们把这个用PercDown(A,i,N)来实现对A[]中的
前N个元素从第i个元素开始 向下迁移调整 的过程。
*/
void PercDown(elementtype A[], int p, int N)
{
    //将N个元素的数组中以A[p]为根的子堆调整为最大堆
    int Parent, Child;
    elementtype X;

    X = A[p]; //取出根结点存放的值
    for (Parent = p; (Parent*2 + 1) < N; Parent = Child)
    {
        Child = Parent * 2 + 1;
        if ((Child != N-1) && (A[Child]< A[Child + 1]))
        {
            Child++; //Child指向左右子结点的较大者
        }
        if (X >= A[Child]) //找到了合适位置   这个显然是最大堆
        {
            break;
        }else  //下滤X
        {
            A[Parent] = A[Child];
        }
    }
    A[Parent] = X;
}

void HeapSort(elementtype A[], int N)
{
    //堆排序
    int i;

     or (i = N/2 - 1; i>= 0; i--) //建立最大堆，这的确是建立最大堆的过程
    {
        PercDown(A,i,N); //在A数组中前N个元素，从第i个元素，开始向下迁移调整，其实这就是建立最大堆的过程。
    }
    
    for (i = N-1; i>0; i--)
    {
        //删除最大堆项
        Swap(&A[0], &A[i]);  //A[0]肯定就是最大元素，A[i]就是最大元素要放在的地方
        PercDown(A,0,i;) //在A数组中的前i个元素，从第0个元素，开始向下迁移调整。 这要是保证了i从最大N-1开始，然后逐渐变小，因为我要重新生成堆的元素数在减少。
    }
    
}