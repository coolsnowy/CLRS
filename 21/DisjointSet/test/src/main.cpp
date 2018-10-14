// chapter 21， 不相交集合

#include <memory>
#include <iostream>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;

class DisjointSetNode {
public:
	DisjointSetNode() = default;
	DisjointSetNode(int v) : value (v) {

	}
public:
	int value;/*!< 结点保存的数据的弱指针*/
	int rank;/*!< 结点的秩*/
	std::shared_ptr<DisjointSetNode> parent;/*!< 结点的父指针*/

};

class DisjointSet {
public:
	DisjointSet() = default;
	//!find_set：返回结点所在集合的代表结点
	/*
	* \param node:要查找的结点。它必须非空，否则抛出异常
	* \return: 结点所在集合的代表结点的强指针
	*
	* 该操作简单沿着指向父节点的指针找到树的根。树的根的特征是：它的父节点就是它本身。
	* 若结点不在不相交集合森林中（当结点的父节点指针为空时），则抛出异常。
	*
	* find_set过程是一个 two_pass method，当它递归时，第一趟沿着查找路径向上直到找到树根；
	* 当递归回溯时，第二趟沿着搜索树向下更新每个节点，使其父节点直接指向树根
	*
	*/
	shared_ptr<DisjointSetNode> findSet(shared_ptr<DisjointSetNode> node) {
		if(!node) {
			throw std::invalid_argument("findSet error : node must not be a nullptr!\n");
		}
		if(node != node->parent) {
			node->parent = findSet(node->parent);
		}
		return node->parent;
	}

	//!make_set：创建集合
	/*
	* \param node:创建集合的结点。它必须非空，否则抛出异常
	*
	* 该操作简单地创建一棵只有一个结点的树。它将树根的秩设为0，将树根的父节点指向树根本身
	*
	*/
	void makeSet(shared_ptr<DisjointSetNode> node) {
		if(node) {
			node->parent = node;
			node->rank = 0;
		} else {
			throw std::invalid_argument("makeSet error: node must not be nullptr!");
		}
	}

	//!union_set：合并集合
	/*
	* \param nodeX:待合并的第一个集合中的某个结点
	* \param nodeY:待合并的第二个集合中的某个结点
	*
	* 该操作首先获取每个结点所在集合的代表结点，然后将它们合并起来
	*
	*/
	void unionSet(shared_ptr<DisjointSetNode> nodeX, shared_ptr<DisjointSetNode> nodeY)
	{
		linkSet(findSet(nodeX), findSet(nodeY));
	}

	//!link_set：链接集合
	/*!
	*
	* \param nodeX:待链接的第一个集合中的根节点。
	* \param nodeY:待合并的第二个集合中的根节点
	*
	* 每个结点x维持一个整数值属性rank,它代表了x的高度（从x到某一后代叶结点的最长简单路径上的结点数目）的一个上界。
	 * 在链接时我们让具有较小秩的根指向具有较大秩的根.
	*
	* - 如果 nodeX或者nodeY为空，则直接返回
	* - 如果 nodeX 和 nodeY非空，但是nodeX或者nodeY不是根结点，抛出异常
	*
	*/
	void linkSet(shared_ptr<DisjointSetNode> nodeX, shared_ptr<DisjointSetNode> nodeY) {
		if(!nodeX || !nodeY)
			return;
		if(nodeX != nodeX->parent || nodeY != nodeY->parent)
			throw std::invalid_argument("link_set error: node must be root of the set!");
		if(nodeX->rank > nodeY->rank) {
			nodeY->parent = nodeX;
		} else {
			nodeX->parent = nodeY;
			if(nodeX->rank == nodeY->rank) {
				nodeY->rank++;
			}
		}
	}

};

int main() {
	const int size = 5;
	shared_ptr<DisjointSetNode> node[size];
	for(int i = 0; i < size; i++) {
		node[i] = make_shared<DisjointSetNode>(i);
	}
	DisjointSet set;
	for(int i = 0; i < size; i++) {
		set.makeSet(node[i]);
	}
	set.unionSet(node[0], node[1]);
	set.unionSet(node[2], node[3]);
	set.unionSet(node[3], node[4]);
	for(int i = 0; i< size; i++) {
		cout << "node " <<i << ".root = node " << set.findSet(node[i])->value << endl;
	}

	return 0;

};