typedef struct PolyNode *PtrToPolyNode;

struct PolyNode
{
    int coef;
    int expon;
    PtrToPolyNode Next;
};
typedef PtrToPolyNode Polynomial;

