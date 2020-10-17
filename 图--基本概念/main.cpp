/*
图状结构是一种比树形结构更复杂的非线性结构，树型结构中结点具有分支层次关系，树的关系是一对多的关系，而图的关系是多对多的关系。

图的结构是任意两个数据对象之间都可能存在某种特定关系的数据结构。

关于图的定义，与以前的线性表和树比较，还有几点需要明确：
1.在线性表中，一般叫数据对象为元素；在树中，将数据对象称为结点；在图中，把数据对象称作顶点vertex.
2.线性表中可以没有数据对象，此时叫空表；没有数据对象的树称为空树；而在图中，我们至少要求有一个顶点，但是边集为空。

图的相关术语
1.无向图Undirected Graphs:顶点之间的边Edge没有方向，即(v,w) = (w,v)。用圆括号表示无向边。边的起点w和终点v的次序并不重要。
2.有向图Directed Graphs:有向图中顶点之间的所有边都有方向，即边<v,w> != <w,v>，用尖括号表示有向边。有向边也称为弧Arc，弧的起点(弧头)和终点
(弧尾)的次序不能颠倒。在不会混淆的场合，有向边和无向边都简称为边。
3.简单图Simple Graph:如果图中出现重边，或者边的集合E中出现了重复的元素，或者有自回路边，就叫做非简单图。
4.邻接点Adjacent Vertices:如果(v,w)是无向图中任意一条边，那么称v和w互为邻接点；如果<v,w>是有向图的一条边，那么称起点v邻接到终点w，也可以
说终点w邻接自起点v。
5.路径Path:图中的一条路径是一顶点序列v1,v2,...,vN,序列中任何相邻的两顶点都可以在图中找到对应的边。一条路径的长度是这条路径所包含的边数。
一条简单路径是指除了路径的首尾顶点外，其余顶点都是不同的。 (也就是说如果首尾顶点相同，即就是个环，那么也叫作简单路径)；简单路径形成的回路
称为简单回路。
有向图中的一条回路是指v1=vn的一条路径。路径长度为1的回路是一个自回路，属于非简单图。
如果一个有向图中不存在回路，那么这个有向图成为无环图。

对于无向图，由于顶点是无序的，环路的长度要大于等于3(因为如果顶点只有两个，构不成回路)。比如路径u,v,u不会是一条环路，而是重边。是重边图。

无向完全图: Undirected Complete Graph:在一个无向图中，如果任意两顶点都有一条边相连接，则称该图为无向完全图。在一个含有n个顶点的无向完全图中，
共有n(n-1)/2条边。

有向完全图: Directed Complete Graph:在一个有向图中，如果任意两顶点之间都由方向 互为相反 的 两条弧 相连接，则称该图为有向完全图。在一个含有n
个顶点的有向完全图中，共有n(n-1)条边。

顶点的度(degree)：顶点v的度是指依附于该顶点的边数。在有向图中，顶点的度又分为入度In degree和出度Out-degree。顶点v的入度是指以顶点v为终点的弧的数目，顶点v的出度
是指以顶点v为起点的弧的数目。 Degree(v) = In degree(v) + Out degree(v)。

稠密图Dense Graph,稀疏图Sparse Graph:若一个图的边数接近完全图的边数，则称这样的图为稠密图。相反地，称边数很少的图为稀疏图。通常，设图G=(V,E)
|V|表示顶点的数量，|E|表示边的数量，一个图的稠密度(Density)定义为平均顶点度2|E|/|V|，对于完全图，平均顶点度是|V|-1，所以|E| = (|V|-1)|V|/2。
所以我们可以把稠密图定量定义成“平均顶点度与顶点数量|V|成正比的图”

权Weight、网图(Network)：边上带权的图称为网图！！

子图！！！(SubGraph):对于图G={V,E},G'={V',E'}，如果V'是V的子集，并且E'是E的子集，那么G'是G的一个子图。即要求边和顶点都是子集。

!!!重要
连通图(Connected Graph)、连通分量(Connected Component)：在无向图中，如果从一个顶点vi到另一个顶点vj(i!=j)有路径，则称顶点vi和vj是连通的，
如果图中任意两顶点都是连通的，则称该图是连通图。 无向图的极大连通子图称为连通分量。连通分量的概念包含下面四点：
1.子图：连通分量应该是原图的子图。
2.连通：连通分量本身应该是连通的。
3.极大顶点数：连通子图含有极大顶点数，即再加入其他顶点将会导致子图不连通。argmax
4.极大边数：具有极大顶点数的连通子图包含依附于这些顶点的所有边。

所以满足这些条件，连通的无向图只有一个连通分量，即这个连通分量就是本图。而不连通的无向图，则有多于一个的连通分量。

强连通图Strongly Connected Graph，强连通分量：对于有向图来说，若图中任意一对顶点vi和vj的路径，也有从vj到vi的路径，则称该有向图是强连通图。
有向图的极大强连通子图成为强连通分量。

强连通分量与上面的连通分量有类似的定义。一定要注意，首先强连通分量一定要是原图的子图，如果方向都不对，那肯定不是强连通分量。

生成树：所谓连通图G的生成树，是G的包含其全部n个顶点的一个 极小连通子图。 它必定包含且仅包含G的n-1条边。即生成树共有n个顶点，n-1条边。
如果有n个顶点的图，边数少于n-1，那么它必定是不连通的，所以n-1是连通图所需的“极小”的边的数量。而多于n-1条边的图必将产生回路，它就不是树了，
因为树中没有回路，由此可见，图G是一棵树，当且仅当G满足下面4个条件之一：
1.G有n-1条边，且没有环
2.G有n-1条边，且是连通的。
3.G的每一对顶点有且仅有一条路径相连。
4.G是连通的，但删除任何一条边就会使得它不连通。
对于有向图来说，生成树应该是一棵有向树。如果一个有向图中恰有一个顶点的入度为0，其余的顶点入度为1，则它就是一棵有向树。对有向树的理解并不难，入度为
0的顶点就是树的根，其余顶点入度为1表示非根结点只有一个父结点。

生成森林：在非连通图中，由于每个连通分量都是一个极小连通子图，即一棵生成树可以对应一个连通分量，对应每个连通分量的各棵生成树就组成了一个图的生成森林。
对于无向图而言，一个图的生成森林中树的数量就等于它的连通分量数。对于有向图来说，一个强连通分量当然可以得到对应的生成树(不唯一)，但是，非强连通
图也可能 只需要 一棵生成树(有向树)与之对应(无向图的非连通图会有多个连通分量）。

*/

/*
图的抽象数据类型
*/
Graph CreateGraph(int VertexNum) //这是用来构造一个有VertexNum个顶点但没有边的图。
void InsertEdge(Graph G, Edge E) //在图G中插入边E
void DeleteEdge(Graph G, Edge E) //从G中删除边E
bool IsEmpty(Graph G) //如果图G为空，则返回true，否则返回false
void DFS(Graph G, Vertex V, (* Visit)(Vertex)) //在图G中，从顶点V出发进行深度优先遍历
void BFS(Graph G, Vertex V,(* Visit)(Vertex)) //在图G中，从顶点V出发进行广度优先遍历

