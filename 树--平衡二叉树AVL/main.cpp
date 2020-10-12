/*
对于二叉搜索树进行查找的时间复杂度是根据查找过程中的比较次数来定的，比较式从根结点到叶结点的路径进行的，取决于树的深度。树深在最好的情况下
查找的复杂度是O(logN)，即完全二叉树。当二叉树退化成线性表(单枝树的极端情况)，查找的复杂度是O(N).

假定二叉搜索树的每个结点的查找概率都是相同的，我们称查找所有结点的比较次数的平均值为树的“平均查找长度”ASL
ASL = 树的深度 * 该层的结点数(累加)/所有结点数

事实证明，一棵树的ASL越小，则其结构越好，与完全二叉树越接近，查找的时间复杂度越接近O(logN).所以为了提高二叉搜索树的查找效率，应尽可能
创建枝繁叶茂的树，而避免树枝过长、过少。

最好的树结构就是满二叉树(完美二叉树)，其从根到叶结点的各条路径都是相同的，我们称这种树是完全平衡的。但是，通常情况下二叉搜索树的结点插入顺序
并不是事先确定的，动态查找(插入和删除)总是要改变树的结构，不可能做到完全平衡，所以需要找出一种方法，既能保证插入和删除正常进行又能保证二叉搜索树
的查找性能不退化，尽可能接近平衡。
上述问题有两个：
1.确定一个接近平衡的标准
2.如何在动态查找过程中进行平衡化处理，使之保持平衡。

下面就引出了平衡二叉树的定义AVL。
*/

/*
平衡二叉树AVL树 要么是一个空树，要么具有下列性质的非空二叉搜索树：
1.任一结点的左右字数均为AVL树
2.根结点左右子树高度差的绝对值不超过1.

对于二叉树的任一结点T，其平衡因子BF定义为BF(T) = HL - HR,其中HL HR分别是左右子树的高度。 （平衡因子的计算都是从下向上的）

有了平衡因子的定义，AVL树任一结点左右子树高度差的绝对值不超过1，即BF属于集合{-1,0,1}，这就是平衡的量化标准
*/

/*
平衡二叉树的调整
当向AVL树插入新结点时，该结点的平衡因子可能不在上述集合内，所以需要对局部进行旋转调整，使得调整后的树达到平衡。

1.单旋调整
右单旋：当发现被插入结点C、发现问题的结点A、以及它们之间路径上的结点B三个结点向右排成一线，就称这种右子树的不平衡状态为RR型不平衡(向右倾斜)
将B作为AC的父结点，A处于左子树、C作为右子树，若B有左子树，则将左子树置为A的右子树。保证该小区域是仍然是平衡二叉树。
同样的还有左单旋，来应对LL型不平衡。 

2.双旋调整
三个相关结点的倾斜是先左后右的排列形式，成为LR型不平衡，解决方法就是左右双旋
对应的还有RL型不平衡，需要右左双旋。

下面是AVL树的插入操作的算法(通常用递归算法来实现插入操作)
AVL树的数据结构中除了一般二叉树的数据成员外，还需要附加平衡信息。在实际的插入操作汇总，我们假设结点的附加信息为以该节点为根的子树的高度，
定义为整型的Height。当然也可以用平衡因子BF来取代height。
*/
typedef struct AVLNode * Position;
typedef Position AVLTree; //AVL树类型
typedef struct AVLNode{
    elementtype Data;
    AVLTree left;
    AVLTree right;
    int Height; //结构多了个height
};

int Max(int a, int b)
{
    if (a > b)
    {
        return a;
    }else
    {
        return b;
    }
    
    //return a>b?a:b;
}

AVLTree Insert(AVLTree T, elementtype X)
{
    if (!T) //T是空树
    {
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Data = X;
        T->Height = 1;
        T->left = T->right = NULL;//插入空树的情况
    }else if (X < T->Data) 
    {
        T->left = Insert(T->left, X);
        //如果需要左旋
        if (GetHeight(T->left) - GetHeight(T->right) == 2)
        {
            if (X < T->left->Data)
            {
                T = SingleLeftRotation(T);
            }else
            {
                T = DoubleLeftRightRotation(T);
            }//插入左子树结束
        }
        
    }else if (X > T->Data)
    {
        T->right = Insert(T->right, X);
        //如果需要右旋
        if (GetHeight(T->left) - GetHeight(T->right) == -2)
        {
            if (X > T->right->Data)
            {
                T = SingleRightRotation(T);
            }else
            {
                T = DoubleRightLeftRotation(T);
            }//插入右子树结束
            
            
        }
        
    }//else X == T->Data 无需插入
    T->Height = Max(GetHeight(T->left),GetHeight(T->right)) + 1;
    return T;   
}

AVLTree SingleLeftRotation(AVLTree A)
{
    /*
    A必须要有一个左子结点B
    将A和B做左单旋，更新A与B的高度，返回新结点B
    
    */
    AVLTree B = A->left;
    A->left = B->right;
    B->right = A;
    A->Height = Max(GetHeight(A->left), GetHeight(A->right)) + 1;
    B->Height = Max(GetHeight(B->left), A->Height) + 1;

    return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{
    /*
    A必须有一个左子结点B，且B必须有一个右子结点C
    将A,B与C做两次单旋，返回新的根结点C
    
    */
    //将B与C做右单旋，C被返回
    A->left = SingleRightRotation(A->left);
    //将A与C做左单旋，C被返回
    return SingleLeftRotation(A);
}