#include <iostream>
#include "BT.h"
#include "BST.h"
#include "MaxHeapTree.h"

int main() {

	
	//Binary tree
	std::cout << "Binary Tree" << std::endl;
	BT t1;
	std::cout << "BT Preorder - Normal" << std::endl;
	t1.PreOrder();
	std::cout << std::endl;
	std::cout << "BT Preorder - Iterativo" << std::endl;
	t1.PreOrderI();
	std::cout << std::endl;
	std::cout << "BT Search"<<std::endl;
	BT::Node * Node = t1.Search(1);

	std::cout << Node->key << std::endl;
/*
	std::cout << "BT Exist" << std::endl;
	if (t1.Exist(1)) {
		std::cout << "Existe" << std::endl;
	}
*/
	std::cout << "BT Heigth" << std::endl;
	std::cout << t1.Height() << std::endl;
/*
	std::cout << "BT Max" << std::endl;
	std::cout << t1.Max() << std::endl;

	std::cout << "BT Min" << std::endl;
	std::cout << t1.Min() << std::endl;


	std::cout << "BT Balanced" << std::endl;
	if (t1.IsBalanced())
		std::cout << "balanced" << std::endl;
*/
	//t1.PreOrderI();

	//Binary Search Tree
	std::cout << "Binary Search Tree" << std::endl;
	BST t2;

	BT::Node* n = t2.Search(7);

	std::cout << "BST Search" << std::endl;
	std::cout << n->key << std::endl;

	std::cout << "BST Min" << std::endl;
	std::cout << t2.Min() << std::endl;

	std::cout << "BST Insert" << std::endl;
	t2.PreOrder();
	std::cout << std::endl;
	t2.Insert(9);
	t2.PreOrder();
	std::cout << std::endl;

	//MaxHeapTree
	std::cout << "MaxHeapTree" << std::endl;
	MaxHeapTree t3;

	std::cout << "MaxHT Exist" << std::endl;
	if (t3.Exist(50)) {
		std::cout << "Existe" << std::endl;
	}
	std::cout << "MaxHT Max" << std::endl;
	std::cout << t3.Max() << std::endl;

	//MinHeapTree
	std::cout << "MinHT" << std::endl;
	MaxHeapTree t4;

	std::cout << "MinHT Min" << std::endl;
	std::cout << t3.Min() << std::endl;

	return 0;

};
