//双向链表结点的数据类型与单向链表类似，只是多了一个前驱单元指针
typedef struct DNode *PtrToDNode;

struct DNode
{
    ElementType Data;
    PtrToDNode Next;
    PtrToDNode Previous;
};
typedef PtrToDNode Dlist;


//双向链表的插入
//p指向的结点后插入新结点t的方法
t -> Previous = p;
t -> Next = p->Next;
p->Next->Previous = t; //把之前p后面的结点的previous也要更新
p->Next = t;
//顺序不可改变
