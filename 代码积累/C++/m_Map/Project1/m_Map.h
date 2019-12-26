#pragma once
#include "Node.h"

#include <vector>
#include <iostream>

using namespace std;
class m_Map
{
public:
	m_Map(int capacity);
	~m_Map();

	bool addNode(Node *pNode);					//向图中加入顶点（节点）
	void resetNode();							//重置节点
	bool setValueToMatrixForDirectedGraph(int row, int col, int val = 1);	//为有向图设置邻接矩阵
	bool setValueToMatrixForUndirectedGraph(int row, int col, int val = 1);	//为无向图设置邻接矩阵
	bool getValueFromMatrix(int row, int col, int &val);
	void printMatrix();				//打印邻接矩阵

	void depthFirstTraverse(int nodeIndex);			//深度优先遍历
	void breadthFirstTraverse(int nodeIndex);		//广度优先遍历

	void breadthFirstTraverseImpl(vector<int> preVec);

private:
	int m_iCapacity;		//图中最多可以容纳的顶点数
	int m_iNodeCount;		//已经添加的顶点（节点）个数
	Node *m_pNodeArray;		//用来存放顶点数组
	int *m_pMatrix;			//用来存放邻接矩阵
};

