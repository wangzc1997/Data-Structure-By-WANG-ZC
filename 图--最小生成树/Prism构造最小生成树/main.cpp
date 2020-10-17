/*
最小生成树的构造过程：
对n个顶点的连通图来说，其最小生成树可以由图中的n-1条边构成，我们要做的就是如何从图中的边里面选择适当边的方法。从任何一个顶点出发，构建过程从初始只有
这个顶点的“当前树”开始，不断加入边和相关顶点到当前树中，使当前树不断生长，最终成为最小生成树。

Prim算法构建最小生成树的过程就是当前树的生长过程，n个顶点的网图只要通过n-1步的生长就可以完成。

Prim算法的形式化描述：
假设G=(V,E)为一网图，其中V为网图中所有顶点的集合，E为网图中所有带权边的集合。设置两个集合Vt和Et，其中集合Vt用于存放G的最小生成树中的顶点，集合Et存放G中最小生成树的边，
即当前树T = {Et,Vt}.令集合Vt的初始值为Vt={v0},集合Et的初值为空集。 Prim算法的思想就是 从所有的u属于Vt， v属于V-Vt的边中，选取具有最小权值的边(u,v)，然后
将顶点v加入Vt中，将边(u,v)加入集合Et中，如此不断重复，直到Vt= V时，最小生成树构造完毕，这时集合Et中包含了最小生成树所有的边。

Prim算法的过程描述

Vt = {v0}, Et={空集};
 while(Vt ！= V){
     (u,v) = min{ Wuv| u 属于 Vt，v属于V-Vt};
     Et = Et + {(u,v)};
     Vt = Vt + {v};

 }
结束

为实现Prim算法，顶点用0~|V|-1编号，顶点之间没有边用权值无穷大表示，并设置两个辅助一维数组parent和dist。其中数组parent用来保存当前树的顶点生长过程，每个顶点的父顶点
parent[0] = -1表示v0为根。 dist[j]用来保存顶点vj到Vt顶点的边的最小权值，即存储各顶点与当前树的距离，如果vj属于当前树，则dist[j]=0，如果vj不属于当前树
并且不是当前树所有顶点的邻接点，则用dist[j] = 无穷表示。

在程序中，我们用顶点编号代表顶点，假设初始状态时，Vt={0}，这是有dist[0] = 0，表示顶点v0已经加入集合Vt中。然后从dist中不断选取权值最小的边(u,v)，每选取一条边
就将dist[v] = 0（当前树生长至v）。由于顶点v从集合V-Vt进入集合Vt后，两个集合的内容就发生了变化，就需要对每个 w 属于V-Vt，更新数组parent和dist的内容：若收录v使得
dist[w]变小，则将dist[w]更新为(v,w)的权值，并将v设置为w的父顶点。

下面是用邻接矩阵存储图的Prim算法的实现。 由于最后生成的 最小生成树 肯定是个 稀疏图 ，只有Nv-1条边，所以我们用邻接表存储它。
*/

#define ERROR -1 //错误标记，表示生成树不存在

int Prim(MGraph Graph, LGraph MST)  //将最小生成树保存为邻接表存储的图MST，返回最小权重和
{
    WeightType dist[MaxVertexNum], TotalWeight;
    Vertex parent[MaxVertexNum], V, W;
    int VCount;
    Edge E;

    //初始化，默认初始点下标是0
    for (V = 0; V < Graph->NV; V++)
    {
        dist[V] = Graph->G[0][V];
        parent[V] = 0; //暂且定义所有顶点的父结点都是初始点0
    }
    TotalWeight = 0; //初始化权重和
    VCount = 0; //初始化收录的顶点数
    
    //创建包含所有顶点但没有边的图，用邻接表版本
    MST = CreateGraph(Graph->NV);
    E = (Edge)malloc(sizeof(struct ENode));

    //将初始点0收录进MST
    dist[0] = 0;
    VCount ++;
    parent[0] = -1;

    while (1)
    {
        V = FindMinDist(Graph, dist);
        /*V 表示未被收录顶点中dist最小者*/
        if (V == ERROR)
        {
            break;
        }
        //将V及相应的边 <parent[V],V > 收录进MST
        E -> V1 = parent[V];
        E->V2 = V;

        E->Weight = dist[V];
        InsertEdge(MST, E);
        TotalWeight += dist[V];
        dist[V] = 0;
        VCount++;

        for (W = 0; W < Graph->NV; W++) //对于图中的每个顶点W
        {
            if (dist[W] != 0 && Graph->G[V][W] < INFINITY)
            {
                //若W是V的邻接点并且未被收录
                if (Graph -> G[V][W] < dist[W])
                {
                    //若收录V使得dist[W]变小
                    dist[W] = Graph[V][W]; //更新dist[w]
                    parent[W] = V; //更新树
                }
                
            }
            
        }
        
    }
    if (VCount < Graph->NV){
        TotalWeight = ERROR;
    }
    return TotalWeight;

}

//下面是求当前树与非当前树顶点之间的最小距离的算法FindMinDist函数
Vertex FindMinDist(MGraph Graph, WeightType dist[])
{
    //返回未被收录顶点中dist最小者
    Vertex MinV, V;
    WeightType MinDist = INFINITY;

    for (V =0 ; V < Graph->NV; V++)
    {
        if (dist[V] != 0 && dist[V] < MinDist)
        {
            //若V未被收录，且dist[V]更小
            MinDist = dist[V];
            MinV = V; //更新对应顶点。
        }
        
    }
    
    if (MinDist < INFINITY) //若找到最小dist
    {
        return MinV;  //返回对应顶点下标
    }else
    {
        return ERROR; //若这样的顶点不存在，返回-1作为标记。
    }
    
    
}
/*
在这个以邻接矩阵为存储结构的Prim算法中，第一个初始化辅助数组的for循环的执行次数为|V|-1; CreateGraph用O(|V|)建立起一个空的邻接表表示的MST，接下来的while循环最多执行
|V|-1次，但是其中又要执行FindMinDist和一个for循环，执行次数为2(|V|-1)^2，所以Prim算法的时间复杂度为O(|V|^2).这对于稠密图是比较好的方法，也因为我们用邻接矩阵
表示Graph。

但是对于稀疏图来说，这个时间是不理想的，一个改进是，改用邻接表作为存储结构并更换FindMinDist函数，改用最小堆结构。另一种方法就是Kruskal算法，时间复杂度可以改进到
O(|E|lov|V|).

*/