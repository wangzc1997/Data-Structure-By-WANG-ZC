/*
快速排序，也是交换排序的一种，就是和我们之前讨论集合中位数的时候一样，就是采用分治法，将问题的规模减小，然后再分别进行处理。

原理：将未排序元素根据一个作为基准的“主元”Pivot分为两个子序列，其中一个子序列的记录均大于主元，而另一个子序列均小于主元，然后递归地对这两个子序列用类似的方法进行排序。

具体步骤为：
1.选择一个主元，并与最后一个元素交换。
2.设置两个指针low和high，初值分别指向第一和倒数第二个位置。
3.low从左向右扫描，其位置左侧为已遍历或交换过的比主元小的元素；high从右向左扫描，其位置右侧为已遍历或交换过比主元大的元素。首先low指向的位置向右扫描，若遇到比主元大的
元素，则停止。然后从high指向的位置向左扫描，若遇到比主元小的元素，则停止。
4.若low和high没有错位，则high和low指向的元素交换位置。
5.重复3、4直至low和high错位，将基准(也就是那个主元)，与A[low]换位，这样就完成了一次划分，以主元为边界分别划分为大于和小于主元的两个子序列。
6.递归的对两个子序列用同样的方法进行快速排序。


下面是快速排序的时间复杂度分析：

平均时间复杂度：O(Nlog2 N),相对于其他内部排序，快速排序的平均时间效率是最高的。

最好的情况：每一次选取主元都恰好把序列分为两个等长的序列，随着递归层次的加深，子序列的数量翻倍，但在每一递归层次上，比较总次数都是O(N)次，而递归层次是log2 N. 由此可见，
快速排序最好时间复杂度应为O(Nlog2 N)

最坏的情况，每次选取主元都划分成1和N-1，快速排序的执行时间复杂度就接近于冒泡排序，可能导致O(N^2)的时间效率。

为了避免最坏结果，在确定主元时需要有一定技巧，一种比较好的方法是：将A[low],A[high],A[(low + high)/2]三者关键字的中值作为主元，这样有可能避免
在基本有序的序列中进行快速排序时时间复杂度出现最坏情况的可能。

另外一个问题是：由于快速排序是递归实现的， 如果待排序列的规模比较小，递归的副作用就凸显出来了，效果甚至不如简单的插入排序。 所以更专业一些的处理就是，在递归过程中
检验当前子问题的规模，当其小于某个阈值时就不继续递归，而是直接调用插入排序解决问题。

我们在设置主元的时候，可以这样设置：将最左边、最右边、中间的三个元素的中位数作为主元，并且把三个元素调整成“最左元<= 主元 <= 最右元”的状态，此时最右元一定
大于等于主元，所以我们可以保持最右元的位置不变，且后续根本不用考虑这个元素，然后我们不是把主元与最后一个元素交换，而是换到倒数第二个元素的位置上，并且返回主元的值。
*/

elementtype Median3(elementtype A[], int left, int right)
{
    int center = (left + right)/2;
    if (A[left] > A[center])
    {
        Swap(A[left], A[center]);
    }
    if (A[left] > A[right])
    {
        Swap(A[left],A[right]);
    }
    if (A[center]> A[right])
    {
        Swap(A[center],A[right]);
    }
    
    //下面只要把A[center]换到A[right-1]即可
    Swap(A[center], A[right-1]);
    return A[right- 1];  //返回基准元
}

void Qsort(elementtype A[], int left, int right)
{
    int Pivot, Cutoff, low, high;

    if (Cutoff <= right - left)  //如果规模足够大， 超过了阈值Cutoff，则进入快速排序的递归过程，否则进入插入排序
    {
        Pivot= Median3(A, left, right); //调用函数确定主元
        low = left;
        high = right - 1;
        while (1)
        {
            while (A[++low] < Pivot)
            {
                ;
            }
            while (A[--high] > Pivot)
            {
                ;
            }
            if (low < high)
            {
                Swap(A[low], A[high]);
            }else
            {
                break;
            }
        }
        Swap(&A[low], &A[right - 1]); //在把主元从right-1的位置给挪回来，放到正确的位置
        Qsort(A,left, low-1);  //递归解决左边
        Qsort(A,low + 1, right); //递归解决右边
        
    }else
    {
        InsertionSort(A+left, right-left+1); //元素太少，规模不够， 采取插入排序
    }

}

void QuickSort(elementtype A[], int N)
{
    Qsort(A, 0, N-1);  //这一步是跟其他几种排序算法一样，统一函数接口。
}

/*
空间复杂度上，由于快速排序需要进行至少log2 N层的递归，因此需要至少O(log2 N)深度的栈空间，若每次划分的子组大小不够平均，则栈空间的深度更大，在最坏的情况下
将导致接近O(N)的栈空间深度。

快速排序是不稳定的，相同的两个元素的相对位置会随着排序发生改变。

ps:如果遇到了数据元素与主元相同的情况，我们选择停下来交换(最坏时时间复杂度为O(NlogN))，而非不理他 继续移动指针(最坏时时间复杂度为O(N^2)).
*/