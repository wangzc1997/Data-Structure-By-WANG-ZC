/*
后缀表达式求值过程中，我们需要暂存不能马上参与运算的运算数，对这些运算数的管理方法是先入后出的原则，所以需要
使用一个堆栈来对这些暂存的运算数在求值过程中进行管理

具体操作：
1.当读入的是一个运算数时，把它压入栈中
2.当读入的是一个运算符时，就从堆栈中弹出适当数量的运算数，对该运算进行计算，计算结果再压回到栈中
3.当处理完整个后缀表达式后，堆栈顶上的元素就是表达式的结果值。

在下面的程序中，假设后缀表达式的对象（运算数和运算符号）之间用空格分割开来，运算数为正数
1.2 1.3 + 2 4.2 * -
代码如下
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100 //操作数序列可能的最大长度
#define INFINITY 1e9  //代表正无穷
typedef double elementtype; //将元素类型具体化

typedef enum {num, opr, end} Type;

//影响好如何把堆栈--链式存储实现的函数放进来
Type GetOp(char * Expr, int * start, char * str)
{
    //从*start开始读入下一个对象（操作数或运算符），并保存在字符串str中
    int i = 0;
    //跳过表达式前的空格
    while ((str[0] = Expr[(*start)++])==' ');

    while (str[i]!=' ' && str[i] != '\0')
    {
        str[++i] = Expr[(*start)++];
    }
    if (str[i] == '\0') //如果读到输入的结尾
    {
        (*start)--; // *start指向结束符
    }
    str[i] = '\0'; 结束一个对象的获取

    if (i == 0)
    {
        return end; //读到了结束
    }else if (isdigit(str[0]) ||isdigit(str[1]))
    {
        return num;
    }else
    {
        return opr;
    }

}

elementtype Postfixexp(char * Expr)
{
    //调用GetOp函数读入会追表达式并求值
    Stack S;
    Type T;
    elementtype Op1, Op2;
    char str[MAXOP];
    int start = 0;

    /*申请一个新堆栈*/
    S = CreatStack(MAXOP);

    Op1 = Op2 = 0;
    while ((T = GetOp(Expr, &start, str))!= end)
    {
        if (T==num)
        {
            Push(S, atof(str));
        }else
        {
            if (!isempty(S))
            {
                Op2 = Pop(S);
            }else
            {
                Op2 = INFINITY;
            }
            if (!isempty(S))
            {
                Op1 = Pop(S);
            }else
            {
                Op2 = INFINITY;
            }
            switch (str[0])
            {
            case '+':
                Push(S, Op1 + Op2)
                break;
            case '-':
                Push(S, Op1 - Op2)
                break;
            case '*':
                Push(S, Op1 * Op2)
                break;
            case '/':
                if (Op2!=0.0)
                {
                    Push(S, Op1/Op2);
                }else
                {
                    printf("错误：除法分母为零\n")；
                    Op2 = INFINITY;
                }
                break;                                            
            default:
                printf("错误：位置运算符%s \n", str);
                Op2 = INFINITY;
                break;
            }
            if (Op2 >= INFINITY)
            {
                break;
            }
        }
    }
    if (Op2 < INFINITY)//如果处理完了表达式
    {
        if (!isempty(S)) //而此时堆栈正常
        {
            Op2 = Pop(S); //记录计算结构
        }else
        {
            Op2 = INFINITY; //否则标记错误
        }
    }
    free(S); //释放堆栈
    return(Op2);
    
}

int main()
{
    char Expr[MAXOP];
    elementtype f;

    gets(Expr);
    f = Postfixexp(Expr);
    if (f < INFINITY)
    {
        printf("% .4f\n", f);
    }else
    {
        printf("表达式错误\n");
    }
    return 0;
    
}

//应用堆栈将中缀表达式转换为后缀表达式的基本过程：
/*
从头到尾读取中缀表达式的每个对象，对不同对象按不同的情况处理。对象分为下列6种情况
1.如果遇到空格则认为是分隔符，不需要处理
2.若遇到运算数，则直接输出  //与后面的呼应起来，我们要处理的就是运算符
3.若是左括号，则将其压入堆栈中
4.若遇到的是右括号，表明括号内的中缀表达式已经扫描完毕，将栈顶的运算符弹出并输出，直到遇到左括号（左括号也出栈，但不输出）
5.若遇到的是运算符，若该运算符的优先级大于栈顶运算符的优先级时，则把它压栈。若该运算符的优先级小于等于栈顶运算符时，将栈顶运算符
弹出并输出，再比较新的栈顶运算符，按同样的处理方法，直到该运算符大于栈顶运算符优先级为止，然后将该运算符压栈。 （把优先级大的先pop出去）
6.若中缀表达式中的各对象处理完毕，则把堆栈中存留的运算符一并输出。

注意：在P82的案例中，左括号一旦入栈，则优先级降到最低。


*/