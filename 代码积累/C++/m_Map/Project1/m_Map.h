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

	bool addNode(Node *pNode);					//��ͼ�м��붥�㣨�ڵ㣩
	void resetNode();							//���ýڵ�
	bool setValueToMatrixForDirectedGraph(int row, int col, int val = 1);	//Ϊ����ͼ�����ڽӾ���
	bool setValueToMatrixForUndirectedGraph(int row, int col, int val = 1);	//Ϊ����ͼ�����ڽӾ���
	bool getValueFromMatrix(int row, int col, int &val);
	void printMatrix();				//��ӡ�ڽӾ���

	void depthFirstTraverse(int nodeIndex);			//������ȱ���
	void breadthFirstTraverse(int nodeIndex);		//������ȱ���

	void breadthFirstTraverseImpl(vector<int> preVec);

private:
	int m_iCapacity;		//ͼ�����������ɵĶ�����
	int m_iNodeCount;		//�Ѿ���ӵĶ��㣨�ڵ㣩����
	Node *m_pNodeArray;		//������Ŷ�������
	int *m_pMatrix;			//��������ڽӾ���
};

