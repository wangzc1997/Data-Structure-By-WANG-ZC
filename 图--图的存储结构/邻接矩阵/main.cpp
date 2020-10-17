/*
邻接矩阵
就是用矩阵表示图中各顶点之间的邻接关系和权值。在有权值的图中，因为0可能被误认为是权值，所以常用无穷表示没有边。

1.无向图的邻接矩阵一定是对称矩阵。因此，在具体存放邻接矩阵时只需存放上(或下)三角矩阵的元素即可。需要存储的元素个数是|V|*|V-1|/2

2.某个顶点，比如v0顶点的度就是对应行或者列中非零元素的个数。 （在无向无权图中）

3.在有向图中，某个顶点的 出度 就是看 对应行中 非0或者非无穷大的个数。 某个顶点的 入度 就是 对应列中 非0或者非无穷大的个数。

4.用邻接矩阵方法存储图，很容易确定图中任意顶点之间是否有边相连，只需考察邻接矩阵对应的元素即可；确定一个顶点的所有邻接点，也只需邻接矩阵
对应的一行(或一列)；但是，要确定图中有多少边，则必须按行(或按列)对每个元素进行检测，所花费的时间代价是O(|v|^2)。这就是邻接矩阵来存储图的局限性
*/

/*
下面是邻接矩阵存储的C语言描述
首先分析一下用邻接矩阵来存储图，需要什么？
1.需要用一个二维数组来存储表示顶点间相邻关系的邻接矩阵
2.用一个一维数组来存储顶点信息
3.另外还要存储图的顶点数和边数
*/

#define MaxVertexNum 100  //最大顶点数设为100
#define INFINITY 65535 //这个就是那个无穷大，表明两点之间没有边，65535是双字节无符号整数的最大值
typedef int Vertex; //用顶点下标表示顶点，为整型
typedef int WeightType;  //边的权值设为整型
typedef char DataType; //顶点存储的数据类型设为字符型 如果顶点没有数据，则Data[]可以不用出现，自然DataType也不用出现，其实此时也是方便起见，
                        //事实上关于顶点的信息可以有很多，一般使用一个struct类型来描述。
/*图结点的定义*/
typedef struct GNode *PtrToGNode;
struct GNode{
    int NV;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum]; //邻接矩阵，但是采用固定大小的数组可能会导致比较大的空间浪费，实际上，最好根据实际情况，动态分配大小。
    DataType Data[MaxVertexNum];   //存顶点的数据，若顶点无数据，此时Data[]可以不用出现
};
typedef PtrToGNode MGraph; 


/*
有了图的结构与类型定义，可以先创建一个包含全部顶点但没有边的图，再逐条插入边，从而创建一个无向网图的数据对象。其中edge是边的类型，边结构中
包含两个端点V1,V2，还有边的权重Weight， Edge是指向这个结构的指针。
下面是无向网图的初始化程序 (用邻接矩阵表示),程序的时间复杂度和空间复杂度都是O(Nv^2)
*/

//边的定义
typedef struct ENode * PtrToENode;
struct ENode
{
    Vertex V1,V2;   //注意此时是有向边<V1,V2>,如果是无向图，可以插入两条有向边
    WeightType Weight; //权重
};
typedef PtrToENode Edge;

MGraph CreateGraph(int VertexNum)
{
    //初始化一个有VertexNum个顶点没有边的图
    Vertex V,M;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode)); //建立图
    Graph -> NV = VertexNum;
    Graph->Ne = 0; //先把点弄好，边后来在插入
    for (V = 0; V < Graph->NV; V++)
    {
        for (W=0; W<Graph->NV; W++)
        {
            Graph->G[V][W] = INFINITY;
        }
    }
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
    //插入边<V1,V2>
    Graph->G[E->V1][E->V2] = E->Weight;
    //若是无向图，还要插入边<V2,V1>
    Graph ->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    Vertex V;
    int NV,i;

    scanf("%d", &NV); //读入顶点个数
    Graph = CreateGraph(NV);  //初始化有NV个顶点但没有边的图

    scanf("%d", &(Graph->Ne)); //读入边数
    if (Graph ->Ne != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode)); //建立边界点
        for (i = 0; i< Graph->Ne; i++)
        {
            scanf("%d%d%d",&E->V1， &E->V2, &E->Weight); //如果权重不是整型，则注意修改读入格式
            InsertEdge(Graph, E);
        }
        
    }
    

    //如果顶点有数据的话，读入数据  指的是之前我们设置的char Data。
    for (V = 0; V<Graph->NV; V++)
    {
        scanf("%c", &(Graph->Data[V]));
    }
    
    return Graph;
}
/*
邻接矩阵时一种表示各类图的简洁的数据结构。但我们发现，不论图中的边的数量多还是少，我们都花费了O(|V|^2)的存储空间。这对稠密图是一种高效的方法。
但是如果面对的是稀疏矩阵，则邻接矩阵中大多数项为0(或无穷)，形成了所谓的稀疏矩阵，就会浪费很多空间。 同时，有些操作也会经常访问邻接矩阵中0或无穷
代表的无效元素，也会浪费很多时间。

我们可以考虑用链表来做这个，用链式存储的方式来减少空间浪费的问题。

*/

