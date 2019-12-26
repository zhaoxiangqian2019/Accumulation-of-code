#include <string>
#include <iostream>

#include "m_Map.h"

using namespace std;

/*
		  A
	    /   \
	   B     D
	 /  \   / \
	C   F  G   H
	 \ /
	  E

	A B C D E F G H
A	0 1 0 1 0 0 0 0
B	1 0 1 0 0 1 0 0
C	0 1 0 0 1 0 0 0
D	1 0 0 0 0 0 1 1
E	0 0 1 0 0 1 0 0
F	0 1 0 0 1 0 0 0
G	0 0 0 1 0 0 0 0
H	0 0 0 1 0 0 0 0

*/


int main()
{
	m_Map *pMap = new m_Map(8);

	Node *pNodeA = new Node('A');
	Node *pNodeB = new Node('B');
	Node *pNodeC = new Node('C');
	Node *pNodeD = new Node('D');
	Node *pNodeE = new Node('E');
	Node *pNodeF = new Node('F');
	Node *pNodeG = new Node('G');
	Node *pNodeH = new Node('H');

	pMap->addNode(pNodeA);
	pMap->addNode(pNodeB);
	pMap->addNode(pNodeC);
	pMap->addNode(pNodeD);
	pMap->addNode(pNodeE);
	pMap->addNode(pNodeF);
	pMap->addNode(pNodeG);
	pMap->addNode(pNodeH);

	pMap->setValueToMatrixForUndirectedGraph(0, 1);
	pMap->setValueToMatrixForUndirectedGraph(0, 3);
	pMap->setValueToMatrixForUndirectedGraph(1, 2);
	pMap->setValueToMatrixForUndirectedGraph(1, 5);
	pMap->setValueToMatrixForUndirectedGraph(3, 6);
	pMap->setValueToMatrixForUndirectedGraph(3, 7);
	pMap->setValueToMatrixForUndirectedGraph(6, 7);
	pMap->setValueToMatrixForUndirectedGraph(2, 4);
	pMap->setValueToMatrixForUndirectedGraph(4, 5);

	pMap->printMatrix();
	cout << endl << "深度优先遍历结果为：";
	pMap->depthFirstTraverse(0);

	cout << endl << "广度优先遍历结果为：";
	pMap->resetNode();
	pMap->breadthFirstTraverse(0);
	cout << endl;
	system("pause");
	return 0;
}
