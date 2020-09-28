//选择排序的伪码描述
void SelectionSort(int List[], int N)
{
    int i;
    for ( i = 0; i < N; i++)
    {
        //从List[i]到List[N-1]中找最小元，并将其位置赋给MinPosition,注意是把位置赋给MinPositon
        MinPosition = ScanForMin(List, i, N-1);

        //将未排序部分的最小元换到有序部分的最后位置
        Swap(List[i], List[MinPosition]);
    }   
}