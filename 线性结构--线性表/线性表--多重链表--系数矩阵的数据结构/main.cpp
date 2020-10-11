typedef  enum{Head, Term} NodeTag;

struct TermNode{
    //非零元素结点
    int Row,Col;
    elementtype Value;
};

typedef struct MNode *PtrToMNode;
struct MNode{
    //矩阵结点的定义
    PtrToMNode Down,Right;
    NodeTag Tag;
    union URegion
    {
        PtrToMNode Next;
        struct TermNode Term;
    };
};
typedef PtrToMNode Matrix; //稀疏矩阵类型定义
Matrix HeadNode[MAXSIZE]; //MAXSIZE是矩阵最大规模，即行数、列数的最大值。
//HeadNode是为了能快速指向各行或列链表头结点的指针数组。