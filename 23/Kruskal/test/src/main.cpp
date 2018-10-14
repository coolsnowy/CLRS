
#include "DisjointSet.h"
#include "Graph.h"

//!kruskal：最小生成树的Kruskal算法，算法导论23章23.2节
/*!
* \param graph:指向图的强指针，必须非空。若为空则抛出异常
* \param source_id：最小生成树的根结点`id`，必须有效。若无效则抛出异常
* \param pre_action:一个可调用对象，在每次从最小优先级队列中弹出最小顶点时立即调用，调用参数为该顶点的`id`。默认为空操作，即不进行任何操作
* \param post_action:一个可调用对象，在每次从最小优先级队列中弹出最小顶点并处理完它的边时立即调用，调用参数为该顶点的`id`。默认为空操作，即不进行任何操作
* \return: 最小生成树的权重
*
* ## 最小生成树
*
* 最小生成树：对于一个连通无向图G=(V,E)，对于每一条边(u,v)属于E都赋予了一个权重w(u,v)。我们希望找出一个无环子集T，其中T为E的子集，使得所有的顶点V位于T中，
* 同时T具有最小的权重。由于T是无环的，且连通所有结点因此T必然是一棵树。我们称这样的树为生成树。称从G中求取该生成树的问题为最小生成树问题。
*
* 通用的最小生成树使用贪心策略。该策略在每个时刻找到最小生成树的一条边，并在整个策略过程中维持循环不变式：边的集合A在每次循环之前是某棵最小生成树的一个子集。
*
* 在每一步，选择一条边(u,v)，将其加入集合A中，使得A不违反循环不变式。称这样的边(u,v)为边集合A的安全边。
*
* ## Kruskal 算法
*
* ### 算法原理
*
* 在Kruskal算法中集合A是一个森林，其结点就是G的结点。Kruskal算法找到安全边的办法是：在所有连接森林中两棵不同树的边里面，找到权重最小的边(u,v)。
* Kruskal算法使用一个不相交集合数据结构来维护几个互不相交的元素集合。每个集合代表当前森林中的一棵树
*
* ### 算法步骤
*
* - 初始化：将集合A置为空；对G中的每一个结点v,以它为根构造一棵单根树
* - 将G中的边E按照权重单调递增的顺序排序
* - 循环挑选E中的(u,v)，按照单调增的顺序。在循环内执行：
*   - 如果u所在的树不等于v所在的树，则将(u,v)加入A中，并且合并u所在的树与v所在的树
*
* >根据算法的特征，如果图中只有一个顶点，算法得到的集合A为空集；但是实际上集合A应该包含该顶点。这是算法在极端情况下的BUG。
*
* ### 算法性能
*
* Kruskal算法运行时间依赖于不相交集合数据结构的实现方式。如果采用算法导论21.3节讨论的不相交集合森林实现（也是我在src/set_algorithms/disjoint_set中实现的），
* 则Kruskal算法的时间为 O(ElgV)
*/
void kruskal( Graph &graph) {
	// 注意，指定的节点序号，也应该是从0开始
	int size = graph.V().size();
	// node指向一个vector，vector中存放着所有节点的智能指针
	std::vector<shared_ptr<DisjointSetNode>> node(size, nullptr);
	for(int i = 0; i < size; i++) {
		node[i] = make_shared<DisjointSetNode> (graph.V()[i]);
	}

	DisjointSet set;
	for(int i = 0; i < size; i++) {
		set.makeSet(node[i]);
	}
	std::vector<edge> edges = graph.E();
	// sort by the weight of the edge
	std::sort(edges.begin(), edges.end(), [](const edge &e1, const edge &e2) { return e1.second < e2.second; });


	for(int i = 0; i < edges.size(); i++) {
		if(set.findSet(node[edges[i].first.first]) != set.findSet(node[edges[i].first.second])) {
			cout << static_cast<char>('a' + edges[i].first.first) <<"---" << static_cast<char>('a' + edges[i].first.second) << std::endl;
			set.unionSet(node[edges[i].first.first], node[edges[i].first.second]);
		}
	}
}

int main() {
	// 见书上367页例子
	std::vector<int> point {0, 1, 2, 3, 4, 5, 6, 7, 8};
	std::vector<edge> edges{
		std::pair<std::pair<int, int>, double> ({0, 1}, 4),
		std::pair<std::pair<int, int>, double> ({1, 2}, 8),
		std::pair<std::pair<int, int>, double> ({2, 3}, 7),
		std::pair<std::pair<int, int>, double> ({3, 4}, 9),
		std::pair<std::pair<int, int>, double> ({4, 5}, 10),
		std::pair<std::pair<int, int>, double> ({5, 6}, 2),
		std::pair<std::pair<int, int>, double> ({6, 7}, 1),
		std::pair<std::pair<int, int>, double> ({0, 7}, 8),
		std::pair<std::pair<int, int>, double> ({1, 7}, 11),
		std::pair<std::pair<int, int>, double> ({2, 8}, 2),
		std::pair<std::pair<int, int>, double> ({8, 7}, 7),
		std::pair<std::pair<int, int>, double> ({8, 6}, 6),
		std::pair<std::pair<int, int>, double> ({2, 5}, 4),
		std::pair<std::pair<int, int>, double> ({3, 5}, 14),
	};
	Graph graph(point, edges);
	kruskal(graph);
}

