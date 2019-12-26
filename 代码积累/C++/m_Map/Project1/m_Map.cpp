#include "m_Map.h"



m_Map::m_Map(int capacity)
{
	m_iCapacity = capacity;
	m_iNodeCount = 0;
	m_pNodeArray = new Node[m_iCapacity];
	m_pMatrix = new int[m_iCapacity * m_iCapacity];
	memset(m_pMatrix, 0, m_iCapacity * m_iCapacity * sizeof(int));
}


m_Map::~m_Map()
{
	delete[]m_pNodeArray;
	delete[]m_pMatrix;
}

bool m_Map::addNode(Node *pNode)
{
	if (!pNode)
	{
		return false;
	}
	m_pNodeArray[m_iNodeCount].m_cData = pNode->m_cData;
	m_iNodeCount++;
	return true;
}

void m_Map::resetNode()
{
	for (int i = 0; i < m_iNodeCount; i++)
	{
		m_pNodeArray[i].m_bIsVisited = false;
	}
}

bool m_Map::setValueToMatrixForDirectedGraph(int row, int col, int val)
{
	if (row < 0 || row >= m_iCapacity || col < 0 || col >= m_iCapacity)
	{
		return false;
	}
	m_pMatrix[row * m_iCapacity + col] = val;
	return true;
}

bool m_Map::setValueToMatrixForUndirectedGraph(int row, int col, int val)
{
	if (row < 0 || row >= m_iCapacity || col < 0 || col >= m_iCapacity)
	{
		return false;
	}
	m_pMatrix[row * m_iCapacity + col] = val;
	m_pMatrix[col * m_iCapacity + row] = val;
	return true;
}

bool m_Map::getValueFromMatrix(int row, int col, int &val)
{
	if (row < 0 || row >= m_iCapacity || col < 0 || col >= m_iCapacity)
	{
		return false;
	}
	val = m_pMatrix[row * m_iCapacity + col];
	return true;
}

void m_Map::printMatrix()
{
	for (int i = 0; i < m_iCapacity; i++)
	{
		for (int j = 0; j < m_iCapacity; j++)
		{
			cout << m_pMatrix[i * m_iCapacity + j] << " ";
		}
		cout << endl;
	}
}

void m_Map::depthFirstTraverse(int nodeIndex)
{
	int value = 0;
	cout << m_pNodeArray[nodeIndex].m_cData << " ";
	m_pNodeArray[nodeIndex].m_bIsVisited = true;

	for (int i = 0; i < m_iCapacity; i++)
	{
		getValueFromMatrix(nodeIndex, i, value);
		if (value == 1)
		{
			if (m_pNodeArray[i].m_bIsVisited)
			{
				continue;
			}
			else
			{
				depthFirstTraverse(i);
			}
		}
		else
		{
			continue;
		}
	}
}

void m_Map::breadthFirstTraverse(int nodeIndex)
{
	cout << m_pNodeArray[nodeIndex].m_cData << " ";
	m_pNodeArray[nodeIndex].m_bIsVisited = true;

	vector<int> curVec;
	curVec.push_back(nodeIndex);

	breadthFirstTraverseImpl(curVec);
}

void m_Map::breadthFirstTraverseImpl(vector<int> preVec)
{
	int value = 0;
	vector<int> curVec;
	
	for (int i = 0; i < (int)preVec.size(); i++)
	{	
		for (int j = 0; j < m_iCapacity; j++)
		{
			getValueFromMatrix(preVec[i], j, value);
			if (value != 0)
			{
				if (m_pNodeArray[j].m_bIsVisited)
				{
					continue;
				}
				else
				{
					cout << m_pNodeArray[j].m_cData << " ";
					m_pNodeArray[j].m_bIsVisited = true;
					curVec.push_back(j);
				}
			}
		}
	}
	if (curVec.size() == 0)
	{
		return;
	}
	else
	{
		breadthFirstTraverseImpl(curVec);
	}
}