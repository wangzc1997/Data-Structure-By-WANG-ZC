/*
栈的顺序存储结构通常由一个一维数组和一个记录栈顶元素位置的变量组成，另外我们还可以用一个变量来存储堆栈的最大容量MAXSIZE，这样方便判断
什么时候堆栈是满的，我们用一维数组Data[MAXSIZE](下标0~MAXSIZE-1)存储一个栈的元素。
习惯上将栈底放在数组下标小的那端，栈顶位置用一个整形变量Top记录当前栈顶元素的下标值！！！！
当Top指向-1时，表示空栈
当Top指向MAXSIZE-1时，表示满栈。
*/
typedef int Position;
typedef struct SNode * PtrToSNode;
struct SNode
{
    elementtype * Data;
    Position Top; //栈顶指针
    int MAXSIZE;  
};
typedef PtrToSNode Stack;

//顺序栈的创建
Stack CreatStack( int MAXSIZE)
{
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Data = (elementtype *)malloc(MAXSIZE*sizeof(elementtype));
    S->Top = -1;
    S->MAXSIZE = MAXSIZE;
    return S;
}

//入栈操作：执行之前，首先判别栈是否满，若不满，Top+1，并将新元素放入到Data的top位置上。
bool isfull(Stack S)
{
    return(S->Top == S->MAXSIZE-1);
}

bool Push(Stack S, elementtype X)
{
    if (isfull(S))
    {
        printf("堆栈满");
        return false;
    }else
    {
        S->Data[++(S->Top)] = X;
        return true;
    }  
}

//出栈操作Pop：执行pop时首先判别站是否空，若不空，返回Data[Top],同时将Top-1；否则要返回一个elementtype类型的特殊错误标志，即ERROR，不过需要提前define一下
bool isempty(Stack S)
{
    return(S->Top == -1);
}

elementtype Pop(Stack S)
{
    if (isempty(S))
    {
        printf("堆栈空");
        return ERROR;
    }else
    {
        return(S->Data[(S->Top)--]);
    }
}

//双堆栈结构！！！！用一个数组来实现两个堆栈，且充分利用数组空间。
//两个栈分别从数组的两头开始向中间生长，当两个栈的栈顶指针相遇时，表示两个栈都满了
//双堆栈的结构只是比标准堆栈多了一个栈顶指针
typedef int Position;
typedef struct SNode * PtrToSNode;
struct SNode
{
    elementtype *Data;
    Position TOP1;
    Position TOP2;
    int MAXSIZE;
};
typedef PtrToSNode Stack;

//双堆栈的创建
//只是需要初始化两个栈顶指针，方法是令Top1 = Top2 = Maxsize。
bool Push(Stack S, elementtype X, int Tag)
{
    /*Tag作为区分两个堆栈的标志，取值为1和2*/
    if (S->Top2 - S->Top2 == 1)
    {
        printf("堆栈满\n");
        return false;
    }
    else
    {
        if (Tag == 1)
        {
            S->Data[++(S->Top1)] = X;
        }
        else
        {
            S->Data[--(S->Top2)] = X;
        }
        return true;
        
    }
    
}
elementtype Pop(Stack S, int Tag)
{
    if (Tag == 1)
    {
        if (S->Top1 == -1)
        {
            printf("堆栈1空\n");
            return ERROR;
        }else
        {
            return S->Data[(S->Top1)--];
        }
    else
    {
        if (S->Top2 == S->Maxsize)
        {
            printf("堆栈2空\n");
            return ERROR            
        }else
        {
            return S->Data[(S->Top2)++];
        }
        
        
    }
    
        
        
    }
    
}