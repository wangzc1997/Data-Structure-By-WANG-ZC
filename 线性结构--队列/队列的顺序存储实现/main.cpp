/*
队列最简单的表达方法就是用数组。一般选择，将队列头放数组下标小的位置，而将队列尾放在数组下标大的位置（注意是下标值），并用
两个变量Front和Rear分别表示队列的头和尾。 

一般初始化时，将front和rear都初始化为-1。当有元素入队，则rear加1，向右移动一格，放入队尾元素。当有元素出队，先将front向右移动1格，
即front加1，然后再删除队头元素。也就是说，队头和队尾都不固定，添加元素，则队尾rear加1，在队尾放入元素。若删除元素，则在表头去掉，表头
front加1，然后把表头元素删除。
但是这种情况有个缺陷，都不是固定的，会使得整个队列整体向后移动，这样就出现一种情况，队尾指针已经移到了最后，再有元素入队，则会溢出。而此时
整个队列前面是很空的，并不是真的满员，这种现象称为假溢出。

为了解决上述问题，一般采用循环队列，就是圆环形的那种。rear和front到达数组端点时，能折回到数组开始处，即相当于数组头和尾相接，呈环状。
当插入和删除操作的作用单元达到数组的末端时，用公式rear（或front）%数组长度，取余运算，就可以实现折返到起始单元。意思就是，我们如果设置成
首尾相接的形状，即使我们整体向后移动，但是到最后取余运算后，还可以回到最开始的情况。

上述解决方法是解决了假溢出的问题。但是在循环队列中，front和rear的初始化又是一个问题，如何根据front和rear来判别当前队列是空还是满，
如果还是按照之前的方法，即看当front和rear值是否相等，但是在循环队列中，front和rear相等的话，队列可能为空或者满，无法判别。

无法判别列满还是空的原因是front和rear提供的信息量不够。解决方法有两种：
1.另外增设一个变量，比如记录当前队列元素个数的变量size，根据变量size，我们可以直接判断队列是满还是空。
或者设置一个变量Flag记录最后一次操作是入队还是出队，若是入队，则表明是满了；若是出队，则表明是空的。
2.少用一个元素空间，当只占用n-1个空格时就认为队列满，此时队尾指针加1就会从后面赶上队头指针，因此，队满的条件是：（rear+1）%数组长度等于
Front。队空的条件仍然是：rear = front。
*/

typedef int position;
typedef struct QNode * PtrToQNode;
struct QNode
{
    elementtype *Data;
    position front, rear;
    int Maxsize;  //队列最大容量
};
typedef PtrToQNode Queue;

//下面是循环队列的创建
Queue creatQueue(int Maxsize)
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (elementtype*)malloc(Maxsize*sizeof(elementtype));
    Q->front = Q->rear = 0;
    Q->Maxsize = Maxsize;
    return Q;
}

//判断队列是否满
bool isfull(Queue Q)
{
    return((Q->rear + 1)%Q->Maxsize == Q->front); //就是队满的条件
}

//队列元素的插入
bool addQ(Queue Q, elementtype X)
{
    if (isfull(Q))
    {
        printf("队列满");
        return false;
    }else
    {
        Q->rear = (Q->rear+1)%Q->Maxsize;  //每次都要更新一下rear的位置
        Q->Data[Q->rear] = X;
        return true;
    }

}

//判断队列是否为空
bool isempty(Queue Q)
{
    return(Q->front == Q->rear);
}

//队列删除元素的操作
elementtype DeleteQ(Queue Q)
{
    if (isempty(Q))
    {
        printf("队列空");
        return ERROR;
    }else
    {
        
        Q->front = (Q->front+1)%Q->Maxsize; //直接把front加1位置上的数覆盖掉front的位置。
        return Q->Data[Q->front];
    }
}

