#include <iostream>
#include "BT.h"

int main() {

	

	BT t1;

	t1.PreOrder();
	std::cout << std::endl;
	t1.PreOrderI();

	BT::Node * Node = t1.Search(1);

	std::cout << Node->key << std::endl;

	if (t1.Exist(1)) {
		std::cout << "Yye" << std::endl;
	}

	std::cout << t1.Height() << std::endl;

	std::cout << t1.Max() << std::endl;

	std::cout << t1.Min() << std::endl;

	if (t1.IsBalanced())
		std::cout << "balanced" << std::endl;

	//int x = t1.GetNumberNodesI();


	/*

	std::vector<int> v;

	t1.GetNPair(v);
	*/
	
	return 0;

};
