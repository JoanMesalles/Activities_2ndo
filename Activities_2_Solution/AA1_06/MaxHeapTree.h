#pragma once
#include "BT.h"
class MaxHeapTree: public BT
{
public:
	MaxHeapTree();
	~MaxHeapTree();
	
	Node* Search(int key);
	bool Exist(int key);
	int Max();
private:
	bool Exist(Node* n, int key);
};

