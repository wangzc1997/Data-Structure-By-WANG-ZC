/*
多源最短路经就是求任意两顶点间的最短路径。
方法1：直接将单源最短路径算法调用|V|遍
T = O(|V|^3 + |E|*|V|)  对于稀疏图效果好

方法2：采用Floyd算法。时间复杂度是O(|V|^3)，但是形式上非常简洁优雅，而且对于稠密图来说，实际运行效率更快。

Floyd算法：求任意两顶点间的最短路径的代码 ， 算法时间复杂度为O(|V|^3)。
*/
bool Floyd(MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum])
{
    Vertex i, j, k;

    //初始化
    for (i = 0; i < Graph->NV; i++)
    {
        for (j = 0; j < Graph->NV; j++)
        {
            D[i][j] = Graph->G[i][j];
            path[i][j] = -1;
        }
        
    }
    
    for (k = 0; k < Graph->NV; k++)
    {
        for (i = 0; i < Graph->NV; i++)
        {
            for (j = 0; j < Graph->NV; j++)
            {
                if (D[i][k] + D[k][j] < D[i][j]) 
                {
                    D[i][j] = D[i][k] + D[k][j];
                    if (i == j && D[i][j] < 0 )
                    {
                        return false; //不能正确解决，返回错误标记
                    }
                    path[i][j] = k;
                    
                }
                
            }
            
        }
        
    }
    return true;
    
}