/*
所谓基准排序，就是用一个基准数e将集合S分解为 不包含e在内的两个小集合S1,S2,其中S1中的元素均大于e，
S2中的元素均小于e，记|S|代表集合S中的个数，这样如果|S1|>=K，则说明第K大数在S1中，如果|S1|正好
等于K-1，则说明e是第K大数；否则第K大数在S2中，并且是S2中的第K-|S1|-1大数，然后可以用类似的思路
继续在S1和S2中查找
*/

//这是一种将大问题分解为小问题的思路，由于小问题的解决采用与大问题同样的思路，则使用递归
//伪代码
ElementType FindKthLargest(ElementType S[], int K)
{   
    选取S中的第一个元素e;
    根据e将集合S（不包含e）分解为元素集合S1,S2;
    if (|S1| >= K)
    {
        return FindKthLargest(S1,K);
    }else if (|S1|<K-1)
    {
        return FindKthLargest(S2,K-|S1|-1);
    }else
    {
        return e;
    }
}