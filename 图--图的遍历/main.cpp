/*
由于图结构的复杂性，所以图的遍历操作对比树的遍历更复杂，主要表现在下面四个方面：
1.图结构中，没有一个“自然”的首结点，图中任意一个顶点都可以作为第一个被访问的结点，所以遍历的序列通常还要指出从哪个顶点出发。
2.在非连通图中，从一个顶点出发，只能够访问它所在的连通分量上的所有顶点，因此还要考虑如何选取下一个出发点以访问图中其余的连通分量。
3.在图结构中，如果有回路存在，那么一个顶点被访问之后，有可能沿回路又回到该结点，因此需要标记已经被访问的顶点，比如点亮交叉点的灯，或者用Visited数组
4.在图结构中，一个顶点可以和其他多个顶点相连，当这样的顶点访问过后，存在如何选取下一个要访问的顶点的问题。

图的遍历的应用：
求连通分量、欧拉回路、生成树、DAG的判定、DAG的根、桥边、关节点等的计算都可以通过遍历来进行。


*/