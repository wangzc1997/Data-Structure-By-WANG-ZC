/*
拓扑序：如果图中从V到W有一条有向路径，则V一定排在W之前，满足此条件的顶点序列成为一个拓扑序。
获得一个拓扑序的过程就是拓扑排序。

AOV如果有合理的拓扑序，则必定是有向无环图(Directed Acyclic Graph, DAG). AOV是什么？AOV(Activity on Vertex)网络指的是作用在顶点上，而边表示顶点间的先后关系。
为什么说AOV如果有合理的拓扑序，就一定是有向无环图？因为如果是有环，V必须在V之前结束，这是不可能的。

拓扑序应用的伪代码
*/
void Topsort()
{
    for (cnt = 0; cnt < |V|; cnt++)
    {
        V = 未输入的入度为0的顶点;
    }
    if (这样的V不存在)
    {
        Error（"图中有回路");
        break;
    }
    输出V，或者记录V的输出序号;
    for (V的每个邻接点W)
    {
        Indegree[W]--;
    }
    if (cnt != Graph->NV)
    {
        return false;
    }else
    {
        return true;
    }
    
    
    
    
}
//算法的时间复杂度是O(|V|^2)
//下面是对上面算法的优化，随时将入度为0的顶点放到一个容器里
void Topsort()
{
    for (图中每个顶点V)
    {
        if (Indegree[V] == 0)
        {
            AddQ(V,Q);
        }    
    }
    while (!IsEmpty(Q))
    {
        V = DeleteQ(Q);
        输出v，或者记录v的输出序号; cnt++;
        for (V的每个邻接点W)
        {
            if (--Indegree[W] == 0)
            {
                AddQ(W,Q);
            }
            
        }
        
    }
    if (cnt != |V|)  //如果cnt < |V|，则图中还有顶点，说明有回路。
    {
        Error("图中有回路");
    }
    
    
}
//下面是改进后的拓扑排序算法 C语言， 此时用邻接表表示图
bool Topsort(LGraph Graph, Vertex TopOrder[])
{
    //对Graph进行拓扑排序，TopOrder[]顺序存储排序后的顶点下标
    int Indegree[VertexNum], cnt;
    Vertex V;
    PtrToAdjNode W;
    Queue Q = CreateQueue(Graph->NV);

    //初始化Indegree[]
    for (V = 0; V < Graph->NV; V++)
    {
        Indegree[V] = 0;
    }

    //遍历图，得到Indegree[]
    for (V = 0; V < Graph->NV; V ++)
    {
        for (W = Graph->G[V].FirstEdge; W ; W = W->Next)
        {
            Indegree[W -> AdjV]++;  //对有向边<V,W->AdjV>累计终点的入度
        }
    }

    //将所有入度为0的顶点入列
    for (V = 0; V < Graph->NV; V++)
    {
        if (Indegree[V] == 0)
        {
            AddQ(Q, V);
        }
    }

    //下面进入拓扑排序
    cnt = 0;
    while (!IsEmpty(Q))
    {
        V = DeleteQ(Q); //弹出一个入度为0的顶点
        TopOrder[cnt++] =  V; //将之存为结果序列的下一个元素
        //对V的每个邻接点W -> AdjV
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
        {
            if (--Indegree[W->AdjV] == 0)  //若删除V使得W->AdjV入度为0
            {
                AddQ(Q, W -> AdjV);  //则该顶点入列
            }
            
        }
        
    }

    if (cnt != Graph->NV)
    {
        return false; //cnt!= Graph->NV,说明没有回路。
    }else
    {
        return true;
    }
}

//若图的表示采用邻接表，改进后的算法的时间复杂度为O(|E|+|V|).拓扑排序算法可以用来检测一个有向图是否是DAG(有向无环图),就看cnt与NV的比较。