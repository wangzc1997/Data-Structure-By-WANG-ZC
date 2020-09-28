/*
之前是使用了一个基准数，分成两大部分，但是使用递归的话，需要创建一个临时数组，把整个数组放进去，然后分成两部分。
下面的方法可以避免创建临时数组
思路：先从左边扫描，如果发现比e小的元素则暂停；再从数组右边扫描，遇到大于等于e的元素则暂停。如果发现左右两个暂停点是错位的，把它们交换一下。
然后从左右暂停点重复上述步骤，直到左右扫描在中间某处想回。此时相会的位置就是基准e把两个集合分开的位置，把e换到这个位置上，那么左边的就是S1，右边的就是
S2。
*/

void swap(elementtype *x, elementtype *y)
{
    elementtype temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
//fkl == find kth largest
elementtype fkl(elementtype S[], int k, int left, int right)
{
    elementtype e = S[left]; //简单选取最左边的元素为基准
    int l = left, r = right;

    while (1)
    {
        while (left <= right && e <= S[left])
        {
            left ++;  //从左边扫描，如果发现比e小的元素则暂停
        }
        while (left < right && e > S[right])
        {
            right --;
        }

        if (left < right)
        {
            swap(&s[left],&s[right]);
        }else
        {
            break;
        }
    }
    swap(&S[left-1],&S[right]); //将基准换到两集合之间

    if ((left - l -1)>=k) //left-l-1代表了集合S1的大小
    {
        return fkl(S,k,l,left-2); //在集合S1中找
    }else if ((left-l-1) < k-1) //在集合S2中找
    {
        return fkl(S, k-(left-l-1)-1, left, r);
    }else
    {
        return e;
    }
}

//如果要求集合S的中位数，就可以直接调用上面的fkl函数
elementtype Median(elementtype S[], int N)
{
    return fkl(S, (N+1)/2 , 0, N-1);
}