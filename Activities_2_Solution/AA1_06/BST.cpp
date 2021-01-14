
#include "BST.h"


BST::BST()
{
	root = new Node(8);
	root->left = new Node(3);
	root->right = new Node(10);
	root->left->right = new Node(6);
	root->left->left = new Node(1);
	root->left->right->left = new Node(4);
	root->left->right->right = new Node(7);
	root->right->right = new Node(14);
	root->right->right->left = new Node(13);
}


BST::~BST()
{
}



int BST::Max()
{
	return 0;
}



bool BST::Exist(int key)
{
	return false;
}


void BST::GetKeysByOrder(std::vector<int>& v)
{
}

void BST::PreOrder()
{
	PreOrder(root);
}

void BST::PreOrder(Node* n)
{
	if (n == nullptr) return;
	std::cout << n->key << '-';  //raiz
	PreOrder(n->left);	  // se va al hijo izquierdo
	PreOrder(n->right);	  // se va al hijo derecho
}


BT::Node* BST::Search(int key) {
	return Search(root, key);
}

BT::Node* BST::Search(Node* n, int key)
{
	if (n == nullptr || n->key == key)
		return n;

	if (n->key < key) {
		return Search(n->right, key);
	}
	else
	{
		return Search(n->left, key);
	} 
		
}

int BST::Min()
{
	return Min(root);
}


int BST::Min(Node* n)
{
	if (n->left == nullptr) {
		return n->key;
	}
	else {
		return (Min(n->left));
	}
}

void BST::Insert(int key)
{
	Node* toinsert = new Node(key);
	Insert(root, toinsert);
}

bool BST::Insert(Node* n, Node* toinsert)
{
	if (n->left)
		Insert(n->left, toinsert);

	if (n->key < toinsert->key)
		if (n->right)
		{
			if (!Insert(n->right, toinsert))
			{
				Node* aux = n;
				n = toinsert;
				toinsert->left = aux;
				return true;
			}
		}
		else
		{
			Node* aux = n;
			n = toinsert;
			toinsert->left = aux;
			return true;
		}
	return false;
}
