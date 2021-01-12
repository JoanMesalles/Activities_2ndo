#pragma once
#include "BT.h"
class BST :	public BT
{
public:
	BST();
	~BST();
	
	Node* Search(int key);
	bool Exist(int key);
	int Min();
	int Max();
	void Insert(int key);
	void GetKeysByOrder(std::vector<int>& v);

	
};

