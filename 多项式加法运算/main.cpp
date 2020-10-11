//采用链表结构来存储多项式的非零项的实现方法
/*
用链表表示多项式时，每个链表结点存储多项式中的一个非零项，包括系数、指数两个数据域以及一个指针域。下面是采用不带头结点的单向链表
表示一元多项式，并按照指数递减的顺序排列各项。

而对于链表存放的两个多项式进行加法运算可以使用两个指针P1和P2，初始时，P1和P2分别指向这两个多项式的第一个结点（指指数最高的项）
通过循环不断比较P1和P2指向的各结点，比较结果有下面三种情况：
1.两数据项指数相等，则系数相加，若结果不为0，则作为结果多项式对应项的系数，连同指数一并存入结果多项式。P1,P2分别指向多项式的下一项，进行循环
2.P1中的数据项指数较大，P2不变，将P1的当前项存入结果多项式，并使得P1指向下一项，再进行新一轮的比较和处理。
3.P2中的数据项指数较大，P1不变，则P2的当前项存入结果多项式，并使P2指向下一项，再进行新一轮的比较。
当某一多项式最后一个结点处理完时，停止上述求和过程，将未处理完的另一个多项式的所有结点依次复制到结果多项式中去。

下面是链表存储的两个多项式加法运算的具体实现
*/

typedef struct PolyNode *PtrToPolyNode;

struct PolyNode
{
    int coef;
    int expon;
    PtrToPolyNode Next;
};
typedef PtrToPolyNode Polynomial;

int compare(int e1, int e2)
{
    //比较两项指数e1和e2，根据大小等于三种情况分别返回1，-1,0
    if (e1>e2)
    {
        return 1;
    }else if (e1 < e2)
    {
        return -1;
    }else
    {
        return 0;
    }
}

void attach(int coef, int expon, Polynomial *PtrRear) //polynomial 多项式的
{
    /*
    由于在本函数中需要改变当前结果表达式尾项指针的值，所以函数传递进来的是尾项结点指针的地址，*PtrRear指向尾项
    */
   Polynomial P;

   //申请新结点，并赋值
   P = (Polynomial)malloc(sizeof(struct PolyNode));
   P->coef = coef;
   P->expon = expon;
   P->link = NULL;
   /*将P指向的新结点插入到当前结果表达式尾项的后面*/
   (*PtrRear) -> link = P;   //这一步其实是最关键的。
   *PtrRear = P; //修改尾项结点指针
}

Polynomial PolyAdd(Polynomial P1, Polynomial P2)
{
    Polynomial front, rear, temp;
    int sum;

    //为方便表头插入，先产生一个临时空结点作为 结果多项式 链表头
    rear = (Polynomial)malloc(sizeof(struct PolyNode));
    front = rear; //由front记录结果多项式链表头结点
    while (P1 && P2)
    {
        switch (compare(P1->expon, P2->expon))
        {
        case 1:
            attach(P1->coef, P1->expon,&rear);
            P1= P1->link;
            break;
        case -1:
            attach(P2->coef, P2->expon,&rear);
            P2= P2->link;
            break;
        case 0: //两数据项指数相等
            sum = P1->coef + P2->coef;
            if (sum)
            {
                attach(sum, P1->expon, &rear);
            }
            P1 = P1->link;
            P2 = P2->link;
            break;       

        }
    }
    //把未处理完的另一个多项式的所有结点依次复制到结果多项式中去
    for (; P1; P1 = P1->link)
    {
        attach(P1->coef,P1->expon, &rear);
    }
    for (; P2; P2 = P2->link)
    {
        attach(P2->coef,P2->expon, &rear);
    }    
    rear->link = NULL;
    temp = front;
    front = front->link;

    free(temp);
    return front;
}