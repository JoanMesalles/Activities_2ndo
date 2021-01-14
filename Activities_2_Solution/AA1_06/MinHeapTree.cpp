#include "MinHeapTree.h"

MinHeapTree::~MinHeapTree()
{
}

MinHeapTree::MinHeapTree() {
	root = new Node(1);
	root->left = new Node(2);
	root->right = new Node(3);
	root->left->right = new Node(4);
	root->left->right->left = new Node(6);
	root->left->right->right = new Node(7);
	root->right->right = new Node(5);
	root->right->right->left = new Node(8);


}

BT::Node* MinHeapTree::Search(int key)
{
    return nullptr;
}

bool MinHeapTree::Exist(int key)
{
    return false;
}

int MinHeapTree::Min()
{
    return root->key;
}
