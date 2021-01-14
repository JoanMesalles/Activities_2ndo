
#include "MaxHeapTree.h"


MaxHeapTree::MaxHeapTree()
{
	root = new Node(100);
	root->left = new Node(88);
	root->right = new Node(80);
	root->left->right = new Node(60);
	root->left->right->left = new Node(50);
	root->left->right->right = new Node(40);
	root->right->right = new Node(55);
	root->right->right->left = new Node(40);


}


MaxHeapTree::~MaxHeapTree()
{
}

BT::Node* MaxHeapTree::Search(int key)
{
	return nullptr;
}

int MaxHeapTree::Max()
{
	return root->key;
}

bool MaxHeapTree::Exist(int key)
{
	return Exist(root, key);
}
bool MaxHeapTree::Exist(Node* n, int key)
{
	if (!n) return false;
	bool l = Exist(n->left, key);
	bool r = Exist(n->right, key);
	if (r || l) return true;
	if (n->key == key) return true;
	return false;
}


