/*
队列也可以采用链式存储结构。但队列的头front必须指向链表的头结点（方便删除元素），队列的尾rear必须指向链表的尾结点，用来在后面添加元素。
*/

typedef struct Node * PtrToNode;
struct Node //队列中的结点
{
    elementtype Data;
    PtrToNode Next;
};
typedef PtrToNode Position;

typedef struct QNode * PtrToQNode; //队列
struct QNode
{
    Position front, rear;
    int Maxsize;
};
typedef PtrToQNode Queue;

//采用链式存储的入队和出队操作实际上是在一个链表的尾部插入结点（入队）或者在头部删除结点（出队）。
//下面是不带头结点的链式队列出队操作的代码

//判断队列是否为空
bool isempty(Queue Q)
{
    return(Q->front == NULL);
}

//在头部删除结点 出队,并返回其值
elementtype DeleteQ(Queue Q)
{
    Position frontcell;
    elementtype frontelem;

    if (isempty(Q))
    {
        printf("队列空");
        return ERROR;
    }else
    {
        frontcell = Q->front;
        if (Q->front == Q->rear) //若队列只有一个元素
        {
            Q->front = Q->rear = NULL; //删除后队列为空
        }else
        {
            Q->front = Q->front->Next;
        }
        frontelem = frontcell->Data;

        free(frontcell); //释放被删除结点空间。
        return frontelem;
    }
}
