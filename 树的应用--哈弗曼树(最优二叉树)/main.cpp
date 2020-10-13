//哈夫曼树又叫做最优二叉树

/*
问题背景：
对于同一个问题，采用不同的判定逻辑，计算效率是不一样的。
对概率大的数据有更少的比较次数，计算效率得到了提高。最优树(哈夫曼树)要解决的就是找到最好的比较判定逻辑，使得运算效率达到最高。

哈夫曼树(Huffman Tree)的定义：
我们已经知道，从树根到某个结点的路径就是从根结点沿着某个分支到达该节点的一个结点序列，路径所含的分支个数(结点个数减1)称为此路径的长度。而一棵树
的路径长度是指从从树根到其余各结点的路径长度之和。

结点的带权路径长度是指从根结点到该结点之间的路径长度与该结点上所带权值的乘积。
设一棵树有N个叶结点，每个叶结点带有权值Wk，从根结点到每个叶结点的长度为lk，则每个叶结点的带权路径长度之和就是这棵树的带权路径长度WPL。

假设有n个权值，构造有n个叶子的二叉树，这样的二叉树可以构造很多个，其中必有一个是带权路径长度最小的，这棵二叉树就是最优二叉树或哈夫曼树。
*/


/*
哈夫曼树的构造
由哈夫曼树和带权路径长度的定义可知，一棵二叉树要使其WPL值最小，就必须使权重越大的叶结点越靠近根结点，而权值越小的叶结点越远离根结点。
使用贪心算法，该算法在初始状态下将每个字符看成一棵独立的树，每一步执行两棵树的合并，而选择合并对象的原则是贪心的，即每次选择权重最小的两棵树
进行合并。具体过程如下：
1.由给定的n个权值{W1,W2,...,Wn}构造n棵只有一个叶结点的二叉树，从而得到一个二叉树的集合F = {T1,T2,...,Tn}.
 //这个集合，我们可以放在最小堆中，每次deletemin就可以把最小的给输出来
2.在F中选取根结点的权值最小和次小的两棵二叉树作为左右子树构造一棵新的二叉树，这棵新的二叉树根结点的权值为其左右子树权值之和。
3.在集合F中删除(2)中作为左右子树的两棵二叉树，并将新构造的二叉树加入到集合F中。//把新的二叉树的根结点的值Insert插回最小堆中
4.重复(2)(3),当F中只剩下一棵二叉树时，这棵二叉树就是所要建立的哈夫曼树。

下面是代码实现
*/
typedef struct HTNode * HuffmanTree; //哈夫曼树类型
struct HTNode
{
    int weight; //结点权值
    HuffmanTree left; //指向左子树
    HuffmanTree right;
};

HuffmanTree Huffman(MinHeap H)
{
    //这里最小堆的元素类型为HuffmanTree
    //假设H->size个权值已经存在H->Data[]->weight里
    int i, N;
    HuffmanTree T;

    BuildHeap(H); //将H->Data[]按照权值weight调整为最小堆
    N = H->size;
    for (i = 1; i < N; i++)  //做H->size-1次合并
    {
        T = (HuffmanTree)malloc(sizeof(struct HTNode)); //建立一个新的根结点
        T->left = DeleteMin(H); //从最小堆中删除一个结点，作为新T的左子结点
        T->right = DeleteMin(H); //从最小堆中删除一个结点，作为新T的右子结点
        T->weight = T->left->weight + T->right->weight; //计算新权值
        Insert(H, T); //将新的T插入回最小堆中
    }
    return DeleteMin(H); //最小堆中最后一个元素即是指向哈夫曼树 根结点 的指针。
}

/*
哈夫曼树的一个最主要的应用就是哈夫曼编码。

哈夫曼编码：给定一段字符串，如何对其中的字符进行编码？使得该字符串的编码存储空间最小？
(字符串进行编码，同样地，这些编码也必须能通过对应的解码还原出原字符串)

常见的ASCII字符大约有一百多个，所以一般可以用Log2 128=7，再加上一位校验码，所以一般用8位即一个字节来表示一个字符。
但一般文本中每个字符出现的频率不一样，都用8位来表示一个字符是比较浪费的。所以要对字符重新编码。
要获得更好的压缩效果，采用等长的编码是不好的。所以我们可以让频率高的字符编码短一些，出现频率低的字符编码长一些。
同样问题也就来了：如果允许不同字符采用不同长度的编码的情况下，如何保证解码能顺利实现？ 即不能出现二义性。

不产生二义性的关键在于任何一个字符的编码都不能是另一个字符的前缀，因此哈夫曼编码也称为前缀编码。

而采用哈夫曼树生成方法可以保证构成正确的文本前缀编码。通过设置在每个结点的左分支记为0，右分支记为1。某一字符的编码可以通过组合从根结点到该字符
叶结点的路径上标注的01得到。注意前缀编码树的特点是每个字符必是叶结点，且树中没有度为1的结点，否则会出现解码二义性的问题。

在生成哈夫曼树的时候，还是按照上面哈夫曼树的构造，先调整为最小堆，然后用贪心算法，每次合并两个最小的，依次类推，构造了哈夫曼树。




*/