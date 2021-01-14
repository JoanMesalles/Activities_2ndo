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
	void PreOrder();
private:
	Node* Search(Node* n, int key);
	int Min(Node* n);
	bool Insert(Node* n, Node* toinsert);
	void PreOrder(Node* n);


	
};

