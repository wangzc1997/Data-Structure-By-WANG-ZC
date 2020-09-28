//通常使用结构的嵌套来定义单向链表结点的数据类型，例如
typedef struct Node *PtrToNode;

struct Node{
    ElementType Data; //store data
    PtrToNode Next; //point to next node
};

/*通常我们所说的给定一个单链表，就是给定一个指向该链表头结点的指针，所以
单链表类型list可以定义为链表结点结构的指针*/
typedef PtrToNode List;

/*链表是一种动态数据结构，在进行动态存储分配的操作中，C语言提供了
几个常用的函数，malloc，free，例如，要申请大小为struct node结构的
动态内存空间，由下面语句实现*/
PtrToNode p = (PtrToNode)malloc(sizeof(struct node));

/*单向链表的常用操作*/
//将结点t插在结点p之后的语句为
t -> Next = p -> Next;
p -> Next = t;

//如果需要在链表的头上插入一个结点t
t->Next = head; //指针更新
head = t; //值更新

//删除结点
//1.找到被删除结点的前一个结点p 2.删除p之后的结点
t = p->Next;
p->Next = t -> Next;
free(t);
//如果删除的是第一个结点
t = head;
head = head -> next;
free(t);

//单向链表的遍历
p = head;
while ( p != NULL)
{
    对p所指结点的信息进行处理
    p = p -> Next;
}


//链表的建立
/*两种常见的插入结点方式，1.在链表的头上不断插入新结点。 2.在链表尾部不断
插入新结点，但是要有一个临时的结点指针一直指向当前链表的最后一个结点，以
方便新结点的插入，应该就是确定尾部的位置作用*/



//单链表的逆转
/*
问题描述：一个单链表，涉及一个函数Reverse将链表L就地逆转，不要申请新的结点，将链表的第一个元素转化为最后一个元素，第二个元素转为倒数第二个元素，依次类推
思路：每次循环开始前我们都要面临两个链表，其中old_head是一个待逆转的链表，New_head是一个已经逆转好的链表，每次循环都是old_head的第一个元素插入到New_head
的头上，这轮循环执行好后，old_head和new_head还是分别指向新的逆转链表和已经逆转好的链表

循环程序的主体部分就是将old_head的第一个元素插入到new_head头上，同时更新old_head,new_head的值。当将old_head的第一元素插入到new_head头上后，我们需要知道
old_head链表新的头结点在哪里，因此还要有一个temp临时变量。

所以循环主体为
tmep = old_head -> next;
old_head -> next = new_head;
new_head = ole_head;
old_head = temp;
*/

List Reverse(List L)
{
    PtrToNode old_head, new_head, temp;

    old_head = L; //初始化当前旧表头为L
    new_head = NULL; 
    while (old_head)
    {
        temp = old_head -> next;
        old_head ->next = new_head;//这个的意思是old_head指向new_head，那么此时的old_head就已经换到new_head阵营了（指针上）
        new_head = old_head;  //将当前旧表头逆转为新表头
        old_head = temp; //更新旧表头（之前的old_head->next变成了此时的old_head）
    }
    L = new_head;
    return L;
}
