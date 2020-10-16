/*
邻接表是图的一种顺序存储与链式存储相结合的存储方法。就是对于图G中的每个顶点vi,将所有邻接于vi的顶点vj链成一个单链表，这个单链表就称为顶点vi的
邻接表，再将所有 点 的邻接表表头放到一个数组中，就构成图的邻接表。 在邻接表表示中有两种结点结构。

一种是顶点表的结点结构，由顶点数据域(Data)和指向第一条邻接边的指针域(FirstEdge)构成。
另一种是边表(即邻接表)结点，由邻接点域(AdjV)和指向下一条林街边的指针域Next构成。如果是网图，还要在增设一个存储边上信息(如权值)的域Weight。

下面是邻接表表示的图结构和类型声明
*/

#define MaxVertexNum 100  //最大顶点数设为100
typedef int Vertex; //用顶点下标表示顶点，整型
typedef int WeightType; //边的权值设为整型
typedef char DataType; //顶点存储的数据类型设置为字符型

//边的定义
typedef struct ENode* PtrToENode;
struct ENode{
    Vertex V1,V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

//邻接点的定义
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
    Vertex AdjV; //邻接点下标
    WeightType Weight; //边权重
    PtrToAdjVNode Next; //指向下一个邻接点的指针
};

//顶点表头结点的定义
typedef struct Vnode{
    PtrToAdjVNode FirstEdge; //边表头指针
    DataType Data; //存顶点的数据
    //很多情况下， 如果顶点没有数据，此时Data可以不用出现
}AdjList[MaxVertexNum]; //AdjList是邻接表类型，应该就是把Vnode命名为AdjList

//图结点的定义
typedef struct GNode *PtrToGNode;
struct GNode{
    int NV;
    int Ne;
    AdjList G; //邻接表
}; 
typedef PtrToGNode LGraph;  //以邻接表方式存储的图类型

//下面是图的初始化过程
LGraph CreatGraph(int VertexNum)
{
    //首先初始化一个有VertexNum个顶点但没有边的图
    Vertex V;
    LGraph Graph; //类似于int a

    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->NV = VertexNum;
    Graph->Ne = 0; //此时还没有边
    //初始化邻接表头结点
    //注意：这里默认顶点编号是从0开始，到Graph->NV-1 和之前的邻接矩阵的一样
    for (V =0; V < Graph->NV; V++)
    {
        Graph->G[V].FirstEdge = NULL;  //此时还没有边，所以邻接表G的firstEdge是NULL
    }
    return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode;  //开始引入邻接点了
    //插入边<V1,V2>，为V2建立新的邻接点
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;

    //将V2插入至V1的表头
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    //若是无向图，还要插入边<V2,V1>
    //为V1建立新的邻接点
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;
    //将V1插入V2的表头
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    Vertex V;
    int NV, i;

    scanf("%d",&NV);
    Graph = CreatGraph(NV);

    scanf("%d",&(Graph->Ne)); //读入边数
    if (Graph->Ne != 0) //如果有边
    {
        E = (Edge)malloc(sizeof(struct ENode)); //建立边结点
        /*读入边，格式为 起点 终点 权重， 插入邻接矩阵*/
        for (i = 0; i < Graph->Ne; i++)
        {
            scanf("%d%d%d",&E->V1,&E->V2, &E->Weight);
            InsertEdge(Graph, E);
        }
    }

    //如果顶点有数据的话，读入数据
    for (V = 0; V<Graph->NV; V++)
    {
        scanf("%c", &(Graph->G[V].Data)); //G就是邻接表
    }
    
    return Graph;
}

/*
若无向图中有|V|个顶点和|E|条边，则它的邻接表需要|V|个头结点和2|E|个表边结点。 显然在边稀疏时， (|E|<<|V|(|V|-1)/2)的情况下，用邻接表
表示图比邻接矩阵节省存储空间，当和边相关的信息较多时更是如此。

在无向图中，顶点vi的度正好是第i个链表中的结点数。
但在有向图中，我们只能计算vi顶点的出度。如果要计算入度，我们还要对所有头结点的各个链表进行遍历，找到值为i的结点个数，才是Vi顶点的入度。
所以，可以建立一个有向图的逆邻接表，我们把方向都给调整过来，比如原来，我有v0结点指向了v1和v3结点，现在就是反过来，v1和v3结点都指向了v0，
则自然可以计算出此时的v0的出度，则也自然是原来V0的入度！！！ 参考P214.

在建立邻接表和逆邻接表时，若输入的顶点信息为顶点的编号，则建立邻接表的复杂度为O(|V| + |E|)，否则，需要查找才能得到顶点在图中位置，时间复杂度为
O(|V|*|E|).

在邻接表上容易找到任一顶点的第一个邻接点和下一个邻接点，但要判定！任意！ 两个顶点之间是否有边或者弧项链，则需要搜索第i个或者第j个链表，因此
不如邻接矩阵方便。

*/