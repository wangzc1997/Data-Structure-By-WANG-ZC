/*
二叉搜索树Binary Search Tree. 也叫二叉排序树或二叉查找树，它是一种对“排序”和“查找”都很有用的特殊二叉树。

一个二叉搜索树是一棵二叉树，它可以为空。如果不为空，将满足以下性质
1.非空左子树的所有键值小于其根结点的键值
2.非空右子树的所有键值大于其根结点的键值
3，左右子树都是二叉搜索树（上面两条仍适用于左右字数）

如果对二叉搜索树进行中序遍历，则将得到一个从小到大的输出序列。
*/


/*
二叉搜索树的动态查找
二叉搜索树是施加了一定约束的特殊二叉树，之前二叉树里面的表示和操作都可以直接用于二叉搜索树，比如中序先序和后序遍历。
不同的是，二叉搜索树的查找、插入和删除操作将与其特性有关，但这些主要是算法实现的不同，而函数原型并没有什么变化。
二叉搜索树一般用链表存储。与普通二叉树相比，操作集中多了下列几个特别的函数
Position find(BinTree BST, elementtype X):从二叉搜索树BST中查找元素X，返回其所在结点的地址。
Position FindMin(BinTree BST):找到并返回最小元素所在结点的地址
Position FindMax(BinTree BST):找到并返回最大元素所在结点的地址
*/
//结构和之前的是一样的
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    //树结点定义
    elementtype Data;
    BinTree left;
    BinTree right;
};

/*
二叉搜索树的查找操作find，算法过程如下：
1.查找从树的根结点开始，如果树为空，返回NULL，表示未找到关键字为X的节点。
2.若搜索树非空，则根结点关键字与X相比较，依据比较结果，需要进行不同的处理。
若根结点关键字小于X，则满足条件的结点将不会出现在它的左子树，接下来的搜索只需在此根结点的右子树中进行。
若根结点关键字大于X，接下来就在左子树中进行
若两者比较结果是相等，搜索完成，返回指向此结点的指针。

可以使用递归算法来解决这个
*/
Position find(BinTree BST, elementtype X)
{
    if (!BST)
    {
        return NULL;
    }

    if (X > BST->Data)
    {
        return find(BST->right,X);
    }else if (X < BST->Data)
    {
        return find(BST->left,X);
    }else  
    {
        return BST; //在当前结点查找成功，返回当前结点的地址
    }
} 

//由于非递归函数的执行效率高，一般采用非递归的迭代来实现查找。只需要用while循环代替find递归调用即可
Position find(BinTree BST, elementtype X)
{
    while (BST)
    {
        if (X > BST->Data)
        {
            BST = BST -> right;
        }else if (X < BST->Data)
        {
            BST = BST->left;
        }else
        {
            break;
        }
    }
    return BST;
}

/*
查找最大和最小元素
根据二叉搜索树的定义，最小元素一定是在树的最左分支的端结点上，所谓最左分支的端结点，就是指最左分支上无左孩子的结点。
而最大元素一定是在树的最右分支的端结点上。

这就使得FindMin和FindMax较find函数更为简单，只需要从根结点开始，当其不为空时，沿着左分支或右分支逐个判断各结点的指针，直到遇到空指针为止
（此时这个指针就是最左分支的端结点）。
下面是代码（递归）
*/
Position FindMin(BinTree BST)
{
    if (!BST) //如果BST为空
    {
        return NULL;
    }else if (!BST->left) //如果没有左子树，则
    {
        return BST;
    }else
    {
        return FindMin(BST->left);
    }
}
//找到最小元素的函数，迭代
Position FindMin(BinTree BST)
{
    if (BST)
    {
        while (BST->left)
        {
            BST = BST->left;
        }
        return BST;
    }
    
}
//找到最大元素的函数，非递归 用的迭代函数
Position FindMax(BinTree BST)
{
    if (BST)
    {
        while (BST->right)
        {
            BST = BST->right;
        }
        return BST;
        
    }
    
}
//找到最大元素的函数，递归
Position FindMax(BinTree BST)
{
    if (!BST)
    {
        return NULL;
    }else if (!BST->right)
    {
        return BST;
    }else
    {
        return FindMax(BST->right);
    }
}
/*
从上述基于二叉搜索树的动态查找可以看到，实现的基本原理与基于线性表的静态二分查找类似，都是利用有序性不断缩小查找空间。而之所以有静态和动态之分
就是为了适应不同的应用需求，前者适用于一旦建立好数据，一般不需要改变，很少需要进行删除和插入操作。 而后者则适用于频繁的数据变化，插入和删除
都是基本操作。
*/


/*
下面就是二叉搜索树的插入
将元素X插入二叉搜索树BST中的关键：是要找到元素应该插入的位置，也就是我们要先查找要插入的位置，如果在BST树中找到X，说明要插入的元素已经存在，
可放弃插入操作。如果没有找到X，则查找终止的位置就是X应该插入的位置。看P129的4.26

下面是BST的插入算法
*/
BinTree Insert(BinTree BST, elementtype X)
{
    if (!BST)
    {
        BST = (BinTree)malloc(sizeof(struct TNode)); //TNode结构参考树的结构
        BST->Data =X;
        BST->left = BST->right = NULL;
    }else
    {
        if (X < BST->Data)
        {
            BST->left = Insert(BST->left, X);
        }else if(X > BST->Data)
        {
            BST->right = Insert(BST->right,X);
        }
        
    }
    return BST;
    
}

/*
二叉搜索树的删除
因为二叉搜索树BST是一个动态查找，所以如果删除结点，要比其他操作更为复杂，主要分为下面三种情况
1.要删除的是叶结点，这种情况最为简单，可以直接删除，然后再修改其父结点的指针，置空即可。
2.如果要删除的结点只有一个孩子结点，删除之前需要改变其父结点的指针，指向要删除结点的孩子结点。（让其父直接指向其孩子）
3.如果要删除的结点有左右两棵子树，有两种不同的选择，基本原则是保持二叉搜索树的有序性，一种是取其右子树中的最小元素，另外就是取其左子树的最大元素。
无论哪种选择，被选择的结点都必定最多只有一个孩子。

下面是针对上述三种情况给出的BST的删除操作算法（第三种情况，是采用右子树最小元素的删除替代策略）
*/
BinTree Delete(BinTree BST, elementtype X)
{
    Position tmp;
    if (!BST)
    {
        printf("要删除的元素未找到");
    }else
    {
        if (X < BST->Data)
        {
            BST->left = Delete(BST->left, X);
        }else if (X > BST->Data)
        {
            BST->right = Delete(BST->right,X);
        }else
        {
            //BST就是要删除的结点
            //如果被删除结点有左右两个子结点
            if (BST->left && BST->right)
            {
                //从右子树中找最小的元素填充删除结点
                tmp = FindMin(BST->right);
                BST->Data = tmp->Data; //该结点的值换成右子树最小元素的值
                //然后从右子树中删除最小元素
                BST->right = Delete(BST->right, BST->Data);
            }else
            {
                //被删除结点有一个或无子结点
                tmp = BST;
                if (!BST->left) //没有左孩子
                {
                    BST = BST->right;
                }else
                {
                    BST = BST->left;
                }
                free(tmp);
            }
        }

    }
    return BST;
}
