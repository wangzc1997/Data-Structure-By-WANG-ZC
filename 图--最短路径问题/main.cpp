/*
最短路径问题，是图的一个比较典型的问题，一般来说，对于一个无向网图(也可以是有向网图)，边上的权值可以理解为距离(自然约定为非负)，那么最短路径问题就可以归结为：
在网图中，求两个不同顶点的所有路径中，边的权值之和最短的那一条路径。这条路径就是两点之间的最短路径(Shortest Path)，并称路径上的第一个顶点为源点Source，最后一个顶点
为终点(Destination)。 

在非网图中，最短路径是指两点之间经历的边数最少的路径。

边上权值有负数的情况下，必须限定网图中任意回路上的权值和为正值，否则最短路径一直循环走这个回路，会得到最短路径为负无穷的情况。

常见的最短路径问题分为 单源最短路径  和 多源最短路经问题。


*/