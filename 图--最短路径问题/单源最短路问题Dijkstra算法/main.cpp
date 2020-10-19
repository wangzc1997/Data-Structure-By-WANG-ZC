/*
从一个固定源点到所有其他各顶点的最短路径问题称为“单源最短路径问题”。 

单源最短路径分为无权图的单源最短路径和 有权图的单源最短路径

对于无权图的单源最短路算法，我们要求顶点数最少，其实就是最短的边数。具体解决方法就是：按照递增(非递减)的顺序找出各个顶点的最短路。
其实就是BFS，广度优先搜索，将所有顶点访问一遍。(只不过一般这解决的是有向图)
*/


//下面是无权图的单源最短路算法的伪代码
void Unweighted(Vertex S)
{
    Enqueue(S,Q);
    while (!IsEmpty(Q))
    {
        V = DeleteQ(Q);
        for (V的每一个邻接点W)
        {
            if (dist[W] == -1)
            {
                dist[W]= dist[V] + 1;
                path[W] = V;
                Enqueue(W,Q);
            }
            
        }
        
    }
    
}
//总共时间复杂度为T = O(|E| + |V|)；

/*
下面是有权图的单源最短路算法
有权图和无权图的差异在于：不是要求顶点最少，而是权重和最小。所以上面的算法就不适用有权图了。

按照递增的顺序找出到各个顶点的最短路。使用Dijkstra算法。

Dijkstra算法：
1.令 S = {源点s + 已经确定了最短路径的顶点vi}
2.对任一未收录的顶点v，！！ 定义dist[v]为s到v的最短路径长度 ！！，但该路径仅经过S集合中的顶点。即路径{s -> （vi 属于 S) -> v}的最小长度。
3.路径是按照递增(非递减)的顺序生成的。
真正的最短路必须只经过S中的顶点，因为dist最小的都被S收录了。
每次从未收录的顶点中选一个dist最小的收录(贪心算法)
增加一个v进入S,可能影响另外一个w的dist值，(只会影响v的邻接点) dist[w] = min{dist[w] , dist[v] + <v,w>的权重}
*/
//Dijkstra的伪码描述
void Dijkstra(Vertex s)
{
    while (1)
    {
        V = 未收录顶点中dist最小者;
        if (这样的V不存在)
        {
            break;
        }
        collected[V] = true;  //将V收录进一个数组中
        for (V 的每个邻接点W)
        {
            if (collected[W] == false )
            {
                if (dist[V] + E<V,W> < dist[W])  //这个dist就是如果从源点到该点的权重和， 一开始都是无穷大，一旦从源点开始，不断插入dist最小的点，则这个最小点指向的那些顶点的dist值也就确定了。
                {
                    dist[W] = dist[V] + E<V,W>;
                    path[W] = V;
                }
                
            }
            
        }
        
        
    }
    
}
//其实思想很简单， 就是贪心原则，我们先收录一个源点，然后看这个点的每个邻接点，如果还没有被收录，则看一下dist值，然后根据情况进行收录。

/*
在计算复杂度的时候，分两种情况：
1.直接扫描所有未被收录顶点 --O(|V|)
T = O(|V|^2 + |E|)  对于稠密图更好

2.将dist存在最小堆中 --O(log|V|)
T = O(|V|log|V| + |E|log|V|) = O(|E|log|V|)  对于稀疏图更好

下面是书上的Dijkstra算法C语言代码
*/
Vertex FindMinDist(MGraph Graph, int dist[], int collected[])
{
    //返回未被收录顶点中dist的最小值
    Vertex MinV, V;
    int MinDist = INFINITY;  //刚开始的MinDist设置为无穷大

    for (V = 0; V < Grah->NV; V++)
    {
        if (collected[V] == false && dist[V] < MinDist)
        {
            //若V未被收录，且dist[V]更小
            MinDist = dist[V]; //更新最小距离
            MinV = V;  //更新对应顶点
        }
        
    }
    if (MinDist < INFINITY)
    {
        return MinV; //返回对应顶点的下标
    }else
    {
        return ERROR; //若这样的顶点不存在，则返回错误标记
    }
    
    
}

bool Dijkstra(MGraph Graph, int dist[], int path[], Vertex S)  //S第一次出现的地方，S就是初始点/源点
{
    int collected[MaxVertexNum]; //
    Vertex V, W;

    //初始化：此处默认邻接矩阵中不存在的边用INFINITY表示
    for (V = 0; V < Graph->NV; V++)
    {
        dist[V] = Graph->G[S][V];
        if (dist[V] < INFINITY)
        {
            path[V] = S；
        }else
        {
            path[V] = -1;
        }
        collected[V] = false;
        
    }
    
    //将起点收入集合
    dist[S] = 0;
    collected[S] = true;

    while (1)
    {
        //V = 未被收录顶点中dist最小值
        V = FindMinDist(Graph, dist, collected);
        if (V == ERROR) //如果这样的V不存在
        {
            break; //算法结束
        }
        collected[V] = true; //收录V
        for (W = 0; W < Graph->NV; W++)
        {
            if (collected[W] = false && Graph->G[V][W] < INFINITY)
            {
                if (Graph->G[V][W] < 0) //如果有负边
                {
                    return false; //不可正确解决，返回错误标志；
                }
                if (dist[V] + Graph->G[V][W] < dist[W])
                {
                    dist[W] = dist[V] + Graph->G[V][W];
                    path[W] = V; //更新S到W的路径
                }
                
                
            }
            
        }
        
        
    }
    return true;
    
}
//以上就是Dijkstra算法。

/*
上面的算法，第一个for循环的时间复杂度是O(|V|)，随后while循环共进行|V|-1次，每次执行的时间是O(|V|)，所以总的时间复杂度是O(|V|^2)。如果用带权的邻接表作为
有向图的存储结构，虽然修改dist的时间可以减少，但由于在dist中选择最小分量的时间不变，所以总的时间仍为O(|V|^2)，对稠密图来说是一个好的选择。

对于稀疏图来说，这个时间界不是理想的，一个改进是：改用邻接表作为存储结构，并改用优先队列(最小堆)的DeleteMin操作！！！就是说我每次都找最小的dist，查找最小值的
时间是O(log|V|),这样时间界可以改进为O(|E|log|V|). //但是CreateHeap应该也是要时间的，可以看一下最小堆的时间复杂度。




*/