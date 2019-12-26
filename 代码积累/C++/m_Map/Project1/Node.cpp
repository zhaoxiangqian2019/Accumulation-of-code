#include "Node.h"



Node::Node(char data)
{
	m_cData = data;			//节点的数据
	m_bIsVisited = false;	//节点是否被访问过
}


Node::~Node()
{

}
