/*
希尔排序的基本原理是：将待排序的一组元素按一定间隔分为若干个序列，然后每个序列分别进行插入排序。 开始的时候，设置的间隔较大，然后在每轮排序中将间隔逐步减小，
直到间隔为1，就是前面讲的简单插入排序，但是这时候其实大部分都已经排好序了。

希尔排序将间隔定义为一组增量序列，用来分割待排序列，即将位置之差等于当前增量的元素归属于同一个子序列，并分别进行插入排序，排好后再选取下一个增量，划分子序列再次排序，
直到最后一个增量(一般最后一个增量为1)。

*/
void ShellSort(elementtype A[], int N)
{
    //希尔排序，用Sedgewick增量序列 1 5 19 41 109 209 505 929 2161 3905 8929 16001 36289 64769 146305 260609 587521 1045505 2354689 4188161 
    int Si, D, P, i;
    elementtype tmp;

    //此处只列出一小部分增量
    int Sedgewick[] = {929,505,209,109,41,19,5,1,0};

    for (Si = 0; Sedgewick[Si]>=N;Si++)
    {
        ;  //因为我们肯定不能让增量序列的值超过总共待排序列的长度呀
    }

    for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si]) //因为Sedgerick数组，Si代表序号，但是数组的值是从大到小的，D每一次循环，都是换了一个增量
    {
        for (P = D; P < N; P++)   
        {
            tmp = A[P];
            for (i = P; i>=D&& A[i-D] > tmp; i-=D)  //这个其实就是前面简单插入排序的过程，我们要把后面的未排序序列往前面已排序序列里面挪
            {
                A[i] = A[i-D];  
            }
            A[i] = tmp; //跳出循环后，就是找到了要插入的位置。
            
        }
        
    }
    
    
}

/*
空间复杂度上，和简单插入排序一样，希尔排序只需要O(1)的额外空间；时间复杂度上，每一次针对某增量进行插入排序，随着增量逐渐变小，整体序列逐渐有序起来，每次插入排序的比较和
交换次数变少。

希尔排序算法的整体时间复杂度和增量序列的选取有关，目前并没有统一的最优增量序列，
使用{N/2, N/2^2,...,1}进行希尔排序时，最差情况下时间复杂度为O(N^2)。当使用增量序列{2^k -1,...,7,3,1}时，最差情况下时间复杂度为O(N^3/2)，平均时间复杂度猜想结果
为O(N^5/4),除此之外，还有上述的Sedgerick增量序列，平均时间复杂度为O(N^7/6)，最差情况是O(N^4/3)。

经验表明，希尔排序对规模以万计的待排序列会体现出比较好的效率。

和简单的插入排序不同的是，希尔排序并不是一个稳定的排序，选取不同增量进行排序时，可能导致数值相同的两个元素发生相同位置上的改变。

*/