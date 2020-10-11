//用C语言描述链栈
/*栈的链式存储结构与单链表类似，但是其操作受限制，插入和删除操作只能在链栈的栈顶进行，栈顶指针Top就是链表的头指针。
有时候为了简便算法，采取链栈带一个空表头结点，表头结点后面的第一个结点就是链栈的栈顶结点。栈中其他结点通过指针Next连接起来，
栈底结点的Next为NULL。
*/
typedef struct SNode * PtrToSNode;
struct SNode
{
    elementtype Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

//带头结点的链栈主要操作的实现


//创建一个带头结点的链栈
Stack CreatStack()
{
    //构建一个堆栈的头结点，返回该结点的指针
    Stack S;

    S = malloc(sizeof(struct SNode));
    S ->Next = NULL;
    return S; //这个S就是链栈的头结点
}

//判断链栈是不是空的
bool isempty(Stack S)
{
    return(S->Next == NULL);
}

//压入栈
bool push(Stack S, elementtype X)
{
    PtrToSNode tmpcell;

    tmpcell = (PtrToSNode)malloc(sizeof(struct SNode));
    temcell -> Data = X;
    tmpcell -> Next = S->Next; //因为是从链头插进去的
    S->Next = tmpcell;
    return true;
}

//Po出栈
elementtype Pop(Stack S)
{
    //删除并返回堆栈S的栈顶元素:包含两个操作：删除S的栈顶元素，返回栈顶元素的值
    PtrToSNode firstcell;
    elementtype Topelem;

    if (isempty(S))
    {
        printf("堆栈空");
        return ERROR;
    }else
    {
        firstcell = S->Next;
        Topelem = firstcell -> Data;
        S->Next = firstcell -> Next;
        free(firstcell);
        return Topelem;
    } 
}