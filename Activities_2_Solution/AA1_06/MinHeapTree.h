#pragma once
#include "BT.h"
class MinHeapTree : public BT
{
	MinHeapTree();
	~MinHeapTree();
	Node* Search(int key);
	bool Exist(int key);
	int Min();

};

