/*
之前顺序表的存储特点是 用物理上的相邻实现逻辑上的相邻，要求用连续的存储单元顺序存储线性表的各元素。
但是链表结构可以避免顺序表的缺点，通过链建立起数据元素之间的逻辑关系，此时对线性表的插入和删除就不要移动其他数据，直接对链进行修改

对于链表结构，有n个数据单元，每个数据单元由数据域和链接域两部分组成，数据域用于存放数值，链接域是结构指针，线性表的顺序是用各结点上指针构成的指针链实现的。
为了访问链表，需要先找到链表的第一个单元，实际应用中常用header的指针来指向链表的第一个单元，并用他表示一个具体的链表
*/
typedef struct LNode *PtrToLNode;
struct LNode
{
    elementtype Data;
    PtrToLNode Next;  
};
typedef PtrToLNode Position; //这个位置是结点的地址
typedef PtrToLNode List;
//同样也可以用List定义具体的表头结点指针，该指针就代表了一个链式表
List L;
/*
无论是顺序存储还是链式存储，我们都用一致的接口，例如都是LNode、List、Position等来定义线性表。因为两种具体的存储方式都是对同一个抽样概念的实现
*/

//一些操作
//求表长：在顺序存储中求表长是很简单的，直接返回Last+1.但是在链式存储中，需要将链表从头到尾遍历一遍
//方法：设一个移动指针p和计数器cnt，初始化后，p从表头开始逐步往后移动，同时cnt+1.当后面不再有结点时，这个cnt就是表长
int length(List L)
{
    Position p;
    int cnt = 0;
    p = L; //这个其实相当于p = L[0]，但是这是链表，相当于p指向第一个链结点，即指向了表头
    while (p)
    {
        p = p ->Next;
        cnt++;
    }
    return cnt;
}

//查找：1.按序号查找。2.按值查找
/*
1.按序号查找
对于顺序存储很简单，直接去L->Data[K-1]
对于链表，需要从头遍历，判断当前结点是否是第K个，若是，则返回该结点的值，否则继续后一个，直到表结束为止。如果没有第K个结点则返回错误信息。
*/
#define ERROR -1 
//fk == findkth
elementtype fk(List L, int K)
{
    Position p;
    int cnt = 1; //位序从1开始
    p = L; //p指向L的第一个结点 就是p= L[0]
    while (p && cnt < K)
    {
        p = p->Next;
        cnt ++;
    }
    if ((cnt == K)&& p)
    {
        return p -> Data; //把当前序号的值取出来
    }else
    {
        return ERROR;
    }
}

/*
2.按值查找
也是从头到尾进行遍历，直到找到为止
判断当前结点其值是否等于X，若是，则返回结点的位置，否则继续后一个，知道表结束为止。找不到则返回错误信息。
*/
#define ERROR -1

Position find(List L, elementtype X)
{
    Position p = L; 

    while (p && p->Data != X)
    {
        p = p->Next;
    }
    if (p)
    {
        return p;
    }else
    {
        return ERROR;
    }
}
//上面两种查找的时间复杂度均为0(n)


//插入：在指定位序i(1~n)前插入一个新元素。插入元素后，位序i的范围变成1~n+1
/*
当插入位序i为1时，代表插入到链表的头结点。
当i为n+1时，代表插入到链表的最后。
基本思路：如果i不为1，则找到位序为i-1的结点pre，若存在，则申请一个新结点并在数据域填上相应值X，然后将新结点插入到结点pre之后，返回结果链表
如果不存在则返回错误信息
*/
#define ERROR NULL //用空地址表示错误

List insert(List L, elementtype X, int i)
{
    Position tmp, pre;

    tmp = (Position)malloc(sizeof(struct LNode));
    tmp -> Data = X;
    if (i==1)
    {
        tmp -> Next = L;
        return tmp;
    }else
    {
        int cnt = 1;
        pre = L; //pre指向L的第一个结点 因为我们需要遍历来找到位置
        while (pre && cnt < i-1)
        {
            pre = pre->Next;
            cnt++;
        }
        if (pre = NULL || cnt != i-1) //所找结点不在L中
        {
            printf("插入位置错误\n");
            free(tmp);
            return ERROR;
        }else //找到了待插结点的前一个结点pre
        {
            tmp -> Next = pre->Next;
            pre -> Next = tmp;
            return L;
        }
    }
}
/*
!!!!!!!
在上述插入程序中，有一个问题，就是L，既作为函数参数，同时也作为函数返回值，保证新的L值能够被带回来。
但是一旦遇上插入不成功的时候，return的就是NULL，L也变成了NULL，这就不对了。所以一个解决方法就是
为链表新增一个空的”头结点“，真正的元素链接在这个空结点之后，这样的好处是，无论在哪里插入或者删除，L的值
一直指向固定的空结点，不会改变，下面是"带头结点的链式表"的插入函数，时间复杂度为0(n)
下面这个代码，就不存在插入头结点的问题了。
*/
bool insert(List L, elementtype X, int i)  //之前是List，现在说bool
{
    Position tmp, pre;
    int cnt =0;

    //查找位序为i-1的节点
    pre = L;
    while (pre && cnt <i-1)
    {
        pre = pre->Next;
        cnt ++;
    }
    if (pre == NULL || cnt != i-1)
    {
        printf("插入位置参数错误\n");
        return false;
    }
    else
    {
        tmp = (Position)malloc(sizeof(struct LNode));
        tmp->Data = X;
        tmp ->Next = pre->Next;
        pre->Next = tmp;
        return true;
    }
}

//删除：在单向链表中删除指定位序i的元素，首先需要找到被删除结点的前一个元素，然后再删除结点并释放空间。 时间复杂度为0(n)
bool delete(List L, int i)
{
    //此时默认L有头结点,即有个空结点
    Position tmp,pre;
    int cnt = 0;

    //查找位序为i-1的结点
    pre = L;
    while (pre && cnt < i-1)
    {
        pre = pre -> Next;
        cnt ++;
    }
    if (pre == NULL || cnt != i-1 || pre->Next == NULL)
    {
        printf("删除位置参数错误\n");
        return false;
    }
    else
    {
        //此时就是找到了前一个结点
        tmp = pre->Next;
        pre->Next = tmp->Next;
        free(tmp;)
        return true;
    }
}
/*我们讨论的主要是以单向链表的形式存储线性表，这样的结构可以使每个结点找到其后继结点很容易，但要找到其前驱结点，必须要从头到尾遍历。
如果我们需要前后查找都很容易，则可以采用双向链表表示，占用空间相对大些，因为每个结点都要用到两个指针域*/

//广义表与多重链表
//广义表：GList
/*
广义表中的结点可能有两种情况：
1.单元素，需要有一个域来存储该单元素的值
2.广义表，需要有一个域来指向另一个链表。 
对于每个结点来说，上述两个域只可能需要其中的一种，所以可以用C语言中的共用体Union来实现这两个域的复用
*/
typedef struct GNode *PteToGNode;
typedef PtrToGNode GList;
struct GNode{
    int Tag; //Tag标志域，0表示该结点是单元素；1表示该结点是广义表
    union 
    {
        elementtype Data;
        GList sublist; //子表指针域
    } URegion;
    
    PtrToGNode Next;
    
};

