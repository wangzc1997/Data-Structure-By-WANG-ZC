/*
顺序存储用一维数组来表示是很合适的

！！由于线性表的运算有插入删除等，所以表的长度是动态可变的。
因为数组的容量设计的足够大。线性表的数据从Data[0]开始依次顺序存放，由于当前线性表中的实际元素个数可能未达到Maxisze个，所以需要
用一个变量Last来记录当前线性表中最后一个元素在数组中的位置，此时Last起指针的作用（实际上是数组下标），始终指向线性表中最后一个元素，
表空时Last = -1.
*/

//为了体现数据组织的整体性，通常将数组Data和变量Last封装成一个结构作为顺序表的类型

typedef int Position;
//这个position就是数组的整型下标，从0开始
//之前提到的位序是指第几个，从1开始

typedef struct LNode *PtrToLNode;
struct LNode
{
    elementtype Data[Maxsize];
    Position Last;  //指的是数组的整型下标 从0开始。
};

typedef PtrToLNode List; /*此时LNode是一个包含数组的结构，当我们实现各种针对顺序表的操作时，直接将该结构作为函数参数传递显示不合适，
使用结构指针传递效率更高，所以我们把List定义为结构指针，这样可以利用List定义线性表L；
*/
List L;
/*通过L，可以访问相应线性表的内容。
比如下标为i的元素，可以通过L-> Data[i]访问
线性表的长度可以通过L->Last+1得到。
*/

//基于上述存储方式来实现主要操作如下：

//初始化:即构造一个空表。步骤如下
/*
step1:动态分配表结构所需要的存储空间
step2:将表中Last指针置为-1，表示表中没有数据元素。
*/
List MakeEmpty()
{
    List L;
    L = (List)malloc(sizeof(struct LNode));
    L -> Last = -1;
    return L;
}


//查找：在线性表中查找与给定值X相等的数据元素
/*
由于线性表的元素都存储在数组Data中，所以这个查找过程就是在数组里的顺序查找。
***顺序查找***  平均时间复杂度为0(n)
从第一个元素a1起，依次和X比较，直到找到一个与X相等的数据元素，返回它在顺序表中的存储下表。
或者查边整个表都没有与X相等的元素，则返回错误信息ERROR。
*/

#define ERROR -1  /*将错误信息ERROR的值定义为任一负数都可以*/

Position find(List L, elementtype X)
{
    Position i = 0;
    while (i <= L->Last && L -> Data[i] != X)
    {
        i++;
    }
    if (i > L->Last)
    {
        return ERROR;
    }else
    {
        return i; /*因为返回的是存储位置*/
    }
}


//插入：指在表的第i(i >= 1 && i <= n+1)个位序（从1开始计数）上插入一个值为X的新元素
// == 在第i个元素之前插入新元素（因为元素是从0开始放的），插入后使得原长度为n的数组元素系列(a1,a2,...,ai-1,ai,ai+1,...,an)变成(a1,a2,...,ai-1,X,ai,ai+1,...,an)
//当插入位序为1时，代表插入到序列最前端；为n+1时，代表插入到序列最后
/*
顺序表的插入 按照如下步骤：
step1：将ai~an顺讯向后移动(移动次序是从an到ai)，为新元素让出位置
step2：将X置入空出的第i个位序
step3：修改Last指针(相当于修改表长)，使之仍指向最后一个元素
*/
bool insert(List L, elementtype X, int i)
{
    //在L的指定位序i前插入一个新元素X
    //位序i元素的数组位置下标是i-1
    Position j; 

    if (L->Last == Maxsize - 1)
    {
        printf("表满");
        return false;
    }

    if (i<1 || i > L->Last+2)  //这个i指的是位序，范围是1~n+1,即Last+1
    {
        printf("位序不合法");
        return false;
    }

    for ( j = L->Last; j >= i-1; j--)   //这个j其实就是下标，而这个i是位序
    {
        L->Data[j+1] = L->Data[j]; //将位序i及以后的元素顺序向后移动
    }
    L->Data[i-1] = X; //新元素插入第i位序，其数组下标为i-1
    L->Last++; //Last仍然指向最后一个元素
    
    return true;
}
/*
上述程序的注意事项
1.数组有Maxsize个存储单元，要检查表空间是否满了，在表满的情况下不能做插入，否则产生溢出错误
2.检验插入位序的合法性 //其实可以直接检验下标的合法性
3.注意数据的移动次序和方向  //在顺序表上做插入操作平均需移动表中一半的数据元素，显然时间复杂度为O(n)
*/


//删除:是指表中 位序为i(i属于1~n)的元素从线性表中去掉，删除后使原长度为n的数组元素序列(a1,a2,...,ai-1,ai,ai+1,..,an)成为长度为(a1,a2,...,ai-1,ai+1,...,an)
/*
两个步骤完成：
step1:将ai+1~an顺序向前移动，ai元素被ai+1覆盖。
step2:修改Last指针(相当于修改表长)使之仍指向最后一个元素。
*/
bool delete(List L, int i)
{
    //从L中删除位序为i的元素，该元素坐标为i-1
    Position j;

    if (i < 1 || i > L->Last+1) //i是位序，此时是检查空表和删除位序的合法性
    {
        printf("位序%d不存在元素",i);
        return false;
    }
    for ( j = i; i < L->Last; j++)
    {
        L->Data[j-1] = L->Data[j]; //将位序i+1及以后的元素顺序向前移动
    }
    L->Last--; //undate Last
    return true;
}
/*
注意事项
1.位序i的取值一定要是1~n，否则元素不存在
2.表空时无法使用删除，i<1 ||i>L->Last+1都是对表空做检查
3.删除ai后，数据已不存在，如果需要用，可以先把ai取出来，再做删除
4.时间复杂度为0(n).
*/


