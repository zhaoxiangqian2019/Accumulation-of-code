#pragma once
class Node
{
public:
	Node(char data = 0);
	~Node();
	char m_cData;
	bool m_bIsVisited;
};

